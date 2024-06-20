/*-------------------------------------------

Program 2: Search Engine

This project, uses data structure of sets to store in 
multiple URL results of searched terms and maps it 
with the term to print out results

Course: CS 251, Spring 2024, UIC

System: Visual Studio Code

Author: Srijan Suresh

------------------------------------------- */
#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm> 
#include <fstream>
#include <vector>

using namespace std;

/**
 * Cleans a specific token by:
 * - Removing leading and trailing punctuation
 * - Converting to lowercase
 * If the token has no letters, returns the empty string.
 */
string cleanToken(string s) {
  // TODO_STUDENT
  if(s.empty()){  // If empty then end function with empty token
    return "";
  }
  else{

    for(int i=0; i<s.length(); i++){  // convert to lowercase
      s.at(i)=tolower(s.at(i));
    }

    string temp="";
    bool letterExist=false;

    for(auto c: s){   // checks if a letter exists in token

      if(isalpha(c)){
        letterExist=true;
      }

    }

    if(letterExist){
      // Remove leading punctuation
      for (int i = 0; i < s.length(); i++) {

        if (!ispunct(s.at(i))) {
          temp = s.substr(i);
          break;
        }

      }

      // Remove trailing punctuation
      for (int i = temp.length() - 1; i >= 0; i--) {

        if (!ispunct(temp.at(i))) {
          temp = temp.substr(0, i + 1);
          break;
        }

      }
      
    }
    if (temp.empty() || !letterExist) {    //checks if token turns empty after clean
      return "";
    }
    return temp;
  }
}


/**
 * Returns a set of the cleaned tokens in the given text.
 */
set<string> gatherTokens(string text) {   
  // TODO_STUDENT
  set<string>tokens;
  string temp ="";
  for(char c: text){    
    //takes in words from text into set and then performs clean tokens then returns the set

    if(c!=' '){ // when whitespace occurs word ends
      temp+=c;
    }
    
    else{
      tokens.insert(cleanToken(temp));
      temp="";
    }
     
  }
  tokens.insert(cleanToken(temp));
  tokens.erase("");

  return tokens;
}

/**
 * Builds the inverted index from the given data file. The existing contents
 * of `index` are left in place.
 */
int buildIndex(string filename, map<string, set<string>>& index) {
  // TODO_STUDENT
  ifstream inFS;   // Input file stream 
  int URLcount =0;
  inFS.open(filename);
  if(!inFS.is_open()){  //if the file is not open then return 0 denoting no URL's found
    return URLcount;
  }
  string sentence;
  string URL;
  int numIndex=0;
  while (!inFS.eof()) {   
    //Goes through file when until end
    getline(inFS,URL);
    URLcount++;     //increment amount of URL processed
    getline(inFS,sentence);
    set<string>tokens=gatherTokens(sentence); //Gather token
    tokens.erase("");
    if (!tokens.empty() && !URL.empty()) {  //check for null case
      for (const auto &token : tokens) {
        index[token].insert(URL);     // maps the url with token if token and url exists
      }
    }
 
    if(inFS.eof()) {
      break;
    }
  }

  return URLcount-1;    // returns total amount of urls processed
}

/**
 * Runs a search query on the provided index, and returns a set of results.
 *
 * Search terms are processed using set operations (union, intersection, difference).
 */
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
  vector<string> queryWords;
  set<string>emptySet;
  string word = "";

  // Remove white space and add words to vector
  for (auto letter : sentence) {
    if (isalpha(letter)||letter=='+'||letter=='-') {
      word += tolower(letter);
    } 
    else {
      if (!word.empty()) {
        queryWords.push_back(word);
        word = "";
      }
    }
  }

  if (!word.empty()) {    //Null case
    queryWords.push_back(word); 
  }
 
  // Initialize results with the set corresponding to the first term

  set<string> results = index[queryWords[0]]; 

  for (int wordIndex = 1; wordIndex < queryWords.size(); ++wordIndex) {
    // Check for the prefix and extract the term accordingly
    string term = "";
    if(queryWords[wordIndex][0] == '+' || queryWords[wordIndex][0] == '-'){
      term = queryWords[wordIndex].substr(1);
    }
    else{
      term = queryWords[wordIndex];
    }

    set<string> URL = index[term];
    //Performs Intersection if + prefix
    if (queryWords[wordIndex][0] == '+') {
      set<string> tempResult;
      set_intersection(results.begin(), results.end(), URL.begin(), URL.end(),inserter(tempResult, tempResult.begin()));
      results = move(tempResult);
    } 
    //Performs Difference if - prefix
    else if (queryWords[wordIndex][0] == '-') {
      set<string> tempResult;
      set_difference(results.begin(), results.end(), URL.begin(), URL.end(),inserter(tempResult, tempResult.begin()));
      results = move(tempResult);
    } 
    else {
     // If there is no symbol, treat it as a regular term and use set union
      set<string> tempResult;
      set_union(results.begin(), results.end(), URL.begin(), URL.end(),inserter(tempResult, tempResult.begin()));
      results = move(tempResult);
    }
  }

  return results;
}
/**
 * Runs the main command loop for the search program
 */
void searchEngine(string filename) {
  // TODO_STUDENT
  map<string, set<string>>index;
  set<string>resultURL;
  string command;
  if(buildIndex(filename,index)==0){      //Default case no file found
    cout<<"Invalid filename."<<endl;      
    cout<<"Stand by while building index..."<<endl;
    cout<<"Indexed 0 pages containing 0 unique terms\n"<<endl;
  }
  else{
    int urlSize = buildIndex(filename,index);     //Perform mapping URLs with Term and output value based
    int sizeSet =index.size();
    cout<<"Stand by while building index..."<<endl;
    cout<<"Indexed ";
    cout<<urlSize;
    cout<<" pages containing ";
    cout<<sizeSet;
    cout<<" unique terms"<<endl;
  }
  while(true){
    cout<<"\nEnter query sentence (press enter to quit): ";
    getline(cin,command);
    if(command.empty()){
      break;
    }
    resultURL=move(findQueryMatches(index,command));
    cout<<"Found ";
    cout<<resultURL.size();
    cout<<" matching pages"<<endl;
    for(auto url:resultURL){      //Output urls for each word mapped with set
      cout<<url<<endl;
    }
  }
  cout<<"Thank you for searching!";
  
}
