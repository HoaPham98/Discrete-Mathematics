#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

// A function to generate random graph.
void GenerateRandGraphs(int NOE, int NOV)
{
    int i, j, edge[NOE][2], count;
    i = 0;
    // Build a connection between two random vertex.
    while(i < NOE)
    {
        edge[i][0] = rand()%NOV+1;
        edge[i][1] = rand()%NOV+1;
        
        if(edge[i][0] == edge[i][1])
            continue;
        else
        {
            for(j = 0; j < i; j++)
            {
                if((edge[i][0] == edge[j][0] && edge[i][1] == edge[j][1]) || (edge[i][0] == edge[j][1] && edge[i][1] == edge[j][0]))
                    i--;
            }
        }
        i++;
    }
    for(j = 0; j < NOE; j++){
        cout<<edge[j][0]<<" "<<edge[j][1]<<endl;
    }
}

int main()
{
    int e, v;
    freopen("dothi.txt","w+",stdout);
    // Randomly assign vertex and edges of the graph.
    srand(time(0));
    v = 8 + rand()%10;
    e = rand()%((v*(v-1))/2);
    
    cout<<v<<" "<<e<<endl;
    
    // A function to generate a random undirected graph with e edges and v vertexes.
    GenerateRandGraphs(e, v);
}
