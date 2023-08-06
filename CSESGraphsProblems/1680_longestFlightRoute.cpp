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
VVI graph;
VVII weightedGraph;
VVLL matrix;
 
void readEdges(int M,bool isWeighted) {
    FOR(M) {
        int u,v,weight = 0;
        cin>>u>>v;
        if(isWeighted) {
            cin>>weight;
        }
        edges.PB(VI{u,v,weight});
    }
}
 
void readEdgesAndCreatGraph(int n,int m,bool isWeighted,bool isDirected) {
    if(isWeighted) {
        weightedGraph.assign(n + 1,VII{});
        while(m--){
            int u,v,w = 1;
            cin>>u>>v;
            weightedGraph[u].PB(MKP(v,w));
            if(!isDirected) weightedGraph[v].PB(MKP(u,w));
        }
    }else{
        graph.assign(n + 1,VI{});
        while(m--){
            int u,v;
            cin>>u>>v;
            graph[u].PB(v);
            if(!isDirected) graph[v].PB(u);
        }
    }
}
 
void printGraph(int V, bool isWeighted) {
    cout<<"\n";
    cout<<"*****************  Printing Graph started: **********************\n";
    LOOP(u,0,V + 1,1) {
        cout<<u<<" : ";
        if(isWeighted) {
            LOOP(v,0,weightedGraph[u].size(),1) cout<<"(v:"<<weightedGraph[u][v].FF<<", W:"<<weightedGraph[u][v].SS<<") ";
            cout<<"\n";
        }else{
            LOOP(v,0,graph[u].size(),1) cout<<graph[u][v]<<" ";
            cout<<"\n";
        }
    }
    cout<<"*****************  Printing Graph Ended **********************\n\n";
}
 
void createGraphFromEdges(int V,VVI &edges,bool isDirected) {
    graph.assign(V + 1,VI{});
    for(VI edge:edges) {
        graph[edge[0]].PB(edge[1]);
        if(!isDirected) graph[edge[1]].PB(edge[0]);
    }
}
 
void createWeightedGraphFromEdges(int V,VVI &edges,bool isDirected) {
    weightedGraph.assign(V + 1,VII{});
    for(VI edge:edges) {
        weightedGraph[edge[0]].PB(MKP(edge[1],edge[2]));
        if(!isDirected) weightedGraph[edge[1]].PB(MKP(edge[0],edge[2]));
    }
}
 
void readAndCreateAdjMatrix(int n,int m,bool isDirected) {
    matrix.assign(n + 1 , VLL(n + 1 , INT_MAX));
 
    FOR(m) {
        LL u,v,w;
        cin>>u>>v>>w;
        matrix[u][v] = min(w,matrix[u][v]);
        if(!isDirected) matrix[v][u] = min(w,matrix[v][u]); 
    }
}
 
/* 
************************* SOLUTION STARTS HERE ****************************
Identified by :
So This is : 
 
*/
 void dijkistra(int n) {
    VI dist(n + 1 , -1e9);
    dist[1] = 0;
    VI parent(n + 1,0);
    parent[1] = 0;
    priority_queue<II,VII,greater<II>> pq;
    pq.push({0,1});
    while(!pq.empty()) {
        II top = pq.top(); pq.pop();
        int d = top.FF;
        int u = top.SS;
        if(dist[u] > d) continue;
        for(II node:weightedGraph[u]) {
            int v = node.FF, w = node.SS;
            if(dist[v] < d + w) {
                dist[v] = d + w;
                parent[v] = u;
                pq.push({dist[v],v});
            }
        }
    }
    
    if(dist[n] == -1e9) {
        cout<<"IMPOSSIBLE";
        return;
    }
    
    stack<int> ans;
    int u = n;
    while(u != 0) {
        ans.push(u);
        u = parent[u];
    }
    cout<<ans.size()<<"\n";
    while(!ans.empty()) {
        cout<<ans.top()<<" ";
        ans.pop();
    }
 }
 
int main() {
    int n,m;
    cin>>n>>m;
    readEdgesAndCreatGraph(n,m,true,true);
    dijkistra(n);
    return 0;
}