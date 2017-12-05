#ifndef _adjListGraph_h
#define _adjListGraph_h
#include <iostream>
using namespace std;

template <class elemType>
class linkQueue {
private:
    struct node {
        elemType data;
        node *next;
        node(const elemType &x, node *N=NULL) {data = x; next = N;}
        node():next(NULL) {}
        ~node() {}
    };
    node *Front, *rear;
public:
    linkQueue() {Front = rear = NULL;}
    ~linkQueue();
    bool isEmpty() {return Front==NULL;}
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() {return Front->data;}
};

template <class elemType>
linkQueue<elemType>::~linkQueue()
{
    node *tmp;
    while (Front != NULL) {
        tmp = Front;
        Front = Front->next;
        delete tmp;
    }
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
    if (rear == NULL) Front = rear = new node(x);
    else {
        rear->next = new node(x);
        rear = rear->next;
    }
}

template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
    node *tmp = Front;
    elemType value = Front->data;
    Front = Front->next;
    if (Front == NULL) rear = NULL;
    delete tmp;
    return value;
}
template <class TypeOfVer>
class adjListGraph {
private:
    struct edgeNode {
        int End;
        edgeNode *next;
        edgeNode(int e, edgeNode *n = NULL) {End = e; next = n;}
    };
    struct verNode {
        TypeOfVer ver;
        edgeNode *head;
        verNode(edgeNode *h = NULL) {head = h;}
    };
    verNode *verList;
    int Vers, Edges;
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    bool Insert(int u, int v);
    bool Remove(int u, int v);
    bool exist(int u, int v) const;
    ~adjListGraph();
    void dfs() const;
    void dfs(int start, bool visited[]) const;
    void getParts(int start, bool visited[]) const;
    int getParts();
    int topSort() const;
};
#endif // _adjListGraph_h

template <class TypeOfVer>
adjListGraph<TypeOfVer>::adjListGraph(int vSize, const TypeOfVer d[])
{
    Vers = vSize; Edges = 0;
    verList = new verNode[vSize];
    for (int i=0; i<Vers; ++i) verList[i].ver = d[i];
}

template <class TypeOfVer>
bool adjListGraph<TypeOfVer>::Insert(int u, int v)
{
    verList[u].head = new edgeNode(v, verList[u].head);
    ++Edges;
    return true;
}

template <class TypeOfVer>
bool adjListGraph<TypeOfVer>::Remove(int u, int v)
{
    edgeNode *p = verList[u].head, *q;
    if (p == NULL) return false;
    if (p->End == v) {
        verList[u].head = p->next;
        delete p; --Edges;
        return true;
    }
    while (p->next!=NULL && p->next->End!=v) p = p->next;
    if (p->next == NULL) return false;
    q = p->next; p->next = q->next; delete q;
    --Edges;
    return true;
}

template <class TypeOfVer>
bool adjListGraph<TypeOfVer>::exist(int u, int v) const
{
    edgeNode *p = verList[u].head;
    while (p!=NULL && p->End!=v) p = p->next;
    if (p == NULL) return false; else return true;
}

template <class TypeOfVer>
adjListGraph<TypeOfVer>::~adjListGraph()
{
    int i;
    edgeNode *p;
    for (i=0; i<Vers; ++i) {
        while ((p=verList[i].head) != NULL) {
            verList[i].head = p->next;
            delete p;
        }
    }
    delete [] verList;
}

template <class TypeOfVer>
void adjListGraph<TypeOfVer>::dfs() const
{
    bool *visited = new bool[Vers];
    int i;
    for (i=0; i<Vers; ++i) visited[i] = false;
    cout << "DFS result:" << endl;
    for (i=0; i<Vers; ++i) {
        if (visited[i] == true) continue;
        dfs(i, visited);
        cout << endl;
    }
}

template <class TypeOfVer>
void adjListGraph<TypeOfVer>::dfs(int start, bool visited[]) const
{
    edgeNode *p = verList[start].head;
    cout << verList[start].ver << '\t';
    visited[start] = true;
    while (p != NULL) {
        if (visited[p->End] == false) dfs(p->End, visited);
        p = p->next;
    }
}

template <class TypeOfVer>
void adjListGraph<TypeOfVer>::getParts(int start, bool visited[]) const
{
    edgeNode *p = verList[start].head;
    visited[start] = true;
    while (p != NULL) {
        if (visited[p->End] == false) getParts(p->End, visited);
        p = p->next;
    }
}

template <class TypeOfVer>
int adjListGraph<TypeOfVer>::getParts()
{
    bool *visited = new bool[Vers];
    int i, k = 0;
    for (i=0; i<Vers; ++i) visited[i] = false;
    for (i=0; i<Vers; ++i) {
        if (visited[i] == true) continue;
        getParts(i, visited);
        k++;
    }
    return k;
}

template <class TypeOfVer>
int adjListGraph<TypeOfVer>::topSort() const
{
    linkQueue<int> q;
    edgeNode *p;
    int current, i, cnt = 0;
    int *inDegree = new int [Vers];
    for (i=0; i<Vers; ++i) inDegree[i] = 0;
    for (i=0; i<Vers; ++i) {
        for (p=verList[i].head; p!=NULL; p=p->next) ++inDegree[p->End];
    }
    for (i=0; i<Vers; ++i) if (inDegree[i] == 0) q.enQueue(i);
    q.enQueue(-1);
    //cout << "TopSort result:" << endl;
    while (!q.isEmpty()) {
        if (q.getHead() == -1) {
            cnt++;
            //cout << "\nnumber:" << number << endl;
            q.deQueue();
            if (!q.isEmpty()) q.enQueue(-1);
        }
        else {
            current = q.deQueue();
            //cout << verList[current].ver << '\t';
            for (p=verList[current].head; p!=NULL; p=p->next)
                if (--inDegree[p->End] == 0) q.enQueue(p->End);
        }
    }
    //cout << endl;
    return cnt;
}
