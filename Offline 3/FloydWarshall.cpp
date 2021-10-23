#include<bits/stdc++.h>
#include<fstream>
#define INF 999999
#define NIL -9999
#define num 200

using namespace std;

int dist[100][100],prev[100][100];


void printGraph(int **graph,int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
                cout << "INF\t"  ;
            else
                cout << graph[i][j] << "\t" ;
        }
        cout << endl;
    }
}

void printDistance(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] == INF)
                cout << "INF\t" ;
            else
            {
                cout << dist[i][j] << "\t" ;

            }
        }
        cout << endl;
    }
}

void printPrevious(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (prev[i][j] == NIL)
                cout << "NIL\t" ;
            else
                cout << prev[i][j] << "\t" ;
        }
        cout << endl;
    }
}

void FloydWarshall(int **graph,int n)
{
    //int dist[n][n], prev[n][n];

    //printGraph(graph,n);

    int negc=0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dist[i][j] = graph[i][j];
            if(graph[i][j]!=INF)
                prev[i][j]=i;
            else
                prev[i][j] = NIL;
        }
    }

    //printDistance(n);


    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k]!=INF && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    prev[i][j] = prev[k][j];
                }
            }
        }
    }

    for(int i=0; i<n; i++)
    {
        if(dist[i][i]<0)
            negc=1;
    }

    if(negc==0)
    {
        cout << "Distance Matrix:" << endl;

        printDistance(n);

        cout << endl;

        cout << "Predecessor Matrix:" << endl;

        printPrevious(n);

        cout << endl;

        cout << "No negative cycle" << endl;
    }

    else
    {
        cout << "Negative cycle exists" << endl;
    }


}

int main()
{
    char fname[99];
    gets(fname);
    freopen(fname,"r",stdin);
    freopen("output.txt","w",stdout);


    int n,m,u,v,w,dir;
    int **graph;

    cin >> n >> m >> dir;

    graph= new int *[n];
    for (int i=0; i<n; i++)
    {
        graph[i]=new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            graph[i][j] = INF;
        }
    }

    for(int i=0; i<n; i++)
    {
        graph[i][i] = 0;
    }

    //printGraph(graph, n);

    for(int i=0; i<m ; i++)
    {
        cin >> u >> v >> w;
        graph[u][v]=w;
    }

    //printGraph(graph, n);

    //cout << endl;

    FloydWarshall(graph,n);



}
