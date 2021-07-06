#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 256
#define CHAR_SIZE 10

/*---------------------------------------------------------------------------------------*/

/*those structures are for representing graph*/
/*this struct contains vertices and their weight*/
struct socialNetListNode
{
	int destination, weight;
	struct socialNetListNode *next;
};

/*this struct represents the upper struct*/
struct socialNetList
{
	struct socialNetListNode *header;
};

/*represents the graph and contains maxSize as how many vertices there are*/
struct graph
{
	int maxSize;
	struct socialNetList *arrayList;
};

/*---------------------------------------------------------------------------------------*/

/*those structures are for minheaps*/
/*this struct represents minHeap node*/
struct minHeapNode
{
	int maxSize, destination;
};

/*this structure represent min heap*/
struct minHeap
{
	int size; /*size represents how many nodes there are as vertices*/	
	int capacity; /*capacity represents minHeap's capacity*/
	int *position; /*position is going to be using for reduce() function*/
	struct minHeapNode **arrayList;
};

/*---------------------------------------------------------------------------------------*/

/*because of previous impicit declaration, all of the functions written here to avoid this bug*/
struct socialNetListNode *newsocialNetListNode(int destination, int weight);
struct graph *newGraph(int size);
struct minHeap* newMinHeap(int capacity);
void addVertex(struct graph *graph, int source, int destination, int weight);
struct minHeapNode* newMinHeapNode(int maxSize, int destination);
void changeMinHeap(struct minHeapNode** firstHeapNode, struct minHeapNode** secondHeapNode);
void heapifyingMinHeap(struct minHeap* minHeap, int index);
int isInMinHeap(struct minHeap *minHeap, int vertice);
int isEmpty(struct minHeap* minHeap);
struct minHeapNode *getMin(struct minHeap* minHeap);
void reduce(struct minHeap* minHeap, int maxSize, int destination);
void algorithmDijkstra(struct graph *graph, int source);
void display(int destination[], int maxSize);

/*---------------------------------------------------------------------------------------*/

/*this function is using to add a new vertice*/
struct socialNetListNode *newsocialNetListNode(int destination, int weight)
{
	/*allocating a place from memory for new vertice*/
	struct socialNetListNode *newNode = (struct socialNetListNode*) malloc(sizeof(struct socialNetListNode));
	/*adding values to current vertice*/
	newNode->destination = destination;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

/*creating a new graph according to number of vertices*/
struct graph *newGraph(int size)
{
	/*allocating a place from memory for new graph*/
	struct graph *graph = (struct graph *) malloc(sizeof(struct graph));
	graph->maxSize = size;

	/*allocating a place according to size of vertices*/
	graph->arrayList = (struct socialNetList *) malloc(sizeof(struct socialNetList) * size);

	/*allocated places for arrayList will be initializing as value NULL*/
    int i;
	for (i = 0; i < size; ++i)
	{
		graph->arrayList[i].header = NULL;
	}

	return graph;
}

/*this function is using to create min heap*/
struct minHeap* newMinHeap(int capacity)
{
	/*allocating memory for min heap according to capacity*/
	struct minHeap* minHeap = (struct minHeap*) malloc(sizeof(struct minHeap));
	/*allocating one int place from memory for position which is gonna be using for reduce() function later*/
	minHeap->position = (int *)malloc(capacity * sizeof(int));
	/*signing size as zero becuase there is no any value yet*/
	minHeap->size = 0;
	minHeap->capacity = capacity;
	/*allocating memory for arrayList which is in min heap*/
	minHeap->arrayList = (struct minHeapNode**) malloc(capacity * sizeof(struct minHeapNode*));
	return minHeap;
}

/*this function adds a new vertice to current graph*/
void addVertex(struct graph *graph, int source, int destination, int weight)
{
	/*new vertices are sending newsocialNetListNode to add nodes*/
	struct socialNetListNode *newNode = newsocialNetListNode(destination, weight);
	/*adding vertices to node*/
	newNode->next = graph->arrayList[source].header;
	graph->arrayList[source].header = newNode;

	/*because graph is not organized yet, edge is gonna be adding to source*/
	newNode = newsocialNetListNode(source, weight);
	newNode->next = graph->arrayList[destination].header;
	graph->arrayList[destination].header = newNode;
}

/*this function creates min heap node*/
struct minHeapNode* newMinHeapNode(int maxSize, int destination)
{
	/*allocating memory for minheapnode*/
	struct minHeapNode* minHeapNode = (struct minHeapNode*) malloc(sizeof(struct minHeapNode));

	/*assigning values to values of node*/
	minHeapNode->maxSize = maxSize;
	minHeapNode->destination = destination;
	return minHeapNode;
}

/*---------------------------------------------------------------------------------------*/

/*this function changes to values of min heap node for heapifying*/
void changeMinHeap(struct minHeapNode** firstHeapNode, struct minHeapNode** secondHeapNode)
{
	/*holding the value after changing first value, then it gets its value from this tempminheapnode*/
	struct minHeapNode* tempMinHeapNode = *firstHeapNode;
	*firstHeapNode = *secondHeapNode;
	*secondHeapNode = tempMinHeapNode;
}

/*unorganized min heap is organizing with this function (heapifying)*/
void heapifyingMinHeap(struct minHeap* minHeap, int index)
{
	int smallest, leftNode, rightNode;
	smallest = index;

	/*due to that we didn't start from index 1, 1 should be adding to left node after multiplication
	also positionition of right node is 2*index+1 but in this situation also 1 should be adding to here*/
	leftNode = 1 + (index * 2);
	rightNode = (index * 2) + 2;

	/*checking the condition if the positionition of current node smaller than smallest node destination*/
	if ((minHeap->arrayList[leftNode]->destination < minHeap->arrayList[smallest]->destination) && (leftNode < minHeap->size))
	{
		/*assigning smallest node as left node because left node's positionition is smaller*/
		smallest = leftNode;
	}

	/*checking if positionition of the current node is smaller than smallest node destination*/
	if ((minHeap->arrayList[rightNode]->destination < minHeap->arrayList[smallest]->destination) && (rightNode < minHeap->size))
	{
		/*assigning smallest node as right node because positionition of right node is smaller*/
		smallest = rightNode;
	}

	/*because min heap is not organized completly, it should be heapifying again*/
	if (smallest != index)
	{
		/*those nodes will be using to change*/
		struct minHeapNode *smallestNode = minHeap->arrayList[smallest];
		struct minHeapNode *indexNode = minHeap->arrayList[index];

		/*changing the positionition of node*/
		minHeap->position[smallestNode->maxSize] = index;
		minHeap->position[indexNode->maxSize] = smallest;
		
		/*with using function changeMinHeap(), positionitions change then heapifyingMinHeap is calling again until heapifying is not required*/
		changeMinHeap(&minHeap->arrayList[smallest], &minHeap->arrayList[index]);
		heapifyingMinHeap(minHeap, smallest);
	}
}

/*checking if vertice is in min heap*/
int isInMinHeap(struct minHeap *minHeap, int vertice)
{
	/*returning 1 because given vertice is in min heap*/
	if (minHeap->position[vertice] < minHeap->size)
		return 1;
	/*returning zero because given vertice is not in min heap*/
	return 0;
}

/*checking if given min heap is empty or not*/
int isEmpty(struct minHeap* minHeap)
{
	/*returning one(true value) because min heap size is empty, means there is nothing*/
	if(minHeap->size == 0)
	{
		return 1;
	}
	/*returning zero(false value) because min heap is not empty*/
	return 0;
}

/*getting the minimum node from min heap*/
struct minHeapNode *getMin(struct minHeap* minHeap)
{
	/*first of all, it must be checking if min heap is empty or not. if it is empty then value NULL must be returning*/
	if (isEmpty(minHeap))
		return NULL;

	/*assigning the root of node to minheap *root*/
	struct minHeapNode *root = minHeap->arrayList[0];

	/*and here, root and the last node change their positionition*/
	struct minHeapNode *lastNode = minHeap->arrayList[minHeap->size - 1];
	/*assigning root to last node*/
	minHeap->arrayList[0] = lastNode;

	/*updating last node's positionition*/
	minHeap->position[root->maxSize] = minHeap->size-1;
	minHeap->position[lastNode->maxSize] = 0;

	/*decreasing the size of min heap*/
	--minHeap->size;
	/*then min heap should be heapifiying*/
	heapifyingMinHeap(minHeap, 0);

	return root;
}

/*this function reduces destination of vertice*/
void reduce(struct minHeap* minHeap, int maxSize, int destination)
{
	/*getting the index of the min heap*/
	int size = minHeap->position[maxSize];

	/*updating min heap destination with the given destination*/
	minHeap->arrayList[size]->destination = destination;

	// Travel up while the complete
	// tree is not hepified.
	// This is a O(Logn) loop
	while (size && minHeap->arrayList[size]->destination < minHeap->arrayList[(size - 1) / 2]->destination)
	{
		// Swap this node with its parent
		minHeap->position[minHeap->arrayList[size]->maxSize] = (size-1)/2;
		minHeap->position[minHeap->arrayList[(size-1)/2]->maxSize] = size;
		changeMinHeap(&minHeap->arrayList[size], &minHeap->arrayList[(size - 1) / 2]);

		// move to parent index
		size = (size - 1) / 2;
	}
}

/*calculating distance between vertices with using dijsktra algorithm*/
void algorithmDijkstra(struct graph *graph, int source)
{
	/*getting the number of vertex from the graph*/
	int maxSize = graph->maxSize;
	
	/*initializing int array (according to number of vertex (maxSize)) for weights*/
	int destination[maxSize];	
	struct minHeap *minHeap = newMinHeap(maxSize);
	
	/*assigning min heap from vertices*/
    int i;
	for (i = 0; i < maxSize; ++i)
	{
		destination[i] = MAX_SIZE;
		minHeap->arrayList[i] = newMinHeapNode(i, destination[i]);
		minHeap->position[i] = i;
	}

	minHeap->arrayList[source] = newMinHeapNode(source, destination[source]);
	minHeap->position[source] = source;
	destination[source] = 0;
	reduce(minHeap, source, destination[source]);

	/*assigning number of vertices in graph*/
	minHeap->size = maxSize;

	while (!isEmpty(minHeap))
	{
		/*getting shortest distance*/
		struct minHeapNode* minHeapNode = getMin(minHeap);
	
		/*getting number of vertices*/
		int tempMaxSize = minHeapNode->maxSize;

		struct socialNetListNode *moveOn = graph->arrayList[tempMaxSize].header;

		while (moveOn != NULL)
		{
			int tempDestination = moveOn->destination;
			if ((destination[tempMaxSize] != MAX_SIZE) && (moveOn->weight + destination[tempMaxSize] < destination[tempDestination]) && (isInMinHeap(minHeap, tempDestination)))
			{
				destination[tempDestination] = destination[tempMaxSize] + moveOn->weight;
				/*changing distance between vertices*/
				reduce(minHeap, tempDestination, destination[tempDestination]);
			}
			moveOn = moveOn->next;
		}
	}
	/*displaying shortest distance between vertices*/
	display(destination, maxSize);
}

/*displaying the result*/
void display(int destination[], int maxSize)
{
	printf("maxSize: %d\n", maxSize);
	printf("Vertex \tDistance from Source\n");
    int i;
	for (i = 0; i < maxSize; ++i)
	{
		printf("  %d \t\t %d\n", i, destination[i]);
	}
}

/*---------------------------------------------------------------------------------------*/

/*this function asks user to input file's name, checks if the input file exists.
then reads vertices and weights from input file to process*/
int inputFile()
{
	/*it will be using for input file name which is entering by user*/
	char fileName[MAX_SIZE];

	char source[CHAR_SIZE], destination[CHAR_SIZE];
	int weight;

	/*printf("Enter the name of the input file(i.e. input.txt): ");
	scanf("%s", fileName);*/
	printf("----------------------------------------------------------------------------------\n");
	FILE *inputText = fopen("input.txt", "r");
	if(inputText == NULL)
	{
		/*printing input file's name is wrong or file doesn't exist*/
		printf("Please check the input file name.\n");
		/*returning zero(false value) because file doesn't exist*/
		return 0;
	}

	while(!feof(inputText))
	{
		fscanf(inputText, "%[^,],%[^,],%d\n", source, destination, &weight);
		printf("%s %s %d\n", source, destination, weight);
	}

	
}

/*---------------------------------------------------------------------------------------*/

int main()
{
	int V = 9;
	struct graph *graph = newGraph(V);
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

	/*
	addVertex(graph, 'A', 'B', 2);
	addVertex(graph, 'A', 'D', 7);
	addVertex(graph, 'A', 'F', 12);
	addVertex(graph, 'A', 'G', 2);
	addVertex(graph, 'B', 'C', 1);
	addVertex(graph, 'B', 'D', 4);
	addVertex(graph, 'B', 'E', 3);
	addVertex(graph, 'B', 'G', 5);
	addVertex(graph, 'C', 'E', 4);
	addVertex(graph, 'C', 'G', 4);
	addVertex(graph, 'D', 'E', 1);
	addVertex(graph, 'D', 'H', 5);
	addVertex(graph, 'E', 'H', 7);
	addVertex(graph, 'F', 'H', 3);
	*/

	algorithmDijkstra(graph, 0);
	//inputFile();





	return 0;
}