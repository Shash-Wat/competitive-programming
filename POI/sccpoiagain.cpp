/*input
6 7
1 2
1 3
2 4
3 4
4 5
5 6
6 5
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

const int INF = 1e9+1;
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

const int N = 5e5+1;
vector<int> adj[N];
vector<int> g[N];
int cur = 0;
int comp[N];
set<int> dag[N];
set<int> gad[N];
int n,m;
stack<int> s;
vector<int> ans;
bool vis[N];
int front[N];
int back[N];

void ini(){
	REP(i,N)vis[i] = 0;
}

void dfs1(int u){
	if(vis[u])return;
	vis[u] = 1;
	for(int v:adj[u]){
		dfs1(v);
	}
	s.push(u);
}

void dfs2(int u){
	if(vis[u])return;
	vis[u] = 1;
	comp[u] = cur;
	for(int v:g[u]){
		dfs2(v);
	}
}

void solve(){
  	cin >> n >> m;
  	REP(i,m){
  		int a,b;cin >> a >> b;
  		adj[a].pb(b);
  		g[b].pb(a);
  	}
  	ini();
  	RE(i,n){
  		if(!vis[i])dfs1(i);
  	}
  	ini();
  	while(!s.empty()){
  		int u = s.top();s.pop();
  		if(vis[u])continue;
  		cur++;
  		dfs2(u);
  	}
  	RE(i,n){
  		for(int v:adj[i]){
  			if(comp[i] == comp[v])continue;
  			dag[comp[i]].insert(comp[v]);
  			gad[comp[v]].insert(comp[i]);
  		}
  	}
  	ini();
  	int till = 1;
  	for(int i = cur;i > 0;i--){
  		for(int v:dag[i]){
  			if(!vis[v]){
  				vis[v] = 1;
  				till++;
  			}
  		}
  		front[i] = till;
  	}
  	ini();
  	till = 1;
  	for(int i = 1;i <= cur;i++){
  		for(int v:gad[i]){
  			if(!vis[v]){
  				vis[v] = 1;
  				till++;
  			}
  		}
  		back[i] = till;
  	}
  	RE(i,n){
  		int compno = comp[i];
  		bool one = (front[compno] == (cur-compno+1));
  		bool two = (back[compno] == (compno));
  		if(one and two)ans.pb(i);
  	}
  	cout << ans.size() << "\n";
  	print(ans);
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