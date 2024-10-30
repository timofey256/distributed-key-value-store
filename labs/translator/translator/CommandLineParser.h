#pragma once

#include <string>
#include <sstream>

class CommandLineParser
{
	void read_once(std::istream& f, std::string& r, std::string& cmd, std::string& arg);
};

