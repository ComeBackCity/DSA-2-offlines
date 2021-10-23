#include<bits/stdc++.h>

using namespace std;

template<class T>
class Queue
{
private:
    T *arr;
    int length, front, rear,capacity;

public:
    Queue();
    Queue(int x);
    bool isFull();
    bool isEmpty();
    void enQueue(T item);
    T deQueue();
    void print();
    ~Queue();

};

template<class T>
Queue<T>::Queue()
{
    capacity=0;
    length=0;
}

template<class T>
Queue<T>::Queue(int x)
{
    capacity=x;
    arr=new T[capacity];
    length=0;
    front=0;
    rear=capacity-1;
}

template<class T>
bool Queue<T>::isFull()
{
    if(length==capacity)
        return true;
    else
        return false;
}

template<class T>
bool Queue<T>::isEmpty()
{
    if(length==0)
        return true;
    else
        return false;
}

template<class T>
void Queue<T>::enQueue(T item)
{
    if(isFull())
        return;
    rear=(rear+1)%capacity;
    arr[rear]=item;
    length++;
}

template<class T>
T Queue<T>::deQueue()
{
    if(isEmpty())
        return NULL;
    T item= arr[front];
    front=(front+1)%capacity;
    length--;
    return item;
}

/*template<class T>
void Queue<T>::print()
{
    for(int i=0; i<length; i++)
    {
        cout << arr[i] << " ";
    }
}*/

template<class T>
Queue<T>::~Queue()
{
    delete[] arr;
    capacity=0;
    length=0;
    front=0;
    rear=0;
}
