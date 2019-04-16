/*
*	@author Rajvaibhav Rahane
*/
#include<iostream>
using namespace std;

class Node{
	int primaryKey;
	string name;
	public:
		int getPrimaryKey(){
			return primaryKey;	
		}
		void setPrimaryKey(int primaryKey){
			this->primaryKey=primaryKey;
		}
		Node(){}
		Node(int primaryKey,string name){
			this->primaryKey=primaryKey;
			this->name=name;
		}
		string getName(){
			return name;		
		}
		friend ostream& operator<<(ostream &,const Node&);		
};

ostream& operator<<(ostream &out,const Node& node){
	out<<node.name<<" "<<node.primaryKey<<endl;
	return out;
}

template<class T>
class MyHashMap{
	T** hashTable;
	int capacity,size;
	public:
		MyHashMap(int capacity=10){
			this->capacity=capacity;
			size=0;
			this->hashTable=new T*[capacity];
			for(int i=0;i<capacity;i++){
				hashTable[i]=NULL;
			}
		}
		void insert(T *node){
			if(size==capacity){
				cout<<"FULL";		
			}
			int hashKey=(*node).getPrimaryKey()%capacity;
			for(int i=0;i<capacity;i++){
				int lpHashKey=(hashKey+i)%capacity;
				if(hashTable[lpHashKey]==NULL){
					hashTable[lpHashKey]=node;
					size++;
					cout<<"node inserted\n";
					cout<<*hashTable[lpHashKey]<<" index "<<lpHashKey<<endl;
					return ;
				}
			}
		}
		void printHashTable();
};

template<class T>
void MyHashMap<T>::printHashTable(){
	for(int i=0;i<capacity;i++){
		Node *node=(Node*)hashTable[i];
		if(node!=NULL)cout<<*node;
		else cout<<0<<endl; 
		//cout<<((Node*)((hashTable[i])))->getName()<<endl;
	}
}
int main(){
	string name;
	cin>>name;
	Node *node=new Node(1,name);
	cout<<*node<<endl;
	cout<<node<<endl;
	MyHashMap<Node> hashMap(10);
	hashMap.printHashTable();
	hashMap.insert(node);	
	node->setPrimaryKey(2);
	hashMap.insert(node);	
	node->setPrimaryKey(1);
	for(int i=0;i<10;i++)
	hashMap.insert(node);
	hashMap.printHashTable();
	return 0;
}
