#ifndef _linkList_h
#define _linkList_h
#include <iostream>
using namespace std;

template <class elemType>
class linkList {
private:
    struct node {
        elemType data;
        node *prev, *next;
        node(const elemType &x, node *p = NULL, node *n = NULL) {data = x; next = n; prev = p;}
        node():next(NULL), prev(NULL) {}
        ~node() {}
    };
    node *head, *tail;
    int currentLength;
    node *Move(int i) const
    {
        node *p = head->next;
        while (i--) p = p->next;
        return p;
    }
public:
    linkList();
    ~linkList() {Clear(); delete head; delete tail;}
    void Clear();
    int length() const {return currentLength;}
    void Insert(int i, const elemType &x);
    void Remove(int i);
    int Search(const elemType &x) const;
    elemType visit(int i) const {node *p = Move(i); return p->data;}
    void traverse() const;
    void traverse_back() const;
    void add(linkList<elemType> *a, linkList<elemType> *b);
};
#endif // _linkList_h

template <class elemType>
linkList<elemType>::linkList()
{
    head = new node;
    head->next = tail = new node;
    tail->prev = head;
    currentLength = 0;
}
template <class elemType>
void linkList<elemType>::Clear()
{
    node *p = head->next, *q;
    head->next = tail;
    tail->prev = head;
    while (p != tail) {
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}
template <class elemType>
void linkList<elemType>::Insert(int i, const elemType &x)
{
    node *pos, *tmp;
    pos = Move(i);
    tmp = new node(x, pos->prev, pos);
    pos->prev->next = tmp;
    pos->prev = tmp;
    ++currentLength;
}
template <class elemType>
void linkList<elemType>::Remove(int i)
{
    node *pos;
    pos = Move(i);
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    delete pos;
    --currentLength;
}
template <class elemType>
int linkList<elemType>::Search(const elemType &x) const
{
    node *p = head->next;
    int i = 0;
    while (p!=tail && p->data!=x) {p = p->next; ++i;}
    if (p == tail) return -1; else return i;
}
template <class elemType>
void linkList<elemType>::traverse() const
{
    node *p = head->next;
    cout << endl;
    while (p != tail) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}
template <class elemType>
void linkList<elemType>::traverse_back() const
{
    node *p = tail->prev;
    while (p->data == 0) {
        p = p->prev;
    }
    if (p != head)
        while (p != head) {
            cout << p->data;
            p = p->prev;
        }
    else cout << '0' << endl;
}
template <class elemType>
void linkList<elemType>::add(linkList<elemType> *a, linkList<elemType> *b)
{
    node *p = a->head->next, *q = b->head->next, *r = head->next;
    int tmp = 0;
    while (p!=a->tail && q!=b->tail) {
        r->data = (p->data + q->data + tmp) % 10;
        tmp = (p->data + q->data + tmp) / 10;
        p = p->next; q = q->next; r = r->next;
    }
    if (p != a->tail)
        while (p != a->tail) {
            r->data = (p->data + tmp) % 10;
            tmp = (p->data + tmp) / 10;
            p = p->next; r = r->next;
        }
    else if (q != b->tail)
        while (q != b->tail) {
            r->data = (q->data + tmp) % 10;
            tmp = (q->data + tmp) / 10;
            q = q->next; r = r->next;
        }
    if (tmp != 0) r->data = tmp;
}
