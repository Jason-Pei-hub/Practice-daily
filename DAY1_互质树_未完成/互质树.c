#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 1001
#define MAX_VALUES 51

// �������ڵ�Ķ���
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

typedef struct TreeNode TreeNode;

// �������Լ����GCD���ĺ���
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// �洢���������
int ans[MAX_NODES];

// �洢ÿ���ڵ�����
int depth[MAX_NODES];

// �洢ÿ��ֵ�Ľڵ�����
int idxs[MAX_VALUES][MAX_NODES];
int idxs_len[MAX_VALUES];

// �洢ͼ������
int graph[MAX_NODES][MAX_NODES];
int graph_size[MAX_NODES];

// �洢�ڵ��ֵ
int values[MAX_NODES];

// �洢Ԥ��������Լ��ֵ
int gcds[MAX_VALUES][MAX_VALUES];

// ִ��DFS�������ҵ����ʵ����Ƚڵ�
void dfs(int x, int d) {
    depth[x] = d;  // ��¼��ǰ�ڵ�����
    // ����ÿ�����ܵ�ֵ
    for (int i = 1; i <= 50; ++i) {
        // ������ֵ��Ӧ�Ľڵ��б�
        for (int j = 0; j < idxs_len[i]; ++j) {
            int last = idxs[i][j];  // ��ȡ�ڵ�����
            // �����ǰ�ڵ�Ĵ�Ϊ�գ��������Ƚڵ����ȸ���
            if (ans[x] == -1 || depth[last] > depth[ans[x]]) {
                ans[x] = last;  // ���´�Ϊ��������Ƚڵ�
            }
        }
    }
    idxs[values[x]][idxs_len[values[x]]++] = x;  // ����ǰ�ڵ�����Ӧֵ�Ľڵ��б���
    // ������ǰ�ڵ���ھӽڵ�
    for (int i = 0; i < graph_size[x]; ++i) {
        int y = graph[x][i];
        // ����ھӽڵ���δ�����ʹ�
        if (depth[y] == 0) {
            dfs(y, d + 1);  // �ݹ����DFS��������ȼ�1
        }
    }
    idxs_len[values[x]]--;  // ���ݲ���������ǰ�ڵ�ӽڵ��б���ɾ��
}

// �����������ػ��ʵ����Ƚڵ�����
int* getCoprimes(int* nums, int numsSize, int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    // ��ʼ������
    for (int i = 0; i < MAX_NODES; ++i) {
        ans[i] = -1;
        depth[i] = 0;
        graph_size[i] = 0;
    }
    for (int i = 1; i <= 50; ++i) {
        idxs_len[i] = 0;
        for (int j = 1; j <= 50; ++j) {
            // ���i��j���ʣ�����Ӧ��λ����Ϊ1��������Ϊ0
            if (gcd(i, j) == 1) {
                gcds[i][j] = 1;
            }
            else {
                gcds[i][j] = 0;
            }
        }
    }

    // ����ͼ
    for (int i = 0; i < edgesSize; ++i) {
        int x = edges[i][0], y = edges[i][1];
        graph[x][graph_size[x]++] = y;
        graph[y][graph_size[y]++] = x;
    }

    // ��ֵ�ڵ��ֵ
    for (int i = 0; i < numsSize; ++i) {
        values[i] = nums[i];
    }

    // ִ��DFS
    dfs(0, 1);

    // ׼���������
    int* result = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; ++i) {
        result[i] = ans[i];
    }
    *returnSize = numsSize;
    return result;
}

int main() {
    // ��������
    int nums[] = { 2, 3, 2, 4, 5, 3, 1 };
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int* edgesColSize;
    int edges[][2] = { {0,1},{0,2},{1,3},{1,4},{2,5},{2,6} };
    int edgesSize = sizeof(edges) / sizeof(edges[0]);
    int returnSize;

    // ���ú���
    int* result = getCoprimes(nums, numsSize, (int**)edges, edgesSize, edgesColSize, &returnSize);

    // ������
    printf("Result: ");
    for (int i = 0; i < returnSize; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // �ͷ��ڴ�
    free(result);
    return 0;
}