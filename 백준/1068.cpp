// https://www.acmicpc.net/problem/1068

#include<iostream>
#include<vector>
#define MAX 51
using namespace std;

int N, target, ans, root;
vector<int> tree[MAX];

void dfs(int node){
	
	int numOfChild = 0;
	for(int child : tree[node]){
		if(child == target) continue;
		
		dfs(child);	
		++numOfChild;
	}
	
	if(!numOfChild){
		++ans;	
	}
}

int main(){
	
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	// inputs
	cin >> N;
	for(int i=0;i<N;i++){
		int node;
		cin >> node;
		
		if(node == -1){
			root = i;
			continue;
		}
		
		tree[node].push_back(i);
	}
	cin >> target;
	
	if(root == target){
		ans = 0;
	}
	else{
		dfs(root);	
	}
	
	cout << ans << "\n";
	
	return 0;
}