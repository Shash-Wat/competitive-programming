/*input
5 2
1 2
2 3
3 4
4 5
5 6
7
2 1 5
2 1 3
2 3 5
1 5 -1 -2
2 1 5
1 4 -1 -2
2 1 5
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

const int MOD = 1e9+7;
const int INF = 1e7+1;
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

const int K = 5;
const int N = 2e5+1;
int mn[4*N][1<<K];
int mx[4*N][1<<K];
int b[N][K];
int n,k;

#define child 2*node
#define mid (l+r)/2

void build(int num,int node,int l,int r){
	if(l == r){
		int cur = 0;
  		for(int j = 0;j < k;j++)cur += b[l][j]*(num&(1<<j)?1:-1);
		mn[node][num] = mx[node][num] = cur;
		return;
	}
	build(num,child,l,mid);build(num,child+1,mid+1,r);
	mn[node][num] = min(mn[child][num],mn[child+1][num]);
	mx[node][num] = max(mx[child][num],mx[child+1][num]);
}

void upd(int num,int node,int l,int r,int ind,int val){
	if(l == r){
		mn[node][num] = mx[node][num] = val;
		return;
	}
	if(ind <= mid)upd(num,child,l,mid,ind,val);
	else upd(num,child+1,mid+1,r,ind,val);
	mn[node][num] = min(mn[child][num],mn[child+1][num]);
	mx[node][num] = max(mx[child][num],mx[child+1][num]);
}

int getmx(int num,int node,int l,int r,int start,int end){
	if(l > end or r < start)return -INF;
	if(start <= l and r <= end){
		return mx[node][num];
	}
	return max(getmx(num,child,l,mid,start,end),getmx(num,child+1,mid+1,r,start,end));
}

int getmn(int num,int node,int l,int r,int start,int end){
	if(l > end or r < start)return INF;
	if(start <= l and r <= end){
		return mn[node][num];
	}
	return min(getmn(num,child,l,mid,start,end),getmn(num,child+1,mid+1,r,start,end));
}

void solve(){
   	cin >> n >> k;
  	RE(i,n){
  		REP(j,k)cin >> b[i][j];
  	}
  	REP(basumad,1<<k){
  		build(basumad,1,1,n);
  	}
  	int q;cin >> q;
  	while(q--){
  		int ty;cin >> ty;
  		if(ty == 1){
  			int i;cin >> i;
  			REP(j,k)cin >> b[i][j];
  			REP(bits,1<<k){
  				int cur = 0;
  				for(int l = 0;l < k;l++)cur += b[i][l]*(bits&(1<<l)?1:-1);
  				upd(bits,1,1,n,i,cur);
  			}
  		}
  		else{
  			int l,r;cin >> l >> r;
  			int ans = 0;
  			REP(lnorz,1<<k){
  				ans = max(ans,getmx(lnorz,1,1,n,l,r)-getmn(lnorz,1,1,n,l,r));
  			}
  			cout << ans << "\n";
  		}
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