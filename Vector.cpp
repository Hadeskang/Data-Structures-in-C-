/**数据结构与算法分析_C++描述版本课本源码
  *实现vector
  *定义类名为Vector和类模版vector区分
  */
#include <algorithm>

template<typename Object>
class Vector{
public:
    explicit Vector( int initSize = 0 ) : theSize{ initSize },
        theCapacity{ initSize + SPARE_CAPACITY }{
            objects = new Object[ theCapacity ];
        }

    Vector(const Vector &rhs) : theSize{ rhs.theSize },
        theCapacity { rhs.theCapacity },
        objects{ nullptr }
        {
            objects = new Object[ theCapacity ];
            for(int i = 0; i < theSize; ++i)
                objects[ i ] = rhs.objects[ i ];
        }

    Vector & operator= ( const Vector &rhs ){
        Vector copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    ~Vector( ){
        delete [ ] objects;
    }

    Vector( Vector &&rhs ) : theSize{ rhs.theSize },
        theCapacity{ rhs.theCapacity },
        objects{ rhs.objects }{
            rhs.objects = nullptr;
            rhs.theSize = 0;
            rhs.theCapacity = 0;
        }

    Vector & operator= ( Vector && rhs ){
        std::swap( theSize, rhs.theSize );
        std::swap( theCapacity, rhs.theCapacity );
        std::swap( objects, rhs.objects );

        return *this;
    }

    void resize( int newSize ){
        if( newSize > theCapacity )
            reverse( newSize * 2 );
        theSize = newSize;
    }

    void reverse( int newCapacity ){
        if( newCapacity < theSize )
            return ;

        Object *newArray = new Object[ newCapacity ];
        for(int i = 0; i < theSize; ++i)
            newArray[ i ] = std::move( objects[ i ] );

        theCapacity = newCapacity;
        std::swap( objects, newArray );
        delete [ ] newArray;
    }

    Object & operator[ ] ( int index ){
        return objects[ index ];
    }

    const Object & operator[ ] ( int index ) const {
        return objects[ index ];
    }

    bool empty( ) const {
        return theSize == 0;
    }

    int size( ) const {
        return theSize;
    }

    int capacity( ) const {
        return theCapacity;
    }

    void push_back( const Object & x){
        if( theSize == theCapacity)
            reverse( 2 * theCapacity + 1);
        objects[ theSize++ ] = x;
    }

    void push_back( Object && x ){
        if( theSize == theCapacity )
            reverse( 2 * theCapacity + 1 );
        objects[ theSize++ ] = std::move( x );
    }

    void pop_back( ) {
        --theSize;
    }

    const Object & back( ) const {
        return objects[ theSize - 1 ];
    }

    using iterator = Object *;
    using const_iterator = const Object *;

    iterator begin( ) {
        return &objects[ 0 ];
    }

    iterator end( ) {
        return &objects[ size( ) ];
    }

    const_iterator begin( ) const {
        return &objects[ 0 ];
    }

    const_iterator end( ) const {
        return &objects[ size( ) ];
    }

    static const int SPARE_CAPACITY = 16;
private:
    int theSize;
    int theCapacity;
    Object *objects;
}  ;
