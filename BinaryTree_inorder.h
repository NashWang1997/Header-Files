#ifndef _BinaryTree_inorder_h
#define _BinaryTree_inorder_h
#include <iostream>
using namespace std;

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


class BinaryTree {
private:
    struct Node {
        Node *left, *right;
        int data;
        int place_inorder;
        Node():left(NULL), right(NULL) {}
        Node(int item, int p, Node *L=NULL, Node *R=NULL):data(item),place_inorder(p),left(L),right(R) {}
        ~Node() {}
    };
    struct StNode {
        Node *node;
        int TimesPop;
        StNode(Node *N=NULL):node(N), TimesPop(0) {}
    };
    Node *root;
    int Size;
    void CLEAR(Node *t);
    int height(Node *t) const;
    int SIZE(Node *t) const;
    void preOrder_re(Node *t) const;
    void postOrder_re(Node *t) const;
    void midOrder_re(Node *t) const;
public:
    BinaryTree():root(NULL) {}
    BinaryTree(const int &value, int p) {root = new Node(value, p);}
    BinaryTree(Node *P) {root = P;}
    ~BinaryTree() {CLEAR();}
    int getRoot() const {return root->data;}
    int getLeft() const {return root->left->data;}
    int getRight() const {return root->right->data;}
    void SetSize(int n) {Size = n;}
    int getSize() const {return Size;}
    void makeTree(const int &x, int p, BinaryTree &lt, BinaryTree &rt);
    void delLeft();
    void delRight();
    bool isEmpty() const {return root == NULL;}
    void CLEAR() {if(root != NULL) CLEAR(root); root = NULL;}
    int SIZE() const {return SIZE(root);}
    int height() const {return height(root);}
    void preOrder_re() const;
    void postOrder_re() const;
    void midOrder_re() const;
    void postOrder() const;
    void createTree();
};
#endif // _BinaryTree_inorder_h

void BinaryTree::CLEAR(Node *t)
{
    if (t->left != NULL) CLEAR(t->left);
    if (t->right != NULL) CLEAR(t->right);
    delete t;
}
int BinaryTree::height(Node *t) const
{
    if (t == NULL) return 0;
    else {
        int lt = height(t->left), rt = height(t->right);
        return 1 + ((lt>rt) ? lt : rt);
    }
}
int BinaryTree::SIZE(Node *t) const
{
    if (t == NULL) return 0;
    return 1 + SIZE(t->left) + SIZE(t->right);
}
void BinaryTree::preOrder_re(Node *t) const
{
    if (t != NULL) {
        cout << t->data << ' ';
        preOrder_re(t->left);
        preOrder_re(t->right);
    }
}
void BinaryTree::postOrder_re(Node *t) const
{
    if (t != NULL) {
        postOrder_re(t->left);
        postOrder_re(t->right);
        cout << t->data << ' ';
    }
}
void BinaryTree::midOrder_re(Node *t) const
{
    if (t != NULL) {
        midOrder_re(t->left);
        cout << t->data << ' ';
        midOrder_re(t->right);
    }
}
void BinaryTree::makeTree(const int &x, int p, BinaryTree &lt, BinaryTree &rt)
{
    root = new Node(x, p, lt.root, rt.root);
    lt.root = NULL;
    rt.root = NULL;
}
void BinaryTree::delLeft()
{
    BinaryTree tmp = root->left;
    root->left = NULL;
    tmp.CLEAR();
}
void BinaryTree::delRight()
{
    BinaryTree tmp = root->right;
    root->right = NULL;
    tmp.CLEAR();
}
void BinaryTree::preOrder_re() const
{
    if (root != NULL) {
        cout << "\n";
        preOrder_re(root);
    }
}
void BinaryTree::postOrder_re() const
{
    if (root != NULL) {
        cout << "\n";
        postOrder_re(root);
    }
}
void BinaryTree::midOrder_re() const
{
    if (root != NULL) {
        cout << "\n";
        midOrder_re(root);
    }
}
void BinaryTree::postOrder() const
{
    linkStack<StNode> s;
    StNode current(root);
    s.push(current);
    int Size = getSize(), i = 0;
    //int *place_in_order = new int [Size];
    int *post = new int [Size];
    while (!s.isEmpty()) {
        current = s.pop();
        if (++current.TimesPop == 3) {
            post[i] = current.node->data;
            //place_in_order[post[i]-1] = current.node->place_inorder;
            i++;
            continue;
        }
        s.push(current);
        if (current.TimesPop == 1) {
            if (current.node->left != NULL) s.push(StNode(current.node->left));
        }
        else {
            if (current.node->right != NULL) s.push(StNode(current.node->right));
        }
    }
    //for (i=0; i<Size; ++i) cout << place_in_order[i] << ' ';
    //cout << endl;
    for (i=0; i<Size; ++i) cout << post[i] << ' ';
}
void BinaryTree::createTree()
{
    int n;
    cin >> n;
    SetSize(n);
    int Lchild[n], Rchild[n], start;
    int i, x, y, z;
    cin >> x >> y >> z;
    start = x; Lchild[x-1] = y; Rchild[x-1] = z;
    for (i=1; i<n; ++i) {
        cin >> x >> y >> z;
        Lchild[x-1] = y; Rchild[x-1] = z;
    }
    int ldata = Lchild[start-1], rdata = Rchild[start-1];
    linkQueue<Node *>que;
    Node *tmp;
    root = new Node(start, 1);
    que.enQueue(root);
    while (!que.isEmpty()) {
        tmp = que.deQueue();
        if (ldata != -1) {
            Node *pos;
            pos = new Node(ldata, 2 * tmp->place_inorder);
            que.enQueue(tmp->left = pos);
        }
        if (rdata != -1) {
            Node *pos;
            pos = new Node(rdata, 2 * tmp->place_inorder + 1);
            que.enQueue(tmp->right = pos);
        }
        if (!que.isEmpty()) {
            ldata = Lchild[que.getHead()->data-1];
            rdata = Rchild[que.getHead()->data-1];
        }
    }
}
