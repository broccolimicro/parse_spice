#include "line_comment.h"

namespace parse_spice {

line_comment::line_comment()
{
	debug_name = "line_comment";
}

line_comment::~line_comment()
{

}

token line_comment::consume(tokenizer &tokens, void *data)
{
	token result;
	result.type = tokens.token_type<line_comment>();
	result.start = tokens.offset+1;

	tokens.next_char();

	char character;

	do {
		character = tokens.next_char();
	} while (character != '\0' and character != '\n' and character != '\r');

	result.end = tokens.offset;
	return result;
}

bool line_comment::is_next(tokenizer &tokens, int i, void *data)
{
	return tokens.peek_char(i) == '*';
}

}
