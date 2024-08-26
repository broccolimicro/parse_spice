#pragma once

#include <parse/parse.h>
#include <parse/syntax.h>
#include "subckt.h"

namespace parse_spice
{

struct netlist : parse::syntax
{
	netlist();
	netlist(tokenizer &tokens, void *data = NULL);
	~netlist();

	vector<subckt> subckts;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}
