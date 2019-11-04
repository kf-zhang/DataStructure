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
        struct buildBlock
        {
            int pL,pR,mL,mR;
            buildBlock(int x,int y,int z,int w):pL(x),pR(y),mL(z),mR(w){}
            buildBlock(){}
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
        void create(T *mid,T* pre,int n)  //非递归实现根据中序先序遍历建树,rootb必须为空，否则会丢失之前的数据
        {
            if(n<=0)
                return;
            linkStack<buildBlock> bS;
            linkStack<Node *> nS;
            buildBlock b(0,n-1,0,n-1);
            buildBlock tmp;
            Node *p;
            root=new Node(pre[0]);
            int i;
            int interval;
            nS.push(root);
            bS.push(b);
            while(!nS.isEmpty())
            {
                p=nS.pop();
                b=bS.pop();

                for(i=b.mL;i<=b.mR&&mid[i]!=pre[b.pL];++i);
                interval=i-1-b.mL;
                if(b.pL+2+interval<=b.pR){ //判断条件
                    p->right=new Node(pre[b.pL+2+interval]);
                    nS.push(p->right);
                    tmp=buildBlock(b.pL+2+interval,b.pR,i+1,b.mR);
                    bS.push(tmp);
                }
                if(0<=interval){  //判断条件
                    p->left=new Node(pre[b.pL+1]);
                    nS.push(p->left);
                    tmp=buildBlock(b.pL+1,b.pL+1+interval,b.mL,b.mL+interval);
                    bS.push(tmp);
                }
            }
        }
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
        void midOrder()
        {
            if(!root) return;
            linkStack<Node *> s;
            Node *p=root;
            s.push(root);
            while(p->left)
            {
                s.push(p->left);
                p=p->left;
            }
            while(!s.isEmpty())
            {
                p=s.Top();
                s.pop();
                std::cout<<p->data<<' ';
                if(p->right)
                {
                    p=p->right;
                    s.push(p);
                    while(p->left)
                    {
                        s.push(p->left);
                        p=p->left;
                    }
                }
            }

        }
        void postOrder()
        {
            if(!root) return;
            linkStack<Node*> nS;
            linkStack<int> tS;//维护node 访问次数的栈
            Node *p;
            int zero=0;
            int time;
            nS.push(root);
            tS.push(zero);
            while(!nS.isEmpty())
            {
                p=nS.pop();
                time=tS.pop();
                time++;       //time记录的是访问该节点的次数
                switch(time)
                {
                    case 3: std::cout<<p->data<<' ';
                            break;
                    case 2: 
                            nS.push(p);
                            tS.push(time);
                            if(p->right){       
                                nS.push(p->right);
                                tS.push(zero);
                            }
                            break;
                    case 1:
                            nS.push(p);
                            tS.push(time);
                            if(p->left){
                                nS.push(p->left);
                                tS.push(zero);
                            }
                            break;
                }
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
// int main()
// {
//     BinaryTree<int> tree;
//     //tree.create(-1,-2);
//     int pre[]={0,1,3,5,6,8,7,2,4};
//     int mid[]={8,6,5,7,3,1,0,2,4};
//     tree.create(mid,pre,9);
//     tree.preOrder();
//     tree.midOrder();
//     std::cout<<std::endl;
//     std::cout<<tree.height();
//     return 0;
// }
