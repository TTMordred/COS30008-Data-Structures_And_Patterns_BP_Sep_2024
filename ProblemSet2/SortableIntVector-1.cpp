#include "SortableIntVector.h"

// Constructor: Initialize using base class IntVector
SortableIntVector::SortableIntVector(const int aArrayOfIntegers[], size_t aNumberOfElements) :
    IntVector(aArrayOfIntegers, aNumberOfElements)
{}

// Sort function using a comparison function to define the order
void SortableIntVector::sort(Comparable aOrderFunction)
{
    // Outer loop through all elements
    for (size_t i = 0; i < size(); i++)
    {
        // Inner loop to compare and swap elements
        for (size_t j = size() - 1; j > i; j--)
        {
            if (aOrderFunction(get(j), get(j - 1)))  // Compare elements
            {
                swap(j, j - 1);  // Swap elements if needed
            }
        }
    }
}
