#include <Lexer/Lexer.hpp>
#include <cassert>
#include <cctype>
#include <iostream>
#include <typeinfo>

#include "Lexer/Token.hpp"

namespace ESP {

Token Lexer::get() {
    if (next_token_.has_value()) {
        const auto token = next_token_.value();
        next_token_.reset();
        return token;
    }

    skip_spaces();
    if (eof()) {
        return Token(Token::Kind::ESP_EOF, "EOF", cursor_);
    }

    const auto next_char = peek_char();

    switch (next_char) {
        case '0':
            get_char();
            if (peek_char() == '0') {
                // ERROR: UNRECOGNIZED TOKEN '00'
            } else {
                return Token(Token::Kind::ZERO, "0", cursor_);
            }
            break;

        case ',':
            get_char();
            return Token(Token::Kind::COMMA, ",", cursor_);

        case ';':
            get_char();
            return Token(Token::Kind::SEMICOLON, ";", cursor_);

        case '(':
            get_char();
            return Token(Token::Kind::LRB, "(", cursor_);

        case ')':
            get_char();
            return Token(Token::Kind::RRB, ")", cursor_);

        case '[':
            get_char();
            return Token(Token::Kind::LSB, "[", cursor_);

        case ']':
            get_char();
            return Token(Token::Kind::RSB, "]", cursor_);

        case '{':
            get_char();
            return Token(Token::Kind::RCB, "{", cursor_);

        case '}':
            get_char();
            return Token(Token::Kind::LCB, "}", cursor_);

        case '>':
            get_char();
            if (peek_char() == '=') {
                return Token(Token::Kind::GTE, ">=", cursor_);
            }
            return Token(Token::Kind::GT, ">", cursor_);

        case '<':
            get_char();
            if (peek_char() == '=') {
                return Token(Token::Kind::LTE, "<=", cursor_);
            }
            return Token(Token::Kind::LT, "<", cursor_);

        case '*':
            get_char();
            return Token(Token::Kind::MUL, "*", cursor_);

        case '+':
            get_char();
            return Token(Token::Kind::PLUS, "+", cursor_);

        case '-':
            get_char();
            return Token(Token::Kind::MINUS, "-", cursor_);

        case '/':
            get_char();
            return Token(Token::Kind::DIV, "/", cursor_);

        case '!':
            get_char();
            if (peek_char() == '=') {
                return Token(Token::Kind::NEQ, "!=", cursor_);
            }
            return Token(Token::Kind::UNKNOWN, "UNKNOWN", cursor_);

        case '=':
            get_char();
            if (peek_char() == '=') {
                return Token(Token::Kind::EQ, "==", cursor_);
            }
            return Token(Token::Kind::ASSIGN, "=", cursor_);

        case '\'':
            get_char();
            return Token(Token::Kind::SQUOTE, "'", cursor_);

        case '\"':
            get_char();
            return Token(Token::Kind::DQUOTE, "\"", cursor_);

        default:
            if (isdigit(next_char)) {
                return get_numeric_token();
            }
            if (isalpha(next_char)) {
                return get_string_token();
            }
            break;
    }
    return Token(Token::Kind::UNKNOWN, "UNKNOWN", cursor_);
}

Token Lexer::peek() {
    if (next_token_.has_value()) {
        return next_token_.value();
    }
    next_token_ = get();
    return next_token_.value();
}

char Lexer::peek_char() const {
    assert(!eof());
    return input_[cursor_.offset_];
}

char Lexer::get_char() {
    char const current = peek_char();

    cursor_.offset_++;

    if (current == '\n') {
        cursor_.row_++;
        cursor_.col_ = 0;

    } else {
        cursor_.col_++;
    }

    return current;
}

void Lexer::skip_spaces() {
    while (isspace(peek_char()) != 0) {
        get_char();
    }
}

bool Lexer::eof() const {
    return input_.size() == cursor_.offset_;
}

Token Lexer::get_numeric_token() {
    const auto begin = cursor_;

    while (!eof() && (std::isdigit(peek_char()) != 0 || peek_char() == '.')) {
        get_char();
    }

    const auto end = cursor_;
    const auto text = input_.substr(
        begin.offset_,
        end.offset_ - begin.offset_);

    for (size_t i = 0; i < text.size(); i++) {
        if (text[i] == '.') {
            return Token(Token::Kind::REAL, text, begin);
        }
    }

    return Token(Token::Kind::NUMERIC, text, begin);
}

Token Lexer::get_string_token() {
    const auto begin = cursor_;

    while (!eof() && std::isalnum(peek_char()) != 0) {
        get_char();
    }

    const auto end = cursor_;
    const auto text = input_.substr(
        begin.offset_,
        end.offset_ - begin.offset_);

    if (text == "let") {
        return Token(Token::Kind::kwLET, text, begin);
    }

    if (text == "for") {
        return Token(Token::Kind::kwFOR, text, begin);
    }

    if (text == "loop") {
        return Token(Token::Kind::kwLOOP, text, begin);
    }

    if (text == "func") {
        return Token(Token::Kind::kwFUNC, text, begin);
    }

    if (text == "use") {
        return Token(Token::Kind::kwUSE, text, begin);
    }

    if (text == "ret") {
        return Token(Token::Kind::kwRET, text, begin);
    }

    if (text == "while") {
        return Token(Token::Kind::kwWHILE, text, begin);
    }

    if (text == "struct") {
        return Token(Token::Kind::kwSTRUCT, text, begin);
    }

    if (text == "typedef") {
        return Token(Token::Kind::kwTYPEDEF, text, begin);
    }

    if (text == "int" || text == "double" || text == "float" || text == "char" || text == "bool") {
        return Token(Token::Kind::TYPE, text, begin);
    }

    return Token(Token::Kind::ID, text, begin);
}

std::vector<Token> Lexer::dump_tokens() {
    std::vector<Token> result;
    while (!eof()) {
        Token token = get();
        result.push_back(token);
        // Если хотите посмотреть на вывод, то вам сюда
        // std::cout << token << '\n';
    }
    return result;
}

}  // namespace ESP
