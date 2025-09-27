#include "node.h"

namespace parse_spice
{

node::node()
{
	debug_name = "spice_node";
}

node::~node()
{
}

token node::consume(tokenizer &tokens, void *data)
{
	token result;
	result.type = tokens.token_type<node>();
	result.start = tokens.offset+1;
	char character;
	do
	{
		tokens.next_char();
		character = tokens.peek_char(1);
	} while ((character >= 'A' && character <= 'Z') || character == '_' || character == '#' || (character >= 'a' && character <= 'z') || (character >= '0' && character <= '9'));
	result.end = tokens.offset+1;
	return result;
}

bool node::is_next(tokenizer &tokens, int i, void *data)
{
	char character = tokens.peek_char(i);

	return ((character >= 'A' && character <= 'Z') || character == '_' || character == '#' || (character >= 'a' && character <= 'z'));
}

}
