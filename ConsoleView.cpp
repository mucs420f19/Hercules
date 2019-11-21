#include "ConsoleView.h"
#include "Command.h"
#include "CommandFactory.h"
#include <string>

const std::string PROMPT_STRING = "> ";

ConsoleView::ConsoleView(std::ostream &os, std::istream &is) : os(os), is(is) {}

void
ConsoleView::runREPL() {

  std::string line;
  os << PROMPT_STRING << std::flush;
  while (std::getline(is, line)) {
    make_command(os,split(line))->execute();
    os << PROMPT_STRING << std::flush;
  }
}

std::vector<std::string>
ConsoleView::split(const std::string &line) const {

  std::vector<std::string> tokenized;
  const char* WS = "\t ";
  auto wordStart = line.find_first_not_of(WS);
  while (wordStart != std::string::npos)
    {
      auto wordEnd = line.find_first_of(WS, wordStart);
      if (wordEnd == std::string::npos)
      {
        wordEnd = line.size();
      }
      tokenized.emplace_back(line.begin() + wordStart, line.begin() + wordEnd);
      wordStart = line.find_first_not_of(WS, wordEnd);
    }
  return tokenized;
}
