#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    int* visited;
    Node** adjList;
} Graph;

typedef struct Stack {
    int top;
    int capacity;
    int* array;
} Stack;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->visited = (int*)calloc(numVertices, sizeof(int));
    graph->adjList = (Node**)malloc(numVertices * sizeof(Node*));

    for (int i = 0; i < numVertices; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(capacity * sizeof(int));
    return stack;
}

void push(Stack* stack, int value) {
    if (stack->top < stack->capacity - 1) {
        stack->array[++stack->top] = value;
    }
}

int pop(Stack* stack) {
    if (stack->top >= 0) {
        return stack->array[stack->top--];
    }
    return -1;
}

void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

void dfs(Graph* graph, Stack* stack, int vertex) {
    graph->visited[vertex] = 1;
    push(stack, vertex);

    Node* temp = graph->adjList[vertex];
    while (temp != NULL) {
        int connectedVertex = temp->data;
        if (!graph->visited[connectedVertex]) {
            dfs(graph, stack, connectedVertex);
        }
        temp = temp->next;
    }
}

int isReachable(Graph* graph, int start, int end) {
    Stack* stack = createStack(graph->numVertices);
    dfs(graph, stack, start);
    int reachable = 0;
    for (int i = 0; i <= stack->top; i++) {
        if (stack->array[i] == end) {
            reachable = 1;
            break;
        }
    }
    free(stack->array);
    free(stack);
    resetVisited(graph);
    return reachable;
}

void insertEdges(Graph* graph, int numEdges) {
    int src, dest;
    printf("Introdu %d muchii (ex: 0 1):\n", numEdges);
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

int main() {
    int numVertices, numEdges;
    printf("Cate noduri are graful? ");
    scanf("%d", &numVertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &numEdges);

    Graph* graph = createGraph(numVertices);
    insertEdges(graph, numEdges);

    int start, end;
    printf("Verifica daca exista drum direct intre doua restaurante.\n");
    printf("Nod sursa: ");
    scanf("%d", &start);
    printf("Nod destinatie: ");
    scanf("%d", &end);

    if (isReachable(graph, start, end)) {
        printf("Exista drum intre %d si %d.\n", start, end);
    } else {
        printf("Nu exista drum intre %d si %d.\n", start, end);
    }

    for (int i = 0; i < numVertices; i++) {
        Node* temp = graph->adjList[i];
        while (temp) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adjList);
    free(graph->visited);
    free(graph);

    return 0;
}
