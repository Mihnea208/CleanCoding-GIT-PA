#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int vertices;
    int* visited;
    Node** adjacency_lists;
} Graph;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Graph* create_graph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->visited = (int*)calloc(vertices, sizeof(int));
    graph->adjacency_lists = (Node**)malloc(vertices * sizeof(Node*));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
    }

    return graph;
}

void add_edge(Graph* graph, int src, int dest) {
    Node* new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(Graph* graph, int num_vertices, int num_edges) {
    int src, dest;
    printf("Adauga %d muchii (de la 0 la %d):\n", num_edges, num_vertices - 1);
    for (int i = 0; i < num_edges; i++) {
        scanf("%d %d", &src, &dest);
        if (src >= 0 && dest >= 0 && src < num_vertices && dest < num_vertices) {
            add_edge(graph, src, dest);
        } else {
            printf("Muchie invalida: %d - %d\n", src, dest);
            i--; // retrimite muchia dacă e invalidă
        }
    }
}

int is_empty(Node* queue) {
    return queue == NULL;
}

void enqueue(Node** queue, int data) {
    Node* new_node = create_node(data);
    if (*queue == NULL) {
        *queue = new_node;
    } else {
        Node* temp = *queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(Node** queue) {
    if (*queue == NULL) return -1;
    int data = (*queue)->data;
    Node* temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void wipe_visited(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

void DFS(Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    Node* temp = graph->adjacency_lists[vertex];
    while (temp != NULL) {
        int adj = temp->data;
        if (!graph->visited[adj]) {
            DFS(graph, adj);
        }
        temp = temp->next;
    }
}

void BFS(Graph* graph, int start) {
    Node* queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node* temp = graph->adjacency_lists[current];
        while (temp != NULL) {
            int adj = temp->data;
            if (!graph->visited[adj]) {
                graph->visited[adj] = 1;
                enqueue(&queue, adj);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int num_vertices, num_edges, start_vertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &num_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &num_edges);

    Graph* graph = create_graph(num_vertices);
    insert_edges(graph, num_vertices, num_edges);

    printf("De unde plecam in DFS? ");
    scanf("%d", &start_vertex);
    printf("Parcurgere DFS: ");
    DFS(graph, start_vertex);

    wipe_visited(graph);
    printf("\n");

    printf("De unde plecam in BFS? ");
    scanf("%d", &start_vertex);
    printf("Parcurgere BFS: ");
    BFS(graph, start_vertex);
    printf("\n");

    for (int i = 0; i < num_vertices; i++) {
        Node* temp = graph->adjacency_lists[i];
        while (temp != NULL) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adjacency_lists);
    free(graph->visited);
    free(graph);

    return 0;
}
