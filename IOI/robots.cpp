/*input
3 2 10
6 2 9
4 7
4 6
8 5
2 3
7 9
1 8
5 1
3 3
8 7
7 6
10 5
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

const int N = 1e6+1;
const int K = 5e4+1;
int w[N],s[N];
int x[K],y[K];
int a,b,t;
vector<int> nice;

bool comp1(int ind1,int ind2){
  return w[ind1] < w[ind2];
}

bool check(int sz){
     priority_queue<int> pq;
    /* for(int i = 0;i < t;i++)cout << w[nice[i]] << " ";
     cout << endl;*/
     int cur = 0;
     int toy = 0;
     while(cur < a){
        if(toy == t or (w[nice[toy]] >= x[cur]) ){
          int did = 0;
          while(!pq.empty() and did < sz){pq.pop();did++;}
          cur++;
        }
        else{
          pq.push(s[nice[toy]]);
          toy++;
        }
     }
     
     int did = 0;
     if(cur < a)while(!pq.empty() and did < sz){pq.pop();did++;}
     
     while(toy < t){
      pq.push(s[nice[toy]]);
      toy++;
     }
     priority_queue<int> two;
     while(!pq.empty()){
         two.push(-pq.top());
         pq.pop();
     }
     cur = 0;
     did = 0;
     while(cur < b and !two.empty()){
        if(did == sz){cur++;did = 0;}
        else if(y[cur] <= -two.top()){cur++;did = 0;}
        else{
            two.pop();
            did++;
        }
     }
     return two.empty();
}

void solve(){
    cin >> a >> b >> t;
    REP(i,a)cin >> x[i];
    REP(i,b)cin >> y[i];
    sort(x,x+a);
    sort(y,y+b);
    REP(i,t){
      cin >> w[i] >> s[i];
    }
     REP(i,t)nice.pb(i);
     sort(nice.begin(),nice.end(),comp1);
    int lo = 1;
    int hi = t;
    while(lo < hi){
      int mid = (lo+hi)/2;
      if(check(mid))hi = mid;
      else lo = mid+1;
    }
    if(check(lo))cout << lo;
    else cout << -1;
} 

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  solve();
  return 0;
}