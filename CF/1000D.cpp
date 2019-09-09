/*input
4
1 2 2 1
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
const int MOD = 998244353;
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
    if(x < 0)x += m;
    return x;
}

int inv(int a){
	return raise(a,MOD-2);
}

int floor1(int n,int k){
    if(n%k == 0 || n >= 0)return n/k;
    return (n/k)-1;
}

int ceil1(int n,int k){
    return floor1(n+k-1,k);
}


const int N = 1001;
int n;
int a[N];
int dp[N];
int fact[N];
int pref[N];

int nck(int n,int k){
	 int one = fact[n]*inv(fact[n-k]);
	 one %= MOD;
	 one *= inv(fact[k]);
	 one %= MOD;
	 if(one < 0)one += MOD;
	 return one;
}

void solve(){
     cin >> n;  
     RE(i,n)cin >> a[i];
     dp[0] = fact[0] = pref[0] = 1;
     RE(i,N){
     	fact[i] = fact[i-1]*i;
     	fact[i] %= MOD;
     	if(fact[i] < 0)fact[i] += MOD;
     }
     int ans = 0;
     RE(i,n){
     	dp[i] = 0;
     	for(int j = 1;j < i;j++){
     		int reqlen = a[j]+1;
     		if(reqlen < 2 or reqlen > (i-j+1))continue;
     		dp[i] += pref[j-1]*nck(i-j-1,reqlen-2);
     		dp[i] %= MOD;
     		if(dp[i] < 0)dp[i]+= MOD;	
     	}
        ans += dp[i];
        ans %= MOD;
     	if(ans < 0)ans += MOD;
     	pref[i] = pref[i-1]+dp[i];
     	pref[i] %= MOD;
     	if(pref[i] < 0)pref[i] += MOD;
     }
     debug(ans);
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