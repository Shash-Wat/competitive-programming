/*input
12 8 2
0 8 4
8 2 2
2 7 4
5 11 3
5 1 7
1 3 1
1 9 5
10 6 3
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
vector< pair<int,int> > adj[N];
int n,m,l;
vector< pair<int,int> >bests;//for each component takes best node
int comp[N];
bool vis[N];
int dist[N];
int flex[N];
bool visever[N];
int cur = 1;
vector<int> this_fuck;
bool keep = 0;

void getready(){
	REP(i,N){
		vis[i] = 0;
		dist[i] = 0;
		flex[i] = 0;
	}
}

void getreadyfor(){
	for(int i:this_fuck){
		vis[i] = 0;
		dist[i] = 0;
	}
}

int find_end(){
	int u = 0;
	for(int i:this_fuck){
		if(dist[i] > dist[u])u = i;
	}
	return u;
}

void get_center(){
	int nn = INF;
	int u = 0;
	for(int i:this_fuck){
		if(flex[i] < nn){
			nn = flex[i];
			u = i;
		}
	}
	bests.pb({flex[u],u});
}

void update_flex(){
	for(int i:this_fuck){
		flex[i] = max(flex[i],dist[i]);
	}
}

void dfs(int u){
	visever[u] = 1;
	vis[u] = 1;
	if(keep)this_fuck.pb(u);
	comp[u] = cur;
	for(int i = 0;i < adj[u].size();i++){
		int v = adj[u][i].f;
		if(vis[v])continue;
		dist[v] = dist[u] + adj[u][i].s;
		dfs(v);
	}
}

bool comp1(pair<int,int> a,pair<int,int> b){
	return a.f > b.f;
}

void solve(){
  	cin >> n >> m >> l;
  	REP(i,m){
  		int a,b,c;
  		cin >>a >> b >> c;
  		a++;b++;
  		adj[a].pb({b,c});
  		adj[b].pb({a,c});
  	}
  	getready();
  	RE(i,n){
  		if(!visever[i]){
  			keep = 1;
  			dfs(i);
  			keep = 0;
  			int one =find_end();
  			getreadyfor();
  			dfs(one);
  			update_flex();
  			int two = find_end();
  			getreadyfor();
  			dfs(two);
  			update_flex();
  			get_center();
  			this_fuck.clear();
  			cur++;
  		}
  	}
  	sort(bests.begin(),bests.end(),comp1);
  	int which = bests[0].s;

  	RE(i,(int)bests.size()-1){
  		adj[which].pb({bests[i].s,l});
  		adj[bests[i].s].pb({which,l});
  	}
  	getready();
  	keep = 1;
  	dfs(1);
 	int x = find_end();
 	getready();
 	dfs(x);
 	int ans = 0;
 	RE(i,n)ans = max(ans,dist[i]);
 	cout << ans;
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