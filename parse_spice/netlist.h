#pragma once

#include <parse/parse.h>
#include <parse/syntax.h>
#include "subckt.h"

namespace parse_spice
{

struct netlist : parse::syntax
{
	netlist();
	netlist(tokenizer &tokens, std::any data=std::any());
	~netlist();

	vector<string> header;
	vector<subckt> subckts;
	vector<string> footer;

	void parse(tokenizer &tokens, std::any data=std::any());
	static bool is_next(tokenizer &tokens, int i = 1, std::any data=std::any());
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}
