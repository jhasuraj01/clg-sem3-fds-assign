#include <stdio.h>

struct Queue {
    int read;
    int write;
    int MAX_SIZE;
    int array[];
};

void enqueue(int data, struct Queue *queue) {
    if((queue->write + 1) % queue->MAX_SIZE != queue->read) {
        queue->array[queue->write] = data;
        queue->write = (queue->write + 1) % queue->MAX_SIZE;
    }
    else {
        printf("Overflow Detected!");
    }
}

int isEmpty(struct Queue *queue) {
    return (queue->read == queue->write);
}

int dequeue(struct Queue *queue) {
    if(!isEmpty(queue)) {
        int result = queue->array[queue->read];
        queue->read = (queue->read + 1) % queue->MAX_SIZE;
        return result;
    }
    printf("Attempting to dequeue Empty Queue!");
    return 0;
}


int main() {

    int MAX_QUEUE_SIZE = 5;

    struct Queue queue;
    queue.array[MAX_QUEUE_SIZE];
    queue.read = 0;
    queue.write = 0;
    queue.MAX_SIZE = MAX_QUEUE_SIZE;

    enqueue(1, &queue);
    enqueue(2, &queue);
    enqueue(3, &queue);
    enqueue(4, &queue);

    printf("%d ", dequeue(&queue));
    printf("%d ", dequeue(&queue));

    enqueue(5, &queue);
    enqueue(6, &queue);

    printf("%d ", dequeue(&queue));
    printf("%d ", dequeue(&queue));
    printf("%d ", dequeue(&queue));
    printf("%d ", dequeue(&queue));
    
    enqueue(1, &queue);
    enqueue(2, &queue);
    enqueue(3, &queue);
    enqueue(4, &queue);

    printf("%d ", dequeue(&queue));
    printf("%d ", dequeue(&queue));
    printf("%d ", dequeue(&queue));
    printf("%d ", dequeue(&queue));

    return 0;
}