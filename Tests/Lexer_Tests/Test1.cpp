#include <cassert>
#include <iostream>

#include "Lexer/Lexer.hpp"

void TEST1() {
    const char* input = "int i = 0;\n   float double char bool 12 12.4 hello \' \" {}[]()";
    ESP::Location loc;
    ESP::Lexer lex(input, loc);
    std::vector<ESP::Token> result = lex.dump_tokens();
    for (auto& token : result) {
        if (token.kind() == ESP::Token::Kind::TYPE)
            assert(token.lexeme() == "int" || token.lexeme() == "double" || token.lexeme() == "float" || token.lexeme() == "char" || token.lexeme() == "bool");
        if (token.lexeme() == "int" || token.lexeme() == "double" || token.lexeme() == "float" || token.lexeme() == "char" || token.lexeme() == "bool") {
            assert(token.kind() == ESP::Token::Kind::TYPE);
        }
        if (token.lexeme() == "i") {
            assert(token.kind() == ESP::Token::Kind::ID);
        }
        if (token.lexeme() == "=") {
            assert(token.kind() == ESP::Token::Kind::ASSIGN);
        }
        if (token.lexeme() == "0") {
            assert(token.kind() == ESP::Token::Kind::ZERO);
        }
        if (token.lexeme() == ";") {
            assert(token.kind() == ESP::Token::Kind::SEMICOLON);
            assert(token.location().row_ == 0);
        }
        if (token.lexeme() == "12") {
            assert(token.kind() == ESP::Token::Kind::NUMERIC);
            assert(token.location().row_ == 1);
        }
        if (token.lexeme() == "12.4") {
            assert(token.kind() == ESP::Token::Kind::REAL);
        }
        if (token.lexeme() == "hello") {
            assert(token.kind() == ESP::Token::Kind::ID);
        }
        if (token.lexeme() == "\'") {
            assert(token.kind() == ESP::Token::Kind::SQUOTE);
        }
        if (token.lexeme() == "\"") {
            assert(token.kind() == ESP::Token::Kind::DQUOTE);
        }
        if (token.lexeme() == "[") {
            assert(token.kind() == ESP::Token::Kind::LSB);
        }
        if (token.lexeme() == "]") {
            assert(token.kind() == ESP::Token::Kind::RSB);
        }
        if (token.lexeme() == "{") {
            assert(token.kind() == ESP::Token::Kind::RCB);
        }
        if (token.lexeme() == "}") {
            assert(token.kind() == ESP::Token::Kind::LCB);
        }
        if (token.lexeme() == "(") {
            assert(token.kind() == ESP::Token::Kind::LRB);
        }
        if (token.lexeme() == ")") {
            assert(token.kind() == ESP::Token::Kind::RRB);
        }
    }
    std::cout << "\033[92m";
    std::cout << "TEST1 ✔ ✔ ✔\n";
    std::cout << "\033[39m";
}

int main() {
    TEST1();
    return 0;
}