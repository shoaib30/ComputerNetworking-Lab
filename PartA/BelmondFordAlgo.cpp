#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include<iostream>
using namespace std;
struct Edge
{
    int src, dest, weight;
};
struct Graph
{
    int V, E;
    Edge* edge;
};
struct Graph createGraph(int V, int E)
{
    Graph graph;
    graph.V = V;
    graph.E = E;
    graph.edge = new Edge[E];
    return graph;
}
void printArr(int dist[], int n)
{
    cout<<"Vertex\tDistance\n";
    for (int i = 0; i < n; ++i)
        cout<<i<<"\t"<<dist[i]<<endl;
}
void BellmanFord(Graph graph, int src)
{
    int V = graph.V;
    int E = graph.E;
    int dist[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;
    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph.edge[j].src;
            int v = graph.edge[j].dest;
            int weight = graph.edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
    printArr(dist, V);
    return;
}

int main()
{
    int V;
    int E;
    cout<<"Enter number of vertices: ";
    cin>>V;
    cout<<"Enter number of edges: ";
    cin>>E;
    struct Graph graph = createGraph(V, E);
    for(int i = 0; i < E; i++)  {
        cout<<"Enter source of E"<<i<<": ";
        cin>>graph.edge[i].src;
        cout<<"Enter Dest of E"<<i<<": ";
        cin>>graph.edge[i].dest;
        cout<<"Enter Weight of E"<<i<<": ";
        cin>>graph.edge[i].weight;
    }
    BellmanFord(graph, 0);
    return 0;
}
