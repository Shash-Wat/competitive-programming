/*input
4
1 2
1 3
1 2
1 2
1 3
1 2
2 5
1 2
3 1
1 4
5 1
1 6
2 15
1 2
1 3
1 4
1 5
1 6
2 3
2 4
2 5
2 6
3 4
3 5
3 6
4 5
4 6
5 6
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
vector<int> matching;
vector<int> leaves;
vector<pair<int,int> > adj[N];
bool vis[N];
bool paired[N];
int n,m;

void ini(){
	leaves.clear();
	matching.clear();
	REP(i,n+1){
		vis[i] = 0;
		paired[i] = 0;
		adj[i].clear();
	}
}

void dfs(int u){
	if(vis[u])return;
	vis[u] = 1;
	if(!paired[u]){
		for(auto v:adj[u]){
			if(vis[v.f])continue;
			paired[u] = 1;
			paired[v.f] = 1;
			matching.pb(v.s);
			break;
		}
	}
	bool leaf = 1;
	for(auto v:adj[u]){
		if(!vis[v.f]){
			dfs(v.f);
			leaf = 0;
		}
	}
	if(leaf)leaves.pb(u);
}

void solve(){
	cin >> n >> m;
	n = 3*n;
  	ini();
  	RE(i,m){
  		int a,b;cin >> a >> b;
  		adj[a].pb({b,i});
  		adj[b].pb({a,i});
  	}
  	RE(i,n){
  		if(!vis[i])dfs(i);
  	}
  	if(leaves.size() >= n/3){
  		cout << "IndSet\n";
  		for(int i = 0;i < n/3;i++)cout << leaves[i] << " ";
  		cout << "\n";
  	}
  	else{
  		cout << "Matching\n";
  		for(int i = 0;i < n/3;i++)cout << matching[i] << " ";
  		cout << "\n";
  	}
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;
  cin >> t;
  while(t--){
    solve();
  }
  return 0;
}