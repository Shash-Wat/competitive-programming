/*input
5 6
1 2 1 1 5
1 2 3 4 5 6
*/
#include<iostream>
using namespace std;

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
int n,m;
int a[N];
long long int suma = 0;
long long int minn[N];

void solve(){
	scanf("%d",&n);
	scanf("%d",&m);
  	RE(i,n){
  		scanf("%d",&a[i]);
  	}
  	while(m--){
  		int k;scanf("%d",&k);
  		suma = 0;
  		minn[0] = 0;
  		int ans = 0;
  		RE(i,n){
  			int lo = 0;
  			int hi = i-1;
  			suma += (long long)a[i]-k;
  			minn[i] = min(minn[i-1],suma);
  			if(minn[hi] > suma)continue;
  			while(lo < hi){
  				int mid = (lo+hi)/2;
  				if(minn[mid] <= suma)hi = mid;
  				else lo = mid+1;
  			}
  			ans = max(ans,i-lo);
  		}
  		printf("%d ",ans);
  	}
}

signed main(){
  //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;
  //cin >> t;
  while(t--){
    solve();
  }
  return 0;
}