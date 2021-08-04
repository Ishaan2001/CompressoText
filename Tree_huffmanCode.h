class TreeNode{
public:
    char data;
    int count;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char data,int count){
        this->data = data;
        this->count = count;
        left=NULL;
        right=NULL;
    }

};
