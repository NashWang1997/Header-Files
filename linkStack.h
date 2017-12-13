#ifndef _linkStack_h
#define _linkStack_h

template <class elemType>
class linkStack {
private:
    struct node {
        elemType data;
        node *next;
        node(const elemType &x, node *N=NULL) {data = x; next = N;}
        node(): next(NULL) {}
        ~node() {}
    };
    node *elem;
public:
    linkStack() {elem = NULL;}
    ~linkStack();
    bool isEmpty() const {return elem == NULL;}
    void push(const elemType &x) {node *tmp = new node(x, elem); elem = tmp;}
    elemType pop();
    elemType top() const {return elem->data;}
};
#endif // _linkStack_h

template <class elemType>
linkStack<elemType>::~linkStack()
{
    node *tmp;
    while (elem != NULL) {
        tmp = elem;
        elem = elem->next;
        delete tmp;
    }
}

template <class elemType>
elemType linkStack<elemType>::pop()
{
    node *tmp = elem;
    elemType x = tmp->data;
    elem = elem->next;
    delete tmp;
    return x;
}
