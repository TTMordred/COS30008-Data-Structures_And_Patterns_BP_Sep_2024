
// COS30008, Problem Set 4, Problem 1, 2022

#pragma once

#include <stdexcept>
#include <algorithm>

template<typename T>
struct BinaryTreeNode
{
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    
    T key;
    BTreeNode left;
    BTreeNode right;
    
    static BNode NIL;
    
    const T& findMax() const
    {
        if ( empty() )
        {
            throw std::domain_error( "Empty tree encountered." );
        }
        
        return right->empty() ? key : right->findMax();
    }

    const T& findMin() const
    {
        if ( empty() )
        {
            throw std::domain_error( "Empty tree encountered." );
        }
        
        return left->empty() ? key : left->findMin();
    }

    bool remove( const T& aKey, BTreeNode aParent )
    {
        BTreeNode x = this;
        BTreeNode y = aParent;

        while ( !x->empty() )
        {
            if ( aKey == x->key )
            {
                break;
            }

            y = x;                                      // new parent
            
            x = aKey < x->key ? x->left : x->right;
        }

        if ( x->empty() )
        {
            return false;                               // delete failed
        }
        
        if ( !x->left->empty() )
        {
            const T& lKey = x->left->findMax();         // find max to left
            x->key = lKey;
            x->left->remove( lKey, x );
        }
        else
        {
            if ( !x->right->empty() )
            {
                const T& lKey = x->right->findMin();    // find min to right
                x->key = lKey;
                x->right->remove( lKey, x );
            }
            else
            {
                if ( y != &NIL )                        // y can be NIL
                {
                    if ( y->left == x )
                    {
                        y->left = &NIL;
                    }
                    else
                    {
                        y->right = &NIL;
                    }
                }
                
                delete x;                               // free deleted node
            }
        }

        return true;
    }

    // PS4 starts here
    
    BinaryTreeNode() : // Default constructor
        key(T()),
        left(&NIL),
        right(&NIL)
    {}

    BinaryTreeNode(const T& aKey) :  // Copy constructor
        key(aKey),                                        
        left(&NIL),                                           
        right(&NIL)
    {}

    BinaryTreeNode(T&& aKey) :// Move constructor   
        key(std::move(aKey)),                                
        left(&NIL),                                              
        right(&NIL)
    {}

    ~BinaryTreeNode() // Destructor
    {
        if (!left->empty())                                     
        {
            delete left;                                           
        }

        if (!right->empty())                                    
        {
            delete right;                                         
        }
    }
    
    bool empty() const  // Check if node is empty
    {
        return this == &NIL;
    }

    bool leaf() const // Check if the elements is leaf or not 
    {
        return left->empty() && right->empty();
    }

    size_t height() const 
    {
        if (empty())
        {
            throw std::domain_error("Tree is empty. No height can be calculated.");
        }

        if (leaf())                                             
        {
            return 0;                                              
        }
        else
        {
            size_t leftHeight = 0;
            size_t rightHeight = 0;

            if (!left->empty())                               
            {
                leftHeight = left->height();    // đổi gốc 
            }

            if (!right->empty())                                 
            {
                rightHeight = right->height();   // đổi gốc 
            }

            return max(leftHeight, rightHeight) + 1;
        }
    }

    bool insert(const T& aKey) 
    {
        BTreeNode x = this;
        BTreeNode y = &NIL;

        while (!x->empty())
        {
            y = x;

            if (aKey == x->key)
            {
                return false;         // duplicate key - error
            }

            x = aKey < x->key ? x->left : x->right;
        }

        BTreeNode z = new BNode(aKey);

        if (y->empty())
        {
            return false;           // insert failed (NIL) - emptyy
        }
        else
        {
            if (aKey < y->key)
            {
                y->left = z;
            }
            else
            {
                y->right = z;
            }
        }

        return true;                 // insert done
    }
};

template<typename T>
BinaryTreeNode<T> BinaryTreeNode<T>::NIL;
