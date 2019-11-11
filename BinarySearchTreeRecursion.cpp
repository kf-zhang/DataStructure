#include<iostream>
template<class T>
class BinarySearchTree//递归大法好
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
        BinarySearchTree():root(NULL){}
        void clear(Node*p)
        {
            if(!p)
                return;
            if(p->left)
                clear(p->left);
            if(p->right)   
                clear(p->right);
            delete p;
        }
        ~BinarySearchTree()
        {
            clear(root);
        }
        void insert(const T&x) {insert(x,root);}
        void insert(const T&x,Node*&p)//指针引用嗷
        {
            if(!p){
                p=new Node(x);
                return;
            }
            if(x<p->data)
                insert(x,p->left);
            else if(x>p->data)
                insert(x,p->right);//相同不插入    
        }
        void remove(const T&x) {    remove(x,root); }
        void remove(const T&x,Node*&p)
        {
            if(!p)
                return;
            else if(x<p->data)
                remove(x,p->left);
            else if(x>p->data)
                remove(x,p->right);
            else if(p->left&&p->right)
            {
                Node*tmp=p->right;
                while(tmp->left)
                    tmp=tmp->left;
                p->data=tmp->data;
                remove(x,tmp);
            }
            else
            {
                Node*tmp=p;
                p=p->left?p->left:p->right;
                delete tmp;
            }  
        }
        void traverse()
        {
            traverse(root);
        }
        void traverse(Node *p)//中序遍历
        {
            if(!p)
                return;
            traverse(p->left);
            std::cout<<p->data<<' ';
            traverse(p->right);
        }
};


int main()
{
    int a[10]={1,5,2,7,97,32,45,1,3,55};
    int j[7]={3,2,5,0,1,1,97};
    BinarySearchTree<int> b;
    for(int i=0;i<10;++i){
        b.insert(a[i]);
        b.traverse();
        std::cout<<std::endl;
    }
    for(int i=0;i<7;++i){
        b.remove(j[i]);
        b.traverse();
        std::cout<<std::endl;
    }
}
