#include <iostream>
#include "../../Scanner.hpp"

using namespace std;

int main(int argc, char** argv){

  if (argc < 2) {
    cout << "usage: " << argv[0] << " inputfile" << endl;
    return 0;
  }

  //okay now assume that argv[1] is the desired input filename :D
  Scanner s(argv[1]);

  list<Token> tokenList = s.getTokens();

  if (tokenList.empty())  return 0;
  
  cout << endl <<
    "Token list:" << endl << endl;

  for (auto t = tokenList.begin(); t != tokenList.end(); ++t) {
    cout << "Token type: " << getReadableTokenType(t->getType()) << endl <<
      "Token:      " << t->getSpelling() << endl << endl;
  }

  cout << endl << endl;

  return 0;
}