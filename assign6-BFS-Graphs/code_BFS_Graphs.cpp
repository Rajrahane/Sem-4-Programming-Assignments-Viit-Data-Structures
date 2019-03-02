/*
	@author Rajvaibhav Rahane

	Problem Statement Link - https://www.hackerearth.com/practice/algorithms/graphs/depth-first-search/practice-problems/algorithm/bishu-and-his-girlfriend/
	Application of BFS algorithm on Graphs.

	There are N countries {1,2,3,4....N} and N-1 roads(i.e depicting a tree)
	Bishu lives in the Country 1 so this can be considered as the root of the tree.
	Now there are Q girls who lives in various countries (not equal to 1) .
	All of them want to propose Bishu.But Bishu has some condition.
	He will accept the proposal of the girl who lives at minimum distance from his country.
	Now the distance between two countries is the number of roads between them.
	If two or more girls are at the same minimum distance then he will accept the proposal of the girl who lives in a country with minimum id.
	No two girls are at same country.
	Input: First line consists of N,i.e number of countries Next N-1 lines follow the type u v which denotes there is a road between u and v. 
	Next line consists of Q Next Q lines consists of x where the girls live.
	Output: Print the id of the country of the girl who will be accepted.
	Help Him!!!!!
	contraints: 2<=N<=1000 1<=u,v<=N 1<=Q<=(N-1)
*/
#include<iostream>
#include<queue>
using namespace std;
/*
	@return A Vector of levels  of all nodes in graph, level[rootNode]=0;
	@param rootNode-The node to start traversal from
	@param edgeList-Adjacency list depicting the graph
	@param nodes- No of nodes in Graph
*/
vector<int> getLevelList(int rootNode,vector<int> *edgeList,int nodes){
    vector<int> levelList(nodes,-1);
    bool isNodeVisited[nodes]={false};
    int poppedNode,iterator;
    
    queue<int> nodeQueue;
    nodeQueue.push(rootNode);
    levelList[rootNode]=0;
    isNodeVisited[rootNode]=true;
    
    while(!nodeQueue.empty()){
        poppedNode=nodeQueue.front();
        nodeQueue.pop();
        
        for(iterator=0;iterator<edgeList[poppedNode].size();iterator++){
            if(!isNodeVisited[edgeList[poppedNode][iterator]]){
                levelList[edgeList[poppedNode][iterator]]=levelList[poppedNode]+1;
                isNodeVisited[edgeList[poppedNode][iterator]]=true;
                nodeQueue.push(edgeList[poppedNode][iterator]);
            }
        }
    }
    return levelList;
}
int main(){
    int nodes,edges;
    cin>>nodes;
    vector<int> edgeList[nodes];
    int x,y; 
    edges=nodes-1;
    for(int i=0;i<edges;i++){
        cin>>x>>y;
        x--;y--;
        edgeList[x].push_back(y);
        edgeList[y].push_back(x);
    }
    vector<int> levelList=getLevelList(0,edgeList,nodes);
    /*for(int i=0;i<levelList.size();i++){
        cout<<levelList[i]<<" ";
    }cout<<endl;*/
    int queries;
    cin>>queries;
    int cityNumber,minDistanceCity,minimumDistance,cityDistance;
    cin>>cityNumber;
    minDistanceCity=(--cityNumber);
    minimumDistance=levelList[cityNumber];
    while(--queries){
        cin>>cityNumber;
        cityDistance=levelList[--cityNumber];
        if(minimumDistance>cityDistance){
            minimumDistance=cityDistance;
            minDistanceCity=cityNumber;
        }else if(minimumDistance==cityDistance && cityNumber<minDistanceCity){
            minDistanceCity=cityNumber;
        }
    }
    cout<<minDistanceCity+1<<endl;
    return 0;
}