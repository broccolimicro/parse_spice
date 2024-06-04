#include "subckt.h"
#include "line_comment.h"
#include <parse/default/symbol.h>
#include <parse/default/number.h>
#include <parse/default/white_space.h>
#include <parse/default/new_line.h>

namespace parse_spice {

subckt::subckt() {
	debug_name = "subckt";
}

subckt::subckt(tokenizer &tokens, void *data) {
	debug_name = "subckt";
	parse(tokens, data);
}

subckt::~subckt() {

}

void subckt::parse(tokenizer &tokens, void *data) {
	tokens.syntax_start(this);

	tokens.increment(true);
	tokens.expect<parse::new_line>();

	tokens.increment(false);
	tokens.expect<parse::symbol>();
	tokens.expect<parse::number>();

	tokens.increment(true);
	tokens.expect<parse::symbol>();

	tokens.increment(true);
	tokens.expect(".subckt");
	tokens.expect(".SUBCKT");

	if (tokens.decrement(__FILE__, __LINE__, data)) {
		tokens.next();
	}

	if (tokens.decrement(__FILE__, __LINE__, data)) {
		name = tokens.next();
	}

	while (tokens.decrement(__FILE__, __LINE__, data)) {
		ports.push_back(tokens.next());

		tokens.increment(false);
		tokens.expect<parse::symbol>();
		tokens.expect<parse::number>();
	}

	if (tokens.decrement(__FILE__, __LINE__, data)) {
		tokens.next();
	}

	tokens.increment(true);
	tokens.expect<parse::new_line>();

	tokens.increment(true);
	tokens.expect(".ends");
	tokens.expect(".ENDS");

	tokens.increment(false);
	tokens.expect<parse_spice::device>();

	while (tokens.decrement(__FILE__, __LINE__, data)) {
		devices.push_back(device(tokens, data));

		tokens.increment(false);
		tokens.expect<parse_spice::device>();
	}

	if (tokens.decrement(__FILE__, __LINE__, data)) {
		tokens.next();
	}

	if (tokens.decrement(__FILE__, __LINE__, data)) {
		tokens.next();
	}

	tokens.syntax_end(this);
}

bool subckt::is_next(tokenizer &tokens, int i, void *data) {
	return tokens.is_next(".subckt", i) || tokens.is_next(".SUBCKT", i);
}

void subckt::register_syntax(tokenizer &tokens) {
	if (!tokens.syntax_registered<subckt>())
	{
		tokens.register_syntax<subckt>();
		device::register_syntax(tokens);
		tokens.register_token<parse::symbol>();
		tokens.register_token<parse::number>();
		tokens.register_token<parse::white_space>(false);
		tokens.register_token<parse::new_line>();
	}
}

string subckt::to_string(string tab) const {
	string result = ".subckt " + name;

	for (int i = 0; i < (int)ports.size(); i++) {
		result += " " + ports[i];
	}

	result += "\n";
	for (int i = 0; i < (int)devices.size(); i++) {
		result += devices[i].to_string(tab);
	}
	result += ".ends\n";

	return result;
}

parse::syntax *subckt::clone() const {
	return new subckt(*this);
}

}
