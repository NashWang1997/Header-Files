#ifndef _seqStack_h
#define _seqStack_h

template <class elemType>
class seqStack {
private:
    elemType *elem;
    int top_p;
    int maxSize;
    void doubleSpace();
public:
    seqStack(int initSize = 101);
    ~seqStack() {delete [] elem;}
    bool isEmpty() const {return top_p == -1;}
    void push(const elemType &x);
    elemType pop() {return elem[top_p--];}
    elemType top() const {return elem[top_p];}
};
#endif // _seqStack_h

template <class elemType>
void seqStack<elemType>::doubleSpace()
{
    elemType *tmp = elem;
    elem = new elemType[2 * maxSize];
    for (int i=0; i<maxSize; ++i) elem[i] = tmp[i];
    maxSize *= 2;
    delete [] tmp;
}
template <class elemType>
seqStack<elemType>::seqStack(int initSize)
{
    maxSize = initSize;
    elem = new elemType[initSize];
    top_p = -1;
}
template <class elemType>
void seqStack<elemType>::push(const elemType &x)
{
    if (top_p == maxSize - 1) doubleSpace();
    elem[++top_p] = x;
}
