#include "dijkstras.h"
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    struct Node{
        int vertex;
        int weight;
        Node(int a, int b){
            vertex = a;
            weight = b;
        }
    };
    struct Compare{
        bool operator()(Node a, Node b){
            return a.weight > b.weight;
        }
    };
    int n = G.numVertices;
    vector<int> distance(n, INF);
    for (int i = 0; i < n; ++i){
        previous[i] = -1;
    }
    vector<bool> visited(n, false);
    priority_queue<Node, vector<Node>, Compare> q;
    q.push(Node(source, 0));
    distance[source] = 0;
    while (!q.empty()){
        int current = q.top().vertex;
        q.pop();
        if (visited[current]){
            continue;
        }
        visited[current] = true;
        for (auto e: G[current]){
            int a = e.dst;
            int b = e.weight;
        if (!visited[a] && distance[current] + b < distance[a]){
            distance[a] = distance[current] + b;
            previous[a] = current;
            q.push(Node(a, distance[a]));
        }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<int> path;
    for (int i = destination; i != -1; i = previous[i]){
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total){
    for (auto e: v){
        cout << e << endl;
    }
    cout << "Total cost is " << total;
}