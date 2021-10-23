#include<bits/stdc++.h>

using namespace std;

template<class T>
class Disjoint_Set
{
    T parent[10000];
    int rank[10000];
    int s;

public:
    Disjoint_Set();
    Disjoint_Set(int x);

    void make_set(T val);
    void Union(T val1, T val2);
    void link(T val1, T val2);
    T Find_set(T val);
};

template<class T>
Disjoint_Set<T>::Disjoint_Set()
{

}

template<class T>
Disjoint_Set<T>::Disjoint_Set(int x)
{
    s=x;
}

template<class T>
void Disjoint_Set<T>::make_set(T val)
{
    parent[val]=val;
    rank[val]=val;
}

template<class T>
void Disjoint_Set<T>::Union(T val1, T val2)
{
    link(Find_set(val1),Find_set(val2));
}

template<class T>
void Disjoint_Set<T>::link(T val1, T val2)
{
    if(rank[val1]>rank[val2])
    {
        parent[val2]=val1;
    }
    else
    {
        parent[val1]=val2;
        if(rank[val1]==rank[val2])
        {
            rank[val2]=rank[val2]+1;
        }
    }

}

template<class T>
T Disjoint_Set<T>::Find_set(T val)
{
    if(val!=parent[val])
        parent[val]=Find_set(parent[val]);
    return parent[val];
}

