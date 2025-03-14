#include "dijkstras.h"

int main(int argc, char* argv[]) {
    // Check if a filename was provided
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <graph_file>" << endl;
        cout << "Example: " << argv[0] << " small.txt" << endl;
        return 1;
    }
    
    string filename = argv[1];
    Graph G;
    
    try {
        // Load the graph from file
        file_to_graph(filename, G);
        cout << "Loaded graph from " << filename << " with " << G.numVertices << " vertices." << endl;
        
        // Source vertex is 0 as specified in the assignment
        int source = 0;
        vector<int> previous;
        
        // Run Dijkstra's algorithm
        vector<int> distances = dijkstra_shortest_path(G, source, previous);
        
        // Print the results
        cout << "\nShortest paths from vertex " << source << ":" << endl;
        
        for (int i = 0; i < G.numVertices; i++) {
            cout << "To vertex " << i << ": ";
            
            // Extract and print the path
            vector<int> path = extract_shortest_path(distances, previous, i);
            
            if (distances[i] == INF) {
                cout << "No path exists" << endl;
            } else {
                print_path(path, distances[i]);
            }
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}