#include <iostream>
#define MinPQSize (10)
#define MinData (-32676)
using namespace std;

struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;
typedef int ElementType;

PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void Insert(ElementType X, PriorityQueue H);
ElementType DeleteMin(PriorityQueue H);
ElementType FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);

struct HeapStruct{
    int Capacity;
    int Size;
    ElementType *Elements;
};

int IsEmpty(PriorityQueue H){
    return H->Capacity == 0;
}
int IsFull(PriorityQueue H){
    return H->Capacity == H->Size;
}

PriorityQueue Initialize(int MaxElements){
    PriorityQueue H;

    if(MaxElements <MinPQSize)
        cout << "Priority queue size is too small!" << endl;

    H = (HeapStruct *)malloc(sizeof(struct HeapStruct));
    if(H == nullptr)
        cout << "Out of Space !" << endl;
    H->Elements = (ElementType *)malloc(sizeof(ElementType) * (MaxElements + 1));

    if(H->Elements == nullptr)
        cout << "Out of Space!" << endl;

    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData;

    return H;
}

void Insert(ElementType X, PriorityQueue H){
    int i;

    if(IsFull(H)){
        cout << "Priority queue is full!" << endl;
        return ;
    }
    for(i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
        H->Elements[i] = H->Elements[i / 2];
    H->Elements[i] = X;
}

ElementType DeleteMin(PriorityQueue H){
    int i, Child;
    ElementType MinElement, LastElement;

    if(IsEmpty(H)){
        cout << "Priority queue is empty" << endl;
        return H->Elements[0];
    }
    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];
    for(int i = 1; i * 2 <= H->Size; i = Child){
        Child = i * 2;
        if(Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
            ++Child;
        if(LastElement > H->Elements[Child])
            H->Elements[i] = H->Elements[Child];
        else
            break;
    }
    H->Elements[i] = LastElement;
    return MinElement;
}
