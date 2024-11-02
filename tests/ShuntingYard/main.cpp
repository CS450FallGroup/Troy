/**
 * @file main.cpp
 * @author Bo THompson (extralife.xyz)
 * @brief for testing the Shunting Yard module
 * @version 0.1
 * @date 2024-10-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../../Scanner.hpp"
#include "../../PostFixEvaluator.hpp"
#include <sstream>
#include <fstream>

using namespace std;

int main(){

  string testIns[] = {
    "io/in/shuntyard/t1",
    "io/in/shuntyard/t2",
    "io/in/shuntyard/t3",
    "io/in/shuntyard/t4",
    "io/in/shuntyard/t5", //I'm sorry that we have to do this one. Pray that we don't gotta handle pointer stuff
  };

  string testOuts[] = {
    "io/out/shuntyard/t1",
    "io/out/shuntyard/t2",
    "io/out/shuntyard/t3",
    "io/out/shuntyard/t4",
    "io/out/shuntyard/t5",
  };

  //iterate across input files
  for (int i = 0; i < 5; ++i) {
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

      PostFixEvaluator currentEquation;

      for(auto t: tokenList){
          currentEquation.Eval(t);
      }
      //at this point you'd probably want to instantiate your shunting yard conversion object and feed it this list of tokens
      //I think that it would be most convenient to just output a list of tokens for the converted postfix expression

      //here's how you'd probably want to output the token list for comparison against the test output files
      for(int i = 0; i < currentEquation.getEquation().size(); i++){
          cout << currentEquation.getEquation().at(i).getSpelling() << " ";
      }

      cout << endl << endl;
    }

    //restore cout
    cout.rdbuf(coutBackup);

    //here's the actual output for this file
    cout << testout.str();

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
