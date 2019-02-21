/*input
1 99
100 1500 500 500 1000
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
#define REP(i,n) for (int i = 0; i < (int)n; i++)
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

vi one,two;
int a[45];
int n,m;
int haha;

void rec1(int i,int sum){
	 if(i == haha+1){one.pb(sum);return;}
	 rec1(i+1,sum);
	 rec1(i+1,sum+a[i]);
}

void rec2(int i,int sum){
	 if(i == n+1){two.pb(sum);return;}
	 rec2(i+1,sum);
	 rec2(i+1,sum+a[i]);
}

void solve(){
     cin >> n >> m;
     haha = (n+1)/2;
     RE(i,n)cin >> a[i];
     rec1(1,0);
     rec2(haha+1,0);
     sort(all(two));
     int ans = 0;
     REP(i,one.size()){
     	int lo = 0;
     	int hi = two.size()-1;
     	if(one[i] > m)continue;
     	int req = m-one[i];
     	while(lo < hi){
     		int mid = (lo+hi+1)/2;
     		if(two[mid] > req)hi = mid-1;
     		else lo = mid;
     	}
     	ans += (1+lo);
     }
     cout << ans;
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;//cin >> t;
  WL(t)solve();
  return 0;
}