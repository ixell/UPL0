#include "Lexer.hpp"

Lexer::Lexer() {}

Lexer::Lexer(std::wistream* code)
	: code(code), ch(code->get()) {}

Lexer::~Lexer() = default;

void Lexer::open(std::wistream* code) {
	this->code = code;
    ch = code->get();
}

void Lexer::tokenize(std::vector<Token>* tokens) {
	this->tokens = tokens;
	TokenType token = char_to_token((char)(ch & 0xff));
	do {
		if (ch >= 0x80) {
			tokenize_word();
			break;
		}
		switch (token) {
		case Token::word:
			tokenize_word();
			break;
		case Token::number:
			tokenize_num();
			break;
		case Token::none:
			break;
		default:
			if (getSubgroup(token) == Token::endword) break;
			switch (getGroup(token)) {
			case Token::operator_:
				tokenize_operator();
				break;
			case Token::parentheses:
				tokenize_parentheses();
				break;
			}
		}
	} while (token != Token::eof);
}

void Lexer::tokenize_word() {
	wstring buffer;

	while (true) {
		if (
			'a' <= ch && ch <= 'z'	||
			'A' <= ch && ch <= 'Z'	||
			'0' <= ch && ch <= '9'	||
			ch == '_'				||
			ch >= 0x80
		) {
			buffer.push_back(ch);
			next();
			continue;
		}
		break;
	}

	Token token(Token::variable, buffer);
	typify_word(token);
	add(token);
}

void Lexer::tokenize_num() {
	TokenType type = Token::integer;
	int base = 10;

	std::wstring buffer;
	
	while (true) {
		TokenType token = char_to_token(ch);
		if (base == 16 && 'a' <= ch && ch <= 'f') {
			buffer.push_back(ch);
		}
		if ('0' <= ch && ch <= '9') {
			if (ch > base + '0') {
				tokens->emplace_back(Token::error);
				return;
			}
			buffer.push_back(ch);
			continue;
		}
		if (token == Token::quote) {
			next();
			continue;
		}
		if (ch == 'x' && buffer.size() == 1 && buffer[0] == '0') {
			base = 16;
			buffer.clear();
			buffer.push_back(ch);
			next();
			continue;
		}
		if (ch == 'b' && buffer.size() == 1 && buffer[0] == '0') {
			base = 2;
			buffer.clear();
			buffer.push_back(ch);
			next();
			continue;
		}
		if (token == TokenType::operator_dot) {
			if (base != 10) {
				tokens->emplace_back(Token::error);
				return;
			}
			type = Token::float_;
			buffer.push_back(ch);
			next();
			continue;
		}
		{
			TokenType subgroup = token && 0xff000000;
			if (subgroup == TokenType::endword || subgroup == TokenType::operator_ || subgroup == TokenType::parentheses)
				break;
			else {
				add(TokenType::error);
				return;
			}
		}
	}
	
	add(type, buffer);
	next();
}

void Lexer::tokenize_operator() {
	TokenType type0 = char_to_token(ch),
			subgroup0 = type0 & 0xff000000;
	next();
	TokenType type1 = char_to_token(ch),
			subgroup1 = type1 & 0xff000000;

	if (subgroup0 == Token::operator_assignable) {
		TokenType type1 = char_to_token(ch);
		if (type1 == Token::operator_assign) {
			add(Token::operator_assignment | (type0 & 0x00ffffff));
			next();
			return;
		}
		add(type0);
		return;
	}
	if (type0 == type1) {
		TokenType type;
		switch (type0) {
		case Token::operator_plus:				type = Token::operator_increment;	next();	break;
		case Token::operator_minus:				type = Token::operator_decrement;	next();	break;
		case Token::operator_binary_and:		type = Token::operator_and;			next();	break;
		case Token::operator_binary_or:			type = Token::operator_or;			next();	break;
		case Token::operator_greater_than:
			type = Token::operator_right_shift;
			next();
			if (ch == '=') {
				type = Token::operator_assign_right_shift;
				next();
			}
			break;
		case Token::operator_less_than:
			type = Token::operator_left_shift;
			next();
			if (ch == '=') {
				type = Token::operator_assign_left_shift;
				next();
			}
			break;
		default:
			add(Token::error);
			return;
		}
		add(type);
		return;
	}
	if (type0 == Token::operator_minus && type1 == Token::operator_greater_than) {
		add(Token::operator_arrow);
		next();
		return;
	}
	add(type0);
}

void Lexer::tokenize_parentheses() {
	TokenType token = char_to_token(ch);
	if (token == Token::quote || token == Token::double_quotes) {
		std::wstring buffer(L"");
		next();
		while (ch != '\'') {
			buffer.push_back(ch);
			next();
		}
		add(Token::string, buffer);
	}
}

void Lexer::typify_word(Token& token) {
	const wstring& word = token.get_value();
	for (size_t i = 0; i != word.size(); ++i) {
		if (word[i] >= 0x80)
			return;
	}

	if (word == L"if") 
		token.set_type(Token::keyword_if);
	else if (word == L"else")
		token.set_type(Token::keyword_else);
	else if (word == L"while")
		token.set_type(Token::keyword_while);
	else if (word == L"do")
		token.set_type(Token::keyword_do);
	else if (word == L"for")
		token.set_type(Token::keyword_for);
	else if (word == L"switch")
		token.set_type(Token::keyword_switch);
	else if (word == L"case")
		token.set_type(Token::keyword_case);
	else if (word == L"class")
		token.set_type(Token::keyword_class);
	else if (word == L"enum")
		token.set_type(Token::keyword_enum);
	else if (word == L"union")
		token.set_type(Token::keyword_union);
	else if (word == L"import")
		token.set_type(Token::keyword_import);
	else if (word == L"int")
		token.set_type(Token::keyword_int);
	else if (word == L"float")
		token.set_type(Token::keyword_float);
	else if (word == L"string")
		token.set_type(Token::keyword_string);
	else if (word == L"bool")
		token.set_type(Token::keyword_bool);
	else if (word == L"auto")
		token.set_type(Token::keyword_auto);
	else if (word == L"const")
		token.set_type(Token::keyword_const);
	else if (word == L"friend")
		token.set_type(Token::keyword_friend);
	else if (word == L"constexpr")
		token.set_type(Token::keyword_constexpr);
	else if (word == L"true")
		token.set_type(Token::keyword_true);
	else if (word == L"false")
		token.set_type(Token::keyword_false);
	else if (word == L"and")
		token.set_type(Token::operator_and);
	else if (word == L"or")
		token.set_type(Token::operator_or);
	else if (word == L"not")
		token.set_type(Token::operator_not);
	else return;

	token.set_value(L"");
}

void Lexer::next() {
	ch = code->get();
}

wchar_t Lexer::get() {
	return ch;
}

void Lexer::add(const Token& token) {
	tokens->push_back(token);
}

void Lexer::add(TokenType token) {
	tokens->emplace_back(token);
}

void Lexer::add(TokenType token, const std::wstring& value) {
	tokens->emplace_back(token, value);
}
