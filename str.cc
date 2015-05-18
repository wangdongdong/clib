/*
The MIT License (MIT)

Copyright (c) [2015] [liangchengming]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
 This is a handy string utils set, including string split,split,charset convert
 and etc.
*/


#include "str.h"
#include "log.h"
#include <sstream>

#ifdef __cplusplus
extern "C" {
#endif

int split(const std::string &src, const std::string &delimeter, std::vector<std::string> &fields) {
	fields.clear();

	if (src.empty()) {
		notice("Spliting empty string by \"%s\"\n", delimeter.c_str());
		return -1;
	}

	size_t begin = 0;
	size_t end   = 0;

	while ( true ) {
		end = src.find(delimeter, begin);
		if(end == std::string::npos) {
			break;
		}
		fields.push_back(src.substr(begin, end-begin));
		begin = end + delimeter.size();
	}

	fields.push_back(src.substr(begin, end-begin));

	return fields.size();
}




int strip(std::string& src, const std::string &chars) {
	if (chars.empty()) {
		notice("Noting to do.. Tring to strip nothing. chars==\"\" \n");
		return -1;
	}

	while(chars.find(src[0]) != std::string::npos) {
		src.erase(src.begin());
	}

	while(chars.find(*(src.rbegin())) != std::string::npos) {
		src.erase(src.end() - 1);
	}

	return 0;
}

/* try not to return std::string, becase that cause two times constructions. */
int join(const std::string &delim, std::vector<std::string> &words, std::string &res){

	std::ostringstream ostr;

	for (std::vector<std::string>::iterator iw = words.begin();
		iw != words.end(); iw++) {
		ostr << *iw;
		if (iw + 1 != words.end()) {
			ostr << delim;
		}
	}

	res = ostr.str();

	return 0;
}


int replace(std::string &src, const std::string &from, const std::string &to) {
	if (from.empty()) {
		notice("Tring to replace '' into '%s'\n", to.c_str());
		return -1;
	}

	size_t begin = 0;
	size_t end   = 0;
	std::ostringstream ostr;

	while(true) {
		end = src.find(from, begin);
		if (end == std::string::npos) {
			ostr << src.substr(begin);
			break;
		}
		ostr << src.substr(begin, end - begin) << to;
		begin = end + from.size();
	}
	
	src = ostr.str();
	return 0;
}



#ifdef __cplusplus
}
#endif


