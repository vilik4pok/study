#include <iostream>

class Graph2;

class Node
{
    int vertex, cost;
    Node* next;
public:
    Node(int x, int y, Node* z);
    ~Node()
    {
        delete this->next;
    };
    int operator[](int x);
    friend Graph2;
};

Node::Node(int x, int y, Node* z)
{
    vertex = x;
    cost = y;
    next = z;
};

int Node::operator[](int x)
{
    Node* temp = this;
    int res = 0;
    while(temp)
    {
        if(x==temp->vertex)
            res = temp->cost;
        temp = temp->next;
    };
    return res;
};

class Graph2
{
    Node** g;
    int nodeCount;
public:
    Graph2();
    Graph2(int x);
    ~Graph2();
    void print();
    void test();
    void addNode();
    void addEdge(int vertex1, int vertex2, int cost);
    int getEccentricity(int start);
    void getDiameter();

};

Graph2::Graph2()
{
    g=NULL;
    nodeCount=0;
}


void Graph2::addNode()
{
    nodeCount++;
    if(!g)
    {
        g=new Node*[nodeCount];
        *g = NULL;
    }
    else
        {
            Node **temp = new Node*[nodeCount];
            int i, j;
            for(i=0; i<nodeCount-1; i++)
                temp[i] = g[i];
            delete[] g;
            temp[i] = NULL;
            g=temp;
        };
}

void Graph2::addEdge(int vertex1, int vertex2, int cost)
{
    if(vertex1<nodeCount&&vertex2<nodeCount&&cost!=0)
    {
        Node* temp = new Node(vertex2, cost, g[vertex1]);
        g[vertex1] = temp;
    };
}

Graph2::~Graph2()
{
    if(g)
    {
        for(int i=0; i<nodeCount; i++)
            delete g[i];
        delete[] g;
    };
}

void Graph2::print()
{
    Node* temp;
    for(int i = 0; i<nodeCount; i++)
    {
        temp = g[i];
        printf("%-2d", i);
        while(temp)
        {
            printf("%2d/%-2d ", temp->vertex, temp->cost);
            temp = temp->next;
        };
        printf("\n");
    };
}

int Graph2::getEccentricity(int start)
{
    int distance[nodeCount], i, j, min, minIndex, res=0;
    bool nodesVisit[nodeCount];
    for (i = 0; i < nodeCount; i++)
    {
        distance[i] = INT_MAX;
        nodesVisit[i] = false;
    };
    distance[start] = 0;
    for (i = 0; i < nodeCount - 1; i++)
    {
        for (j = 0,  min = INT_MAX; j < nodeCount; j++)
            if (!nodesVisit[j] && distance[j] <= min)
            {
                min = distance[j];
                minIndex = j;
            };
        nodesVisit[minIndex] = true;
        for (j = 0; j < nodeCount; j++)
            if (!nodesVisit[j] && (*g[minIndex])[j] && distance[minIndex] != INT_MAX)
                distance[j] = std::min(distance[j], distance[minIndex] + (*g[minIndex])[j]);
    }
    for(i = 0; i<nodeCount; i++)
    {
        if(distance[i]!=INT_MAX&&distance[i]>res)
            res = distance[i];
    };
    return res;
}

void Graph2::getDiameter()
{
    int res = 0;
    for(int i = 0; i<nodeCount; i++)
        res = std::max(res, this->getEccentricity(i));
    std::cout<<res<<"\n";
}

