/*input
6 3 2 13 3
AFBBet
AFC 6
cp 4
A 3
EE 3
Bc 1
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

string s;
int n;
int m;
int a;
int coins;
int r;
vector< pair<int,string> >pretty;
vector< pair<string,int> >good;
vector< pair<int,char> > changes;
int cost[100001];
string what[100001];
vector< pii > pos;
int ind_of_cheap;
int cheapcost = INF;
int cheaplen = INF;
int ops = 0;

int getcost(char o){
    if(o >= 'a' && o <= 'z')return (o-'a'+1);
    else return (o-'A'+27);
}

int replace_cost(string t){
     if(t.size() > s.size())return INF;
     int res = 0;
     REP(i,t.size()){
         res += abs(getcost(s[i])-getcost(t[i]));
     }
     return res;
}

void gen_changes(string t){
     int res = 0;
     REP(i,t.size()){
         if(t[i] != s[i]){
            changes.pb({i+1,t[i]});
         }
     }
}

void extend(){
     srand(time(0));
     string wow = "";
     int xx = coins;
     int haha = xx;
     int ind = 0;
     int wait = 0;
     while(ind < n){
        int one = rand()%MOD;
        int two = rand()%MOD;
        int rand_ind = (one*two)%a;
        if(wow.size()+what[rand_ind].size()+n-ind-1 > 1000000 || ops > 99999)break;
        if(haha < cost[rand_ind]){
            wait++;
            if(wait == 69)break;
            continue;
        }
        wait = 0;
        pos.pb(mp(rand_ind+1,wow.size()+1));
        wow += what[rand_ind];
        haha -= cost[rand_ind];
        ind++;
        ops++;
     }
     for(int i = ind;i < n;i++)wow += s[i];
     int subtract = xx;
     subtract -= haha;
     coins -= subtract;
     s = wow;
     return;
}

void solve(){
     cin >> n >> m >> a >> coins >> r >> s;
     pretty.resize(m);good.resize(a);
     REP(i,m){
         cin >> pretty[i].s >> pretty[i].f;
     }
     REP(i,a){
        cin >> good[i].f; good[i].s = i;
        what[i] = good[i].f;
        cin >> cost[i];
     } 
     sort(all(pretty));reverse(all(pretty));
     sort(all(good));
     cheaplen = good[0].f.size();
     ind_of_cheap = good[0].s;
     extend();
   /*  int now = 0;
     string cur = "";
     while(now < m || ops > 99999){
         // add if possible
         if(pretty[now].f < 0)break;
         string haha = cur;
         haha += pretty[now].s;
         int xd = replace_cost(haha);
         if(xd <= coins){
            coins -= xd;
            cur = haha;
            continue;
         }
         ops++;
         now++;
     }
     gen_changes(cur);*/
  /*   if(coins >= r){
        cout << changes.size()+1 << endl;
        REP(i,changes.size()){
            debug3(1,changes[i].f,changes[i].s);
        }
        debug3(1,1,n);
     }
     else{*/
        cout << pos.size() << endl;
        REP(i,pos.size()){
            cout << 2 << " ";debug3(pos[i].s,pos[i].s,pos[i].f);
        }
    // }
}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;//cin >> t;
  WL(t)solve();
  return 0;
}