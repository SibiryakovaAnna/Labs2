#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int Graph(int n, int m, int**graph) {
    int a, b, l;
    for (int i = 0; i < m; i++) {
        if (scanf("%d%d%d", &a, &b, &l) < 3) {
            printf("bad number of lines\n");
            return 0;
        } else {
            if ((a < 1) || (a > n) || (b < 1) || (b > n)) {
                printf("bad vertex\n");
                return 0;
            } else {
                if ((l < 0) || (l > INT_MAX)) {
                    printf("bad length\n");
                    return 0;
                }
            }
        }
        graph[a - 1][b - 1] = l;
        graph[b - 1][a - 1] = l;
    }
    return 1;
}

void Min(int s, int n, unsigned int* len, int* path, int* pathCounter, int**graph) {
    int* used = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        used[i] = 0;
    }
    len[s - 1] = 0;
    path[s - 1] = s - 1;
    pathCounter[s - 1] = 1;
    for (int i = 0; i < n; i++) {
        int v=-1;
        for (int j = 0; j < n; j++) {
            if ((!used[j]) && ((v == -1) || (len[j] < len[v]))) {
                v=j;
            }
        }
        if (len[v] == UINT_MAX) {
            return;
        }
        for (int u = 0; u < n; u++) {
            if (!used[u] && graph[v][u] != -1) {
                pathCounter[u] += pathCounter[v];
                unsigned int relax = len[v] + graph[v][u];
                if (relax > INT_MAX) {
                    relax = (unsigned int)INT_MAX + 1;
                }
                if (relax < len[u]) {
                    len[u] = relax;
                    path[u] = v;
                }
            }
        }
        used[v] = 1;
    }
    free(used);
}

int main() {
    int n, m, s, f, v;
    if (scanf("%d%d%d%d", &n, &s, &f, &m) < 4) {
        printf("bad number of lines\n");
        return 0;
    } else {
        if (n < 0 || n > 5000) {
            printf("bad number of vertices\n");
            return 0;
        } else {
            if (s < 1 || s > n || f < 0 || f > n) {
                printf("bad vertex\n");
                return 0;
            } else
            if (m < 0 || m > n*(n - 1) / 2) {
                printf("bad number of edges\n");
                return 0;
            }
        }
    }
    int**graph = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        graph[i] = malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            graph[i][j] = -1;
        }
    }
    if (!Graph(n, m, graph)) {
        for (int i = 0; i < n; i++) {
            free(graph[i]);
        }
        free(graph);
        return 0;
    }
    unsigned int* len = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        len[i] = -1;
    }
    int* path = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        path[i] = -1;
    }
    int* pathCounter = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        pathCounter[i] = 0;
    }
    Min(s, n, len, path, pathCounter, graph);
    v = f - 1;
    for (int i = 0; i < n; i++) {
        if (len[i] == UINT_MAX) {
            printf("oo ");
        } else
        if (len[i] > INT_MAX) {
            printf("INT_MAX+ ");
        } else {
            printf("%d ", len[i]);
        }
    }
    printf("\n");
    if (path[f - 1] == -1) {
        printf("no path\n");
        return 0;
    } else {
        if ((pathCounter[f - 1] > 1) && (len[f - 1] > INT_MAX)) {
            printf("overflow\n");
            return 0;
        }
    }
    printf("%d ", f);
    while (path[v] != v) {
        v = path[v];
        printf("%d ", v + 1);
    }
    free(path);
    free(len);
    free(pathCounter);
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    return 0;
}
