#include<iostream>
#include"error.cpp"
template<class T>
class linkList
{
    private:
        struct Node
        {
            T data;
            Node*next;
            Node():next(NULL){}
            Node(T x,Node*p=NULL):data(x),next(p){}
        };
        Node*head;
        int len;
    public:
        linkList();
        ~linkList();
        void remove(const T&x);
        void insert(const T&x);
        bool exist(const T&x)const;
        void traverse() const;
        void reverse();
        T&  at(int index);
        T&  operator[](int index);
        void del(int index);
};
template<class T>
linkList<T>::linkList()
{
    head=new Node();//需要一个空结点,为了插入和删除的方便
    len=0;
}
template<class T>
linkList<T>::~linkList()
{
    Node*tmp;
    while(head)
    {
        tmp=head;
        head=head->next;
        delete tmp;
    }
}
template<class T>
void linkList<T>::remove(const T&x)
{
    Node*p=head;
    while(p->next&&p->next->data!=x)  //找到x之前的一个节点，同时一定要注意判断指针是否为空,否则程序会异常终止。
        p=p->next;   
    if(!(p->next))   
        return;
    Node*tmp=p->next;
    p->next=tmp->next;
    delete tmp;
    len--;
}
template<class T>
void linkList<T>::insert(const T&x)
{
    Node*tmp=new Node(x,head->next);
    head->next=tmp;
    len++;
}
template<class T>
bool linkList<T>::exist(const T&x)const
{
    Node*p=head->next;//要跳过空结点
    while(p&&p->data!=x)
        p=p->next;  //写程序记得要p->p->ext,不要忘记。
    return p;
}
template<class T>
void linkList<T>::traverse()const
{
    Node*p=head->next;
    while(p)
    {
        std::cout<<p->data<<' ';
        p=p->next; 
    }
}
template<class T>
void linkList<T>::reverse()
{
    Node*p1,*p2=NULL;//p2初始一定要置零
    while(head->next)
    {
        p1=head->next;
        head->next=p1->next;
        p1->next=p2;
        p2=p1;
    }
    head->next=p2;//！！！！！一定要把链表链回去
}
template<class T>
T &linkList<T>::at(int index)
{
    if(index>=len)
        throw error("linkList<T>::at(int index) out of boundary ");
    Node*p=head;
    for(int i=0;i<len-index;++i)
        p=p->next;
    return p->data;
}
template<class T>
T &linkList<T>::operator[](int index)
{
    if(index>=len)
        throw error("linkList<T>::operator[](int index) out of boundary ");
    Node*p=head;
    for(int i=0;i<len-index;++i)
        p=p->next;
    return p->data;
}
template<class T>
void linkList<T>::del(int index)
{
    if(index>=len)
        return;
    Node*p=head;
    for(int i=0;i<len-index-1;++i)
        p=p->next;
    Node*tmp=p->next;
    p->next=tmp->next;
    delete tmp;
    len--;
}
