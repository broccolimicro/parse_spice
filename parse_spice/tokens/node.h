#pragma once

#include <parse/parse.h>

namespace parse_spice
{

struct node
{
	node();
	~node();

	string debug_name;

	static token consume(tokenizer &tokens, std::any data=std::any());
	static bool is_next(tokenizer &tokens, int i = 1, std::any data=std::any());
};

}

