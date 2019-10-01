/*input
5 5
1 2
2 3
3 4
4 5
1 5
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
int n,m;
vector<int> adj[N];
int ans[N];
int vis[N];
int vis1[N];
int found = 0;
int compli = 0;
set< pair<int,int> > ok;
set< pair<int,int> > pre;

void dfs(int u,int p = -1){

	if(vis[u])return;
	vis[u] = 1;
	for(int v:adj[u]){
		if(v == p)continue;
		else if(vis[v]){
			found = v;
			compli = u;
		}
		else dfs(v,u);
	}
}

void dfs1(int u){
	if(vis1[u])return;
	vis1[u] = 1;
	for(int v:adj[u]){
		if(vis1[v] or (v == compli and u == found))continue;
		ans[v] = u;
		dfs1(v);
	}
}

void solve(){
	cin >> n >> m;
	RE(i,m){
		int a,b;
		cin >> a >> b;
		pre.insert({a,b});
		adj[a].pb(b);
		adj[b].pb(a);
	}  
	RE(i,n){
		ans[i] = 0;
		vis[i] = 0;
		vis1[i] = 0;
	}
	bool wow = 1;
	RE(i,n){
		if(vis[i])continue;
		found = 0;
		compli = 0;
		dfs(i);
		if(!found)wow = 0;
		else{
			ans[found] = compli;
			dfs1(found);
		}
	}
	if(!wow){
		cout << "NIE";
		return;
	}
	cout << "TAK\n";
	RE(i,n){
		int x = i;
		int y = ans[i];
		if(x > y)swap(x,y);
		ok.insert({x,y});
		assert(pre.find({x,y}) != pre.end());
	}
	assert(ok.size() == n);
	RE(i,n){
		cout << ans[i] << "\n";
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