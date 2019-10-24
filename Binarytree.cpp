#include"linkStack.cpp"
#include"linkQueue.cpp"
template<class T>
class BinaryTree
{
    private:
        struct Node
        {
            T data;
            Node*left,*right;
            Node():left(NULL),right(NULL){}
            Node(T x,Node *l=NULL,Node *r=NULL):data(x),left(l),right(r){}
        };
        Node *root;
    public:
        BinaryTree():root(NULL){}
        void clear(Node *p)         //非递归实现类似于traverse，不再赘述
        {
            if(!p)
                return;
            clear(p->left);
            clear(p->right);
            delete p;
        }
        ~BinaryTree(){ clear(root);}

        void create(T flag,T quit)
        {
            T data;
            linkQueue<Node*> s;
            Node* p;
            std::cin>>data;
            if(data==flag)
                return;
            root=new Node(data);
            s.enQueue(root);
            while(!s.isEmpty())
            {
                p=s.getHead();
                s.deQueue();

                std::cin>>data;
                if(data==quit)
                    return;
                if(data!=flag)  
                {
                    p->left=new Node(data);
                    s.enQueue(p->left);
                }

                std::cin>>data;
                if(data==quit)
                    return;
                if(data!=flag)  
                {
                    p->right=new Node(data);
                    s.enQueue(p->right);
                }
            }
        }
        int height()     //利用一个栈非递归找height
        {
            if(!root)
                return 0;
            linkStack<int> hStack;
            linkStack<Node*> nStack;
            int max=0;
            Node *p;
            int h;
            nStack.push(root);
            hStack.push(1);
            while(!nStack.isEmpty())
            {
                h=hStack.pop();
                p=nStack.pop();
                if(h>max)   max=h;
                h++;//stack 的push参数为引用，不能push h+1
                if(p->right)
                {
                    nStack.push(p->right);
                    hStack.push(h);
                }
                if(p->left)
                {
                    nStack.push(p->left);
                    hStack.push(h);
                }
            }
            return max;
        }
        void preOrderR()
        {     preOrderR(root);    }
        void preOrderR(Node *p) //递归实现
        {
            if(!p)
                return;
            std::cout<<p->data;
            preOrderR(p->left);
            preOrderR(p->right);
        }
        // void buildTreeBasedOnPreMid(T *pre,T *Mid)
        // {

        // }
        void levelOrder()
        {
            if(!root) return;
            linkQueue<Node *> q;
            Node *p;
            q.enQueue(root);
            while(!q.isEmpty())
            {
                p=q.deQueue();
                std::cout<<p->data<<' ';
                if(p->left) q.enQueue(p->left);
                if(p->right)    q.enQueue(p->right);
            }
        }
        void preOrder()    //非递归实现
        {
            if(!root)           //root非空
                return;
            linkStack<Node *> s;
            s.push(root);
            Node* p;
            while(!s.isEmpty())
            {
                p=s.Top();
                s.pop();
                std::cout<<p->data; //data需要重载过<<
                if(p->right)    s.push(p->right);
                if(p->left)     s.push(p->left);
            }
        }
};
int main()
{
    BinaryTree<int> tree;
    tree.create(-1,-2);
    tree.levelOrder();
    std::cout<<tree.height();
    return 0;
}
