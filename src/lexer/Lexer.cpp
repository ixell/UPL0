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

#ifdef DEBUG
	while (true) {
#else
	for (int TIME = 10'000; TIME != 0; --TIME) {
#endif
		if (ch >= 0x80) {
			if (ch == 0xffff) {
				add(Token::eof);
				return;
			}
			tokenize_word();
			break;
		}
		TokenType token = char_to_token((char)ch);
		switch (token) {
		case Token::word:
			tokenize_word();
			break;
		case Token::number:
			tokenize_number();
			break;
		case Token::none:
			next();
			break;
		case Token::eof:
			add(Token::eof);
			this->tokens = nullptr;
			return;
		default:
			if (getSubgroup(token) == Token::endword) {
				if (token == Token::endline) {
					tokenize_tabs();
				}
				next();
				break;
			}
			switch (getGroup(token)) {
			case Token::operator_:
				tokenize_operator();
				break;
			case Token::parentheses:
				tokenize_parentheses();
				break;
			case Token::other:
				tokenize_other();
				break;
			}
		}
	}
}

void Lexer::tokenize_word() {
#ifdef DEBUG
	while (true) {
#else
	for (int TIME = 1'000; TIME != 0; --TIME) {
#endif
		if (
			ch >= 0x80 && ch != 0xffff			||
			'0' <= ch && ch <= '9'				||
			char_to_token(ch) == Token::word
		) {
			buffer.push_back(ch);
			next();
			continue;
		}
		break;
	}

	Token token(Token::variable, buffer);
	buffer.clear();
	typify_word(token);
	add(token);
}

static void parse_number(std::wstring* result, std::wstring input, int base);

void Lexer::tokenize_number() {
	TokenType type;
	if (buffer.empty()) type = Token::integer;
	else type = Token::float_;
	int base = 10;
	
#ifdef DEBUG
	while (true) {
#else
	for (int TIME = 1'000; TIME != 0; --TIME) {
#endif
		TokenType token = char_to_token(ch);
		if (base == 16 && ('a' <= ch && ch <= 'f' || 'A' <= ch && ch <= 'F')) {
			if ('A' <= ch && ch <= 'F')
				ch += ('a' - 'A');
			buffer.push_back(ch);
			next();
			continue;
		}
		if ('0' <= ch && ch <= '9') {
			if (ch > base + '0') {
				add(Token::error_unknown);
				buffer.clear();
				return;
			}
			buffer.push_back(ch);
			next();
			continue;
		}
		if (token == Token::quote) {
			next();
			continue;
		}
		if ((ch == 'x' || ch == 'X') && buffer.size() == 1 && buffer[0] == '0') {
			base = 16;
			buffer = L'x';
			next();
			continue;
		}
		if ((ch == 'b' || ch == 'B') && buffer.size() == 1 && buffer[0] == '0') {
			base = 2;
			buffer = L"b";
			next();
			continue;
		}
		if (token == TokenType::operator_dot) {
			if (base != 10) {
				tokens->emplace_back(Token::error_unknown);
				return;
			}
			type = Token::float_;
			buffer.push_back(ch);
			next();
			continue;
		}
		if (token != TokenType::word && token != TokenType::parentheses) {
			add(type, buffer);
			buffer.clear();
			return;
		}
		else {
			add(TokenType::error);
			buffer.clear();
			return;
		}
	}
	
	add(type, buffer);
	buffer.clear();
	next();
}

static void parse_number(std::wstring& result, std::wstring& input, int base) {
	int number, place = 0;
	for (auto i = input.crbegin(); i != input.crend(); i++) {
		wchar_t ch = *i;
		if ('0' <= ch && ch <= '9') {
			int n = ch - '0';
			if (n < base)
				number += n;
			else {
				result.clear();
				return;
			}
		}
		else if ('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z') {
			int n;
			if ('a' <= ch && ch <= 'z') 
				n = ch - 'a' + 16;
			else
				n = ch - 'A' + 16;
			if (n < base)
				number += n;
			else {
				result.clear();
				return;
			}
		}
		//...
	}
}

void Lexer::tokenize_operator() {
	TokenType type0 = char_to_token(ch),
			subgroup0 = getSubgroup(type0);
	next();
	TokenType type1 = char_to_token(ch),
			subgroup1 = getSubgroup(type1);
	if (subgroup0 == Token::operator_assignable) {
		TokenType type1 = char_to_token(ch);
		if (type1 == Token::operator_assign) {
			add(static_cast<TokenType>(Token::operator_assignment | (type0 & 0x00ffffff)));
			next();
			return;
		}
	}
	if (type0 == type1) {
		TokenType type;
		switch (type0) {
		case Token::operator_plus:
			type = Token::operator_increment;
			next();
			if (!tokens->empty() && tokens->crbegin()->get_type() == Token::operator_increment && ch == L'+') {
				add(Token::operator_plus);
				add(Token::operator_increment);
				next();
				return;
			}
			break;
		case Token::operator_minus:
			type = Token::operator_decrement;
			next();
			if (!tokens->empty() && tokens->crbegin()->get_type() == Token::operator_decrement && ch == L'-') {
				add(Token::operator_minus);
				add(Token::operator_decrement);
				next();
				return;
			}
			break;
		case Token::operator_binary_and:	type = Token::operator_and;	next();	break;
		case Token::operator_binary_or:		type = Token::operator_or;	next();	break;
		case Token::operator_greaterThan:
			type = Token::operator_binary_rightShift;
			next();
			if (ch == '=') {
				type = Token::operator_assign_binary_rightShift;
				next();
			}
			break;
		case Token::operator_lessThan:
			type = Token::operator_binary_leftShift;
			next();
			if (ch == '=') {
				type = Token::operator_assign_binary_leftShift;
				next();
			}
			break;
		case Token::operator_slash:
			tokenize_comment();
			return;
		default:
			add(type0);
			return;
		}
		add(type);
		return;
	}
	if (type0 == Token::operator_dot && type1 == Token::number) {
		buffer = L"0.";
		tokenize_number();
		return;
	}
	if (type0 == Token::operator_minus && type1 == Token::operator_greaterThan) {
		add(Token::operator_arrow);
		next();
		return;
	}
	add(type0);
}

void Lexer::tokenize_parentheses() {
	TokenType token = char_to_token(ch);
	if (token == Token::quote || token == Token::double_quotes) {
		tokenize_string();
		return;
	}
	add(token);
	next();
}

void Lexer::tokenize_string() {
	int char_size = 1;
	if (!(ch == '\'' || ch == '"'))
		return;
	wchar_t quote = ch;
	next();
	while (ch != quote) {
		switch (ch) {
			case '\\':
				next();
				switch (ch) {
					case '\\':
					case '"':
					case '\'':
						break;
					case 'n':
						ch = '\n';
						break;
					case 't':
						ch = '\t';
						break;
					case 'v':
						ch = '\v';
						break;
					case 'r':
						ch = '\r';
						break;
					case 'f':
						ch = '\f';
						break;
					case 'a':
						ch = '\a';
						break;
					case '0':
						ch = '\0';
						break;
					case 'x':
						add(Token::error_indev);
						break;
					default:
						if (char_to_token(ch) == Token::number) {
							add(Token::error_indev);
							break;
						}
						add(Token::error_unknown);
				}
				break;
			case 0xffff:
				add(Token::error_unknown);
				return;
		}
		buffer.push_back(ch);
		next();
	}
	add(Token::string, buffer);
	buffer.clear();
	next();
}

void Lexer::tokenize_other() {
	TokenType token = char_to_token(ch);
	switch (token) {
	case Token::sharp:
		add(Token::error_indev);
		next();
		return;
	case Token::at:
		add(Token::error_indev);
		next();
		return;
	case Token::backslash:
		next();
		next();
		return;
	default:
		add(token);
		next();
	}
}

void Lexer::tokenize_comment() {
	do next(); while (!(ch == ' ' || ch == 0xffff));
}

void Lexer::tokenize_tabs() {
	int spaces = 0;
	while (true) {
		switch (ch) {
		case ' ': ++spaces; break;
		case '\t': spaces += tab_size ? tab_size : 4; break;
		default: goto out;
		}
	}
	out:
	if (tab_size == 0) tab_size = spaces;
	int new_tabs = spaces / tab_size;
	if (tabs != new_tabs) {
		if (tabs > new_tabs)
			for (int i = tabs - new_tabs; i != 0; --i)
				add(Token::untab);
		else
			for (int i = new_tabs - tabs; i != 0; --i)
				add(Token::tab);
	}
	tabs = new_tabs;
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
