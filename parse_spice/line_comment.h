#pragma once

#include <parse/parse.h>

namespace parse_spice
{

struct line_comment
{
	line_comment();
	~line_comment();

	string debug_name;

	static token consume(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
};

}

