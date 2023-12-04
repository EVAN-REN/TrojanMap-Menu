#include "trojanmap.h"
#include <queue>

//-----------------------------------------------------
// TODO: Students should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id. If id does not exist, return
 * -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(const std::string &id)
{
  if (!data.count(id))
    return -1;
  else
    return data[id].lat;
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist,
 * return -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string &id)
{
  if (!data.count(id))
    return -1;
  else
    return data[id].lon;
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return
 * "NULL".
 *
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string &id)
{
  if (!data.count(id))
    return "NULL";
  else
    return data[id].name;
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node. If id does not exist, return
 * an empty vector.
 *
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(const std::string &id)
{
  std::vector<std::string> neighbors;
  if (!data.count(id))
    return neighbors;
  else
  {
    for (auto n : data[id].neighbors)
    {
      neighbors.push_back(n);
    }
    return neighbors;
  }
}

/**
 * GetID: Given a location name, return the id.
 * If the node does not exist, return an empty string.
 * The location name must be unique, which means there is only one node with the name.
 *
 * @param  {std::string} name          : location name
 * @return {std::string}               : id
 */
std::string TrojanMap::GetID(const std::string &name)
{
  for (auto it = data.begin(); it != data.end(); it++)
  {
    if (it->second.name == name)
    {
      return it->first;
    }
  }
  return "";
}

/**
 * GetPosition: Given a location name, return the position. If id does not
 * exist, return (-1, -1).
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name)
{
  std::pair<double, double> results(-1, -1);
  std::string id = GetID(name);
  if (id.empty())
    return results;
  else
    return {GetLat(id), GetLon(id)};
}

/**
 * CalculateEditDistance: Calculate edit distance between two location names
 * @param  {std::string} a          : first string
 * @param  {std::string} b          : second string
 * @return {int}                    : edit distance between two strings
 */
int TrojanMap::CalculateEditDistance(std::string a, std::string b)
{
  std::vector<std::vector<int>> dp(a.size() + 1, std::vector<int>(b.size() + 1, 0));
  int sa = a.size();
  int sb = b.size();
  for (int i = 0; i <= sa; i++)
  {
    dp[i][0] = i;
  }
  for (int i = 0; i <= sb; i++)
  {
    dp[0][i] = i;
  }
  for (int i = 1; i <= sa; i++)
  {
    for (int j = 1; j <= sb; j++)
    {
      int min = std::min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
      if (a[i - 1] == b[j - 1])
      {
        dp[i][j] = std::min(min, dp[i - 1][j - 1]);
      }
      else
      {
        dp[i][j] = std::min(min, dp[i - 1][j - 1] + 1);
      }
    }
  }
  return dp[sa][sb];
}

/**
 * FindClosestName: Given a location name, return the name with the smallest edit
 * distance.
 *
 * @param  {std::string} name          : location name
 * @return {std::string} tmp           : the closest name
 */
std::string TrojanMap::FindClosestName(std::string name)
{
  std::string tmp = ""; // Start with a dummy word
  int minDis = __INT_MAX__;
  for (auto it = data.begin(); it != data.end(); it++)
  {
    if (it->second.name == "")
    {
      continue;
    }
    int currentDis = CalculateEditDistance(name, it->second.name);
    if (currentDis < minDis)
    {
      minDis = currentDis;
      tmp = it->second.name;
    }
  }
  return tmp;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix. The function should be case-insensitive.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
bool caseInsensitiveStringCompare(std::string s1, std::string s2)
{
  for (char &c1 : s1)
  {
    if (c1 >= 'A' && c1 <= 'Z')
    {
      c1 = static_cast<char>(c1 + 32);
    }
  }
  for (char &c2 : s2)
  {
    if (c2 >= 'A' && c2 <= 'Z')
    {
      c2 = static_cast<char>(c2 + 32);
    }
  }
  return s1 == s2;
}

std::vector<std::string> TrojanMap::Autocomplete(std::string name)
{
  std::vector<std::string> results;
  int size = name.size();
  for (auto it = data.begin(); it != data.end(); it++)
  {
    std::string temp = it->second.name;
    if (temp.size() < size)
    {
      continue;
    }
    else
    {
      if (caseInsensitiveStringCompare(temp.substr(0, size), name))
      {
        results.push_back(temp);
      }
    }
  }

  return results;
}

/**
 * GetAllCategories: Return all the possible unique location categories, i.e.
 * there should be no duplicates in the output.
 *
 * @return {std::vector<std::string>}  : all unique location categories
 */
std::vector<std::string> TrojanMap::GetAllCategories()
{
  std::set<std::string> Categories;
  std::vector<std::string> res;
  for (auto &node : data)
  {
    for (const std::string &att : node.second.attributes)
      Categories.insert(att);
  }
  for (auto &cate : Categories)
    res.push_back(cate);
  return res;
}

/**
 * GetAllLocationsFromCategory: Return all the locations of the input category (i.e.
 * 'attributes' in data.csv). If there is no location of that category, return
 * (-1, -1). The function should be case-insensitive.
 *
 * @param  {std::string} category         : category name (attribute)
 * @return {std::vector<std::string>}     : ids
 */
std::vector<std::string> TrojanMap::GetAllLocationsFromCategory(
    std::string category)
{
  std::vector<std::string> res;
  if (category.empty())
    return res;
  for (auto &node : data)
  {
    for (const std::string &att : node.second.attributes)
    {
      if (att == category)
      {
        res.push_back(node.second.id);
        break;
      }
    }
  }
  if (res.empty())
    res.push_back("-1");
  if (res.empty())
    res.push_back("-1");

  return res;
}

/**
 * GetLocationRegex: Given the regular expression of a location's name, your
 * program should first check whether the regular expression is valid, and if so
 * it returns all locations that match that regular expression.
 *
 * @param  {std::regex} location name      : the regular expression of location
 * names
 * @return {std::vector<std::string>}     : ids
 */
std::vector<std::string> TrojanMap::GetLocationRegex(std::regex location)
{
  std::vector<std::string> Locations;
  for (auto &node : data)
  {
    if (std::regex_match(node.second.name, location))
    {
      Locations.push_back(node.second.id);
    }
  }
  return Locations;
}

/**
 * CalculateDistance: Get the distance between 2 nodes.
 * We have provided the code for you. Please do not need to change this function.
 * You can use this function to calculate the distance between 2 nodes.
 * The distance is in mile.
 * The distance is calculated using the Haversine formula.
 * https://en.wikipedia.org/wiki/Haversine_formula
 *
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id,
                                    const std::string &b_id)
{
  // Do not change this function
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2), 2.0) + cos(a.lat * M_PI / 180.0) *
                                           cos(b.lat * M_PI / 180.0) *
                                           pow(sin(dlon / 2), 2.0);
  double c = 2 * asin(std::min(1.0, sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations
 * inside the vector.
 * We have provided the code for you. Please do not need to change this function.
 *
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path)
{
  // Do not change this function
  double sum = 0;
  for (int i = 0; i < int(path.size()) - 1; i++)
  {
    sum += CalculateDistance(path[i], path[i + 1]);
  }
  return sum;
}
struct cmp{
  bool operator()(std::pair<double, std::string> &a, 
                  std::pair<double, std::string> &b){

      return a.first > b.first; 
  }
};
/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path
 * which is a list of id. Hint: Use priority queue.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name)
{
  std::vector<std::string> path;
  // if name uncorrect.
  std::string sourceID = GetID(location1_name);
  std::string destID = GetID(location2_name);
  if (sourceID.size() == 0 || destID.size() == 0){
    return path;
  }
  // if source = destination
  if (sourceID == destID){
    return path;
  }
  // if name correct. Initialization.
  std::unordered_set<std::string> visited;
  std::unordered_map<std::string, double> dist;
  std::unordered_map<std::string, std::string> prev;
  std::priority_queue<std::pair<double, std::string>,
                      std::vector<std::pair<double, std::string>>, cmp> Q;  

  for (auto cur : data){
    dist[cur.first] = INT_MAX/2.0;
    prev[cur.first] = cur.first;
  }

  // Start from source
  dist[sourceID] = 0;
  Q.push(std::make_pair(dist[sourceID], sourceID));

  while (!Q.empty()){
    std::pair<double, std::string> cur = Q.top();
    Q.pop();
    std::string id = cur.second;
    double distance = cur.first;
    if (visited.count(id) > 0){
      continue;
    }
    visited.insert(id);
    if (data[id].neighbors.empty()){
      continue;
    }
    if (distance > dist[id]){
      continue;
    }
    // for each neighbour
    std::vector<std::string> neighbors = data[id].neighbors;
    for (std::string neighborID : neighbors){
      double alt = dist[id] + CalculateDistance(id, neighborID);
      if (dist[neighborID] > alt){
        dist[neighborID] = alt;
        prev[neighborID] = id;
        Q.push(std::make_pair(dist[neighborID], neighborID));
      }
    }
  }
  
  if (prev[destID] == destID){
    return path;
  }
  std::string curID = destID;
  while (curID != sourceID){
    path.push_back(curID);
    curID = prev[curID];
  }
  path.push_back(sourceID);
  std::reverse(path.begin(), path.end());
  
  return path;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest
 * path which is a list of id. Hint: Do the early termination when there is no
 * change on distance.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name)
{
  std::vector<std::string> path;
  std::string sourceID = GetID(location1_name);
  std::string destID = GetID(location2_name);
  if (sourceID.empty() || destID.empty())
    return path;

  std::unordered_map<std::string, double> dist;
  std::unordered_map<std::string, std::string> prev;
  bool stop = true;

  for (auto cur : data)
  {
    dist[cur.first] = INT_MAX / 2.0;
    prev[cur.first] = cur.first;
  }
  // Initialzie source
  dist[sourceID] = 0;

  for (int i = 0; i < data.size() - 1; i++)
  {
    stop = true;
    // for each edge
    for (auto cur : data)
    {
      std::string id = cur.first;
      std::vector<std::string> neighbors = data[id].neighbors;
      for (std::string neighbor : neighbors)
      {
        double distance = CalculateDistance(id, neighbor);
        if (dist[id] + distance < dist[neighbor])
        {
          dist[neighbor] = dist[id] + distance;
          prev[neighbor] = id;
          stop = false;
        }
      }
    }
    // early termination: no relaxation this time
    if (stop == true)
    {
      break;
    }
  }
  // no path to dest
  if (prev[destID] == destID)
  {
    return path;
  }
  std::string curID = destID;
  while (curID != sourceID)
  {
    path.push_back(curID);
    curID = prev[curID];
  }
  path.push_back(sourceID);
  std::reverse(path.begin(), path.end());

  return path;
}

/**
 * Traveling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path,
 *                                                                      for example: {10.3, {{0, 1, 2, 3, 4, 0}, {0, 1, 2, 3, 4, 0}, {0, 4, 3, 2, 1, 0}}},
 *                                                                      where 10.3 is the total distance,
 *                                                                      and the first vector is the path from 0 and travse all the nodes and back to 0,
 *                                                                      and the second vector is the path shorter than the first one,
 *                                                                      and the last vector is the shortest path.
 */
// Please use brute force to implement this function, ie. find all the permutations.
double euclideanDistance(double x1, double y1, double x2, double y2)
{
  return static_cast<double>(sqrt((long double)(pow(x2 - x1, 2) + pow(y2 - y1, 2))));
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Brute_force(
    std::vector<std::string> location_ids)
{
  std::pair<double, std::vector<std::vector<std::string>>> records;
  // input is empty or one input
  if (location_ids.empty())
  {
    return records;
  }

  if (location_ids.size() == 1)
  {
    records.first = 0.0;
    records.second.push_back({location_ids[0]});
    return records;
  }

  double minDistance = 0;
  // get all permutaion and all paths
  do
  {
    double cDistance = 0;
    for (int i = 1; i < location_ids.size(); i++)
    {
      if(cDistance > minDistance && minDistance != 0){
        break;
      }
      cDistance += CalculateDistance(location_ids[i - 1], location_ids[i]);
    }
    cDistance += CalculateDistance(location_ids.back(), location_ids[0]);
    if (minDistance == 0 || cDistance < minDistance)
    {
      std::vector<std::string> path = location_ids;
      path.push_back(location_ids[0]);
      records.second.clear();
      records.second.push_back(path);
      minDistance = cDistance;
    }else if(cDistance == minDistance){
      std::vector<std::string> path = location_ids;
      path.push_back(location_ids[0]);
      records.second.push_back(path);
    }

  } while (std::next_permutation(location_ids.begin() + 1, location_ids.end()));
  records.first = minDistance;
  return records;
}

void TrojanMap::TTBT_DFS(std::vector<std::string> &location_ids, std::pair<double, std::vector<std::vector<std::string>>> &records, std::vector<std::string> &cPath, std::vector<bool> &visited, std::string cNode, int passNodeNumber, double &minDistance, double cDistance)
{
  // when all nodes have visited
  if (passNodeNumber == location_ids.size())
  {
    cDistance += CalculateDistance(cNode, location_ids[0]);
    if(cDistance < minDistance || minDistance == 0){
      std::vector<std::string> path = cPath;
      path.push_back(location_ids[0]);
      records.second.clear();
      records.second.push_back(path);
      minDistance = cDistance;
    }else if(cDistance == minDistance){
      std::vector<std::string> path = location_ids;
      path.push_back(location_ids[0]);
      records.second.push_back(path);
    }
    return;
  }

  // visit node which isn't visited
  for (int i = 1; i < location_ids.size(); i++)
  {
    if (visited[i] == false)
    {
      double nDistance = cDistance + CalculateDistance(cNode, location_ids[i]);
      if(nDistance > minDistance && minDistance != 0){
        continue;
      }
      cPath.push_back(location_ids[i]);
      visited[i] = true;
      passNodeNumber++;
      TTBT_DFS(location_ids, records, cPath, visited, location_ids[i], passNodeNumber, minDistance, nDistance);
      cPath.pop_back();
      visited[i] = false;
      passNodeNumber--;
    }
  }
}

// Please use backtracking to implement this function
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Backtracking(
    std::vector<std::string> location_ids)
{
  // input is empty
  std::pair<double, std::vector<std::vector<std::string>>> records;
  if (location_ids.empty())
  {
    return records;
  }

  if (location_ids.size() == 1)
  {
    records.first = 0.0;
    records.second.push_back({location_ids[0]});
    return records;
  }

  // using backtracking
  std::vector<bool> visited(location_ids.size(), false); // visited node
  std::vector<std::string> cPath;             // current passing path
  cPath.push_back(location_ids[0]);
  visited[0] = true;
  double minDistance = 0;
  TTBT_DFS(location_ids, records, cPath, visited, location_ids[0], 1, minDistance, 0);
  records.first = minDistance;
  return records;
}

bool ifHasDistance(const std::vector<std::vector<std::string>> &record, std::vector<std::string> compare){
  if(record.empty()){
    return false;
  }

  for(const std::vector<std::string> ids : record){
    bool flag = true;
    for(int i = 0; i < record.size(); i++){
      if(ids[i] != compare[i]){
        flag = false;
        break;
      }
    }
    if(flag){
      return true;
    }
  }
  return false;
}

// Hint: https://en.wikipedia.org/wiki/2-opt
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_2opt(
    std::vector<std::string> location_ids)
{
  std::pair<double, std::vector<std::vector<std::string>>> records;
  // input is empty or one input
  if (location_ids.empty())
  {
    return records;
  }

  if (location_ids.size() == 1)
  {
    records.first = 0.0;
    records.second.push_back({location_ids[0]});
    return records;
  }

  location_ids.push_back(location_ids[0]);

  //if have improvement
  bool improvement = true;
  while(improvement){
    improvement = false;
    for(int i = 1; i < location_ids.size() - 1; i++){
      for(int j = i + 1; j < location_ids.size() - 1; j++){
        //compare swap distance
        double curDistance = CalculateDistance(location_ids[i - 1], location_ids[i]) + CalculateDistance(location_ids[j], location_ids[j + 1]);
        double newDistance = CalculateDistance(location_ids[i - 1], location_ids[j]) + CalculateDistance(location_ids[i], location_ids[j + 1]);
        if(newDistance < curDistance){
          //swap distance
          std::reverse(location_ids.begin() + i, location_ids.begin() + j + 1);
          improvement = true;
          records.second.clear();
          records.second.push_back(location_ids);
        }else if(newDistance == curDistance){
          std::vector<std::string> newlocation = location_ids;
          std::reverse(newlocation.begin() + i, newlocation.begin() + j + 1);
          if(!ifHasDistance(records.second, newlocation)){
            records.second.push_back(newlocation);
          }
        }
      }
    }
  }
  double minDistance;
  for(int i = 1; i < location_ids.size(); i++){
    minDistance += CalculateDistance(location_ids[i - 1], location_ids[i]);
  }
  records.first = minDistance;
  return records;
}

// This is optional
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_3opt(
    std::vector<std::string> location_ids)
{
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 * We have provided the code for you. Please do not need to change this function.
 * Example:
 *   Input: "topologicalsort_locations.csv"
 *   File content:
 *    Name
 *    Ralphs
 *    KFC
 *    Chick-fil-A
 *   Output: ['Ralphs', 'KFC', 'Chick-fil-A']
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(
    std::string locations_filename)
{
  std::vector<std::string> location_names_from_csv;
  std::fstream fin;
  fin.open(locations_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, word))
  {
    location_names_from_csv.push_back(word);
  }
  fin.close();
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 * We have provided the code for you. Please do not need to change this function.
 * Example:
 *   Input: "topologicalsort_dependencies.csv"
 *   File content:
 *     Source,Destination
 *     Ralphs,Chick-fil-A
 *     Ralphs,KFC
 *     Chick-fil-A,KFC
 *   Output: [['Ralphs', 'Chick-fil-A'], ['Ralphs', 'KFC'], ['Chick-fil-A', 'KFC']]
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(
    std::string dependencies_filename)
{
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::fstream fin;
  fin.open(dependencies_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, line))
  {
    std::stringstream s(line);
    std::vector<std::string> dependency;
    while (getline(s, word, ','))
    {
      dependency.push_back(word);
    }
    dependencies_from_csv.push_back(dependency);
  }
  fin.close();
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a
 * sorting of nodes that satisfies the given dependencies. If there is no way to
 * do it, return a empty vector.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(
    std::vector<std::string> &locations,
    std::vector<std::vector<std::string>> &dependencies)
{
  std::vector<std::vector<int>> DAG(locations.size(),std::vector<int>(locations.size(),0));
  std::unordered_map<std::string,int> dir;
  std::vector<std::string> result;
  std::vector<int> vis(locations.size(),0);
  int i=0;
  for(auto &name:locations)dir[GetID(name)] = i++;
  for(int k=0;k<dependencies.size();k++)
  {
    int id1 = dir[GetID(dependencies[k][0])];
    int id2 = dir[GetID(dependencies[k][1])];
    DAG[id2][id1] = 1;//means id2 needs id1 
  }
  while(result.size()<locations.size())
  {
    for(int i=0;i<locations.size();i++)
    {
      if(vis[i])continue;
      int flag=1;
      for(int j=0;j<locations.size();j++)
      {
        if(DAG[i][j]== 1) {flag = 0;break;}
      }
      //flag = 1 means this node has no dependencies right now, we can push it into result
      if(flag)
      {
        result.push_back(locations[i]);
        vis[i] = 1;
        // use another loop to erase other nodes' dependencies to this node
        for(int k=0;k<locations.size();k++)
        {
          DAG[k][i] = 0;
        }
      }
    }
  }
  return result;
}

/**
 * inSquare: Give a id return whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square)
{
  Node curnode = data[id];
  return (curnode.lon >= square[0] && curnode.lon <= square[1] && curnode.lat <= square[2] && curnode.lat >= square[3]);
}

/**
 * GetSubgraph: Give four vertexes of the square area, return a list of location
 * ids in the squares
 *
 * @param  {std::vector<double>} square         : four vertexes of the square
 * area
 * @return {std::vector<std::string>} subgraph  : list of location ids in the
 * square
 */
std::vector<std::string> TrojanMap::GetSubgraph(std::vector<double> &square)
{
  // include all the nodes in subgraph
  std::vector<std::string> subgraph;
  for (auto &node : data)
  {
    if (inSquare(node.first, square))
    {
      subgraph.push_back(node.first);
    }
  }
  return subgraph;
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true
 * if there is a cycle path inside the square, false otherwise.
 *
 * @param {std::vector<std::string>} subgraph: list of location ids in the
 * square
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::hasCycle_DFS(std::vector<std::string> &subgraph, std::unordered_map<std::string, bool> allsubgraph, std::string cNodeId, std::string pNodeId, std::vector<double> &square)
{
  if (!inSquare(cNodeId, square))
  {
    return false;
  }
  //find cycle
  if (allsubgraph[cNodeId] == true)
  {
    if (std::find(subgraph.begin(), subgraph.end(), cNodeId) != subgraph.end())
    {
      return true;
    }
  }
  allsubgraph[cNodeId] = true;
  for (std::string neighbor : data[cNodeId].neighbors)
  {
    if(neighbor == pNodeId){
      continue;
    }
    if (hasCycle_DFS(subgraph, allsubgraph, neighbor, cNodeId, square))
    {
      return true;
    }
  }
  return false;
}

bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square)
{
  if (subgraph.size() <= 1)
  {
    return false;
  }

  // if visited
  std::unordered_map<std::string, bool> allsubgraph;
  for (auto node : data)
  {
    if (inSquare(node.first, square))
    {
      allsubgraph.insert(std::pair<std::string, bool>(node.first, false));
    }
  }

  // search cycle by DFS
  for (auto nodeid : subgraph)
  {
    if (hasCycle_DFS(subgraph, allsubgraph, nodeid, "0", square))
    {
      return true;
    }

    for (auto &node : allsubgraph)
    {
      node.second = false;
    }
  }
  return false;
}

/**
 * FindNearby: Given a class name C, a location name L and a number r,
 * find all locations in class C on the map near L with the range of r and
 * return a vector of string ids
 *
 * @param {std::string} className: the name of the class
 * @param {std::string} locationName: the name of the location
 * @param {double} r: search radius
 * @param {int} k: search numbers
 * @return {std::vector<std::string>}: location name that meets the requirements
 */
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k)
{
  std::vector<std::string> res;
  std::vector<std::string> nodesWithAttribute = GetAllLocationsFromCategory(attributesName);
  std::string curNode = GetID(name);
  for (std::string id : nodesWithAttribute)
  {
    if (id == curNode)
      continue;
    double distance = CalculateDistance(id, curNode);
    if (distance <= r)
    {
      bool flag = false;
      for(auto it = res.begin(); it != res.end(); it++){
        if(distance < CalculateDistance(curNode, *it)){
          res.insert(it, id);
          flag = true;
          break;
        }
      }
      if(!flag){
        if(res.size() < k){
          res.push_back(id);
        }
      }else{
        if(res.size() > k){
          res.pop_back();
        }
      } 
    }
  }

  return res;
}

/**
 * Shortest Path to Visit All Nodes: Given a list of locations, return the shortest
 * path which visit all the places and no need to go back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::vector<std::string> }      : the shortest path
 */

std::vector<std::string> TrojanMap::TrojanPath(
    std::vector<std::string> &location_names)
{
  std::vector<std::string> res;
  // input is empty or one input
  if (location_names.empty())
  {
    return res;
  }
  if(location_names.size() == 1){
    for(auto nodes : data){
      if(nodes.second.name == location_names[0]){
        res.push_back(nodes.first);
      }
      return res;
    }
  }

  //reflect name to index
  std::unordered_map<std::string, int> location_map;
  for(auto nodes : data){
    for(int i = 0; i < location_names.size(); i++){
      if(nodes.second.name == location_names[i]){
        location_map[location_names[i]] = i;
        break;
      }
    }
  }

  //calculate shortest path and store path
  std::vector<std::vector<double>> pathDis(location_names.size(), std::vector<double>(location_names.size(), 0));
  for(int i = 0; i < location_names.size(); i++){
    for(int j = i + 1; j < location_names.size(); j++){
      pathDis[i][j] = CalculatePathLength(CalculateShortestPath_Dijkstra(location_names[i], location_names[j]));
      pathDis[j][i] = pathDis[i][j];
    }
  }

  //brute force to solve tsp
  std::vector<std::string> pathName;
  double minDistance = 0;
  do
  {
    double cDistance = 0;
    for (int i = 1; i < location_names.size(); i++)
    {
      if(cDistance > minDistance && minDistance != 0){
        break;
      }
      cDistance += pathDis[location_map[location_names[i - 1]]][location_map[location_names[i]]];
    }
    if (minDistance == 0 || cDistance < minDistance)
    {
      pathName = location_names;
      minDistance = cDistance;
    }

  } while (std::next_permutation(location_names.begin(), location_names.end()));

  // convert name to path id
  for (int i = 1; i < location_names.size(); i++)
  {
    std::vector<std::string> pathId = CalculateShortestPath_Dijkstra(pathName[i - 1], pathName[i]);
    if(i == 1){
      res.insert(res.end(), pathId.begin(), pathId.end());
    }else{
      res.insert(res.end(), pathId.begin() + 1, pathId.end());
    }
  }
  return res;
}

/**
 * Given a vector of queries, find whether there is a path between the two locations with the constraint of the gas tank.
 *
 * @param  {std::vector<std::pair<double, std::vector<std::string>>>} Q : a list of queries
 * @return {std::vector<bool> }      : existence of the path
 */
class UnionFind{
  private:
    std::unordered_map<std::string, std::string> parent;
    std::unordered_map<std::string, int> rank;
  public:
    UnionFind(std::unordered_map<std::string, Node> &data){
      for(auto it = data.begin(); it != data.end(); it++){
        parent.insert(std::pair<std::string, std::string>(it->first, it->first));
        rank.insert(std::pair<std::string, int>(it->first, 0));
      }
    }

    //find the root of unit which include str
    std::string find(std::string str){
      if(parent[str] != str){
        parent[str] = find(parent[str]);
      }
      return parent[str];
    }

    //unite two units
    void unite(std::string s1, std::string s2){
      std::string ps1 = find(s1);
      std::string ps2 = find(s2);

      if(ps1 != ps2){
        if(rank[ps1] < rank[ps2]){
          parent[ps1] = ps2;
        }else if(rank[ps1] > rank[ps2]){
          parent[ps2] = ps1;
        }else{
          parent[ps1] = ps2;
          rank[ps2]++;
        }
      }
    }
};

std::vector<bool> TrojanMap::Queries(const std::vector<std::pair<double, std::vector<std::string>>> &q)
{
  //empty input
  std::vector<bool> ans(q.size());
  if(q.empty()){
    return ans;
  }
  ans.clear();
  //iterate all condition
  for(std::pair<double, std::vector<std::string>> query : q){
    if(query.second.size() < 2){
      ans.push_back(false);
      continue;
    }

    //create Disjoint-set
    double maxDistance = query.first;
    std::vector<std::string> nodeIds;
    UnionFind uf(data);
    for(auto it = data.begin(); it != data.end(); it++){
      for(std::string neighbor : it->second.neighbors){
        if(CalculateDistance(it->first, neighbor) <= maxDistance){
          uf.unite(it->first, neighbor);
        }
      }
      if(it->second.name == query.second[0] || it->second.name == query.second[1]){
        nodeIds.push_back(it->first);
      }
    }
    //didn't find destination
    if(nodeIds.size() != 2){
      ans.push_back(false);
    }else{
      ans.push_back(uf.find(nodeIds[0]) == uf.find(nodeIds[1]));
    } 
  }
  return ans;
}

/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * We have provided the code for you. Please do not need to change this function.
 */
void TrojanMap::CreateGraphFromCSVFile()
{
  // Do not change this function
  std::fstream fin;
  fin.open("src/lib/data.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line))
  {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ','))
    {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else
      {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        if (isalpha(word[0]))
          n.attributes.insert(word);
        if (isdigit(word[0]))
          n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}
