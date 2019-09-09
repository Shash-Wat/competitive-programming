/*input
4 3 1
6 1 2 4
1 3
*/
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O2")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<time.h>
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define double long double
#define f first
#define s second
#define mp make_pair
#define pb push_back

#define RE(i,n) for (int i = 1; i <= n; i++)
#define RED(i,n) for (int i = n; i > 0; i--)
#define REPS(i,n) for(int i = 1; (i*i) <= n; i++)
#define REP(i,n) for (int i = 0; i < (int)n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)

#define all(v) v.begin(),v.end()
#define pii pair<int,int>
#define vi vector<int>
#define vvi vector<vi>
#define print(arr) for (auto it = arr.begin(); it != arr.end(); ++it) cout << *it << " "; cout << endl;
#define debug(x) cout << x << endl;
#define debug2(x,y) cout << x << " " << y << endl;
#define debug3(x,y,z) cout << x << " " << y << " " << z << endl;


#define mid (l+r)/2
#define child 2*node

const int N = 1e6+1;
multiset<int> seg[4*N];
int nseg[4*N];
int segm[4*N];
vector<pair<int,int> > qs;
int a[N];
//int ans[4*N];
bool change[N];
int n,k,q;
multiset<int> answers;

void build(int node,int l,int r){
	if(l == r){
		segm[node] = a[l];
		return;
	}
	build(child,l,mid);
	build(child+1,mid+1,r);
	segm[node] = max(segm[child],segm[child+1]);
	nseg[node] = max(nseg[child],nseg[child+1]);
}


void addinans(int oldval,int val){
	auto it = answers.find(-oldval);
	if(it != answers.end()){
		if(oldval == val)return;
		answers.erase(it);
	}
	answers.insert(-val);
}

void addinnor(int oldval,int val,int node){
	auto it = seg[node].find(-oldval);
	if(it != seg[node].end()){
		if(oldval == val)return;
		seg[node].erase(it);
	}
	seg[node].insert(-val);
}

void lazyupd(int node,int l,int r,int start,int end,int val){
	if(start > r or end < l)return;
	//cout << l << " " << r << " " << start << " " << end <<  endl;
	if(start <= l and end >= r){
		if(nseg[node] > val)return;
		nseg[node] = val;
		return;
	}	
	lazyupd(child,l,mid,start,end,val);
	lazyupd(child+1,mid+1,r,start,end,val);
}


void add(int node,int l,int r,int start,int end,int ind,int val){
	if(start > r or end < l)return;
	if(l >= start and end >= r){
		int oldans = -*seg[node].begin();
		addinnor(a[ind],val,node);
		int ansofthis = -*seg[node].begin();
		ansofthis = max(ansofthis,nseg[node]);
		addinans(oldans+segm[node],ansofthis+segm[node]);
		return;
	}
	add(child,l,mid,start,end,ind,val);
	add(child+1,mid+1,r,start,end,ind,val);
}

void update(int node,int l,int r,int ind,int val){
	if(ind < l or ind > r)return;
	
	int prev = segm[node];
	if(l != r){
		update(child,l,mid,ind,val);
		update(child+1,mid+1,r,ind,val);
		segm[node] = max(segm[child],segm[child+1]);
	}
	else{
		segm[node] = val;
	}
	
	int oldans = max(-*seg[node].begin(),nseg[node]);
	addinans(oldans+prev,oldans+segm[node]);
	return;
}


void solve(){
//	auto start = chrono::steady_clock::now();
  	scanf("%d",&n);
  	scanf("%d",&k);
  	scanf("%d",&q);
  	RE(i,n){
  		change[i] = 0;
  		scanf("%d",&a[i]);
  	}
  	RE(ind,q){
  		int i,val;
  		scanf("%d",&i);scanf("%d",&val);
  		qs.pb({i,val});
  		change[i] = 1;
  	}
  	build(1,1,n);
  	RE(i,n){
  		int l1 = max(1,i-k+1);
  		int r1 = i-1;
  		int r2 = min(i+k-1,n);
  		int l2 = i+1;
  		if(!change[i]){
  			if(l1 <= r1)lazyupd(1,1,n,l1,r1,a[i]);
  			if(l2 <= r2)lazyupd(1,1,n,l2,r2,a[i]);		
  		}
  		else{
  			//if(l1 <= r1)add(1,1,n,l1,r1,i,a[i]);
  			if(l2 <= r2)add(1,1,n,l2,r2,i,a[i]);
  		}
  	}
 	RE(node,4*n){
 		if(!nseg[node])continue;
 		int oldans = -*seg[node].begin();
		int ansofthis = oldans;
		ansofthis = max(ansofthis,nseg[node]);
		addinans(oldans+segm[node],ansofthis+segm[node]);
		//return;
 	}

  	printf("%d\n",-*answers.begin());
  	REP(ind,q){
  		int i = qs[ind].f;
  		int val = qs[ind].s;
  		int l1 = max(1,i-k+1);
  		int r1 = i-1;
  		int r2 = min(i+k-1,n);
  		int l2 = i+1;
  	//	if(l1 <= r1)add(1,1,n,l1,r1,i,val);
  		if(l2 <= r2)add(1,1,n,l2,r2,i,val);
  		a[i] = val;
  		update(1,1,n,i,val);
  		
  		printf("%d\n",-*answers.begin());
  	}
//	auto end = chrono::steady_clock::now();
//	auto diff = end - start;
	//cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;

}

signed main(){
  //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen("inp.txt","r",stdin);//freopen(".out","w",stdout);
  int t = 1;
  //cin >> t;
  while(t--){
    solve();
  }
  return 0;
}