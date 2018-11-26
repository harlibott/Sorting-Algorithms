#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <stdlib.h> 
#include "sort.h"

using namespace std;

const char INSERTION = 'i';
const char MERGE = 'm';
const char QUICK = 'q';
const char QUIT = 'e';
const char COMMANDS_LIST = 'c';

char commandsArray[5] = {INSERTION, MERGE, QUICK, QUIT, COMMANDS_LIST};

int size = 0;
int num[10000];
int mergeCount = 0;
int insertionCount = 0;
int quickCount = 0;

void commands(){
  cout << endl;
  cout << "COMMANDS: " << endl;
  // handles printing out the commands 
  string example = "";
  for (int i = 0; i < 5; i++){
    cout << "   " << "(" << commandsArray[i] << ") " << "- "; 
    switch(i){
    case 0:
      example = "Insertion Sort";
      break;
    case 1:
      example = "Merge Sort";
      break;
    case 2:
      example = "Quick Sort";
      break;
    case 3:
      example = "Quit";
      break;
    case 4:
      example = "Commands List";
      break;
    default:
       example = "No options availible";
    }
    cout << example << endl; 
  }
}// commands

void commandDirection(char command){
  if(command == 'e'){
    cout << "\nQUITTING...\n" << endl;
    exit(EXIT_SUCCESS);
  }else if(command == 'i'){
    cout << endl;
    cout << "Insertion Sort: ";
    insertionSort();
    print();
    cout << "\nTotal # of comparisons: ";
    cout << insertionCount << endl;
  }else if(command == 'm'){
    cout << endl;
    cout << "Merge Sort: ";
    mergeSort(0, size-1);
    print();
    cout << "\nTotal # of comparisons: ";
    cout << mergeCount << endl;
  }else if(command == 'q'){
    cout << endl;
    cout << "Quick Sort: "; 
    quickSort(0,size-1);
    print();
    cout << "\nTotal # of comparisons: ";
    cout << quickCount << endl;
  }else if(command == 'c'){
    commands();
  }else if(command == 'p'){
    cout << endl;
    print();
    cout << endl;
  }else if(command == 's'){
    cout << endl;
    cout << size << endl;
  }
}// commandDirection

void print(){

  for(int i = 0; i < size; i++){
    cout << num[i] << + " ";
  }
}// print

int partition(int beg, int end){
  int pivot = num[end];
  int i = (beg-1);

  for(int j = beg; j < end; j++){
    if(num[j] <= pivot){
      i++;

      int temp = num[i];
      num[i] = num[j];
      num[j] = temp;
      quickCount ++;
    }
  }// for

  int temp = num[i+1];
  num[i+1] = num[end];
  num[end] = temp;

  return i+1;
}// partition

void insertionSort(){
  int j;
  for(int i = 1; i < size; i++){
    int temp = num[i];
    j = i-1;
    
    while(j >= 0 && num[j] > temp){
      num[j+1] = num[j];
      j = j-1;
      insertionCount ++;
    }
    num[j+1] = temp;
  }// for
}// insertion sort

void merge(int l, int m, int r){
  int i, j, k;
  int num1 = m-l + 1;
  int num2 = r-m;

  int left[num1];
  int right[num2];

  for(i = 0; i < num1; i++){
    left[i] = num[l+i];
  }// for

  for(j= 0; j < num2; j++){
    right[j] = num[m+1+j];
  }// for

  i = 0;
  j = 0;
  k = l;

  while(i < num1 && j < num2){
    if(left[i] <= right[j]){
      num[k] = left[i];
      i++;
      mergeCount ++;
    }else{
      num[k] = right[j];
      j++;
      mergeCount ++;
    }
    k++;
  }// while

  while(i < num1){
    num[k] = left[i];
    i++;
    k++;
  }// while

  while(j < num2){
    num[k] = right[j];
    j++;
    k++;
  }// while
}// merge

void mergeSort(int l, int r){
  if(l < r){
    int m = l+(r-l)/2;
    mergeSort(l, m);
    mergeSort(m+1, r);
    merge(l, m, r);
  }
}// merge sort

void quickSort(int beg, int end){
 
  if(beg < end){
    int index = partition(beg, end);

    quickSort(beg, index-1);
    quickSort(index+1, end);
  }
}// quick sort

void prompt(){
  string commandString;
  string err = "There was an error. Please type only char letters listed in commands list (c) in lower case form...";
  
  cout << "\nEnter an algoirthm for sorting, (i, m, q): ";
  cin >> commandString;
  char command = commandString.at(0);
     
  if(command == 'i' || command == 'm' || command == 'q' || command == 'c' || command == 'e' || command == 'p'|| command == 's'){
    commandDirection(command);
  }else{
    cout << "\n" << err << endl;
  }
}// prompt

int main(int argc, char* argv[]){
 //opens file
  if (argc > 1) {
    string fn = argv[1];
    int file;
    ifstream fin;
    
    cout << endl;
    fin.open(fn.c_str());
    assert(fin.is_open());

    cout << "Welcome to the binary search tree program..."<< endl;
    cout << "The name of the file you are using is: " + fn << endl;
    
    int i = 0;
    int count = 0;
    
    while(fin >> file){
      count ++;
      num[i] = file;
      i++;
    }
    size = count;
  }else{
    cout << "No file entered. Please enter a file containing a list. Exiting..."<< endl;
    return -1;
  }
  commands();

  while (true){
    prompt();
  }
}// main

