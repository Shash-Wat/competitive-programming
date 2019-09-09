/*input
5 6
2 3
4 5
1 2
1 3
1 4
1 5
6
2 4 3
2 4 4
2 4 5
1 3 3
1 3 4
1 3 5
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


const int N = 1e5+1;
const int RN = 320;

struct qus{
	int a,b,z;
	int ind;
};

int ans[N];
int dummy_sz[RN][N];
int dummy_par[RN][N];
int par[N];
int sz[N];
vector<pii> edges;
int n,m,q;
vector<qus> pro[RN];

int find(int x){
	if(par[x] == x)return x;
	par[x] = find(par[x]);
	return par[x];
}

int dummyfind(int x,int bl){
	if(dummy_par[bl][x] == x)return x;
	dummy_par[bl][x] = dummyfind(dummy_par[bl][x],bl);
	return dummy_par[bl][x];
}

void merge(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y)return;
	if(sz[x] < sz[y])swap(x,y);
	sz[x] += sz[y];
	par[y] = x;
}

void ini(){
	REP(i,N){
		sz[i] = 1;
		par[i] = i;
	}
}

void reg(int blnum){
	RE(i,n){
		dummy_par[blnum][i] = par[i];
		dummy_sz[blnum][i] = sz[i];
	}
}

bool dummycheck(int a,int b,int z,int bl){
	a = dummyfind(a,bl);
	b = dummyfind(b,bl);
	if(a == b){
		return dummy_sz[bl][a]>=z;
	}
	return (dummy_sz[bl][a]+dummy_sz[bl][b]) >= z;
}

bool check(int a,int b,int z){
	a = find(a);
	b = find(b);
	if(a == b)return sz[a] >= z;
	return (sz[a]+sz[b]) >= z;
}

void solve(){
	ini();
  	cin >> n >> m;
  	int curblock = 1;
  	int blocksize = 0;
  	RE(i,m){
  		int x,y;cin >> x >> y;
  		edges.pb({x,y});
  		merge(x,y);
  		blocksize++;
  		if(blocksize != RN and i != m)continue;
  		reg(curblock);
  		curblock++;
  		blocksize = 0;
  	}
  	curblock--;
  	//now for each query pair find first block such that after it ended they were connected
  	cin >> q;
  	REP(i,q){
  		ans[i] = -1;
  		qus now;
  		cin >> now.a >> now.b >> now.z;
  		now.ind = i;
  		int lo = 1;
  		int hi = curblock;
  		while(lo < hi){
  			int mid = (lo+hi)/2;
  			if(dummycheck(now.a,now.b,now.z,mid))hi = mid;
  			else lo = mid+1;
  		}
  		pro[lo].pb(now);
  	}
  	int blocknow = 1;
  	blocksize = 0;
  	ini();
  	RE(i,m){
  		merge(edges[i-1].f,edges[i-1].s);
  		REP(j,pro[blocknow].size()){
  			if(check(pro[blocknow][j].a,pro[blocknow][j].b,pro[blocknow][j].z) and ans[pro[blocknow][j].ind] == -1)ans[pro[blocknow][j].ind] = i;
  		}
  		blocksize++;
  		if(blocksize == RN){
  			blocknow++;
  			blocksize = 0;
  		}
  	}
  	REP(i,q)cout << ans[i] << "\n";
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