/*input
7 7
1 2
2 3
3 4
4 5
5 6
6 7
7 1
*/
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

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

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

const int N = 5e4+1;
vector<int> adj[N];
vector<int> g[N];
int n,m;
stack<int> st;
bool vis[N];
int comp[N];
int sub[N];
int in[N];
int sz = 0;
int cur = 1;
set<int> scc_adj[N];

void ini(){
	REP(i,N)vis[i] = 0;
}

void ini_big(){
	while(st.size())st.pop();
	REP(i,N){
		comp[i] = 0;
		sub[i] = 0;
		in[i] = 0;
		g[i].clear();
		adj[i].clear();
		scc_adj[i].clear();
	}
}

void dfs0(int u){
	if(vis[u])return;
	vis[u] = 1;
	
	for(int v:adj[u]){
		dfs0(v);
	}
	st.push(u);
}

void dfs1(int u){
	if(vis[u])return;
	sz++;
	vis[u] = 1;comp[u] = cur;
	for(int v:g[u]){
		dfs1(v);
	}
}

void dfs2(int u,int p){
	if(vis[u])return;
	vis[u] = 1;
	for(int v:scc_adj[u]){
		if(v == p)continue;
		dfs2(v,u);
		sub[u] += sub[v];
	}
}

void solve(){
	ini_big();
  	cin >> n >> m;
  	RE(i,m){
  		int a,b;cin >> a >> b;
  		adj[a].pb(b);
  		g[b].pb(a);
  	}
  	ini();
  	RE(i,n){
  		if(!vis[i])dfs0(i);
  	}
  	ini();
  	while(!st.empty()){
  		if(!vis[st.top()]){
  			dfs1(st.top());
  			sub[cur] = sz;
  			cur++;
  			sz = 0;
  		}
  		st.pop();
  	}
  	cur--;
  	RE(i,n){
  		for(int v:adj[i]){
  			if(comp[i] != comp[v]){
  				scc_adj[comp[i]].insert(comp[v]);
  				in[comp[v]] = 1;
  			}
  		}
  	}
  	ini();
  	vector<int> roots;
  	RE(i,cur){
  		if(!in[i])roots.pb(i);
  	}
  	for(int root:roots){
  		dfs2(root,0);
  	}
  	RE(i,n){
  		cout << sub[comp[i]]-1 << "\n";
  	}
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