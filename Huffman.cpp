#include<iostream>
#include"linkStack.cpp"
#include<string>
template<class T>
class HuffmanTree
{
    private:
        struct Node{
            T data;
            int left,right,parent;
            double pro;
            Node(){}
            Node(const T& m,double d,int x=-1,int y=-1,int z=-1):data(m),pro(d),left(x),right(y),parent(z){}
        };
        Node *p;
        int size;
    public:
        void buildTree()
        {
            int index1,index2;    //1为最小
            double pro1,pro2;
            T flag;
            for(int i=size-2;i>=0;--i)
            {
                pro1=pro2=0x7fffffff;
                for(int j=2*size-1;j>i;--j)
                {
                    if(p[j].parent==-1)
                    {
                        if(p[j].pro<pro1)
                        {
                            index2=index1;
                            pro2=pro1;
                            index1=j;
                            pro1=p[j].pro;
                        }
                        else if(p[j].pro<pro2)
                        {
                            index2=j;
                            pro2=p[j].pro;
                        }
                    }
                }
                p[i]=Node(flag,pro1+pro2,index1,index2);
                p[index1].parent=i;
                p[index2].parent=i;
            }
        }
        HuffmanTree(int n)   //n为需要编码的数量
        {
            size=n;
            p=new Node[2*n-1];
            T data;
            double x;
            std::cout<<"Please input data";
            for(int i=size-1;i<2*size-1;++i)  //?????
            {
                    std::cin>>data;
                    std::cin>>x;
                    p[i]=Node(data,x);
            }
            buildTree();
        }
        ~HuffmanTree(){ delete [] p;}
        void show()
        {
            for(int i=0;i<2*size-1;++i)
            {
                std::cout<<p[i].data<<' '<<p[i].pro<<' '<<p[i].left<<' '<<p[i].right<<' '<<p[i].parent<<std::endl;
            }
            std::cout<<std::endl;
        }
        void getCode()
        {
            bool *CODE=new bool[size];
            getCode(CODE);
        }
        void getCode(bool *CODE,int node=0,int last=0)//为了偷懒就不写成非递归啦,权值相同的节点的左右子树顺序不确定
        {
            if(p[node].left==-1&&p[node].right==-1)
            {
                std::cout<<"The code of "<<p[node].data<<" is ";
                for(int i=0;i<last;++i)
                    std::cout<<CODE[i]?1:0;
                std::cout<<std::endl;
                return;
            }
            if(p[node].left!=-1){
                CODE[last]=true;
                getCode(CODE,p[node].left,last+1);
            }
            if(p[node].right!=-1){
                CODE[last]=false;
                getCode(CODE,p[node].right,last+1);
            }
        }
};

// int main()
// {
//     HuffmanTree<char> s(7);
//     s.show();
//     s.getCode();
// }
