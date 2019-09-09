/*input
9
4 6 3 6 3 7 2 6 5
2
2
5
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

const int INF = 1e7+1;
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

const int N = 1e6+1;
int a[N];
int dp[N];
deque<int> dq;
int n,k,q;

void solve(){
  	cin >> n;
  	RE(i,n)cin >> a[i];
  	cin >> q;
  	while(q--){
  		int k;cin >> k;
  		while(!dq.empty())dq.pop_back();
  		RE(i,n)dp[i] = INF;
  		dq.push_back(1);
  		dp[1] = 0;
  		for(int i = 2;i <= n;i++){
  			dp[i] = dp[dq.front()]+(a[i] >= a[dq.front()]);
  			while(!dq.empty()){
  				if(dp[dq.back()] > dp[i])dq.pop_back();
  				else if(dp[dq.back()] == dp[i] and a[i] > a[dq.back()])dq.pop_back();
  				else break;
  			}
  			dq.push_back(i);
  			if(dq.front()+k == i)dq.pop_front();
  		}
  		cout << dp[n] << "\n";
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