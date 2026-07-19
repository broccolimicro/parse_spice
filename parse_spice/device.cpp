#include "device.h"
#include "tokens/line_comment.h"

#include "tokens/node.h"
#include "tokens/number.h"
#include <parse/default/white_space.h>
#include <parse/default/new_line.h>

namespace parse_spice {

device::device() {
	debug_name = "spice_device";
}

device::device(tokenizer &tokens, std::any data) {
	debug_name = "spice_device";
	parse(tokens, data);
}

device::~device() {

}

void device::parse(tokenizer &tokens, std::any data) {
	tokens.syntax_start(this);

	tokens.increment(true);
	tokens.expect<parse::new_line>();
	tokens.expect<parse_spice::line_comment>();

	tokens.increment(true);
	tokens.expect<node>();

	tokens.increment(true);
	tokens.expect<node>();

	if (tokens.decrement(__FILE__, __LINE__)) {
		name = lower(tokens.next());
	}

	if (tokens.decrement(__FILE__, __LINE__)) {
		ports.push_back(lower(tokens.next()));
	}

	while (tokens.is_next<node>() and not parameter::is_next(tokens, 1, data)) {
		ports.push_back(lower(tokens.next()));
	}
	if (not ports.empty()) {
		type = ports.back();
		ports.pop_back();
	}

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

	if (tokens.decrement(__FILE__, __LINE__)) {
		if (tokens.found<parse_spice::line_comment>()) {
			atend = string_from_comment(tokens.next());
		} else {
			tokens.next();
		}
	}

	tokens.syntax_end(this);
}

bool device::is_next(tokenizer &tokens, int i, std::any data) {
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
		tokens.register_token<line_comment>();
		tokens.register_token<parse::new_line>();
	}
}

string device::to_string(string tab) const {
	string result;
	for (std::string s : header) {
		result += comment_string(s) + "\n";
	}

	result += name;
	for (int i = 0; i < (int)ports.size(); i++) {
		result += " " + ports[i];
	}
	result += " " + type;

	for (int i = 0; i < (int)params.size(); i++) {
		result += " " + params[i].to_string(tab);
	}

	if (not atend.empty()) {
		result += comment_string(atend);
	}

	result += "\n";

	return result;
}

parse::syntax *device::clone() const {
	return new device(*this);
}

}
