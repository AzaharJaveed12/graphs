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
        map<II,int> mp; // uv --> weight
        weightedGraph.assign(n + 1,VII{});
        while(m--){
            int u,v,w;
            cin>>u>>v>>w;
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
    graph.assign(V,VI{});
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

/* 
************************* SOLUTION STARTS HERE ****************************
Identified by : 
 1. We need to find the shortest path from source to destination
 2. There are no negative edges.

So This is : Disjistra algorithm problem.

NOTE: GOT TLE IF WE DONT USE : if(dist[u] < d) continue;
    because, we already explored with better node so we dont wana explore with d any more..!!

*/

void dijkstraAlgorithm(int n) {
    int source = 1;
    priority_queue<PLL,VPLL,greater<PLL>> pq;
    
    pq.push({0,source});
    VLL dist(n + 1, 1e17);
    dist[1] = 0;

    while(!pq.empty()) {
        PLL top = pq.top(); pq.pop();
        int u = top.SS;
        LL d = top.FF;
        if(dist[u] < d) continue;
        for(PLL v:weightedGraph[u]) {
            LL vDistance = v.SS;
            int vNode = v.FF;
            if( d + vDistance < dist[vNode]) {
                dist[vNode] = d + vDistance;
                pq.push(MKP(dist[vNode],vNode));
            }
        }
    }

    LOOP(i,1,n + 1, 1) cout<<dist[i]<<" ";
}

int main() {
    FIO;
    int n,m;
    cin>>n>>m;
    
    map<II,int> mp;
    LOOP(i,0,m,1) {
        int u,v,w;
        cin>>u>>v>>w;
        if(mp.count(MKP(u,v))) {
            mp[MKP(u,v)] = min(w,mp[MKP(u,v)]);
        }else{
            mp[MKP(u,v)] = w;
        }
    }

    VVI edgesWithoutDuplicateNodes;
    for(auto it:mp) {
        edgesWithoutDuplicateNodes.PB({it.FF.FF,it.FF.SS,it.SS});
    }

    createWeightedGraphFromEdges(n,edgesWithoutDuplicateNodes,true);
  //  printGraph(n,true);
    dijkstraAlgorithm(n);
    return 0;
}