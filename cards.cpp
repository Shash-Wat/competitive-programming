/*input
4
2 5
3 4
6 3
2 7
2
3 4
1 3
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

const int INF = 1e8+1;
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

const int N = 2e5+1;
int n,q;
int seg[4*N][2];// value if start from ith
int a[N][2];

#define child 2*node
#define mid (l+r)/2

void build(int node,int l,int r){
    if(l == r){
      seg[node][0] = a[l][0];
      seg[node][1] = a[l][1];
      return;
    }
    build(child,l,mid);build(child+1,mid+1,r);
    seg[node][0] = INF;
    seg[node][1] = INF;
    REP(i,2){
      if(seg[child][i] <= a[mid+1][0])seg[node][i] = seg[child+1][0];
      if(seg[child][i] <= a[mid+1][1])seg[node][i] = min(seg[node][i],seg[child+1][1]);
    }
}

void update(int node,int l,int r,int ind){

    if(l == r){
      seg[node][0] = a[l][0];
      seg[node][1] = a[l][1];
    //  cout << "@[ " << l << " " << r << "]\n";
      //cout << seg[node][0] << " " << seg[node][1] << endl;
      return;
    }
    if(ind <= mid)update(child,l,mid,ind);
    else update(child+1,mid+1,r,ind);
    seg[node][0] = INF;
    seg[node][1] = INF;
    REP(i,2){
      if(seg[child][i] <= a[mid+1][0])seg[node][i] = seg[child+1][0];
      if(seg[child][i] <= a[mid+1][1])seg[node][i] = min(seg[node][i],seg[child+1][1]);
    }
    //cout << "@[ " << l << " " << r << "]\n";
    //cout << seg[node][0] << " " << seg[node][1] << endl;
}

void solve(){
    cin >> n;
    RE(i,n)cin >> a[i][0] >> a[i][1];
    cin >> q;
    build(1,1,n);
    while(q--){
      int x,y;cin >> x >> y;
      swap(a[x][0],a[y][0]);
      swap(a[x][1],a[y][1]);
      update(1,1,n,x);update(1,1,n,y);
      (seg[1][0] < INF or seg[1][1] < INF)?cout << "TAK\n":cout << "NIE\n";
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