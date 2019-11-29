#include<iostream>
template<class T>
void swap(T&x,T&y)
{
    T tmp=x;
    x=y;
    y=tmp;
}
template<class T>
void BubbleSort(T*p,int n,bool (*f)(T,T))
{
    bool flag=false;
    for(int i=0;i<n-1&&!flag;++i)
    {
        flag=true;
        for(int j=0;j<n-i-1;++j)
        {
            if(f(p[j],p[j+1])){
                swap(p[j],p[j+1]);
                flag=false;
            }
        }
    }
}

template<class T>
void ChooseSort(T*p,int n,bool (*f)(T,T))
{
    int maxIndex;
    int i,j;
    for(i=0;i<n-1;++i)
    {
        maxIndex=i;
        for(j=i+1;j<n;++j)
        {
            if(f(p[j],p[maxIndex]))
                maxIndex=j;
        }
        swap(p[i],p[maxIndex]);
    }
}
template<class T>
void InsertSort(T*p,int n,bool (*f)(T,T))
{
    T tmp;
    int i,j;
    for(i=1;i<n;++i)
    {
        tmp=p[i];
        for(j=i-1;j>=0&&f(tmp,p[j]);--j)
            p[j+1]=p[j];
        p[j+1]=tmp;
    }
}
template<class T>
int partition(T *p,int left,int right,bool (*f)(T,T))
{
    T divider=p[right];
    int i=left,j=left;
    for(;j<right;++j)
    {
        if(f(divider,p[j]))
            swap(p[i++],p[j]);
    }
    swap(p[right],p[i]);
    return i;
}
template<class T>
void quickSort(T *p,int left,int right,bool (*f)(T,T))
{
    if(left>=right)
        return;
    int mid=partition<T>(p,left,right,f);
    quickSort<T>(p,left,mid-1,f);
    quickSort<T>(p,mid+1,right,f);
}
template<class T>
void quickSort(T *p,int n,bool (*f)(T,T))
{
    quickSort(p,0,n-1,f);
}
template<class T>
void shellSort(T*p,int n,bool (*f)(T,T),int *shell=NULL,int len=0)
{
    T tmp;
    int i,j,step;
    if(!shell)
        for(step=n/2;step>=1;step/=2) 
        {
            for(i=2*step-1;i<n;++i)
            {
               tmp=p[i];
               for(j=i-step;j>=0&&f(tmp,p[j]);j-=step)
                    swap(p[j],p[j+step]);
                p[j+step]=tmp;
            }
        }
    else
        for(step=shell[len-1];len>0;step=shell[--len]) 
        {
            for(i=2*step-1;i<n;++i)  //i的初始值为2*step-1
            {
               tmp=p[i];
               for(j=i-step;j>=0&&f(tmp,p[j]);j-=step)
                    swap(p[j],p[j+step]);
                p[j+step]=tmp;
            }
        }
}
template<class T>
void percolateDown(T*p,int n,int hole,bool (*f)(T,T))
{
    int maxChild;
    T tmp=p[hole];
    for(;hole*2+1<n;hole=maxChild)
    {
        maxChild=hole*2+1;
        if(maxChild+1<n&&f(p[maxChild+1],p[maxChild]))
            maxChild++;
        if(f(p[maxChild],tmp))
            p[hole]=p[maxChild];
        else
            break;
        
    }
    p[hole]=tmp;
}
template<class T>
void heapSort(T *p,int n,bool (*f)(T,T))
{
    for(int i=(n-2)/2;i>=0;i--)
        percolateDown(p,n,i,f);
    for(int i=0;i<n;++i)
    {
        swap(p[0],p[n-i-1]);
        percolateDown(p,n-i-1,0,f);
    }
}
template<class T>
struct Node
{
    T data;
    Node*next;
    Node():next(NULL){}
    Node(T x,Node*p=NULL):data(x),next(p){}
};
void bucketSort(int *p,int n,bool (*f)(int,int))//基数排序需要几个优先级不同的键来对比，需要根据实际数据来选择这里用整形来演示
{
    int max=p[0];
    for(int i=1;i<n;++i)
        if(f(p[i],max))
            max=p[i];

    int len=0;
    int base=1;
    int index;
    for(;max>0;max/=10,len++);
    Node<int> *head[10]={0};//一定要初始化置零
    Node<int> *rear[10]={0};
    Node<int> *link=NULL;
    Node<int> *pointer;
    //Node<int> *debug;
    int i,j;
    for(i=0;i<n;++i)
        link=new Node<int>(p[i],link);
  
    for(i=0;i<len;++i,base*=10)
    {
        for(j=0,pointer=link;j<n;++j,pointer=link)
        {
            index=(pointer->data/base)%10;
            if(!head[index])
            {
                head[index]=rear[index]=pointer;
                link=pointer->next;
                pointer->next=NULL;
            }
            else//链接入链的时候要把在之前优先级比较中优先级小的放在前面
            {
                link=pointer->next;
                rear[index]->next=pointer;
                rear[index]=pointer;
            }
        }
        for(j=0;j<10;++j)
        {
            if(head[j])
            {
                if(!link){
                    link=head[j];
                    pointer=rear[j];
                }
                else
                {
                    pointer->next=head[j];
                    pointer=rear[j];
                }
                head[j]=rear[j]=NULL;
            }
        }
        // debug=link;
        // std::cout<<"debug";
        // while(debug)
        // {
        //     std::cout<<debug->data<<' ';
        //     debug=debug->next;
        // }
        // std::cout<<'\n';
    }
    for(i=0,pointer=link;i<n;++i,pointer=pointer->next)//输入排序的结果
        p[i]=pointer->data;
    while(link)//释放内存
    {
        pointer=link->next;
        delete link;
        link=pointer;
    }
}
template<class T>
void merge(T*p,int left,int right,int mid,bool (*f)(T,T))//left~mid,mid+1~right
{
    T* array=new T[right-left+1];
    int i=left,j=mid+1;
    int index=0;
    while(i<=mid&&j<=right)
        if(f(p[i],p[j]))
            array[index++]=p[i++];
        else
            array[index++]=p[j++];
    while(i<=mid)
        array[index++]=p[i++];
    while(j<=right)
        array[index++]=p[j++];
    for(i=0;i<right-left+1;++i)
        p[left+i]=array[i];
    delete [] array;    
}
template<class T>
void mergeSort(T*p,int left,int right,bool(*f)(T,T))
{
    if(left>=right)
        return;
    int mid=(left+right)/2;
    mergeSort(p,left,mid,f);
    mergeSort(p,mid+1,right,f);
    merge(p,left,right,mid,f);
}
template<class T>
void mergeSort(T*p,int n,bool(*f)(T,T))
{
    mergeSort(p,0,n-1,f);
}
//测试
template<class T>
bool greater(T x,T y)
{
    return x>y;
}
template<class T>
bool smaller(T x,T y)
{
    return x<y;
}
int main()
{
    int a[]={32,25,234,34523,5254,56,194,4364,341,651,3,545,574,935,335};
    int shell[]={5,4,2,1};
    //BubbleSort<int>(a,15,greater);
    //ChooseSort<int>(a,15,greater);
    //InsertSort<int>(a,15,greater);
    //quickSort<int>(a,15,greater);
    //shellSort<int>(a,15,greater,shell,4);
    //shellSort<int>(a,15,greater);
    //heapSort<int>(a,15,greater);
    //bucketSort(a,15,greater);
    //mergeSort(a,0,14,greater);
    mergeSort(a,15,greater);
    for(auto &i:a)
        std::cout<<i<<' ';
}