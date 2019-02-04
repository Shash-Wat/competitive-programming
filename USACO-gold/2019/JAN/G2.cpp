/*input
6

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
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define remin(a,b) a = min(a,b)
#define all(v) v.begin(),v.end()
#define pii pair<int,int>
#define mii map<int,int>
#define vi vector<int>
#define vvi vector<vi>
#define WL(t) while(t --)
#define gcd(a,b) __gcd((a),(b))
#define lcm(a,b) ((a)*(b))/gcd((a),(b))
const int INF = 1e18+1;
const int MOD = 1e9+7;
const double PI = 3.14159265358979323846264338;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int n;
int a[100001];
int b[100001];

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  freopen("sleepy.in","r",stdin);
  freopen("sleepy.out","w",stdout);
  cin >> n;
  int i = 1;
  while(cin >> a[i])i++;
  ordered_set x;
  n = i-1;
  int pos = n;
  while(pos > 0){
	if(x.order_of_key(a[pos]) == 0){
		x.insert(a[pos]);pos--;
	}
	else break;
  }
  for(int i = 1;i <= pos;i++){
       int tmp = x.order_of_key(a[i]);
       tmp += pos-i;
       x.insert(a[i]);
       b[i] = tmp;
  }
  cout << pos << endl;
  for(int i = 1;i <= pos;i++){
    	cout << b[i];
    	if(i != pos)cout << " ";
  }	
  return 0;
}
