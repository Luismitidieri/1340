#include <stdio.h>
#include <stdlib.h>

typedef struct {
int value;
int priority;
} Element;

int main() {
int n;
while (scanf("%d", &n) != EOF) {
int isStack = 1, isQueue = 1, isPQueue = 1;
int stackSize = 0, queueSize = 0, pQueueSize = 0;
Element *pQueue = malloc(n * sizeof(Element));


    for (int i = 0; i < n; i++) {
        int op, x;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d", &x);

            stackSize++;

            queueSize++;
            
            pQueueSize++;
            pQueue[pQueueSize-1].value = x;
            pQueue[pQueueSize-1].priority = x;
            int j = pQueueSize-1;
            while (j > 0 && pQueue[(j-1)/2].priority < pQueue[j].priority) {
                Element temp = pQueue[j];
                pQueue[j] = pQueue[(j-1)/2];
                pQueue[(j-1)/2] = temp;
                j = (j-1)/2;
            }
        } else {
            if (stackSize == 0 || queueSize == 0 || pQueueSize == 0) {
                isStack = 0;
                isQueue = 0;
                isPQueue = 0;
                continue;
            }

            stackSize--;

            int front = x;
            x = 0;
            if (queueSize > 0) {
                front = pQueue[0].value;
                for (int j = 0; j < queueSize-1; j++) {
                    pQueue[j] = pQueue[j+1];
                }
                queueSize--;
            }

            // Check priority queue
            int maxPriority = pQueue[0].priority;
            x = pQueue[0].value;
            pQueueSize--;
            if (pQueueSize > 0) {
                pQueue[0] = pQueue[pQueueSize];
                int j = 0;
                while (j*2+1 < pQueueSize) {
                    int child = j*2+1;
                    if (child+1 < pQueueSize && pQueue[child+1].priority > pQueue[child].priority) {
                        child++;
                    }
                    if (pQueue[j].priority < pQueue[child].priority) {
                        Element temp = pQueue[j];
                        pQueue[j] = pQueue[child];
                        pQueue[child] = temp;
                        j = child;
                    } else {
                        break;
                    }
                }
            }

            if (front != x) {
                isQueue = 0;
            }
            if (maxPriority != x) {
                isPQueue = 0;
            }
            if (isStack == 0 && isQueue == 0 && isPQueue == 0) {
                break;
            }
        }
    }

    if (isStack == 1 && isQueue == 0 && isPQueue == 0) {
        printf("stack\n");
    } else if (isStack == 0 && isQueue == 1 && isPQueue == 0) {
        printf("queue\n");
    } else if (isStack == 0 && isQueue == 0 && isPQueue == 1) {
        printf("priority queue\n");
    } else if (isStack == 0 && isQueue == 0 && isPQueue == 0) {
        printf("impossible\n");
    } else {
        printf("not sure\n");
    }

    free(pQueue);
}

return 0;
}
