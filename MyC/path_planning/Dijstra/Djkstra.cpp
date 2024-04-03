//
// Created by QianWu on 2024/3/23.
//

#include <climits>
#include <vector>
#include <iostream>
#include "Djkstra.h"
using namespace std;

//Stay calm.
// cost[]: 从start point到其他节点的cost
//定义最大值
//时间复杂度0(n^2)
int infinity = INT_MAX;
//初始化邻接矩阵，找Node 0 到Node5的最短路径
vector<vector<int>> e{ {0,1,12,infinity,infinity,infinity},
                       {infinity,0, 9, 3, infinity, infinity},
                       {infinity,infinity,0,infinity,5, infinity},
                       {infinity,infinity,4, 0,13,15},
                       {infinity, infinity, infinity, infinity,0, 4},
                       {infinity, infinity, infinity, infinity,infinity, 0}
};

void dijkstar( )
{

    int n = e.size();
    vector<int> cost(n, 0);
    vector<int> used(n, 0);
    // 初始化cost
    for (int i = 0; i < n; i++)
    {
        cost[i] = e[0][i];
    }
    used[0] = 1;//1代表已经更新完成
    int min = 0;
    int u = 0; //记录离0最小距离的坐标

    // 在相邻的节点里找距离start point最近的点，并记下距离
    for (int i = 0; i < n ; i++)
    {
        // 找到离1号顶点最近的顶点u
        min = infinity;
        for (int j = 1; j < n; j++)
        {
            if (used[j] == 0 && cost[j] < min) // 如果是和当前节点相邻的节点
            {
                min = cost[j];
                u = j;
            }
        }
        used[u] = 1;
        // 更新所有节点在加入了v之后的cost
        for (int v = 1; v < n; v++)
        {
            if (e[u][v] < infinity)
            {
                if (cost[v] > cost[u] + e[u][v])
                    cost[v] = cost[u] + e[u][v];
            }
        }
    }
    //打印更新过的结果
    for (auto d : cost)
    {
        cout << d << endl;
    }
}


void test(){
    int n_node = e.capacity();

    vector<int> cost(n_node, 0);
    vector<int> used(n_node, 0);
    used[0] = 1;
    // 初始化cost
    for(int i =0; i< n_node; i++){
        cost[i] = e[0][i];
    }

    int min = 0;
    int u = 0;  //新找到的距离start point最近的元素

    for(int i = 0; i<n_node; i++){
        //找到新的相邻节点
        min = infinity;
        for (int j = 1; j < n_node; j++) {
            if (used[j] == 0 && cost[j] < min){
                min = cost[j];
                u = j;
            }
        }
        used[u] = 1;


        // 找到了新节点，更新通过新节点的距离
        for (int v = 1; v < n_node; ++v) {
            if (e[u][v] < infinity && cost[v] > cost[u] + e[u][v]) {
                cost[v] = cost[u] + e[u][v];
            }
        }
    }

    for (auto i: cost) {
        cout<<i<<endl;
    }

}