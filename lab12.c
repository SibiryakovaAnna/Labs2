#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int Arr(int count, int value) {
    int*arr = malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++) {
        arr[i] = value;
    }
    return arr;
}

int buildGraph(int n, int m, unsigned int**graph) {
    int a, b, len;
    for (int i = 0; i < m; i++) {
        if (scanf("%d%d%d", &a, &b, &len) < 3) {
            printf("bad number of lines\n");
            return 0;
        }
        if ((a < 1) || (a > n) || (b < 1) || (b > n)) {
            printf("bad vertex\n");
            return 0;
        }
        if (len < 0 || len > INT_MAX){
           printf("bad length\n");
            return 0;
        }
        graph[a - 1][b - 1] = len;
        graph[b - 1][a - 1] = len;
    }
    return 1;
}

int minV(int n, int*ar, unsigned int *l) {
    int v = -1;
    for (int u = 0; u < n; u++) {
        if ((!ar[u]) && ((v == -1) || (l[u] < l[v]))) {
            v = u;
        }
    }
    return v;
}

int findMST(int n, int *MST, unsigned int**graph) {
    unsigned int *l = Arr(n, -1);
    int *ar = Arr(n, 0);
    l[0] = 0;
    for (int i = 0; i < n; i++) {
        int v = minV(n, ar, l);
        if (l[v] == UINT_MAX) {
            return 0;
        }
        ar[v] = 1;
        for (int u = 0; u < n; u++) {
            if ((graph[v][u] < l[u]) && (!ar[u])) {
                l[u] = graph[v][u];
                MST[u] = v;
            }
        }
    }
    free(l);
    free(ar);
    return 1;
}


void prim(int n, int m) {
    unsigned int **graph;
    graph = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        graph[i] = Arr(n, -1);
    }
    if (!buildGraph(n, m, graph)) {
        for (int i = 0; i < n; i++) {
            free(graph[i]);
        }
        free(graph);
        return;
    }
    int *MST = Arr(n, -1);
    if (!n || !findMST(n, MST, graph)) {
        printf("no spanning tree\n");
    }
    else {
        for (int i = 0; i < n; i++) {
            if (MST[i] != -1) {
                printf("%d %d\n", i + 1, MST[i] + 1);
            }
        }
    }

    free(MST);

    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
}

int main() {
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) {
        printf("bad number of lines\n");
        return 0;
    } else {
        if (( n > 5000)|| (n < 0)) {
            printf("bad number of vertices\n");
            return 0;
        } else {
            if ((m > n*(n - 1) / 2) || (m < 0)) {
                printf("bad number of edges\n");
                return 0;
            }
        }
    }
    prim(n, m);

    return 0;
}
