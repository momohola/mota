#pragma once
#include <string>

class EncodingTransform
{
public:
	static std::string UTF8ToString(const std::string& str);
	static std::string StringToUTF8(const std::string& str);
};

