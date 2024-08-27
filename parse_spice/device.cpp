#include "device.h"
#include "tokens/line_comment.h"

#include "tokens/node.h"
#include "tokens/number.h"
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

	tokens.increment(true);
	tokens.expect<node>();

	if (tokens.decrement(__FILE__, __LINE__, data)) {
		name = lower(tokens.next());
	}

	while (tokens.is_next<node>() and not parameter::is_next(tokens, 1, data)) {
		ports.push_back(lower(tokens.next()));
	}
	type = ports.back();
	ports.pop_back();

	while (true) {
		if (parameter::is_next(tokens, 1, data)) {
			params.push_back(parameter(tokens, data));
		} else if (tokens.is_next<number>()) {
			params.push_back(parameter());
			params.back().value = lower(tokens.next());
		} else {
			break;
		}
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
		tokens.register_token<node>();
		tokens.register_token<number>();
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
