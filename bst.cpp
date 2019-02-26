/*
*	@author Rajvaibhav D Rahane
*/
/*
*	Generic Implementation of Binary Search Tree
*	implements functions - add(),traversePreorder()-Recursive
*	Permits classes with overloaded << extraction, == equals and > greater than operators.
*	Permits dynamically allocated basic datatypes.
*/
#include<iostream>
using namespace std;
enum TraversalOrder{PREORDER=1,INORDER=2,POSTORDER=3};

template<class E>
class BinaryTree{
	private:
		class Node{
			private:
				Node *leftChild,*rightChild;
				E *element;
			public:
				Node(Node *leftChild,E* element,Node* rightChild){
					this->leftChild=leftChild;
					this->element=element;
					this->rightChild=rightChild;
				}
				void setElement(E* element){
					this->element=element;
				}
				E* getElement(){
					return element;
				}
				void setLeftChild(Node *leftChild){
					this->leftChild=leftChild;
				}
				Node *getLeftChild(){
					return leftChild;
				}
				Node *setRightChild(Node *rightChild){
					this->rightChild=rightChild;
				}
				Node *getRightChild(){
					return rightChild;
				}
		};
		Node *rootNode;
		void preorderRecursive(Node *);
		void traverseTreeRecursively(Node *root,TraversalOrder);
		int heightOfNode(Node *root);
	public:
		BinaryTree(){
			rootNode=NULL;
		}
		void add(E *element);
		void traversePreorder();
		void traverseTree(TraversalOrder);
		int height();
		E* min();
};
template<class E>
void BinaryTree<E>::add(E* element){				//function to insert node in the bSTree. Non Recursive
	Node *newNode=new Node(NULL,element,NULL);		//create a New Node	
	if(!rootNode){
		rootNode=newNode;
	}else{
		bool nodeInserted=false;
		Node *tempRoot=rootNode;
		do{
			if(*(tempRoot->getElement())==*element){
				cout<<"Cant Insert";break;
			}else if(*(tempRoot->getElement())>*element){		//element to left of tempRoot
				if(!tempRoot->getLeftChild()){
					tempRoot->setLeftChild(newNode);
					nodeInserted=true;
					break;
				}else{
					tempRoot=tempRoot->getLeftChild();
				}
			}else{
				if(!tempRoot->getRightChild()){
					tempRoot->setRightChild(newNode);
					nodeInserted=true;
					break;
				}else{
					tempRoot=tempRoot->getRightChild();
				}
			}
		}while(!nodeInserted);
	}
}

template<class E>
void BinaryTree<E>::traverseTree(TraversalOrder order){
	if(rootNode){
		traverseTreeRecursively(rootNode,order);
		cout<<endl;
	}
}

template<class E>
void BinaryTree<E>::traverseTreeRecursively(Node *root,TraversalOrder order){
	if(root){
		if(order==PREORDER){
			cout<<*(root->getElement())<<" ";
		}
		traverseTreeRecursively(root->getLeftChild(),order);
		if(order==INORDER){
			cout<<*(root->getElement())<<" ";
		}
		traverseTreeRecursively(root->getRightChild(),order);
		if(order==POSTORDER){
			cout<<*(root->getElement())<<" ";
		}
	}
}
template<class E>
void BinaryTree<E>::preorderRecursive(Node *root){
	if(root){
		cout<<*(root->getElement())<<" ";
		preorderRecursive(root->getLeftChild());
		preorderRecursive(root->getRightChild());
	}
}

template<class E>
void BinaryTree<E>::traversePreorder(){
	if(rootNode){
		preorderRecursive(rootNode);
		cout<<endl;
	}
}

template<class T>
int BinaryTree<T>::heightOfNode(Node *root){
	if(!root)
		return 0;
	int lHeight=heightOfNode(root->getLeftChild()),rHeight=heightOfNode(root->getRightChild());
	return 1+(lHeight>rHeight?lHeight:rHeight);
}

template<class T>
T* BinaryTree<T>::min(){
	if(!rootNode)
		return NULL;
	Node* leftNode=rootNode;
	while(leftNode->getLeftChild()){
		leftNode=leftNode->getLeftChild();
	}
	return leftNode->getElement();
}

template<class T>
int BinaryTree<T>::height(){
	return heightOfNode(rootNode);
}

class Integer{
		int data;
	public:
		Integer(int data){
			this->data=data;
		}
		bool operator==(Integer secondInteger){
			return (data==secondInteger.data);
		}
		bool operator>(Integer secondInteger){
			return data>secondInteger.data;
		}
		friend ostream& operator<<(ostream &out,const Integer);
		~Integer(){
			//cout<<"Destructor called\n";
		}
};
ostream & operator<<(ostream &out,Integer integer){
	out<<integer.data<<" ";
	return out;
	}
int main(){
	int choice;
	BinaryTree<Integer> iBST;
	do{
		cin>>choice;
		switch(choice){
			case 1:{
				int num;
				cin>>num;
				Integer *nn=new Integer(num);	
				//cout<<&(*nn);			
				iBST.add(nn);
				//cout<<"Here\n";
				break;
			}
			case 2:{
				iBST.traversePreorder();
				iBST.traverseTree(PREORDER);
				iBST.traverseTree(INORDER);
				iBST.traverseTree(POSTORDER);
				break;
			}
			case 3:{
				cout<<iBST.height()<<endl;
				break;
			}
			case 4:{
				Integer *nn=iBST.min();
				if(nn)
					cout<<*nn<<endl;
				else 
					cout<<"Empty Tree\n";		
			}
			case 5:break;
			default:cout<<"Invalid Input";
		}
	}while(choice!=5);
	/*float *nn=new float;*nn=(100.34);
	float *n2=new float;*n2=(99.43);
	iBST.add(nn);iBST.add(n2);*/
	iBST.traversePreorder();
	return 0;
}
