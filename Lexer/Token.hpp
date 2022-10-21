#pragma once

#include <ostream>
#include <string_view>

#include "Lexer/Location.hpp"

namespace ESP {

class Token {
   public:
    enum class Kind {
        COMMA,
        SEMICOLON,
        ID,
        TYPE,
        kwLET,
        kwFOR,
        kwLOOP,
        kwWHILE,
        kwRET,
        kwUSE,
        kwFUNC,
        kwSTRUCT,
        kwTYPEDEF,
        LRB,      // '('
        RRB,      // ')'
        LCB,      // '{'
        RCB,      // '}'
        LSB,      // '['
        RSB,      // ']'
        GT,       // '>'
        GTE,      // '>='
        LT,       // '<'
        LTE,      // '<='
        EQ,       // '=='
        NEQ,      // '!='
        ASSIGN,   // '='
        PLUS,     // '+'
        MINUS,    // '-'
        DIV,      // '*'
        MUL,      // '/'
        ESP_EOF,  // EOF занято, поэтому с префиксом
        NUMERIC,  // Какой-то числовой литерал
        REAL,     // Числовой литерал с плавающей точкой
        DQUOTE,   // '"'
        SQUOTE,   // '\''
        ZERO,     // '0'
        UNKNOWN,
    };

    // Конструктор по умолчанию отсутствует, поскольку странно было бы иметь "пустой" токен
    Token(Kind kind, std::string_view lexeme, Location loc) : kind_(kind), lexeme_(lexeme), cursor_(loc) {}

    Kind kind() const { return kind_; }
    std::string_view lexeme() const { return lexeme_; }
    Location location() const { return cursor_; }

   private:
    Kind kind_;
    std::string_view lexeme_;  // Лексема - то, как фактически выглядит токен.
                               // Пример: 'int' - это лексема, разновидность(kind) которой 'TYPE'
    Location cursor_;
};

std::string_view token_kind_to_string(Token::Kind kind);
std::ostream& operator<<(std::ostream& os, const Token& token);

}  // namespace ESP