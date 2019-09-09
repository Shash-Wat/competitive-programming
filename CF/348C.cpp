/*input
5 3 5
5 -5 5 1 -4
2 1 2
4 2 1 4 5
2 2 5
? 2
+ 3 4
? 1
+ 2 1
? 2
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long
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
const int T = 315;
int n,m,q;
vector<int> special;
vector<int> inds[N];
int nice[N];
vector<int> adj[N];
ll updsum[T];
ll comeback[T];
ll a[N];
int intersect[T+10][N];

void solve(){
  REP(i,N){
    nice[i] = -1;
    REP(j,T+10){
      intersect[j][i] = 0;
       comeback[j] = 0;
    updsum[j] = 0;
    }
  }
    cin >> n >> m >> q;
    RE(i,n)cin >> a[i];
    REP(i,m){
      int k;cin >> k;
      if(k >= T)special.pb(i);
      REP(j,k){
        int x;cin >> x;
        adj[x].pb(i);
        inds[i].pb(x);
      }
    }
    REP(i,special.size()){
      nice[special[i]] = i;
      REP(j,inds[special[i]].size()){
        int now = inds[special[i]][j];
        comeback[i] += (ll)a[now];
        for(int v:adj[now]){
          if(v == special[i])continue;
          intersect[i][v]++;
        }
      }
    }
    while(q--){
      char o;cin >> o;
      if(o == '+'){
        int ind;cin >> ind;ind--;
        int y;cin >> y;
        if(nice[ind] != -1){
         // cout << "here" << endl;
          updsum[nice[ind]] += (ll)y;
        }
        else{
          //cout << "here" << endl;
          REP(i,inds[ind].size()){
            //cout << inds[ind][i] << " ";
            a[inds[ind][i]] += (ll)y;
          }
          //cout << endl;
        }
        // going through all special ones now
        REP(i,special.size()){
          if(special[i] == ind)continue;
          comeback[i] += (ll)y*intersect[i][ind];
        }
      }
      else{
        int ind;cin >> ind;ind--;
        ll res = 0;
        if(nice[ind] == -1){
          REP(i,special.size()){
            res += (ll)intersect[i][ind]*updsum[i];
          }
          REP(i,inds[ind].size()){
            res += a[inds[ind][i]];
          }
          cout << res << "\n";
        }
        else{
          cout << (ll)updsum[nice[ind]]*inds[ind].size()+comeback[nice[ind]] << "\n";
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