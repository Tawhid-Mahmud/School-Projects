//Name: Mohammad Mahmud
//Class: CS-335
//Final
//subsequence.cc
/* The first program finds the longest common subsequence in between two strings and
Prints the length of the string and backtracks the program to print the common
String
*/

#include <iostream>
#include <string>

using namespace std;
//Finds the maximum of two values
int max(int a, int b);
// finds the longest subsequence in two strings
void longSub(string First_string, string Second_string, int m, int q)
{
  int L[m + 1][q + 1]; 
    int i, j; 
  
    for (i = 0; i <= m; i++) { 
        for (j = 0; j <= q; j++) { 
            if (i == 0 || j == 0) {
                L[i][j] = 0;
            } 
  
            else if (First_string[i - 1] == Second_string[j - 1]){
                L[i][j] = L[i - 1][j - 1] + 1; 
            }
  
            else{
                L[i][j] = max(L[i - 1][j], L[i][j - 1]); 
            }
        }
    } 
  
    
    int num =L[m][q];
    cout << num << endl; 

//Back tracking the table for the common subsequence 
    char str[num+1];
    str[num]=0;
    int index = m, jump =q;
    while(index>0 && jump>0)
    {
      if(First_string[index-1] == Second_string[jump-1])
      {
        str[num-1] =  First_string[index-1];
        index--;
        jump--;
        num--;
      }
      else if(L[index-1][jump] > L[index][jump-1])
      {
        index--;
      }
      else
      {
        jump--;
      }
    }
    cout << str <<endl;
}

//Finds the maximum of two values
int max(int a, int b)
{
  return (a>b)?a:b;
}


int subsequence_driver(int argc, char **argv) {
    const string first_word(argv[1]);
    const string second_word(argv[2]);
    //size of both strings
    int m = first_word.length();
    int n = second_word.length();
    
    longSub(first_word,second_word,m,n);
    return -1;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << "<word_a>" << "<word_b>" << endl;
		return 0;
    }
    subsequence_driver(argc, argv);
    return 0;
}
