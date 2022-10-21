#pragma once

#include <optional>
#include <string_view>
#include <vector>

#include "Lexer/Token.hpp"
#include "Location.hpp"

namespace ESP {

class Lexer {
   public:
    Lexer(std::string_view input, Location loc) : input_(input), cursor_(loc) {}

    Token get();
    Token peek();
    std::vector<Token> dump_tokens();

   private:
    bool eof() const;

    char peek_char() const;
    char get_char();
    void skip_spaces();
    Token get_string_token();
    Token get_numeric_token();

    std::string_view input_;
    Location cursor_;
    std::optional<Token> next_token_;
};

}  // namespace ESP