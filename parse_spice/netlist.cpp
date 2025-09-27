#include "netlist.h"
#include "tokens/line_comment.h"
#include "tokens/command.h"
#include "tokens/node.h"
#include "tokens/number.h"
#include <parse/default/white_space.h>
#include <parse/default/new_line.h>

namespace parse_spice {

netlist::netlist() {
	debug_name = "spice_netlist";
}

netlist::netlist(tokenizer &tokens, void *data) {
	debug_name = "spice_netlist";
	parse(tokens, data);
}

netlist::~netlist() {

}

void netlist::parse(tokenizer &tokens, void *data) {
	tokens.syntax_start(this);

	tokens.increment(false);
	tokens.expect(".end");
	tokens.expect(".END");

	tokens.increment(true);
	tokens.expect<subckt>();
	tokens.expect<parse::new_line>();

	while (tokens.decrement(__FILE__, __LINE__, data)) {
		if (tokens.found<subckt>()) {
			subckts.push_back(subckt(tokens, data));
		} else if (tokens.found<parse::new_line>()) {
			tokens.next();
		}

		tokens.increment(false);
		tokens.expect<subckt>();
		tokens.expect<parse::new_line>();
	}

	if (tokens.decrement(__FILE__, __LINE__, data)) {
		tokens.next();
	}

	tokens.syntax_end(this);
}

bool netlist::is_next(tokenizer &tokens, int i, void *data) {
	return true;
}

void netlist::register_syntax(tokenizer &tokens) {
	if (!tokens.syntax_registered<netlist>())
	{
		tokens.register_syntax<netlist>();
		subckt::register_syntax(tokens);
		tokens.register_token<parse::white_space>(false);
		tokens.register_token<line_comment>(false);
		tokens.register_token<command>();
		tokens.register_token<parse::new_line>();
	}
}

string netlist::to_string(string tab) const {
	string result;

	for (auto ckt = subckts.begin(); ckt != subckts.end(); ckt++) {
		result += ckt->to_string(tab);
	}

	result += ".end\n";

	return result;
}

parse::syntax *netlist::clone() const {
	return new netlist(*this);
}

}
