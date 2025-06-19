#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int pid;
    char command[256];
} valueT;

typedef struct _nodeT {
    valueT value;
    struct _nodeT *next;
} nodeT;

typedef struct {
    nodeT *head;
} stackT;

nodeT *NewNode(void) {
    nodeT *newNode = (nodeT *)malloc(sizeof(nodeT));
    if (newNode == NULL) {
        printf("Erro: Não há espaço suficiente para criar um novo nó.\n");
        return NULL;
    }
    return newNode;
}

stackT *NewStack(void) {
    stackT *stack = (stackT *)malloc(sizeof(stackT));
    if (stack == NULL) {
        printf("Erro: Não há espaço suficiente para criar uma nova Stack.\n");
        return NULL;
    }
    stack->head = NULL;
    return stack;
}

void Push(stackT *stack, valueT processo) {
    nodeT *newNode = NewNode();
    if (newNode == NULL) return;

    newNode->value = processo;
    newNode->next = stack->head;
    stack->head = newNode;
}

valueT Pop(stackT *stack) {
    if (stack->head == NULL) {
        printf("Erro: A Stack está vazia.\n");
        valueT emptyProcess = {0, ""};
        return emptyProcess;
    }

    nodeT *temp = stack->head;
    valueT poppedValue = temp->value;
    stack->head = stack->head->next;
    free(temp);
    return poppedValue;
}

void EmptyStack(stackT *stack) {
    while (stack->head != NULL) {
        Pop(stack);
    }
}

void FreeStack(stackT *stack) {
    if (stack->head != NULL) {
        printf("Erro: A Stack não está vazia. Esvazie-a antes de liberar.\n");
        return;
    }
    free(stack);
}

int isEmpty(stackT *stack) {
    return stack->head == NULL;
}

void DisplayStack(stackT *stack) {
    nodeT *current = stack->head;
    printf("Conteúdo da Stack:\n");
    while (current != NULL) {
        printf("PID: %d, Comando: %s\n", current->value.pid, current->value.command);
        current = current->next;
    }
}

int main() {
    stackT *myStack = NewStack();

    valueT process1 = {1, "processo1"};
    valueT process2 = {2, "processo2"};
    valueT process3 = {3, "processo3"};

    Push(myStack, process1);
    Push(myStack, process2);
    Push(myStack, process3);

    DisplayStack(myStack);

    valueT poppedProcess = Pop(myStack);
    printf("Processo removido: PID: %d, Comando: %s\n", poppedProcess.pid, poppedProcess.command);

    DisplayStack(myStack);

    EmptyStack(myStack);
    printf("Stack esvaziada.\n");

    FreeStack(myStack);
    printf("Stack liberada.\n");

    return 0;
}

