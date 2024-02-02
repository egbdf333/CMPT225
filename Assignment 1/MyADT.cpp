/*
 * MyADT.cpp
 * 
 * Class Description: A linear data collection ADT.
 * 
 * Class Invariant: Data collection with the following characteristics:
 *                  - This is a value-oriented data collection and 
 *                    the elements are kept in ascending sort order of search key.
 *                  - Each element is unique (no duplicates). 
 *                  - Its data structure (CDT) is not expandable. This signifies that 
 *                    when this data collection becomes full, you do not have to resize 
 *                    its data structure (not in this Assignment 1). 
 *
 * Author: AL and <put your name here>
 * Last modified on: Jan. 2024
 */


#include <iostream>
#include <cctype>
#include "MyADT.h"     // Header file of MyADT file
#include "Profile.h"   // Header file of Profile class

using std::cout;
using std::endl;

    
// Default constructor.
MyADT::MyADT() {
   // cout << "MyADT::default constructor executed!" << endl;   // For testing purposes ...
   // You can also use the above to figure out when this constructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
 
   for (unsigned int i = 0; i < MAX_ALPHA; i++) {
      elements[i] = nullptr;
      elementCount[i] = 0;
   }

   // for (i - 26) {
   //    malloc Profile array size 1
   //    assign pointer to Profile array
   //    store pointer into elements[i]
   // }
}  

// Copy constructor - Covered in Lab 3
MyADT::MyADT(const MyADT& rhs) {
   // cout << "MyADT::copy constructor executed!" << endl; // For testing purposes ... 
   // You can also use the above to figure out when this constructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.

   unsigned int i;
   unsigned int j;

  for (i = 0; i < MAX_ALPHA; i++) {
   elementCount[i] = rhs.elementCount[i];
   if (rhs.elements[i] != nullptr) {
      
      elements[i] = new Profile[elementCount[i]];

      for (j = 0; j < elementCount[i]; j++) {
        elements[i][j] = rhs.elements[i][j];

      }
    }
    else {
      elements[i] = nullptr;
    }
  }
}

// Overloaded assignment operator - Covered in Lab 5
// Therefore, we shall not be overloading this operator in our Assignment 1
// MyADT & MyADT::operator=(const MyADT& rhs) {
   // cout << "MyADT::operator= executed!" << endl; // For testing purposes ... 
   // You can also use the above to figure out when this overloaded assignment = operator is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
   
   /* Put your code here */

//}
    
// Destructor
// Description: Destroys this object, releasing heap-allocated memory.
MyADT::~MyADT() {
   // cout << "MyADT::destructor" << endl;  // For testing purposes ...
   // You can also use the above to figure out when this destructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
  
  // delete/free dynamically allocated arrays
  // the actual elements[] and elementCount[] do not need to be freed as they will be gone when it goes out of scope
   unsigned int i;
   for (i = 0; i < MAX_ALPHA; i++) {
      if (elements[i] != nullptr) {
         delete[] elements[i];
      }
   }
   
}  


// Description: Returns the total number of elements currently stored in the data collection MyADT.  
unsigned int MyADT::getElementCount() const {

   unsigned int totalElementCount = 0;
   for (unsigned int i = 0; i < MAX_ALPHA; i++) {
      totalElementCount += elementCount[i];
   }
   return totalElementCount;
}


// Description: Inserts an element in the data collection MyADT.
// Precondition: newElement must not already be in the data collection MyADT.  
// Postcondition: newElement inserted and the appropriate elementCount has been incremented.
//                Returns "true" when the insertion is successfull, otherwise "false".
bool MyADT::insert(const Profile& newElement) {
 
   /* Put your code here */
   // get first letter of the username
   // take first letter - 'a' to get index
   // insert into the array pointed to by the pointer in the index

   char searchKey = newElement.getSearchKey();
   int traverseIndex = searchKey - 'a';
   int i;

   if (elementCount[traverseIndex] == MAX_ELEMENTS) {
      return false;
   }

   if (elements[traverseIndex] == nullptr) {
      // create a new dynamically allocated Profile array and set first index to be newElement
      elements[traverseIndex] = new Profile[MAX_ELEMENTS];
      elements[traverseIndex][0] = newElement;
      elementCount[traverseIndex]++;
   }
   else {
      // traverse the current array and compare each profile with the current profile
      for (i = elementCount[traverseIndex] - 1; (0 <= i) && (elements[traverseIndex][i] > newElement); i--) {
         elements[traverseIndex][i + 1] = elements[traverseIndex][i];
      }
      elements[traverseIndex][i + 1] = newElement;
      elementCount[traverseIndex]++;
   }
   return true;
}  

// Description: Removes an element from the data collection MyADT. 
// Postcondition: toBeRemoved (if found) is removed and the appropriate elementCount is decremented.
//                Returns "true" when the removal is successfull, otherwise "false".  
bool MyADT::remove(const Profile& toBeRemoved) {
   unsigned int i;
   unsigned int j;

   char searchKey = toBeRemoved.getSearchKey();
   int traverseIndex = searchKey - 'a';
   
   for ( i = 0; i < elementCount[traverseIndex]; i++) {
      if (elements[traverseIndex][i] == toBeRemoved) {
         std::cout << "in array: " << elements[traverseIndex][i] << endl; //debug
         std::cout << "toBeRemoved: " << toBeRemoved << endl; //debug
         for (j = i; j < (elementCount[traverseIndex] - 1); j++) {
            elements[traverseIndex][j] = elements[traverseIndex][j + 1];
         }
         elementCount[traverseIndex] -= 1;
         std::cout << elements[traverseIndex][0]; //debug
         return true;
      }
   }
   
   return false;
}  


// Description: Removes all elements from the data collection MyADT. 
// Postcondition: MyADT reverts back to its initialization state, i.e., 
//                the state it is in once it has been constructed (once
//                the default constructor has executed). 
void MyADT::removeAll() {
   // loop through and delete all profile objects in the sub arrays
   unsigned int i;
   for (i = 0; i < MAX_ALPHA; i++) {
      delete[] elements[i];
      elementCount[i] = 0;
   }
}   

// Description: Searches for target element in the data collection MyADT. 
//              Returns a pointer to the element if found, otherwise, returns nullptr.
Profile* MyADT::search(const Profile& target) {
    
   unsigned int i;
   char searchKey = target.getSearchKey();
   int traverseIndex = searchKey - 'a';
   
   for (i = 0; i < elementCount[traverseIndex]; i++) {
      if (elements[traverseIndex][i] == target) {
         Profile* targetProfile = &elements[traverseIndex][i];
         return targetProfile;
      }
   }
   return nullptr;
}  


// Description: Prints all elements stored in the data collection MyADT in ascending order of search key.
// ***For Testing Purposes - Not part of this class' public interface.***
void MyADT::print() {
  
   unsigned int i;
   unsigned int j;

   for (i = 0; i < MAX_ALPHA; i++) {
      for (j = 0; j < elementCount[i]; j++) {
         std::cout << elements[i][j] << endl;
      }
   }

} 

//  End of implementation file