#include<bits/stdc++.h>

using namespace std;

template<class T>
class treeNode
{
public:
    T key;
    treeNode<T> *parent;
    treeNode<T> *leftChild;
    treeNode<T> *rightChild;

    treeNode();
    treeNode(T x);
    int max_depth() const
    {
        const int left_depth = leftChild ? leftChild->max_depth() : 0;
        const int right_depth = rightChild ? rightChild->max_depth() : 0;
        return (left_depth > right_depth ? left_depth : right_depth) + 1;
    }

};

template<class T>
treeNode<T>::treeNode()
{
    this->key=0;
    this->parent=NULL;
    this->leftChild=NULL;
    this->rightChild=NULL;
}

template<class T>
treeNode<T>::treeNode(T x)
{
    this->key=x;
    this->parent=NULL;
    this->leftChild=NULL;
    this->rightChild=NULL;
}

template<class T>
class splayTree
{
    treeNode<T> *root;

public:

    splayTree();
    splayTree(T x);
    void leftRotate(treeNode<T> *x);
    void rightRotate(treeNode<T> *x);
    void splay(treeNode<T> *node);
    treeNode<T>* find(T x);
    treeNode<T>* subtreeMax(treeNode<T> *subRoot);
    treeNode<T>* subtreeMin(treeNode<T> *subRoot);
    treeNode<T>* join(treeNode<T> *t1, treeNode<T>* t2);
    void search(T x);
    void insert(T x);
    void Delete(T x);
    int depth();
    void printTree();
    void printlv(int n);
    void dispLV(treeNode<T> *p, int lv, int d);


};

template<class T>
splayTree<T>::splayTree()
{
    this->root=NULL;
}

template<class T>
splayTree<T>::splayTree(T x)
{
    root= new treeNode<T>(x);
}

template<class T>
void splayTree<T>::leftRotate(treeNode<T> *x)
{
    treeNode<T> *y=x->rightChild;
    treeNode<T> *yp=y->leftChild;
    treeNode<T> *p=x->parent;
    if(p)
    {
        if(p->rightChild==x)
            p->rightChild=y;
        else
            p->leftChild=y;
    }
    if(yp)
        yp->parent=x;
    y->parent=p;
    y->leftChild=x;

    x->parent=y;
    x->rightChild=yp;
}

template<class T>
void splayTree<T>::rightRotate(treeNode<T> *x)
{
    treeNode<T> *y=x->leftChild;
    treeNode<T> *yp=y->rightChild;
    treeNode<T> *p=x->parent;
    if(p)
    {
        if(p->rightChild==x)
            p->rightChild=y;
        else
            p->leftChild=y;
    }

    if(yp)
        yp->parent=x;

    y->parent=p;
    y->rightChild=x;

    x->parent=y;
    x->leftChild=yp;
}

template<class T>
void splayTree<T>::splay(treeNode<T> *node)
{

    while(true)
    {
        if(node==root)
            return;

        treeNode<T> *p=node->parent;
        if(!p)
        {
            //cout << 1 << endl;
            break;
        }
        treeNode<T> *gp= p->parent;
        if(!gp)
        {
            if(p->leftChild==node)
            {
                //cout << 2 << endl;
                rightRotate(p);
            }
            else
            {
                //cout << 3 << endl;
                leftRotate(p);
            }

        }
        else
        {
            if(gp->leftChild==p)
            {
                if(p->leftChild==node)
                {
                    //cout << 4 << endl;
                    rightRotate(gp);
                    //cout << 5 << endl;
                    rightRotate(p);
                }
                else
                {
                    //cout << 6 << endl;
                    leftRotate(p);
                    //cout << 7 << endl;
                    rightRotate(gp);
                }
            }
            else
            {
                if(p->leftChild==node)
                {
                    //cout << 8 << endl;
                    rightRotate(p);
                    //cout << 9 << endl;
                    leftRotate(gp);
                }
                else
                {
                    //cout << 10 << endl;
                    leftRotate(gp);
                    //cout << 11 << endl;
                    leftRotate(p);
                }
            }
        }

    }

    //cout << 12 << endl;
    this->root=node;

}


template<class T>
treeNode<T>* splayTree<T>::find(T x)
{
    treeNode<T> *temp=NULL;
    treeNode<T> *cur=this->root;
    treeNode<T> *prev=NULL;
    //cout << 101 << endl;
    while(cur!=NULL)
    {
        prev=cur;
        //cout << 102 << endl;
        if(x < cur->key)
            cur = cur->leftChild;
        else if (x>cur->key)
            cur = cur->rightChild;
        else
        {
            temp = cur;
            break;
        }
    }
    //cout << 103 << endl;

    if(temp!= NULL)
    {
        //cout << 104 << endl;
        splay(temp);
        //printTree();
        //cout << 105 << endl;

    }
    else if(prev!= NULL)
    {
        //cout << 106 << endl;
        splay(prev);
        //printTree();

    }
    //cout << 107 << endl;
    return temp;

}

template<class T>
treeNode<T>* splayTree<T>::subtreeMax(treeNode<T> *subRoot)
{
    treeNode<T>* cur=subRoot;
    while(cur->rightChild!=NULL)
    {
        cur = cur->rightChild;
    }
    return cur;

}

template<class T>
treeNode<T>* splayTree<T>::subtreeMin(treeNode<T> *subRoot)
{
    treeNode<T>* cur=subRoot;
    while(cur->leftChild!=NULL)
    {
        cur = cur->leftChild;
    }
    return cur;
}

/*treeNode* splayTree::join(treeNode* t1, treeNode* t2)
{
    treeNode* temp=NULL;

    if(t1==NULL && t2==NULL)
    {

    }
    else if (t1==NULL)
    {
        temp=subtreeMin(t2);
        splay(temp);
    }
    else if (t2==NULL)
    {
        temp=subtreeMax(t1);
        splay(temp);
    }
    else
    {
        temp=subtreeMax(t1);
        splay(temp);
        temp->rightChild=t2;
        t2->parent=temp;
    }

    return temp;
}*/

template<class T>
treeNode<T>* splayTree<T>::join(treeNode<T>* t1, treeNode<T>* t2)
{
    treeNode<T>* temp=NULL;
    temp=subtreeMax(t1);
    splay(temp);
    temp->rightChild=t2;
    t2->parent=temp;
    return temp;
}

template<class T>
void splayTree<T>::search(T x)
{
    treeNode<T> *temp=find(x);
    if(temp!=NULL)
    {
        cout << x << " is in the tree" << endl;
    }
    else
    {
        cout << x << " is not in the tree" << endl;
    }
}

template<class T>
void splayTree<T>::insert(T x)
{
    if(root==NULL)
    {
        root = new treeNode<T>(x);
        return ;
    }

    treeNode<T> *cur=this->root;
    treeNode<T> *temp=new treeNode<T>(x);

    while(cur)
    {
        if(x < cur->key)
        {
            if(cur->leftChild==NULL)
            {
                cur->leftChild=temp;
                temp->parent=cur;
                splay(temp);
                return;
            }
            else
                cur = cur->leftChild;
        }
        else if(x > cur->key)
        {
            if(cur->rightChild==NULL)
            {
                cur->rightChild=temp;
                temp->parent=cur;
                splay(temp);
                return;
            }
            else
                cur = cur->rightChild;
        }
        else
        {
            splay(cur);
            return;
        }
    }
}

template<class T>
void splayTree<T>::Delete(T x)
{
    if(root==NULL)
        return;

    treeNode<T> *temp=find(x);

    if(temp==NULL)
        return;

    treeNode<T> *left=temp->leftChild;
    treeNode<T> *right=temp->rightChild;

    if(left==NULL && right == NULL)
    {
        this->root=NULL;
    }
    else if (left==NULL)
    {
        this->root = right;
    }
    else if (right==NULL)
    {
        this->root = left;
    }
    else
    {
        this->root=join(left,right);
    }

    //this->root=join(left,right);

    delete temp;
    if(root!=NULL)
    {
        this->root->parent=NULL;
    }

}

template<class T>
int splayTree<T>::depth()
{
    int x;

    x=root->max_depth();

    return x;
}

template<class T>
void splayTree<T>::printTree()
{
    if(root==NULL)
        cout << "Tree is empty" << endl;
    else
    {
        int i = 0;
        while (i <= depth())
        {
            printlv(i);
            i++;
            cout << endl;
        }
    }
}

template<class T>
void splayTree<T>::printlv(int n)
{
    int val = pow(2, depth() -n+2);
    cout << setw(val) << "";
    dispLV(root, n, val);
}

template<class T>
void splayTree<T>::dispLV(treeNode<T>* p, int lv, int d)
{
    int disp = 2 * d;
    if (lv == 0)
    {
        if (p == NULL)
        {

            cout << "   ";
            cout << setw(disp -3) << "";
            return;
        }
        else
        {
            int result = ((p->key <= 1) ? 1 : log10(p->key) + 1);
            cout << " " << p->key << " ";
            cout << setw(disp - result-2) << "";
        }
    }
    else
    {
        if (p == NULL&& lv >= 1)
        {
            dispLV(NULL, lv - 1, d);
            dispLV(NULL, lv - 1, d);
        }
        else
        {
            dispLV(p->leftChild, lv - 1, d);
            dispLV(p->rightChild, lv - 1, d);
        }
    }
}

int main()
{
    cout << "Enter your option" << endl;
    cout << "1. Integer" << endl;
    cout << "2. Character" << endl;

    int option;
    cin >> option;
    if(option==1)
    {
        splayTree<int> s;

        while(true)
        {
            cout << "Enter your option:\n" << endl;
            cout << "1. Insert" << endl;
            cout << "2. Delete" << endl;
            cout << "3. Search" << endl;
            cout << "4. Print" << endl;
            cout << "5. Exit" << endl;

            int x,y;
            cin >> x ;
            if(x==1)
            {
                cout << "Enter your number: " << endl;
                cin >> y;
                s.insert(y);
            }
            else if(x==2)
            {
                cout << "Enter your number: " << endl;
                cin >> y;
                s.Delete(y);
            }
            else if(x==3)
            {
                cout << "Enter your number: " << endl;
                cin >> y;
                s.search(y);
            }
            else if(x==4)
                s.printTree();
            else if(x==5)
                break;
            else
                cout << "Please enter a valid option." << endl;
        }
    }
    else
    {
        splayTree<char> s1;

        while(true)
        {
            cout << "Enter your option:\n" << endl;
            cout << "1. Insert" << endl;
            cout << "2. Delete" << endl;
            cout << "3. Search" << endl;
            cout << "4. Print" << endl;
            cout << "5. Exit" << endl;

            int x;
            char y;
            cin >> x ;
            if(x==1)
            {
                cout << "Enter your number: " << endl;
                cin >> y;
                s1.insert(y);
            }
            else if(x==2)
            {
                cout << "Enter your number: " << endl;
                cin >> y;
                s1.Delete(y);
            }
            else if(x==3)
            {
                cout << "Enter your number: " << endl;
                cin >> y;
                s1.search(y);
            }
            else if(x==4)
                s1.printTree();
            else if(x==5)
                break;
            else
                cout << "Please enter a valid option." << endl;
        }
    }
}



