/*input
8
T a
T b
U 1
T c
T d
T e
U 1
P 2
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

//const int INF = 1e18+1;
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

const int lg = 20;
const int N = 1e6+1;
string ops = "";
int much[N];
int undolast[N];
int len[N][20];
int anc[N][20];
int actual[N];
int n;

void Init(){
	cin >> n;
	int nownow = -1;//undo index;
	int i = 0;
	REP(haha,n){
		char o;
		cin >> o;
		much[i] = 0;
		if(o == 'T'){
			char why;
			cin >> why;
			ops += why;
			undolast[i] = nownow;
			//cout << undolast[i] << endl;
			i++;
		}
		else if(o == 'U'){
			cin >> much[i];
			ops += 'u';
			
			if(nownow == -1){
				//first undo 
				actual[i] = i-much[i];
				REP(j,lg){
					len[i][j] = 0;
					anc[i][j] = -1;
				}
			}
			else{
				int undogo = undolast[i-much[i]-1];
				actual[i] = actual[undogo] + (i-much[i]-undogo-1);
			    int term = (i-much[i]-undogo-1);
			    anc[i][0] = undogo;
			    len[i][0] = term;
			    RE(j,lg-1){
			    	if(anc[i][j-1] == -1){
			    		anc[i][j] = -1;
			    	}
			    	else anc[i][j] = anc[anc[i][j-1]][j-1];
			    	if(anc[i][j] == -1){
			    		len[i][j] = 0;
			    		continue;
			    	}
			    	len[i][j] = len[anc[i][j-1]][j-1]+len[i][j-1];
			    }
			    
			}
			//cout << i << " " << actual[i] << endl;
			undolast[i] = i;
			nownow = i;
			i++;
		}
		else{
			int pos;
			cin >> pos;
			pos++;
			int startfrom = undolast[i-1];
			//cout << startfrom << endl;
			if(startfrom == -1){
				cout << ops[pos-1] << endl;
				continue;
			}
			//cout << actual[startfrom] << endl;
			if(actual[startfrom] < pos){
				pos -= actual[startfrom];
				//cout << pos << endl;
				cout << ops[startfrom+pos] << endl;
			}
			else{
				int want = actual[startfrom]-pos;
				//cout << want << endl;
				for(int j = 19;j > -1;j--){
					if(anc[startfrom][j] == -1)continue;
					if(want >= len[startfrom][j]){
						want -= len[startfrom][j];
						startfrom = anc[startfrom][j];
					}
				}
				
				int startpos = startfrom-much[startfrom];
				//cout << startfrom << endl;
				cout << ops[startpos-want-1] << endl;
			}
		}

	}
}


void solve(){
  	Init();
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