#include <stdio.h>
#include <stdlib.h>

typedef struct stack{
    int value;
    struct stack* next;
} Stack;

typedef struct graph{
    int color;
    Stack* Next;
} Graph;

void push(Stack**stack, int value) {
    Stack* tmp = malloc(sizeof(Stack));
    tmp->value = value;
    tmp->next = *stack;
    *stack = tmp;
}


int freeStack(Stack* stack) {
    while (stack) {
        int value = (stack)->value;
        Stack* tmp = stack;
        stack = (stack)->next;
        free(tmp);
        return value;
    }
}


Graph* buildGraph(int n, int m) {
    Graph* graph = malloc(sizeof(Graph) * n);
    for (int i = 0; i < n; i++) {
        graph[i].color = 0;
        graph[i].Next = 0;
    }
    int a, b;
    for (int i = 0; i < m; i++) {
        if (scanf("%d%d", &a, &b) < 2) {
            for (int j = 0; j < n; j++) {
                freeStack(graph[j].Next);
            }
            free(graph);
            printf("bad number of lines\n");
            return 0;
        }
        if ((a < 1) || (a > n) || (b < 1) || (b > n)) {
            for (int i = 0; i < n; i++) {
                freeStack(graph[i].Next);
            }
            free(graph);
            printf("bad vertex\n");
            return NULL;
        } push(&graph[a - 1].Next, b - 1);
    }
    return graph;
}

void dfs(Graph* graph, int vertex, Stack** sortedGraph, int* cycle) {
    graph[vertex].color = 1;
    Stack* tmp = graph[vertex].Next;
    while (tmp) {
        if (graph[tmp->value].color == 0) {
            dfs(graph, tmp->value, sortedGraph, cycle);
        }
        if (graph[tmp->value].color == 1) {
            *cycle = 1;
        }
        tmp = tmp->next;
    }
    graph[vertex].color = 2;
    push(sortedGraph, vertex);
}


Stack* topSort(Graph* graph, int n) {
    int cycle = 0;
    Stack* sortedGraph = NULL;
    for (int i = 0; i < n; i++) {
        if (graph[i].color == 0) {
            dfs(graph, i, &sortedGraph, &cycle);
        }
        if (cycle) {
            printf("impossible to sort\n");
            freeStack(sortedGraph);
            return NULL;
        }
    }
    return sortedGraph;
}

int main() {
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) {
        printf("bad number of lines\n");
        return 0;
    } else {
        if (( n > 1000)|| (n < 0)) {
            printf("bad number of vertices\n");
            return 0;
        } else {
            if ((m > n*(n - 1) / 2) || (m < 0)) {
                printf("bad number of edges\n");
                return 0;
            }
        }
    }

    Graph* graph = buildGraph(n, m);
    if (!graph) {
        return 0;
    }
    Stack* sortedGraph = topSort(graph, n);
    if (sortedGraph) {
        while (sortedGraph) {
            int value = (sortedGraph)->value;
            Stack *tmp = sortedGraph;
            sortedGraph = (sortedGraph)->next;
            free(tmp);
            printf("%d ", value + 1);
        }
    }

    for (int i = 0; i < n; i++) {
        freeStack(graph[i].Next);
    }
    free(graph);

    return 0;
}
