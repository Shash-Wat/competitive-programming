/*input
4 4 1
****
*..*
*.**
****
3 2
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

const int N = 1001;
int n,m,q;
//bool a[N][N];
int per[N*N];
int comp[N][N];

int cnt = 1;

int add1[] = {0,0,1,-1};
int add2[] = {1,-1,0,0};

bool ok(int x,int y){
	 if(x > 0 and y > 0 and x <= n and y <= m)return 1;
	 return 0;
}

void dfs(int i,int j){
     per[cnt]+= 4;
     comp[i][j] = cnt;
     REP(k,4){
     	int ni = i+add1[k];
     	int nj = j+add2[k];
     	if(ok(ni,nj)){
     		if(comp[ni][nj] != INF)per[cnt]--;
            if(!comp[ni][nj])dfs(ni,nj);
     	}
     }
}

void solve(){
     cin >> n >> m >> q;
     RE(i,n){
     	RE(j,m){
     		char o;cin >> o;
     		if(o == '*')comp[i][j] = INF;
     	}
     }
     RE(i,n){
     	RE(j,m){
     		if(!comp[i][j]){
     			dfs(i,j);
     			cnt++;
     		}
     	}
     }
     while(q--){
     	int a,b;cin >> a >> b;
     	cout << per[comp[a][b]] << endl;
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