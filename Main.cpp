// HerculesProject.cpp : Defines the entry point for the application.
//

#include "ConsoleView.h"

int main(int argc, char** argv)
{
  ConsoleView view(std::cout, std::cin);
  view.runREPL();
  return 0;
}
