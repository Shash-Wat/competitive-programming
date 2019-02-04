/*input
5 6 2
1 2 3 4 5
1 2 5
1 3 3
2 4 3
3 4 5
4 5 2
3 5 7
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
const int MOD = 1e9+7;
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

const int N = 1e4+1;

int n,m,T;
int val[N];
vector<pair<int,int> > adj[N];
vector<int> treadj[N];
int sub[N];
priority_queue<pii> pq;
bool vis[N];
int dist[N];

void dijkstra(){
     dist[1] = 0;
     pq.push({0,1});
     while(!pq.empty()){
     	int u = pq.top().s;
     	int dis = -pq.top().f;
     	pq.pop();
     	if(vis[u] || dist[u] < dis)continue;
     	vis[u] = 1;
     	for(int i = 0;i < adj[u].size();i++){
     		int v = adj[u][i].f;
     		int w = adj[u][i].s;
     		if(dist[u]+w < dist[v]){
     			dist[v] = dist[u]+w;
     			pq.push({-dist[v],v});
     		}
     	}
     }
}

void make_tree(){
	 for(int u = 2;u <= n;u++){
	 	 int minn = INF;
	 	 for(int i = 0;i < adj[u].size();i++){
	 	 	int v = adj[u][i].f;
	 	 	int w = adj[u][i].s;
	 	 	if(dist[u] == (dist[v]+w))minn = min(minn,v);
	 	 }
	 	 treadj[minn].pb(u);
	 }
}

void dfs(int u){
	 sub[u] = val[u];
	 for(int v:treadj[u]){
	 	dfs(v);
	 	sub[u] += sub[v];
	 }
}

void solve(){
     cin >> n >> m >> T;
     RE(i,n){vis[i] = 0;dist[i] = INF;cin >> val[i];}
     RE(i,m){
     	int a,b,c;cin >> a >> b >> c;
     	adj[a].pb({b,c});
     	adj[b].pb({a,c});
     }     
     dijkstra();
     make_tree();
     dfs(1);
     int maxlose = 0;
     for(int i = 2;i <= n;i++){
     	 maxlose = max(maxlose,(dist[i]-T)*sub[i]);
     }
     cout << maxlose;
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  freopen("shortcut.in","r",stdin);freopen("shortcut.out","w",stdout);
  int t = 1;//cin >> t;
  WL(t)solve();
  return 0;
}
