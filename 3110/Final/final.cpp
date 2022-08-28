#include <iostream>
#include <vector>
#include <algorithm>

#define graphEdge std::pair<int, int>
  
class Graph 
{

private:
    int V;                                      // number of nodes in graph
    std::vector<std::pair<int, graphEdge>> G;   // std::vector for graph
    std::vector<std::pair<int, graphEdge>> T;   // std::vector for mst
    int *parent;
     
public:
    Graph(int V) 
    {
        parent = new int[V];
    
        for (int i = 0; i < V; i++)
            parent[i] = i;
        
        G.clear();
        T.clear();
    }

    ~Graph()
    {
        delete [] parent;
    }

    void AddEdge(int u, int v, int wt) 
    {
        G.push_back(make_pair(wt, graphEdge(u, v)));
    }

    int FindSet(int i) 
    {
        
        if (i == parent[i])
            return i;
        else
    
            return FindSet(parent[i]);
    }

    void unionSet(int u, int v) 
    {
        parent[u] = parent[v];
    }

    void Kruskal() 
    {
        int i, uSt, vEd;

        // Fat shame edges and sort based on weight
        std::sort(G.begin(), G.end()); 
        for (i = 0; i < G.size(); i++) 
        {
            uSt = FindSet(G[i].second.first);
            vEd = FindSet(G[i].second.second);
            if (uSt != vEd) 
            {
                T.push_back(G[i]);
                unionSet(uSt, vEd);
            }
        }
    }

    void DisplayMST() 
    {
        std::cout << "Edge :" << " Weight" << std::endl;
        for (int i = 0; i < T.size(); i++) 
        {
            std::cout << T[i].second.first << " - " << T[i].second.second << " : "
                    << T[i].first;
            std::cout << std::endl;
        }
    }
};


int main() 
{
    Graph g(5);
    g.AddEdge(0,1,9);
    g.AddEdge(0,3,16);
    g.AddEdge(2,8,2);
    g.AddEdge(3,4,1);
    g.AddEdge(4,4,5);
     
    g.Kruskal();
    std::cout<<"The Minimum Spanning Tree according to Kruskal's Algorithm:"<< std::endl;
    g.DisplayMST();
    return 0;
}