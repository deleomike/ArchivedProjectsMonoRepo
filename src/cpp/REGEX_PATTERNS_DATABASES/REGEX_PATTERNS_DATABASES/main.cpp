//
//  main.cpp
//  REGEX_PATTERNS_DATABASES
//
//  Created by Michael DeLeo on 6/10/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//


//REGEX
/*This is a means of describing a set of strings using a subset of common characteristics. For example, the common characteristics of aaa, aba, and aca are that they all start and end with the letter a.
 
 Regular expressions add a level of abstraction to strings that makes it easier to search and manipulate text. While they can seem very confusing at first, the syntax for regular expressions is pretty standard across different programming languages (so knowledge of RegEx is universally applicable).
 */

//Character Classes
/*This is not a class in the traditional sense, but rather a term that refers to a set of one or more characters that can be used to match a single character from some input string. Here are the basic forms:
- Enclosed within square brackets. Specify the what you'd like your expression to match within square brackets; for example, [a-f] will match any lowercase a through f character.
- Predefined: \ followed by a letter. For example, \d for matching digits (0-9) or \D for matching non-digits. There are also additional predefined character classes that are followed by a set of curly braces, such as \p{Punct} which matches punctuation (i.e.: !"#$%&'()*+,-./:;<=>?@[]^_`{|}~).
 */

//Some key constructs to know are:
/*
. The period will match any character; it does not have to be a letter.
+ When appended to a character or character class, it means 'one or more instances of the previous character'.
* When appended to a character or character class, it means 'zero or more instances of the previous character'.
^ if this is before a character class, it means you're matching the first character; however, if this is the first character inside a bracketed character class, it means negation/not. For example, ^[a].+ or ^a.+ matches any consecutive sequence of 2 or more characters starting with the letter a, and ^[^a].+ matches any consecutive sequence of 2 or more characters not starting with a.
$ When appended to a character or character class, it means 'ends with the previous character'. For example, .+a$ will match a sequence of 2 or more characters ending in a.
*/

//EXAMPLE
/*
// This will match a sequence of 1 or more uppercase and lowercase English letters as well as spaces
String myRegExString = "[a-zA-Z\\s]+";

// This is the string we will check to see if our regex matches:
String myString = "The quick brown fox jumped over the lazy dog...";

// Create a Pattern object (compiled RegEx) and save it as 'p'
Pattern p = Pattern.compile(myRegExString);

// We need a Matcher to match our compiled RegEx to a String
Matcher m = p.matcher(myString);

// if our Matcher finds a match
if( m.find() ) {
    // Print the match
    System.out.println( m.group() );
}
 */
//#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <set>
#include <regex>

using namespace std;

vector<string> split_string(string);


int main()
{
    int N;
    cin >> N;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    multiset<string> users;
    
    for (int N_itr = 0; N_itr < N; N_itr++) {
        string firstNameEmailID_temp;
        getline(cin, firstNameEmailID_temp);    //get full line
        
        vector<string> firstNameEmailID = split_string(firstNameEmailID_temp);  //split up full line
        
        string firstName = firstNameEmailID[0];
        
        string emailID = firstNameEmailID[1];
        regex e(".+@gmail\\.com$");   //REGEX
        bool match = regex_match(emailID,e);
        if (match){
        users.insert(firstName);   //create user, and store
        }
    }
    //TODO
    for(auto& it : users)
    {
        cout << it << endl;
    }
    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });
    
    input_string.erase(new_end, input_string.end());
    
    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }
    
    vector<string> splits;
    char delimiter = ' ';
    
    size_t i = 0;
    size_t pos = input_string.find(delimiter);
    
    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));
        
        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }
    
    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));
    
    return splits;
}

