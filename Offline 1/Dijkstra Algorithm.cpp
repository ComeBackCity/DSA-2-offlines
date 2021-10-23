#include<bits/stdc++.h>
#include<fstream>
#include "List.h"
#include "MinHeap.h"
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

int dist[1000],parent[1000];

void dijkstra(int src, linkedlist<node> l[], int n)
{
    for(int i=0; i<n; i++)
    {
        dist[i]=INF;
        parent[i]=NIL;
    }

    dist[src]=0;

    MinHeap<node> h;
    h.Insert(node(src,0));

    while(!h.is_empty())
    {
        node u=h.extract_min();
        for(listNode<node>* i = l[u.getVertex()].getHead(); i!=0; i=i->next)
        {
            int v=(i->value).getVertex();
            int w=(i->value).getWeight();
            if(dist[v]>dist[u.getVertex()]+w)
            {
                dist[v]= dist[u.getVertex()]+w;
                parent[v]=u.getVertex();
                h.Insert(node(v,dist[v]));
            }
        }
    }
}

int main()
{
    char fname[99];
    gets(fname);
    ifstream fin(fname);
    ofstream fout("output.txt");


    int n,m,u,v,w,s,dir;
    fin >> n >> m >> dir;

    linkedlist<node> l[n];

    for(int i=0; i<m; i++)
    {
        fin >> u >> v >> w;
        l[u].createlistNode(node(v,w));
        if (!dir)
        {
            l[v].createlistNode(node(u,w));
        }
    }

    /*for (int i=0; i<n; i++)
    {
        listNode<node>* h = l[i].getHead();
        for(listNode<node>* i = h; i!=0; i=i->next)
        {
            fout << i->value << " ";
        }
        fout << endl;
    }*/

    fin >> s;

    dijkstra(s,l,n);

    /*for (int i=0; i<n; i++)
    {
        if (dist[i]==INF)
            fout << "INF" << " ";
        else
            fout << dist[i] << " ";
    }

    fout << endl;

    for (int i=0; i<n; i++)
    {
        if(parent[i]==NIL)
            fout << "NIL" << " ";
        else
            fout << parent[i] << " ";
    }*/

    fout << "Source:" << s << "\n" << endl;

    fout << "Vertex    Distance    Previous" << endl;

    for (int i=0; i<n; i++)
    {

        fout << i << "         ";

        if (dist[i]==INF)
            fout << "INF" << "         ";
        else if(dist[i]>=100)
            fout << dist[i] << "         ";
        else if(dist[i]>=10 && dist[i]<100)
            fout << dist[i] << "        ";
        else if(dist[i]>=0 && dist[i]<10)
            fout << dist[i] << "           ";

        if(parent[i]==NIL)
            fout << "NIL" << "         ";
        else
            fout << parent[i] << "         ";

        fout << endl;
    }

}
