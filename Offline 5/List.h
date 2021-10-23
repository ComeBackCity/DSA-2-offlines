#include<iostream>

using namespace std;

template<class T>
class listNode
{
public:
    T value;
    listNode<T> *next;
};

template<class T>
class linkedlist
{
private:
    listNode<T> *head,*tail;
public:
    linkedlist()
    {
        head=NULL;
        tail=NULL;
    }


    void createlistNode(T val)
    {
        listNode<T> *temp =new listNode<T>;
        temp->value=val;
        temp->next=NULL;
        if(head==NULL)
        {
            head=temp;
            tail=temp;

        }
        else
        {
            tail->next=temp;
            tail=temp;
        }
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
            cout<<temp->value<<"\t";
            temp=temp->next;
        }
    }
};

