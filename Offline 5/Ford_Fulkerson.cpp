#include<bits/stdc++.h>
#include<fstream>
#include "List.h"
#include "queue.h"
#define INF 99999999
#define NIL -9999

using namespace std;

class node
{
    int vertex;
    int weight;
public:
    node();
    node(int x, int w);
    int getVertex();
    int getWeight();
    bool operator<(node &rhs)
    {
        return this->getWeight()<rhs.getWeight();
    }

    bool operator>(node &rhs)
    {
        return this->getWeight()>rhs.getWeight();
    }
    friend ostream& operator<<(ostream& os, const node& rhs)
    {
        os << "(" << rhs.vertex <<"," << rhs.weight <<")"<< " ";
        return os;
    }
    ~node();

};

node::node()
{
    vertex=0;
    weight=0;
}

node::node(int x,int w)
{
    vertex=x;
    weight=w;
}

int node::getVertex()
{
    return vertex;
}

int node::getWeight()
{
    return weight;
}

node::~node()
{
    vertex=0;
    weight=0;
}

int visited[1000],parent[1000],dist[1000];

void bfs(int src, linkedlist<node> l[], int n, int **resGraph)
{
    for (int i=0; i<n; i++)
    {
        visited[i]=false;
        parent[i]=NIL;
    }

    parent[src]=NIL;

    Queue<int> q(n);

    q.enQueue(src);
    while(!q.isEmpty())
    {
        int u=q.deQueue();
        for(listNode<node>* i = l[u].getHead(); i!=0; i=i->next)
        {
            int v=(i->value).getVertex();
            if(!visited[v] && resGraph[u][v]>0)
            {
                parent[v]=u;
                q.enQueue(v);
            }
        }
        visited[u]=true;
    }

}

void ford_fulkerson(int src, int t, linkedlist<node> l[], int n, int **graph)
{

    int **resGraph, max_flow=0,u,v;

    resGraph= new int *[n];
    for (int i=0; i<n; i++)
    {
        resGraph[i]=new int[n];
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            resGraph[i][j]=0;
        }
    }

    for(int j=0; j<n; j++)
    {
        for(listNode<node>* i = l[j].getHead(); i!=0; i=i->next)
        {
            int v=(i->value).getVertex();
            int w=(i->value).getWeight();
            resGraph[j][v]=w;
        }
    }

    bfs(src, l, n, resGraph);

    while(visited[t])
    {
        int path_flow=INF;

        for (v=t; v!=src; v=parent[v])
        {
            //cout << v << endl;
            u = parent[v];
            path_flow = min(path_flow, resGraph[u][v]);
        }

        for (v=t; v != src; v=parent[v])
        {
            u = parent[v];
            resGraph[u][v] -= path_flow;
            resGraph[v][u] += path_flow;
        }

        max_flow += path_flow;

        bfs(src, l, n, resGraph);
    }

    cout << "Max Flow is: " << max_flow << endl;

    //bfs(src, l, n, resGraph);

    cout << "\nMin Cut edges are: " <<  endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (visited[i] && !visited[j] && graph[i][j])
            {
                cout << "(" << i << "," << j << ")" <<endl;
            }
        }
    }


    cout << "\nMax flow along each edge is: " << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j]>0)
            {
                cout << "(" << i << "," << j << ")" << " -> " << resGraph[j][i] << endl;
            }
        }
    }
}

int main()
{
    char fname[99];
    gets(fname);
    freopen(fname,"r",stdin);
    freopen("output.txt","w",stdout);


    int n,m,u,v,w,s,t;
    cin >> n >> m;

    linkedlist<node> l[n];
    int **graph;

    graph= new int *[n];
    for (int i=0; i<n; i++)
    {
        graph[i]=new int[n];
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            graph[i][j]=0;
        }
    }

    for(int i=0; i<m; i++)
    {
        cin >> u >> v >> w;
        l[u].createlistNode(node(v,w));
        graph[u][v]=w;
        //edgelist[i]=make_pair(u,v);
        l[v].createlistNode(node(u,0));

    }


    cin >> s >> t;

    ford_fulkerson(s, t, l, n, graph);


}
