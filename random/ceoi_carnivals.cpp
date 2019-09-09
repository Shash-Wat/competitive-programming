/*input
2
2
1
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
 
const int N = 151;
int n;
int cur = 1;
int color[N];
 
int retquer(int l,int r){
	cout << r-l+1 << " ";
	for(int i = l;i <= r;i++)cout << i << " ";
	cout << endl;
    int res;cin >> res;
    return res;
}
 
void dfs(int u){
     color[u] = cur;
     int lo = u+1;
     int hi = n;
     int ans = INF;
     while(lo <= hi){
     	int mid = (lo+hi)/2;
     	int get = retquer(u,mid);
     	int get2 = retquer(u+1,mid);
     	if(get != get2)lo = mid+1;
     	else {
     		ans = mid;
     		hi = mid-1;
     	}
     }
     if(ans == INF)return;
     dfs(ans);
}
 
void solve(){
     REP(i,n)color[i] = 0;
	 cin >> n;
     RE(i,n){
     	if(!color[i]){
     		dfs(i);
     		cur++;
     	}
     }     
     cout << 0 << " ";
     RE(i,n)cout << color[i] << " ";
     cout << endl;
}
 
signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;//cin >> t;
  WL(t)solve();
  return 0;
}