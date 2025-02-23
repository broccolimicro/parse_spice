#include "factory.h"

#include "netlist.h"

namespace parse_spice {

parse::syntax *produce(tokenizer &tokens, void *data) {
	return new netlist(tokens, data);
}

void expect(tokenizer &tokens) {
	tokens.expect<netlist>();
}

void register_syntax(tokenizer &tokens) {
	netlist::register_syntax(tokens);
}

}

