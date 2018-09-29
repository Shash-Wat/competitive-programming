#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define f first
#define s second 
#define int long long
 
int n,q,typ,i,j,k,te;
int lazy[400001],t[400001];
 
void lazyify(int node,int a,int b,int start,int end,int val){
     if(lazy[node] != 0){
        t[node] += (lazy[node]*((end-start)+1));
        if(start != end){
            lazy[node*2] += lazy[node];
            lazy[(node*2) + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if(start > b || end < a)return;
    if(start >= a && b >= end){
        t[node] += val*(end-start+1);
         if(start != end){
            lazy[node*2] += val;
            lazy[(node*2) + 1] += val;
        }
        return;
    }
    int mid = (start+end)/2;
    lazyify( (2*node),a,b,start,mid,val);
    lazyify( (2*node) + 1,a,b,mid+1,end,val);
    if(start != end)t[node] = t[2*node]+t[(2*node) + 1];
    return;
}
 
int query(int node,int a,int b,int start,int end){
    if(lazy[node] != 0){
        t[node] += (lazy[node]*((end-start)+1));
        if(start != end){
            lazy[node*2] += lazy[node];
            lazy[(node*2) + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if(start > b || end < a)return 0;
    if(start >= a && b >= end){
        return t[node];
    }
    int mid = (start+end)/2;
    return query(2*node,a,b,start,mid)+query((2*node) + 1,a,b,mid+1,end);
}
 
signed main() {
    cin >> te;
    while(te--){
       cin >> n >> q;
       for(i = 1;i < 4*n;i++){t[i] = 0;lazy[i] = 0;}
       while(q--){
       cin >> typ;
         if(typ == 0){
           cin >> i >> j >> k;
           i--;
           j--;
           lazyify(1,i,j,0,n-1,k);
         }
         if(typ == 1){
             cin >> i >> j;
             i--;
             j--;
             cout << query(1,i,j,0,n-1) << endl;
         }
       }
     
    }
	return 0;
} 