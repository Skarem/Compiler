#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

#include "../inc/lexer.hpp"

void Preprocess(const std::string& input_file,
                const std::string& preprocessed_file)
{
    std::string command =
        "gcc -E -P " + input_file + " -o " + preprocessed_file;
    std::cout << "Command : " << command << std::endl;

    int ret_code = std::system(command.c_str());
    if (ret_code != 0)
    {
        std::cerr << "Error during preprocessing" << std::endl;
        exit(ret_code);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ./compiler_driver [--lex | --parse | --codegen | "
                     "-S] <input_file>"
                  << std::endl;
        return 1;
    }

    // Parse command-line arguments
    std::string option;
    std::string input_file;
    if (argc == 3)
    {
        option = argv[1];
        input_file = argv[2];
    }
    else
    {
        input_file = argv[1];
    }

    if (!std::filesystem::exists(input_file))
    {
        std::cerr << "Error: File not found: " << input_file << std::endl;
        return 1;
    }

    if (!option.empty())
    {
        if (option != "--lex" && option != "--parse" && option != "--codegen")
        {
            std::cerr << "Error: Option not supported: " << option << std::endl;
            return 1;
        }
    }

    // Get file paths and names
    std::filesystem::path input_path(input_file);
    std::string base_name = input_path.stem().string();
    std::string output_path = input_path.parent_path() / base_name;

    // std::cout << "input_path  : " << input_path << std::endl;
    // std::cout << "base_name         : " << base_name << std::endl;
    // std::cout << "output_path       : " << output_path << std::endl;

    std::string preprocessed_file = base_name + ".i";
    std::string assembly_file = base_name + ".s";

    // std::cout << "preprocessed_file : " << preprocessed_file << std::endl;
    // std::cout << "assembly_file     : " << assembly_file << std::endl;

    // Handle options (--lex, --parse, --codegen)
    if (option == "--lex")
    {
        std::vector<std::unique_ptr<TOKEN>> tokens;
        Lexer lexer;
        int ret_code = lexer.TokenizeFile(input_file, tokens);
        if (ret_code != 0)
        {
            std::cerr << "Error while lexing code: " << ret_code << std::endl;
            return 1;
        }
        return 0;
    }
    if (option == "--parse")
    {
        std::cout << "Parser not yet implemented" << std::endl;
        return 0;
    }
    if (option == "--codegen")
    {
        std::cout << "Code generation not yet implemented" << std::endl;
        return 0;
    }

    return 0;
}