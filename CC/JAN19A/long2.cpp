/*input
2 2 23
23 2
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

int a[51][51];
bool done[51][51];
int n,m;
int mx = 1;

void form1(int n){
     int b[n+1][2];
    b[0][0] = 1;
    b[0][1] = 1;
    b[1][0] = 2;
    b[1][1] = 2;
    for(int i = 2;i < n;i++){
        for(int j= 0;j < 2;j++){
           if(!j){int one = b[i-2][j];
           int two = b[i-1][1];
           if(min(two,one) == 2)b[i][j] = 1;
           else if(min(two,one) == 1 && max(two,one) == 2)b[i][j] =3;
           else b[i][j] =2;
           }
           if(j){
           int one = b[i-2][j];
           int two = b[i-1][0];
           if(min(two,one) == 2)b[i][j] = 1;
           if(min(two,one) == 1 && max(two,one) == 2)b[i][j] =3;
           else b[i][j] =2;
           }
        }
    }
    for(int i = 0;i < n;i++){
        for(int j= 0;j < 2;j++){
          cout << b[j][i] << " ";
        }
          cout << endl;
     } 
}

void form2(int n){
    int b[n+1][2];
    b[0][0] = 1;
    b[0][1] = 1;
    b[1][0] = 2;
    b[1][1] = 2;
    for(int i = 2;i < n;i++){
        for(int j= 0;j < 2;j++){
           if(!j){int one = b[i-2][j];
           int two = b[i-1][1];
           if(min(two,one) == 2)b[i][j] = 1;
           else if(min(two,one) == 1 && max(two,one) == 2)b[i][j] =3;
           else b[i][j] =2;
           }
           if(j){
           int one = b[i-2][j];
           int two = b[i-1][0];
           if(min(two,one) == 2)b[i][j] = 1;
           if(min(two,one) == 1 && max(two,one) == 2)b[i][j] =3;
           else b[i][j] =2;
           }
        }
    }
    for(int i = 0;i < n;i++){
        for(int j= 0;j < 2;j++){
          cout << b[i][j] << " ";
        }
          cout << endl;
     } 
}


void ini(){
	 mx = 1;
	 REP(i,51){
	 	REP(j,51){
	 		done[i][j] = 0;
	 	}
	 }
}

bool ok(int x,int y){
	 return x > 0 and y > 0 and x < n+1 and y < m+1;
}

void assign(int x,int y){
     set<int> c;
     for(int d1 = -2;d1 <= 2;d1++){
     	for(int d2 = -2;d2 <= 2;d2++){
            if(abs(d1)+abs(d2) != 2 || !ok(x+d1,y+d2))continue;
            if(done[x+d1][y+d2])c.insert(a[x+d1][y+d2]);
     	}
     }
     int haha = 1;
     while(1){
     	if(c.find(haha) != c.end())haha++;
     	else break;
     }
     a[x][y] = haha;
     remax(mx,haha);
     done[x][y] = 1;
} 



void solve(){
	 ini();
   int n1,n2;
	 cin >> n1 >> n2;
   if(n2 == 2){cout << 3 << endl;form2(n1);return;}
   if(n1 == 2){cout << 3 << endl;form1(n2);return;}
   n = m = 50;
	// a[1][1] = 1;done[1][1] = 1;
	 RE(i,n){
	 	RE(j,m){
           assign(i,j);
	 	}
	 }
	 RE(i,n1){
	 	RE(j,n2){
	 		cout << a[i][j] << " ";
	 	}
	 	cout << endl;
	 }
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);
  //freopen("out.txt","w",stdout);
  int t = 1;cin >> t;
  WL(t)solve();
  return 0;
}