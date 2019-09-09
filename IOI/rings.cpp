/*input
6 8
0 1
1 2
2 3
3 4
4 5
5 0
5 3
-1
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

const int N = 1e6+1;
int deg[N];
bool vis[N];
vector<int> adj[N];
int n,q;
int edges = 0;
int comp = 0;
vector<int> three;
bool flag = 0;
int wow = 0;
int mxdeg = 0;
int scmax = 0;
int u;

void updatesdeg(int y,int hehe){
	if(y > mxdeg){
		scmax = mxdeg;
		mxdeg = y;
		wow = hehe;
	}
	else if(y > scmax){
		scmax = y;
	}

}

void dfs(int x,int p){
	if(vis[x]){
		flag = 1;
		return;
	}
	vis[x] = 1;
	for(int v:adj[x]){
		if(v == p or v == u)continue;
		dfs(v,x);
	}
}

void ndfs(int x,int p){
	if(vis[x]){
		return;
	}
	vis[x] = 1;
	edges += deg[x];
	comp++;
	for(int v:adj[x]){
		if(v == p)continue;
		ndfs(v,x);
	}
}

void precheck(){
	for(int v:adj[u]){
		deg[v]--;
	}
}

void postcheck(){
	for(int v:adj[u]){
		deg[v]++;
	}
}

bool check(){
	flag = 0;
	bool fuck = 0;
	for(int i = 0;i < n;i++){
		vis[i] = 0;
		if(i == u)continue;
		if(deg[i] > 2){
			fuck = 1;
		}
	}
	
	if(fuck){
		//cout << u << endl;
		return 0;
	}
	for(int i = 0;i < n;i++){
		if(vis[i] or i == u)continue;
		dfs(i,-1);
	}
	return !flag;
}

void solve(){
  	cin >> n >> q;
  	REP(i,n)deg[i] = 0;
  	while(q--){
  		int x;cin >> x;
  		if(x == -1){
  			int sz =0;
  			if(mxdeg < 3){
  				REP(i,n){
  					vis[i] = 0;
  				}
  				int cnt = 0;
  				int found = 0;
  				REP(i,n){
  					if(vis[i])continue;
  					edges = 0;
  					comp = 0;
  					ndfs(i,-1);
  					edges /= 2;
  					if(comp-1 != edges){
  						cnt++;
  						found = comp;
  					}
  					edges = 0;
  					comp = 0;
  				}
  				if(cnt == 1){
  					cout << found << endl;
  				}
  				else if(cnt == 0){
  					cout << n << endl;
  				}
  				else cout << 0;
  				continue;
  			}
  			else if(mxdeg > 3){
  				//cout << "here haha\n";
  				u = wow;
  				precheck();
  				cout << check() << endl;
  				postcheck();
  				continue;
  			}
  			else{
  				set<int> chex;
  				for(int i = 0;i < three.size();i++){
  					chex.insert(three[i]);
  					for(int v:adj[three[i]]){
  						chex.insert(v);
  					}
  				}
  					int sz = 0;
  					for(auto it:chex){
  						u = it;
  						precheck();
  						sz += check();
  						postcheck();
  					}
  					cout << sz << endl;
  			}
  		}
  		else{
  			int y;cin >> y;
  			adj[x].pb(y);
  			adj[y].pb(x);
  			deg[x]++;
  			deg[y]++;
  			updatesdeg(deg[x],x);
  			updatesdeg(deg[y],y);
  			if(deg[x] == 3){
  				if(three.size())continue;
  				three.pb(x);
  			}
  			if(deg[y] == 3){
  				if(three.size())continue;
  				three.pb(y);
  			}
  		}
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