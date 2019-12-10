#pragma once

#include <iostream>
#include <string>
#include <vector>

class ConsoleView {

public:
  ConsoleView(std::ostream &os, std::istream &is);

  void runREPL();

private:
  std::vector<std::string> split(const std::string &line) const;

  std::ostream &os;
  std::istream &is;
};
