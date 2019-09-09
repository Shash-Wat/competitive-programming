/*input
4
1 4
3 1 3 4
2 1 2
1 3
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

const int N = 5001;
vector<int> adj[N];
int n;
int dist[N];

int bfs(int s){
	RE(i,n)dist[i] = INF;
	dist[s] = 0;
	int sum = 0;
	queue<int> q;
	q.push(s);
	int vis = 0;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		vis++;
		for(int v:adj[u]){
			if(dist[v] == INF){
				dist[v] = dist[u]+1;
				q.push(v);
			}
		}
	}
	if(vis < n)return INF;
	RE(i,n)sum += dist[i];
	return sum;
}

void solve(){
  	cin >> n;
  	RE(i,n){
  		//adj[i].clear();
  		int k;cin >> k;
  		REP(j,k){
  			int x;cin >> x;
  			adj[x].pb(i);
  		}
  	}
  	int ans = INF;
  	RE(i,n)ans = min(ans,bfs(i));
  	assert(ans < INF);
  	cout << ans+n;
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