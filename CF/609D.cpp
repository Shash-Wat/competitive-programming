/*input
4 3 1 1000000000
900000 910000 940000 990000
990000 999000 999900 999990
1 87654
2 76543
1 65432
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

int n,m,k,s;
const int N = 2e6+1;
int cheap[N][2];
int cost[N][2];
int rate[N][2];
vector<pii> items;//cost,index

bool check(int x,bool print = 0){
	 items.clear();
     RE(i,m){
     	int d1 = cheap[x][0];
     	int d2 = cheap[x][1];
     	int cj = 0;
     	if(cost[i][0] == INF)cj = cost[i][1]*rate[d2][1];
     	if(cost[i][1] == INF)cj = cost[i][0]*rate[d1][0];
     	items.pb({cj,i});
     }
     int inc = 0;
     REP(i,k){
     	inc += items[i].f;
     }
     if(print){
     	cout << x << endl;
     	REP(i,k){
     		int ind = items[i].s;
     		int bot;
     		if(cost[ind][0] == INF)bot = cheap[x][1];
     		if(cost[ind][1] == INF)bot = cheap[x][0];
            debug2(ind,bot);
     	}
     }
     return(inc <= s);
}

void solve(){
     cin >> n >> m >> k >> s;
     cheap[0][0] = cheap[0][1] = 1;
     RE(i,n){
     	cin >> rate[i][0];
     	int currate = cheap[i-1][0];
     	currate = rate[currate][0];
     	if(currate > rate[i][0])cheap[i][0] = i;
        else cheap[i][0] = cheap[i-1][0];
     }
     RE(i,n){
     	cin >> rate[i][1];
     	int currate = cheap[i-1][1];
     	currate = rate[currate][1];
     	if(currate > rate[i][1])cheap[i][1] = i;
        else cheap[i][1] = cheap[i-1][1];
     }
     RE(i,m){
     	int t1,c;cin >> t1 >> c;
     	t1--;
     	cost[i][0] = cost[i][1] = INF;
     	cost[i][t1] = c;
     }
     int lo = 1;
     int hi = n;
     while(lo < hi){
     	int mid = (lo+hi)/2;
     	if(check(mid))hi = mid;
     	else lo = mid+1;
     }
     if(!check(lo)){
     	cout << -1;
     	return;
     }
     check(lo,1);
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