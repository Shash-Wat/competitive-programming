/*input
3
N 2 1
T 3
N 2 1
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

const int MOD = 1e9+7;
const double PI = 3.14159265358979323846264338;

long long raise(int a,int n,int m = MOD){
  if(n == 0)return 1;
  if(n == 1)return a;
  long long x = 1;
  // (long long)
    x *= (long long)raise(a,n/2,m);
    x %= m;
    x *= (long long)x;
    x %= m;
    if(n%2)x*= (long long)a;
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

const int N = 2e6+1;
int deg[N];
set<int> adj[N];
int n;
vector< pair<int,int> > edges;
bool done[N];
int match[N];
set< pair<int,int> > q;
int comp = 0;

void dfs(int u){
    if(done[u])return;
    done[u] = 1;
    for(int v:adj[u]){
      dfs(v);
    }
}


void solve(){
    cin >> n;
    RE(i,n){
      char o;cin >> o;
      if(o == 'T'){
        int y;cin >> y;
        y+= n;
        done[i] = 1;
        done[y] = 1;
        match[i] = y;
      }
      else{
        int x,y;cin >> x >> y;
        x += n;
        y += n;
        edges.pb({i,x});
        edges.pb({i,y});
      }
    }
    REP(i,edges.size()){
        int a = edges[i].f;
        int b = edges[i].s;
        if(done[a] or done[b])continue;
        deg[a]++;
        deg[b]++;
        adj[a].insert(b);
        adj[b].insert(a);
    }
    for(int i = n+1;i <= 2*n;i++){
      if(done[i])continue;
      //cout << i << " " << deg[i] << endl;
      q.insert({deg[i],i});
    }
    bool phase = 0;
    while(q.size()){
      int u = q.begin()->s;
      int sz = q.begin()->f;
      q.erase(*q.begin());
      if(sz == 2){
        phase = 1;
        break;
      }
      if(sz == 0){
        cout << "NIE\n";
        cout << 0 << endl;
        return;
      }
      int v = *adj[u].begin();
      done[u] = done[v] = 1;
      match[v] = u;

      adj[u].erase(v);
      adj[v].erase(u);

      for(int y:adj[v]){
        q.erase({deg[y],y});
        deg[y]--;
        adj[y].erase(v);
        q.insert({deg[y],y});
      }
      for(int y:adj[u]){
        q.erase({deg[y],y});
        deg[y]--;
        adj[y].erase(u);
        q.insert({deg[y],y});
      }
    }
    if(!phase){
      cout << "TAK\n";
      RE(i,n)cout<< match[i]-n << "\n";
      return;
    }
    RE(i,2*n){
      if(!done[i]){
        dfs(i);
        comp++;
      }
    }
    cout << "NIE\n";
    cout << raise(2,comp,MOD);
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