#include <iostream>
#include<fstream>
#include<queue>
#include<string>
#include "Tree_huffmanCode.h"
#include "mycompare.h"
#include<utility>
#include<unordered_map>
using namespace std;

//For reading and compressing/extracting file
int* freq(string s){
    int* ans = new int[256];
    for(int i=0;i<256;i++){
        ans[i] = 0;
    }
    for(int i=0;i<s.length();i++){
        int index = s[i];
        ans[index]++;
    }
    return ans;
}

TreeNode* formtree(int* freq){
    priority_queue<TreeNode*,vector<TreeNode*>,my_compare> pq;
    for(int i=0;i<256;i++){
        if(freq[i]){
            TreeNode* node = new TreeNode(i,freq[i]);
            pq.push(node);
        }
    }

    while(pq.size()!=1){
    TreeNode* cL = pq.top();
    pq.pop();
    TreeNode* cR = pq.top();
    pq.pop();
    TreeNode* parent = new TreeNode('\0',cL->count+cR->count);
    parent->left = cL;
    parent->right = cR;
    pq.push(parent);
    }
    TreeNode* root = pq.top();
    pq.pop();
    return root;
}
void fillmap(unordered_map<char,string>& charToCode,TreeNode* root,string inmaking,unordered_map<string,char>& codeToChar){
    if(!root) return;
    if(!root->left && !root->right){
        charToCode[root->data] = inmaking;
        codeToChar[inmaking] = root->data;
        return;
    }
        fillmap(charToCode,root->left,inmaking+"0",codeToChar);
        fillmap(charToCode,root->right,inmaking+"1",codeToChar);
}
void fillcompressed(string& s_compressed,string& convert,int n=8){
    int temp=0;
    for(int i=n-1;i>=0;i--){
        char c = convert[i];
        temp = temp + (c<<(n-1-i));
    }
    char converted = temp;
    s_compressed = s_compressed + converted;
}
string huffman(string s,int* freq){
    TreeNode* root = formtree(freq);
    unordered_map<char,string> charToCode;
    unordered_map<string,char> codeToChar;
    fillmap(charToCode,root,"",codeToChar);
    int start=0,end=0,tillconv=0;
    string s_compressed="";
    string mainstream="";
    string convert="";
    string leftout="";
    int i=0;
    while(s[i]!='\0'){
        mainstream = leftout + mainstream + charToCode[s[i]];
        leftout="";
        if(mainstream.length()>=8){
            convert = mainstream.substr(0,8);
            if(mainstream.length()>=9) leftout = mainstream.substr(9);
            fillcompressed(s_compressed,convert);
            mainstream = "";
        }
        i++;
    }
    if(mainstream.length()>0 && mainstream.length()<8) fillcompressed(s_compressed,mainstream,mainstream.length());
    return s_compressed;
}

int main(){
    string s;
    fstream indata;
    indata.open("Sample.txt");
    if(indata.is_open()){
        getline(indata,s,'\0');
        indata.close();
    }
    int* frequency = freq(s);
    string s_compressed = huffman(s,frequency);
    cout<<s_compressed;
    ofstream output("Output.txt");
    output<<s_compressed;
    output.close();

}
