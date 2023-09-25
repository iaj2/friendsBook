/**
 * MyADT_test_driver
 * 
 * Description: unit tests for MyADT class methods.
 * 
 * Author: Isaac James
*/

#include <iostream>
#include "MyADT.h"
#include "Profile.h"

using std::cout;
using std::endl;

// Description: tests the getElementCount() method of MyADT
bool testGetElementCount(MyADT &adt, unsigned int expectedResult) {
    if(adt.getElementCount() == expectedResult){
        return true;
    }

    return false;
}

// Description: tests the insert() method of MyADT
bool testInsert(MyADT &adt, Profile &profile) {
    return adt.insert(profile);
}

bool testSearch(MyADT &adt, Profile &profile) {
    return (adt.search(profile) != nullptr);
}

// Description: tests the remove() method of MyADT
bool testRemove(MyADT &adt, Profile &profile) {
    return adt.remove(profile); 
}

// Description: tests the removeAll() method of MyADT
bool testRemoveAll(MyADT &adt) {
    adt.removeAll();

    if (adt.getElementCount() == 0) {
        return true;
    }

    return false;
}

// Description: tests copy constructor of MyADT by searching for profiles that were inserted
// in the source object
bool testCopyConstructor (MyADT &adt, Profile profiles[], int arrSize) {
    MyADT destAdt = adt; // allocated on stack

    // sanity check
    destAdt.print();
    
    for(int i = 0; i < arrSize; i++) { 
        if(destAdt.search(profiles[i]) == nullptr) {
            return false;
        }
    }

    return true;
}


int main () {
    // init new ADT
    MyADT * adt = new MyADT();

    // Test initialized properly
    if(adt == nullptr) {
        cout << "Failed to initialize MyADT" << endl;
        return -1;
    }

    // Test getElementCount
    // Should return 0
    cout << "-- TEST GET ELEMENT COUNT (EXPECTED: 0) --" << endl;
    if(testGetElementCount(*adt, 0)) {
        cout << "PASSED" << endl;
    }
    else {
        cout << "FAILED" << endl;
    }


    // Set up profiles array to use for inserting, searching and removing
    Profile profilesToTest_1[] = {
        Profile("Anna"), Profile("Bob"), Profile("Zuck"), Profile("Aang")
    }; // allocate on stack

    // Test insert and find inserted element
    cout << "-- TEST INSERT --" << endl;
    for(int i = 0 ; i < 4; i++){
        if(testInsert(*adt, profilesToTest_1[i])) {
            cout << "PASSED " << i+1 << endl;
        }
        else {
            cout << "FAILED " << i+1 << endl;
        }
    }

    // Test search for elements just inserted
    cout << "-- TEST SEARCH --" << endl;
    for(int i = 0 ; i < 4; i++){
        if(testSearch(*adt, profilesToTest_1[i])) {
            cout << "PASSED " << i+1 << endl;
        }
        else {
            cout << "FAILED " << i+1 << endl;
        }
    }

    // Check element count again
    cout << "-- TEST GET ELEMENT COUNT (EXPECTED: 4) --" << endl;
    if(testGetElementCount(*adt, 4)) {
        cout << "PASSED" << endl;
    }
    else {
        cout << "FAILED" << endl;
    }
    
    // Test Print for sanity check
    adt->print();

    // Test remove a profile
    cout << "-- TEST REMOVE --" << endl;
    for(int i = 0; i < 2; i++) {
        if(testRemove(*adt, profilesToTest_1[i])) {
                cout << "PASSED " << i+1 << endl;
            }
            else {
                cout << "FAILED " << i+1 << endl;
            }
    }

    // Test Remove all
    cout << "-- TEST REMOVE ALL --" << endl;
    if(testRemoveAll(*adt)) {
        cout << "PASSED" << endl;
    }
    else {
        cout << "FAILED" << endl;
    }

    // print for sanity check
    adt->print(); // nothing should be displayed in sdout

    // Test Insert on full and remove non-existent profile
    // Precondition: number of profiles to test must be > MAX_ELEMENTS
    Profile profilesToTest_2[] = {
        Profile("Anna"), Profile("Aang"), Profile("Abba"), Profile("Abbey"),
        Profile("Alicia"), Profile("Axel")
    }; // allocate on stack
    
    cout << "-- TEST INSERT ON FULL --" << endl;
    for(int i = 0; i < 5; i++) {
        if (i==5) {
            
        }
        if(testInsert(*adt, profilesToTest_2[i])) {
            cout << "PASSED " << i+1<< endl;
        }
        else {
            cout << "FAILED " << i+1 << endl;
        }
    } // SHOULD FAIL TO INSERT
    if(!testInsert(*adt, profilesToTest_2[5])) {
            cout << "PASSED " << 6 << endl;
        }
        else {
            cout << "FAILED " << 6 << endl;
        }
    // SHOULD FAIL TO REMOVE
    cout << "-- TEST REMOVE NON-EXISTENT PROFILE --" << endl;
    if(!testRemove(*adt, profilesToTest_2[5])) {
            cout << "PASSED" << endl;
        }
        else {
            cout << "FAILED" << endl;
        }

    // sanity check
    adt->print();


    // Check element count again
    cout << "-- TEST GET ELEMENT COUNT (EXPECTED: 5) --" << endl;
    if(testGetElementCount(*adt, 5)) {
        cout << "PASSED" << endl;
    }
    else {
        cout << "FAILED" << endl;
    }

    // Test copy constructor
    cout << "-- TEST COPY CONSTRUCTOR --" << endl;
    // pass array size of 5 since the 6th should have failed to insert in adt
    if(testCopyConstructor(*adt, profilesToTest_2, 5)) {
        cout << "PASSED" << endl;
    }
    else {
        cout << "FAILED" << endl;
    }

    // Test remove all using remove()
    cout << "-- TEST REMOVE ALL WITH SINGLE REMOVE --" << endl;
    for(int i = 0; i < 5; i++) {
        if (testRemove(*adt, profilesToTest_2[i])) {
            cout << "PASSED " << i+1 << endl;
        }
        else {
            cout << "FAILED " << i+1 << endl;
        }
    }

    // Check element count again
    cout << "-- TEST GET ELEMENT COUNT (EXPECTED: 0) --" << endl;
    if(testGetElementCount(*adt, 0)) {
        cout << "PASSED" << endl;
    }
    else {
        cout << "FAILED" << endl;
    }

    adt->print(); // should print nothing

    // Delete adt
    delete adt;

    return 0;
}