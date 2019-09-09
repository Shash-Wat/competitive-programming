/*input
4 5 5
....#
.#..#
...#.
....#
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

const int N = 1025;

int vis[N][N];
int n,m;
int grid[N][N];
int c1,c2;
int leaves[N*N];
// 0 means empty
// 1 blocked
// 2 is me block
int cuco = 0;
vector< pair<int,int> > bests;

int xd[] = {-1,0,1,0};
int yd[] = {0,1,0,-1};

void printans(){
     string best = ".#X";
     RE(i,n){
      RE(j,m){
        //if(!grid[i][j] and vis[i][j] != which)grid[i][j] =2;
        cout << best[grid[i][j]];
      }
      cout << "\n";
    }
}

bool ok(int x,int y){
	return (x > 0 and y > 0 and x <= n and y <= m and !grid[x][y]);
}

int get_ne(int x,int y){
	int res = 0;
	for(int i = 0;i < 4;i++){
		int xn = x+xd[i];
		int yn = y+yd[i];
		if(ok(xn,yn) and vis[xn][yn] == vis[x][y])res++;
	}
	return res;
}

int wow_ne(int x,int y,int col){
  int res = 0;
  for(int i = 0;i < 4;i++){
    int xn = x+xd[i];
    int yn = y+yd[i];
    if(ok(xn,yn) and vis[xn][yn] == col)res++;
  }
  return res;
}

void bfs(int si,int sj){
	vis[si][sj] = cuco;
	queue< pair<int,int> > q;
	q.push({si,sj});
	int ans = 0;
	while(!q.empty()){
		int i = q.front().f;
		int j = q.front().s;
		q.pop();
		int viscount = 0;
		for(int k = 0;k < 4;k++){
			int ni = i+xd[k];
			int nj = j+yd[k];
			if(!ok(ni,nj))continue;
			if(vis[ni][nj] == cuco)viscount++;
		}
		if(viscount > 1){
			vis[i][j] = 0;
			continue;
		}
		for(int k = 0;k < 4;k++){
			int ni = i+xd[k];
			int nj = j+yd[k];
			if(!ok(ni,nj))continue;
			if(vis[ni][nj])continue;
			q.push({ni,nj});
			vis[ni][nj] = cuco;
		}
	}
}

int k;

int trythis(int col){
    int temp = 0;
    RE(i,n){
      RE(j,m){
        if(vis[i][j] != col and !grid[i][j]){
          int haha = wow_ne(i,j,col);
          if(haha == 1)temp++;
        }
      }
    }
    return leaves[col];
}

void solve(){
  	cin >> n >> m >> k;
  	//cout << n << " " << m << endl;
  	RE(i,n){
  		RE(j,m){
  			char o;cin >> o;
  			grid[i][j] = (o == '#');
  		}
  	}
  	int ans = 0;
  	int which = 0;
  	//sort(all(wow),cmp);
  	//random_shuffle(all(wow));
  	RE(i,n){
      RE(j,m){
  			
  			if(vis[i][j] or grid[i][j])continue;
  			cuco++;
  			bfs(i,j);
      }
  			//cout << cuco << " " << cur << endl;
  	}
  	RE(i,n){
  		RE(j,m){
  			leaves[vis[i][j]] += (get_ne(i,j) == 1);
  		}
  	}

  	RE(i,cuco){
  		bests.pb({leaves[i],i});
  	}
    sort(all(bests));
    reverse(all(bests));
    
    REP(i,min((int)bests.size(),20LL)){
        int mesmart = trythis(bests[i].s);

        if(mesmart > ans){
          which = bests[i].s;
          ans = mesmart;
        }
    }

   RE(i,n){
      RE(j,m){
        if(!grid[i][j]){
          if(vis[i][j] == which)continue;
          else if(wow_ne(i,j,which) == 1){
            vis[i][j] = which;
            continue;
          }
          grid[i][j] = 2;
        }
      }
   }
   //cout << ans << " " << k << endl;
   printans();
}

signed main(){
  //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  freopen("03.in","r",stdin);
  freopen("03.out","w",stdout);
  int t = 1;
  //cin >> t;
  while(t--){
    solve();
  }
  return 0;
}