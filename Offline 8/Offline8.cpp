#include<bits/stdc++.h>
#include"queue.h"
//#include"DoublyLinkedList.h"
#define HMS 999
#define INF 9999
using namespace std;

class Node
{
public:
    int val,degree;
    Node* child[HMS], *parent;

    Node();
    Node(int key);
    Node* treeMerge( Node* t2);
    void printTree();

};

Node::Node()
{
    this->val=NULL;
    this->degree=0;
    for(int i=0; i<HMS; i++)
    {
        this->child[i]=NULL;
    }
    this->parent=NULL;
}

Node::Node(int key)
{
    this->val=key;
    this->degree=0;
    for(int i=0; i<HMS; i++)
    {
        this->child[i]=NULL;
    }
    this->parent=NULL;
}

Node* Node::treeMerge(Node* t)
{
    if(this->val<t->val)
    {
        this->child[this->degree]=t;
        t->parent=this;
        this->degree++;
        return this;
    }
    else
    {
        t->child[t->degree]=this;
        this->parent=t;
        t->degree++;
        //cout << 9 << endl;
        return t;
    }

}

void Node::printTree()
{

    Queue<Node*> q(40);
    Queue<int> level(40);
    q.enQueue(this);
    level.enQueue(0);

    int prevLevel=-1;

    while(!q.isEmpty())
    {
        if(prevLevel!=level.deQueue())
        {
            prevLevel++;
            cout<<endl<<"Level "<<prevLevel<<" : ";
        }
        Node* temp=q.deQueue();
        cout << temp->val << "\t";
        for(int i=0; i<temp->degree; i++)
        {
            q.enQueue(temp->child[i]);
            level.enQueue(prevLevel+1);
        }
    }

}

class binomial_heap
{
    Node* bh[HMS];
    int tree_max_degree;
public:
    binomial_heap();
    binomial_heap(Node* x);
    void setMaxdeg(int x);
    int getMaxdeg();
    static binomial_heap heapUninon(binomial_heap &b1, binomial_heap &b2);
    void insert(int key);
    void insert_tree_into_heap(Node* n);
    int find_min();
    int extract_min();
    void printHeap();
    ~binomial_heap();
};

binomial_heap::binomial_heap()
{
    this->tree_max_degree=-1;
}

binomial_heap::binomial_heap(Node* x)
{
    int j=x->degree;
    this->bh[j]=x;
    this->tree_max_degree=j;

}

void binomial_heap::setMaxdeg(int x)
{
    this->tree_max_degree=x;
}

int binomial_heap::getMaxdeg()
{
    return this->tree_max_degree;
}

binomial_heap binomial_heap::heapUninon(binomial_heap &b1, binomial_heap &b2)
{
    int x=b1.tree_max_degree;
    int y=b2.tree_max_degree;
    int Max;
    if(x<=y)
        Max=y;
    else
        Max=x;

    binomial_heap nbh;
    Node *carry=new Node;
    Node *sum=new Node;
    carry=NULL;
    sum=NULL;


    for(int i=0; i<=Max+1; i++)
    {
        if(b1.bh[i]==NULL && b2.bh[i]==NULL)
        {
            sum=carry;
            carry=NULL;
            nbh.bh[i]=sum;
        }

        else if(b1.bh[i]==NULL && b2.bh[i]!=NULL)
        {
            if(carry==NULL)
            {
                sum=b2.bh[i];
                carry=NULL;
                nbh.bh[i]=sum;
            }
            else
            {
                sum=NULL;
                carry=b2.bh[i]->treeMerge(carry);
                nbh.bh[i]=sum;
            }
        }
        else if(b1.bh[i]!=NULL && b2.bh[i]==NULL)
        {
            if(carry==NULL)
            {
                sum=b1.bh[i];
                carry=NULL;
                nbh.bh[i]=sum;
            }
            else
            {
                sum=NULL;
                carry=b1.bh[i]->treeMerge(carry);
                nbh.bh[i]=sum;
            }
        }
        else
        {
            sum=carry;
            carry=b1.bh[i]->treeMerge(b2.bh[i]);
            nbh.bh[i]=sum;

        }
    }

    if(nbh.bh[Max+1]!=NULL)
        nbh.setMaxdeg(Max+1);
    else
        nbh.setMaxdeg(Max);

    return nbh;

}

void binomial_heap::insert_tree_into_heap(Node* n)
{
    binomial_heap b1(n);
    //b1.printHeap();
    binomial_heap b2=binomial_heap::heapUninon(*this,b1);
    *this=b2;
}

void binomial_heap::insert(int key)
{
    Node *n= new Node(key);
    this->insert_tree_into_heap(n);
}


int binomial_heap::find_min()
{

    int Min=INF;
    for(int i=0; i<=tree_max_degree; i++)
    {
        if(bh[i]!=NULL && bh[i]->val<Min)
        {
            Min=bh[i]->val;
        }
    }

    return Min;
}

void binomial_heap::printHeap()
{

    for(int i=0; i<=this->tree_max_degree; i++)
    {
        if(this->bh[i]==NULL)
        {
            cout << "NULL\n" << endl;
        }
        else
        {
            bh[i]->printTree();
            cout << "\n" << endl;
        }

    }
}

int binomial_heap::extract_min()
{
    int idx=0;
    int Max=this->tree_max_degree;
    int Min=INF;
    for(int i=0; i<=Max; i++)
    {
        if(bh[i]!=NULL && bh[i]->val<Min)
        {
            idx=i;
            Min=bh[i]->val;
        }
    }

    Node* temp=new Node;
    temp=this->bh[idx];
    this->bh[idx]=NULL;
    int x=temp->degree;
    Node* children[x];

    for(int i=0; i<x; i++)
    {
        children[i]=temp->child[i];
        temp->child[i]=NULL;
        children[i]->parent=NULL;
    }

    for(int i=0; i<x; i++)
    {

        //this->printHeap();
        this->insert_tree_into_heap(children[i]);
    }

    if(this->bh[Max]!=NULL)
        this->setMaxdeg(Max);
    else
        this->setMaxdeg(Max-1);



    return Min;


}

binomial_heap::~binomial_heap()
{
    for(int i=0; i<=tree_max_degree; i++)
    {
        this->bh[i]=NULL;
    }
}

int main()
{
    binomial_heap a,b,c;
    int option,x;

    while(true)
    {
        cout << "Enter your option:" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Find Min" << endl;
        cout << "3. Extract Min" << endl;
        cout << "4. Union" << endl;
        cout << "5. Print" << endl;
        cout << "6. Exit" << endl;

        cin >> option;

        if(option==1)
        {
            cout << "Enter you number" << endl;
            cin >> x;
            a.insert(x);
            cout << "\n" << endl;
        }
        else if(option==2)
        {
            cout << a.find_min() << endl;
            cout << "\n" << endl;
        }
        else if(option==3)
        {
            cout << a.extract_min() << endl;
            //a.printHeap();
            cout << "\n" << endl;
        }
        else if(option==4)
        {
            b.insert(2);
            b.insert(10);
            b.insert(12);
            b.insert(15);
            b.insert(21);
            b.insert(7);
            cout << "------------a------------" << endl;
            a.printHeap();
            cout << "------------b------------" << endl;
            b.printHeap();
            c=binomial_heap::heapUninon(a,b);
            cout << "------------c------------" << endl;
            c.printHeap();
            cout << "\n" << endl;
        }
        else if(option==5)
        {
            a.printHeap();
            cout << "\n" << endl;
        }
        else if(option==6)
        {
            break;
        }

    }

    return 0;

}
