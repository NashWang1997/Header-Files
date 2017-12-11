#ifndef _linkList_single_h
#define _linkList_single_h
#include <iostream>
using namespace std;

template <class elemType>
class linkList_single {
    template <class T>
    friend linkList_single<T> operator+(const linkList_single<T> &l1, const linkList_single<T> &l2);
    template <class T>
    friend ostream& operator<<(ostream &os, const linkList_single<T> &obj);
private:
    struct node {
        elemType data;
        node *next;
        node(const elemType &x, node *n = NULL) {data = x; next = n;}
        node():next(NULL) {}
        ~node() {}
    };
    node *head, *rear;
    int currentLength;
public:
    linkList_single() {head = rear = new node; currentLength = 0;}
    ~linkList_single() {Clear(); delete head;}
    void Clear();
    int getLength() const {return currentLength;}
    void input(elemType &x);
    elemType getTail() {return rear->data;}
    elemType visit(int i);
};

#endif // _linkList_single_h

template <class elemType>
linkList_single<elemType> operator+ (const linkList_single<elemType> &l1, const linkList_single<elemType> &l2)
{
    linkList_single<elemType> tmp; linkList_single<elemType> tmp0;
    int i;
    tmp0.rear = l1.head->next;
    for (i=0; i<l1.getLength(); ++i) {
        tmp.input(tmp0.rear->data);
        tmp0.rear = tmp0.rear->next;
    }
    tmp0.rear = l2.head->next;
    for (i=0; i<l2.getLength(); ++i) {
        tmp.input(tmp0.rear->data);
        tmp0.rear = tmp0.rear->next;
    }
    return tmp;
}
template <class elemType>
ostream& operator<<(ostream &os, const linkList_single<elemType> &obj)
{
    linkList_single<elemType> tmp;
    tmp.rear = obj.head->next;
    for (int i=0; i<obj.getLength(); ++i) {
        os << tmp.rear->data << ' ';
        tmp.rear = tmp.rear->next;
    }
    return os;
}
template <class elemType>
void linkList_single<elemType>::Clear()
{
    node *p = head->next, *q;
    int i = 0;
    while (i < currentLength) {
        q = p->next;
        delete p;
        p = q;
        i++;
    }
    currentLength = 0;
}
template <class elemType>
void linkList_single<elemType>::input(elemType &x)
{
    node *p;
    p = new node(x);
    rear->next = p;
    rear = p;
    rear->next = NULL;
    currentLength++;
}

template <class elemType>
elemType linkList_single<elemType>::visit(int i)
{
    node *p = head;
    for (int j=0; j<i; ++j) p = p->next;
    return p->data;
}
