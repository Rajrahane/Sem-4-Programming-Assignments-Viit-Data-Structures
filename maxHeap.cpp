#include<iostream>
#include<vector>
#include<exception>
using namespace std;
class EmptyHeapException:public exception{
	public: const char*what()const throw(){
		return "EmptyHeapException";	
	}
};
template<class T>
class MaxHeap{
	private:
		vector<T> values;
		int capacity,size;
		void adjust(const int root,const int size);
	public:
		MaxHeap(int capacity=10){
			values.resize(capacity);
			this->capacity=capacity;
			size=0;
		}
		void insert(T element);
		T remove();
		void display(){
			for(int i=0;i<size;i++){
				cout<<values[i]<<" ";
			}cout<<endl;
		}
		void heapSort();
};
template<class T>
void MaxHeap<T>::heapSort(){
	for(int i=size-1;i>0;i--){		//sort heap
		T temp=values[i];
		values[i]=values[0];
		values[0]=temp;
		adjust(0,i);
	}
	display();
	for(int i=size/2-1;i>=0;i--){		//rebuild heap
		adjust(i,size);	
		display();
	}
}
template<class T>
void MaxHeap<T>::adjust(const int root,const int size){		//auxiliary method to heapify a subtree
	T element=values[root];
	int j;
	for(j=2*root+1;j<size;){
		if((j+1)<size && values[j]<values[j+1])
			j++;
		if(element>=values[j])
			break;
		values[(j-1)/2]=values[j];
		j*=2;j++;
	}
	values[(j-1)/2]=element;
}
template<class T>
T MaxHeap<T>::remove(){				//remove node from heap
	if(size==0)
		throw EmptyHeapException();
	T element=values[0];
	T lastElement=values[--size];
	int currentNode=0,child=1;
	while(child<=size){
		if(child<size && values[child]<values[child+1])
			child++;
		if(lastElement>=values[child])
			break;	
		values[currentNode]=values[child];
		currentNode=child;
		child*=2;child++;
	}
	values[currentNode]=lastElement;
	//values.pop_back();
	//capacity--;
	cout<<"capacity "<<values.capacity()<<endl;
	return element;
}
template<class T>
void MaxHeap<T>::insert(T element){				//insert node to heap
	if(size==capacity){
		cout<<"resizing"<<capacity<<" "<<values.capacity()<<endl;
		values.resize(2*capacity);
		capacity*=2;
	}
	int currentNode=size++;
	while(currentNode!=0 && values[((currentNode-1)/2)]<element){
		values[currentNode]=values[(currentNode-1)/2];
		currentNode--;
		currentNode/=2;
	}	
	values[currentNode]=element;
}
int main(){
	MaxHeap<int> myMaxHeap(1);
	int choice,num;
	do{
		cin>>choice;
		switch(choice){
			case 1:{
				cin>>num;
				myMaxHeap.insert(num);
				break;
			}case 2:{
				myMaxHeap.display();
				break;
			}case 3:{
				try{
					cout<<myMaxHeap.remove();
				}catch(EmptyHeapException e){
					cout<<e.what()<<endl;
				}
				break;
			}case 4:{
				myMaxHeap.heapSort();
				myMaxHeap.display();
				break;
			}case 5:break;
		}
	}while(choice!=5);
	return 0;
}
