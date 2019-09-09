#include "bubblesort2.h"
#include <bits/stdc++.h>

using namespace std;

#define all(v) v.begin(),v.end()
#define pb push_back
#define REP(i,n) for(int i = 0;i < n;i++)
#define RE(i,n) for(int i = 1;i <= n;i++)

const int N = 1e6+1;
int seg[4*N];
int f[4*N];
int lazy[4*N];
set<int> best[N];
map<int,int> cool;
vector<int> comp;
int n;

#define mid (l+r)/2
#define child 2*node

void build(int node,int l,int r){
	lazy[node] = 0;
	if(l == r){
		f[node] = 0;
		seg[node] = -*best[l].begin();
		return;
	}
	build(child,l,mid);
	build(child+1,mid+1,r);
	seg[node] = max(seg[child+1],seg[child]);
}

inline void pushdown(int node,int l,int r,bool goat = 1){
	seg[node] -= lazy[node];
	f[node] -= lazy[node];
	if(l != r){
		lazy[child] += lazy[node];
		lazy[child+1] += lazy[node];
		if(goat){
			pushdown(child,l,mid,0);
			pushdown(child+1,mid+1,r,0);
		}
	}
	lazy[node] = 0;
	return;
}

void add(int node,int l,int r,int start,int end,int val){
	
	pushdown(node,l,r);
	if(l > end or start > r)return;
	if(start <= l and r <= end){
		
		lazy[node] += val;
		pushdown(node,l,r);
		return;
	}
	add(child,l,mid,start,end,val);
	add(child+1,mid+1,r,start,end,val);
	seg[node] = max(seg[child+1],seg[child]);
}

void update(int node,int l,int r,int ind){
	pushdown(node,l,r);
	if(l == r){
		seg[node] = f[node]-*best[l].begin();
		return;
	}
	if(ind <= mid)update(child,l,mid,ind);
	else update(child+1,mid+1,r,ind);
	seg[node] = max(seg[child+1],seg[child]);
}

int cur = 0;

void compress(){
	sort(all(comp));
	REP(i,comp.size()){
		if(!i or comp[i] != comp[i-1]){
			cur++;
			best[cur].insert(0);
			cool[comp[i]] = cur;
		}
	}
}

vector<int> countScans(vector<int> a,vector<int> x,vector<int> v){
	vector<int> answer;
	n = a.size();
	int q = x.size();
	REP(i,n)comp.pb(a[i]);
	REP(i,q)comp.pb(v[i]);
	compress();
	REP(i,n){
		a[i] = cool[a[i]];
		best[a[i]].insert(-(i+1));
	}
	REP(i,q){
		v[i] = cool[v[i]];
	}
	build(1,1,cur);
	REP(i,n){
		add(1,1,cur,a[i],cur,1);
	}	
	REP(i,q){
		int ind = x[i];
		int val = v[i];
		if(a[ind] != val){
			int upd = (a[ind] > val)?1:-1;
			add(1,1,cur,min(a[ind],val),max(a[ind],val)-1,upd);
			best[a[ind]].erase(-(ind+1));
			best[val].insert(-(ind+1));
			update(1,1,cur,a[ind]);
			update(1,1,cur,val);
			a[ind] = val;
		}
		answer.push_back(seg[1]);
	}
	return answer;
}
