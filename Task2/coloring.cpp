//
//  main.cpp
//  coloring
//
//  Created by HoaPQ on 7/29/18.
//  Copyright © 2018 HoaPQ. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstdio>

#define MAX 100000

using namespace std;

string colors[] = {"green","red","blue","brown","cyan","gold","hotpink","indigo","greenyellow","limegreen","orange","violet","chocolate"}; // Luu cac mau trong graphviz

vector<vector<int>> adj; // Luu danh sach ke

int n,m; // Luu so dinh va so canh
int *deg; // Luu bac cua dinh
int *colorNode; // Luu mau cua cac dinh
int *orders; // Luu thu tu duyet cac dinh
int **egdes; // Luu danh sach canh

bool *vis; // Danh dau xem dinh duoc tham chua

// Doc du lieu tu file dothi.txt
void readInput(){
    freopen("dothi.txt","r",stdin);
    scanf("%d%d",&n,&m);
    int x,y;
    adj = vector<vector<int>>(n);
    deg = new int[n]();
    egdes = new int*[m];
    for (int i=0;i<m;i++){
        egdes[i] = new int[2];
    }
    for (int i=0;i<m;i++){
        scanf("%d%d",&x,&y);
        // Luu cac dinh vao danh sach ke tuong ung
        adj[x-1].push_back(y-1);
        adj[y-1].push_back(x-1);
        // Luu canh vao danh sach canh
        egdes[i][0] = x-1;
        egdes[i][1] = y-1;
        // Tang bac cua dinh
        deg[x-1]++;
        deg[y-1]++;
    }
}
// DFS
void dfs(int u){
    if (!vis[u]){
        vis[u] = true;
        for (auto v : adj[u]){
            dfs(v);
        }
    }
}

// Kiem tra tinh lien thong va chinh quy cua do thi
bool checkConnected(){
    int d = deg[0];
    // Kiem tra chinh quy
    bool chinhquy = true;
    for (int i=0;i<n;i++){
        if (deg[i] != d){
            chinhquy = false;
            break;
        }
    }
    if (chinhquy){
        return false;
    }
    // Kiem tra lien thong bang dfs
    vis = new bool[n]();
    dfs(0);
    for (int i=0;i<n;i++){
        if (!vis[i]){
            return false;
        }
    }
    
    return true;
}

// Thuat toan tim thu tu duyet dinh
void ordering(){
    orders = new int[n];
    queue<int> Q;
    bool *mark = new bool[n];
    int i, u=0, v;
    // Tim dinh u co bac nho nhat
    int mindeg = MAX;
    for (i=0;i<n;i++){
        mark[i] = false;
        if(mindeg > deg[i]){
            mindeg = deg[i];
            u = i;
        }
    }
    // Luu u vao vi tri cuoi cung
    orders[n-1] = u;
    // Cho u vao hang doi
    Q.push(u);
    mark[u] = true;
    i = n-2;
    while(!Q.empty()){
        v = Q.front();
        Q.pop();
        for (auto k :adj[v]){
            // Neu k chua duoc cho vao mang orders thi cho k vao hang doi va orders roi danh dau
            if(!mark[k]){
                Q.push(k);
                mark[k] = true;
                orders[i] = k;
                i--;
            }
        }
    }
    delete[] mark;
}

// Thuat toan to mau tham lam
void greedyColoring(){
    colorNode = new int[n];
    for(int i=0;i<n;i++){
        colorNode[i] = -1; // Khoi tao colorNode[i] = -1 : Chua duoc to mau
    }
    colorNode[orders[0]] = 0; // To mau dinh dau tien trong orders
    // Duyet cac dinh theo thu tu trong orders
    for(int i=1;i<n;i++){
        int u = orders[i];
        int color;
        // Tim mau nho nhat co the to
        bool flagColor[12] = {false};
        for(auto v : adj[u]){
            if (colorNode[v] != -1){
                flagColor[colorNode[v]] = true;
            }
        }
        color = 0;
        while(flagColor[color]){
            color++;
        }
        colorNode[u] = color;
    }
}

void printColor(bool connected){
    int maxdeg = 0;
    int numColor = 0;
    for(int i=0;i<n;i++){
        if(maxdeg < deg[i]){
            maxdeg = deg[i];
        }
        if (numColor < colorNode[i]){
            numColor = colorNode[i];
        }
    }
    if (connected)
        cout<<"Do thi lien thong."<<endl;
    else cout<<"Do thi khong lien thong hoac chinh quy."<<endl;
    cout<<"So dinh: "<<n<<endl;
    cout<<"Bac cao nhat: "<<maxdeg<<endl;
    cout<<"So mau can dung: "<<numColor+1<<endl;
    
}

// In ra file dothitomau.dot
void printToFile(){
    freopen("dothitomau.dot", "w+", stdout);
    printf("graph dothi {\n");
    for(int i=0;i<n;i++){
        printf("\t%d [fillcolor=%s, style=filled];\n",i+1,colors[colorNode[i]].c_str());
    }
    for(int i=0;i<m;i++){
        printf("\t%d -- %d;\n",egdes[i][0]+1,egdes[i][1]+1);
    }
    printf("}\n");
}

int main(int argc, const char * argv[]) {
    readInput();
    bool check = checkConnected();
    if (check)
        ordering(); // Neu do thi lien thong va khong chinh quy thi tim thu tu
    else{           // Neu khong thi duyet theo nhan cua dinh
        orders = new int[n];
        for(int i=0;i<n;i++){
            orders[i] = i;
        }
    }
    greedyColoring();
    // printColor(check);
    printToFile();
    
    delete [] deg;
    delete [] egdes;
    delete [] colorNode;
    delete [] orders;
    
    return 0;
}
