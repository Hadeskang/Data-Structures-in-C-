#include <iostream>
#include <cstdlib>

#define MinTableSize (10)

using namespace std;


typedef int ElementType;
struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Tetrieve(Position P);

struct ListNode{
    ElementType Element;
    Position Next;
};

typedef Position List;

struct HashTbl{
    int TableSize;
    List *TheLists;
};

static int NextPrime(int N){
    int i;
    if(N % 2 == 0)
        ++N;
    for( ; ; N += 2){
        for(i = 3; i * i <= N; i += 2)
            if(N % i  == 0)
                goto ContOuter;
        return N;
        ContOuter: ;
    }
}

HashTable InitializeTable(int TableSize){
    HashTable H;
    int i;

    if(TableSize < MinTableSize){
        cout << "Table Size Too Small!" << endl;
        return nullptr;
    }

    H = (HashTbl *)malloc(sizeof(struct HashTbl));
    if(H == nullptr)
        cout << "Out of Space!!!" << endl;

    H->TableSize = NextPrime(TableSize);

    H->TheLists = (List *)malloc(sizeof(List) * H->TableSize);
    if(H->TheLists == nullptr)
        cout << "Out of Space!!!" << endl;

    for(int i = 0; i < H->TableSize; ++i){
        H->TheLists[i] = (Position)malloc(sizeof(struct ListNode));
        if(H->TheLists[i] == nullptr)
            cout << "Out of Space!!!" << endl;
        else
            H->TheLists[i]->Next = nullptr;
    }
}

Position Find(ElementType Key, HashTable H){
    Position P;
    List L;

    L = H->TheLists[Hash(Key, H->TableSize)];
    P = L->Next;
    while(P != nullptr && P->Element != Key)
        P = P->Next;

    return P;
}

void Insert(ElementType Key, HashTable H){
    Position Pos, NewCell;
    List L;

    Pos = Find(Key, H);
    if(Pos == nullptr){
        NewCell = (Position)malloc(sizeof(struct ListNode));
        if(NewCell == nullptr)
            cout << "Out of Space!!!" << endl;
        else{
            L = H->TheLists[Hash(Key, H->TableSize)];
            NewCell->Next = L->Next;
            NewCell->Element = Key;
            L->Next = NewCell;
        }
    }
}
