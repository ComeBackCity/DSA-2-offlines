#include<bits/stdc++.h>
#include<cstring>
#define psi pair<string, int>
using namespace std;

psi nullPair=make_pair("0000000",-1);

static const char alphanum[] =
    "abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char genRandom()
{

    return alphanum[rand() % stringLength];
}

//separate chaining with Hash1(k)
class hashTable1
{
    vector< list<psi> >bucketArray;
    int n;

public:
    hashTable1();
    hashTable1(int x);
    int hash1(string key);
    int insert1(string k, int v);
    int search1(string k);
    void delete1(string s);


};


hashTable1::hashTable1()
{
    n=0;
}


hashTable1::hashTable1(int N)
{
    n=N;
    bucketArray.resize(n);
}

int hashTable1::hash1(string key)
{
    int x=0;

    for(int i=0; i<key.size(); i++)
    {
        x+=(int)key[i];
    }

    return x%n;
}


int hashTable1::insert1(string s, int v)
{

    int idx=hash1(s)%n;
    int cnt=0;
    psi p=make_pair(s,v);
    list<psi>::iterator it;
    for(it=bucketArray[idx].begin(); it!=bucketArray[idx].end(); it++)
    {
        cnt++;
    }
    bucketArray[idx].push_back(p);
    return cnt;

}


int hashTable1::search1(string s)
{
    int idx=hash1(s)%n;
    int cnt=0;
    psi p;
    list<psi>::iterator it;
    for(it=bucketArray[idx].begin(); it!=bucketArray[idx].end(); it++)
    {
        p=*it;
        cnt++;
        if(p.first==s)
        {
            //cout << s << " is found" << endl;
            return cnt;
        }
    }

    //cout << s << " is not found" << endl;
    return cnt;

}



void hashTable1::delete1(string s)
{
    int idx=hash1(s)%n;
    psi p;
    list<psi>::iterator it;
    for(it=bucketArray[idx].begin(); it!=bucketArray[idx].end(); it++)
    {
        p=*it;
        if(p.first==s)
        {
            bucketArray[idx].erase(it);
            return;
        }
    }
}

//separate chaining with Hash2(k)
class hashTable2
{
    vector< list<psi> >bucketArray;
    list<psi> l;
    int n;

public:
    hashTable2();
    hashTable2(int x);
    int hash2(string key);
    int insert2(string k, int v);
    int search2(string k);
    void delete2(string s);


};

hashTable2::hashTable2()
{
    n=0;
}


hashTable2::hashTable2(int N)
{
    n=N;
    bucketArray.resize(n);
}


int hashTable2::hash2(string key)
{
    int x=0;

    for(int i=0; i<key.size(); i++)
    {
        x=(53*x+(int)key[i])%n;
    }

    return x%n;
}

int hashTable2::insert2(string s, int v)
{

    int idx=hash2(s)%n;
    int cnt=0;
    psi p=make_pair(s,v);
    list<psi>::iterator it;
    for(it=bucketArray[idx].begin(); it!=bucketArray[idx].end(); it++)
    {
        cnt++;
    }
    bucketArray[idx].push_back(p);
    return cnt;

}

int hashTable2::search2(string s)
{
    int idx=hash2(s)%n;
    int cnt=0;
    psi p;
    list<psi>::iterator it;
    for(it=bucketArray[idx].begin(); it!=bucketArray[idx].end(); it++)
    {
        p=*it;
        cnt++;
        if(p.first==s)
        {
            //cout << s << " is found" << endl;
            return cnt;
        }
    }


    //cout << s << " is not found" << endl;
    return cnt;
}

void hashTable2::delete2(string s)
{
    int idx=hash2(s)%n;
    psi p;
    list<psi>::iterator it;
    for(it=bucketArray[idx].begin(); it!=bucketArray[idx].end(); it++)
    {
        p=*it;
        if(p.first==s)
        {
            bucketArray[idx].erase(it);
            return;
        }
    }
}

//Double hashing with Hash1(k)
class hashTable3
{
    vector< psi > arr;
    int n;
    int length;

public:
    hashTable3();
    hashTable3(int n);
    bool isFull();
    int hash1(string s);
    int auxHash(string s);
    int insert3(string s, int v);
    int search3(string s);
    void delete3(string s);


};

hashTable3::hashTable3()
{
    n=0;
}

hashTable3::hashTable3(int N)
{
    n=N;
    arr.resize(n,nullPair);

}

bool hashTable3::isFull()
{
    return length==n;
}

int hashTable3::hash1(string s)
{
    int x=0;

    for(int i=0; i<s.size(); i++)
    {
        x+=(int)s[i];
    }

    return x%n;
}

int hashTable3::auxHash(string s)
{
    int x=0;

    for(int i=0; i<s.size(); i++)
    {
        x+=(3*x+(i+5)*(int)s[i])%n;
    }

    return x%n;
}

int hashTable3::insert3(string s, int v)
{
    if(isFull())
        return 0;

    int idx=hash1(s)%n;

    psi p=make_pair(s,v);

    //cout << 1 <<endl;
    if(arr[idx]!=nullPair)
    {
        //cout << 2 <<endl;
        int i=1;
        int idx2=auxHash(s);

        while(i<n)
        {
            //cout << 3 << endl;
            int newIdx=(idx+i*idx2)%n;

            if(arr[newIdx]==nullPair)
            {
                arr[newIdx]=p;
                length++;
                return i;
            }
            i++;
            //getchar();

        }

    }

    else
    {
        //cout << 4 << endl;
        arr[idx]=p;
        length++;
        return 0;
    }
}

/*int hashTable3::insert3(string s, int v)
{
    if(isFull())
        return 0;

    int idx=hash1(s);
    int idx2=auxHash(s);

    psi p=make_pair(s,v);

    int i = 0;
        while(i<n)
        {
            int newIdx=(idx+i*idx2)%n;

            if(arr[newIdx]==nullPair)
            {
                arr[newIdx]=p;
                length++;
                return i;
            }
            i++;
            //getchar();

        }
        return n;

}*/

int hashTable3::search3(string s)
{
    int idx=hash1(s)%n;

    if(arr[idx].first==s)
    {
        //cout << s << " is in the hashtable" << endl;
        return 1;
    }
    else
    {
        int i=1;
        int idx2=auxHash(s);


        while(i<n)
        {
            int newIdx=(idx+i*idx2)%n;


            if(arr[newIdx].first==s )
            {
                //cout << s << " is in the hashtable" << endl;
                return i+1;
            }
            else if(arr[newIdx]==nullPair)
            {
                //cout << s << " is not in the hashtable" << endl;
                return i+1;
            }
            i++;


        }

    }
}


void hashTable3::delete3(string s)
{
    int idx=hash1(s)%n;


    if(arr[idx].first==s)
    {
        arr[idx]=nullPair;
        length--;
        return;
    }
    else
    {
        int i=1;
        int idx2=auxHash(s);

        while(i<n)
        {
            int newIdx=(idx+i*idx2)%n;

            if(arr[newIdx].first==s)
            {
                arr[newIdx]=nullPair;
                length--;
                return;
            }
            else if(arr[newIdx]==nullPair)
            {
                return;
            }
            i++;


        }


    }

    return;


}


//Double hashing with Hash2(k)
class hashTable4
{
    vector< psi > arr;
    int n;
    int length;

public:
    hashTable4();
    hashTable4(int n);
    bool isFull();
    int hash2(string s);
    int auxHash(string s);
    int insert4(string s, int v);
    int search4(string s);
    void delete4(string s);


};

hashTable4::hashTable4()
{
    n=0;
}

hashTable4::hashTable4(int N)
{
    n=N;
    arr.resize(n,nullPair);

}

bool hashTable4::isFull()
{
    return length==n;
}

int hashTable4::hash2(string s)
{
    int x=0;

    for(int i=0; i<s.size(); i++)
    {
        x=(53*x+(int)s[i])%n;
    }

    return x%n;
}

int hashTable4::auxHash(string s)
{
    int x=0;

    for(int i=0; i<s.size(); i++)
    {
        x+=(3*x+(i+5)*(int)s[i])%n;
    }

    return x%n;
}

int hashTable4::insert4(string s, int v)
{
    if(isFull())
        return 0;

    int idx=hash2(s)%n;

    psi p=make_pair(s,v);
    length++;

    if(arr[idx]!=nullPair)
    {
        int i=1;
        int idx2=auxHash(s);

        while(i<n)
        {
            int newIdx=(idx+i*idx2)%n;

            if(arr[newIdx]==nullPair)
            {
                arr[newIdx]=p;
                return i;
            }
            i++;

        }
    }

    else
    {
        arr[idx]=p;
        return 0;
    }




}


int hashTable4::search4(string s)
{
    int idx=hash2(s)%n;

    if(arr[idx].first==s)
    {
        //cout << s << " is in the hashtable" << endl;
        return 1;
    }

    else
    {
        int i=1;
        int idx2=auxHash(s);


        while(i<n)
        {
            int newIdx=(idx+i*idx2)%n;


            if(arr[newIdx].first==s )
            {
                //cout << s << " is in the hashtable" << endl;
                return i+1;
            }
            else if(arr[newIdx]==nullPair)
            {
                //cout << s << " is not in the hashtable" << endl;
                return i+1;
            }
            i++;


        }

    }
}


void hashTable4::delete4(string s)
{
    int idx=hash2(s)%n;

    if(arr[idx].first==s)
    {

        arr[idx]=nullPair;
        length--;
        return;
    }
    else
    {
        int i=1;
        int idx2=auxHash(s);


        while(i<n)
        {
            int newIdx=(idx+i*idx2)%n;

            if(arr[newIdx].first==s)
            {
                arr[newIdx]=nullPair;
                length--;
                return;
            }
            else if(arr[newIdx]==nullPair)
            {
                return;
            }
            i++;


        }

    }

    return;


}


//Custom Probing with Hash1(k)
class hashTable5
{
    vector< psi > arr;
    int n;
    int length;
    int c1=10,c2=8;

public:
    hashTable5();
    hashTable5(int n);
    bool isFull();
    int hash1(string s);
    int auxHash(string s);
    int insert5(string s, int v);
    int search5(string s);
    void delete5(string s);


};

hashTable5::hashTable5()
{
    n=0;
}

hashTable5::hashTable5(int N)
{
    n=N;
    arr.resize(n,nullPair);

}

bool hashTable5::isFull()
{
    return length==n;
}

int hashTable5::hash1(string s)
{
    int x=0;

    for(int i=0; i<s.size(); i++)
    {
        x+=(int)s[i];
    }

    return x%n;
}

int hashTable5::auxHash(string s)
{
    int x=0;

    for(int i=0; i<s.size(); i++)
    {
        x+=(3*x+(i+5)*(int)s[i])%n;
    }

    return x%n;
}

int hashTable5::insert5(string s, int v)
{
    if(isFull())
        return 0;

    int idx=hash1(s)%n;

    psi p=make_pair(s,v);
    length++;

    if(arr[idx]!=nullPair)
    {
        int i=1;
        int idx2=auxHash(s);

        while(i<n)
        {
            int newIdx=(idx+c1*i*idx2+c2*i*i)%n;

            if(arr[newIdx]==nullPair)
            {
                arr[newIdx]=p;
                return i;
            }
            i++;

        }
    }

    else
    {
        arr[idx]=p;
        return 0;
    }


}


int hashTable5::search5(string s)
{
    int idx=hash1(s)%n;

    if(arr[idx].first==s)
    {
        //cout << s << " is in the hashtable" << endl;
        return 1;
    }

    else
    {
        int i=1;
        int idx2=auxHash(s);


        while(i<n)
        {
            int newIdx=(idx+c1*i*idx2+c2*i*i)%n;


            if(arr[newIdx].first==s )
            {
                //cout << s << " is in the hashtable" << endl;
                return i+1;
            }
            else if(arr[newIdx]==nullPair)
            {
                //cout << s << " is not in the hashtable" << endl;
                return i+1;
            }
            i++;


        }

    }
}


void hashTable5::delete5(string s)
{
    int idx=hash1(s)%n;

    if(arr[idx].first==s)
    {
        arr[idx]=nullPair;
        length--;
        return;
    }
    else
    {
        int i=1;
        int idx2=auxHash(s);


        while(i<n)
        {
            int newIdx=(idx+c1*i*idx2+c2*i*i)%n;

            if(arr[newIdx].first==s)
            {
                arr[newIdx]=nullPair;
                length--;
                return;
            }
            else if(arr[newIdx]==nullPair)
            {
                return;
            }
            i++;
        }

    }

    return;


}


class hashTable6
{
    vector< psi > arr;
    int n;
    int length;
    int c1=10,c2=8;

public:
    hashTable6();
    hashTable6(int n);
    bool isFull();
    int hash2(string s);
    int auxHash(string s);
    int insert6(string s, int v);
    int search6(string s);
    void delete6(string s);


};

hashTable6::hashTable6()
{
    n=0;
}

hashTable6::hashTable6(int N)
{
    n=N;
    arr.resize(n,nullPair);

}

bool hashTable6::isFull()
{
    return length==n;
}

int hashTable6::hash2(string s)
{
    int x=0;

    for(int i=0; i<s.size(); i++)
    {
        x=(53*x+(int)s[i])%n;
    }

    return x%n;
}

int hashTable6::auxHash(string s)
{
    int x=0;

    for(int i=0; i<s.size(); i++)
    {
        x+=(3*x+(i+5)*(int)s[i])%n;
    }

    return x%n;
}

int hashTable6::insert6(string s, int v)
{
    if(isFull())
        return 0;

    int idx=hash2(s)%n;

    psi p=make_pair(s,v);
    length++;

    if(arr[idx]!=nullPair)
    {
        int i=1;
        int idx2=auxHash(s);

        while(i<n)
        {
            int newIdx=(idx+c1*i*idx2+c2*i*i)%n;

            if(arr[newIdx]==nullPair)
            {
                arr[newIdx]=p;
                return i;
            }
            i++;

        }
    }

    else
    {
        arr[idx]=p;
        return 0;
    }




}


int hashTable6::search6(string s)
{
    int idx=hash2(s)%n;

    if(arr[idx].first==s)
    {
        //cout << s << " is in the hashtable" << endl;
        return 1;
    }

    else
    {
        int i=1;
        int idx2=auxHash(s);


        while(i<n)
        {
            int newIdx=(idx+c1*i*idx2+c2*i*i)%n;


            if(arr[newIdx].first==s )
            {
                //cout << s << " is in the hashtable" << endl;
                return i+1;
            }
            else if(arr[newIdx]==nullPair)
            {
                //cout << s << " is not in the hashtable" << endl;
                return i+1;
            }
            i++;


        }

    }
}


void hashTable6::delete6(string s)
{
    int idx=hash2(s)%n;

    if(arr[idx].first==s)
    {
        arr[idx]=nullPair;
        length--;
        return;
    }
    else
    {
        int i=1;
        int idx2=auxHash(s);


        while(i<n)
        {
            int newIdx=(idx+c1*i*idx2+c2*i*i)%n;

            if(arr[newIdx].first==s)
            {
                arr[newIdx]=nullPair;
                length--;
                return;
            }
            else if(arr[newIdx]==nullPair)
            {
                return;
            }
            i++;
        }

    }

    return;


}

int main()
{
    srand(time(0));
    ofstream of("output.txt");
    vector<string> v1,v2;
    int n=10000;
    //cin >> n;
    hashTable1 h1(n);
    hashTable2 h2(n);
    hashTable3 h3(n);
    hashTable4 h4(n);
    hashTable5 h5(n);
    hashTable6 h6(n);
    int cnt=0,t=0,col_count[6],hit_count[6];
    double avg_col_count[6],avg_hit_count[6];

    for(int i=0; i<6; i++)
    {
        col_count[i]=0;
        hit_count[i]=0;
        avg_col_count[i]=0;
        avg_hit_count[i]=0;
    }


    do
    {
        string S;

        for(unsigned int i = 0; i < 7; i++)
        {
            S += genRandom();

        }

        of << S << endl;

        if(find(v1.begin(), v1.end(), S)==v1.end())
        {
            v1.push_back(S);

        }
        else
        {
            continue;
        }

        cnt++;

        col_count[0]+=h1.insert1(S,cnt);
        col_count[1]+=h2.insert2(S,cnt);
        col_count[2]+=h3.insert3(S,cnt);
        col_count[3]+=h4.insert4(S,cnt);
        col_count[4]+=h5.insert5(S,cnt);
        col_count[5]+=h6.insert6(S,cnt);


    }
    while(cnt<=9999);

    set<int> indexes;
    vector<string> choices;
    int max_index = v1.size();
    while (indexes.size() < min(1000, max_index))
    {
        int random_index = rand() % max_index;
        if (indexes.find(random_index) == indexes.end())
        {
            choices.push_back(v1[random_index]);
            indexes.insert(random_index);
        }
    }

    //random_shuffle(v1.begin(),v1.end());


    for(int i=0; i<1000; i++)
    {
        hit_count[0]+=h1.search1(choices[i]);
        hit_count[1]+=h2.search2(choices[i]);
        hit_count[2]+=h3.search3(choices[i]);
        hit_count[3]+=h4.search4(choices[i]);
        hit_count[4]+=h5.search5(choices[i]);
        hit_count[5]+=h6.search6(choices[i]);
    }

    /*for(int i=0; i<100; i++)
        cout << choices[i] << endl;*/

    for(int i=0; i<6; i++)
    {
        avg_col_count[i]=col_count[i]/10000.00;
        avg_hit_count[i]=hit_count[i]/1000.00;
    }


    /*for(int i=0; i<6; i++)
    {
        //cout << col_count[i] << endl;
        cout << avg_col_count[i] << endl;
        cout << avg_hit_count[i] << endl;
    }*/
    cout << "\t\t\t\tHash1(k)\t\t\t\t\tHash2(k)" << endl;
    cout << "\t\tNumber of Collisions" << "\t" << "Average Hits" << "\t\t" << "Number of Collisions" << "\t" << "Average Hits" << endl;
    cout << "Chaining Method\t" << avg_col_count[0] << "\t\t\t" << avg_hit_count[0] << "\t\t\t" << avg_col_count[1] << "\t\t\t" << avg_hit_count[1] <<  endl;
    cout << "Double Hashing\t" << avg_col_count[2] << "\t\t\t" << avg_hit_count[2] << "\t\t\t" << avg_col_count[3] << "\t\t\t" << avg_hit_count[3] <<  endl;;
    cout << "Custom Probing\t" << avg_col_count[4] << "\t\t\t" << avg_hit_count[4] << "\t\t\t" << avg_col_count[5] << "\t\t\t" << avg_hit_count[5] <<  endl;



    return 0;
}

