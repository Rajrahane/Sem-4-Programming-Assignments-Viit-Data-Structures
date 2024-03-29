/*
*
*	@author Rajvaibhav Rahane
*/

#include<iostream>
#include<string.h>
using namespace std;
int max(int a,int b){
	return a>b?a:b;
}

template<class E>
class AVLTree{
	private:
		class Node{
			private:
				Node *leftChild,*rightChild;
				E *element;
				int height;
			public:
				Node(Node *leftChild,E* element,Node* rightChild){
					this->leftChild=leftChild;
					this->element=element;
					this->rightChild=rightChild;
					height=1;
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
				void setHeight(int height){
					this->height=height;
				}
				int getHeight(){
					return height;
				}				
		};
		Node* rootNode;
		int height(Node *);
		Node *leftRotate(Node*);
		Node *rightRotate(Node*);
		Node* insert(E*,Node*);
		Node* minValueNode(Node*);
		Node* removeNodeUtil(E*,Node*);
		int getBalance(Node*);
		void preorderRecursive(Node *);
	public:
		AVLTree(){
			rootNode=NULL;
		}
		void add(E* element);	
		void remove(E*);	
		E* find(E);
		void traversePreorder();
};
template<class E>
E* AVLTree<E>::find(E element){
	Node* currentNode=rootNode;
	while(currentNode){
		E* currentElement=currentNode->getElement();
		if(*(currentElement)==element){
			return currentElement;
		}
		if(*(currentElement)<element){
			currentNode=currentNode->getRightChild();
		}else{
			currentNode=currentNode->getLeftChild();
		}
	}
	return NULL;
}
template<class E>
int AVLTree<E>::height(Node* node){
	if(node==NULL)return 0;
	return node->getHeight();
}

template<class E>
typename AVLTree<E>::Node* AVLTree<E>::leftRotate(Node *node){
	Node* y=node->getRightChild();
	Node* x=y->getLeftChild();
	
	y->setLeftChild(node);
	node->setRightChild(x);
	
	node->setHeight(1+max(height(node->getLeftChild()),height(node->getRightChild())));	
	y->setHeight(1+max(height(y->getLeftChild()),height(y->getRightChild())));	

	return y;	
}

template<class E>
typename AVLTree<E>::Node * AVLTree<E>::rightRotate(Node *node){
	Node *y=node->getLeftChild();
	Node *x=y->getRightChild();

	y->setRightChild(node);
	node->setLeftChild(x);

	node->setHeight(1+max(height(node->getLeftChild()),height(node->getRightChild())));	
	y->setHeight(1+max(height(y->getLeftChild()),height(y->getRightChild())));	

	return y;
}

template<class T>
int AVLTree<T>::getBalance(Node* node){
	if(node==NULL)return 0;
	return height(node->getLeftChild())-height(node->getRightChild());
}

template<class E>
typename AVLTree<E>::Node* AVLTree<E>::minValueNode(Node* node){
	if(node){
		while(node->getLeftChild()){
			node=node->getLeftChild();
		}
	}
	return node;
}

template<class E>
typename AVLTree<E>::Node* AVLTree<E>::insert(E*element, Node* rootNode){
	if(rootNode==NULL){
		return new Node(NULL,element,NULL);
	}
	if(*element<*(rootNode->getElement())){
		cout<<"Go Left\n";
		rootNode->setLeftChild(insert(element,rootNode->getLeftChild()));
	}else if(*(rootNode->getElement())<*element){
		cout<<"Go Right\n";
		rootNode->setRightChild(insert(element,rootNode->getRightChild()));
	}else{
		cout<<"Dupliate Entry\n";
		return rootNode;
	}
	rootNode->setHeight(1+max(height(rootNode->getLeftChild()),height(rootNode->getRightChild())));
	int balance=getBalance(rootNode);
	
	if(balance>1){							//left
		if(*element<*(rootNode->getLeftChild()->getElement())){	//left left
			cout<<"LL Rotation\n";
			return rightRotate(rootNode);
		}else{							//left right
			cout<<"LR Rotation\n";
			rootNode->setLeftChild(leftRotate(rootNode->getLeftChild()));
			return rightRotate(rootNode);
		}
	}else if(balance<-1){						//right rotate
		if(*(rootNode->getRightChild()->getElement())<*element){	//right right
			cout<<"RR Rotation\n";
			return leftRotate(rootNode);
		}else{							//right left
			cout<<"RL Rotation\n";
			rootNode->setRightChild(rightRotate(rootNode->getRightChild()));
			return leftRotate(rootNode);
		}
	}
	cout<<"No Rotation\n";
	return rootNode;
}

template<class E>
typename AVLTree<E>::Node* AVLTree<E>::removeNodeUtil(E* element,Node *rootNode){
	if(!rootNode){
		return rootNode;
	}
	if(*element<*(rootNode->getElement())){		//less than
		rootNode->setLeftChild(removeNodeUtil(element,rootNode->getLeftChild()));
	}else if(*element==*(rootNode->getElement())){	//equals
		Node * left=rootNode->getLeftChild(),*right=rootNode->getRightChild();
		if(!left || !right){	//one or no child
			Node *temp=left?left:right;
			if(!temp){		//no child
				temp=rootNode;
				rootNode=NULL;
			}else{
				Node* swap=rootNode;
				rootNode=temp;
				temp=swap;
			}
			delete temp;
		}else{
			Node* temp=minValueNode(right);
			rootNode->setElement(temp->getElement());
			rootNode->setRightChild(removeNodeUtil(temp->getElement(),rootNode->getRightChild()));
		}
	}else{						//greater
		rootNode->setRightChild(removeNodeUtil(element,rootNode->getRightChild()));
	}
	if(!rootNode)
		return rootNode;
	rootNode->setHeight(1+max(height(rootNode->getLeftChild()),height(rootNode->getRightChild())));
	int balance=getBalance(rootNode);
	if(balance>1){		//left case
		int leftChildBalance=getBalance(rootNode->getLeftChild());
		if(leftChildBalance>=0){	//left left case;
			return rightRotate(rootNode);
		}else{				//left right case;
			rootNode->setLeftChild(leftRotate(rootNode->getLeftChild()));
			return rightRotate(rootNode);
		}
	}else if(balance<-1){	//right case
		int rightChildBalance=getBalance(rootNode->getRightChild());
		if(rightChildBalance<=0){	//right right case
			return leftRotate(rootNode);
		}else{
			rootNode->setRightChild(rightRotate(rootNode->getRightChild()));
			return leftRotate(rootNode);
		}
	}
	return rootNode;		//unchanged root
}

template<class E>
void AVLTree<E>::remove(E* element){
	rootNode=removeNodeUtil(element,rootNode);
}

template<class E>
void AVLTree<E>::add(E* element){	
	rootNode=insert(element,rootNode);
}
template<class E>
void AVLTree<E>::preorderRecursive(Node *root){
	if(root){
		cout<<*(root->getElement())<<" ";
		preorderRecursive(root->getLeftChild());
		preorderRecursive(root->getRightChild());
	}
}

template<class E>
void AVLTree<E>::traversePreorder(){
	if(rootNode){
		preorderRecursive(rootNode);
		cout<<endl;
	}
}
class Entry{
	string name,meaning;
	public:
		Entry(){}
		Entry(string name,string meaning){		
			this->name=name;
			this->meaning=meaning;
		}
		void setMeaning(string meaning){
			this->meaning=meaning;
		}
		string getName(){
			return name;
		}
		string getMeaning(){
			return meaning;
		}
		friend ostream& operator<<(ostream&,const Entry&);
		bool operator<(Entry e);
		bool operator==(Entry e);
};
bool Entry::operator==(Entry entry){
	return name.compare(entry.name)==0;
}
bool Entry::operator<(Entry entry){
	int value=name.compare(entry.name);
	//cout<<name<<" "<<entry.name<<" "<<value<<endl;
	if(value<0)
		return true;
	return false;
}
ostream& operator<<(ostream& out,Entry& entry){
	out<<entry.getName()<<" "<<entry.getMeaning();
	return out;
}

int main(){
	int choice;
	char changeDescription;
	AVLTree <Entry> avlTree;
	do{
		cin>>choice;
		switch(choice){
			case 1:{
				string name,meaning;
				cin>>name>>meaning;
				Entry* entry=new Entry(name,meaning);
				avlTree.add(entry);
				break;
			}case 2:{
				avlTree.traversePreorder();
				break;
			}case 3:{
				string name;
				cout<<"Enter Name : ";
				cin>>name;
				Entry e(name,"empty");
				Entry * entry=avlTree.find(e);
				if(entry!=NULL){
					cout<<*entry<<endl;
					cout<<"Change Description?(Y,y) : ";
					cin>>changeDescription;
					if(changeDescription=='y' || changeDescription=='Y'){
						cout<<"Enter new Description : ";
						string meaning;
						cin>>meaning;
						(*entry).setMeaning(meaning);
						cout<<"Changes Saved\n";
						cout<<*entry<<endl;	
					}else{
						cout<<"Changes Aborted\n";
					}
				}else{
					cout<<"Name not found\n";
				}
				break;
			}case 4:{
				string name;
				cout<<"Enter Name : ";
				cin>>name;
				Entry e(name,"empty");
				Entry * entry=avlTree.find(e);
				if(entry){
					cout<<*entry<<endl;
					cout<<"Confirm Delete ? (Y,y) : ";
					char option;
					cin>>option;
					if(option=='y' || option=='Y'){
						avlTree.remove(entry);
						cout<<"Entry removed";
						cout<<*entry<<endl;
						delete entry;
					}else{
						cout<<"Deletion aborted";
					}
				}else{
					cout<<"Name not found\n";
				}
				break;
			}case 5:break;
		}
	}while(choice!=5);
	return 0;
}
/*	UI 1.0
int main(){
	string name,meaning;
	cin>>name>>meaning;
	Entry entry(name,meaning);
	cout<<entry<<endl;
	return 0;
}*/
