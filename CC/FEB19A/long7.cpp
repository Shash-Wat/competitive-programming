/*input
8
1 2 3 6 6 4 5 2
1 2
2 3
2 5
2 6
4 5
5 7
5 8
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

const int N = 1e5+1;
const int lg = 20;

int n;
int k[N];
int dist[N];
int pre[N][lg+1];
int par[N];//parent in the centroid tree
set<int> adj[N];
int ans[N];
int sub[N];
vi belowpar[N];// FUCK THIS SHIT I AM DUMB
vi below[N];//distance to nodes in its subtree

//ORIGINAL TREE

void ini(){
     REP(i,N){
         dist[i] = 0;
         REP(j,lg+1){
           pre[i][j] = 0;
         }
         par[i] = 0;
         adj[i].clear();
     }
}

void dfs(int u,int p){
  pre[u][0] = p;
  FOR(i,1,lg){
    pre[u][i] = pre[pre[u][i-1]][i-1];
    }
  for(auto it = adj[u].begin();it != adj[u].end();it++){
    int v = *it;
    if(v == p)continue;
    dist[v] = dist[u]+1;
    dfs(v,u);
  }
}

int lca(int u,int v){
    if(dist[u] > dist[v])swap(u,v);
    //bring v to u's level
    FORD(i,lg-1,0){
      if(dist[v] >= dist[u]+ (1<<i) )v = pre[v][i];
    }
    //lift both together 
    FORD(j,lg-1,0){
    //  cout << u << " " << v << endl;
      if(pre[v][j] != pre[u][j]){
        v = pre[v][j];
        u = pre[u][j];
      }
    }
    if(u != v){u = pre[u][0];v = pre[v][0];}
    return u;
}

int dis(int u,int v){
    return ((dist[u]+dist[v])-2*dist[lca(u,v)]);
}

// MAKING CENTROID TREE

int sz;

void dfs1(int u,int p){
    sub[u] = 1;
    sz++;
    for(auto it = adj[u].begin();it != adj[u].end();it++){
       int v = *it;
       if(v == p)continue;
       dfs1(v,u);
       sub[u] += sub[v];
    }
}

int dfs2(int u,int p){
    for(auto it = adj[u].begin();it != adj[u].end();it++){
       int v = *it;
       if(v == p)continue;
       if(sub[v] > sz/2)return dfs2(v,u);
    }
    return u;
}

void decompose(int u,int p){
    sz = 0;
    dfs1(u,u);
    int centroid = dfs2(u,u);
    if(!p)p = centroid;
    par[centroid] = p;
    for(auto it = adj[centroid].begin();it != adj[centroid].end();it++){
      int v = *it;
      adj[v].erase(centroid);
      decompose(v,centroid);
    }
    adj[centroid].clear();
}

//PREPROCESSING 

void add(int u){
     int v = u;
     while(1){
         below[v].pb(dis(u,v));
         if(par[v] == v)break;
         belowpar[v].pb(dis(u,par[v]));
         v = par[v];
     }
}

int get1(int u,int x){
    int lo = 0;
     int haha = belowpar[u].size();
     int hi = haha-1;
     if(belowpar[u][0] > x)return haha;
     while(lo < hi){
       int mid = (lo+hi+1)/2;
       if(belowpar[u][mid] <= x)lo = mid;
       if(belowpar[u][mid] > x)hi = mid-1;
     }
     return (haha-(lo+1));
}

int get(int u,int x){
     // number of values smaller than or equal to x
     int lo = 0;
     int haha = below[u].size();
     int hi = haha-1;
     if(below[u][0] > x)return haha;
     while(lo < hi){
       int mid = (lo+hi+1)/2;
       if(below[u][mid] <= x)lo = mid;
       if(below[u][mid] > x)hi = mid-1;
     }
     return (haha-(lo+1));
}

bool check(int u,int val){
     int v = u;
     int prev = u;
     int res = 0;
     while(1){
        int first = dis(u,v);
        //dist(u,v)+dist(v,some node) > val -> dist(v,some node) > val-dist(u,v)
        int req = val-first;
        res += get(v,req);
        if(prev != v)res -= get1(prev,req);
        if(par[v] == v)break;
        prev = v;
        v = par[v];
     }
     return (res >= k[u]);
}

void solve(){
     ini();
     cin >> n;
     RE(i,n)cin >> k[i];
     RE(i,n-1){
      int a,b;cin >> a >> b;
      adj[a].insert(b);
      adj[b].insert(a);
     }
     dfs(1,1);
     decompose(1,0);
     RE(i,n)add(i);
     RE(i,n){
      sort(all(below[i]));
      sort(all(belowpar[i]));
     }
     RE(i,n){
       int lo = 0;
       int hi = n-1;
       while(lo < hi){
         int mid = (lo+hi+1)/2;
         if(check(i,mid))lo = mid;
         else hi = mid-1;
       }
       ans[i] = lo;
     }
     RE(i,n)cout << ans[i] << " ";
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;//cin >> t;
  WL(t)solve();
  return 0;
}