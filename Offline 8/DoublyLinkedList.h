#include<bits/stdc++.h>

using namespace std;


template<class T>
class listNode
{
public:
    T val;
    listNode<T> *next;
    listNode<T> *previous;
};

template<class T>
class doublyLinkedList
{
    listNode<T> *head;
    listNode<T> *tail;
public:
    doublyLinkedList()
    {
        head=NULL;
        tail=NULL;
    }

    void insert_first(T x)
    {
        listNode<T> *temp=new listNode<T>;
        temp->val=x;
        temp->next=NULL;
        temp->previous=NULL;
        if(head==NULL)
        {
            head=temp;
            tail=temp;
        }
        else
        {
            temp->next=head;
            head->previous=temp;
            head=temp;
        }
    }

    void insert_last(T x)
    {
        listNode<T> *temp=new listNode<T>;
        temp->val=x;
        temp->next=NULL;
        //temp->previous=NULL;
        temp->previous=tail;
        tail->next=temp;
        tail=temp;

    }

    void insert(T x, int pos)
    {
        listNode<T> *q=new listNode<T>;
        listNode<T> *temp=new listNode<T>;
        temp->val=x;
        q=head;
        for(int i=0; i<pos-1; i++)
        {
            q=q->next;
        }
        temp->next=q->next;
        temp->next->previous=temp;
        q->next=temp;
        temp->previous=q;
    }


    void delete_first()
    {
        listNode<T> *temp=new listNode<T>;
        temp=head;
        head=head->next;
        head->previous=NULL;
        delete temp;
    }

    void delete_last()
    {
        listNode<T> *temp=new listNode<T>;
        temp=tail;
        tail=tail->previous;
        tail->next=NULL;
        delete temp;
    }

    void delete_pos(int pos)
    {
        listNode<T> *q=new listNode<T>;
        listNode<T> *temp=new listNode<T>;
        q=head;
        for(int i=0; i<pos-1; i++)
        {
            q=q->next;
        }

        temp=q->next;
        q->next=temp->next;
        temp->next->previous=q;
        delete temp;
    }

    int search(T x)
    {
        listNode<T> *q=new listNode<T>;
        q=head;
        int i=0;
        for(q=head; q!=tail; q=q->next)
        {
            i++;
            if(q->val=x)
                return i;
        }

        return i;

    }

    int size()
    {
        listNode<T> *q=new listNode<T>;
        q=head;
        int i=1;
        for(q=head; q!=tail; q=q->next)
        {
            i++;
        }

        return i;
    }

    listNode<T> *getHead()
    {
        return head;
    }

    listNode<T> *getTail()
    {
        return tail;
    }

    void display()
    {
        listNode<T> *temp=new listNode<T>;
        temp=head;
        while(temp!=NULL)
        {
            cout<<temp->val<<"\t";
            temp=temp->next;
        }
    }
};






