#include<bits/stdc++.h>
#define pii pair< int, int >
#define pip pair < int, pii >
using namespace std;

class Graph
{
    int V,E;
    vector< pii > edgeList;
    int *degree;

public:
    Graph();
    Graph(int n, int m);
    void addEdge(int u, int v);
    int VertexCover1();
    int VertexCover2();

};

Graph::Graph(int n, int m)
{
    this->V=n;
    this->E=m;
    degree= new int[V];
    for(int i=0; i<V; i++)
    {
        degree[i]=0;
    }
}

void Graph::addEdge(int u, int v)
{
    pii p;
    p=make_pair(u,v);
    degree[u]+=1;
    degree[v]+=1;
    edgeList.push_back(p);
}

int Graph::VertexCover1()
{
    int vCov=0;

    bool visited[V];
    for (int i=0; i<V; i++)
        visited[i] = false;

    srand(unsigned(time(0)));

    random_shuffle(edgeList.begin(), edgeList.end());

    for(int i=0; i<E; i++)
    {
        pii p=edgeList[i];
        int u=p.first;
        int v=p.second;

        if(visited[u]==false && visited[v]==false)
        {
            visited[u]=true;
            visited[v]=true;
            //cout << "Accepted " << u << " , " << v << endl;
        }
    }

    for(int i=0; i<V; i++)
    {
        if(visited[i]==true)
            vCov++;
    }

    return vCov;

}

int Graph:: VertexCover2()
{
    int vCov = 0;
    bool visited[V];
    bool edgeVisited[E];
    for(int i=0 ; i<V ; i++)
        visited[i] = false;
    for(int i=0 ; i<E ; i++)
        edgeVisited[i] = false;
    for(int i = 0 ; i<E ; i++)
    {
        int idx = -1;
        int mx = 0;
        int u,v;
        for(int j=0 ; j<E ; j++)
        {
            u = edgeList[j].first;
            v = edgeList[j].second;
            if(edgeVisited[j] == false && degree[u]+degree[v] > mx)
            {
                mx = degree[u]+degree[v];
                idx = j;
            }
        }
        if(idx != -1)
        {
            vCov += 2;
            //cout<<edgeList[idx].first<<" "<<edgeList[idx].second<<endl;
            edgeVisited[idx] = true;
            u = edgeList[idx].first;
            v = edgeList[idx].second;
            visited[u] = true;
            visited[v] = true;
            degree[u] = 0;
            degree[v] = 0;
            for(int k=0 ; k<E ; k++)
            {
                if(edgeVisited[k] == false)
                {
                    if(edgeList[k].first == u && degree[edgeList[k].second]>0)
                    {
                        degree[edgeList[k].second]--;
                        edgeVisited[k]=true;
                    }
                    else if(edgeList[k].second == u && degree[edgeList[k].first]>0)
                    {
                        degree[edgeList[k].first]--;
                        edgeVisited[k]=true;
                    }
                    else if(edgeList[k].first == v && degree[edgeList[k].second]>0)
                    {
                        degree[edgeList[k].second]--;
                        edgeVisited[k]=true;
                    }
                    else if(edgeList[k].second == v && degree[edgeList[k].first]>0)
                    {
                        degree[edgeList[k].first]--;
                        edgeVisited[k]=true;
                    }
                }
            }

        }
        else
            break;

    }
    return vCov;
}

int main()
{

        //char fileName[] = "frb30-15-1.mis";
        char fileName[] = "test1.txt";

        if(freopen(fileName,"r",stdin))
            cout<<"FIle loaded successfully"<<endl;
        else
            cout<<"FIle loaded unsuccessfully"<<endl;

        string s;
        cin>>s>>s;
        int n,e,u,v;
        cin>>n>>e;
        Graph g(n,e);
        for(int i=0; i<e; i++)
        {
            cin>>s>>u>>v;
            g.addEdge(u-1,v-1);
            //cout<<s<<" "<<u<<" "<<v<<endl;

        }


        cout << g.VertexCover2() << endl;
        cout << g.VertexCover1() << endl;



}
