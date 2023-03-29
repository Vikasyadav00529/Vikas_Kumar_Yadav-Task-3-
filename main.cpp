#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <cmath>
#include <tuple>

using namespace std;
// Define the size of the grid
const int M = 20;
const int N = 20;
// Define the Node struct
struct Node {
    int x, y, t;
    double g, h;
    Node* parent;
    // Node constructor
    Node(int x, int y, int t, double g, double h, Node* parent)
        : x(x), y(y), t(t), g(g), h(h), parent(parent) {}

    double f() const { return g + h; }
};

// Operator Overloading, For min-heap
struct Compare {
    bool operator()(const Node* a, const Node* b) {
        return a->f() > b->f();
    }
};

// Defines the boundary 
bool isValid(int x, int y) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

// Define Mahnhattan Distance
double manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Checks whether the cell is occupied or not
bool isOccupied(int x, int y, int t, const vector<vector<pair<int, int>>>& drone_positions) {
    for (const auto& positions : drone_positions) {
        if (t < positions.size() && positions[t] == make_pair(x, y)) {
            return true;
        }
    }
    return false;
}

vector<pair<int, int>> findPath(int sx, int sy, int dx, int dy, const vector<vector<pair<int, int>>>& drone_positions) {
    priority_queue<Node*, vector<Node*>, Compare> open_list; // min-heap
    vector<vector<vector<bool>>> closed_list(M, vector<vector<bool>>(N, vector<bool>(1001, false)));
    int dt[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // all the four directions we have used

    open_list.push(new Node(sx, sy, 0, 0, manhattanDistance(sx, sy, dx, dy), nullptr));

    while (!open_list.empty()) {
        Node* current = open_list.top();
        open_list.pop();

        // checking if the current cell is the destination cell
        // and reconstructing the path from the starting cell to the destination cell 
        // and storing it in the output list
        if (current->x == dx && current->y == dy) {
            vector<pair<int, int>> path;
            while (current->parent) {
                path.push_back({current->x, current->y});
                current = current->parent;
            }
            path.push_back({sx, sy});
            reverse(path.begin(), path.end());
            return path;
        }

        // if the current cell is not the destination cell
        // add the current cell to the closed list and expand its adjacent
        if (!closed_list[current->x][current->y][current->t]) {
            closed_list[current->x][current->y][current->t] = true;

            for (int i = 0; i < 4; ++i) {
                int nx = current->x + dt[i][0];
                int ny = current->y + dt[i][1];
                int nt = current->t + 1;

                if (isValid(nx, ny) && !closed_list[nx][ny][nt]) {
                    double ng = current->g + 1;
                    double nh = manhattanDistance(nx, ny, dx, dy);

                    if (!isOccupied(nx, ny, nt, drone_positions)) {
                        open_list.push(new Node(nx, ny, nt, ng, nh, current));
                    }
                }
            }
        }
    }

    return {}; // Return an empty path if no solution is found
}

int main() {
    // define the number of drones
    int num_drones;
    cin >> num_drones;
    vector<tuple<int, int, int, int, int>> input(num_drones);

    // taking the input
    for (int i = 0; i < num_drones; ++i) {
        cin >> get<0>(input[i]) >> get<1>(input[i]) >> get<2>(input[i]) >> get<3>(input[i]) >> get<4>(input[i]);
    }

    vector<vector<pair<int, int>>> drone_positions(num_drones);
      // Print the path
    for (int i = 0; i < num_drones; ++i) {
        int sx, sy, dx, dy, t;
        tie(sx, sy, dx, dy, t) = input[i];
        drone_positions[i] = findPath(sx, sy, dx, dy, drone_positions);

        cout << "Path for drone " << i + 1 << ":\n";
        for (const auto& position : drone_positions[i]) {
            cout << "(" << position.first << ", " << position.second << ")\n";
        }
    }

    return 0;
}
