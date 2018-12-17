/*input
5 1
1 1 -100
1 1 100
2 1 200000
1 1 10000000
3 1
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

int zero= 0;

struct node{
	int l,r,lazy1,lazy2,hist1,hist2,leftbest,rightbest;
  node *left,*right;
  node(){
    left = NULL,right = NULL;
    l = 1;
    r = 1<<30;
    hist1 = lazy2 = lazy1 = hist2 =leftbest=rightbest= 0;
  }
  void extend(){
    if(left == NULL){
      left = new node();
      right = new node();
      left->l = l;
      right->r = r;
      int mid = (l+r)/2;
      left->r = mid;
      right->l = mid+1;
    }
  }
};

void pushdown(node *tmp){
     if(tmp->l == tmp->r)return;

     tmp->left->leftbest = max(tmp->left->leftbest+tmp->lazy1,zero);
     tmp->left->rightbest = max(tmp->left->rightbest+tmp->lazy2,zero);
     tmp->right->leftbest = max(tmp->right->leftbest+tmp->lazy1,zero);
     tmp->right->rightbest = max(tmp->right->rightbest+tmp->lazy2,zero);

     tmp->left->hist1 = max(tmp->hist1+tmp->left->lazy1,tmp->left->hist1);
     tmp->left->lazy1 += tmp->lazy1;
     tmp->left->hist2 = max(tmp->hist2+tmp->left->lazy2,tmp->left->hist2);
     tmp->left->lazy2 += tmp->lazy2;
     tmp->right->hist1 = max(tmp->hist1+tmp->right->lazy1,tmp->right->hist1);
     tmp->right->lazy1 += tmp->lazy1;
     tmp->right->hist2 = max(tmp->hist2+tmp->right->lazy2,tmp->right->hist2);
     tmp->right->lazy2 += tmp->lazy2;
     tmp->lazy1 = 0;
     tmp->lazy2 = 0;
     tmp->hist1 = 0;
     tmp->hist2 = 0;
} 

//whi = 0 means prefix
void lazyify(node *cur,int l,int r,int x,bool whi){
     cur->hist1 = max(cur->hist1,cur->lazy1);
     cur->hist2 = max(cur->hist2,cur->lazy2);
     cur->extend();
     pushdown(cur);
     //break condition
     if(r < cur->l || l > cur->r)return;
     if(cur->l >= l && cur->r <= r){
       if(!whi){
         cur->lazy1 += x;
         if(cur->l == cur->r){
            cur->leftbest = max(zero,cur->leftbest+x);
            cur->hist1 = max(cur->hist1,cur->lazy1); 
            return;
         }
         int fu = 0;
         cur->hist1 += max(x,fu);
        // pushdown(cur);
       }
       else{
         cur->lazy2 += x;
         if(cur->l == cur->r){
           cur->rightbest = max(zero,cur->rightbest+x);
            cur->hist2 = max(cur->hist2,cur->lazy2); 
            return;
         }
         int fu = 0;
         cur->hist2 += max(x,fu);
         //pushdown(cur);
       }
       //pushdown(cur);
       return;
     }
     if(cur->left != cur->right){
     lazyify(cur->left,l,r,x,whi);
     lazyify(cur->right,l,r,x,whi);
     }
     return;
}

int haha1 = 0,haha2 = 0;

int query(node *cur,int ind,bool whi){
    cur->hist1 = max(cur->hist1,cur->lazy1);
    cur->hist2 = max(cur->hist2,cur->lazy2);
    cur->extend();
    pushdown(cur);
    if(ind < cur->l || ind > cur->r)return 0;
    if(cur->l == cur->r && cur->r == ind){
      /*debug(cur->hist1);
      if(cur->lazy2 > 0){
        cur->lazy2 = 0;
        cur->hist2 += cur->lazy2;
      }
      if(cur->lazy1 > 0){
        cur->lazy1 = 0;
        cur->hist1 += cur->lazy1;
      }
      */
      if(whi){haha1 = cur->rightbest;return max(cur->lazy2,cur->hist2);}
      else{haha2 = cur->leftbest; return max(cur->lazy1,cur->hist1);}
    }
    return max(query(cur->left,ind,whi),query(cur->right,ind,whi));
}

node *root;
int q,k,ans = 0;
int onee = 1;

signed main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  cin >> q >> k;
  root = new node();
  while(q--){
    int b,C,d;
    cin >> b >> C;
    int c = C^ans;
    if(b == 1){
       cin >> d;
       lazyify(root,max(onee,c-k),min((int)1e9,c+k),d,0);
    } 
    if(b == 2){
       cin >> d;
       lazyify(root,max(onee,c-k),min((int)1e9,c+k),d,1);
    }
    if(b == 3){
      //  cout << endl;
       int one = query(root,c,0);
       int two = query(root,c,1);
       ans = one+two;
       //int fu = 0;
       ans = max(ans,max(haha1,haha2));
       assert(ans >= 0);
       cout << ans << endl;
    }
  }
  return 0;
}
