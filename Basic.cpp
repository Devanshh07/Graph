#include<iostream>
#include<bits/stdc++.h>
using namespace std;
/*
 1.total degree of a graph is 2 * E[no of edges]
*/

//REPRESENTATION WITH ADJANCENCY LIST
class graph {
public:

 unordered_map<int,list<int>> adj;

 void addEdge(int u,int v,bool direction){
    //if direction == 0 -> undirected Graph
    //if direction == 1 -> directed graph
    adj[u].push_back(v);
    if(direction==0){
        adj[v].push_back(u);
    }
 }
 void PrintEdge(){
    for (auto i: adj){
        cout<<i.first<<"-> ";
        for(auto j: i.second){
           cout<<j<<" , ";
        }
        cout<<endl;
        
    }
    cout<<endl;
 }

};
 //BFS = Breadth First Search  
 //here V is the number of node 
 // adj is the Ad lIST 
 vector<int> bfsOfGraph(int V, vector<int> adj[]) {
        // Code here
        int vis[V] = {0};
        vis[0] = 1;
        queue<int> q;
        q.push(0);
        vector<int> bfs;
        
        while(!q.empty()){
            int node = q.front();
            q.pop();
            bfs.push_back(node);
            for(auto it: adj[node]){
                if(!vis[it]){
                    vis[it] = 1;
                    q.push(it);
                }
            }
        }
        return bfs;
    }

//DFS -> defth first Search [deep->deep->deep(recursive)]

void dfs(int node,int vis[],int adj[],int &ans[]){
    vis[node] = 1;
    ans.push_back(node);
    for(auto it: adj[node]){
        if(!vis[node]){
            dfs(it,vis,adj,ans);
        }
    }
}
vector<int> dfs(int v,vector<int> adj[]){
    int vis[v] = {0};
    int start = 0;
    vector<int>ans;
    dfs(start,vis,adj,ans);
    return ans;
}

//CODE - 200 Question no of isepand;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int numIslands = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') {
                    numIslands++;
                    dfs(grid, i, j);
                }
            }
        }
        
        return numIslands;
    }
    
private:
    void dfs(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] != '1') {
            return;
        }
        
        grid[i][j] = '0'; // mark as visited
        dfs(grid, i + 1, j); // down
        dfs(grid, i - 1, j); // up
        dfs(grid, i, j + 1); // right
        dfs(grid, i, j - 1); // left
    }
};


//Detect a Cycle in a GRAPH


//USING  BFS

bool check(int src,int n,vector<int> &adj[],vector<int> &vis[]){
    vis[src] = 1;
    queue<pair<int,int>> q;
    q.push({src,-1});

    while(!q.empty()){
        int node = q.front().first;
        int parent = q.front().second;
       for(auto adj_node : adj[node]){
        if(!vis[adj_node]){
            vis[adj_node] = 1;
            q.push({adj_node,node});
        }
        if(parent!=adj_node){
                   return true;
        }
       }
        
    }
    return false;
    
}
bool detect(int v,int n,vector<int> adj[]){
    
    vector<int> vis(n,0);
    //for a component graph
    //v = no of graph or element
    for(int 0;i<v;i++){
        if(!vis[i]){
            if(check(i,vis,adj)) return true;
        }
    }
return false;
    
}

//Using DFS -> defth first Search [12]
bool dfs(int node,int parent,vector<int> adj[],int vis[]){
    vis[node] = 1;

    for(auto it: adj[node]){
        if(!vis[it]){
            if(dfs(it,node,adj,vis)==true) return true;
        }
        else if(it!=parent){
            return true;
        }
    }
return false;
}
bool(int v, vector<int> adj[]){
    int vis[v] = {0};
    for(int i=0;i<v;i++){
            if(!vis[i]){
                if(dfs(i,-1,adj,vis)==true)return true;
            }
    }
  return false;
}


//LeetCode 130 surrounded regions 
class Solution {
    private:
    void dfs(int row,int col,vector<vector<int>> &vis,vector<vector<char>>& board,int delR[],int delC[]){
     vis[row][col] = 1;
     int n = board.size();
     int m = board[0].size();


     //this all stuff is only for marking conneced component
     for(int i=0;i<4;i++){
    
            int nr = row+ delR[i];
            int nc = col+ delC[i];
            if(nr>=0 &&nr<n && nc>=0&&nc<m &&!vis[nr][nc] && board[nr][nc]=='O'){
                dfs(nr,nc,vis,board,delR,delC);
            }
     }

     //connected 

    }
public:
    void solve(vector<vector<char>>& board) {
        int n  = board.size();
        int m = board[0].size();
        vector<vector<int>> vis(n,vector<int>(m,0));

        int delR[] = {-1,0,+1,0};
        int delC[] = {0,+1,0,-1};
        // traverse from edge [1,1,last row ,last col];

        //first row
        for(int j = 0;j<m;j++){
            if(!vis[0][j] && board[0][j]=='O'){
                dfs(0,j,vis,board,delR,delC);
            }
            if(!vis[n-1][j]&& board[n-1][j]=='O'){
                dfs(n-1,j,vis,board,delR,delC);
            }
        }
        for(int i=0;i<n;i++){
            if(!vis[i][0] &&board[i][0]=='O'){
                dfs(i,0,vis,board,delR,delC);
            }
            if(!vis[i][m-1] &&board[i][m-1]=='O'){
                dfs(i,m-1,vis,board,delR,delC);
            }
        }

        //after that check all O;
        for(int i=0;i<n;i++){
            for(int j = 0;j<m;j++){
                if(!vis[i][j] && board[i][j]=='O'){
                    board[i][j] = 'X';
                }
            }
        }
        return board;
    }
    
    
};

//Clean code 

    void dfs(int i,int j,vector<vector<char>>& A)
    {
        int m=A.size(),n=A[0].size();

        if(i<0 || i>=m || j<0 || j>=n || A[i][j]!='O') 
            return;

        A[i][j]='T'; //modified with T;
 
        dfs(i+1,j,A); //this is for bottom
        dfs(i,j+1,A); //right
        dfs(i-1,j,A); //top
        dfs(i,j-1,A); //left
    }

public:
    void solve(vector<vector<char>>& A) {
        int m=A.size(),n=A[0].size();

        // Traverse Borders
        queue<pair<int,int>> q;
        for(int i=0;i<m;i++){
            if(A[i][0]=='O')dfs(i,0,A);
            if(A[i][n-1]=='O')dfs(i,n-1,A);
        }
        
        for(int j=1;j<n-1;j++){
            if(A[0][j]=='O')dfs(0,j,A);
            if(A[m-1][j]=='O')dfs(m-1,j,A);
        }

        
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                if(A[i][j]=='T')A[i][j]='O';
                else if(A[i][j]=='O')A[i][j]='X';
    }




//no of Enclaves 1020 leetCode
 //DFS
    void dfs(int i,int j,vector<vector<int>>& A)
    {
        int m=A.size(),n=A[0].size();
        if(i<0 || i>=m || j<0 || j>=n || A[i][j]!=1) return;

        A[i][j]=0;

        dfs(i+1,j,A);
        dfs(i,j+1,A);
        dfs(i-1,j,A);
        dfs(i,j-1,A);
    }

public:
    int numEnclaves(vector<vector<int>>& A) 
    {
        int m=A.size(),n=A[0].size();

        // Traverse Borders
        queue<pair<int,int>> q;
        for(int i=0;i<m;i++){
            if(A[i][0])dfs(i,0,A);
            if(A[i][n-1])dfs(i,n-1,A);
        }
        
        for(int j=1;j<n-1;j++){
            if(A[0][j])dfs(0,j,A);
            if(A[m-1][j])dfs(m-1,j,A);
        }

        int count=0;
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                if(A[i][j])count++;
        
        return count;
    }


    //using bfs
    public:
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n,vector<int>(m,0));
       
        queue<pair<int,int>> q;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(i==0||j==0||j==m-1||i==n-1){
                    if(grid[i][j]==1){
                        q.push({i,j});
                        vis[i][j] = 1;
                    }
                }
            }
        }
        int delR[] = {-1,0,+1,0};
        int delC[] = {0,+1,0,-1};


        while(!q.empty()){
            int row = q.front().first;
            int col = q.front().second;
            q.pop();

            for(int i=0;i<4;i++){
                int nr = row + delR[i];
                int nc = col+delC[i];
                if(nr>=0 && nr<n&&nc>=0&&nc<m&& grid[nr][nc]==1 && vis[nr][nc]==0){
                    q.push({nr,nc});
                    vis[nr][nc] = 1;
                }
            }

        }


       int cnt = 0;

        for(int i=0;i<n;i++){
            for(int j = 0;j<m;j++){
                if(grid[i][j]==1 && !vis[i][j]){
                    cnt++;
                }
            }
        }
 
      return cnt;
    }


//biptrate Graph [biptrate graph is nothing but containing 0 and 1 alternate color ]

/*Using BFS*/
class BiptrateGraph{
    private: 
    bool check(int start,int v,vector<int> adj[],int col[]){
        col[start] = 0;
        q.push(start);

        while(!q.empty()){
            int node = q.front();
            for(auto it: adj[node]){
                if(col[it]== -1){
                    col[it] = !col[node];
                    q.push(it);
                }
                else if(col[it]==col[node]){
                    return false;
                }
            }
        }
        return true;
    }
public:
	bool isBipartite(int V, vector<int>adj[]){
	    // Code here
	    int col[V];
	    for(int i=0;i<V;i++) col[i] = -1;
	   
	   for(int i = 0;i<V;i++){
	       if(col[i]==-1){
	           if(check(i,V,adj,col)==false){
	               return false;
	           }
	       }
	   }
	   return true;
	    
	}

};

//using DFS

void dfs(int node ,int col,int color[],vector<int> adj[]){
    color[node] = col;

    for(auto it : adj[node]){
         if(color[it]==-1){
            if(dfs(it,!col,color,adj) == false )return false;
         }
         else if(color[it]==col){
            return true;
         }

    }
    return true;
}
bool bipotite(int v,vector<int> adj[]){
    int color[v];
    for(int i=0;i<v;i++) color[i] = -1;
    for(int i = 0;i<v;i++){
        if(color[i]==-1){
            if(dfs(i,0,col,adj)==false) return false;
        } 
    }
    return true;
}
//G-19 Detect a cycle in a directed Graph

//now this is all stuff for detecting a cycle in a Directed graph(notice that DIRECTED)

bool dfs(int node,int vis[],int path[],int adj[]){
    vis[node] = 1;
    path[node] = 1;

    for(auto it: adj[node]){
        
        if(!vis[it]){
            if(dfs(it,vis,path,adj)==true) return true;
        }
        else if(path[it]) return true;

    }

    path[node] = 0; //while returning -> unmarked the path 
    return false;
} 
bool detectAcycle(int V,vector<int> adj[]){
    
    int vis[v] = {0};
    int path[v] = {0};
   
   //loop for component of a graph
    for(int i = 1;i<v;i++){
         if(!vis[i]){
            if(dfs(i,vis,path,adj)==false) return false;
         }
         
    }
    return true;

}

//Eventual Safe States problem 
 //https://www.geeksforgeeks.org/problems/eventual-safe-states/1
 //https://leetcode.com/problems/find-eventual-safe-states/description/

 //Descriptions -> all node whos does not have a cycle is SafeNode


 bool dfs(int node ,int vis[],int path[],int check[],int adj[]){
    vis[node] = 1;
    path[node] = 1;
    check[node] = 0;
    for(auto it : adj[node]){
        if(!vis[it])
        if(dfs(it,vis,path,check,adj)==true) {
            check[it] = 0; //if cycle not be a safe node
            return true;
        }
        if(path[it]){
            check[it] = 0; //if cycle not be a safe node
            return true;
        }
    }

   //if no cycle code is come this side and mark all safe node to 1

    check[node] = 1;
    path[node] = 0;
    return false;
 }

 vector<int> SafeNode(int v,vector<int> adj[]){
    int vis[v] = {0};
    int path[v] = {0};
    int check[v] = {0};
    vector<int> safe;

    for(int i= 0;i<v;i++){
        if(!vis[i]){
            dfs(i,vis,path,check,adj)
            
        }
    }

    //check arry with value 1 have a safe node , put it into the safe vector and returm\n
    for(int i = 0;i<v;i++){
        if(check[i]==1){
            safe.push_back(i);
        }
    }
    return safe; //return
 }

 // Eventual Safe Node Problem
 class Solution {
public:

    bool dfs(int node, vector<int>& visited, vector<vector<int>>& graph){
        
        visited[node] = 2;
        for(auto it : graph[node]){
            if(!visited[it]){
                if(dfs(it, visited, graph) == true){
                    return true;
                }
            }
            else if(visited[it] == 2){
                return true;
            }
        }
        visited[node] = 1;
        return false;
    }
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        
        int V = graph.size();

        vector<int> visited(V, 0);
        
        for(int i = 0;i<V;i++){
            if(!visited[i]){
                dfs(i, visited, graph);
            }
        }

        vector<int> safe_nodes;
        
        for(int i = 0;i<V;i++){
            if(visited[i] == 1){
                safe_nodes.push_back(i);
            }
        }

        return safe_nodes;
    }
};





 // TOPOLOGICAL SORTING 
  
  //Topological sorting for Directed Acyclic Graph (DAG) is a
  // linear ordering of vertices
  // such that for every directed edge u-v, vertex u comes before v in the ordering.

  //Note: Topological Sorting for a graph is not possible if the graph is not a DAG.

  //DAG - directed acyclic graph

  //DAGs are a special type of graphs in which each edge is directed such that no cycle exists in the graph

  //
  
class topologica_Sort{
    private:
     void dfs(int node,vector<int> &vis,stack<int> &st,vector<int> adj[]){
        //visit current node;
        vis[node] = 1;

        for(auto it: adj[node]){
            if(!vis[it]){
                dfs(it,vis,st,adj);
            }
        }

     st.push(node);

     }
    public:

   vector<int> topo(int V,vector<int> adj[]){
             
        vector<int> v(V,0);
        vector<int> ans;
        stack<int> st;

        //for component Graph;
        for(int i=0;i<V;i++){
            if(!vis[i]){
                dfs(i,vis,st,adj);
            }
        }
        
        //store from top into ans DS;
        while(!st.empty()){
            ans.push_back(st.top());
            st.pop();
        }
        return ans;

   }



};


//KAHN'S AlgoriThm -> it is for TopoLogical Sorting 

//Topological Sorted order: It is a linear ordering of vertices such that
// for every directed edge u -> v
//where vertex u comes before v in the ordering.

//[link gfg refrence ] -> https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/

/*
Algo->>
 1. all nodes having inDegree 0 put it into the queue
 
*/

class KahnsAlgo{
    public:

    vector<int> topoSort(int v,vector<int> adj[]){

        int indegree[v] = {0};
        for(int i=0;i<v;i++){
            for(auto it : adj[i]){
                indegree[it]++;
            }
        }
        //indegree is ready

        queue<int> q;
        for(int i = 0;i<V;i++){
            if(indegree[i]==0){
                q.push(i);
            }
        }

        //q is ready with node having indegree 0;

        vector<int> topo;

        while(!q.empty()){
            int node = q.front();
            q.pop();
            topo.push_back(node);
            for(auto it: adj[node]){
                indegree[it]--;
                if(indegree[it]==0){
                    q.push(it);
                }
            }
        }
        return topo;

    }

};


//Cycle detection using KAhn algo

/* as we know that topoSort algorithm is only for Directed Acyclic graph 
   if we try this algorithm in a Directed graph our TopoSort is not fill */

class CycleDetectUsingKHANs{
     public:

     bool cycle(int v,vector<int> adj[]){
        int indegree[v] = {0};
        //create indegree
        for(int i=0;i<v;i++){
            for(auto it: adj[i]){
                indegree[it]++;
            }
        }
        queue<int> q;

        for(int i=0;i<v;i++){
                if(indegree[i]==0){
                    q.push(i);
            }
        }
    vector<int> topo;
         while(!q.empty()){
            int node = q.front();
            q.pop();
            topo.push(node);
            for(auto it: adj[node]){
                indegree[it]--;
                if(indegree[it]==0) q.push(it);
            }
         }
     }
     int n = topo.size();
     if(n == v) return false;
     return true;
 
   };


//Course Shedule I & II Problem
// Course Shedule 2 -> https://leetcode.com/problems/course-schedule-ii/
//Course Shedule 1 -> https://leetcode.com/problems/course-schedule/

//using topoSort algoRithm
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int N=numCourses;
        vector<int>adj[N];
        for(auto it:prerequisites){
            adj[it[1]].push_back(it[0]);
        }
        int inDegree[N];
        for(int i=0;i<N;i++){
            inDegree[i]=0;
        }
        for(int i=0;i<N;i++){
            for(auto it:adj[i]){
                inDegree[it]++;
            }
        }
        queue<int>q;
        for(int i=0;i<N;i++){
            if(inDegree[i]==0){
                q.push(i);
            }
        }
        vector<int>ans;
        while(!q.empty()){
            int node=q.front();
            q.pop();
            ans.push_back(node);
            for(auto it:adj[node]){
                inDegree[it]--;
                if(inDegree[it]==0){
                    q.push(it);
                }

            }
        }
        if(ans.size()==N)return ans;
        return {};
        
    }
};

//Alien Dictionary 

//https://www.geeksforgeeks.org/problems/alien-dictionary/1
class Solution{
    private:
    vector<int> topoSort(int v,vector<int> adj[]){

        int indegree[v] = {0};
        for(int i=0;i<v;i++){
            for(auto it : adj[i]){
                indegree[it]++;
            }
        }
        //indegree is ready

        queue<int> q;
        for(int i = 0;i<v;i++){
            if(indegree[i]==0){
                q.push(i);
            }
        }

        //q is ready with node having indegree 0;

        vector<int> topo;

        while(!q.empty()){
            int node = q.front();
            q.pop();
            topo.push_back(node);
            for(auto it: adj[node]){
                indegree[it]--;
                if(indegree[it]==0){
                    q.push(it);
                }
            }
        }
        return topo;

    }
    public:
    string findOrder(string dict[], int N, int K) {
        //code here
        vector<int> adj[K];
        
        for(int i=0;i<N-1;i++){
            
            string s1 = dict[i];
            string s2 = dict[i+1];
            int len = min(s1.size(),s2.size());
            for(int ptr = 0;ptr<len;ptr++){
                if(s1[ptr]!=s2[ptr]){
                    adj[s1[ptr]-'a'].push_back(s2[ptr]-'a');
                    break;
                }
            }
        }
        vector<int> topo = topoSort(K,adj);
        string s ="";
        for(auto it: topo){
            s = s + char(it+'a');
        }
        return s;
        
    }
};

int main(){
graph g;


int m;
int n;
cout<<"enter number of node : ";
cin>>n;
cout<<"enter number of edge : ";
cin>>m;

for(int i=0;i<m;i++){
    int u,v;
    cin>>u>>v;
    g.addEdge(u,v,0);
}
g.PrintEdge();




return 0;

};
