#pragma once

#include <parse/parse.h>
#include <parse/syntax.h>
#include "parameter.h"

namespace parse_spice
{

struct device : parse::syntax
{
	device();
	device(tokenizer &tokens, void *data = NULL);
	~device();

	string name;
	vector<string> ports;
	string type;
	vector<parameter> params;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}
