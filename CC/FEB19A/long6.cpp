/*input
1
4 4 1
2 8 15 9
1 3
2 1
4 3
3 2
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long 
#define double long double
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define RE(i,n) for (int i = 1; i <= n; i++)
#define RED(i,n) for (int i = n; i > 0; i--)
#define REPS(i,n) for(int i = 1; (i*i) <= n; i++)
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define remax(a,b) a = max(a,b)
#define remin(a,b) a = min(a,b)
#define all(v) v.begin(),v.end()
#define pii pair<int,int>
#define mii map<int,int>
#define vi vector<int>
#define vvi vector<vi>
#define WL(t) while(t --)
#define gcd(a,b) __gcd((a),(b))
#define lcm(a,b) ((a)*(b))/gcd((a),(b))
#define print(arr) for (auto it = arr.begin(); it != arr.end(); ++it) cout << *it << " "; cout << endl;
#define debug(x) cout << x << endl;
#define debug2(x,y) cout << x << " " << y << endl;
#define debug3(x,y,z) cout << x << " " << y << " " << z << endl;
const int INF = 1e18+1;
const int MOD = 1e9+21;
const double PI = 3.14159265358979323846264338;

int fast_ex(int a,int n,int m){
  if(n == 0)return 1;
  if(n == 1)return a;
  int x = 1;
    x *= fast_ex(a,n/2,m);
    x %= m;
    x *= x;
    x %= m;
    if(n%2)x*= a;
    x %= m;
    return x;
}

const int N = 1e5+1;

int n,m,k;
vi adj1[N],adj2[N];
bool vis[N];
int comp[N];
stack<int> ord;
int timer = 0;
int cost[N][201];//cost we get if we leave first J of the i th scc
vi scc_wise[N];//sort to cal cost
int dp[N][201];//max by ending at SCC I with J left
int aux[N][201];
vi scc_adj[N];
int b[N];
set<pii> edges;

void ini(){
	 REP(i,N){
	 	adj1[i].clear();adj2[i].clear();
	 	vis[i] = 0;
	 	comp[i] = 0;
	 	scc_wise[i].clear();
	 	scc_adj[i].clear();
	 	REP(j,201){
	 		cost[i][j] = dp[i][j] = aux[i][j] = 0;
	 	}
	 }
	 timer = 0;
	 while(!ord.empty())ord.pop();
	 edges.clear();
}

void dfs1(int u){
	vis[u] = 1;
	for(auto v : adj1[u]){
		if(!vis[v])dfs1(v);
	}
	ord.push(u);
}

void dfs2(int u){
     comp[u] = timer;
     scc_wise[timer].pb(b[u]);
     for(auto v : adj2[u]){
     	if(!comp[v])dfs2(v);
     }
}

void solve(){
  ini();
  cin >> n >> m >> k;
  RE(i,n)cin >> b[i];
  REP(i,m){
  	int a,be;
  	cin >> a >> be;
  	adj1[a].pb(be);
  	adj2[be].pb(a);
  }
  RE(i,n){
  	if(!vis[i])dfs1(i);
  }
  //find components
  while(!ord.empty()){
  	int j = ord.top();
  	ord.pop();
  	if(!comp[j]){
  		timer++;
  		dfs2(j);
  	}
  }
  //calculate costs
  RE(i,timer)sort(scc_wise[i].begin(),scc_wise[i].end());
  RE(i,timer){
  	 int sz = scc_wise[i].size();
  	 cost[i][0] = scc_wise[i][0]*sz;
  	 RE(j,min(sz-1,k)){
  	 	cost[i][j] = scc_wise[i][j]*(sz-j);
  	 }
  }
  //make edges in scc dag
  RE(i,n){
  	for(int j:adj1[i]){
  		if(comp[i] != comp[j] && (edges.find({comp[i],comp[j]}) == edges.end())){
  			scc_adj[comp[j]].pb(comp[i]);
            edges.insert({comp[i],comp[j]});
  		}
  	}
  }
  // dp part
  RE(i,timer){
  	  int sz = scc_wise[i].size();
      for(int v:scc_adj[i]){
      	  for(int l = 0;l <= k;l++){aux[i][l] = max(aux[i][l],dp[v][l]);}
      }
      for(int left = 0;left < min(k+1,sz);left++){
         for(int j = 0;j <= k;j++){
         	if(j >= left)dp[i][j] = max(dp[i][j],aux[i][j-left]+cost[i][left]);
         }
      }
  }
  //getting ans
  int ans = -INF;
  RE(i,timer){
  	REP(j,k+1){
  		ans = max(ans,dp[i][j]);
  	}
  }
  ans %= MOD;
  cout << ans << endl;
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;cin >> t;
  WL(t)solve();
  return 0;
}