/*input
8
1 5 7 8 1 7 6 1
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
int n;
int a[N];
int inds[N];
int lst[N];
int pre[N];

struct node{
	int val;//sum of indices here
	node *left,*right;
	node(){
		val = 0;
		left = right = NULL;
	}
	node(int v,node* l,node* r){
		val = v;
		left = l;
		right = r;
	}
};

#define mid (l+r)/2

node* build(int l,int r){
	if(l == r){
		return new node(!pre[l],NULL,NULL);
	}
	node *nleft = build(l,mid);
	node *nright = build(mid+1,r);
	return new node(nleft->val+nright->val,nleft,nright);
}

node* insert(node* cur,int l,int r,int ind){
	if(ind < l or ind > r)return cur;
	if(l == r and l == ind){
		return new node(1,NULL,NULL);
	}
	node *nleft = insert(cur->left,l,mid,ind);
	node *nright = insert(cur->right,mid+1,r,ind);
	return new node(cur->val+1,nleft,nright);
}

int sum(node *cur,int l,int r,int start,int end){
	if(l > end or r < start or !end)return 0;
	if(start <= l and r <= end)return cur->val;
	return sum(cur->left,l,mid,start,end)+sum(cur->right,mid+1,r,start,end);
}


int basugod(node *cur,int l,int r,int lnorz){
	if(l == r)return l;
	int one = cur->left->val;
	if(one <= lnorz)return basugod(cur->right,mid+1,r,lnorz-one);
	return basugod(cur->left,l,mid,lnorz);
}

node *roots[N];

inline int gets(int start,int val){
	// gets me highest index end such that number of distinct values in [start,end] is <= val
	int tillstart = sum(roots[start-1],1,n,1,start-1);
	
	int act = basugod(roots[start-1],1,n,tillstart+val);
	if(sum(roots[start-1],1,n,start,act) > val)return act-1;
	else return act;
}

void solve(){
  	cin >> n;
  	RE(i,n){
  		lst[i] = 0;
  		cin >> a[i];
  	}
  	RE(i,n){
  		pre[i] = lst[a[i]];
  		inds[pre[i]] = i;
  		lst[a[i]] = i;
  	}
  	roots[0] = build(1,n);
  	RE(i,n){
  		if(!inds[i]){roots[i] = roots[i-1];}
  		else roots[i] = insert(roots[i-1],1,n,inds[i]);
  	}
  	// to get number of distinct values in l-r , do sum(roots[l-1],1,n,l,r);
  	RE(i,n){
  		int start = 1;
  		int ans = 0;
  		while(start <= n){
  			ans++;
  			start = gets(start,i)+1;
  		}
  	    cout << ans << " ";
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