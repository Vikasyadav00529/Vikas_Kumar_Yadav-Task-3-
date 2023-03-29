# Vikas_Kumar_Yadav-Task-3-

### *Approach:- To solve this problem, we will use a modified version of the A* search algorithm, incorporating the time factor, to plan the paths for the drones. The algorithm will be designed to avoid collisions between drones and ensure that they reach their destinations in the minimum time possible.

## Algorithm:-
  - Initialize the open list and closed list for the A* search algorithm, which will store the grid cells that need to be explored and the ones that have already been explored, respectively.
 -  Define the heuristic function, h(n), which will be the Euclidean or Manhattan        distance from the current cell to the destination cell, depending on whether  8-adjacency or 4-adjacency is used.
- Define the cost function, g(n), which will be the time taken to move from the starting cell to the current cell, including waiting time.
    For each drone, perform the following steps:
    1. Add the starting cell of the drone to the open list.
    2. While the open list is not empty:
       - Find the cell with the lowest f(n) = g(n) + h(n) in the open list, and remove it   from the open list.
       - If the current cell is the destination cell, reconstruct the path from the starting cell to the destination cell and store it in the output list.
       - Otherwise, add the current cell to the closed list and expand its adjacent cells.
    1. Calculate the g(n) and h(n) for each adjacent cell.
    2. If the adjacent cell is not in the closed list and not occupied by another drone at the current time step, add it to the open list.
    3. If the adjacent cell is occupied by another drone at the current time step, update the g(n) to account for the waiting time and add the cell to the open list.
Return the output list containing the paths for each drone.
## Assumptions:
 The grid is discretized into 1x1 unit cells, and drones can only occupy integer grid positions.
All drones have the same maximum speed of 1 cell/second.
Drones can wait in a cell if needed to avoid collisions.
There are no obstacles in the grid, except for other drones.
This algorithm will ensure that drones do not collide with each other, as they will plan their paths taking into account the positions and movements of other drones. Moreover, the use of the A* search algorithm with the defined cost and heuristic functions will ensure that the drones reach their destinations in the minimum time possible
