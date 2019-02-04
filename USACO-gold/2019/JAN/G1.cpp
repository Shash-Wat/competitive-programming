/*input
3 3 10
3 1
4 1
3 2
A
B
A
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

const int N = 5001;

vector<int> lenghts;
vector<int> classwise[N];
int freq[26];
int dp[N];// dp[i] = no of ways to get sum I
int ending[N];// ends[i] = no of ways to get a line ending with Ith class
int n,m,k;

void solve(){
	 cin >> n >> m >> k;
	 REP(i,n){
	 	int a,b;cin >> a >> b;
	 	lenghts.pb(a);
	 	classwise[b].pb(a);
	 }
     REP(i,m){
     	char o;cin >> o;
     	freq[o-'A']++;
     }
     dp[0] = 1;
     for(int i = 1;i <= k;i++){
     	 dp[i] = 0;
     	 for(int j = 0;j < n;j++){
     	 	 if(k >= lenghts[j]){dp[i] += dp[i-lenghts[j]];dp[i]%=MOD;}
     	 }
     }
     
    for(int i = 1;i <= n;i++){
     	ending[i] = 0;
     	for(int j = 0;j < classwise[i].size();j++){
           ending[i] += dp[k-classwise[i][j]];
           ending[i] %= MOD;
     	}
     	//cout << ending[i] << " ";
     }
     int ans = 1;
     for(int i = 0;i < 26;i++){
     	if(!freq[i])continue;
     	int tmp = 0;
     	for(int j = 1;j <= n;j++){
     		tmp += fast_ex(ending[j],freq[i],MOD);
     		tmp %= MOD;
     	}
     	ans *= tmp;
     	ans %= MOD;
     }
     cout << ans;
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  freopen("poetry.in","r",stdin);freopen("poetry.out","w",stdout);
  int t = 1;//cin >> t;
  WL(t)solve();
  return 0;
}
