/*
Source code - Data Sructures and Algorithm - ET2100, Semester 20241
Student: Dang Quang Vu, ID: 20223830, Class ID: 154832
Topic 1: Search for directions on HUST map:
	- Create a HUST map (Google Maps API) (including buildings)  
	- Represent maps using a graph structure 
	- Find the shortest path between two points on the map
*/


#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm> 
using namespace std;

// Structure the graph
struct Edge {
    string to;  // destination node - name of building
    int weight; // weight - distance between 2 buildings
};

// Function to add an weight (distance) between 2 nodes (buildings)
void addEdge(unordered_map<string, vector<Edge>>& graph, const string& u, const string& v, int w) {
    graph[u].push_back({v, w}); // add edge from u to v
    graph[v].push_back({u, w}); // add edge from v to u
} // adding two edges from u to v and from v to u because the undirected graph has weights

// Dijkstra algorithm to find the shortest path from start to target
pair<vector<string>, unordered_map<string, int>> dijkstra(const unordered_map<string, vector<Edge>>& graph, const string& start, const string& target) {
    unordered_map<string, int> dist;    // storage the shortest distance
    unordered_map<string, string> prev; // storage the previous node

	//initialize distance to infinity and previous node is empty
    for (const auto& node : graph) {
        dist[node.first] = INT_MAX; // in <climits> lib, INT_MAX = 2147483647 = 2^31 - 1, perform for infinity
    }
    dist[start] = 0; // distance to the start node is 0

	// min-heap (priority queue) to store nodes to explore
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push(make_pair(0, start)); // start with "inited" node

    while (!pq.empty()) {
        pair<int, string> current = pq.top();   // get the node with smallest distance
        pq.pop();                               
        int d = current.first;                  // distance to the current node
        string u = current.second;              // current node

        if (u == target) break;                 // stop if reach the target node

        for (const auto& edge : graph.at(u)) {  // explore neighbor of current node
            string v = edge.to;                 // neighbor node
            int w = edge.weight;                // weight of edge
            if (dist[v] > dist[u] + w) {        // RELAXATION STEP: check the shorter path
                dist[v] = dist[u] + w;          // update the shortest distance
                prev[v] = u;                    // update previous node
                pq.push(make_pair(dist[v], v)); // add the neighbor the the priority queue
            }
        }
    }

	// create the shortest path from 'start' to 'target'
    vector<string> path;
    for (string at = target; !at.empty(); at = prev[at]) {
        path.push_back(at);                     // add each node in the path
        if (prev.find(at) == prev.end()) break; // stop if there's no previous node
    }
    reverse(path.begin(), path.end()); // reverse to get the correct order, using <algorithm> lib
    return {path, dist}; // return the shortest path and distances
}

int main() {
    unordered_map<string, vector<Edge>> graph; // initialize graph

    addEdge(graph, "C1", "C2", 20);   // from C1 to C2, disstance approximate 20 meters
    addEdge(graph, "C1", "C3", 20);   // similar
    addEdge(graph, "C2", "C4", 50);   // similar
    addEdge(graph, "C2", "C5", 50);   // similar
    addEdge(graph, "C2", "C9", 20);   // similar
    addEdge(graph, "C9", "C5", 80);   // similar
    addEdge(graph, "C9", "C10", 60);  // similar
    addEdge(graph, "C9", "TV", 100);  // similar
    addEdge(graph, "C3", "C4", 20);   // similar
    addEdge(graph, "C4", "C5", 20);   // similar
    addEdge(graph, "C5", "C10", 20);  // similar
    addEdge(graph, "C10", "TV", 40);  // similar
    addEdge(graph, "C10", "D3", 50);  // similar
    addEdge(graph, "TV", "D3", 20);   // similar
    addEdge(graph, "D3", "C7", 20);   // similar
    addEdge(graph, "D3", "D3-5", 5);  // similar
    addEdge(graph, "C7", "C6", 20);   // similar
    addEdge(graph, "C6", "C1B", 20);  // similar
    addEdge(graph, "C1B", "C3", 20);  // similar
    addEdge(graph, "D3", "D5", 20);   // similar
    addEdge(graph, "D3", "B1", 120);  // similar
    addEdge(graph, "D3-5", "D5", 5);  // similar
    addEdge(graph, "D3-5", "D7", 5);  // similar
    addEdge(graph, "D3-5", "C7", 20); // similar
    addEdge(graph, "D5", "D7", 5);    // similar
    addEdge(graph, "D5", "D9", 20);   // similar
    addEdge(graph, "D5", "TV", 20);   // similar
    addEdge(graph, "D7", "D9", 5);    // similar
    addEdge(graph, "D9", "TV", 80);   // similar
    addEdge(graph, "D9", "D8", 80);   // similar
    addEdge(graph, "D8", "TV", 100);  // similar
    addEdge(graph, "D8", "D6", 10);   // similar
    addEdge(graph, "D8", "D4", 10);   // similar
    addEdge(graph, "D6", "D4", 10);   // similar
    addEdge(graph, "D6", "TV", 70);   // similar
    addEdge(graph, "B1", "B8", 20);   // similar
    addEdge(graph, "B1", "T", 360);   // similar
    addEdge(graph, "B1", "TC", 360);  // similar
    addEdge(graph, "B8", "T", 380);   // similar
    addEdge(graph, "B8", "B7", 20);   // similar
    addEdge(graph, "B7", "B6", 20);   // similar
    addEdge(graph, "T", "TC", 170);   // similar
    // additional edges, nodes

    string start, target;              // variable user input
    cout << "Nhap toa nha hien tai: ";
    cin >> start;                      // type current building
    cout << "Nhap toa nha muon den: ";
    cin >> target;					   // type target building 

	// call Dijkstra algorithm func
    auto result = dijkstra(graph, start, target);
    vector<string> path = result.first;
    unordered_map<string, int> dist = result.second;

    if (path.size() == 1 && path[0] != target) {
        cout << "Khong tim thay duong di!" << endl; // no path found!!!
    } else {
        cout << "Duong di ngan nhat: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << endl;

        cout << "Do dai duong di ngan nhat khoang: " << dist[target] << " met." << endl;
    }
    return 0;
}
