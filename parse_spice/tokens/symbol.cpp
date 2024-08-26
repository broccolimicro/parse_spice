#include "symbol.h"

namespace parse_spice
{

symbol::symbol()
{
	debug_name = "symbol";
}

symbol::~symbol()
{

}

token symbol::consume(tokenizer &tokens, void *data)
{
	token result;
	result.type = tokens.token_type<symbol>();
	result.start = tokens.offset+1;

	string one(1, tokens.next_char());

	result.end = tokens.offset+1;
	return result;
}

bool symbol::is_next(tokenizer &tokens, int i, void *data)
{
	char character = tokens.peek_char(i);

	return (character == '=');
}

}
