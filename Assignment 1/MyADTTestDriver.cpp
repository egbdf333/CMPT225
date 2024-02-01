/*
 * FriendsBook.cpp - Assignment 1
 * 
 * Class Description: Social network application.
 *
 * In this version, we use our MyADT class.
 *
 * Author: Software developer A
 * Modified on: Jan. 2024
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

/* NOTE:
Using "getline(cin >> ws, theUserName);"
removes all leading whitespace -> ws     
*/

void join(MyADT & theMembers, string currentUser, string currentName, string currentEmail, string currentBirthday) {
    string theUserName = currentUser;
    string theName = currentName;
    string theEmail = currentEmail;
    string theBirthday = currentBirthday;

    // Create a new member profile
    Profile testMember(theUserName);

    // Ensure the userName is a valid username and not the default value defined in Profile class.
    Profile theMember(theUserName, theName, theEmail, theBirthday);
    if (theMembers.insert(theMember)) {
        cout << "Member: " << "'" << theMember.getUserName() << "'" << " has successfully joined FriendsBook." << endl;
    }
    return;
}


void leave(MyADT & theMembers, string currentUser) {
    string theUserName = currentUser;

    Profile toBeRemoved(theUserName);

    // Ensure the userName is a valid username and not the default value defined in Profile class.
    if ( toBeRemoved.getUserName() == Profile::getDefaultStrValue( ) )
        cout << "'" << theUserName << "'" << " is not a valid userName. A userName must have a lower case letter as its first character. Please, try again!." << endl;
    else {
        // Remove friend from FriendsBook
        if ( theMembers.remove(toBeRemoved) )
            cout << "Friend : " << "'" << toBeRemoved.getUserName() << "'" << " has now left this social network." << endl;
        else
            cout << "Friend : " << "'" << toBeRemoved.getUserName() << "'" << " is not a member of this social network!" << endl;
    }
    return;
}

 
void search(MyADT & theMembers, string currentUser) {
    string theUserName = currentUser;
    
    // Create a new member profile
    Profile theMember(theUserName);

    // Ensure the userName is a valid username and not the default value defined in Profile class.
    if ( theMember.getUserName() == Profile::getDefaultStrValue( ) )
         cout << "'" << theUserName << "'" << " is not a valid userName. A userName must have a lower case letter as its first character. Please, try again!." << endl;
   else {
        // Search
        Profile * target = theMembers.search(theMember);

        if ( target != nullptr )
            // Report to user
            cout << "Member: " << "'" << target->getUserName() << "'" << " has been successfully found in FriendsBook." << endl;
        else
            cout << "'" << theUserName << "'" << " is not a member of FriendsBook." << endl;
    }

    return;
} 


void modify(MyADT & theMembers, string currentUser, string modUser, string modEmail, string modBirthday) {    
    string newString = "";
    string theUserName = currentUser;
 
    cout << "Please, enter the username of the profile to be modified: ";  
    Profile theMember(theUserName);
    
    // Ensure the userName is a valid username and not the default value defined in Profile class.
    if ( theMember.getUserName() == Profile::getDefaultStrValue( ) )
        cout << "'" << theUserName << "'" << " is not a valid userName. A userName must have a lower case letter as its first character. Please, try again!." << endl;
    else {
        // Search
        Profile * target = theMembers.search(theMember);
        if ( target != nullptr ) {
            // Modify
            target->setName(modUser);
    
            target->setEmail(modEmail);
            
            target->setBirthday(modBirthday);        
        
        }
    }
  
    return;
}

void print(MyADT & theMembers) {
    
    cout << "Printing FriendsBook" << endl;
    cout << "\nThere are now " << theMembers.getElementCount() << " friends in FriendsBook." << endl;
    theMembers.print();
    
    return;
}

int main() {

    // Variables declaration
    MyADT members = MyADT(); 
    bool done = false;
    char input = 0;

    // test data
    string userName1 = "thai god of war";
    string name1 = "Kaolan Wongsawat";
    string email1 = "kws11@kga.jp";
    string birthday1 = "Dec 11";

    string userName2 = "fang of metsudo";
    string name2 = "Kanoh Agito";
    string email2 = "kag11@kga.jp";
    string birthday2 = "Dec 2";

    string userName3 = "devil lance";
    string name3 = "Himroki Beardsai";
    string email3 = "beard@kga.jp";
    string birthday3 = "Apr 4";

    string userName4 = "asura";
    string name4 = "Tokita Ohma";
    string email4 = "tko99@kga.jp";
    string birthday4 = "May 2";
        
    // Keep going until the user exits
    join(members, userName1, name1, email1, birthday1);
    join(members, userName2, name2, email2, birthday2);
    join(members, userName3, name3, email3, birthday3);
    join(members, userName4, name4, email4, birthday4);

    print(members);

    modify(members, userName1, "ramas personal guard", "rpg11@kga.jp", "Dec 12");

    search(members, userName3);

    print(members);

    leave(members, userName2);

    print(members);


    return 0;
}