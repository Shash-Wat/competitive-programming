/*input
3 5 1
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

int n,m,X;
map< pair<int,pair<int,int> >,bool > vis;
map< pair<int,pair<int,int> >,int > val;


/*int rec(int i,int open,int tot){
	if(tot > n)return 0;
	if(i == (m+1))return (!open and (tot == n));
	if(vis[{i,{open,tot}}])return val[{i,{open,tot}}];
	int res = 0;
	if(i == x){
		res += rec(i+1,open+1,tot+1);//just open
		res %= MOD;
		res += rec(i+1,open,tot+1);//close farthest and then open
		res %= MOD;
	}
	else {
		res += rec(i+1,open+1,tot+1);// just open
		res %= MOD;
	    if(open > 0)res += rec(i+1,open-1,tot);// just close farthest one
	    res %= MOD;
	    res += rec(i+1,open,tot);// do nothing
	    res %= MOD;
	    res += rec(i+1,open,tot+1);//close farthest and open new
	    res %= MOD;
	}
	vis[{i,{open,tot}}] = 1;
	val[{i,{open,tot}}] = res;
	return res;
}*/

void solve(){
  	cin >> n >> m >> X;
  	int ans = 1;
  	if(n > m){
  		cout << 0 << endl;
  		return;
  	}
  	RE(i,n){
  		ans *= i;
  		ans %= MOD;
  	}
  	//cout << (rec(1,0,0)*ans)%MOD;
  	int dp[m+2][n+1][n+1];
  	REP(i,m+2){
  		REP(j,n+1){
  			REP(k,n+1)dp[i][j][k] = 0;
  		}
  	}
  	dp[1][0][0] =1;
  	for(int i = 1;i <= m;i++){
  		for(int open = 0;open <= n;open++){
  			for(int tot = open;tot <= n;tot++){
  				for(int x = 0;x < 2;x++){
  					for(int y = -1;y < 1;y++){
  						if(open+x+y < 0)continue;
  						if(tot+x > n)continue;
  						if(i == X and !x)continue;
  						dp[i+1][open+x+y][tot+x] += dp[i][open][tot];
  						dp[i+1][open+x+y][tot+x] %= MOD;
  					}
  				}
  			}
  		}
  	}
  	cout << (ans*dp[m+1][0][n])%MOD;
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