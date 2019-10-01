/*input
3 8
U 1 5
U 2 7
Z 2 6
U 3 1
Z 2 6
U 2 2
Z 2 6
Z 2 1
*/
#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

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


const int N = 1e3+1;
vector<int> all;
int n,m;

void solve(){
    cin >> n >> m;
    REP(i,n)all.pb(0);
    int sum = 0;
    while(m--){
      char o;cin >> o;
      if(o == 'U'){
        int ind;cin >> ind;
        ind--;
        
        cin >> all[ind];
        
      }
      else{
        vector<int> wow = all;
        sort(all(wow));
        int c,s;cin >> c >> s;
        int lo = 0;
        int hi = wow[n-1];
        while(lo < hi){
          int mid = (lo+hi+1)/2;
          long long int sua = 0;
          REP(i,n){
            sua += (long long int)min(wow[i],mid);
          }
        //  cout << mid << " " << sua << endl;
          if(mid <= sua/c)lo = mid;
          else hi = mid-1;
        }
        //cout << lo << endl;
        long long int sua = 0;
        REP(i,n){
          sua += (long long int)min(wow[i],lo);
        }
        if(sua/c >= s)cout << "TAK\n";
        else cout << "NIE\n";
      }
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