#include<bits/stdc++.h>
using namespace std;

struct Node{
    Node*child[26];
    bool isEnd;

    Node(){
        for(int i=0;i<26;i++){
            child[i]=nullptr;
        }
        isEnd=false;
    }
};
class Trie{
private:
    Node*root;
public:
    Trie(){
        root=new Node();
    }
    void insert(string word){
        Node*node=root;
        for(int i=0;i<word.size();i++){
            if(node->child[word[i]-'a']==nullptr){
                node->child[word[i]-'a']=new Node();
            }
            node=node->child[word[i]-'a'];
        }
        node->isEnd=true;
    }
    bool search(string word){
        Node*node=root;
        for(int i=0;i<word.size();i++){
            if(node->child[word[i]-'a']==nullptr)return false;
            node=node->child[word[i]-'a'];
        }
        return node->isEnd;
    }
    bool prefix(string word){
        Node*node=root;
        for(int i=0;i<word.size();i++){
            if(node->child[word[i]-'a']==nullptr)return false;
            node=node->child[word[i]-'a'];
        }
        return true;
    }
};