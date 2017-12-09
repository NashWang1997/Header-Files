#ifndef _Joseph_h
#define _Joseph_h
#include <iostream>
using namespace std;

template <class elemType>
class Joseph {
private:
    struct node {
        elemType data;
        node *next;
        node(const elemType &x, node *n = NULL) {data = x; next = n;}
        node():next(NULL) {}
        ~node() {}
    };
    node *head, *tail;
    int currentLength;
public:
    Joseph();
    ~Joseph() {Clear(); delete head;}
    void Clear();
    void SetHead(elemType &x) {head->data = x; currentLength++;}
    void input(const elemType &x);
    void traverse() const;
    int length() {return currentLength;}
    void Delete(int i);
    elemType gethead() {return head->data;}
    elemType gettail() {return tail->data;}
};
#endif // _Joseph_h

template <class elemType>
Joseph<elemType>::Joseph()
{
    head = tail = new node;
    head->next = tail;
    tail->next = head;
    currentLength = 0;
}
template <class elemType>
void Joseph<elemType>::Clear()
{
    node *p = head->next, *q;
    while (p != head) {
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}
template <class elemType>
void Joseph<elemType>::input(const elemType &x)
{
    node *pos;
    pos = new node(x, head);
    tail->next = pos;
    tail = pos;
    currentLength++;
}
template <class elemType>
void Joseph<elemType>::traverse() const
{
    node *p = head;
    for (int i=0; i<currentLength; ++i) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}
template <class elemType>
void Joseph<elemType>::Delete(int i)
{
    node *tmp = head, *pos = tail;
    if (i == -1) i = currentLength - 1;
    if (i == 0) {
        pos->next = tmp->next;
        delete head;
        head = pos->next;
    }
    else {
        for (int j=0; j<i; ++j) {
            pos = tmp;
            tmp = tmp->next;
        }
        pos->next = tmp->next;
        if (tmp == tail) tail = pos;
        delete tmp;
    }
    currentLength--;
}
