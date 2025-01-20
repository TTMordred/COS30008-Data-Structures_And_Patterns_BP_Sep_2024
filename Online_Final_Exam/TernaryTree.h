// COS30008, Final Exam
// Nguyen Minh Duy - 104974743
// Implementation of a generic TernaryTree class supporting prefix iteration, copy, and move semantics.

#pragma once

#include <stdexcept>
#include <algorithm>

template<typename T>
class TernaryTreePrefixIterator;

template<typename T>
class TernaryTree
{
public:

    using TTree = TernaryTree<T>; 
    using TSubTree = TTree*;      

private:

    T fKey;                       
    TSubTree fSubTrees[3];        

    // private default constructor used for declaration of NIL
    TernaryTree() :
        fKey(T())                 
    {
        for (size_t i = 0; i < 3; i++)
        {
            fSubTrees[i] = &NIL;  
        }
    }

public:

    using Iterator = TernaryTreePrefixIterator<T>; 

    static TTree NIL;           

    // Getters for subtrees
    const TTree& getLeft() const { return *fSubTrees[0]; }
    const TTree& getMiddle() const { return *fSubTrees[1]; }
    const TTree& getRight() const { return *fSubTrees[2]; }

    // Add a subtree to the left, middle, or right position
    void addLeft(const TTree& aTTree) { addSubTree(0, aTTree); }
    void addMiddle(const TTree& aTTree) { addSubTree(1, aTTree); }
    void addRight(const TTree& aTTree) { addSubTree(2, aTTree); }

    // Remove a subtree from the left, middle, or right position
    const TTree& removeLeft() { return removeSubTree(0); }
    const TTree& removeMiddle() { return removeSubTree(1); }
    const TTree& removeRight() { return removeSubTree(2); }

    /////////////////////////////////////////////////////////////////////////
    // Private helper functions for managing subtrees
    // Problem 1: TernaryTree Basic Infrastructure

private:
    // remove a subtree, may throw a domain error [22]
    // Remove a subtree; checks for valid index and throws errors if conditions are violated
    const TTree& removeSubTree(size_t aSubtreeIndex)
    {
        if (aSubtreeIndex >= 3) // Check for valid subtree index
        {
            throw std::out_of_range("Illegal subtree index");
        }

        if (fSubTrees[aSubtreeIndex]->empty()) // Check if the subtree is NIL
        {
            throw std::domain_error("Subtree is NIL");
        }

        const TTree& Outcome = *fSubTrees[aSubtreeIndex]; // Save subtree for return
        fSubTrees[aSubtreeIndex] = &NIL;                // Set the subtree to NIL

        return Outcome;                                  // Return the removed subtree
    }

    // add a subtree; must avoid memory leaks; may throw domain error [18]
    // Add a subtree; ensures no memory leaks and validates subtree conditions
    void addSubTree(size_t aSubtreeIndex, const TTree& aTTree)
    {
        if (aSubtreeIndex >= 3) // Check for valid subtree index
        {
            throw std::out_of_range("Illegal subtree index");
        }

        if (!fSubTrees[aSubtreeIndex]->empty()) // Ensure the position is currently NIL
        {
            throw std::domain_error("Subtree is not NIL");
        }

        fSubTrees[aSubtreeIndex] = const_cast<TSubTree>(&aTTree); // Add the subtree
    }

    /////////////////////////////////////////////////////////////////////////
    // Public constructors, destructor, and utility methods

public:
    // TernaryTree l-value constructor [10]
    // Constructor for l-value keys
    TernaryTree(const T& aKey) :
        fKey(aKey) // Initialize the key
    {
        for (size_t i = 0; i < 3; i++)
        {
            fSubTrees[i] = &NIL; // Initialize subtrees to NIL
        }
    }

    // destructor (free sub-trees, must not free empty trees) [14]
    // Destructor: Frees all non-NIL subtrees
    ~TernaryTree()
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (!fSubTrees[i]->empty()) // Only delete non-empty subtrees
            {
                delete fSubTrees[i];
            }
        }
    }

    // return key value, may throw domain_error if empty [2]
    // Access the key value; throws error if the tree is empty
    const T& operator*() const
    {
        if (empty())
        {
            throw std::domain_error("NIL payload access");
        }
        return fKey;
    }

    // returns true if this ternary tree is empty [4]
    // Check if the tree is empty
    bool empty() const
    {
        return this == &NIL;
    }

    // returns true if this ternary tree is a leaf [10]
    // Check if the tree is a leaf (all subtrees are NIL)
    bool leaf() const
    {
        return fSubTrees[0] == &NIL &&
            fSubTrees[1] == &NIL &&
            fSubTrees[2] == &NIL;
    }

    // return height of ternary tree, may throw domain_error if empty [48]
    // Compute the height of the tree; throws error if the tree is empty
    size_t height() const
    {
        if (empty())                                                 
        {
            throw std::domain_error("Operation not supported");       
        }

        // leaf
        if (leaf())                                                   
        {
            return 0;                                                   
        }

        // need variables
        size_t lLeft = 0;                                               
        size_t lMiddle = 0;                                             
        size_t lRight = 0;                                              

        // left
        if (!fSubTrees[0]->empty())                                   
        {
            lLeft = fSubTrees[0]->height();                             
        }

        // middle
        if (!fSubTrees[1]->empty())                                   
        {
            lMiddle = fSubTrees[1]->height();                           
        }

        // right
        if (!fSubTrees[2]->empty())                                   
        {
            lRight = fSubTrees[2]->height();                            
        }

        return std::max(lLeft, std::max(lMiddle, lRight)) + 1;      
    }

    /////////////////////////////////////////////////////////////////////////
    // Problem 2: TernaryTree Copy Semantics
    // Copy and move semantics

    // copy constructor, must not copy empty ternary tree
        // Copy constructor: Avoids copying NIL trees
    TernaryTree(const TTree& aOtherTTree) :
        TernaryTree()
    {
        *this = aOtherTTree; // Delegate to copy assignment
    }

    // copy assignment operator, must not copy empty ternary tree
    // may throw a domain error on attempts to copy NIL
    // Copy assignment: Ensures proper handling of NIL and non-NIL trees
    TTree& operator=(const TTree& aOtherTTree)
    {
        if (aOtherTTree.empty())                                      
        {
            throw std::domain_error("NIL as source not permitted.");  
        }

        if (this != &aOtherTTree)                                     
        {
            // free this
            this->~TernaryTree();                                      

            fKey = aOtherTTree.fKey;                                    

            // just use clone
            fSubTrees[0] = aOtherTTree.getLeft().clone();               
            fSubTrees[1] = aOtherTTree.getMiddle().clone();             
            fSubTrees[2] = aOtherTTree.getRight().clone();              
        }

        return *this;                                                   
    }

    // clone ternary tree, must not copy empty trees
    // Clone method: Creates a new tree copy or returns the current object if NIL
    TSubTree clone() const
    {
        if (empty())                                                  
        {
            // const cast required (remove const)
            return const_cast<TSubTree>(this);                          
        }
        else
        {
            return new TTree(*this);                                  
        }
    }

    /////////////////////////////////////////////////////////////////////////
    // Problem 3: TernaryTree Move Semantics
    // Move constructor

    // TTree r-value constructor
    TernaryTree(T&& aKey) :
        fKey(std::move(aKey))
    {
        for (size_t i = 0; i < 3; i++)
        {
            fSubTrees[i] = &NIL;
        }
    }

    // move constructor, must not copy empty ternary tree
    TernaryTree(TTree&& aOtherTTree) :
        /* just use default private default constructor */
        TernaryTree()                                                    
    {
        // use assignent operator
        *this = std::move(aOtherTTree);                                 
    }


    // move assignment operator, must not copy empty ternary tree
    // Move assignment
    TTree& operator=(TTree&& aOtherTTree)
    {
        if (aOtherTTree.empty())                                      
        {
            throw std::domain_error("NIL as source not permitted.");  
        }

        if (this != &aOtherTTree)                                     
        {
            // free this
            this->~TernaryTree();                                      

            // swap preparation
            fKey = T();                                                 

            for (size_t i = 0; i < 3; i++)
            {
                fSubTrees[i] = &NIL;                                   
            }

            std::swap(fKey, aOtherTTree.fKey);                        
            std::swap(fSubTrees[0], aOtherTTree.fSubTrees[0]);        
            std::swap(fSubTrees[1], aOtherTTree.fSubTrees[1]);        
            std::swap(fSubTrees[2], aOtherTTree.fSubTrees[2]);        
        }

        return *this;                                                   
    }

    /////////////////////////////////////////////////////////////////////////
    // Iteration support

        // Prefix iterator positioned at the start of the tree
    Iterator begin() const
    {
        return Iterator(this);
    }

    // Prefix iterator positioned at the end of the tree
    Iterator end() const
    {
        return begin().end();
    }
};

// Definition of the NIL sentinel
template<typename T>
TernaryTree<T> TernaryTree<T>::NIL;
