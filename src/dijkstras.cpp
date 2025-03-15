#include "dijkstras.h"

// Dijkstra's algorithm to find shortest paths from source to all other vertices
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.assign(n, -1);
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    distances[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();
        
        if (dist_u > distances[u]) {
            continue;
        }
        
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            
            if (distances[u] != INF && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    
    return distances;
}


// Extract the shortest path from source to destination using the previous array
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    
    // If destination is unreachable, return empty path
    if (distances[destination] == INF) {
        return path;
    }
    
    // Safety check to prevent infinite loops
    int max_iterations = previous.size();
    int iterations = 0;
    
    // Backtrack from destination to source using the 'previous' array
    for (int at = destination; at != -1 && iterations < max_iterations; at = previous[at], iterations++) {
        path.push_back(at);
        
        // Additional safety check for cycles
        if (path.size() > 1 && path.back() == path[path.size() - 2]) {
            break; // Detected a cycle, break out
        }
    }
    
    // Reverse to get path from source to destination
    reverse(path.begin(), path.end());
    
    return path;
}

// Print the path with its total cost
void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "\nTotal cost is " << total << endl;
        return;
    }
    
    // Print the path
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " ";
        }
    }
    
    // Print the total cost
    cout << " \nTotal cost is " << total << endl;
}