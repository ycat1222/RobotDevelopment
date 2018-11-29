#pragma once
#include <exception>
#include <string>

namespace BBB{
class ErrorBBB : public std::exception{ 
  private:
  std::string str;

  public:
  ErrorBBB(std::string str_) : str(str_) {};
  const char* what() {return str.c_str();}
};
};