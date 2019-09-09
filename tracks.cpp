/*input
5 8
FFR.....
.FRRR...
.FFFFF..
..RRRFFR
.....FFF
*/
#pragma comment(linker, "/stack:200000000")
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
 
#define ll int
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
 

const double PI = 3.14159265358979323846264338;

int floor1(int n,int k){
    if(n%k == 0 || n >= 0)return n/k;
    return (n/k)-1;
}
 
int ceil1(int n,int k){
    return floor1(n+k-1,k);
}
 
const int N = 4001;
int a[N][N];
int lev[N][N];
int n,m;
 
pair<int,int> xd[] = {{-1,0},{0,-1},{1,0},{0,1}};
 
bool ok(int x,int y){
	return (x and y and (x <= n) and (y <= m));
}
 
queue<pair<pair<int,int>,ll > > q;
stack<pair<pair<int,int>,int> > st;
 

void dfs(){
	
	
}
 
 
void solve(){
  	cin >> n >> m;
  	RE(i,n){
  		RE(j,m){
  			char o;cin >> o;
  			//cout << o;
  			if(o == '.')continue;
  			if(o == 'F')a[i][j] = 1;
  			else a[i][j] = 2;
  		}
  	}
  	q.push({{1,1},1});
	ll ans = 1;
	while(!q.empty()){
		int i1 = q.front().f.f;
		int j1 = q.front().f.s;
		ll npara = q.front().s;
		q.pop();
		if(lev[i1][j1])continue;
		ans = max(ans,npara);
		st.push({{i1,j1},npara});
		while(!st.empty()){
			int i = st.top().f.f;
			int j = st.top().f.s;
			int para = st.top().s;
			lev[i][j] = para;
			st.pop();
			REP(k,4){
				int ni = i+xd[k].f;
				int nj = j+xd[k].s;
 
				if(!ok(ni,nj))continue;
				if(a[i][j] != a[ni][nj]){
					if(a[ni][nj] and !lev[ni][nj])q.push({{ni,nj},para+1});
					continue;
				}
		
				if(!lev[ni][nj])st.push({{ni,nj},para});
			}
		}
	}
	cout << ans;
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
