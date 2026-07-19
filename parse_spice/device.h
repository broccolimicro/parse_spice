#pragma once

#include <parse/parse.h>
#include <parse/syntax.h>
#include "parameter.h"

namespace parse_spice
{

struct device : parse::syntax
{
	device();
	device(tokenizer &tokens, std::any data=std::any());
	~device();

	vector<string> header;
	string atend;

	string name;
	vector<string> ports;
	string type;
	vector<parameter> params;

	void parse(tokenizer &tokens, std::any data=std::any());
	static bool is_next(tokenizer &tokens, int i = 1, std::any data=std::any());
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}
