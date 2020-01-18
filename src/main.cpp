#include "Evaluator.hpp"
#include "Parser.hpp"
#include <boost/filesystem.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "usage: pl0 FILE\n";
        return 1;
    }

    try {
        std::string input;
        boost::filesystem::load_string_file(argv[1], input);
        auto program = PL0::Parser{input, std::cerr}();
        if (!program) return 1;
        PL0::Evaluator evaluator{std::cin, std::cout};
        program->accept(evaluator);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
