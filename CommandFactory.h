#pragma once

#include "Command.h"

std::unique_ptr<Command>
make_command(std::ostream& os, const std::vector<std::string> &cmdLineArgs);
