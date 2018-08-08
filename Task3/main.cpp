//
//  main.cpp
//  words
//
//  Created by HoaPQ on 8/4/18.
//  Copyright © 2018 HoaPQ. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>

using namespace std;

vector<string> words;
vector<vector<int>> adjA, adjB;
vector<int> parrentA;

int n;

// Doc du lieu
void readInput(){
    ifstream fileInput("sgb-words.txt");
    string s;
    while(getline(fileInput, s)){
        words.push_back(s);
    }
    n = words.size();
    cout<<"Loaded sgb-words.txt containing "<<n<<" five-letter English words."<<endl;
}

// Diem so ki tu khac nhau giua 2 tu
int countDifferences(string a, string b){
    int c = 0;
    for(int i=0;i<5;i++){
        if (a[i] != b[i]){
            c++;
        }
    }
    return c;
}

// BFS cho do thi khong trong so
void bfs(int u, vector<bool> &vis, vector<vector<int>> adj){
    queue<int> Q;
    int v;
    vis[u] = true;
    Q.push(u);
    while(!Q.empty()){
        v = Q.front();
        Q.pop();
        for(auto i: adj[v]){
            if (!vis[i]){
                Q.push(i);
                vis[i] = true;
            }
        }
    }
}

// Tim duong di ngan nhat bang BFS
void findPathBFS(int u,int v, vector<vector<int>> adj){
    queue<int> Q;
    vector<int> parrent(n,-1);
    int k;
    vector<bool> vis = vector<bool>(n,false);
    bool found = false;
    vis[u] = true;
    Q.push(u);
    while(!Q.empty()){
        k = Q.front();
        Q.pop();
        for(auto i:adj[k]){
            if(!vis[i]){
                vis[i] = true;
                Q.push(i);
                parrent[i] = k;
                if (i == v){
                    found = true;
                    break;
                }
            }
        }
        if (found){
            break;
        }
    }
    if(!found){
        cout<<"Not found the path."<<endl;
        return;
    }
    int tmp = v;
    vector<int> path;
    while(tmp != -1){
        path.push_back(tmp);
        tmp = parrent[tmp];
    }
    cout<<"The shortest path from "<<words[u]<<" to "<<words[v]<<":"<<endl;
    for(int i = path.size()-1; i >= 1;i--){
        cout<<words[path[i]]<<" -> ";
    }
    cout<<words[path[0]]<<endl;
}

// Tim duong di ngan nhat
void findPath(vector<vector<int>> adj){
    string a,b;
    bool check = false;
    int u,v;
    while(!check){
        cout<<"Nhap A: ";
        cin>>a;
        for(int i=0;i<n;i++){
            if(words[i] == a){
                u = i;
                check = true;
                break;
            }
        }
        if (check) break;
        cout<<a<<" not in the list!"<<endl;
    }
    check = false;
    while(!check){
        cout<<"Nhap B: ";
        cin>>b;
        for(int i=0;i<n;i++){
            if(words[i] == b){
                v = i;
                check = true;
                break;
            }
        }
        if (check) break;
        cout<<b<<" not in the list!"<<endl;
    }
    findPathBFS(u, v, adj);
}

// Tim so thanh phan lien thong bang BFS
void countConnected(vector<vector<int>> adj){
    vector<bool> visited = vector<bool>(n,false);
    int count = 0;
    for(int i=0;i<n;i++){
        if(!visited[i]){
            count++;
            bfs(i,visited,adj);
        }
    }
    cout<<"Graph A has "<<count<<" connected components."<<endl;
}

// Khoi tao do thi vo huong A
void initGraphA(){
    adjA = vector<vector<int>>(n);
    int count = 0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if (countDifferences(words[i], words[j]) == 1){
                adjA[i].push_back(j);
                adjA[j].push_back(i);
                count++;
            }
        }
    }
    cout<<"Graph A has "<<n<<" nodes with "<<count<<" edges."<<endl;
}

// Kiem tra xem giua 2 tu co canh noi hay khong
bool hasDirect(string a, string b){
    if (a==b)
        return false;
    bool check = false;
    for(int i=1;i<5;i++){
        check = false;
        for(int j=0;j<5;j++){
            if (a[i] == b[j]){
                b[j] = '*';
                check = true;
                break;
            }
        }
        if (!check) return false;
    }
    return true;
}

// Khoi tao do thi co huong B
void initGraphB(){
    adjB = vector<vector<int>>(n);
    int count = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if (hasDirect(words[i], words[j])){
                adjB[i].push_back(j);
                count++;
            }
        }
    }
    cout<<"Graph B has "<<n<<" nodes with "<<count<<" edges."<<endl;
}

// Khoi tao bien can cho thuat toan tarjan
int m, *num, *low, cnt=0, numSCC=0, *mark = NULL;
stack<int> S;
// Tim so thanh phan lien thong manh bang thuat toan Tarjan
void tarjan(int u){
    low[u] = num[u] = ++cnt;
    S.push(u);
    
    for (auto v : adjB[u]){
        if (num[v])
            low[u] = min(low[u],num[v]);
        else{
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
    }
    if(num[u] == low[u]){
        numSCC++;
        int v;
        do {
            v = S.top();
            S.pop();
            mark[v] = numSCC;
            num[v] = low[v] = 10000;
        } while(v!=u);
    }
}

// Dem so thanh phan lien thong manh
int countStronglyConnected(){
    num = new int[n];
    low = new int[n];
    mark = new int[n];
    cnt = 0;
    numSCC = 0;
    memset(num, 0, n);
    memset(low, 0, n);
    memset(mark,-1,n);
    for(int u = 0; u < n; u++)
        if (!num[u]) tarjan(u);
    return numSCC;
}

// In ra man hinh cac tu cung thanh phan lien thong manh
void showStronglyConnected(string s){
    if (mark == NULL){
        countStronglyConnected();
    }
    int u=0, i=0;
    for (i=0;i<n;i++){
        if(s == words[i]){
            u = i;
            break;
        }
    }
    if (i == n){
        cout<<s<<" khong co trong danh sach."<<endl;
        return;
    }
    int num = mark[i];
    for(i=0;i<n;i++){
        if(mark[i] == num){
            cout<<words[i]<<" ";
        }
    }
    cout<<endl;
}

// Giai phong bo nho
void retain(){
    delete num;
    delete low;
    delete mark;
    
}

int main(int argc, const char * argv[]) {
    readInput();
    cout<<"Problem A:"<<endl;
    initGraphA();
    countConnected(adjA);
    cout<<"Find the shortest path:"<<endl;
//    findPath(adjA);
    cout<<endl<<endl<<"Problem B:"<<endl;
    initGraphB();
    cout<<"Graph B has "<<countStronglyConnected()<<" strongly connected components"<<endl;
    cout<<"Cac dinh trong thanh phan lien thong manh chua "<<"pupal"<<" la:"<<endl;
    showStronglyConnected("pupal");
    cout<<"Find the shortest path:"<<endl;
//    findPath(adjB);
    retain();
    return 0;
}
