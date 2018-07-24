#include <iostream>
#include <stdio.h>

#include <vector>
#include <set>

#define MAX 100000

using namespace std;

/*
Chuyển từ cây sang prufer code v2
Input: Các cạnh của cây
Ouput: Prufer code

Độ phức tạp: O(NlogN) (N: số đỉnh)
Notes: Sử dụng cấu trúc dữ liệu vector và set của C++

V2 nhanh hơn v1 khoảng 120-130 lần trên dữ liệu n ~ 100000
*/

void TreeToPruferCode(vector<vector<int> > adj) {
    int n = adj.size();

    set<int> leafs; // Lưu trữ các đỉnh bậc 1 (có sắp xếp tăng dần)
    vector<int> deg(n); // Lưu bậc các đỉnh của cây
    vector<bool> removed(n,false); // Kiểm tra xem đỉnh của cây đã remove chưa

    for(int i=1; i<n; i++){
        // Tính toán bậc cho đỉnh
        deg[i] = adj[i].size();
        // Nếu đỉnh có bậc 1 thì insert vào set leafs
        if (deg[i] == 1){
            leafs.insert(i);
        }
    }

    for(int i=0; i<n-2; i++){
        // Lấy lá đầu tiên trong set leafs
        int node = *leafs.begin();
        leafs.erase(leafs.begin());
        removed[node] = true;
        // Lấy đỉnh kề với lá
        int v;
        for(int j=0;j<adj[node].size();j++){
            int u = adj[node][j];
            if(!removed[u]){
                v = u;
            }
        }

        printf("%d ",v);
        // Nếu đỉnh kề sau khi xoá lá có bậc là 1 thì insert vào leafs
        if (--deg[v] == 1){
            leafs.insert(v);
        }
    }
}

vector<vector<int> > ReadInput(int e){
    vector<vector<int> > adj(e+1);
    int x,y;
    for(int i=0; i<e; i++){
        scanf("%d%d",&x,&y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    return adj;
}

int main()
{
    // freopen("data.inp","r",stdin);
    // freopen("data_v2.out","w",stdout);
    int e;
    scanf("%d", &e);
    vector<vector<int> > a = ReadInput(e);
    TreeToPruferCode(a);

	return 0;
}
