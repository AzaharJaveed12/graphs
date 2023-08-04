#include<bits/stdc++.h>
#define LL             long long
#define II             pair<int,int>
#define VI             vector<int>
#define VVI            vector<VI>
#define VLL            vector<LL>
#define VII            vector<II>
#define VVLL           vector<VLL>
#define VVII           vector<vector<II>>
#define VPLL           vector<pair<LL,LL>>
#define VS             vector<string>
#define VB             vector<bool>
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

// DIRECTION : URDL
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

void printGraph(int V, bool isWeighted) {
    cout<<"\n";
    cout<<"*****************  Printing Graph started: **********************\n";
    LOOP(u,0,V,1) {
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
    weightedGraph.assign(V,VII{});
    for(VI edge:edges) {
        weightedGraph[edge[0]].PB(MKP(edge[1],edge[2]));
        if(!isDirected) weightedGraph[edge[1]].PB(MKP(edge[0],edge[2]));
    }
}

// *************************   SOLUTION ANF GLOBAL VARIABLES FOR THIS PROBLEM *********
int n,m;

char getDir(int i) { 
    /*
    int X[8] = {0,1,0,-1,1,-1,1,-1};
    int Y[8] = {1,0,-1,0,1,1,-1,-1}; */
    // URDL
    if(i == 0) return 'R';
    if(i == 1) return 'D';
    if(i == 2) return 'L';
    if(i == 3) return 'U';
    return ' ';
}

string possibleAns;
bool DFS(int i,int j,VS &input,string &ans) {
    
    bool found = false;
    LOOP(dir,0,4,1) {
        if(!isValid( i + X[dir] , j + Y[dir] , n , m)) continue;
        if(input[i+X[dir]][j + Y[dir]] == '#') continue;
        
        ans += getDir(dir);
        
        if(input[i+X[dir]][j + Y[dir]] == 'B') {
            found = true;
            DEB2(ans,possibleAns);
            if(possibleAns == "") possibleAns = ans;
            if(ans.size() < possibleAns.size()) possibleAns = ans;
            return true;
        }
        
        input[i+X[dir]][j + Y[dir]] = '#';
        DFS(i + X[dir], j + Y[dir] , input,ans);
        input[i+X[dir]][j + Y[dir]] = '.';
        ans.pop_back();
    }

    return found;
}

void printAnswer(int i ,int j,vector<vector<char>> &mat) {
    string ans = "";
    while(mat[i][j] != '-') {
        int dir = mat[i][j] - '0';
        ans += getDir(dir);
        // because we are going from v --> u (added parent from u --> v)
        i -= X[dir];
        j -= Y[dir];
    }
    reverse(ALL(ans));
    cout<<ans.size()<<"\n";
    cout<<ans;
}

void BFS(int i,int j, VS &input) {
    queue<II> que;
    vector<vector<char>> parent(n,vector<char>(m,'-'));

    que.push(MKP(i,j));

    while(!que.empty()) {
        int sz = que.size();
        LOOP(s,0,sz,1) {
            II top = que.front(); que.pop();

            if(input[top.FF][top.SS] == 'B') {
                cout<<"YES\n";
                printAnswer(top.FF,top.SS,parent);
                return;
            }

            LOOP(dir,0,4,1) {
                if(!isValid(top.FF + X[dir],top.SS + Y[dir],n,m)) continue;
                if(input[top.FF + X[dir]][top.SS + Y[dir]] == '#') continue;
                
                que.push(II{top.FF + X[dir],top.SS + Y[dir]});
                parent[top.FF + X[dir]][top.SS + Y[dir]] = '0' + dir;
                if(input[top.FF + X[dir]][top.SS + Y[dir]] == '.') input[top.FF + X[dir]][top.SS + Y[dir]] = '#';
            }
        }
    }
    cout<<"NO";
}

int main() {

    FIO;
    
    cin>>n>>m;
    
    VS input(n);
    FOR(n) cin>>input[i];

    LOOP(i,0,n,1) {
        LOOP(j,0,m,1) {
            if(input[i][j] == 'A') {
                input[i][j] = '#';
                BFS(i,j,input);
                return 0;
            }
        }
    }
    return 0;
}