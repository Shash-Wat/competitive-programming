#include "train.h"
#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define REP(i,n) for(int i = 0;i < n;i++)
 
const int N = 5001;
 
bool reach[N][N];
bool reach2[N][N];
vector<int> aha;
int n,m;
vector<int> adj[N];
int source = 0;
 
void dfs(int u){
	for(int v:adj[u]){
		if(reach[source][v])continue;
		reach[source][v] = 1;
		dfs(v);
	}
}
 
void dfs1(int u){
	for(int v:adj[u]){
		if(reach2[source][v] or aha[v])continue;
		reach2[source][v] = 1;
		dfs1(v);
	}
}
 
vector<int> who_wins(vector<int> a, vector<int> r,vector<int> u, vector<int> v) {
		n = a.size();
		m = u.size();
		aha = r;
		REP(i,m){
			adj[u[i]].pb(v[i]);
		}
		while(source < n){
			dfs(source);
			if(!r[source])dfs1(source);
			source++;
		}
		vector<int> ans;
		REP(i,n){
			bool done = 0;
			REP(j,n){
				if(r[j])continue;
				if(reach[i][j] and reach2[j][j]){
					done = 1;
				}
			}
			ans.pb(!done);
		}
		return ans;
}