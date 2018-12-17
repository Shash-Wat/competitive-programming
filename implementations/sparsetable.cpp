/*input
5
-1212 -1 1 1 0
2
0 2
2 2
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long 
#define double long double
#define f first
#define s second
#define mp make_pair
#define pb push_back
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

const int N = 1e5+1,LG = 30;

int n;
int a[N];
int spa[N][LG];

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  cin >> n;
  REP(i,n){
  	cin >> a[i];
  	spa[i][0] = a[i];
  }
  for(int j = 1;(1 << j) <= n;j++){
  	 REP(i,n){
  	 	if(i+(1 << j) > n)continue;
  	 	spa[i][j] = min(spa[i][j-1],spa[i+(1 << (j-1))][j-1]);
  	 }
  }
  int q;cin >> q;
  WL(q){
     int l,r;
     cin >> l >> r;
     int llg = log2(r-l+1);
     int one = spa[l][llg];
     int two = spa[r-(1 << llg)+1][llg];
     cout << min(one,two) << endl;
  }
  return 0;
}