#pragma once
#include"linkStack.cpp"
template<class T>
class DisjointSet       //只建立逻辑关系上的等价，与data是否相同无关.逻辑上的等价通过在同一个等价类实现
{
    private:
        struct Node
        {
            int parent;
            T data;
            Node(T x,int index=-1):data(x),parent(index){}
            Node():parent(-1){}
        };
        Node *pointer;
        int maxSize;
        int currentSize;
        int privateFind(const T&x)//找下标
        {
            for(int i=0;i<currentSize;++i)
                if(x==pointer[i].data)
                    return i;
            return -1;
        }
        int findParent(int index)//找对应下标的对应等价类
        {
            if(pointer[index].parent<0)
                return index;
            linkStack<int> s;
            s.push(index);
            while(pointer[index].parent>=0){
                s.push(index);
                index=pointer[index].parent;
            }
            while(!s.isEmpty())
            {
                pointer[s.pop()].parent=index;
            }
            return index;
        }
        void doubleSpace()
        {
            Node*p=pointer;
            maxSize*=2;
            pointer=new Node[maxSize];
            for(int i=0;i<currentSize;++i)
                pointer[i]=p[i];
            delete [] p;
        }
    public:
        DisjointSet(int size=64):maxSize(size),currentSize(0){pointer=new Node[maxSize];}
        DisjointSet(const DisjointSet   &x):maxSize(x.maxSize),currentSize(x.maxSize)
        {
            pointer=new Node[maxSize];
            for(int i=0;i<maxSize;++i)
                pointer[i]=(x.pointer)[i];
        }
        ~DisjointSet(){delete pointer;}
        bool find(const T&x)
        {
            return privateFind(x)>=0;
        }
        void insert(const T&x)
        {
            if(currentSize==maxSize)
                doubleSpace();
            pointer[currentSize++]=Node(x);
        }
        void UNION(const T&x,const T&y)
        {
            int index1=privateFind(x);
            index1=findParent(index1);
            int index2=privateFind(y);
            index2=findParent(index2);
            if(index1<0||index2<0)
                return;
            if(pointer[index1].parent<pointer[index2].parent)
            {
                pointer[index1].parent+=pointer[index2].parent;
                pointer[index2].parent=index1;
            }
            else  if(pointer[index1].parent>=pointer[index2].parent)
            {
                pointer[index2].parent+=pointer[index1].parent;
                pointer[index1].parent=index2;
            }
        }
        bool equivalent(const T&x,const T&y)
        {
            int index1=privateFind(x),index2=privateFind(y);
            if(index1<0||index2<0)
                return false;
            return findParent(index1)==findParent(index2);
        }
        void  disp()
        {
            for(int i=0;i<currentSize;++i)
                std::cout<<"data="<<pointer[i].data<<" parent="<<pointer[i].parent<<'\t';
        }
};
// int main()
// {
//     DisjointSet<int> set;
//     int a[]={95,64,214,84,38,22,82,54,91,93,53,26,57,66,62};
//     int b[]={95,214,82,54,95,64,53,57};
//     for(auto i:a)
//         set.insert(i);
//     for(int i=0;i<4;++i)
//         set.UNION(b[2*i],b[2*i+1]);
//     set.disp();
//     std::cout<<(set.equivalent(95,64)?" 95 64 is equivalent":"95 64 is not equivalent");
// }