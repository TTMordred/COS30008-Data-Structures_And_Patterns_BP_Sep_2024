#include "ShakerSortableIntVector.h"

// Constructor, initializes using base class constructor
ShakerSortableIntVector::ShakerSortableIntVector(const int aArrayOfIntegers[], size_t aNumberOfElements) :
    SortableIntVector(aArrayOfIntegers, aNumberOfElements)
{}

// Shaker sort function, sorts elements using a comparison function
void ShakerSortableIntVector::sort(Comparable aOrderFunction)
{
    size_t lBeginIndex = 0;  // Start of the unsorted section
    size_t lEndIndex = size() - 1;  // End of the unsorted section

    // Continue sorting while there are unsorted elements
    while (lBeginIndex < lEndIndex)
    {
        // Forward pass to push the largest element to the end
        for (size_t i = lBeginIndex; i < lEndIndex; i++)
        {
            if (aOrderFunction(get(i), get(i + 1)))
            {
                swap(i, i + 1);  // Swap adjacent elements
            }
        }

        lEndIndex--;  // Reduce the unsorted section from the end

        // Backward pass to push the smallest element to the beginning
        for (size_t i = lEndIndex; i > lBeginIndex; i--)
        {
            if (aOrderFunction(get(i - 1), get(i)))
            {
                swap(i - 1, i);  // Swap adjacent elements
            }
        }

        lBeginIndex++;  // Reduce the unsorted section from the beginning
    }
}
