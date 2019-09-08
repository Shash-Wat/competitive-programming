/*input
7
1 2
2 3
2 4
4 5
4 6
6 7
4
2
7
4
-2
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

const int N = 5e5+1;
vector<int> adj[N];
int l[N];
int r[N];
int par[N];
int edge = 0;
int n,m;
queue<int> q;
int seg[4*N][3];
int lazy[4*N];

void bfs(){
	par[1] = -1;
	q.push(1);
	while(!q.empty()){
		int u = q.front();q.pop();
		l[u] = edge+1;
		for(int v:adj[u]){
			if(par[v])continue;
			edge++;
			par[v] = edge;
			q.push(v);
		}
		r[u] = edge;
	}
}

#define child 2*node
#define mid (l+r)/2

void build(int node,int l,int r){
	seg[node][0] = r-l+1;
	seg[node][1] = seg[node][2] = 0;
	if(l == r)return;
	build(child,l,mid);
	build(child+1,mid+1,r);
}

inline void pushdown(int node,int l,int r){
	if(lazy[node] == 0)return;
	int trans[] = {0,0,0};
	
	REP(i,3){
		if(i+lazy[node] >= 0 and i+lazy[node] < 3)trans[i+lazy[node]] = seg[node][i];
	}
	REP(i,3)seg[node][i] = trans[i];
	if(l != r){
		lazy[child] += lazy[node];
		lazy[child+1] += lazy[node];
	}
	lazy[node] = 0;
	return;
}

void update(int node,int l,int r,int start,int end,int val){

	pushdown(node,l,r);
	if(l > end or start > r)return;
	if(start <= l and r <= end){
		lazy[node] += val;
		pushdown(node,l,r);
		return;
	}
	update(child,l,mid,start,end,val);
	update(child+1,mid+1,r,start,end,val);
	REP(i,3){
		seg[node][i] = seg[child][i]+seg[child+1][i];
	}
}

void solve(){
  	cin >> n;
  	REP(i,n-1){
  		int a,b;cin >> a >> b;
  		adj[a].pb(b);
  		adj[b].pb(a);
  	}
  	bfs();
  	
  	build(1,1,n-1);
  	cin >> m;
  	int cnt = 0;
  	while(m--){
  		int x;cin >> x;
  		if(x < 0){
  			x = abs(x);
  			cnt--;
  			if(l[x] <= r[x]){
  				update(1,1,n-1,l[x],r[x],-1);
  			}
  			if(par[x] != -1){
  				update(1,1,n-1,par[x],par[x],-1);
  			}
  		}
  		else if(x > 0){
  			cnt++;
  			if(l[x] <= r[x]){
  				//cout << "HERE\n";
  				update(1,1,n-1,l[x],r[x],1);
  			}
  			if(par[x] != -1){
  				update(1,1,n-1,par[x],par[x],1);
  			}
  			
  		}
  		cout << 1+seg[1][2]+seg[1][1]-cnt << "\n";
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