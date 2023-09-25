/*
 * MyADT.h
 * 
 * Class Description: A linear data collection ADT.
 * Class Invariant: Data collection with the following characteristics:
 *                   - Each element is unique (no duplicates).
 *                   - This is a value-oriented data collection: the elements are kept in 
 *                     ascending sort order of search key. 
 *                   - Its data structure is not expandable, i.e., resizable. 
 *
 * Author: AL
 * Last modified on: Sept. 2023
 */
 
 
#ifndef MyADT_H
#define MyADT_H

/*
 * You can add more #include statements.
 */
 
#include <string>
#include "Profile.h"

using std::string;


class MyADT {

private:

/* 
 * You can add more attributes to this class, 
 * but you cannot remove/change the attributes below.
 */
    constexpr static int A_ASCII_CODE = (int)'A';
    constexpr static unsigned int MAX_ALPHA = 26;   // 26 letters in the alphabet 
    constexpr static unsigned int MAX_ELEMENTS = 5; // Small capacity so can test when data collection becomes full 
                                                    // Feel free to change this MAX_ELEMENTS value.
    Profile * elements[MAX_ALPHA];                  // MAX_ALPHA arrays of elements 
    unsigned int elementCount[MAX_ALPHA];           // Current element count in each of the MAX_ALPHA arrays of elements
/* 
 * You can add private methods to this class.
 */

    // Description: Returns a boolean stating whether or not an elements array at a given index is full
    //              returns "true" if full
    //              otherwise "false"
    // Precondition: index must be valid
    bool elementsArrIsFull(int index) const;

    // Description: Returns a boolean stating whether or not an elements array at a given index is empty
    //              returns "true" if empty
    //              otherwise "false"
    // Precondition: index must be valid
    bool elementsArrIsEmpty(int index) const;

    // Description: Performs binary search on profile array at a given index.
    //              Returns the index of the profile if found
    //              Otherwise -1
    // Precondition: index must be valid
    int binarySearchOnProfiles(const Profile &target, int index) const;


public:
/* 
 * You cannot remove/change the public methods below.
 * Bottom line: you cannot change the ***public interface*** of this class. 
 */
    // Default constructor
    MyADT();

    // Copy constructor - Covered in Lab 3
    MyADT(const MyADT& rhs);

    // Should overload the = operator.
    // Overloaded Operators - More on this topic in Lab 4.
    // operator=(const MyADT& rhs);
    
    // Destructor
    // Description: Destruct this object, releasing heap-allocated memory.
    ~MyADT();

    // Description: Returns the total element count currently stored in MyADT object.
    unsigned int getElementCount() const;

    // Description: Inserts an element.
    // Precondition: newElement must not already be in data collection.  
    // Postcondition: newElement inserted and the appropriate elementCount has been incremented.
    //                Returns "true" when the insertion is successfull,
    //                otherwise "false".
    bool insert(const Profile& newElement);

    // Description: Remove an element. 
    // Postcondition: toBeRemoved (if found) is removed and the appropriate elementCount is decremented.
    //                Returns "true" when the removal is successfull,
    //                otherwise "false".  
    // Time Efficiency: O(m) where m = # of profiles in an element array
    bool remove(const Profile& toBeRemoved);
    
    // Description: Remove all elements.
    // Postcondition: each element in the elements array should point to a default
    // array of profiles. Element count for all indices should be set to zero.
    // Time Efficiency: O(k) where k = total # of elements in the elements array 
    void removeAll();
   
    // Description: Search for target element.
    //              Returns a pointer to the element if found,
    //              otherwise, returns nullptr.
    // Time Efficiency: O(logm) where m = # of profiles in an element array
    Profile* search(const Profile& target);
    
    // Description: Prints all profiles in alpha ascending order of usernames
    // Time Efficiency: O(n) where n = total # of profiles
    void print();
   

}; // end MyADT
#endif
