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
		static void nonRecursiveInorderTraversal(BinaryTree* rootNode);
		static BinaryTree* deleteBinaryTree(BinaryTree *rootNode);
};
void BinaryTree::nonRecursiveInorderTraversal(BinaryTree* rootNode){
	stack<BinaryTree*> nodeStack;
	BinaryTree* currentNode=rootNode;
	while(currentNode || !nodeStack.empty()){
		while(currentNode){
			nodeStack.push(currentNode);
			currentNode=currentNode->getLeftChild();
		}
		currentNode=nodeStack.top();
		nodeStack.pop();
		cout<<currentNode->getData();
		currentNode=currentNode->getRightChild();
	}
}
void BinaryTree::nonRecursivePostorderTraversal(BinaryTree* rootNode){
	if(rootNode){
		stack<BinaryTree*> nodeStack;
		BinaryTree* tempRoot=rootNode;
		do{
			while(tempRoot){
				if(tempRoot->getRightChild()){
					nodeStack.push(tempRoot->getRightChild());
				}
				nodeStack.push(tempRoot);
				tempRoot=tempRoot->getLeftChild();
			}
			tempRoot=nodeStack.top();nodeStack.pop();
			BinaryTree* rightChild=tempRoot->getRightChild();
			if(rightChild && !nodeStack.empty() && rightChild==nodeStack.top()){
				nodeStack.pop();
				nodeStack.push(tempRoot);
				tempRoot=rightChild;
			}else{
				cout<<tempRoot->getData();
				tempRoot=NULL;
			}
		}while(!nodeStack.empty());
	}
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
int main(){
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
			BinaryTree::nonRecursivePostorderTraversal(bTree);cout<<endl;
			BinaryTree::nonRecursiveInorderTraversal(bTree);cout<<endl;
		bTree=BinaryTree::deleteBinaryTree(bTree);
	}
	return 0;
}
/*			UI 1.0
int main(){
	char postfixExpression[]="ab+ef*g*-";
	//string postfixExpression;
	BinaryTree *bTree;
	bTree=BinaryTree::constructFromPostfixExpression(postfixExpression,strlen(postfixExpression));
	cout<<postfixExpression<<" "<<strlen(postfixExpression)<<endl;
	//cout<<(bTree==NULL?"NULL":"Not NULL")<<endl;
	BinaryTree::inorderTraversal(bTree);cout<<endl;
	BinaryTree::preorderTraversal(bTree);cout<<endl;
	BinaryTree::postorderTraversal(bTree);cout<<endl;
	bTree=BinaryTree::deleteBinaryTree(bTree);
	//cout<<(bTree==NULL?"NULL":"Not NULL")<<endl; 

	
	return 0;
}*/
