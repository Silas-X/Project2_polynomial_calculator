#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

namespace GeneralFunctions {
bool getNumber(int &x) {
  std::string str;
  std::getline(std::cin, str);
  for (std::string::iterator i = str.begin(); i != str.end(); i++)
    if (!isdigit(*i)) return false;
  std::stringstream ss;
  ss.clear();
  ss << str;
  ss >> x;
  return true;
}
}  // namespace GeneralFunctions