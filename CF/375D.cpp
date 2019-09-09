/*input
8 5
1 2 2 3 3 2 3 3
1 2
1 5
2 3
2 4
5 6
5 7
5 8
1 2
1 3
1 4
2 3
5 3
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long 
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

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

const int INF = 1e18+1;
const int MOD = 1e9+7;
const double PI = 3.14159265358979323846264338;

int raise(int a,int n,int m = MOD){
  if(n == 0)return 1;
  if(n == 1)return a;
  int x = 1;
    x *= raise(a,n/2,m);
    x %= m;
    x *= x;
    x %= m;
    if(n%2)x*= a;
    x %= m;
    return x;
}

int floor1(int n,int k){
    if(n%k == 0 || n >= 0)return n/k;
    return (n/k)-1;
}

int ceil1(int n,int k){
    return floor1(n+k-1,k);
}

const int N = 1e5+1;
int bit[N];
int c[N];
int freq[N];
vector<int> adj[N];
int n,m;
vector<pair<int,int> > queries[N];
int ans[N];
int sub[N];
int heavy[N];

void bitupd(int ind,int x){
	if(!ind)return;
	while(ind < N){
		bit[ind] += x;
		ind += ind&(-ind);
	}
}

int bitq(int ind){
	int res = 0;
	while(ind){
		res += bit[ind];
		ind -= ind&(-ind);
	}
	return res;
}

inline void updfreq(int col,int val){
	bitupd(freq[col],-1);
	freq[col] += val;
	bitupd(freq[col],1);
}

inline int greaters(int ind){
	return bitq(N)-bitq(ind-1);
}

void dfs0(int u,int p){
	sub[u] = 1;
	int mx = 0,mxval = 0;
	for(int v:adj[u]){
		if(v == p)continue;
		dfs0(v,u);
		sub[u] += sub[v];
		if(sub[v] > mxval){
			mxval = sub[v];
			mx = v;
		}
	}
	heavy[u] = mx;
}

void addsub(int u,int p,int val){
	updfreq(c[u],val);
	for(int v:adj[u]){
		if(v == p)continue;
		addsub(v,u,val);
	}
}

void dfs(int u,int p,bool keep){
	for(int v:adj[u]){
		if(v == p)continue;
		if(v == heavy[u])continue;
		dfs(v,u,0);
	}
	if(heavy[u]){
		dfs(heavy[u],u,1);
	}
	for(int v:adj[u]){
		if(v == p or v == heavy[u])continue;
		addsub(v,u,1);
	}
	updfreq(c[u],1);
  	for(auto q:queries[u]){
  		ans[q.s] = greaters(q.f);
  	}
  	if(!keep){
  		addsub(u,p,-1);
  	}
}

void solve(){
  	cin >> n >> m;
  	RE(i,n)cin >> c[i];
  	REP(i,n-1){
  		int a,b;cin >> a >> b;
  		adj[a].pb(b);
  		adj[b].pb(a);
  	}
  	REP(i,m){
  		int v,k;cin >> v >> k;
  		queries[v].pb({k,i});
  	}
  	dfs0(1,0);
  	dfs(1,0,0);
  	REP(i,m)cout << ans[i] << "\n";
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;
  //cin >> t;
  while(t--){
    solve();
  }
  return 0;
}