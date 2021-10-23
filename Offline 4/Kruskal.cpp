#include<bits/stdc++.h>
#include<fstream>
#include "List.h"
#include "MinHeap.h"
#include "Disjoint Set.h"
#define INF 99999999
#define NIL -9999

using namespace std;

/*class node
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
}*/


class edge
{
    int src;
    int dest;
    int weight;
public:
    edge();
    edge(int x, int y, int z);
    int getSrc();
    int getDest();
    int getWeight();
    bool operator<(edge &rhs)
    {
        return this->getWeight()<rhs.getWeight();
    }

    bool operator>(edge &rhs)
    {
        return this->getWeight()>rhs.getWeight();
    }
    friend ostream& operator<<(ostream& os, const edge& rhs)
    {
        os << "(" << rhs.src <<"," << rhs.dest <<")"<< " ";
        return os;
    }
    ~edge();

};

edge::edge()
{
    src=0;
    dest=0;
    weight=0;
}

edge::edge(int x,int y, int z)
{
    src=x;
    dest=y;
    weight=z;
}

int edge::getSrc()
{
    return src;
}

int edge::getDest()
{
    return dest;
}

int edge::getWeight()
{
    return weight;
}

edge::~edge()
{
    src=0;
    dest=0;
    weight=0;
}


edge MST[1000];

void Kruskal_MST(edge graph[], int m, int n)
{
    int u,v,w,j=0;
    MinHeap<edge> h;
    Disjoint_Set<int> ds(n);
    edge e;

    for(int i=0; i<n; i++)
    {
        ds.make_set(i);
    }

    for(int i=0; i<m; i++)
    {
        h.Insert(graph[i]);
    }

    cout << "Added Edges:\n" <<  endl;

    while(!h.is_empty())
    {

        e=h.extract_min();
        u=e.getSrc();
        v=e.getDest();
        w=e.getWeight();
        if(ds.Find_set(u)!=ds.Find_set(v))
        {
            MST[j]=e;
            ds.Union(u,v);
            j=j+w;
            cout << e << endl;

        }



    }

    cout << "\nMST weight:"  << j << endl;


}

int main()
{
    char fname[99];
    gets(fname);
    freopen(fname,"r",stdin);
    freopen("output.txt","w",stdout);


    int n,m,u,v,w;
    cin >> n >> m ;

    edge graph[m];

    for(int i=0; i<m; i++)
    {
        cin >> u >> v >> w;
        graph[i] = edge(u,v,w);
    }

    Kruskal_MST(graph, m ,n);


}
