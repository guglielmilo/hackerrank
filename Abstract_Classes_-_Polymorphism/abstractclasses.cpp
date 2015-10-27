#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

fstream fin("input.txt", ios_base::in);
fstream fout("output.txt", ios_base::out);

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : Cache
{
public:

    LRUCache(int capacity)
    {
        cp = capacity;
        head = NULL;
        tail = NULL;
    };
    
    void set(int key, int val)
    {
        map<int,Node*>::iterator it = mp.find(key);

        if(it != mp.end())
        {
            it->second->value = val;
        }
        else
        {
            Node * node_head = new Node(NULL,NULL,key,val);
            
            if(head == NULL)
            {
                head = node_head;
                tail = node_head;
            }
            else
            {
                Node * node_tmp = head;
                node_head->next = node_tmp;
                head = node_head;
                node_tmp->prev = head;
            }
            mp.insert(pair<int, Node*>(key, node_head));

            if(mp.size() > cp)
            {
                Node * node_tail = tail->prev;

                for(map<int,Node*>::iterator i = mp.begin(); i != mp.end(); ++i)
                {
                	if(i->second == tail)
                    {
                        mp.erase(i);
                        break;
                    }
                }
                node_tail->next = NULL;
                delete(tail);
                tail = node_tail;
            }
        }
    }
    
    int get(int key)
    {
        map <int, Node*>::iterator it = mp.find(key);

        if(it != mp.end())
        {
            return it->second->value;
        }
        else
        {
            return -1;
        }
    }
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}


