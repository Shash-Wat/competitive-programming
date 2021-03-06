/*input
4 5
3 1 2 4
M 3 4
S 1 3
P 2 3 1
M 3 4
S 1 3
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long 
#define double long double
#define f first
#define s second
#define mp make_pair
#define pb push_back
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

struct node{
	int m;
	int s;
	int l;
};

const int N = 2e5+2;
node tree[4*N];
int a[N],n,q;

void build(int idx,int l,int r){
	 if(l == r){
	 	tree[idx].s = a[l];
	 	tree[idx].m = a[l];
	 	tree[idx].l = 0;
	 	return;
	 }
	 int mid = (l+r)/2;
     build(2*idx,l,mid);
     build(2*idx + 1,mid+1,r);
     tree[idx].s = tree[2*idx].s + tree[2*idx + 1].s;
	 tree[idx].m = min(tree[2*idx].m,tree[2*idx + 1].m);
	 tree[idx].l = 0;
}

int sumq(int idx,int l,int r,int start,int end){
     if(tree[idx].l != 0){
         tree[idx].m += tree[idx].l;
         tree[idx].s += tree[idx].l*(r-l+1);
         if(l != r){
             tree[idx*2].l += tree[idx].l;
             tree[idx*2 + 1].l += tree[idx].l;
         }
         tree[idx].l = 0;
     }
     if(start > r || end < l)return 0;
     if(start <= l && end >= r)return tree[idx].s;
     int mid = (l+r)/2;
     return sumq(2*idx,l,mid,start,end)+sumq(2*idx+1,mid+1,r,start,end);
}

int minq(int idx,int l,int r,int start,int end){
     if(tree[idx].l != 0){
         tree[idx].m += tree[idx].l;
         tree[idx].s += tree[idx].l*(r-l+1);
         if(l != r){
             tree[idx*2].l += tree[idx].l;
             tree[idx*2 + 1].l += tree[idx].l;
         }
         tree[idx].l = 0;
     }
     if(start > r || end < l)return INF;
     if(start <= l && end >= r)return tree[idx].m;
     int mid = (l+r)/2;
     return min(minq(2*idx,l,mid,start,end),minq(2*idx+1,mid+1,r,start,end));
}

void lazify(int idx,int l,int r,int start,int end,int x){
    if(tree[idx].l != 0){
         tree[idx].m += tree[idx].l;
         tree[idx].s += tree[idx].l*(r-l+1);
         if(l != r){
             tree[idx*2].l += tree[idx].l;
             tree[idx*2 + 1].l += tree[idx].l;
         }
         tree[idx].l = 0;
     }
     if(start > r || end < l)return;
     if(start <= l && end >= r){
         tree[idx].m += x;
         tree[idx].s += x*(r-l+1);
         if(l != r){
             tree[idx*2].l += x;
             tree[idx*2 + 1].l += x;
         }
         return;
     }
     int mid = (l+r)/2;
     lazify(2*idx,l,mid,start,end,x);
     lazify(2*idx + 1,mid+1,r,start,end,x);
     tree[idx].s = tree[2*idx].s + tree[2*idx + 1].s;
	 tree[idx].m = min(tree[2*idx].m,tree[2*idx + 1].m);
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  freopen("haybales.in","r",stdin);
  freopen("haybales.out","w",stdout);
  cin >> n >> q;
  REP(i,n)cin >> a[i+1];
  build(1,1,n);
  while(q--){
      char type;cin >> type;
      if(type == 'M'){
          int a,b;
          cin >> a >> b;
          cout << minq(1,1,n,a,b) << endl;
      }
      if(type == 'S'){
          int a,b;
          cin >> a >> b;
          cout << sumq(1,1,n,a,b) << endl;
      }
      if(type == 'P'){
          int a,b,x;
          cin >> a >> b >> x;
          lazify(1,1,n,a,b,x);
      }
  }
  return 0;
}
