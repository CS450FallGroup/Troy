#include <iostream>
#include "../../Scanner.hpp"

#include <sstream>
#include <fstream>

using namespace std;

int main(){

  string testIns[] = {
    "io/in/assignment2/programming_assignment_2-test_file_1.c",
    "io/in/assignment2/programming_assignment_2-test_file_2.c",
    "io/in/assignment2/programming_assignment_2-test_file_3.c",
    "io/in/assignment2/programming_assignment_2-test_file_4.c",
    "io/in/assignment2/programming_assignment_2-test_file_5.c",
    "io/in/assignment2/programming_assignment_2-test_file_6.c",
  };

  string testOuts[] = {
    "io/out/assignment2/output-programming_assignment_2-test_file_1.txt",
    "io/out/assignment2/output-programming_assignment_2-test_file_2.txt",
    "io/out/assignment2/output-programming_assignment_2-test_file_3.txt",
    "io/out/assignment2/output-programming_assignment_2-test_file_4.txt",
    "io/out/assignment2/output-programming_assignment_2-test_file_5.txt",
    "io/out/assignment2/output-programming_assignment_2-test_file_6.txt",
  };

  //iterate across input files
  for (int i = 0; i < 6; ++i) {
    //announce the file we've made it to
    cout << "input file: " << testIns[i] << endl;

    //open the file containing the correct answers
    ifstream key(testOuts[i]);
    if (!key.is_open()) {
      cout << "unable to open key file " << testOuts[i] << endl;
      exit(-1);
    }


    //dump all output to a stream for comparison later
    stringstream testout;
    streambuf* coutBackup = cout.rdbuf(testout.rdbuf());

    //get tokens
    {
      Scanner s(testIns[i]);

      list<Token> tokenList = s.getTokens();

      cout << endl <<
        "Token list:" << endl << endl;

      for (auto t = tokenList.begin(); t != tokenList.end(); ++t) {
        cout << "Token type: " << getReadableTokenType(t->getType()) << endl <<
          "Token:      " << t->getSpelling() << endl << endl;
      }

      cout << endl << endl;
    }

    //restore cout
    cout.rdbuf(coutBackup);

    //verification
    {
      char c1,c2;
      unsigned int pos = 0, line = 0;

      while (testout.get(c1) && key.get(c2)) {
        if (c1 != c2) {
          cout << "mismatch at " << line << ":" << pos << endl;
          
          cout << "My token type was " << string{c1};
          while (testout.get(c1) && c1 != '\n') {
            cout << string{c1};
          }
          cout << endl;

          exit(-1);
        }


        ++pos;
        if (c1 == '\n') {
          pos = 0;
          ++line;
        }
      }

      cout << "\tsuccess" << endl;
    }
  }

  return 0;
}

//a.exe io\in\assignment2\programming_assignment_2-test_file_1.c
