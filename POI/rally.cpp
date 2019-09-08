/*input
8 10
8 4
8 7
7 6
6 3
6 5
5 4
4 3
4 2
3 2
2 1
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
int n,m;
int en[N];
int start1[N];
int order[N];
int inv[N];
queue<int> q;
int now = 0;
int deg[N];
int seg[4*N];
vector<pair<int,int> > edges;
int pref[N];
int suf[N+1];

#define child 2*node
#define mid (l+r)/2

void update(int node,int l,int r,int start,int end,int val){
	if(l > end or r < start)return;
	if(start <= l and r <= end){
		seg[node] = max(seg[node],val);
		return;
	}
	update(child,l,mid,start,end,val);
	update(child+1,mid+1,r,start,end,val);
}

int get(int node,int l,int r,int ind,int cur){
	int ncur = max(cur,seg[node]);
	if(l == r)return ncur;
	if(ind <= mid)return get(child,l,mid,ind,ncur);
	return get(child+1,mid+1,r,ind,ncur);
}

void solve(){
  	cin >> n >> m;
  	RE(i,m){
  		int a,b;cin >> a >> b;
  		adj[a].pb(b);
  		edges.pb({a,b});
  		deg[b]++;
  	}
  	RE(i,n){
  		if(deg[i] == 0)q.push(i);
  	}
  	while(!q.empty()){
  		now++;
  		order[q.front()] = now;
  		inv[now] = q.front();

  		int u = q.front();
  		//cout << u << endl;
  		q.pop();
  		for(int v:adj[u]){
  			deg[v]--;
  			if(deg[v] == 0)q.push(v);
  		}
  	}
  	RE(i,n){
  		int u = inv[i];
  		for(int v:adj[u]){
  			en[v] = max(en[v],en[u]+1);
  		}
  	}
  	RED(i,n){
  		int u = inv[i];
  		for(int v:adj[u]){
  			start1[u] = max(start1[u],start1[v]+1);
  		}
  	}
  	REP(i,m){
  		int st = order[edges[i].f];
  		int ed = order[edges[i].s];
  		if(st+1 == ed)continue;
  		update(1,1,n,st+1,ed-1,start1[edges[i].s]+en[edges[i].f]+1);
  		//cout << start1[edges[i].s]+en[edges[i].f]+1 << " " << st+1 << " " << ed-1 << endl;
  	}
  	
  	RE(i,n){
  		pref[i] = max(pref[i-1],en[inv[i]]);
  	}
  	RED(i,n){
  		suf[i] = max(suf[i+1],start1[inv[i]]);
  	}
  	int ans = n;
  	int which = 0;
  	RE(i,n){
  		int one = max(pref[i-1],suf[i+1]);
  		int vali = get(1,1,n,i,0);
  		vali = max(vali,one);
  		if(vali < ans){
  			ans = vali;
  			which = inv[i];
  		}
  	}
  	cout << which << " " << ans << "\n";
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