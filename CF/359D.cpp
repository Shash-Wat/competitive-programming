// gives tle cuz of segtree const factor
/*input
5
2 3 5 7 11
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
#define REP(i,n) for (int i = 0; i < n; i++)
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

#define mid (l+r)/2
#define child 2*node

const int N = 3e5+1;

pair<int,int> tree[4*N];//min,gcd
int n;
int a[N];
vi ans;

void build(int node,int l,int r){
     if(l == r){
       tree[node] = {a[l],a[r]};
       return;
     }
     build(child,l,mid);build(child+1,mid+1,r);
     tree[node].f = min(tree[child].f,tree[child+1].f);
     tree[node].s = __gcd(tree[child].s,tree[child+1].s);
}

int querymin(int node,int l,int r,int start,int end){
    if(l > end or r < start)return INF;
    if(l >= start and r <= end)return tree[node].f;
    return min(querymin(child,l,mid,start,end),querymin(child+1,mid+1,r,start,end));
}

bool querygcd(int node,int l,int r,int start,int end,int val){
    if(l > end or r < start)return 1;
    if(l >= start and r <= end){
      return (tree[node].s%val == 0);
    }
    return (querygcd(child,l,mid,start,end,val) and querygcd(child+1,mid+1,r,start,end,val));
}

bool check(int len,bool print){
     int i = 1;
     int j = len;
     bool ok = 0;
     while(j <= n){
        bool temp = querygcd(1,1,n,i,j,querymin(1,1,n,i,j));
        ok |= temp;
        if(temp and print)ans.pb(i);
        i++;
        j++;
     }
     return ok;
}

#undef mid

void solve(){
     cin >> n;
     RE(i,n)cin >> a[i];  
     build(1,1,n);
     int lo = 1;
     int hi = n;
     while(lo < hi){
      int mid = (lo+hi+1)/2;
      if(check(mid,0)){
        lo = mid;
      }
      else hi = mid-1;
     }
     check(lo,1);
     debug2(ans.size(),lo-1);
     print(ans);
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;//cin >> t;
  WL(t)solve();
  return 0;
}