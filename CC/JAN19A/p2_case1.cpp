/*input
1 5 5
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long 
#define double long double
#define RE(i,n) for (int i = 1; i <= n; i++)
#define RED(i,n) for (int i = n; i > 0; i--)
#define REPS(i,n) for(int i = 1; (i*i) <= n; i++)
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define remax(a,b) a = max(a,b)
#define remin(a,b) a = min(a,b)

void do1(int n,int m){
	 if(n == 1 && m == 1){
        cout << 1 << endl << 1 << endl;
        return;
	 }
	 if(n == 1 && m == 2){
	 	cout << 1 << endl;
	 	cout << "1 1" << endl;
	 	return;
	 }
	 if(n == 2 && m == 1){
	 	cout << 1 << endl << 1 << endl << 1 << endl;
	 	return;
	 }
	 if(n == 1){
	 	int a[m+1];
	 	a[0] = 1;
	 	a[1] = 1;
        for(int i = 2;i < m;i++){
        	if(a[i-2] == 1)a[i] = 2;
        	else a[i] = 1;

        }
        cout << 2 << endl;
        for(int i = 0;i < m;i++)cout << a[i] << " ";
        cout << endl;
        return;
	 }
	 else{
	 	int a[n+1];
	 	a[0] = 1;
	 	a[1] = 1;
        for(int i = 2;i < n;i++){
        	if(a[i-2] == 1)a[i] = 2;
        	else a[i] = 1;
        }
        cout << 2 << endl;
        for(int i = 0;i < n;i++)cout << a[i] << endl;
        return;
	 }
}

void do2(int n,int m){
    int b[max(n+1,m+1)][2];
    b[0][0] = 1;
    b[0][1] = 1;
    b[1][0] = 2;
    b[1][1] = 2;
     if(n == 2 && m == 2){
	 	cout << 2 << endl;
	 	REP(i,2){
	 		REP(j,2){
	 			cout << b[i][j] << " ";
	 		}
	 		cout << endl;
	 	} 
	 	return;
	 }
    for(int i = 2;i < max(n,m);i++){
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
           else if(min(two,one) == 1 && max(two,one) == 2)b[i][j] =3;
           else b[i][j] =2;
           }
        }
    }
    cout << 3 << endl;
    if(m == 2){for(int i = 0;i < n;i++){
        for(int j= 0;j < 2;j++){
          cout << b[i][j] << " ";
        }
          cout << endl;
     } 
    }
    else{
    	for(int i = 0;i < 2;i++){
           for(int j= 0;j < m;j++){
            cout << b[j][i] << " ";
          }
          cout << endl;
        } 
    }
}

int done[51][51] = {0};
int a[51][51];
int n,m;

bool ok(int x,int y){
	 return x > 0 and y > 0 and x < 51 and y < 51;
}

void assign(int x,int y){
     set<int> c;
     for(int d1 = -2;d1 <= 2;d1++){
     	for(int d2 = -2;d2 <= 2;d2++){
            if(abs(d1)+abs(d2) != 2 || !ok(x+d1,y+d2))continue;
            if(done[x+d1][y+d2]){c.insert(a[x+d1][y+d2]);}
     	}
     }
     int haha = 1;
    // cout << haha << " ";
     while(1){
     	if(c.find(haha) != c.end())haha++;
     	else break;
     }
     a[x][y] = haha;
     done[x][y] = 1;
} 

void ini(){
	REP(i,51){
		REP(j,51)done[i][j] = 0;
	}
}

void do50(){
  ini();
	RE(i,50){
		RE(j,50){
           assign(i,j);
           //cout << "here";
		}
		//cout << endl;
	}
}

void solve(){
	 //int n,m;
	 cin >> n >> m;
	 if(min(n,m) == 2){do2(n,m);return;}
	 if(min(n,m) == 1){do1(n,m);return;}
	 else{
	 	do50();
    cout << 4 << endl;
    RE(i,n){
      RE(j,m){
         cout << a[i][j] << " ";
      }
      cout << endl;
    }
	 	return;
	 }

}

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  //freopen(".in","r",stdin);freopen(".out","w",stdout);
  int t = 1;cin >> t;
  do50();
  while(t--)solve();
  return 0;
}