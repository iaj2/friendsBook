/*
 * FriendsBook.cpp - Assignment 1
 * 
 * Class Description: Social network application (partial implementation).
 *
 * In this version, we use our MyADT.
 *
 * ***You cannot remove/change the code provided in this file.***
 *
 * Author: AL, Isaac James
 * Modified on: Sept. 14, 2023
 */

#include <iostream>
#include <string>
#include <cctype>
#include "Profile.h"
#include "MyADT.h"

using std::cout;
using std::ws;
using std::cin;
using std::endl;
using std::getline;


void join(MyADT & theMembers) {
   Profile* newProfile;
   string userName;
   string name;
   string email;
   string birthday;

   // Init new profile with userName from user input
   cout << "Enter a userName (only lower/upper letters and underscore allowed, max 16 char)" << endl;
   cin >> userName;
   newProfile = new Profile(userName);
   

   // Check for memory allocation failure
   if(newProfile == nullptr) {
      cout << "Sorry. Something went wrong :(" << endl;
      return;
   }

   // Check if userName already exists
   if(theMembers.search(*newProfile) != nullptr) {
      cout << "Sorry that userName is taken :(" << endl;
      delete newProfile; // Delete new profile because of failure
      return;
   }

   // Get rest of user input
   cout << "Enter your name" << endl;
   cin.ignore();
   getline(cin, name);
   cout << "Enter your email (valid address, no spaces.)" << endl;
   cin >> email;
   cout << "Enter your birthday (month day year)" << endl;
   cin.ignore();
   getline(cin, birthday);

   // Set profile data
   newProfile->setName(name);
   newProfile->setEmail(email);
   newProfile->setBirthday(birthday);

   // Insert profile into MyADT
   theMembers.insert(*newProfile);

   cout << "You successfully joined the network ! :)" << endl;

}

// Removes profile from MyADT with a given username received on user input
void leave(MyADT & theMembers) {
   string userName;
   Profile * toLeave;
   cout << "Enter user name to leave the netowrk." << endl;
   cin >> userName;

   // Init new profile object with userName from user input
   toLeave = new Profile(userName);
   if(toLeave == nullptr) { // Check memory failure
      cout << "Sorry. Something went wrong :(" << endl;
      return;
   }

   // Check remove failure (userName not found)
   if(!theMembers.remove(*toLeave)) {
      cout << "Failed to leave the network.. User name must not exist" << endl;
      delete toLeave;
      return;
   }

   cout << userName << " successfully" << " left the network" << endl;
}

// Searches for a profile from a given MyADT with a username received on user input
void search(MyADT & theMembers) {
   string userName;
   Profile * target;
   Profile * foundUser;
   cout << "Enter the user name you'd like to search up" << endl;
   cin >> userName;

   target = new Profile(userName);
   if(target == nullptr) {
      cout << "Sorry, something went wrong :(" << endl;
      return;
   }

   foundUser = theMembers.search(*target);
   if(foundUser == nullptr) {
      cout << "No user with that userName exists" << endl;
      delete target;
      return;
   }
   
   cout << "User found ! Displaying profile information" << endl;
   cout << *foundUser;

   delete target;
}

// Modifies name on given profile based on user input
void modifyName(Profile &profile) {
   string newName;
   cout << "Enter name" << endl;
   cin.ignore();
   getline(cin, newName);

   profile.setName(newName);
}

// Description: modifies email on given profile based on user input
void modifyEmail(Profile &profile) {
   string newEmail;
   cout << "Enter new email (valid address, no spaces.)" << endl;
   cin >> newEmail;

   profile.setEmail(newEmail);
}

// Description: modifies the birthday on a given profile based on user input
void modifyBirthday(Profile &profile) {
   string newBirthday;
   cout << "Enter new birthday (month day year)" << endl;
   cin.ignore();
   getline(cin, newBirthday);

   profile.setBirthday(newBirthday);
}

// Gets username for profile to modify and then  
// calls respective modification function based on user input
void modify(MyADT & theMembers) {
   bool done = false;
   char input = 0;

   string userName;
   Profile * target;
   Profile * foundUser;
   cout << "Enter the user name you'd like to modify" << endl;
   cin >> userName;

   target = new Profile(userName);
   if(target == nullptr) {
      cout << "Sorry, something went wrong :(" << endl;
      return;
   }

   foundUser = theMembers.search(*target);
   if(foundUser == nullptr) {
      cout << "No user with that userName exists" << endl;
      delete target;
      return;
   }

   delete target; 

        
   // Keep going until the user exits
   while (!done) {
      // Print menu to stdout
      cout << endl << "Enter ..." << endl;
      cout << "n -> modify name" << endl;
      cout << "e -> modify email " << endl;
      cout << "b -> modify birthday" << endl;
      cout << "x -> exit" << endl;

      cout << "Your choice: ";
      cin >> input;
      cout << endl;
      input = tolower(input);
      switch(input) {
         case 'n': modifyName(*foundUser); break;
         case 'e': modifyEmail(*foundUser); break;
         case 'b': modifyBirthday(*foundUser); break;
         case 'x': cout << "\nSaved profile details.\n" << endl; 
                     done = true; break;
         default: cout << "Not sure what you mean! Please, try again!" << endl;
      }
   }

}

// Description: prints profiles stored in given MyADT
void print(MyADT & theMembers) {
   theMembers.print();
}

int main() {

    // Variables declaration
    MyADT members = MyADT();  // Object MyADT on the stack, its arrays on the heap
    bool done = false;
    char input = 0;
        
    // Keep going until the user exits
    while (not done) {
        // Print menu to stdout
        cout << "\n----Welcome to FriendsBook!" << endl << endl;
        cout << endl << "Enter ..." << endl;
        cout << "j -> to join FriendsBook by creating a profile." << endl;
        cout << "l -> to leave FriendsBook." << endl;
        cout << "s -> to search for a friend on FriendsBook." << endl;
        cout << "m -> to modify your profile on FriendsBook." << endl;
        cout << "p -> to print all members on FriendsBook." << endl;
        cout << "x -> to exit FriendsBook." << endl << endl;


        cout << "Your choice: ";
        cin >> input;
        cout << endl;
        input = tolower(input);
        switch(input) {
            case 'j': join(members); break;
            case 'l': leave(members); break;
            case 's': search(members); break;
            case 'm': modify(members); break;
            case 'p': print(members); break;
            case 'x': cout << "\n----Bye!\n" << endl; 
                      done = true; break;
            default: cout << "Not sure what you mean! Please, try again!" << endl;
        }
    }

    return 0;
}
