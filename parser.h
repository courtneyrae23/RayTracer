#ifndef __PARSE_H_INCLUDED__   // if x.h hasn't been included yet...
#define __PARSE_H_INCLUDED__

#include <string>

class Parser{
	public:
	  void parse(std::string, std::vector<Triangle>&);
};

#endif