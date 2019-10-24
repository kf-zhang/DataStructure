#include<iostream>
#include"error.cpp"
class error;
template<class T>
class linkQueue
{
    private:    
        struct Node
        {
            T data;
            Node *next;
            Node(T x,Node *p=NULL):data(x),next(p){}
            Node():next(NULL){}
        };
        Node* head;
        Node* rear;
    public:
        linkQueue():head(NULL),rear(NULL){}
        ~linkQueue()
        {
            Node *tmp;
            while(head)
            {
                tmp=head;
                head=head->next;
                delete tmp;
            }
        }
        bool isEmpty()
        {
            return head==NULL;
        }
        void enQueue(const T& x)
        {
            if(!head){
                head=rear=new Node(x);
                return;
            }
            Node *tmp=new Node(x);
            rear->next=tmp;
            rear=rear->next;
        }
        T deQueue()
        {
            if(!head)
            {
                throw error("deQueue error, quque is empty");
            }
            T x=head->data;
            Node* tmp=head;
            head=head->next;
            if(!head)
                head=rear=NULL;
            delete tmp;
            return x;
        }
        T getRear()
        {
            if(!rear)
                throw error("getHead error, quque is empty");
            return rear->data;
        }
        T getHead()
        {
            if(!head)
                throw error("getHead error, quque is empty");
            return head->data;
        }
};

// int main()
// {
//     linkQueue<int> q;
//     for(int i=0;i<30;++i)
//     {
//         q.enQueue(i);
//         std::cout<<q.getRear()<<' ';
//     }
//     try
//     {
//         std::cout<<std::endl;
//         for(int i=0;i<100;i++)
//         {
//             q.deQueue();
//             std::cout<<q.getHead();
//         }
//     }
//     catch(error & e)
//     {
//         std::cerr << e.what() << '\n';
//     }
// }