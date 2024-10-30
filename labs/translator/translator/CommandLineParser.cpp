#include "CommandLineParser.h"

void CommandLineParser::read_once(std::istream& f, std::string& r, std::string& cmd, std::string& arg) {
	getline(f, r);
	if (f.fail())
		throw std::exception("File fail"); // TODO: be more specific
	std::istringstream line(r);
	line >> cmd >> arg;
}
