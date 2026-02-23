#include "eos.h"
#include "System/IO/eosTokenizer.h"


namespace eos;


Tokenizer::Result Tokenizer::parse(
	uint8_t u) {
		
	_type = Type::none;
	
	Result result = Result::pending;
	
	switch (_state) {
		case 0:
			if (isSpace(u)) {
			}
			else if (isEOF(u))
				result = Result::error;
			else if (isDigit(u) {
				_token[0] = u;
				_tokenLen = 1;
				_state = 10;
			}
			else if (isLeter(u) {
				_token[0] = u;
				_tokenLen = 1;
				_state = 20;
			}
			else if ((u == '\'') || (u = "\""))
				_state = 30;
			break;
			
		case 10:
			if (isDigit(u) {
				_token[_tokenLen++] = u;
			}
			else {
				if (isSeparator(u) || isSpace(u) || isEOF(u)) {
					_type = TokenType::integer;
					_state = 0;
					result = Result::success;
				}
				else {
					_state = 0;
					result = Result::error;
				}
			}
			break;
			
		case 20:
			break;
			
		case 30:
			break;
	}
	
	return result;
}