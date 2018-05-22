/**数据结构与算法分析_C++描述版本课本源码
  *实现BinarySearchTree
  */

  #include <iostream>
template <typename Comparable>
class BinarySearchTree{
public:
    BinarySearchTree( );
    BinarySearchTree( const BinarySearchTree &rhs ) : root{ nullptr } {
        root = clone( rhs.root );
    }

    BinarySearchTree( BinarySearchTree &&rhs );
    ~BinarySearchTree( ) {
        makeEmpty( );
    }

    const Comparable & findMin( ) const{
        return findMin( )->element;
    }

    const Comparable & findMax( ) const{
        return findMax( )->element;
    }

    bool contains( const Comparable &x ) const{
        return contains( x, root );
    }

    bool isEmpty( ) const{
        return root == nullptr;
    }
    void printTree( std::ostream &out = std::cout ) const;

    void makeEmpty( ){
        makeEmpty( root );
    }

    void insert( const Comparable &x );
    void insert( Comparable &&x );
    void remove( const Comparable &x );

    BinarySearchTree &operator= ( const BinarySearchTree &rhs );
    BinarySearchTree &operator= ( BinarySearchTree &&rhs );

private:
    struct BinaryNode{
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const Comparable &theElement, BinaryNode *lt, BinaryNode *rt) :
            element{ theElement }, left{ lt }, right{ rt } { }

        BinaryNode( Comparable &&theElement, BinaryNode *lt, BinaryNode *rt):
            element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root;

    void insert( const Comparable &x, BinaryNode *&t ){
        if( t == nullptr )
            t = new BinaryNode( x, nullptr, nullptr );
        else if( t->element > x )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;
    }

    void insert( Comparable &&x, BinaryNode *&t ){
        if( t == nullptr )
            t = new BinaryNode( std::move( x ), nullptr, nullptr );
        else if( t->element > x )
            insert( std::move( x ), t->left );
        else if( t->element < x)
            insert( std::move( x ), t->right );
        else
            ;
    }

    void remove( const Comparable &x, BinaryNode *&t ){
        if( t == nullptr )
            return ;
        if( x < t->element)
            remove( x, t->left );
        else if( x > t->element )
            remove( x, t->right );
        else{
            if( t->left != nullptr && t->right != nullptr){
                t->element = findMin( t->right )->element;
                remove( t->element, t->right );
            }
            else{
                BinaryNode *oldNode = t;
                t = ( t->left != nullptr ) ? t->left : t->rigth;
                delete oldNode;
            }
        }
    }

    BinaryNode *findMin( BinaryNode *t ) const{
        if( t == nullptr )
            return nullptr;
        else if( t->left )
            findMin( t->left );
        else
            return t;
    }

    BinaryNode *findMax( BinaryNode *t ) const{
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }

    bool contains( const Comparable &x, BinaryNode *t ) const{
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( x > t->element )
            return contains( x, t->right );
        else
            return true;
    }

    void makeEmpty( BinaryNode *&t ){
        if( t != nullptr ){
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
    }
    void printTree( BinaryNode *t, std::ostream &out ) const;
    BinaryNode *clone( BinaryNode *t ) const{
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->root, clone( t->left ), clone( t->right ) };
    }
};
