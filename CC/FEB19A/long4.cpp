/*input
3
5 9 1
7 9 2
3 20 3
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

int inv(int n){
	return fast_ex(n,MOD-2,MOD);
}

int n,m,k;

void solve(){
	 cin >> n >> k >> m;
	 if(m == 1){
	 	//can only guess
	 	cout << inv(n) << endl;
	 	return;
	 }
	 if(n <= k)m++;
	 int x = n%k;
	 if(!x)x = k;
	 int ops = m/2;
	 if(m%2 == 0){
	 	int one = (x-1)*inv(x);
	 	one %= MOD;
	 	int two = fast_ex(one,ops,MOD);
	 	int ans = 1-two;
	 	ans %= MOD;
	 	ans = (ans+MOD)%MOD;
	 	cout << ans << endl;
	 	return;
	 }
	 else{
	 	int one = (x-1)*inv(x);
	 	one %= MOD;
	 	int two = fast_ex(one,ops,MOD);
	 	int ans = 1-two;
	 	int extra = inv(x+k);
	 	extra *= fast_ex(one,ops,MOD);
	 	extra %= MOD;
	 	ans += extra;
	 	ans %= MOD;
	 	ans = (ans+MOD)%MOD;
	 	cout << ans << endl;
	 	return;
	 }
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;cin >> t;
  WL(t)solve();
  return 0;
}