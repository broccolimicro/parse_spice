#include "device.h"
#include "line_comment.h"

#include <parse/default/symbol.h>
#include <parse/default/number.h>
#include <parse/default/white_space.h>
#include <parse/default/new_line.h>

namespace parse_spice {

device::device() {
	debug_name = "device";
}

device::device(tokenizer &tokens, void *data) {
	debug_name = "device";
	parse(tokens, data);
}

device::~device() {

}

void device::parse(tokenizer &tokens, void *data) {
	tokens.syntax_start(this);

	tokens.increment(true);
	tokens.expect<parse::new_line>();

	tokens.increment(false);
	tokens.expect<parameter>();

	tokens.increment(true);
	tokens.expect<parse::symbol>();

	tokens.increment(true);
	tokens.expect<parse::symbol>();

	if (tokens.decrement(__FILE__, __LINE__, data)) {
		name = tokens.next();
	}

	while (tokens.decrement(__FILE__, __LINE__, data)) {
		ports.push_back(tokens.next());

		tokens.increment(false);
		tokens.expect<parse::symbol>();
	}
	type = ports.back();
	ports.pop_back();

	while (tokens.decrement(__FILE__, __LINE__, data)) {
		params.push_back(parameter(tokens, data));

		tokens.increment(false);
		tokens.expect<parameter>();
	}

	if (tokens.decrement(__FILE__, __LINE__, data)) {
		tokens.next();
	}

	tokens.syntax_end(this);
}

bool device::is_next(tokenizer &tokens, int i, void *data) {
	string next = tokens.peek(i);
	return (next.size() > 1 and string("rRcClLdDqQjJmMxXfFhHeEgGkKvViI").find(next[0]) != string::npos);
}

void device::register_syntax(tokenizer &tokens) {
	if (!tokens.syntax_registered<device>())
	{
		tokens.register_syntax<device>();
		parameter::register_syntax(tokens);
		tokens.register_token<parse::symbol>();
		tokens.register_token<parse::number>();
		tokens.register_token<parse::white_space>(false);
		tokens.register_token<line_comment>(false);
		tokens.register_token<parse::new_line>();
	}
}

string device::to_string(string tab) const {
	string result = name;

	for (int i = 0; i < (int)ports.size(); i++) {
		result += " " + ports[i];
	}
	result += " " + type;

	for (int i = 0; i < (int)params.size(); i++) {
		result += " " + params[i].to_string(tab);
	}

	result += "\n";

	return result;
}

parse::syntax *device::clone() const {
	return new device(*this);
}

}
