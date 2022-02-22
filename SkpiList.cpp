#include <iostream>
#include <stdlib.h>

#include "SkipList.h"

int SkipList::randomLevel()
{
    int result = 1;
    while (result < MAX_LEVEL && (double)rand() / RAND_MAX < 0.5)
    {
        ++result;
    }
    return result;
}

void SkipList::Insert(int key, int value)
{
    // TODO
    SKNode* newNode = new SKNode(key,value,SKNodeType::NORMAL);

    int level = MAX_LEVEL - 1;
    SKNode* p = head;
    while (level>=0)
    {
        while (p->forwards[level]->key<key)
            p = p->forwards[level];
        newNode->forwards[level] = p;
        level--;
    }
    
    if(p->forwards.at(0)->key!=key){
        int growLevel = randomLevel();
        for(int i=0;i<growLevel;i++)
        {
            SKNode* next = newNode->forwards.at(i)->forwards.at(i);
            newNode->forwards.at(i)->forwards.at(i) =  newNode;
            newNode->forwards[i] = next;
        }
        for(int i=growLevel;i<MAX_LEVEL;i++)
            newNode->forwards.at(i) = NIL;
    }
    else{
        p->forwards.at(0)->val = value;
        delete newNode;
    }
}
void print(int level,int key)
{
    std::cout<<level+1<<",";
    if(key==0)
        std::cout<<"h ";
    else if(key==INT_MAX)
        std::cout<<"N ";
    else
        std::cout<<key<<" ";
}
void SkipList::Search(int key)
{
    // TODO
    SKNode* p = head;
    int level = MAX_LEVEL - 1;
    while (level>=0)
    {
        print(level,p->key);
        while (p->forwards[level]->key<key)
        {
            p = p->forwards[level];
            print(level,p->key);
        }
        level--;
    }
    p = p->forwards[0];
    print(0,p->key);
    if(p->key==key){
        std::cout<<p->val<<"\n";
    }
    else
        std::cout<<"Not Found\n";
    
}

void SkipList::Delete(int key)
{
    // TODO
    SKNode* p = head;
    std::vector<SKNode*> v;
    v.resize(MAX_LEVEL);

    int level = MAX_LEVEL - 1;
    while(level>=0)
    {
        while( p->forwards[level]->key < key)
            p = p->forwards[level];
        v.at(level) = p;
        level--;
    }

    if(p->forwards.at(0)->key==key)
    {
        SKNode* tmp = p->forwards.at(0);
        for(int i=0;i<MAX_LEVEL;i++)
        {
            if( v.at(i)->forwards.at(i) == tmp )
            {
                v.at(i)->forwards.at(i) = tmp->forwards.at(i);
            }
        }
        delete tmp;
    }
}

void SkipList::Display()
{
    for (int i = MAX_LEVEL - 1; i >= 0; --i)
    {
        std::cout << "Level " << i + 1 << ":h";
        SKNode *node = head->forwards[i];
        while (node->type != SKNodeType::NIL)
        {
            std::cout << "-->(" << node->key << "," << node->val << ")";
            node = node->forwards[i];
        }

        std::cout << "-->N" << std::endl;
    }
}
