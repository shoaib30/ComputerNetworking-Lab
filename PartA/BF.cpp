#include<iostream>
#include<limits.h>
using namespace std;

#define MAX_NODES 10

int graph[MAX_NODES][MAX_NODES];
int nextHop[MAX_NODES];

int findNextHop(int node, int src){
    if(nextHop[node] == src)
        return node;
    return findNextHop(nextHop[node],src);
}

void BellmanFord(int numNodes, int src) {
    int dist[numNodes];
    for(int i = 0; i < numNodes; i++){
        dist[i] = INT_MAX;
        nextHop[i] = 0;
    }
    dist[src] = 0;
    nextHop[src] = src;
    int x=numNodes;
    do{
        for(int i = 0; i < numNodes; i++) {
            //cout<<endl<<"I\tJ\tSrc\tDest\tWt\tdist[s]\tdist[d]"<<endl;
            for(int j = 0; j < numNodes; j++)   {

                if(graph[i][j]>=0)  {
                    int s = i;
                    int d = j;
                    int wt = graph[i][j];
                    //cout<<i<<"\t"<<j<<"\t"<<s<<"\t"<<d<<"\t"<<wt<<"\t"<<dist[s]<<"\t"<<dist[d]<<endl;
                    if(dist[s] != INT_MAX && dist[s]+wt < dist[d])  {
                        dist[d] = dist[s]+wt;
                        nextHop[d]=findNextHop(s,src);
                    }
                }
            }
        }
    }while(--x);
    cout<<"\nDist from "<<src<<":\n";
    cout<<"SOURCE\tDEST\tDIST\tNEXT\n";
    for(int i=0;i<numNodes;i++) {
            cout<<src<<"\t"<<i<<"\t"<<dist[i]<<"\t";
            if(nextHop[i]==src)
                cout<<"-";
            else
                cout<<nextHop[i];
            cout<<endl;
    }
}

int main()  {
    cout<<"Enter number of nodes: ";
    int numNodes;
    cin>>numNodes;
    cout<<"Enter the graph: \n";
    for(int i = 0; i < numNodes; i++){
        for(int j = 0; j <numNodes; j++){
            int temp;
            cin>>graph[i][j];
//            if(temp >= 9)
//                temp = -1;
            //graph[i][j] = temp;
        }
    }
    cout<<"Enter the source node: ";
    int src;
    cin>>src;
//    for(int i = 0; i < numNodes; i++){
//        for(int j = 0; j <numNodes; j++){
//            cout<<graph[i][j]<<"  ";
//        }
//        cout<<endl;
//    }
    BellmanFord(numNodes, src);
}

/*
0 3 2 5 9 9
3 0 9 1 4 9
2 9 0 2 9 1
5 1 2 0 3 9
9 4 9 3 0 2
*/
/*
0 3 2 5 -1 -1
3 0 -1 1 4 -1
2 -1 0 2 -1 1
5 1 2 0 3 -1
-1 4 -1 3 0 2
-1 -1 1 -1 2 0
*/
/*
0 3 2 5 -1 -1 3 0 -1 1 4 -1 2 -1 0 2 -1 1 5 1 2 0 3 -1 -1 4 -1 3 0 2 -1 -1 1 -1 2 0
*/
