#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <functional>

using namespace std;

// 结构体表示地图上的每个节点
struct Node {
    int x, y;         // 节点的坐标
    int g, h;         // 节点的路径成本（g）和启发式估计成本（h）
    Node* parent;     // 节点的父节点指针

    // 构造函数，初始化节点的坐标、路径成本、启发式估计成本和父节点指针
    Node(int _x, int _y) : x(_x), y(_y), g(0), h(0), parent(nullptr) {}

    // 计算当前节点到目标节点的曼哈顿距离（启发式估计）
    int manhattanDistance(Node* goal) const {
        return abs(x - goal->x) + abs(y - goal->y);
    }

    // 计算当前节点的 f 值（路径成本加启发式估计成本）
    int fValue() const {
        return g + h;
    }

    // 重载运算符==，用于比较两个节点是否相等
    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

// 定义哈希函数用于在 unordered_set 中存储节点
namespace std {
    template <> struct hash<Node> {
        size_t operator()(const Node& n) const {
            return hash<int>()(n.x) ^ hash<int>()(n.y);
        }
    };
}

// A* 算法函数
vector<Node*> AStar(Node* start, Node* goal, const vector<vector<int>>& grid) {
    // 定义优先队列 open，用于存储待探索的节点，按节点的 f 值降序排列
    priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>> open([](Node* a, Node* b) {
        return a->fValue() > b->fValue();
    });

    // 定义无序集合 closed，用于存储已经探索过的节点
    unordered_set<Node> closed;

    // 将起始节点加入优先队列中
    open.push(start);

    // Lambda 函数 isOpenContains 用于检查优先队列中是否包含指定节点
    auto isOpenContains = [&](Node* node) {
        // 创建一个临时优先队列，用于遍历判断是否包含指定节点
        priority_queue<Node*, vector<Node*>, decltype(open)::value_compare> temp(open);
        while (!temp.empty()) {
            if (temp.top() == node) {
                return true;
            }
            temp.pop();
        }
        return false;
    };

    // A* 算法的主循环，直到优先队列为空
    while (!open.empty()) {
        // 从优先队列中取出 f 值最小的节点
        Node* current = open.top();
        open.pop();

        // 如果当前节点为目标节点，则回溯生成路径并返回
        if (current == goal) {
            vector<Node*> path;
            while (current) {
                path.push_back(current);
                current = current->parent;
            }
            return path;
        }

        // 将当前节点加入已探索集合中
        closed.insert(*current);

        // 遍历当前节点的所有邻居节点
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;
                int nx = current->x + dx;
                int ny = current->y + dy;
                Node* neighbor = new Node(nx, ny); // 创建邻居节点
                // 如果邻居节点超出边界或是障碍物或已探索过，则跳过
                if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size() || grid[nx][ny] == 1 || closed.count(*neighbor)) {
                    delete neighbor;
                    continue;
                }
                // 计算邻居节点的新路径成本
                int newG = current->g + 1;
                // 如果邻居节点的新路径成本更
                if (newG < neighbor->g || !isOpenContains(neighbor)) {
                    neighbor->g = newG;
                    neighbor->h = neighbor->manhattanDistance(goal); // 更新启发式估计成本
                    neighbor->parent = current; // 更新父节点指针
                    open.push(neighbor); // 将邻居节点加入优先队列中
                } else {
                    delete neighbor; // 否则，释放邻居节点的内存
                }
            }
        }
    }

    return vector<Node*>(); // 如果无法找到路径，则返回空路径
}

int main() {
    // 创建地图，并假设障碍物为1，可行区域为0
    vector<vector<int>> grid = {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
    };

    // 创建起点和终点
    Node* start = new Node(0, 0);
    Node* goal = new Node(4, 4);

    // 运行 A* 算法
    vector<Node*> path = AStar(start, goal, grid);

    // 输出路径
    if (path.empty()) {
        cout << "No path found!" << endl;
    } else {
        cout << "Path found:" << endl;
        for (int i = path.size() - 1; i >= 0; --i) {
            cout << "(" << path[i]->x << ", " << path[i]->y << ")";
            if (i > 0) cout << " -> ";
        }
        cout << endl;
    }

    // 释放内存
    delete start;
    delete goal;
    for (auto node : path) {
        delete node;
    }

    return 0;
}
