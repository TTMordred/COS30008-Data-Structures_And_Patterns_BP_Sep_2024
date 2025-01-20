#include "IntVector.h"
#include <stdexcept>  // Handle exceptions

using namespace std;

// Constructor: Initialize with an array of integers and its size
IntVector::IntVector(const int aArrayOfIntegers[], size_t aNumberOfElements)
{
    fNumberOfElements = aNumberOfElements;  // Set size
    fElements = new int[fNumberOfElements];  // Allocate memory

    // Copy elements to the internal array
    for (size_t i = 0; i < fNumberOfElements; i++)
    {
        fElements[i] = aArrayOfIntegers[i];
    }
}

// Destructor: Release allocated memory
IntVector::~IntVector()
{
    delete[] fElements;  // Free memory
}

// Return the size of the vector
size_t IntVector::size() const
{
    return fNumberOfElements;  // Return size
}

// Get the element at a specific index
const int IntVector::get(size_t aIndex) const
{
    return (*this)[aIndex];  // Return element at index
}

// Swap two elements by their indices
void IntVector::swap(size_t aSourceIndex, size_t aTargetIndex)
{
    // Ensure indices are within bounds
    if (aSourceIndex < fNumberOfElements && aTargetIndex < fNumberOfElements)
    {
        int lTemp = fElements[aSourceIndex];  // Temp store
        fElements[aSourceIndex] = fElements[aTargetIndex];  // Swap
        fElements[aTargetIndex] = lTemp;  // Complete swap
    }
    else
    {
        throw out_of_range("Illegal vector indices");  // Handle out-of-bounds access
    }
}

// Overload [] to access elements at a given index
const int IntVector::operator[](size_t aIndex) const
{
    if (aIndex < fNumberOfElements)
    {
        return fElements[aIndex];  // Return element
    }

    throw out_of_range("Illegal vector index");  // Handle invalid index
}
