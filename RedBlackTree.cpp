#include<iostream>
#include"linkQueue.cpp"
template<class T>
class RedBlackTree
{
    public:
         enum Color{RED,BLACK};
    protected:
         struct Node
        {
            T data;
            Node*left,*right,*parent;
            Color color; 
            Node();
            Node(const T&x,Node*p1=NULL,Node*p2=NULL,Node*p3=NULL);
            virtual ~Node();

        };
        Node* _search(Node*p,const T & tar,Node*&pa);
        Node* _insert(const T & tar);
        void display(Node*p);
        void adjustDoubleRed(Node*p);
        void reconnect(Node*r1,Node*r2,Node*r3,Node*t1,Node*t2,Node*t3,Node*t4);
    private:
        Node *root;
    public:
        RedBlackTree();
        bool in(const T & tar);
        void display();
        void traverse();
        void insert(const T& x);
};

template<class T>
RedBlackTree<T>::Node::Node():left(NULL),right(NULL),parent(NULL),color(RED){}

template<class T>
RedBlackTree<T>::Node::Node(const T& x,Node*p1,Node*p2,Node*p3):data(x),parent(p1),left(p2),right(p3),color(RED){}

template<class T>
RedBlackTree<T>::Node::~Node(){}

template<class T>
RedBlackTree<T>::RedBlackTree():root(NULL){}

template<class T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::_search(Node*p,const T & tar,Node*&pa)
//若找到，则返回指向data的指针，未找到则返回空指针
//若找到，pa为指向data的父节点的指针，若未找到，则为最后一个查找的节点
{
    if(!p || tar==p->data)
        return p;
    pa=p;
    return _search(tar<p->data?p->left:p->right,tar,pa);
}

template<class T>
bool RedBlackTree<T>::in(const T&tar)
{
    Node*p=NULL;
    return _search(root,tar,p)!=NULL;
}

template<class T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::_insert(const T&tar)
{
    if(!root)
    {
        root=new Node(tar);
        root->color=BLACK;
        return root; 
    }
    Node*p;
    _search(root,tar,p);
    if(p->left==NULL&&p->data>tar)
    {
            p->left=new Node(tar,p);
            p->left->parent=p;
            return p->left;
    }
    else if (p->right==NULL&&p->data<tar)
    {
         p->right=new Node(tar,p);
         p->right->parent=p;
         return p->right;
    }
    return NULL;
}

template<class T>
void RedBlackTree<T>::display(Node*p)
{
    if(!p)
        return;
    display(p->left);
    std::cout<<p->data<<' '<<(p->color==RED?"RED":"BLACK")<<"   ";
    display(p->right);
}

template<class T>
void RedBlackTree<T>::display()
{
    display(root);
}

template<class T>
void RedBlackTree<T>::insert(const T& x)
{
    Node*p=_insert(x);
    if(!p)//未插入
        return;
    adjustDoubleRed(p);
}
template<class T>
void RedBlackTree<T>::reconnect(Node*r1,Node*r2,Node*r3,Node*t1,Node*t2,Node*t3,Node*t4)//r1<r2<r3 t1<t2<t3<t4
{
    r2->left=r1;    r1->parent=r2;
    r2->right=r3;   r3->parent=r2;
    r1->left=t1;    if(t1) t1->parent=r1;//子树可能为0！！！
    r1->right=t2;   if(t2) t2->parent=r1;
    r3->left=t3;    if(t3) t3->parent=r3;
    r3->right=t4;   if(t4) t4->parent=r3;
    r1->color=RED; //别忘了修改颜色，虽然这样子全部修改有些不必要，但是这样子可以覆盖全部四种情形
    r2->color=BLACK;
    r3->color=RED;
}
template<class T>
void RedBlackTree<T>::adjustDoubleRed(Node*p)
{
    if(!(p->parent))
        return;
    if(!(p->parent->parent))
        return;
    if(!(p->parent->color==RED&&p->color==RED))
        return;
    Node*g=p->parent->parent;
    Node*f=p->parent;
    if(g->left&&g->right&&g->left->color==g->right->color)  //当祖父结点的左右子节点颜色相同时，也就是都为红色
    {
        g->color=RED;
        g->left->color=BLACK;
        g->right->color=BLACK;
        if(root->color==RED)
            root->color=BLACK;
        adjustDoubleRed(g);
    }
    else
    {
       if(g->data>p->parent->data)//父节点在祖父节点的左侧
       {
           if(f->data>p->data)
           {
               f->parent=g->parent;
               if(!f->parent)//!!!如果向上提升到了父节点，根节点的值也要修改
                root=f;
               else
               {
                   if(f->parent->data>f->data)
                    f->parent->left=f;
                   else
                    f->parent->right=f;
               }
               reconnect(p,f,g,p->left,p->right,f->right,g->right);
           }
           else
           {
               p->parent=g->parent;
               if(!p->parent)
                root=p;
                else
               {
                   if(p->parent->data>p->data)
                    p->parent->left=p;
                   else
                    p->parent->right=p;
               }
               reconnect(f,p,g,f->left,p->left,p->right,g->right);
           }  
       }
       else//父节点在祖父节点的右侧
       {
           if(f->data>p->data)
           {
               p->parent=g->parent;
               if(!p->parent)
                root=p;
                else
               {
                   if(p->parent->data>p->data)
                    p->parent->left=p;
                   else
                    p->parent->right=p;
               }
               reconnect(g,p,f,g->left,p->left,p->right,f->right);
           }
           else
           {
               f->parent=g->parent;
               if(!f->parent)
                root=f;
                else
               {
                   if(f->parent->data>f->data)
                    f->parent->left=f;
                   else
                    f->parent->right=f;
               }
               reconnect(g,f,p,g->left,f->left,p->left,p->right);
           } 
       }
    }
}

template<class T>
void RedBlackTree<T>::traverse()
{
    if(!root)
        return;
    linkQueue<Node*> q;
    q.enQueue(root);
    Node* p;
    while(!q.isEmpty())
    {
        p=q.deQueue();
        std::cout<<p->data<<' '<<(p->color==RED?"RED":"BLACK")<<"   ";
        if(p->left)
            q.enQueue(p->left);
        if(p->right)
            q.enQueue(p->right);
    }
}

// int main()
// {
//     RedBlackTree<int> t;
//     for (int i = 0; i < 100; i++)
//     {
//         t.insert(i);
//     }
//     t.display();
//     std::cout<<'\n';
//     t.traverse();
//     std::cout<<'\n';
//     std::cout<<'\n'<<t.in(1)<<' '<<t.in(99)<<'\n';
//     std::cout<<"end";
//     return 0;
// }





