/*
	@author Rajvaibhav D Rahane
*/
/*
*	Program to implement Binary Tree from Postfix Expression
*	and display Tree using Preorder,Inorder and Postorder Traversal (Recursive and Non-Recursive)
*/

#include<iostream>
#include<string.h>
#include<stack>
using namespace std;
void setPriority(float *arr){
	float p=1000000;
	for(int i=0;i<26;i++){
		p/=2;
		arr[i]=p;
	}	
}
bool isOperator(char ch){
	return (ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^' || ch=='%' || ch=='~');
}
class BinaryTree{
	private :
		BinaryTree *left,*right;
		char data;
	public :
		BinaryTree(BinaryTree* left,char data,BinaryTree* right){
			this->left=left;
			this->right=right;
			this->data=data;
		}
		void setData(char data){
			this->data=data;
		}
		char getData(){
			return data;
		}
		void setLeftChild(BinaryTree *left){
			this->left=left;
		}
		BinaryTree* getLeftChild(){
			return left;
		}
		void setRightChild(BinaryTree *right){
			this->right=right;
		}
		BinaryTree* getRightChild(){
			return right;
		}
		static BinaryTree* constructFromPostfixExpression(char postfixExpression[],int length){
			stack<BinaryTree*> leafNodeStack;
			for(int i=0;i<length;i++){
				if(isOperator(postfixExpression[i])){
					BinaryTree *rChild=leafNodeStack.top();
					leafNodeStack.pop();
					BinaryTree *lChild=leafNodeStack.top();
					leafNodeStack.pop();
					BinaryTree *bTreeNode=new BinaryTree(lChild,postfixExpression[i],rChild);
					leafNodeStack.push(bTreeNode);
				}else{
					BinaryTree *bTreeNode=new BinaryTree(NULL,postfixExpression[i],NULL);
					leafNodeStack.push(bTreeNode);
				}
			}
			BinaryTree *rootNode=leafNodeStack.top();leafNodeStack.pop();
			return rootNode;
		}
		static void inorderTraversal(BinaryTree *rootNode){
			if(rootNode){
				inorderTraversal(rootNode->getLeftChild());
				cout<<rootNode->getData();
				inorderTraversal(rootNode->getRightChild());
			}
		}
		static void preorderTraversal(BinaryTree *rootNode){
			if(rootNode){
				cout<<rootNode->getData();
				preorderTraversal(rootNode->getLeftChild());
				preorderTraversal(rootNode->getRightChild());
			}
		}
		static void postorderTraversal(BinaryTree *rootNode){
			if(rootNode){
				postorderTraversal(rootNode->getLeftChild());
				postorderTraversal(rootNode->getRightChild());
				cout<<rootNode->getData();
			}
		}
		static void nonRecursivePreorderTraversal(BinaryTree *rootNode);
		static void nonRecursivePostorderTraversal(BinaryTree* rootNode);
		static BinaryTree* deleteBinaryTree(BinaryTree *rootNode);
		static BinaryTree* constructHuffmanTree(float *priority);
};
BinaryTree* BinaryTree::constructHuffmanTree(float *priority){
	BinaryTree *lastNode=new BinaryTree(NULL,('z'),NULL);
	for(int i=24;i>-1;i--){
		BinaryTree * node=new BinaryTree(NULL,'a'+i,NULL);
		BinaryTree *prevNode= new BinaryTree(node,'0',lastNode);
		lastNode=prevNode;
	}
	return lastNode;
}
void BinaryTree::nonRecursivePostorderTraversal(BinaryTree* rootNode){

}
void BinaryTree::nonRecursivePreorderTraversal(BinaryTree *rootNode){
	stack<BinaryTree *> nodeStack;
	
	if(rootNode){
		nodeStack.push(rootNode);
	}
	while(!nodeStack.empty()){
		BinaryTree* node=nodeStack.top();
		nodeStack.pop();
		cout<<node->getData();
		BinaryTree *rightChild=node->getRightChild(),*leftChild=node->getLeftChild();
		if(rightChild){
			nodeStack.push(rightChild);		
		}
		if(leftChild){
			nodeStack.push(leftChild);
		}
	}
}
BinaryTree* BinaryTree::deleteBinaryTree(BinaryTree *rootNode){
	if(rootNode){
		BinaryTree *leftChild=rootNode->getLeftChild();
		BinaryTree *rightChild=rootNode->getRightChild();
		delete rootNode;
		//cout<<"Node deleted\n";
		leftChild=deleteBinaryTree(leftChild);
		rightChild=deleteBinaryTree(rightChild);
		return NULL;
	}
}
void decode_huff(BinaryTree * root, string s) {
    BinaryTree *tempRoot=root;
    for(int i=0;i<s.length();i++){
        if(s[i]=='0'){
            tempRoot=tempRoot->getLeftChild();
            if(tempRoot->getData()!='0'){
                cout<<tempRoot->getData();
                tempRoot=root;
            }
        }else if(s[i]=='1'){
            tempRoot=tempRoot->getRightChild();
            if(tempRoot->getData()!='0'){
                cout<<tempRoot->getData();
                tempRoot=root;
            }
        }
    }
}
int main(){
	float priority[26]={0};
	string codes[26]={"0","10","110","1110","11110","111110","1111110","11111110","111111110","1111111110","11111111110","111111111110","1111111111110","11111111111110","111111111111110","1111111111111110","11111111111111110","111111111111111110","1111111111111111110","11111111111111111110","111111111111111111110","1111111111111111111110","11111111111111111111110","111111111111111111111110","1111111111111111111111110","1111111111111111111111111"};
	setPriority(priority);
	BinaryTree* rootNode=BinaryTree::constructHuffmanTree(priority);
	//BinaryTree::inorderTraversal(rootNode);cout<<endl;
	//string s;
	//cin>>s;
	//decode_huff(rootNode,s);
	for(int i=0;i<26;i++){
		if(i%5==0)cout<<"\n";
		cout<<i<<" "<<codes[i]<<" "<<(char)(i+'a')<<"\t\t";	
	}cout<<endl;

	int size;
	cin>>size;
	int msg[size];
	for(int i=0;i<size;i++){
		cin>>msg[i];
	}
	//int msg[16]={8,11,14,21,4,18,7,17,4,24,0,17,0,19,7,8};
	for(int i=0;i<size;i++){
		decode_huff(rootNode,codes[msg[i]]);cout<<" ";
	}cout<<endl;
	string str;
	cin>>str;
	decode_huff(rootNode,str);cout<<endl; 	
	return 0;
}
/*int main(){
	int tc;
	cin>>tc;
	int size;
	while(tc--){
		cin>>size;
		char postfixExpression[size+1];
		cin>>postfixExpression;
		
		BinaryTree *bTree;
		bTree=BinaryTree::constructFromPostfixExpression(postfixExpression,strlen(postfixExpression));
			BinaryTree::inorderTraversal(bTree);cout<<endl;
			BinaryTree::preorderTraversal(bTree);cout<<endl;
			BinaryTree::postorderTraversal(bTree);cout<<endl;
			BinaryTree::nonRecursivePreorderTraversal(bTree);cout<<endl;
		bTree=BinaryTree::deleteBinaryTree(bTree);
	}
	return 0;
}*/
