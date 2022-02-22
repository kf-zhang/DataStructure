#include <iostream>

#include "HashTable.h"

int HashTable::hash(int key)
{
    return key % BUCKET_SIZE;
}

void HashTable::Insert(int key, int value)
{
    // TODO
    int idx = hash(key);
    HashNode* p = bucket.at(idx);

    if(!p)
    {
        //add head node
        bucket[idx] = new HashNode(key,value);
    }
    else
    {
        if(p->key == key)
        {
            p->val = value;
            return;
        }
        while (p->next)
        {
            if(p->next->key==key)
            {
                p->next->val = value;
                break;
            }
            p=p->next;
        }
        if(!p->next)
        {
            p->next = new HashNode(key,value);
        }  
    }
}

void HashTable::Search(int key)
{
    // TODO
    int idx = hash(key);
    HashNode* p = bucket.at(idx);

    int count = 0;
    while(p)
    {
        if(p->key==key)
        {
            std::cout<<"bucket "<<idx<<" index "<< count<<" key "<<key<<" value "<<p->val<<std::endl;
            return;
        }
        p=p->next;
        count++;
    }
    std::cout<<"Not Found"<<std::endl;
}

void HashTable::Delete(int key)
{
    int idx = hash(key);
    HashNode* p = bucket.at(idx);
    if(!p)
        return;
    if(p->key==key)
    {
        bucket.at(idx) = p->next;
        delete p;
        return;
    }
    while (p->next)
    {
        if(p->next->key==key)
        {
            HashNode* tmp = p->next;
            p->next = p->next->next;
            delete tmp;
            return;
        }
        p=p->next;
    }
    
}

void HashTable::Display()
{
    for (int i = 0; i < BUCKET_SIZE; ++i)
    {
        std::cout << "|Bucket " << i << "|";
        HashNode *node = bucket[i];
        while (node)
        {
            std::cout << "-->(" << node->key << "," << node->val << ")";
            node = node->next;
        }
        std::cout << "-->" << std::endl;
    }
}
