#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 1001
#define MAX_VALUES 51

// 二叉树节点的定义
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

typedef struct TreeNode TreeNode;

// 计算最大公约数（GCD）的函数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 存储结果的数组
int ans[MAX_NODES];

// 存储每个节点的深度
int depth[MAX_NODES];

// 存储每个值的节点索引
int idxs[MAX_VALUES][MAX_NODES];
int idxs_len[MAX_VALUES];

// 存储图的数组
int graph[MAX_NODES][MAX_NODES];
int graph_size[MAX_NODES];

// 存储节点的值
int values[MAX_NODES];

// 存储预计算的最大公约数值
int gcds[MAX_VALUES][MAX_VALUES];

// 执行DFS遍历以找到互质的祖先节点
void dfs(int x, int d) {
    depth[x] = d;  // 记录当前节点的深度
    // 遍历每个可能的值
    for (int i = 1; i <= 50; ++i) {
        // 遍历该值对应的节点列表
        for (int j = 0; j < idxs_len[i]; ++j) {
            int last = idxs[i][j];  // 获取节点索引
            // 如果当前节点的答案为空，或者祖先节点的深度更深
            if (ans[x] == -1 || depth[last] > depth[ans[x]]) {
                ans[x] = last;  // 更新答案为最深的祖先节点
            }
        }
    }
    idxs[values[x]][idxs_len[values[x]]++] = x;  // 将当前节点加入对应值的节点列表中
    // 遍历当前节点的邻居节点
    for (int i = 0; i < graph_size[x]; ++i) {
        int y = graph[x][i];
        // 如果邻居节点尚未被访问过
        if (depth[y] == 0) {
            dfs(y, d + 1);  // 递归调用DFS函数，深度加1
        }
    }
    idxs_len[values[x]]--;  // 回溯操作，将当前节点从节点列表中删除
}

// 主函数，返回互质的祖先节点数组
int* getCoprimes(int* nums, int numsSize, int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    // 初始化数组
    for (int i = 0; i < MAX_NODES; ++i) {
        ans[i] = -1;
        depth[i] = 0;
        graph_size[i] = 0;
    }
    for (int i = 1; i <= 50; ++i) {
        idxs_len[i] = 0;
        for (int j = 1; j <= 50; ++j) {
            // 如果i和j互质，将对应的位置置为1，否则置为0
            if (gcd(i, j) == 1) {
                gcds[i][j] = 1;
            }
            else {
                gcds[i][j] = 0;
            }
        }
    }

    // 构建图
    for (int i = 0; i < edgesSize; ++i) {
        int x = edges[i][0], y = edges[i][1];
        graph[x][graph_size[x]++] = y;
        graph[y][graph_size[y]++] = x;
    }

    // 赋值节点的值
    for (int i = 0; i < numsSize; ++i) {
        values[i] = nums[i];
    }

    // 执行DFS
    dfs(0, 1);

    // 准备结果数组
    int* result = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; ++i) {
        result[i] = ans[i];
    }
    *returnSize = numsSize;
    return result;
}

int main() {
    // 测试用例
    int nums[] = { 2, 3, 2, 4, 5, 3, 1 };
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int* edgesColSize;
    int edges[][2] = { {0,1},{0,2},{1,3},{1,4},{2,5},{2,6} };
    int edgesSize = sizeof(edges) / sizeof(edges[0]);
    int returnSize;

    // 调用函数
    int* result = getCoprimes(nums, numsSize, (int**)edges, edgesSize, edgesColSize, &returnSize);

    // 输出结果
    printf("Result: ");
    for (int i = 0; i < returnSize; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // 释放内存
    free(result);
    return 0;
}