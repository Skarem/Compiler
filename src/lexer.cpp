#include "../inc/lexer.hpp"

#include <fstream>
#include <iostream>

#include <algorithm>
#include <unordered_map>

Lexer::Lexer() {}

Lexer::~Lexer() {}

bool Lexer::IsIdentifierChar(char c) { return std::isalpha(c) || c == '_'; }

bool Lexer::IsIdentifierNum(char c) { return std::isdigit(c); }

int Lexer::TokenizeFile(const std::string& filename,
                        std::vector<std::unique_ptr<TOKEN>>& tokens)
{
    // std::cout << "Trying to open and read: " << filename << std::endl;

    std::ifstream file(filename);
    if (!file.is_open())
    {
        perror(("Error while opening file " + filename).c_str());
    }

    bool comment = false;
    std::string line;
    int row = 1;
    while (getline(file, line))
    {
        if (TokenizeLine(line, tokens, comment, row++) > 0)
        {
            return 1;
        }
    }

    if (comment)
    {
        std::cerr << "Unterminated multi-line comment" << std::endl;
        return 1;
    }

    if (file.bad())
    {
        perror(("Error while reading file " + filename).c_str());
    }

    file.close();

    DisplayTokens(tokens);

    // std::cout << "Lex successful!" << std::endl;

    return 0;
}

void Lexer::DisplayTokens(std::vector<std::unique_ptr<TOKEN>>& tokens)
{
    for (const auto& token : tokens)
    {
        switch (token->type)
        {
            case TOKEN_TYPE::IDENTIFIER:
            {
                auto* identifierToken =
                    static_cast<TOKEN_IDENTIFIER*>(token.get());
                std::cout << TOKEN_TYPE_STRING_MAP.at(identifierToken->type)
                          << " : " << identifierToken->identifier << std::endl;
                break;
            }
            case TOKEN_TYPE::KEYWORD:
            {
                auto* keywordToken = static_cast<TOKEN_KEYWORD*>(token.get());
                std::cout << TOKEN_TYPE_STRING_MAP.at(keywordToken->type)
                          << " : "
                          << KEYWORD_TYPE_STRING_MAP.at(keywordToken->keyword)
                          << std::endl;
                break;
            }
            case TOKEN_TYPE::CONSTANT:
            {
                auto* constantToken = static_cast<TOKEN_CONSTANT*>(token.get());
                std::cout << TOKEN_TYPE_STRING_MAP.at(constantToken->type)
                          << " : " << constantToken->constant << std::endl;
                break;
            }
            default:
            {
                std::cout << TOKEN_TYPE_STRING_MAP.at(token->type) << std::endl;
                break;
            }
        }
    }
}

int Lexer::TokenizeLine(std::string& line,
                        std::vector<std::unique_ptr<TOKEN>>& tokens,
                        bool& comment, int row)
{
    size_t start = 0;

    while (start < line.length())
    {
        char current = line[start];

        // Skip single-line comment
        if (!comment && line.length() - start >= 2 &&
            line.substr(start, 2) == "//")
        {
            // std::cout << "Skipping comment line" << std::endl;
            return 0;
        }
        // Skip whitespace
        else if (!comment && std::isspace(current))
        {
            ++start;
            continue;
        }
        else if (!comment && IsIdentifierChar(current))
        {
            size_t end = start;

            while (end < line.length() &&
                   (IsIdentifierChar(line[end]) || IsIdentifierNum(line[end])))
            {
                ++end;
            }

            std::string identifier = line.substr(start, end - start);

            if (auto keyword = KEYWORD_TYPE_MAP.find(identifier);
                keyword != KEYWORD_TYPE_MAP.end())
            {
                // std::cout << "KEYWORD: " << identifier << std::endl;
                tokens.push_back(std::make_unique<TOKEN_KEYWORD>(
                    TOKEN_TYPE::KEYWORD, keyword->second));
            }
            else
            {
                // std::cout << "IDENTIFIER: " << identifier << std::endl;
                tokens.push_back(std::make_unique<TOKEN_IDENTIFIER>(
                    TOKEN_TYPE::IDENTIFIER, identifier));
            }

            start = end;
        }
        // If it starts with a number
        else if (!comment && IsIdentifierNum(current))
        {
            size_t end = start;

            while (end < line.length() && IsIdentifierNum(line[end]))
            {
                ++end;
            }

            // If a char is found directly after a num, it is invalid
            if (end < line.length() && IsIdentifierChar(line[end]))
            {
                std::cerr << "Invalid token error: constant does not end with "
                             "boundary token"
                          << std::endl;
                return 1;
            }

            std::string constant = line.substr(start, end - start);
            // std::cout << "CONSTANT: " << constant << std::endl;
            tokens.push_back(std::make_unique<TOKEN_CONSTANT>(
                TOKEN_TYPE::CONSTANT, std::stoi(constant)));

            start = end;
        }
        else
        {
            // Check for multi-line comments
            if (line.length() - start >= 2 && line.substr(start, 2) == "/*")
            {
                // std::cout << "Start multi-line comment" << std::endl;
                comment = true;
                ++start;
            }
            else if (line.length() - start >= 2 &&
                     line.substr(start, 2) == "*/")
            {
                // std::cout << "End multi-line comment" << std::endl;
                comment = false;
                ++start;
            }
            else if (!comment)
            {
                // Check for singular tokens
                if (auto token = TOKEN_TYPE_MAP.find(line[start]);
                    token != TOKEN_TYPE_MAP.end())
                {
                    // std::cout << "TOKEN: " << token->first << std::endl;
                    tokens.push_back(std::make_unique<TOKEN>(token->second));
                }
                // Invalid token
                else
                {
                    std::cerr << "Invalid token error (row: " << row
                              << ", col: " << start << "): \'" << line[start]
                              << "\' is not a token" << std::endl;
                    return 1;
                }
            }

            ++start;
        }
    }
    return 0;
}