#pragma once

#include <parse/parse.h>

namespace parse_spice
{

struct command
{
	command();
	~command();

	string debug_name;

	static token consume(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
};

}

