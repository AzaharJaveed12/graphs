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
/*
    This is direct question of euliran path.
    used stack instead of DFS as stacks can reduce stackover flow problem as memory is allocated in 
    heap memory.

    corner ccases: 
        impossible cases:
            1. outdegree[1] - outdegree[1] != 1
            2. indegree[n] - indegree[n] != 1
            3. if any intermidates nodes whose indegree[i] != outdegree[i]
            4. when we have disconected componenets and have edges in that comoponents.
        
        possible case steps folowed.
            1. pushed 1 into stack.
            2. till stack become empty:
                    take top element.
                    till any adjecnet has elements :
                        we will iterate and find one edge whose adj is not visited and remove it
                        mark it as visited and pop it from adjecency list and then break loop.
                    if we dont find any adjecente edge which is not visited then we just add this
                    element into PATH and pop this element into stack.
                    (simply this is the end when we have nothing to explore more soo added this.)
            3. now path has our answer. 
*/
int main() {
    int n,m;
    cin>>n>>m;
    
    VVII G(n + 1, VII{});
    VII degree(n + 1 , II{}); // in , out
    FOR(m) {
        int u,v;
        cin>>u>>v;
        G[u].PB(MKP(v,i));
        degree[u].SS++;
        degree[v].FF++;
    }

    // outdegree of 1 should be odd and indegree of n should be even.
    LOOP(i,2, n , 1) if(degree[i].FF != degree[i].SS) {
        cout<<"IMPOSSIBLE";
        return 0;
    }

    if(!(degree[1].SS - degree[1].FF == 1) || !(degree[n].FF - degree[n].SS ==  1)) {
       // DEB2(degree[1].FF,degree[1].SS);
      //  DEB2(degree[n].FF,degree[n].SS);
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
    reverse(ALL(path));
    FOR(m) {
        if(!visited[i]) {
            cout<<"IMPOSSIBLE";
            return 0;
        } 
    }
    for(auto it:path) cout<<it<<" ";
    return 0;
}