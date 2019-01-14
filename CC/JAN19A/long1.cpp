/*input
3 2
10 1 100
4 3
*/
// logic = find max a_i , pair it with all b_js then find min b_j and pair with all a_i,s

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


void solve(){
	 int n,m;
	 cin >> n >> m;
	 int ind_a = 0;
	 int ind_b = 0;
	 int max_a = -INF;
	 int min_b = INF;
	 REP(i,n){
	 	int a;cin >> a;
	 	if(a > max_a){
	 		max_a = a;
	 		ind_a = i;
	 	}
	 }
	 REP(i,m){
	 	int b;cin >> b;
	 	if(b < min_b){
	 		min_b = b;
	 		ind_b = i;
	 	}
	 }
	 REP(i,m){
	 	cout << ind_a << " " << i << endl;
	 }
	 REP(i,n){
	 	if(i == ind_a)continue;
	 	cout << i << " " << ind_b << endl;
	 }
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;//cin >> t;
  WL(t)solve();
  return 0;
}
