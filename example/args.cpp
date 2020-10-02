#include <args.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    args::ArgumentParser parser("This is a test program.", "usage:\n./bin -a -i 3 -c x -c y foo 1 2");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});

    args::Flag a_flag(parser, "aa", "The a flag", {'a', "aaa"});
    args::ValueFlag<int> integer(parser, "integer", "The integer flag", {'i'});
    args::ValueFlagList<char> characters(parser, "characters", "The character flag", {'c'});
    args::Positional<std::string> foo(parser, "foo", "The foo position");
    args::PositionalList<double> numbers(parser, "numbers", "The numbers position list");
    try {
        parser.ParseCLI(argc, argv);
    } catch (const args::Help&) {
        std::cout << parser;
        return 0;
    } catch (const args::ParseError& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    if (a_flag) {
        std::cout << "a_flag set" << std::endl;
    }
    if (integer) {
        std::cout << "i: " << args::get(integer) << std::endl;
    }
    if (characters) {
        for (const auto ch : args::get(characters)) {
            std::cout << "c: " << ch << std::endl;
        }
    }
    if (foo) {
        std::cout << "f: " << args::get(foo) << std::endl;
    }
    if (numbers) {
        for (const auto nm : args::get(numbers)) {
            std::cout << "n: " << nm << std::endl;
        }
    }
    return EXIT_SUCCESS;
}
