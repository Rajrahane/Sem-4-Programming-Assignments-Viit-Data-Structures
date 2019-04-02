#include<iostream>
#include<vector>
using namespace std;
template<class T>
class HashMap{
	private:
		vector<T> values;
		int capacity,size;
		//void heapify(int currentNode);
	public:
		HashMap(int capacity=10){
			values.resize(capacity);
			this->capacity=capacity;
			size=0;
		}
		void insert(T element);
		void display(){
			for(int i=0;i<size;i++){
				cout<<values[i]<<" ";
			}cout<<endl;
		}
};
template<class T>
void HashMap<T>::insert(T element){
	if(size==capacity){
		cout<<"resizing";
		values.resize(2*size);
		capacity=2*size;
	}
	int currentNode=size++;
	while(currentNode!=0 && values[((currentNode-1)/2)]<element){
		values[currentNode]=values[(currentNode-1)/2];
		currentNode--;
		currentNode/=2;
	}	
	values[currentNode]=element;
}
/*template<class T>
void HashMap<T>::heapify(int currentNode){
	while(currentNode!=0 && values[]){
	}
}*/
int main(){
	HashMap<int> myHashMap(1);
	int choice,num;
	do{
		cin>>choice;
		switch(choice){
			case 1:{
				cin>>num;
				myHashMap.insert(num);
				break;
			}case 2:{
				myHashMap.display();
				break;
			}case 3:break;
		}
	}while(choice!=3);
	return 0;
}
