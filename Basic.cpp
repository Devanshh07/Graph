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
