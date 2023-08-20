#include<bits/stdc++.h>
#define LL             long long
#define II             pair<int,int>
#define PLL            pair<LL,LL>
#define VI             vector<int>
#define VVI            vector<VI>
#define VLL            vector<LL>
#define VII            vector<II>
#define VVLL           vector<VLL>
#define VVII           vector<vector<II>>
#define VPLL           vector<pair<LL,LL>>
#define VS             vector<string>
#define VB             vector<bool>
#define VVB            vector<VB>
#define MMS0(a)        memset(a,0,sizeof(a))
#define MMS1(a)        memset(a,-1,sizeof(a))
#define AR             array
#define PB             push_back
#define FF             first
#define SS             second
#define FOR(n)         for(int i=0;i<n;i++)
#define RFOR(n,a)      for(int i=n;i>=a;i--)
#define LOOP(i,a,n,c)    for(int i=a;i<n;i+=c)
#define RLOOP(i,n,a,c)   for(int i=n;i>a;i-=c)
#define DEB1(a)        cout<<#a<<" "<<a<<"\n"
#define DEB2(a,b)      cout<<#a<<" "<<a<<" "<<#b<<" "<<b<<"\n"
#define DEB3(a,b,c)    cout<<#a<<" "<<a<<" "<<#b<<" "<<b<<" "<<#c<<" "<<c<<"\n"
#define MOD7           (LL)1e9+7
#define MOD9           (LL)1e9+9
#define INF            (LL)1e9
#define INFL            (ll)1e18
#define PV(v)          for(auto it:v)cout<<it<<" ";cout<<"\n"
#define PMP(v)         for(auto it:v)cout<<it.ff<<":"<<it.ss<<" ";cout<<"\n"           
#define LB            lower_bound
#define UB            upper_bound
#define _              0
#define FIO            ios_base::sync_with_stdio(false);cin.tie(NULL)
#define ALL(a)         a.begin(),a.end()
#define PPB            pop_back
#define MKP            make_pair

using namespace std;

int X[8] = {0,1,0,-1,1,-1,1,-1};
int Y[8] = {1,0,-1,0,1,1,-1,-1}; 

bool isValid(int i, int j,int n,int m) {
    if(i < 0 || j < 0 || i >= n || j >= m) return false;
    return true;
}

VVI edges;
VVII graph;
VVII weightedGraph;
VVLL matrix;

int main() {
    int n,m;
    cin>>n>>m;
    
    VVII G(n + 1, VII{});
    
    FOR(m) {
        int u,v;
        cin>>u>>v;
        G[u].PB(MKP(v,i));
        G[v].PB(MKP(u,i));
    }

    // if degree is odd then just return.
    LOOP(i, 1, n + 1 , 1) if( G[i].size() & 1) {
        cout<<"IMPOSSIBLE";
        return 0;
    }

    // checking the path.
    stack<int> stk;
    stk.push(1);
    VB visited(m + 1, false); // using visited for edge not for verted.
    VI path;
    while(!stk.empty()) {
        bool hasOneEdge = false;
        int u = stk.top();
        while(!G[u].empty()) {
            auto P = G[u].back();G[u].PPB(); 
            int v = P.FF;
            int i = P.SS;
            if(!visited[i]) {
                stk.push(v);
                visited[i] = true;
                hasOneEdge = true;
                break;
            }
        }
        if(!hasOneEdge) {
            path.PB(u);
            stk.pop(); 
        }
    }
    if(path.size() != m + 1) {
        cout<<"IMPOSSIBLE";
    }else{
        for(auto it:path) cout<<it<<" ";
    }
    return 0;
}