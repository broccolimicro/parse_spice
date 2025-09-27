#include "command.h"

namespace parse_spice {

command::command()
{
	debug_name = "spice_command";
}

command::~command()
{

}

token command::consume(tokenizer &tokens, void *data)
{
	token result;
	result.type = tokens.token_type<command>();
	result.start = tokens.offset+1;

	tokens.next_char();

	char character;

	do {
		character = tokens.next_char();
	} while ((character >= 'A' and character <= 'Z') or (character >= 'a' and character <= 'z'));

	result.end = tokens.offset;
	return result;
}

bool command::is_next(tokenizer &tokens, int i, void *data)
{
	return tokens.peek_char(i) == '.';
}

}
