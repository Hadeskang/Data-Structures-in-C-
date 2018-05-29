#include <iostream>
#define MinTableSize (11)

using namespace std;

typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;
typedef int ElementType;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P, HashTable H);
HashTable Rehash(HashTable H);

enum KindofEntry{Legitimate, Empty, Deleted};

struct HashEntry{
    ElementType Element;
    enum KindofEntry Info;
};

typedef struct HashEntry Cell;

struct HashTbl{
    int TableSize;
    Cell *TheCells;
};

Index Hash(ElementType Key, int TableSize){
    return Key % TableSize;
}

HashTable InitializeTable(int TableSize){
    HashTable H;
    int i;

    if(TableSize < MinTableSize){
        cout << "Table Size too Small!" << endl;
        return nullptr;
    }

    H = (HashTbl *)malloc(sizeof(struct HashTbl));
    if(H == nullptr)
        cout << "Out of Space !!!" << endl;

    H->TheCells = (Cell *)malloc(sizeof(Cell) * H->TableSize);
    if(H->TheCells == nullptr)
        cout << "Out of Space!!!" << endl;

    for(int i = 0; i < TableSize; ++i)
        H->TheCells[i].Info = Empty;

    return H;
}

Position Find(ElementType Key, HashTable H){
    Position CurrentPos;
    int CollisionNum;

    CollisionNum = 0;
    CurrentPos = Hash(Key, H->TableSize);
    while(H->TheCells[CurrentPos].Info != Empty && H->TheCells[CurrentPos].Element != Key){
        CurrentPos += 2 * ++CollisionNum - 1;
        if(CurrentPos >= H->TableSize)
            CurrentPos -= H->TableSize;
    }

    return CurrentPos;
}

void Insert(ElementType Key, HashTable H){
    Position Pos;

    Pos = Find(Key, H);
    if(H->TheCells[Pos].Info != Legitimate){
        H->TheCells[Pos].Info = Legitimate;
        H->TheCells[Pos].Element = Key;
    }
}
