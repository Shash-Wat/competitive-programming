/*input
10 3
1 2 1 2 1 2 3 2 3 3
8
1 2
1 3
1 4
1 5
2 5
2 6
6 9
7 10
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

const int C = 1e4+1;
const int N = 3e5+1;
int a[N];
int tre[4*N];
vector<int> c[C];
int n,m;
vector<int> all;

int occ(int color,int index){
	if(!c[color].size())return 0;
	if(c[color][0] > index)return 0;
	int lo = 0;
	int hi = c[color].size();
	hi--;
	while(lo < hi){
		int mid = (lo+hi+1)/2;
		if(c[color][mid] > index)hi = mid-1;
		else lo = mid;
	}
	return (lo+1);
}


#define child 2*node
#define mid (l+r)/2

void build(int node,int l,int r){
	tre[node] = 0;
	if(l == r){
		tre[node] = a[l];
		return;
	}
	build(child,l,mid);
	build(child+1,mid+1,r);
	int op1 = tre[child];
	int op2 = tre[child+1];

	int tot1 = occ(op1,r)-occ(op1,l-1);
	int tot2 = occ(op2,r)-occ(op2,l-1);
	if(tot1 < tot2){
		swap(tot1,tot2);
		swap(op1,op2);
	}
	if(tot1 > (r-l+1)/2)tre[node] = op1;
}

void query(int node,int l,int r,int start,int end){
	if(l > end or r < start)return;
	if(start <= l and r <= end){
		all.pb(tre[node]);
		return;
	}
	query(child,l,mid,start,end);
	query(child+1,mid+1,r,start,end);
}

int q;

void solve(){
  	cin >> n >> m;
  	RE(i,n){
  		cin >> a[i];
  		c[a[i]].pb(i);
  	}
  	build(1,1,n);
  	cin >> q;
  	while(q--){
  		int l,r;cin >> l >> r;
  		all.clear();
  		query(1,1,n,l,r);
  		bool nicenice = 0;
  		for(auto it:all){
  			int tot = occ(it,r)-occ(it,l-1);
  			if(tot > (r-l+1)/2){
  				cout << "yes ";
  				cout << it << endl;
  				nicenice = 1;
  				break;
  			}
  		}
  		if(!nicenice)cout << "no" << endl;
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