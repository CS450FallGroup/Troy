#include "Tools.hpp"

string getLowercase(const string &s){
  string out;
  
  for (auto c: s) {
    out += tolower(c);
  }

  return out;
}