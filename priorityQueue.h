#ifndef _priorityQueue_h
#define _priorityQueue_h

template <class Type>
class priorityQueue {
private:
    int currentSize;
    Type *ARRAY;
    int maxSize;
    void doubleSpace();
    void buildHeap() {for (int i=currentSize/2; i>0; i--) percolateDown(i);}
    void percolateDown(int hole);
public:
    priorityQueue(int capacity = 10) {ARRAY = new Type[capacity]; maxSize = capacity; currentSize = 0;}
    priorityQueue(const Type data[], int SIZE);
    ~priorityQueue() {delete [] ARRAY;}
    bool isEmpty() const {return currentSize == 0;}
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() {return ARRAY[1];}
    Type visit(int i) {return ARRAY[i];}
    int getsize() {return currentSize;}
    void decrease(int i, int j) {ARRAY[i] -= j; buildHeap();} //将第i个节点的优先级值减少j
};
#endif // _priorityQueue_h

template <class Type>
void priorityQueue<Type>::doubleSpace()
{
    Type *tmp = ARRAY;
    maxSize *= 2;
    ARRAY = new Type[maxSize];
    for (int i=0; i<=currentSize; ++i) ARRAY[i] = tmp[i];
    delete [] tmp;
}

template <class Type>
void priorityQueue<Type>::percolateDown(int hole)
{
    int child;
    Type tmp = ARRAY[hole];
    for (; hole*2<=currentSize; hole=child) {
        child = hole * 2;
        if (child!=currentSize&&ARRAY[child+1]<ARRAY[child]) child++;
        if (ARRAY[child]<tmp) ARRAY[hole] = ARRAY[child];
        else break;
    }
    ARRAY[hole] = tmp;
}

template <class Type>
priorityQueue<Type>::priorityQueue(const Type data[], int SIZE):maxSize(SIZE+10), currentSize(SIZE)
{
    ARRAY = new Type[maxSize];
    for (int i=0; i<SIZE; ++i) ARRAY[i+1] = data[i];
    buildHeap();
}

template <class Type>
void priorityQueue<Type>::enQueue(const Type &x)
{
    if (currentSize == maxSize-1) doubleSpace();
    int hole = ++currentSize;
    for (; hole>1&&x<ARRAY[hole/2]; hole/=2) ARRAY[hole] = ARRAY[hole/2];
    ARRAY[hole] = x;
}

template <class Type>
Type priorityQueue<Type>::deQueue()
{
    Type minItem;
    minItem = ARRAY[1];
    ARRAY[1] = ARRAY[currentSize--];
    percolateDown(1);
    return minItem;
}
