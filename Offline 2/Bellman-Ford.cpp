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

int dist[1000];



int Bellman_Ford(int src, linkedlist<node> l[], int n)
{
    int flag=0;

    for(int i=0; i<n; i++)
    {
        dist[i]=INF;
    }

    dist[src]=0;

    for(int k=0; k<n-1; k++)
    {
        for (int j=0; j<n ; j++)
        {
            for(listNode<node>* i = l[j].getHead(); i!=0; i=i->next)
            {
                int u=j;
                int v=(i->value).getVertex();
                int w=(i->value).getWeight();
                if(dist[u]!=INF && dist[v]>dist[u]+w)
                {
                    dist[v]= dist[u]+w;

                }
            }
        }
    }

    for (int j=0; j<n ; j++)
    {
        for(listNode<node>* i = l[j].getHead(); i!=0; i=i->next)
        {
            int u=j;
            int v=(i->value).getVertex();
            int w=(i->value).getWeight();
            if(dist[u]!=INF && dist[v]>dist[u]+w)
            {

                flag=1;
            }
        }
    }

    return flag;
}

int main()
{
    char fname[99];
    gets(fname);
    ifstream fin(fname);
    ofstream fout("output.txt");


    int n,m,u,v,w,s,dir,x;
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

    x=Bellman_Ford(s,l,n);

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

    if(x==1)
        fout << "Negative weight cycle exists"  << endl;

    else
    {

        fout << "Source:" << s << "\n" << endl;

        fout << "Vertex    Distance" << endl;

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

            fout << endl;
        }
    }
}
