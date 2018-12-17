/*input
4 3
1 2
2 3 
3 4
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;

#define int long long 
#define double long double
#define f first
#define s second
#define mp make_pair
#define pb push_back
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

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

const int N = 1e6+1;

vector<pair<int,int> > ans[75];
int n,m;
vi adj[N];
bool done[N];
int in[N];
int tmp[N];
ordered_set avail;

signed main(){
  srand(time(0));
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  cin >> n >> m;
  while(m--){
    int a,b;cin >> a >> b;
    adj[b].pb(a);
    in[a]++;
    tmp[a]++;
  }
  double mx = 0;
  int ind = 0;
  REP(t,10){
  avail.clear();
  int two = 0;
  REP(i,n){
    done[i+1] = 0;
    in[i+1] = tmp[i+1];
    if(!in[i+1])avail.insert(i+1);
  }
  while(!avail.empty()){
      int how = avail.size();
      int rand1 = (rand()%(int)1e9)*(rand()%(int)1e9);rand1%= how;
      int u = *avail.find_by_order(rand1);
      avail.erase(u);
      bool ok = !(avail.empty());
      int v;
      if(ok){
        how = avail.size();
        int rand2 = (rand()%(int)1e9)*(rand()%(int)1e9);rand2%= how;
        v = *avail.find_by_order(rand2);
        avail.erase(v);
      }
      done[u] = 1;
      for(int p:adj[u]){
         in[p]--;
         if(!in[p] && !done[p])avail.insert(p);
      }
      if(ok){
        two++;
        done[v] = 1;
        for(int p:adj[v]){
         in[p]--;
         if(!in[p] && !done[p])avail.insert(p);
        }
      }
      //rat < two/size -> rat*size < two
      if(ok)ans[t].pb(mp(u,v));
      if(!ok)ans[t].pb(mp(u,u));
  }
  if(mx*ans[ind].size() < two){
    ind = t;
    if(ans[ind].size() != 0)mx = (double)two/ans[ind].size();
  }
  }
  cout << ans[ind].size() << endl;
  REP(i,ans[ind].size()){
    if(ans[ind][i].f == ans[ind][i].s){debug2(1,ans[ind][i].f);}
    else debug3(2,ans[ind][i].f,ans[ind][i].s);
  }
  return 0;
}