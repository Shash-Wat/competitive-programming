/*input
5 5 2
2 1
3 1
5 3
3 2
3 4
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

const int N = 3e5+1;
vector<int> adj[N];
int n,m,k;
int seg[4*N];
int comp = 0;
int comps[N];
int deg;
int vis[N];

#define child 2*node
#define mid (l+r)/2

int get(int node,int l,int r,int start,int end){
	if(end < l or start > r)return -1;
	if(!seg[node])return -1;
	if(l == r)return l;
	if(start <= l and r <= end){
		if(seg[child])return get(child,l,mid,start,end);
		else return get(child+1,mid+1,r,start,end);
	}
	int one = get(child,l,mid,start,end);
	if(one != -1)return one;
	return get(child+1,mid+1,r,start,end);
}

void upd(int node,int l,int r,int ind){
	seg[node]--;
	if(l == r){
		return;
	}
	if(ind <= mid)upd(child,l,mid,ind);
	else upd(child+1,mid+1,r,ind);
}

void build(int node,int l,int r){
	if(l == r){
		seg[node] = (l != 1);
		return;
	}
	build(child,l,mid);build(child+1,mid+1,r);
	seg[node] = seg[child]+seg[child+1];
}

void dfs(int u){
	if(vis[u])return;
	//cout << u << endl;
	vis[u] = 1;
	comps[u] = comp;
	for(int i = 0;i+1 < adj[u].size();i++){
		int one = adj[u][i];int two = adj[u][i+1];
		if(one+1 > two-1)continue;
		//cout << one+1 << " " << two-1 << endl;
		int v = get(1,1,n,one+1,two-1);

		if(v != -1){
			//cout << u << " " << v << endl;
			upd(1,1,n,v);
			dfs(v);
		}
	}
}

bool bad[N];

void solve(){
  	cin >> n >> m >> k;
  	deg = n-1;
  	RE(i,m){
  		int a,b;cin >> a >> b;
  		adj[a].pb(b);adj[b].pb(a);
  		if(min(a,b) == 1){
  			bad[max(a,b)] = 1;
  			deg--;
  		}
  	} 
  	build(1,1,n);
  	RE(i,n){
  		adj[i].pb(i);
  		adj[i].pb(1);
  		adj[i].pb(n+1);
  		sort(all(adj[i]));
  	}
  	for(int i = 2;i <= n;i++){
  		if(!vis[i]){comp++;dfs(i);}
  	}
  	bool flag = 1;
  	set<int> wow;
  	for(int i = 2;i <= n;i++){
  		if(bad[i])continue;
  		wow.insert(comps[i]);
  	}
  	//cout << comp << endl;
  	if(comp > k)flag = 0;
  	if(deg < k)flag = 0;
  	if(wow.size() != comp)flag = 0;
  	if(flag)cout << "possible";
  	else cout << "impossible";
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