#include<iostream>
#include<stack>
using namespace std;
void traverseDepthFirst(int startNode,bool *edgeList,int nodes){
	bool visited[nodes]={false};
	int maxStackSize=-1;
	stack<int> nodeStack;
	int currentNode;
	nodeStack.push(startNode);
	while(!nodeStack.empty()){
		currentNode=nodeStack.top();
		nodeStack.pop();
		if(!visited[currentNode]){
			cout<<currentNode+1<<" ";
			visited[currentNode]=true;
		}
		for(int i=nodes-1;i>-1;i--){
			if(*((edgeList+currentNode*nodes)+i) && !visited[i]){
				nodeStack.push(i);
			}
		} 
		int size=nodeStack.size();
		if(maxStackSize<size){
			//cout<<"here\n";
			maxStackSize=nodeStack.size();		
		}
	}
	cout<<"Max Stk Size"<<maxStackSize<<endl;
}
int main(){
	int nodes,edges;
	int tc,head,tail;
	cin>>tc;
	while(tc--){
		cin>>nodes>>edges;
		bool edgeList[nodes][nodes]={false};
		for(int i=0;i<edges;i++){
			cin>>head>>tail;
			edgeList[--head][--tail]=true;
		}
		for(int i=0;i<nodes;i++){
			cout<<i+1<<"->";
			for(int j=0;j<nodes;j++){
				if(edgeList[i][j])
					cout<<j+1<<", ";
			}cout<<endl;
		}
		traverseDepthFirst(0,(bool*)edgeList,nodes);
	}
	return 0;
}
