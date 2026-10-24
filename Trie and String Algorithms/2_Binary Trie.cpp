#include<bits/stdc++.h>
using namespace std;

struct Node{
    Node*child[2];
    Node(){
        child[0]=nullptr;
        child[1]=nullptr;
    }
};
class BinaryTrie{
private:
    Node*root;
public:
    BinaryTrie(){
        root=new Node();
    }
    void insert(int num){
        Node*node=root;
        for(int i=0;i<32;i++){
            int bit=(num>>i) & 1;
            if(node->child[bit]==nullptr){
                node->child[bit]=new Node();
            }
            node=node->child[bit];
        }
    }
    int getMaxXor(int num){
        Node*node=root;
        int ans=0;
        for(int i=0;i<32;i++){
            int bit=(num>>i) & 1;
            int opo=1-bit;
            if(node->child[opo]!=nullptr){
                ans|=(1<<i);
                node = node->child[opo];
            }else{
                node=node->child[bit];
            }
        }
        return ans;
    }
};