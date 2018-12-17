/*input
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
#define debug4(x,y,z) cout << 1 << " " << x << " " << y << " " << z << endl;
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

int t,n;
vector<int> ans;

void do4(int i){
	int q1,q2,q3,q4;
	debug4(i,i+1,i+2);
	cin >> q1;
  debug4(i,i+1,i+3);
	cin >> q2;
	debug4(i,i+2,i+3);
	cin >> q3;
	debug4(i+1,i+2,i+3);
	cin >> q4;
	int trfo = q1^q2;
	int one = q3^trfo;
	int two = q4^trfo;
	int onto = one^two;
	int three = q1^onto;
	int four = q2^onto;
	ans.pb(one);
	ans.pb(two);
	ans.pb(three);
  ans.pb(four);
}

void do6(int i){
	int q1,q2,q3,q4,q5,q6;
	debug4(i,i+1,i+2);
	cin >> q1;
  debug4(i,i+1,i+3);
	cin >> q2;
	debug4(i+2,i+3,i+4);
	cin >> q3;
	debug4(i+2,i+3,i+5);
	cin >> q4;
	debug4(i+4,i+5,i);
	cin >> q5;
	debug4(i+4,i+5,i+1);
	cin >> q6;
	int trfo = q1^q2;
	int five = trfo^q3;
	int six = trfo^q4;
	int fisi = five^six;
	int one = fisi^q5;
	int two = fisi^q6;
	int onto = one^two;
	int three = q1^onto;
	int four = q2^onto;
	ans.pb(one);
	ans.pb(two);
	ans.pb(three);
  ans.pb(four);
  ans.pb(five);
	ans.pb(six);
}

void do5(int i){
	int q1,q2,q3,q4,q5;
	debug4(i,i+1,i+2);
	cin >> q1;
  debug4(i,i+1,i+3);
	cin >> q2;
	debug4(i+2,i+3,i+4);
	cin >> q3;
	debug4(i,i+2,i+4);
	cin >> q4;
	debug4(i+1,i+3,i+4);
	cin >> q5;
  int trfo = q1^q2;
	int five = trfo^q3;
	int onto = q4^q5^trfo;
	int three = q1^onto;
	int four = q2^onto;
	int one = q4^q3^four;
	int two = q5^q3^three;
	ans.pb(one);
	ans.pb(two);
	ans.pb(three);
  ans.pb(four);
  ans.pb(five);
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  cin >> t;
  while(t--){
  	cin >> n;
  	ans.clear();
  	int cur = 1;
    if(n == 11){
      do6(cur);
      cur += 6;
      do5(cur);
      cur += 5;
      //n = 0;
    }
    else if(n%4 == 1){
    	do5(cur);
    	cur += 5;
    //	n -= 5;
    }
    else if(n%4 == 2){
      do5(cur);
    	cur += 5;
    //	n -= 5;
    	do5(cur);
    	cur += 5;
    //	n -= 5;	
    }
    else if(n%4 == 3){
    	do5(cur);
    	cur += 5;
    //	n -= 5;
    	do5(cur);
    	cur += 5;
    //	n -= 5;
    	do5(cur);
    	cur += 5;
    //	n -= 5;
    }
    else{}
    while(cur <= n){
    	do4(cur);
    	cur += 4;
    }
    cout << 2 << endl;
    print(ans);
    int ver;cin >> ver;
    if(ver == -1)break;
  }
  return 0;
}