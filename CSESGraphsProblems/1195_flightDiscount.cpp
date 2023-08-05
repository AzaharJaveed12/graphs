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
Identified by : minimum distance to reach destination and there is only one source.
                there is no negative cycle. So Diskjstra algorithm works.
So This is :  Diskjistra algorithm.

Approach :
    maintain two dimentional distance array.
    
    dist[v][used] = (dist[u][used] + w,dist[v][used]);
        1. till discount is not used: dist[v][false] = (dist[u][false] + w,dist[v][false]);
        2. after discount used: dist[v][true] = (dist[u][true] + w,dist[v][true]);
    if(!used) dist[v][true] = max(dist[u][false] + w/2,dist[v][true]);

    in both cases pushing tp pq is common..
*/
void disjistra(int n) {
    LL dist[n + 1][2];
    LOOP(i,0,n + 1, 1) LOOP(j , 0 , 3,1) dist[i][j] = 1e16;
    
    dist[1][0] = 0;
    dist[1][1] = 0;

    priority_queue<VLL,VVLL,greater<VLL>> pq; // dist,u,discountUsed

    pq.push({0,1,0});

    while(!pq.empty()) {
        VLL top = pq.top(); pq.pop();
        LL d = top[0] , u = top[1] , used = top[2];

        if(dist[u][used] < d) continue;

        for(II node: weightedGraph[u]) {
            int v = node.FF;
            LL w = node.SS;

            // not using discout here.
            if(dist[v][used] > d + w) {
                dist[v][used] = d + w;
                pq.push({dist[v][used],v,used});
            }

            // if discount is not used then we can use that discount.
            if(!used && dist[v][true] > dist[u][false] + w/2) { // d is nothing but dist[u][false]
                dist[v][true] = dist[u][false] + w/2;
                pq.push({dist[v][true],v,1});
            }
        }
    }
    cout<<dist[n][1];
}

int main() {
    int n,m;
    cin>>n>>m;
    readEdgesAndCreatGraph(n,m,true,true);
   // printGraph(n,true);
    disjistra(n);
    return 0;
}