#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>
#include <unordered_map>

// Basic token type
enum class TOKEN_TYPE
{
    IDENTIFIER,
    CONSTANT,
    KEYWORD,

    PARENTHESIS_OPEN,
    PARENTHESIS_CLOSE,

    BRACE_OPEN,
    BRACE_CLOSE,

    SEMICOLON,
};

// Specific keyword type
enum class KEYWORD_TYPE
{
    VOID,
    INT,
    RETURN,
};

// String to token type map
const std::unordered_map<char, TOKEN_TYPE> TOKEN_TYPE_MAP = {
    {'(', TOKEN_TYPE::PARENTHESIS_OPEN },
    {')', TOKEN_TYPE::PARENTHESIS_CLOSE},
    {'{', TOKEN_TYPE::BRACE_OPEN       },
    {'}', TOKEN_TYPE::BRACE_CLOSE      },
    {';', TOKEN_TYPE::SEMICOLON        },
};

// String to keyword type map
const std::unordered_map<std::string, KEYWORD_TYPE> KEYWORD_TYPE_MAP = {
    {"void",   KEYWORD_TYPE::VOID  },
    {"int",    KEYWORD_TYPE::INT   },
    {"return", KEYWORD_TYPE::RETURN},
};

// Base token struct
struct TOKEN
{
    TOKEN_TYPE type;

    TOKEN(TOKEN_TYPE tokenType) : type(tokenType) {}
    virtual ~TOKEN() = default; // Virtual destructor for polymorphism
};

// Token identifier struct
struct TOKEN_IDENTIFIER : TOKEN
{
    std::string identifier;

    TOKEN_IDENTIFIER(TOKEN_TYPE tokenType, std::string tokenIdentifier)
        : TOKEN(tokenType), identifier(tokenIdentifier)
    {
    }
};

// Token keyword struct
struct TOKEN_KEYWORD : TOKEN
{
    KEYWORD_TYPE keyword;

    TOKEN_KEYWORD(TOKEN_TYPE tokenType, KEYWORD_TYPE tokenKeyword)
        : TOKEN(tokenType), keyword(tokenKeyword)
    {
    }
};

// Token constant struct
struct TOKEN_CONSTANT : TOKEN
{
    int constant;

    TOKEN_CONSTANT(TOKEN_TYPE tokenType, int tokenConstant)
        : TOKEN(tokenType), constant(tokenConstant)
    {
    }
};

// Map to print token types
const std::unordered_map<TOKEN_TYPE, std::string> TOKEN_TYPE_STRING_MAP = {
    {TOKEN_TYPE::IDENTIFIER,        "IDENTIFIER"       },
    {TOKEN_TYPE::CONSTANT,          "CONSTANT"         },
    {TOKEN_TYPE::KEYWORD,           "KEYWORD"          },
    {TOKEN_TYPE::PARENTHESIS_OPEN,  "PARENTHESIS_OPEN" },
    {TOKEN_TYPE::PARENTHESIS_CLOSE, "PARENTHESIS_CLOSE"},
    {TOKEN_TYPE::BRACE_OPEN,        "BRACE_OPEN"       },
    {TOKEN_TYPE::BRACE_CLOSE,       "BRACE_CLOSE"      },
    {TOKEN_TYPE::SEMICOLON,         "SEMICOLON"        },
};

// Map to print keyword types
const std::unordered_map<KEYWORD_TYPE, std::string> KEYWORD_TYPE_STRING_MAP = {
    {KEYWORD_TYPE::VOID,   "VOID"  },
    {KEYWORD_TYPE::INT,    "INT"   },
    {KEYWORD_TYPE::RETURN, "RETURN"},
};

#endif