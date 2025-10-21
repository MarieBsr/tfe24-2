#include <fmt/chrono.h>
#include <fmt/format.h>
#include <random>

#include "CLI/CLI.hpp"
#include "config.h"

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    
    int count = 20;
    app.add_option("-c,--count", count, "number of repetitions")->default_val(20);

    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());
    fmt::print("Count parameter = {}\n", count);

     std::vector<int> numbers(count);

    std::random_device rd;                               
    std::mt19937 gen(rd());                              
    std::uniform_int_distribution<> dist(1, 100);        

    std::generate(numbers.begin(), numbers.end(), [&]() { return dist(gen); });

    fmt::print("randomValues:\n");
    for (auto n : numbers)
    {
        fmt::print("{} ", n);
    }
    fmt::print("\n");

    return 0; /* exit gracefully*/
}
