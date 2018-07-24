#include <iostream>
#include <stdio.h>

#define MAX 100000

using namespace std;

/*
Chuyển từ cây sang prufer code
Input: Các cạnh của cây
Ouput: Prufer code

Độ phức tạp: O(N^2) (N: số đỉnh)
*/

void TreeToPruferCode(int e, int **edge) {
    int i, j, min, v;
    int deg[e+2] = {0};
    int mark[e] = {0};

    for(i = 0; i < e; i++) {
		deg[edge[i][0]]++;
		deg[edge[i][1]]++;
	}

	for(i = 0; i < e-1; i++) {
		min = MAX;
		// Chọn đỉnh bé nhất khác 0 có bậc là 1
		for(j = 0; j < e; j++) {
            if (mark[j])
                continue;

			if(deg[edge[j][0]] == 1 && edge[j][0] != 0) {
				if(min > edge[j][0])
				{
					min = edge[j][0];
					v = j;
				}
			}

			if(deg[edge[j][1]] == 1 && edge[j][1] != 0) {
				if(min > edge[j][1])
				{
					min = edge[j][1];
					v = j;
				}
			}
		}

		// Đánh dấu cạnh được chọn
		mark[v] = 1;

		// Giảm bậc của các đỉnh trong cạnh đã chọn đi 1
		deg[edge[v][0]]--;
		deg[edge[v][1]]--;

		// In ra đỉnh kề với đỉnh bị xoá
		if(deg[edge[v][0]] == 0)
			printf("%d ",edge[v][1]);
		else
			printf("%d ",edge[v][0]);
	}
}

int** ReadInput(int e){
    int **egde = new int*[e];
    for(int i=0;i<e;i++){
        egde[i] = new int(2);
    }
    for (int i = 0; i < e; i++){
        scanf("%d%d", &egde[i][0],&egde[i][1]);
    }
    return egde;
}

int main()
{
    // freopen("data.inp","r",stdin);
    // freopen("data.out","w",stdout);
    int e;
    scanf("%d", &e);
    int **a = ReadInput(e);
    TreeToPruferCode(e,a);

    for(int i=0;i<e;i++){
        delete(a[i]);
    }

    delete a;

	return 0;
}
