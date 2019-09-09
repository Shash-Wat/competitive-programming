/*input
4
1 2 3 4
3
2 3
1 2 2
2 1
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

const int N = 2e5+1;
pair<int,int> lazy[4*N];
pair<int,int> bad = {1e5,0};
int n,q;
int a[N];
// make it {1e5,0} initially
// type 0 means min , 1 means max

pair<int,int> changebymin(pair<int,int> give,int z){
		int x = give.f;
		int y = give.s;
		
		if(z < y){
			return {z,z};
		}
		if(z > x){
			return give;
		}

		return {z,y};
}

pair<int,int> changebymax(pair<int,int> give,int z){
		if(z >= give.f){
			return {z,z};
		}
		return {give.f,max(z,give.s)};
}

void pushdown(int node){
	//for child one
	//if(lazy[node]==bad)return;
	int c1 = 2*node;
	int c2 = c1+1;
	pair<int,int> temp1,temp2;
	temp1 = changebymin(lazy[c1],lazy[node].f);
	pair<int,int> temp11 = changebymax(temp1,lazy[node].s);
	temp2 = changebymin(lazy[c2],lazy[node].f);
	pair<int,int> temp22 = changebymax(temp2,lazy[node].s);
	lazy[c1] = temp11;
	lazy[c2] = temp22;
	lazy[node] = {1e5,0};
}

void update(int node,int l,int r,int start,int end,int type,int z){
	if(  l != r){
		pushdown(node);
	}
	if(l > end or r < start)return;
	if(l >= start and r <= end){
		if(type == 0){
			lazy[node] = changebymin(lazy[node],z);
		}
		if(type == 1){
			lazy[node] = changebymax(lazy[node],z);
		}
		if(l != r)pushdown(node);
		return;
	}
	update(2*node,l,(l+r)/2,start,end,type,z);
	update(2*node+1,((l+r)/2)+1,r,start,end,type,z);
}

int get(int node,int l,int r,int ind){
	if( l != r){
		pushdown(node);
	}
	if(l == r){
		return max(min(lazy[node].f,a[l]),lazy[node].s);
	}
	if(l <= ind and ind <= (l+r)/2)return get(2*node,l,(l+r)/2,ind);
	return get(2*node+1,(l+r)/2 + 1,r,ind);
}

void solve(){
  	cin >> n;
  	RE(i,n)cin >> a[i];
  	REP(i,4*N){
  		lazy[i] = {1e5,0};
  	}
  	cin >> q;
  	while(q--){
  		int type;cin >> type;
  		if(type == 2){
  			int z;cin >> z;
  			update(1,1,n,1,n,1,z);
  		}
  		else{
  			int i,x;
  			cin >> i >> x;
  			a[i] = x;
  		}
  	}
    RE(i,n)cout << get(1,1,n,i) << " ";
  	//cout << endl;
  	
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