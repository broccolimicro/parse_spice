/*
 * parameter.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: nbingham
 */

#include "parameter.h"
#include "tokens/node.h"
#include "tokens/number.h"
#include <parse/default/white_space.h>
#include <parse/default/new_line.h>
#include <common/text.h>

#include "tokens/symbol.h"

namespace parse_spice {

parameter::parameter() {
	debug_name = "spice_parameter";
}

parameter::parameter(string name, string value) {
	debug_name = "spice_parameter";
	this->name = name;
	this->value = value;
}

parameter::parameter(tokenizer &tokens, void *data) {
	debug_name = "spice_parameter";
	parse(tokens, data);
}

parameter::~parameter() {

}

void parameter::parse(tokenizer &tokens, void *data) {
	tokens.syntax_start(this);

	tokens.increment(true);
	tokens.expect<node>();
	tokens.expect<number>();

	tokens.increment(true);
	tokens.expect("=");

	tokens.increment(true);
	tokens.expect<node>();

	if (tokens.decrement(__FILE__, __LINE__, data)) {
		name = lower(tokens.next());
	}

	if (tokens.decrement(__FILE__, __LINE__, data)) {
		tokens.next();
	}

	if (tokens.decrement(__FILE__, __LINE__, data)) {
		value = lower(tokens.next());
	}
	
	tokens.syntax_end(this);
}

bool parameter::is_next(tokenizer &tokens, int i, void *data) {
	return tokens.is_next("=", i+1);
}

void parameter::register_syntax(tokenizer &tokens) {
	if (!tokens.syntax_registered<parameter>())
	{
		tokens.register_syntax<parameter>();
		tokens.register_token<node>();
		tokens.register_token<number>();
		tokens.register_token<symbol>();
		tokens.register_token<parse::white_space>(false);
		tokens.register_token<parse::new_line>();
	}
}

string parameter::to_string(string tab) const {
	return name + "=" + value;
}

parse::syntax *parameter::clone() const {
	return new parameter(*this);
}

}
