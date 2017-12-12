#ifndef _linkQueue_h
#define _linkQueue_h

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

#endif // _linkQueue_h

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
