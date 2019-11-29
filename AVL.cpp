#include<iostream>
#include"linkStack.cpp"
#include"error.cpp"
template<class T>
class AVL
{
    private:
        struct Node
        {
            T data;
            Node *left,*right;
            Node(const T&x,Node* y=NULL,Node* z=NULL):data(x),left(y),right(z){}
            Node():left(NULL),right(NULL){}
        };
        Node *root;

    public:
        AVL(){root=NULL;}
        ~AVL()
        {
            if(!root) return;
            linkStack<Node*> s;
            Node *tmp;
            s.push(root);
            while(!s.isEmpty())
            {
                tmp=s.pop();
                if(tmp->right)
                    s.push(tmp->right);
                if(tmp->left)
                    s.push(tmp->left);
                delete tmp;
            }
        }
        void LL(Node*&pointer)//旋转需要使用指针的引用
        {
            if(!pointer || !pointer->left)
                throw error("AVL LL rotation error");
            Node*tmp=pointer->left;
            pointer->left=tmp->right;
            tmp->right=pointer;
            pointer=tmp;
        }
        void RR(Node*&pointer)
        {
            if(!pointer||!pointer->right)
                throw error("AVL RR rotation error");
            Node *tmp=pointer->right;
            pointer->right=tmp->left;
            tmp->left=pointer;
            pointer=tmp;
        }
        void LR(Node*&pointer)
        {
            RR(pointer->left);
            LL(pointer);
        }
        void RL(Node*&pointer)
        {
            LL(pointer->right);
            RR(pointer);
        }
        int height(Node*p)
        {
            if(!p)
                return 0;
            int max=0;
            int h;
            Node *pointer;
            linkStack<Node*> nS;
            linkStack<int> hS;
            nS.push(p);
            hS.push(1);
            while(!nS.isEmpty())
            {
                h=hS.pop();
                pointer=nS.pop();
                if(h>max)
                    max=h;
                h++;//子树的高度
                if(pointer->right){
                    nS.push(pointer->right);
                    hS.push(h);
                }
                if(pointer->left){
                    nS.push(pointer->left);
                    hS.push(h);
                }
            }
            return max;
        }
        void traverse()
        {
            traverse(root);
        }
        void traverse(Node*p)
        {
            if(!p)
                return;
            linkStack<Node*> nS;
            linkStack<int> tS;
            Node*pointer;
            int time;
            nS.push(p);
            tS.push(0);
            while(!nS.isEmpty())
            {
                pointer=nS.pop();
                time=tS.pop()+1;
                if(time==2){
                    std::cout<<pointer->data<<' ';
                    if(pointer->right){
                        nS.push(pointer->right);
                        tS.push(0);
                    }
                }
                else if(time==1)
                {
                    nS.push(pointer);
                    tS.push(time);
                    if(pointer->left)
                    {
                        nS.push(pointer->left);
                        tS.push(0);
                    }
                }
            }
        }
        void insert(const T&x)
        {
            insert(x,root);
        }
        void insert(const T&x,Node*&p)
        {
            if(!p){
                p=new Node(x);
                return;
            }
            if(x<p->data)
            {
                insert(x,p->left);
                int lH=height(p->left);
                int rH=height(p->right);
                if(lH-rH>=2)
                {
                    if(x<p->left->data){
                        std::cout<<p->data<<"adaping LL\n";
                        LL(p);
                    }
                    else{
                        std::cout<<p->data<<"adaping LR\n";
                        LR(p);
                    }
                }
            }
            else if(x>p->data)
            {
                insert(x,p->right);
                int lH=height(p->left);
                int rH=height(p->right);
                 if(lH-rH<=-2)
                {
                    if(x<p->right->data){
                        std::cout<<p->data<<"adaping RL\n";
                        RL(p);
                    }
                    else{
                        std::cout<<p->data<<"adaping RR\n";
                        RR(p);
                    }
                }
            }
        }
        void del(const T&x)
        {

        }
        T find(int n)//找到第n大的
        {

        }
};
int main()
{
    AVL<int> tree;
    int a[]={12,54,86,4,96,34,94,2524,5,62,58,125,79,13,94,523};
    for(auto i:a)
        tree.insert(i);
    tree.traverse();
}