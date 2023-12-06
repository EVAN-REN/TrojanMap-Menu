#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

TEST(TrojanMapTest, Autocomplete) {
  TrojanMap m;

  // Test the simple case
  std::vector<std::string> actual1 = m.Autocomplete("c");
  std::vector<std::string> expected1 = {"Chinese Street Food", "City Tacos", "Chase", "Chevron 2", "Cognoscenti Coffee Roastery", "Chucks Chicken & Waffles", "Cheebos Burger", "Crosswalk 1", "CAVA", "Cosmo Plaza", "California Family Pharmacy", "Chick-fil-A", "Chevron 1", "Cover the Homeless Ministry", "Church of Christ", "Callejon All Star", "Corwin Denney Research Center", "Crosswalk", "Carson Center", "Chipotle", "CorePower Yoga", "Chase Plaza Heliport", "Central Adult Senior High", "Central Church of Seventh Day Adventists", "City of Angels Independent Studies School", "Cal Mart Beer & Wine Food Store", "Cindys Shoes", "Chevron", "Community of Christ", "CVS Pharmacy"}; 
  EXPECT_EQ(actual1, expected1);

  // Test the upper case
  std::vector<std::string> actual2 = m.Autocomplete("CHI");
  std::vector<std::string> expected2 = {"Chinese Street Food", "Chick-fil-A", "Chipotle"}; 
  EXPECT_EQ(actual2, expected2);

  // Test the null 
  std::vector<std::string> actual3 = m.Autocomplete(""); 
  std::vector<std::string> expected3 = {}; 
  EXPECT_EQ(actual3, expected3);
}

TEST(TrojanMapTest, FindPosition) {
  TrojanMap m;
  // Test Ralphs
  std::pair<double, double> actual1 = m.GetPosition("Ralphs");
  std::pair<double, double> expected1(34.0317653, -118.2908339);
  EXPECT_EQ(actual1, expected1);

  // Test Target
  std::pair<double, double> actual2 = m.GetPosition("Target");
  std::pair<double, double> expected2(34.0257016, -118.2843512);
  EXPECT_EQ(actual2, expected2);

  // Test null
  std::pair<double, double> actual3 = m.GetPosition("");
  std::pair<double, double> expected3(-1, -1);
  EXPECT_EQ(actual3, expected3);
}

// Test FindClosestName function
TEST(TrojanMapTest, FindClosestName) {
  TrojanMap m;
  EXPECT_EQ(m.FindClosestName("Cha"), "Chase");
  EXPECT_EQ(m.FindClosestName("Targe"), "Target");
  EXPECT_EQ(m.FindClosestName(""), "66");
}



// Test cycle detection function
TEST(TrojanMapTest, CycleDetection) {
  TrojanMap m;
  
  std::vector<double> square1 = {-118.299, -118.264, 34.032, 34.011};
  auto subgraph1 = m.GetSubgraph(square1);
  bool result1 = m.CycleDetection(subgraph1, square1);
  EXPECT_EQ(result1, true);

  std::vector<double> square2 = {-118.290, -118.289, 34.030, 34.020};
  auto subgraph2 = m.GetSubgraph(square2);
  bool result2 = m.CycleDetection(subgraph2, square2);
  EXPECT_EQ(result2, false);
}

TEST(TrojanMapTest, TSP_Brute_force_3nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"8566227783","8566227656","6816180153"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_Brute_force(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::vector<std::string>> expected{{"8566227783", "8566227656", "6816180153", "8566227783"}};
  std::cout << "By Brute force, 3 nodes run time: " << duration.count() << "ms" << std::endl;
  
  EXPECT_EQ(actual, expected);
}


TEST(TrojanMapTest, TSP_Backtracking_3nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"8566227783","8566227656","6816180153"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_Backtracking(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::vector<std::string>> expected{{"8566227783", "8566227656", "6816180153", "8566227783"}};
  std::cout << "By Backtracking, 3 nodes run time: " << duration.count() << "ms" << std::endl;
  
  EXPECT_EQ(actual, expected);
}

TEST(TrojanMapTest, TSP_2opt_3nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"8566227783","8566227656","6816180153"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_2opt(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::vector<std::string>> expected{{ "8566227783", "6816180153", "8566227656", "8566227783" }};
  std::cout << "By 2opt, 3 nodes run time: " << duration.count() << "ms" << std::endl;

  EXPECT_EQ(actual, expected);
}


TEST(TrojanMapTest, TSP_Brute_force_4nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"6820935923","122702233","8566227656","6816180153"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_Brute_force(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::vector<std::string>> expected{{"6820935923", "6816180153", "122702233", "8566227656", "6820935923"}};
  std::cout << "By Brute force, 4 nodes run time: " << duration.count() << "ms" << std::endl;
  
  EXPECT_EQ(actual, expected);
}

TEST(TrojanMapTest, TSP_Backtracking_4nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"6820935923","122702233","8566227656","6816180153"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_Backtracking(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::vector<std::string>> expected{{"6820935923", "6816180153", "122702233", "8566227656", "6820935923"}};
  std::cout << "By Backtracking, 4 nodes run time: " << duration.count() << "ms" << std::endl;
  
  EXPECT_EQ(actual, expected);
}

TEST(TrojanMapTest, TSP_2opt_4nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"6820935923","122702233","8566227656","6816180153"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_2opt(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::vector<std::string>> expected{{"6820935923", "8566227656", "122702233", "6816180153", "6820935923"}};
  std::cout << "By 2opt, 4 nodes run time: " << duration.count() << "ms" << std::endl;

  EXPECT_EQ(actual, expected);
}

TEST(TrojanMapTest, TSP_Brute_force_5nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"6820935923","1873055993","7771782316","8566227656","6816180153"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_Brute_force(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::vector<std::string>> expected{{"6820935923", "1873055993", "8566227656", "6816180153", "7771782316", "6820935923"}};
  std::cout << "By Brute force, 5 nodes run time: " << duration.count() << "ms" << std::endl;
  
  EXPECT_EQ(actual, expected);
}

TEST(TrojanMapTest, TSP_Backtracking_5nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"6820935923","1873055993","7771782316","8566227656","6816180153"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_Backtracking(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::vector<std::string>> expected{{"6820935923", "1873055993", "8566227656", "6816180153", "7771782316", "6820935923"}};
  std::cout << "By Backtracking, 5 nodes run time: " << duration.count() << "ms" << std::endl;
  
  EXPECT_EQ(actual, expected);
}

TEST(TrojanMapTest, TSP_2opt_5nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"6820935923","1873055993","7771782316","8566227656","6816180153"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_2opt(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::vector<std::string>> expected{{"6820935923", "7771782316", "6816180153", "8566227656", "1873055993", "6820935923"}};
  std::cout << "By 2opt, 5 nodes run time: " << duration.count() << "ms" << std::endl;

  EXPECT_EQ(actual, expected);
}


TEST(TrojanMapTest, TSP_Brute_force_6nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976", "122702233", "8566227783", "6816180153", "4009734472", "5917800482"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_Brute_force(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::vector<std::string>> expected{{"6819019976", "5917800482", "4009734472", "6816180153", "8566227783", "122702233", "6819019976"}};
  std::cout << "By Brute force, 6 nodes run time: " << duration.count() << "ms" << std::endl;
  
  EXPECT_EQ(actual, expected);
}

TEST(TrojanMapTest, TSP_Backtracking_6nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976", "122702233", "8566227783", "6816180153", "4009734472", "5917800482"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_Backtracking(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::vector<std::string>> expected{{"6819019976", "5917800482", "4009734472", "6816180153", "8566227783", "122702233", "6819019976"}};
  std::cout << "By Backtracking, 6 nodes run time: " << duration.count() << "ms" << std::endl;
  
  EXPECT_EQ(actual, expected);
}

TEST(TrojanMapTest, TSP_2opt_6nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976", "122702233", "8566227783", "6816180153", "4009734472", "5917800482"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_2opt(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::vector<std::string>> expected{{"6819019976", "5917800482", "4009734472", "6816180153", "8566227783", "122702233", "6819019976"}};
  std::cout << "By 2opt, 6 nodes run time: " << duration.count() << "ms" << std::endl;

  EXPECT_EQ(actual, expected);
}

TEST(TrojanMapTest, TSP_Brute_force_7nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976", "6813379578", "7360410808", "8566227656", "5567738306", "5172201326", "8566227783"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_Brute_force(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::vector<std::string>> expected{{"6819019976", "8566227656", "5567738306", "8566227783", "6813379578", "7360410808", "5172201326", "6819019976"}};
  std::cout << "By Brute force, 7 nodes run time: " << duration.count() << "ms" << std::endl;
  
  EXPECT_EQ(actual, expected);
}

TEST(TrojanMapTest, TSP_Backtracking_7nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976", "6813379578", "7360410808", "8566227656", "5567738306", "5172201326", "8566227783"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_Backtracking(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::string> expected{"6819019976", "8566227656", "5567738306", "8566227783", "6813379578", "7360410808", "5172201326", "6819019976"};
  std::cout << "By Backtracking, 7 nodes run time: " << duration.count() << "ms" << std::endl;
  
  EXPECT_EQ(actual[0], expected);
}

TEST(TrojanMapTest, TSP_2opt_7nodes) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976", "6813379578", "7360410808", "8566227656", "5567738306", "5172201326", "8566227783"};
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<std::string>> actual = m.TravelingTrojan_2opt(input).second;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::vector<std::vector<std::string>> expected{{"6819019976", "5172201326", "7360410808", "6813379578", "8566227783", "5567738306", "8566227656", "6819019976"}};
  std::cout << "By 2opt, 7 nodes run time: " << duration.count() << "ms" << std::endl;

  EXPECT_EQ(actual, expected);
}