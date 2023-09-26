/*
 * MyADT.cpp
 * 
 * Class Description: A linear data collection ADT.
 * Class Invariant: Data collection with the following characteristics:
 *                   - Each element is unique (no duplicates).
 *                   - This is a value-oriented data collection: the elements are kept in 
 *                     ascending sort order of search key. 
 *                   - Its data structure is not expandable, i.e., resizable. 
 *
 * Author: AL, Isaac James
 * Last modified on: Sept. 2023
 */


#include <iostream>
#include <cctype>
#include "MyADT.h"  // Header file
#include "Profile.h"

using std::cout;
using std::endl;

using std::string;


    
// Default constructor.
MyADT::MyADT() {
   // Set element pointers to null and element counts to 0
   for (unsigned int i = 0; i < MAX_ALPHA; i++) {
      elements[i] = nullptr;
      elementCount[i] = 0; 
   }
}  // end default constructor


// Copy constructor
MyADT::MyADT(const MyADT& rhs) {
   // Call default constructor

   // Copy data
   for(unsigned int i = 0; i < MAX_ALPHA; i++) {
      // Create profile array
      // if profile array from source is empty, init to nullptr
      // and set element count to 0
      if(rhs.elementsArrIsEmpty(i)) {
         elements[i] = nullptr;
         elementCount[i] = 0;
      } // else init profile array and populate profiles
      else {
         elements[i] = new Profile[MAX_ELEMENTS];

         for(unsigned int j = 0; j < rhs.elementCount[i]; j++) {
            elements[i][j] = Profile(
               rhs.elements[i][j].getUserName(),
               rhs.elements[i][j].getName(),
               rhs.elements[i][j].getEmail(),
               rhs.elements[i][j].getBirthday()
            );
         }

         // Copy element count
         elementCount[i] = rhs.elementCount[i];
      }

      
   }

} // end copy constructor



// Destructor
// Description: Destruct this object, releasing heap-allocated memory.
MyADT::~MyADT() {
   // Delete all profile arrays and nullify element pointers
   removeAll();

} // end destructor

// Description: Checks if elements array (profile array) is full
// Precondition: index must be valid. 
// Should raise exception if not valid but we haven't covered that yet.. :)
// Poscondition Returns "true" if full
//              otherwise "false"
bool MyADT::elementsArrIsFull(int index) const{
   return elementCount[index] == MAX_ELEMENTS;
}

// Description: Checks if elements array (profile array) is empty
// Precondition: index must be valid
// Should raise exception if not valid but we haven't covered that yet.. :)
// Poscondition: Returns "true" if empty
//              otherwise "false"
bool MyADT::elementsArrIsEmpty(int index) const{
   return elementCount[index] == 0 && elements[index] == nullptr;
}

// Description: Searches for profile at a given element (profile) array with binary ssearch
// Precondition: index must be valid
// Poscondition: Returns the index of the profile if found
//               Otherwise -1
int MyADT::binarySearchOnProfiles(const Profile &target, int index) const {
   // fail on non valid index
   if(index < 0 || (unsigned int)index >= MAX_ALPHA) {
      return -1;
   }

   int l = 0;
   int r = elementCount[index] - 1;
   int mid;

   while (l <= r) {
      mid = l + (r - l) / 2;

      if(elements[index][mid] == target) {
         return mid;
      }
      else if(elements[index][mid] < target) {
         l = mid + 1;
      } // if target < profile at midpoint
      else {
         r = mid - 1;
      }
   }

   // Not found
   return -1;
}


// Description: Returns the total element count of elements currently stored in MyADT.
unsigned int MyADT::getElementCount() const {
   unsigned int sum = 0;
   for(unsigned int i = 0; i < MAX_ALPHA; i++) {
      sum += elementCount[i];
   }

   return sum;
}  // end getElementCount


// Description: Inserts an element.
// Precondition: newElement must not already be in data collection.  
// Postcondition: newElement inserted and the appropriate elementCount has been incremented.
//                Returns "true" when the insertion is successfull,
//                otherwise "false".
// Time Efficiency: O(m) where m = # profiles in an element array
bool MyADT::insert(const Profile& newElement) {
   // Get the index for which array the profile should be placed in
   int arrIndex = (int)newElement.getFirstLetter() - A_ASCII_CODE;
   
   // Check if the array where the insert should take place is full
   if(elementsArrIsFull(arrIndex)) {
      return false;
   }

   // Check if empty
   if(elementsArrIsEmpty(arrIndex)) {
      // Init new profile array

      elements[arrIndex] = new Profile[MAX_ELEMENTS];

      // Check for failure to allocate memory for new profile array
      if(elements[arrIndex] == nullptr) return false; 
   }


   for(unsigned int i = 0; i < elementCount[arrIndex]; i++) {
      // If new element userName is less than the userName found at i'th element,
      // shift elements i..in-1 over one to thleare right to make room and then insert
      // new element at i
      if(elements[arrIndex][i] > newElement) {
         for(unsigned int j = MAX_ELEMENTS-1; j > i; j--) {
            elements[arrIndex][j] = elements[arrIndex][j-1];
         }
         elements[arrIndex][i] = newElement;
         // Increment element count
         elementCount[arrIndex]++;

         return true;
      }
      // return false if duplicate
      else if(elements[arrIndex][i] == newElement) {
         return false;
      }
   }
   // Insert at end if not yet inserted
   elements[arrIndex][elementCount[arrIndex]] = newElement;
   elementCount[arrIndex]++;

   return true;

}  // end insert


// Description: Search for target element. 
//              Returns a pointer to the element if found,
//              otherwise, returns nullptr.
// Time Efficiency: O(logm) where m = # of profiles in an element array
Profile* MyADT::search(const Profile& target) {
   // Get the index for which element array the profile should be found in
   int arrIndex = (int)target.getFirstLetter() - A_ASCII_CODE;

   // Check if empty
   if(elementsArrIsEmpty(arrIndex)) {
      return nullptr;
   }

   // Binary search on element array
   int targetIndex = binarySearchOnProfiles(target, arrIndex);

   // Not found
   if(targetIndex == -1) {
      return nullptr;
   }

   // Found
   Profile* result = &elements[arrIndex][targetIndex];

   return result;

}  // end of search

// Description: Remove an element. 
// Postcondition: toBeRemoved is removed and the appropriate elementCount has been decremented.
//                Returns "true" when the removal is successfull,
//                otherwise "false".
// Time Efficiency: O(m) where m = # of profiles in an element array
bool MyADT::remove(const Profile& toBeRemoved) {
   // Get the index for which array the profile should be removed from
   int arrIndex = (int)toBeRemoved.getFirstLetter() - A_ASCII_CODE;
   
   // Check if the array where the remove should take place is empty
   if(elementsArrIsEmpty(arrIndex)) {
      return false;
   }

   // Binary Search to find index to remove
   int indexToRemove = binarySearchOnProfiles(toBeRemoved, arrIndex);
  
   // Return false if element was not found
   if(indexToRemove == -1) {
      return false;
   }

   // Shift elements left to remove profile
   for(unsigned int i = indexToRemove; i < elementCount[arrIndex] - 1; i++) {
      elements[arrIndex][i] = elements[arrIndex][i+1];
   }

   // Decrement element count
   elementCount[arrIndex]--;

   // delete array if empty now
   if(elementCount[arrIndex] == 0) {
      delete[] elements[arrIndex];
      elements[arrIndex] = nullptr;
   }

   return true;

}  // end remove


// Description: Remove all elements.
// Postcondition: each element pointer should be nullified and profiles arrays deleted.
// Element count for all indices should be set to zero.
// Time Efficiency: O(k) where k = total # of element pointers in the elements array 
void MyADT::removeAll() {
   // Loop through elements
   for(unsigned int i = 0; i < MAX_ALPHA; i++) {
      // Delete the element array effectively 
      // removing all profiles of that elements array
      delete[] elements[i];
      // Nullify pointer
      elements[i] = nullptr;
      // Set element count to zero
      elementCount[i] = 0;
   }


}  // end removeAll

// Description: Prints all profiles in alpha ascending order of usernames
// Time Efficiency: O(n) where n = total # of profiles
void MyADT::print() {
   for(unsigned int i = 0; i < MAX_ALPHA; i++) {
      for(unsigned int j = 0; j < elementCount[i]; j++) {
         cout << elements[i][j];
      }
   }

} // end of print 

//  End of implementation file
