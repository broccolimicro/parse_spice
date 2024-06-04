#pragma once

#include <parse/parse.h>
#include <parse/syntax.h>
#include "device.h"

namespace parse_spice
{

struct subckt : parse::syntax
{
	subckt();
	subckt(tokenizer &tokens, void *data = NULL);
	~subckt();

	string name;
	vector<string> ports;
	vector<device> devices;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}
