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
typedef unsigned int Index;

struct HashTbl{
    int TableSize;
    List *TheLists;
};

Index Hash(int Key, int TableSize){
    return Key % TableSize;
}

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

    H = (struct HashTbl *)malloc(sizeof(struct HashTbl));
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

/*void Insert(ElementType Key, HashTable H){
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
}*/

        void
        Insert( ElementType Key, HashTable H )
        {
            Position Pos, NewCell;
            List L;

/* 1*/      Pos = Find( Key, H );
/* 2*/      if( Pos == NULL )   /* Key is not found */
            {
/* 3*/          NewCell = (ListNode *)malloc( sizeof( struct ListNode ) );
/* 4*/          if( NewCell == NULL )
/* 5*/              cout <<  "Out of space!!!" << endl;
                else
                {
/* 6*/              L = H->TheLists[ Hash( Key, H->TableSize ) ];
/* 7*/              NewCell->Next = L->Next;
/* 8*/              NewCell->Element = Key;  /* Probably need strcpy! */
/* 9*/              L->Next = NewCell;
                }
            }
        }

ElementType Retrieve(Position P){
    return P->Element;
}

void DestroyTable(HashTable H){
    int i;

    for(i = 0; i < H->TableSize; ++i){
        Position P = H->TheLists[i];
        Position Tmp;

        while(P != nullptr){
            Tmp = P->Next;
            free(P);
            P = Tmp;
        }
    }

    free(H->TheLists);
    free(H);
}
#define NumItems 400

int main( )
{
    HashTable H;
    Position P;
    int i;
    int j = 0;
    int CurrentSize;

    H = InitializeTable( CurrentSize = 13 );

    for( i = 0; i < NumItems; i++, j += 71 )
    {
    #ifdef QuadProb
        if( i > CurrentSize / 2 )
        {
            H = Rehash( H );
            printf( "Rehashing...\n" );
            CurrentSize *= 2;
        }
    #endif
        Insert( j, H );
    }

    /*for( i = 0, j = 0; i < NumItems; i++, j += 71 )
    #ifdef SepChain
        if( ( P = Find( j, H ) ) == NULL || Retrieve( P ) != j )
    #endif
    #ifdef QuadProb
        if( Retrieve( ( P = Find( j, H ) ), H ) != j )
    #endif
            printf( "Error at %d\n", j );

    printf( "End of program.\n" );*/
    return 0;
}
