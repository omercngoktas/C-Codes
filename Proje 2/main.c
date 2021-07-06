#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*----------------------------------------------------------*/

struct socialNetListNode
{
    int destination, weight;
    struct socialNetListNode *next;
};

struct socialNetList
{
    struct socialNetListNode *header;
};

struct graph
{
    int maxSize;
    struct socialNetList *arrayList;
};

/*----------------------------------------------------------*/

struct minHeapNode 
{
    int dist;
    int number;
};

struct minHeap
{
    int maxSize, *pos ,capacity;
    struct minHeapNode **arrayList;
};

/*----------------------------------------------------------*/

struct socialNetListNode *newSocialNetNode(int destination, int weight)
{
    struct socialNetListNode *iterNode = (struct socialNetListNode *) malloc(sizeof(struct socialNetListNode));
    iterNode->destination = destination;
    iterNode->weight = weight;
    iterNode->next = NULL;
    return iterNode;
}

/*creating a new graph*/
struct graph *newGraph(int maxSize)
{
    int sourceNumber;
    struct graph *iterGraph = (struct graph *) malloc(sizeof(struct graph));
    iterGraph->maxSize = maxSize;
    iterGraph->arrayList = (struct socialNetList *) malloc(sizeof(struct socialNetList) * maxSize);

    for(sourceNumber = 0; sourceNumber < maxSize; ++sourceNumber)
    {
        iterGraph->arrayList[sourceNumber].header = NULL;
    }
    return iterGraph;
}

/*adding a new vertex to graph*/
void addVertex(struct graph *rootGraph, int source, int destination, int weight)
{
    struct socialNetListNode *iterSocialNode = newSocialNetNode(destination, weight);
    iterSocialNode->next = rootGraph->arrayList[source].header;
    rootGraph->arrayList[source].header = iterSocialNode;

    iterSocialNode = newSocialNetNode(source, weight);
    iterSocialNode->next = rootGraph->arrayList[destination].header;
    rootGraph->arrayList[destination].header = iterSocialNode;
}

/*----------------------------------------------------------*/

struct minHeapNode *newMinHeap(int dist, int number)
{
    struct minHeapNode *iterMinHeap = (struct minHeapNode *) malloc(sizeof(struct minHeapNode));
    iterMinHeap->dist = dist;
    iterMinHeap->number = number;
    return iterMinHeap;
}

struct minHeap *initializeMinHeap(int capacity)
{
    struct minHeap *iterMinHeap = (struct minHeap *) malloc(sizeof(struct minHeap));
    iterMinHeap->pos = (int *) malloc(sizeof(int) * capacity);
    iterMinHeap->maxSize = 0;
    iterMinHeap->capacity = capacity;
    iterMinHeap->arrayList = (struct minHeapNode **) malloc(sizeof(struct minHeapNode *) * capacity);
    return iterMinHeap;
}

void changeMinHeap(struct minHeapNode **first, struct minHeapNode **second)
{
    struct minHeapNode *temp = *first;
    *first = *second;
    *second = temp;
}

void minHeapify(struct minHeap *minHeap, int index)
{
    int small, leftOne, rightOne;
    small = index;
    /*because array list starts with 0, we should add 1*/
    leftOne = 2 * index + 1;
    rightOne = 2 * index + 2;

    if(leftOne < minHeap->maxSize && minHeap->arrayList[leftOne]->dist < minHeap->arrayList[small]->dist)
    {
        small = leftOne;
    }

    if(rightOne < minHeap->maxSize && minHeap->arrayList[rightOne]->dist < minHeap->arrayList[small]->dist)
    {
        small = rightOne;
    }

    if(small != index)
    {
        struct minHeapNode *smallNode = minHeap->arrayList[small];
        struct minHeapNode *indexNode = minHeap->arrayList[index];
        minHeap->pos[smallNode->number] = index;
        minHeap->pos[indexNode->number] = small;
        changeMinHeap(&minHeap->arrayList[small], &minHeap->arrayList[index]);
        minHeapify(minHeap, small);
    }
}

/*it will return a value as true or false(0 or 1)
which belongs to size of current minHeap*/
int isEmpty(struct minHeap *minHeap)
{
    return minHeap->maxSize == 0;
}

/*getting the smallest node from heap*/
struct minHeapNode *getMin(struct minHeap *minHeap)
{
    if(isEmpty(minHeap))
    {
        return NULL;
    }

    
    struct minHeapNode *headRoot = minHeap->arrayList[0];
    
    struct minHeapNode *lastNode = minHeap->arrayList[minHeap->maxSize - 1];
    minHeap->arrayList[0] = lastNode;

    minHeap->pos[headRoot->number] = minHeap->maxSize - 1;
    minHeap->pos[lastNode->number] = 0;

    --minHeap->maxSize;
    minHeapify(minHeap, 0);
    return headRoot;
}

void reduce(struct minHeap *minHeap, int number, int dist)
{
    int posNumber = minHeap->pos[number];

    minHeap->arrayList[posNumber]->dist = dist;

    while(posNumber && minHeap->arrayList[posNumber]->dist < minHeap->arrayList[(posNumber-1)/2]->dist)
    {
        minHeap->pos[minHeap->arrayList[posNumber]->number] = (posNumber - 1) / 2;
        minHeap->pos[minHeap->arrayList[(posNumber - 1) / 2]->number] = posNumber;
        changeMinHeap(&minHeap->arrayList[posNumber], &minHeap->arrayList[(posNumber-1)/2]);

        posNumber = (posNumber - 1) / 2;
    }
}

int inMinHeap(struct minHeap *minHeap, int number)
{
    if(minHeap->pos[number] < minHeap->maxSize)
    {
        return 0;
    }
    return 1;
}

void display(int dist[], int number)
{
    printf("Vertex Distance from Source:\n");
    int i;
    for(i = 0; i < number; ++i)
    {
        printf("%d\t\t%d\n", i, dist[i]);
    }
}

void algorithmDijkstra(struct graph *graph, int source)
{
    int maxSize = graph->maxSize;

    int dist[maxSize];

    struct minHeap *minHeap = initializeMinHeap(maxSize);

    int i;
    for(i = 0; i < maxSize; ++i)
    {
        dist[i] = INT_MAX;
        minHeap->arrayList[i] = newMinHeap(dist[i], maxSize);
        minHeap->pos[i] = i;
    }

    minHeap->arrayList[source] = newMinHeap(dist[source], source);
    minHeap->pos[source] = source;
    dist[source] = 0;
    reduce(minHeap, source, dist[source]);

    minHeap->maxSize = maxSize;

    while(!isEmpty(minHeap))
    {
        struct minHeapNode *minHeapNode = getMin(minHeap);

        int tempSize = minHeapNode->number;

        struct socialNetListNode *moveOn = graph->arrayList[tempSize].header;
        while(moveOn != NULL)
        {
            int tempDest = moveOn->destination;

            if(inMinHeap(minHeap, tempDest) && dist[tempSize] != INT_MAX && moveOn->weight + dist[tempSize] < dist[tempDest])
            {
                dist[tempDest] = dist[tempSize] + moveOn->weight;

                reduce(minHeap, tempDest, dist[tempDest]);
            }
            moveOn = moveOn->next;
        }
    }
    display(dist, maxSize);
}

int main()
{
    int maxSize = 9;
    struct graph *graph = newGraph(maxSize);
    addVertex(graph, 0, 1, 4);
	addVertex(graph, 0, 7, 8);
	addVertex(graph, 1, 2, 8);
	addVertex(graph, 1, 7, 11);
	addVertex(graph, 2, 3, 7);
	addVertex(graph, 2, 8, 2);
	addVertex(graph, 2, 5, 4);
	addVertex(graph, 3, 4, 9);
	addVertex(graph, 3, 5, 14);
	addVertex(graph, 4, 5, 10);
	addVertex(graph, 5, 6, 2);
	addVertex(graph, 6, 7, 1);
	addVertex(graph, 6, 8, 6);
	addVertex(graph, 7, 8, 7);

    algorithmDijkstra(graph, 0);

    return 0;
}