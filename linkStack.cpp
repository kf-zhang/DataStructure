#include<iostream>
#include"error.cpp"
template<class T>
class linkStack
{
    private:
        struct Node
        {
            T data;
            Node*next;
            Node():next(NULL){}
            Node(const T &x,Node *p):data(x),next(p){}
        };
        Node *top;
    public:
        linkStack():top(NULL){}
        ~linkStack()
        {
            Node *tmp;
            while(top)
            {
                tmp=top;
                top=top->next;
                delete tmp;
            }
        }
        void push(const T &x)
        {
            Node *tmp=new Node(x,top);
            top=tmp;
        }
        T pop()
        {
            if(top)
            {
                Node*tmp=top;
                T x=top->data;
                top=top->next;
                delete tmp;
                return x;
            }
            throw error("stack pop error");
        }
        bool isEmpty(){return top==NULL;}
        T Top()
        {
            if(!top)
                throw error("stack top error");
            return top->data;
        }   
};
