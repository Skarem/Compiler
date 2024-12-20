#ifndef LEXER_HPP
#define LEXER_HPP

#include "../inc/tokens.hpp"

#include <memory>
#include <vector>

class Lexer
{
public:
    Lexer();
    ~Lexer();

    int TokenizeFile(const std::string& filename,
                     std::vector<std::unique_ptr<TOKEN>>& tokens);

private:
    bool IsIdentifierChar(char c);
    bool IsIdentifierNum(char c);

    void DisplayTokens(std::vector<std::unique_ptr<TOKEN>>& tokens);

    int TokenizeLine(std::string& line,
                     std::vector<std::unique_ptr<TOKEN>>& tokens, bool& comment,
                     int row);
};

#endif