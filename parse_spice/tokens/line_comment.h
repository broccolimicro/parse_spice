#pragma once

#include <parse/parse.h>

namespace parse_spice
{

struct line_comment
{
	line_comment();
	~line_comment();

	string debug_name;

	static token consume(tokenizer &tokens, std::any data=std::any());
	static bool is_next(tokenizer &tokens, int i = 1, std::any data=std::any());
};

std::string comment_string(std::string s);
std::string string_from_comment(std::string s);

}

