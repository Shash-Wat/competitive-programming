/*input
6
hhardh
3 2 9 11 7 1
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

int n;
int a[100001];
int dp[100001][2][2][2][2];
bool vis[100001][2][2][2][2];
string s;

void rec(int i,int one,int two,int three,int four,int cost){
	//cout << i << ": " << one << endl;
	//if(i == n)cout << i << " " << one << two << three << four << ": " << cost << endl;
	if(i == n)return;
	//cout << i << " " << one << two << three << four << ": " << cost << endl;
	if(vis[i][one][two][three][four])return;
	vis[i][one][two][three][four] = 1;
	if(s[i] == 'h'){
		dp[i+1][1][two][three][four] = min(dp[i+1][1][two][three][four],cost);
       dp[i+1][one][two][three][four] = min(dp[i+1][1][two][three][four],cost+a[i]);
       rec(i+1,1,two,three,four,cost);     
       rec(i+1,one,two,three,four,cost+a[i]);
	}
	else if(s[i] == 'a'){
		dp[i+1][one][two|one][three][four] = min(dp[i+1][one][two|one][three][four],cost);
       dp[i+1][one][two][three][four] = min(dp[i+1][one][two][three][four],cost+a[i]);
       rec(i+1,one,two,three,four,cost);     
       rec(i+1,one,one|two,three,four,cost+a[i]);
	}
	else if(s[i] == 'r'){
		dp[i+1][one][two][three|two][four] = min(dp[i+1][one][two][three|two][four],cost);
       dp[i+1][one][two][three][four] = min(dp[i+1][one][two][three][four],cost+a[i]);
       rec(i+1,one,two,three,four,cost);     
       rec(i+1,one,two,two|three,four,cost+a[i]);
	}
	else if(s[i] == 'd'){
	  dp[i+1][one][two][three][four|three] = min(dp[i+1][one][two][three][four|three],cost);
       dp[i+1][one][two][three][three] = min(dp[i+1][one][two][three][four],cost+a[i]);
       rec(i+1,one,two,three,three|four,cost);     
       rec(i+1,one,two,three,four,cost+a[i]);
	}
	else {
		dp[i+1][one][two][three][four] = min(dp[i+1][one][two][three][four],cost);
		rec(i+1,one,two,three,four,cost);
	}
}

string h = "hard";

void solve(){
	 REP(i,100001){
	    REP(j,2){
	    	REP(k,2){
	    		REP(l,2){
	    			REP(w,2)dp[i][j][k][l][w] = INF;
	    		}
	    	}
	    }
	 }
     cin >> n >> s;
     REP(i,n)cin >> a[i];
     dp[0][0][0][0][0] = 0;
/*     REP(i,n){
     	REP(j,4){
     		dp[i+1][j+(s[i] == h[j])] = min(dp[i+1][j+(s[i] ==h[j])],dp[i][j]);
     		dp[i+1][j] = min(dp[i+1][j],dp[i][j]+a[i]);
     		//cout << dp[i][j] << " ";
        }
        //cout << endl;
     }*/
     rec(0,0,0,0,0,0);
     int ans = INF;
	    REP(j,2){
	    	REP(k,2){
	    		REP(l,2){
	    			REP(w,1)ans = min(ans,dp[n-1][j][k][l][w]);
	    		}
	    	}
	    }
	 
     cout << ans;
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