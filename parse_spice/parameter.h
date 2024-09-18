#pragma once

#include <parse/parse.h>
#include <parse/syntax.h>

namespace parse_spice
{

struct parameter : parse::syntax
{
	parameter();
	parameter(string name, string value);
	parameter(tokenizer &tokens, void *data = NULL);
	~parameter();

	string name;
	string value;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}
