Your REPORT.md file should include four sections:
Please create a new REPORT.md file and write your report there.

1. High-level overview of your design (Use diagrams and pictures for your data structures).
2. Detailed description of each function and its time complexity.
3. Time spent for each function.
4. Discussion, conclusion, and lessons learned.

Function: Autocomplete
Description: Iterate through all the data, convert the data to lowercase, and check if the data starts with the specified string. If yes, add it to the result.
Time complexity: O(n * m)

Function: GetPosition
Description: find the ID by name, and find the position by id
Time complexity: O(n)

Function: FindClosestName
Description: Use a two-dimensional array to record the cost of the string change, iterate through all the data and find the closest name.
Time complexity: O(n * m1 * m2)



Function: CycleDetection
Description: Use a two-dimensional array to record the cost of the string change, iterate through all the data and find the closest name.
Time complexity: O(n * m1 * m2)

Function: TravelingTrojan_Brute_force
Description: Use permutation to show all the situations, and use loop to calculate distance and find the minimum distance.
Time complexity: O(n * n!)

Function: TravelingTrojan_Backtracking
Description: Use DFS to recursively explore all possible scenarios, eliminate branches that exceed the minimum distance, and ultimately obtain the minimum distance.
Time complexity: O(n * n!)

Function: TravelingTrojan_2opt
Description: Iterate through swapping any two edges, and calculate the distance after the swap, then compare it with the original distance, retaining the minimum distance.
Time complexity: O(n^3)

Function: FindNearby
Description: Search for all points that meet the specified attribute values, then iterate to find the distances of points within a certain range to the center, and sort the point with the distance.
Time complexity: O(n + m^2)

Function: TrojanPath
Description: Search for all points that meet the specified attribute values, then iterate to find the distances of points within a certain range to the center, and sort the point with the distance.
Time complexity: O(n + m^2)

Function: Queries
Description: Iterate all the data, and put them in different units by tank_capacity, then distinguish if source and destination are in the same unit.
Time complexity: O(m(n + V + E))

TSP:
| Number of nodes      | Time with Brute_force | Time with Backtracking|Time with Backtracking 2opt|
| -------------------- |  |   |    |
|             |  t1        | t2    |    |