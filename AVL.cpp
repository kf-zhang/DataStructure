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
        Node *findElement(const T& x) const
        {
            if(!root)
                return NULL;
            linkStack<Node*> s;
            Node*p;
            s.push(root);
            while(!s.isEmpty())
            {
                p=s.pop();
                if(x==p->data)
                    return p;
                if(p->right)
                    s.push(p->right);
                if(p->left)
                    s.push(p->left);
            }
            return NULL;
        }
        Node*findNth(int n) const//找到第n大的
        {
            if(!root)
                return NULL;
            Node*p;
            linkStack<Node*>s;
            s.push(root);
            p=root;
            while(p->left){
                s.push(p->left);
                p=p->left;
            }
            while(!s.isEmpty())
            {
                p=s.pop();
                if(!(--n))  return p;
                if(p->right)
                {
                    s.push(p->right);
                    p=p->right;
                    while(p->left)
                    {
                        s.push(p->left);
                        p=p->left;
                    }
                }
            }
            return NULL;
        }

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
        bool isEmpty()const
        {return root==NULL;}
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
        int height(Node*p)const
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
        void traverse()const
        {
            traverse(root);
        }
        void traverse(Node*p)const
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
                        //std::cout<<p->data<<"adaping LL\n";
                        LL(p);
                    }
                    else{
                        //std::cout<<p->data<<"adaping LR\n";
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
                        //std::cout<<p->data<<"adaping RL\n";
                        RL(p);
                    }
                    else{
                        //std::cout<<p->data<<"adaping RR\n";
                        RR(p);
                    }
                }
            }
        }
        bool adjust(Node*&p,bool left)
        {
            if(left)
            {
                int minus=height(p->left)-height(p->right);
                switch(minus)
                {
                    case 0:return false;
                    case -1:return true;
                    case -2:
                            minus=height(p->right->left)-height(p->right->right);
                            switch(minus)
                            {
                                case 1:RL(p);return false;
                                case 0:RR(p);return true;
                                case -1:RR(p);return false;
                            }
                }
            }
            else
            {
                int minus=height(p->right)-height(p->left);
                switch(minus)
                {
                    case 0:
                        return false;
                    case -1:
                        return true;
                    case -2:
                        minus=height(p->left->left)-height(p->left->right);
                        switch(minus)
                        {
                            case 1:LL(p);return false;
                            case 0:LL(p);return true;
                            case -1:LR(p);return false;
                        }
                }
            }  
            return true;//这个仅仅是为了去除warnin，实际运行中应该在此之前就返回了。
        }
        bool del(const T&x,Node*&p)
        {
            if(!p)
                return true;
            if(x<p->data)
            {
                if(del(x,p->left))
                    return true;
                else return adjust(p,true);
            }
            else if(x>p->data)
            {
                if(del(x,p->right))
                    return true;
                else return adjust(p,false);
            }
            else if(p->left&&p->right)//找到被删除的元素而且左右子树都存在
            {
                Node*pointer=p->right;
                while(pointer->left)
                    pointer=pointer->left;
                p->data=pointer->data;
                if(del(pointer->data,p->right))  //此时在右子树上删除而不是在替身节点删除  这个非常关键！！！！！！！！！
                    return true;
                else
                    return adjust(p,false);
                // else 
                // {
                //     p->data=p->right->data;
                //     if(del(x,p->right))
                //         return true;
                //     else     //虽然许多else有些赘余，但是为了可读性好一点还是加上
                //         return adjust(p,false);
                // }
            }
            else
            {
                Node*tmp=p;
                p=p->left?p->left:p->right;
                delete tmp;
                return false;
            }
        }
        void del(const T&x)
        {
            del(x,root);
        }
        bool find(const T &x)const{return findElement(x);}
        T findnTH(int n) const //找到第n大的
        {
            Node*p=findNth(n);
            if(p)
                return p->data;
            throw error("AVL findnTH out of boundary");
        }  
};
// int main()
// {
//     AVL<int> tree;
//     int a[]={12,54,86,4,96,34,94,2524,5,62,58,125,79,13,94,523};
//     int m[]={3,9,1,99};
//     int n[]={2524,5,2432,13};
//     for(auto i:a)
//         tree.insert(i);
//     tree.traverse();
//     std::cout<<'\n';
//     try
//     {
//          for(auto i:m)
//         std::cout<<tree.findnTH(i)<<' ';
//     }
//     catch(const error& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
//     for(auto i:n)
//         std::cout<<(tree.find(i)?"Found":"Not find")<<i<<'\n';

//     // for(auto i:a){
//     //     tree.del(i);
//     //     tree.traverse();
//     //     std::cout<<'\n';
//     // }
//     // std::cout<<(tree.isEmpty()?"EMPTY":"NOT EMPTY");
// }