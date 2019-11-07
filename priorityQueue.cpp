#include<iostream>
#include"error.cpp"
template<class T>
class priorityQueue
{
    private:
     
        T *root;
        int maxSize;
        int currentSize;//根节点为0
        bool (*Greater)(T,T);//x >y
    public:
        priorityQueue(bool f(T,T),int max=64):maxSize(max),currentSize(0){root=new T[maxSize];Greater=f;}
        ~priorityQueue()
        {
            delete [] root;
        }
        void doubleSpace()
        {
            T *tmp=new T[maxSize*2];
            maxSize*=2;
            for(int i=0;i<maxSize;++i)
                tmp[i]=root[i];
            delete [] root;
            root=tmp;
        }
        void enQueue(const T&x)
        {
            if(currentSize==maxSize)
                doubleSpace();
            int index=currentSize++;
            while(index&&Greater(x,root[(index-1)/2]))
            {
                root[index]=root[(index-1)/2];
                index=(index-1)/2;
            }
            root[index]=x;
        }
        void down(int index)
        {
            if(index<0)
                return;
            T data=root[index];
            int maxChildIndex;
            while(index*2+1<currentSize)
            {
                maxChildIndex=index*2+1;
                if(maxChildIndex+1<currentSize && Greater(root[maxChildIndex+1],root[maxChildIndex]))
                    maxChildIndex++;
                if(Greater(root[maxChildIndex],data))//应该比较data而非root[index],此处类似于插入排序中的插入
                    root[index]=root[maxChildIndex];
                else
                    break;
                index=maxChildIndex;
            }
            root[index]=data;
        }
        T deQueue()
        {
            if(!currentSize)
                throw error("Heap dequeue error");
            T data=root[0];
            root[0]=root[--currentSize];
            down(0);
            return data;
        }
        void show()
        {
            for(int i=0;i<currentSize;++i)
                std::cout<<root[i]<<' ';
            std::cout<<std::endl;
        }
        void buildHeap(T *pointer,int n)
        {
            delete [] root;
            root=pointer;
            maxSize=currentSize=n;
            for(int i=(currentSize-2)/2;i>=0;--i)
                down(i);
        }
};
bool greater(int x,int y)
{
    return x>y;
}
int main()
{
    bool (*f)(int ,int)=greater;
    priorityQueue<int> x(f,5);
    int a[]={19,2,4,8,45,6,2,4,7,11,34,99,65};
    // for(int i=0;i<13;++i)
    //     x.enQueue(a[i]);
    x.buildHeap(a,13);
    try
    {
        for(int i=0;i<14;++i)
        std::cout<<x.deQueue()<<' ';
    }
    catch(error & e)
    {
        std::cerr << e.what() << '\n';
    }
}
