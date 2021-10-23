#include<bits/stdc++.h>

using namespace std;

template <class T>
class MinHeap{

    T vec[1000];
    int s;

public:
    //Creation
    MinHeap();
    MinHeap(T arr[], int length);
    void heapify();

    //Basic
    T findMin();
    void Insert(T val);
    T extract_min();

    //Inspection
    int size();
    bool is_empty();

    //Internal
    void min_heapify(int i);
    void sift_down(int i);

    //Utility functions
    int parent(int i);
    int left(int i);
    int right(int i);

};

template<class T>
MinHeap<T>::MinHeap()
{
    s=0;
}

template<class T>
MinHeap<T>::MinHeap(T arr[], int length)
{
    for(int i=0; i<length; i++)
    {
        this->vec[i]=arr[i];

    }

    s=length;
    heapify();
}

template<class T>
void MinHeap<T>::heapify()
{

    for(int i=s/2; i>=0; i--)
        min_heapify(i);
}


template<class T>
T MinHeap<T>::findMin()
{
    heapify();
    return vec[0];
}

template<class T>
void MinHeap<T>::Insert(T val)
{

    vec[s]=val;
    s++;

    heapify();
}

template<class T>
T MinHeap<T>::extract_min()
{
    heapify();

    T x=vec[0];

    vec[0]=vec[s-1];
    s--;

    heapify();

    return x;
}


template<class T>
int MinHeap<T>::size()
{
    return s;
}

template<class T>
bool MinHeap<T>::is_empty()
{
    if(s==0)
        return true;
    else
        return false;
}


template<class T>
void MinHeap<T>::min_heapify(int i)
{
    int l,r,smallest;
    l=left(i);
    r=right(i);
    smallest=i;
    if(l<s && vec[l]<vec[smallest])
    {
        smallest=l;
    }

    if(r<s && vec[r]<vec[smallest])
    {

        smallest=r;
    }

    if(smallest!=i)
    {
        swap(vec[i],vec[smallest]);
        min_heapify(smallest);
    }

}


template<class T>
void MinHeap<T>::sift_down(int i)
{
    if(i && vec[parent(i)] < vec[i])
    {
        swap(vec[parent(i)],vec[i]);
        sift_down(parent(i));
    }
}


template<class T>
int MinHeap<T>::parent(int i)
{
    return (i-1)/2;
}


template<class T>
int MinHeap<T>::left(int i)
{
    return (2*i + 1);
}


template<class T>
int MinHeap<T>::right(int i)
{
    return (2*i + 2);
}







