#ifndef _seqList_h
#define _seqList_h

template <class elemType>
class seqList {
private:
    elemType *data;
    int currentLength;
    int maxSize;
    void doubleSpace();
    void Merge_LTH(int arr[], int reg[], int start, int END);
public:
    seqList(int initSize = 10);
    ~seqList() {delete [] data;}
    void input(elemType &x);
    void MergeSort_LTH();
    elemType visit(int i) const {return data[i];}
    bool InIt(elemType &x);
    void traverse();
    void REMOVE(elemType &x);
    int GetLength() {return currentLength;}
    void exchange(int i, elemType &x) {data[i] = x;}
};
#endif // _seqList_h

template <class elemType>
void seqList<elemType>::doubleSpace()
{
    elemType *tmp = data;
    maxSize *= 2;
    data = new elemType[maxSize];
    for (int i=0; i<currentLength; ++i) data[i] = tmp[i];
    delete [] tmp;
}

template <class elemType>
void seqList<elemType>::Merge_LTH(int arr[], int reg[], int start, int END)
{
    if (start >= END) return;
    int len = END - start, mid = (len >> 1) + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = END;
    Merge_LTH(arr, reg, start1, end1);
    Merge_LTH(arr, reg, start2, end2);
    int k = start;
    while (start1 <= end1 && start2 <= end2){
        if (arr[start1] < arr[start2]) {
            reg[k] = arr[start1];
            k++; start1++;
        }
        else {
            reg[k] = arr[start2];
            k++; start2++;
        }
    }
    while (start1 <= end1) {
        reg[k] = arr[start1];
        k++; start1++;
    }
    while (start2 <= end2) {
        reg[k] = arr[start2];
        k++; start2++;
    }
    for (k = start; k <= END; k++) {
        arr[k] = reg[k];
    }
}

template <class elemType>
seqList<elemType>::seqList(int initSize)
{
    data = new elemType[initSize];
    maxSize = initSize;
    currentLength = 0;
}

template <class elemType>
void seqList<elemType>::input(elemType &x)
{
    if (currentLength == maxSize) doubleSpace();
    data[currentLength] = x;
    currentLength++;
}

template <class elemType>
void seqList<elemType>::MergeSort_LTH()
{
    int reg[currentLength];
    Merge_LTH(data, reg, 0, currentLength - 1);
}

template <class elemType>
bool seqList<elemType>::InIt(elemType &x)
{
    int i;
    for (i=0; i<currentLength; ++i) if (x == data[i]) return true;
    return false;
}

template <class elemType>
void seqList<elemType>::traverse()
{
    cout << endl;
    for (int i=0; i<currentLength; ++i) cout << data[i] << ' ';
    cout << endl;
}

template <class elemType>
void seqList<elemType>::REMOVE(elemType &x)
{
    int i;
    for (i=0; i<currentLength; ++i) {
        if (data[i] == x) break;
    }
    if (i < currentLength) {
        for (int j=i; j<currentLength-1; ++j) data[j] = data[j+1];
        currentLength--;
    }
}
