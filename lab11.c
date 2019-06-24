#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct treeEdge {
    int begin, end;
    int len;
    int next;
} Edge;

int fEdges(int n, int m, Edge* edges) {
    int a, b, l;
    for (int i = 0; i < m; i++) {
        if (scanf("%d%d%d", &a, &b, &l) < 3) {
            printf("bad number of lines\n");
            return 0;
        }
        if ((a < 1) || (a > n) || (b < 1) || (b > n)) {
            printf("bad vertex\n");
            return 0;
        }
        if ((l > INT_MAX)|| (l < 0)) {
            printf("bad length\n");
            return 0;
        }
        edges[i].begin = a - 1;
        edges[i].end = b - 1;
        edges[i].len = l;
        edges[i].next = 0;
    }
    return 1;
}

int compare(const Edge* a, const Edge* b) {
    return a->len - b->len;
}

int minTree(int n, int m, Edge* edges) {
    if (!n) {
        return 0;
    }
    qsort(edges, m, sizeof(Edge), compare);
    int* components = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        components[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int compBegin = components[edges[i].begin];
        int compEnd = components[edges[i].end];
        if (compBegin != compEnd) {
            edges[i].next = 1;
            for (int j = 0; j < n; j++) {
                if (components[j] == compBegin) {
                    components[j] = compEnd;
                }
            }
        }
    }
    for (int i = 1; i < n; i++) {
        if (components[0] != components[i]) {
            free(components);
            return 0;
        }
    }
    free(components);
    return 1;
}

int main() {
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) {
        printf("bad number of lines\n");
        return 0;
    } else {
        if ((n > 5000) || (n < 0)) {
            printf("bad number of vertices\n");
            return 0;
        } else {
            if ((m > n * (n - 1) / 2) || (m < 0)) {
                printf("bad number of edges\n");
                return 0;
            }
        }
    }

        Edge* edges = malloc(sizeof(Edge) * m);

    if (!fEdges(n, m, edges)) {
        return;
    }
    if (minTree(n, m, edges)) {
        for (int i = 0; i < m; i++) {
        if (edges[i].next) {
            printf("%d %d\n", edges[i].begin + 1, edges[i].end + 1);
            }
        }
    }
    else {
        printf("no spanning tree\n");
    }
    free(edges);

    return 0;

    }
