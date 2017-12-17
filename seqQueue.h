#ifndef _seqQueue_h
#define _seqQueue_h

template <class elemType>
class seqQueue {
private:
    elemType *elem;
    int maxSize;
    int Front, rear;
    void doubleSpace();
public:
    seqQueue(int Size = 10) {elem = new elemType[Size]; maxSize = Size; Front = rear = 0;}
    ~seqQueue() {delete [] elem;}
    bool isEmpty() {return Front == rear;}
    void enQueue(const elemType &x);
    elemType deQueue() {Front = (Front + 1) % maxSize; return elem[Front];}
    elemType leave() {rear = (rear - 1) % maxSize; return elem[rear];}
    elemType getHead() {return elem[(Front+1)%maxSize];}
    elemType getTail() {return elem[rear % maxSize];}
};
#endif // _seqQueue_h

template <class elemType>
void seqQueue<elemType>::doubleSpace()
{
    elemType *tmp = elem;
    elem = new elemType[2 * maxSize];
    for (int i=1; i<maxSize; ++i) elem[i] = tmp[(Front+i) % maxSize];
    Front = 0; rear = maxSize - 1;
    maxSize *= 2;
    delete tmp;
}
template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x)
{
    if ((rear+1)%maxSize == Front) doubleSpace();
    rear = (rear + 1) % maxSize;
    elem[rear] = x;
}
