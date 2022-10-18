#include "Lexer/Token.hpp"

namespace ESP {

// TODO(1.3): Преобразование токена в строку.
// По аналогии с выводом clang -dump-tokens формат может быть вида:
// id 'name' Loc=1:2

std::string_view token_kind_to_string(Token::Kind kind) {
    switch (kind) {
        case Token::Kind::ID:
            return "ID";

        case Token::Kind::SEMICOLON:
            return "SEMICOLON";

        case Token::Kind::COMMA:
            return "COMMA";

        case Token::Kind::TYPE:
            return "TYPE";

        case Token::Kind::kwLET:
            return "kwLET";

        case Token::Kind::kwFOR:
            return "kwFOR";

        case Token::Kind::kwLOOP:
            return "kwLOOP";

        case Token::Kind::kwWHILE:
            return "kwWHILE";

        case Token::Kind::kwRET:
            return "kwRET";

        case Token::Kind::kwUSE:
            return "kwUSE";

        case Token::Kind::kwFUNC:
            return "kwFUNC";

        case Token::Kind::kwSTRUCT:
            return "kwSTRUCT";

        case Token::Kind::kwTYPEDEF:
            return "kwTYPEDEF";

        case Token::Kind::LRB:
            return "LRB";

        case Token::Kind::RRB:
            return "RRB";

        case Token::Kind::LCB:
            return "LCB";

        case Token::Kind::RCB:
            return "RCB";

        case Token::Kind::LSB:
            return "LSB";

        case Token::Kind::RSB:
            return "RSB";

        case Token::Kind::GT:
            return "GT";

        case Token::Kind::GTE:
            return "GTE";

        case Token::Kind::LT:
            return "LT";

        case Token::Kind::LTE:
            return "LTE";

        case Token::Kind::EQ:
            return "EQ";

        case Token::Kind::NEQ:
            return "NEQ";

        case Token::Kind::ASSIGN:
            return "ASSIGN";

        case Token::Kind::PLUS:
            return "PLUS";

        case Token::Kind::MINUS:
            return "MINUS";

        case Token::Kind::DIV:
            return "DIV";

        case Token::Kind::MUL:
            return "MUL";

        case Token::Kind::ESP_EOF:
            return "EOF";

        case Token::Kind::NUMERIC:
            return "NUMERIC";

        case Token::Kind::DQUOTE:
            return "DQUOTE";

        case Token::Kind::SQUOTE:
            return "SQUOTE";

        case Token::Kind::ZERO:
            return "ZERO";

        default:
            return "UNKNOWN";
    }
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os
        << token_kind_to_string(token.kind()) << " '" << token.lexeme() << "' "
        << "Loc=" << token.location().row_ << ":" << token.location().col_;

    return os;
}

}  // namespace ESP