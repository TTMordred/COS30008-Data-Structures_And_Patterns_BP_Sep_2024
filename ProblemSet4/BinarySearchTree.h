
// COS30008, Problem Set 4, Problem 2, 2022

#pragma once

#include "BinaryTreeNode.h"

#include <stdexcept>

// Problem 3 requirement
template<typename T>
class BinarySearchTreeIterator;

template<typename T>
class BinarySearchTree
{
private:

    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
  
    BTreeNode fRoot;
    
public:

    BinarySearchTree()
    {
        fRoot = &BNode::NIL;                                 
    }

    ~BinarySearchTree()
    {
        if ( !empty() )                                         
        {
            delete fRoot;                                      
        }
    }

    bool empty() const
    {
        return fRoot == &BNode::NIL;
    }
    
    size_t height() const
    {
        // The empty tree has no height.
        if ( empty() )
        {
            throw std::domain_error( "Empty tree has no height." );
        }
        
        return fRoot->height();                                
    }
    
    bool insert( const T& aKey )
    {
        if ( empty() )                                          
        {
            fRoot = new BNode( aKey );                          

            return true;                                        
        }
        else
        {
            return fRoot->insert( aKey );                       
        }
    }

    bool remove( const T& aKey )
    {
        if ( empty() )
        {
            throw std::domain_error( "remove(): NIL encountered." );
        }
        
        if ( fRoot->leaf() )
        {
            // last node
            if ( fRoot->key == aKey )
            {
                delete fRoot;
                fRoot = &BNode::NIL;
                
                return true;
            }
            
            return false;
        }
        else
        {
            return fRoot->remove( aKey, &BNode::NIL );          
        }
    }                                                           

    // Problem 3 methods
    
    using Iterator = BinarySearchTreeIterator<T>;

    // Allow iterator to access private member variables
    friend class BinarySearchTreeIterator<T>;
    
    Iterator begin() const
    {
        return Iterator( *this );                               
    }
    
    Iterator end() const
    {
        return begin().end();                                   
    }
};                                                              
