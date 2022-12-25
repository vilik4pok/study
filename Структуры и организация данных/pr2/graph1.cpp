#include <iostream>

class Graph1
{
    int **g, nodeCount;
public:
    Graph1();
    Graph1(int x);
    ~Graph1();
    void print();
    void test();
    void addNode();
    void addEdge(int vertex1, int vertex2, int cost);
    int getEccentricity(int start);
    void getDiameter();

};

Graph1::Graph1()
{
    g=NULL;
    nodeCount=0;
}


void Graph1::addNode()
{
    nodeCount++;
    if(!g)
    {
        g=new int*[nodeCount];
        *g = new int[nodeCount];
        **g = 0;
    }
    else
        {
            int **temp = new int*[nodeCount], i, j;
            for(i=0; i<nodeCount-1; i++)
            {
                temp[i] = new int[nodeCount];
                memcpy(temp[i], g[i], (nodeCount-1)*sizeof(int));
                temp[i][nodeCount-1] = 0;
                delete[] g[i];
            };
            delete[] g;
            temp[i] = new int[nodeCount];
            for(j=0; j<nodeCount; j++)
                temp[i][j] = 0;
            g = temp;
        }
}

void Graph1::addEdge(int vertex1, int vertex2, int cost)
{
    if(vertex1<nodeCount&&vertex2<nodeCount)
        g[vertex1][vertex2] = cost;
}

Graph1::~Graph1()
{
    if(g)
    {
        for(int i=0; i<nodeCount; i++)
            delete[] g[i];
        delete[] g;
    };
}


void Graph1::print()
{
    for(int i=0; i<nodeCount; i++)
    {
        for(int j=0; j<nodeCount; j++)
            printf("%-5d ", g[i][j]);
        std::cout<<"\n";
    };
}

int Graph1::getEccentricity(int start)
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
            if (!nodesVisit[j] && g[minIndex][j] && distance[minIndex] != INT_MAX)
                distance[j] = std::min(distance[j], distance[minIndex] + g[minIndex][j]);
    }
    for(i = 0; i<nodeCount; i++)
    {
        if(distance[i]!=INT_MAX&&distance[i]>res)
            res = distance[i];
    };
    return res;
}

void Graph1::getDiameter()
{
    int res = 0;
    for(int i = 0; i<nodeCount; i++)
        res = std::max(res, this->getEccentricity(i));
    std::cout<<res<<"\n";
}

