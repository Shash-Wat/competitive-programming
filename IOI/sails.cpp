/*input
6
1 1
2 2
3 1
4 1
5 1
6 1
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

const int N = 1e5+1;
int lazy[4*N];
int mn[4*N];
int mx[4*N];
pair<int,int> vals[N];
int n;

#define child 2*node
#define mid (l+r)/2

inline void pushdown(int node,int l,int r){
	mn[node] += lazy[node];
	mx[node] += lazy[node];
	if(l != r){
		lazy[child] += lazy[node];
		lazy[child+1] += lazy[node];
	}
	lazy[node] = 0;
}

int bslow(int node,int l,int r,int val){
	// returns index of smallest x such that lazy[x] == val
 	if(l == r)return l;
 	pushdown(node,l,r);pushdown(child,l,mid);pushdown(child+1,mid+1,r);
 	if(mn[child] <= val)return bslow(child,l,mid,val);
 	return bslow(child+1,mid+1,r,val);
}

int bshi(int node,int l,int r,int val){
	if(l == r)return l;
 	pushdown(node,l,r);pushdown(child,l,mid);pushdown(child+1,mid+1,r);
 	if(mx[child+1] >= val)return bshi(child+1,mid+1,r,val);
 	return bshi(child,l,mid,val);
}

int getvalue(int node,int l,int r,int ind){
	pushdown(node,l,r);
	if(l == r)return mn[node];
	if(ind <= mid)return getvalue(child,l,mid,ind);
	return getvalue(child+1,mid+1,r,ind);
}

void updrange(int node,int l,int r,int start,int end){
	if(end < l or start > r)return;
	if(start <= l and r <= end){
		lazy[node]++;
		pushdown(node,l,r);
		return;
	}
	pushdown(node,l,r);
	updrange(child,l,mid,start,end);updrange(child+1,mid+1,r,start,end);
	mn[node] = min(mn[child+1],mn[child]);
	mx[node] = max(mx[child+1],mx[child]);
}

void test(){
	int n = 10;
	updrange(1,1,n,n+1 - 1,n+1 - 1);
	updrange(1,1,n,n+1 - 2,n+1 - 2);
	updrange(1,1,n,n+1 - 3,n+1 - 3);
	
	updrange(1,1,n,n+1 - 4,n+1 - 4);
	updrange(1,1,n,n+1 - 4,n+1 - 4);
	updrange(1,1,n,n+1 - 5,n+1 - 5);
	updrange(1,1,n,n+1 - 5,n+1 - 5);
	updrange(1,1,n,n+1 - 6,n+1 - 6);
	updrange(1,1,n,n+1 - 6,n+1 - 6);
	updrange(1,1,n,n+1 - 7,n+1 - 7);
	updrange(1,1,n,n+1 - 7,n+1 - 7);

	updrange(1,1,n,n+1 - 8,n+1 - 8);
	updrange(1,1,n,n+1 - 8,n+1 - 8);
	updrange(1,1,n,n+1 - 8,n+1 - 8);
	updrange(1,1,n,n+1 - 9,n+1 - 9);
	updrange(1,1,n,n+1 - 9,n+1 - 9);
	updrange(1,1,n,n+1 - 9,n+1 - 9);
	updrange(1,1,n,n+1 - 10,n+1 - 10);
	updrange(1,1,n,n+1 - 10,n+1 - 10);
	updrange(1,1,n,n+1 - 10,n+1 - 10);

	int startfrom = bslow(1,1,n,2);
	int end = bshi(1,1,n,2);
	cout <<startfrom << " " << end << endl;

}

void solve(){
	//test();
	//exit(0);
  	cin >> n;
  	int N1 = n;
  	n = 0;
  	REP(i,N1){
  		cin >> vals[i].f >> vals[i].s;
  		n = max(n,vals[i].f);
  	}
  	sort(vals,vals+N1);
  	REP(i,N1){
  		//if(i)break;
  		//cout << "PRINTING FOR : " << " " << vals[i].f << " " << vals[i].s << endl;

  		int k = vals[i].s;
  		int actualindex = vals[i].f-k+1;
  		//cout << "SHOULD START FROM : " << actualindex << endl;
  		int value_of_ind = getvalue(1,1,n,actualindex);
  		//cout << "BUT THIS WILL FUCK UP THE " << value_of_ind << " 's" << endl;
  		int startfrom = bslow(1,1,n,value_of_ind);
  		int endsat = bshi(1,1,n,value_of_ind);
  		int canplace = vals[i].f-endsat;
  		canplace = max(0LL,canplace);
  		int left = k-canplace;
  		if(canplace){
  		//	cout << "SO Updating " << endsat+1 << " to " << vals[i].f << endl;
  			updrange(1,1,n,endsat+1,vals[i].f);
  		}
  		//cout  << "NOW UPDATING THAT BLOCK FROM THE START : " << startfrom << " " << startfrom+left-1 << endl;
  		updrange(1,1,n,startfrom,startfrom+left-1);
  	}
  	int ans = 0;
  	RE(i,vals[N1-1].f){

  		int treapshit = getvalue(1,1,n,i);
  		//cout << i << " " << treapshit << endl;
  		ans += treapshit*(treapshit-1);
  	}
  	cout << ans/2;
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen("rand.txt","r",stdin);//freopen(".out","w",stdout);
  int t = 1;
  //cin >> t;
  while(t--){
    solve();
  }
  return 0;
}