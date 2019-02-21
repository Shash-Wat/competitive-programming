/*input
6 2
1 1 1 2 2 2
5
1 6
4 3
1 1
2 6
2 6
*/
#include<bits/stdc++.h>
using namespace std;

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
#define remax(a,b) a = max(a,b)
#define remin(a,b) a = min(a,b)
#define all(v) v.begin(),v.end()
#define pii pair<int,int>
#define mii map<int,int>
#define vi vector<int>
#define vvi vector<vi>
#define WL(t) while(t --)
#define gcd(a,b) __gcd((a),(b))
#define lcm(a,b) ((a)*(b))/gcd((a),(b))
#define print(arr) for (auto it = arr.begin(); it != arr.end(); ++it) cout << *it << " "; cout << endl;
#define debug(x) cout << x << endl;
#define debug2(x,y) cout << x << " " << y << endl;
#define debug3(x,y,z) cout << x << " " << y << " " << z << endl;
const int INF = 1e18+1;
const int MOD = 1e9+7;
const double PI = 3.14159265358979323846264338;

int fast_ex(int a,int n,int m){
  if(n == 0)return 1;
  if(n == 1)return a;
  int x = 1;
    x *= fast_ex(a,n/2,m);
    x %= m;
    x *= x;
    x %= m;
    if(n%2)x*= a;
    x %= m;
    return x;
}

const int N = 1e5+1;
int prevs[N];
int a[N];
vi haha[N];
vi tree[4*N];
int n,k;

#define mid (l+r)/2
#define child 2*node

void build(int node,int l,int r){
     tree[node].resize(r-l+1);
     if(l == r){
     	tree[node][0] = prevs[l];
     	return;
     }
     build(child,l,mid);build(child+1,mid+1,r);
     merge(tree[child].begin(),tree[child].end(),tree[child+1].begin(),tree[child+1].end(),tree[node].begin());
     return;
}

int query(int node,int l,int r,int start,int end){
    if(end < l or start > r)return 0;
    if(l >= start and r <= end){
    	int lo = 0;
    	int hi = tree[node].size()-1;
    	if(tree[node][lo] >= start)return 0;
    	while(lo < hi){
             int m = (lo+hi+1)/2;
             if(tree[node][m] < start)lo = m;
             else hi = m-1;
    	}
    	return (lo+1);
    }
    return query(child,l,mid,start,end)+query(child+1,mid+1,r,start,end);
}

void solve(){
	 cin >> n >> k;
	 RE(i,n){
	 	int j;cin >> j;
	 	haha[j].pb(i);
	 }
	 RE(i,N-1){
	 	REP(j,haha[i].size()){
	 		if(j < k)prevs[haha[i][j]] = 0;
	 		else prevs[haha[i][j]] = haha[i][j-k];
	 	}
	 }
	 build(1,1,n);
	 int q;cin >> q;
	 int ans = 0;
	 while(q--){
         int x,y;cin >> x >> y;
         int l = (x+ans)%n;l++;
         int r = (y+ans)%n;r++;
         if(l > r)swap(l,r);
         ans = query(1,1,n,l,r);
         cout << ans << endl;
	 }
     
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;//cin >> t;
  WL(t)solve();
  return 0;
}