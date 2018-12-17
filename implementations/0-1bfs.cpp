#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define s second
#define f first

int t,n,m,i,j,k,l;
char a[1001][1001];
int dist[1001][1001];

bool ok(int x,int y){
    if(x > n || y > m)return 0;
    if(y < 1 || x < 1)return 0;
    return 1;
}

bool cost(int x,int y,int x1,int y1){
    return (!(a[x][y] == a[x1][y1]));
}


int main() {
    cin >> t;
    while(t--){
        cin >> n >> m;
        for(i = 1;i <= n;i++){
            for(j = 1;j <= m;j++){
                cin >> a[i][j];
                dist[i][j] = -1;
            }
        }
        deque< pair<int,int> > q;
        q.push_front(mp(1,1));
        dist[1][1] = 0;
        while(!q.empty()){
             int x = q.front().f;
             int y = q.front().s;
             q.pop_front();
             //cout << x << " " << y << endl;
             for(i = x-1;i <= x+1;i++){
                 for(j = y-1;j <= y+1;j++){
                     if( (abs(i-x)+abs(j-y)) != 1)continue;
                     if(!ok(i,j))continue;
                     if(dist[i][j] != -1 && (dist[i][j] <= cost(x,y,i,j)+dist[x][y]))continue;
                     dist[i][j] = dist[x][y]+cost(x,y,i,j);
                     if(cost(x,y,i,j))q.push_back(mp(i,j));
                     if(!cost(x,y,i,j))q.push_front(mp(i,j));
                 }
             }
        }
       /* for(i = 1;i <= n;i++){
            for(j = 1;j <= m;j++){
                cout << dist[i][j] << " ";
            }
            cout << endl;
        }*/        
        cout << dist[n][m] << endl;
    }
	return 0;
}