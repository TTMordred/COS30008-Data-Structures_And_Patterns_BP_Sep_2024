
// COS30008, List, Problem Set 3, 2022

#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

#include <stdexcept>

template<typename T>
class List
{
private:
	// auxiliary definition to simplify node usage
	using Node = DoublyLinkedList<T>;

	Node* fRoot;	// the first element in the list
	size_t fCount;	// number of elements in the list

public:
	// auxiliary definition to simplify iterator usage
    using Iterator = DoublyLinkedListIterator<T>;

	~List()                                                             // destructor - frees all nodes
    {
        while ( fRoot != nullptr )
        {
            if ( fRoot != &fRoot->getPrevious() )                       // more than one element
            {
                Node* lTemp = const_cast<Node*>(&fRoot->getPrevious()); // select last
                
                lTemp->isolate();                                       // remove from list
                delete lTemp;                                           // free
            }
            else
            {
                delete fRoot;                                           // free last
                break;                                                  // stop loop
            }
        }
    }

    void remove( const T& aElement )	                                // remove first match from list
    {
        Node* lNode = fRoot;                                            // start at first
        
        while ( lNode != nullptr )                                      // Are there still nodes available?
        {
            if ( **lNode == aElement )                                  // Have we found the node?
            {
                break;                                                  // stop the search
            }

            if ( lNode != &fRoot->getPrevious() )                       // not reached last
            {
                lNode = const_cast<Node*>(&lNode->getNext());           // go to next
            }
            else
            {
                lNode = nullptr;                                        // stop search
            }
        }
        
        // At this point we have either reached the end or found the node.
        if ( lNode != nullptr )                                         // We have found the node.
        {
            if ( fCount != 1 )                                          // not the last element
            {
                if ( lNode == fRoot )
                {
                    fRoot = const_cast<Node*>(&fRoot->getNext());       // make next root
                }
            }
            else
            {
                fRoot = nullptr;                                        // list becomes empty
            }
            
            lNode->isolate();                                           // isolate node
            delete lNode;                                               // release node's memory
            fCount--;                                                   // decrement count
        }
    } // remove 1st match

	//////////////////////////////////////////////////////////////////
    //// PS3
    //////////////////////////////////////////////////////////////////
    
	// P1

    List() : fRoot(nullptr), fCount(0) {}
                                    // default constructor
    bool empty() const	                                                        // Is list empty?
    {
        return fRoot == nullptr;										       
    }            // Is list empty?

    size_t size() const {
        return fCount;
    }          		// list size

    // Thêm phần tử vào đầu danh sách
    void push_front(const T& aElement) {
        Node* newNode = new Node(aElement); 

        if (fRoot == nullptr) {
            fRoot = newNode;
        }
        else 
        {
            fRoot->push_front(*newNode); // trỏ về trước đó ( tạo nút ) 
            fRoot = newNode; // dời nút
        }
        ++fCount;
    }

    Iterator begin() const 
    {
        return Iterator(fRoot);
    }       // return a forward iterator
    Iterator end() const 
    {
        return begin().end();
    }            // return a forward end iterator
    Iterator rbegin() const 
    {
        return begin().rbegin();
    }                 // return a backwards iterator
    Iterator rend() const 
    {
        return begin().rend();
    }                    // return a backwards end iterator

	// P2
	
    void push_back(const T& aElement)                                         // adds aElement at back
    {
        Node* newNode = new Node(aElement);

        if (fRoot == nullptr)                                             
        {
            fRoot = newNode;
        }
        else
        {
            fRoot->push_front(*newNode);
        }

        fCount++;                                                               
    }      // adds aElement at back

	// P3

    const T& operator[](size_t aIndex) const {
        if (aIndex < fCount)                                                
        {
            const Node* lNode = fRoot;                                   
            while (aIndex)                                               
            {
                // No
                aIndex--;                                                   
                lNode = &lNode->getNext();                                  
            }
            // Yes
            return **lNode;                                                  
        }
        else
        {
            throw std::out_of_range("Index out of bounds.");                 
        }
    }	// list indexer

    // P4

    List(const List& aOtherList) :                                            // copy constructor
        fRoot(nullptr),                                                        
        fCount(0)                                                              
    {
        *this = aOtherList;                                               
    }

    List& operator=(const List& aOtherList)                                   // assignment operator
    {
        if (this != &aOtherList)                                            
        {
            // delete
            this->~List();                                                     

            fRoot = nullptr;                                                 
            fCount = 0;                                                      

            // copy
            for (const auto& e : aOtherList)
            {
                push_back(e);
            }                                                               
        }

        return *this;                                                    
    }
    
    // P5

    // move features

    List(List&& aOtherList) :                                                 // move constructor
        fRoot(nullptr),                                                    
        fCount(0)                                                             
    {
        *this = std::move(aOtherList);                                       
    }

    List& operator=(List&& aOtherList)                                        // move assignment operator
    {
        if (this != &aOtherList)                                           
        {
            // delete
            this->~List();                                                   

            // move (steal memory)
            fRoot = aOtherList.fRoot;                                       
            fCount = aOtherList.fCount;                                       
            aOtherList.fRoot = nullptr;                                         
            aOtherList.fCount = 0;                                              
        }

        return *this;                                                          
    }

    void push_front(T&& aElement)
    {
        Node* lNewElement = new Node(std::move(aElement));                    

        if (fRoot == nullptr)
        {
            fRoot = lNewElement;
        }
        else
        {
            fRoot->push_front(*lNewElement);
            fRoot = lNewElement;
        }

        fCount++;
    }

    void push_back(T&& aElement)
    {
        Node* lNewElement = new Node(std::move(aElement));                    

        if (fRoot == nullptr)
        {
            fRoot = lNewElement;
        }
        else
        {
            fRoot->push_front(*lNewElement);
        }

        fCount++;
    }
   
};


