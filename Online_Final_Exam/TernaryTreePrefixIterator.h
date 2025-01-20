#pragma once

// COS30008, Final Exam
// Nguyen Minh Duy - 104974743

#include "TernaryTree.h"

#include <stack>

template<typename T>
class TernaryTreePrefixIterator
{
private:
    using TTree = TernaryTree<T>;            // Alias for the ternary tree type
    using TTreeNode = TTree*;                // Alias for a pointer to a tree node
    using TTreeStack = std::stack<const TTree*>; // Alias for a stack of tree pointers

    const TTree* fTTree;                     // Pointer to the ternary tree being iterated
    TTreeStack fStack;                       // Stack used for managing the traversal

public:

    using Iterator = TernaryTreePrefixIterator<T>; // Alias for the iterator type

    // Postfix increment operator
    Iterator operator++(int)
    {
        Iterator old = *this;  // Save the current state
        ++(*this);             // Perform prefix increment
        return old;            // Return the state before increment
    }

    // Inequality comparison operator
    bool operator!=(const Iterator& aOtherIter) const
    {
        return !(*this == aOtherIter); // Use equality to determine inequality
    }

    /////////////////////////////////////////////////////////////////////////
    // // Problem 4: TernaryTree Prefix Iterator

private:

    // Pushes the subtrees (left, middle, right) of a given node onto the stack
    void push_subtrees(const TTree* aNode)
    {
        if (!aNode->getRight().empty()) // Check if the right subtree exists
        {
            fStack.push(&aNode->getRight()); // Push the right subtree
        }

        if (!aNode->getMiddle().empty()) // Check if the middle subtree exists
        {
            fStack.push(&aNode->getMiddle()); // Push the middle subtree
        }

        if (!aNode->getLeft().empty()) // Check if the left subtree exists
        {
            fStack.push(&aNode->getLeft()); // Push the left subtree
        }
    }

public:

    // iterator constructor
    TernaryTreePrefixIterator(const TTree* aTTree) :
        fTTree(aTTree) // Initialize the ternary tree pointer
    {
        if (!fTTree->empty()) // If the tree is not empty
        {
            fStack.push(fTTree); // Push the root of the tree onto the stack
        }
    }

    // iterator dereference
    const T& operator*() const
    {
        return **fStack.top(); // Return the value of the node on top of the stack
    }

    // prefix increment
    Iterator& operator++()
    {
        const TTree* lTop = fStack.top(); // Get the current node (top of the stack)
        fStack.pop();                    // Remove the current node from the stack
        push_subtrees(lTop);             // Push its subtrees onto the stack
        return *this;                    // Return the updated iterator
    }

    // iterator equivalence
    bool operator==(const Iterator& aOtherIter) const
    {
        return
            fTTree == aOtherIter.fTTree &&           // Check if they are iterating the same tree
            fStack.size() == aOtherIter.fStack.size(); // Check if their stacks have the same size
    }

    // auxiliaries
    Iterator begin() const
    {
        return TernaryTreePrefixIterator(fTTree); // Create a new iterator starting at the root
    }

    // Returns an iterator representing the end of the traversal
    Iterator end() const
    {
        Iterator Result = *this;       // Copy the current iterator
        Result.fStack = TTreeStack(); // Clear the stack to represent the end
        return Result;                // Return the end iterator
    }
};
