#include <fmt/chrono.h>
#include <fmt/format.h>

#include <random>
#include <vector>
#include <algorithm>
#include <chrono>  

#include "CLI/CLI.hpp"
#include "config.h"

void print_vector(const std::vector<int> &vec, const std::string &label = "Vector")
{
    fmt::print("{} ({} Values):\n", label, vec.size());
    for (auto value : vec)
    {
        fmt::print("{} ", value);
    }
    fmt::print("\n\n");
}

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    
    int count = 500;
    app.add_option("-c,--count", count, "number of repetitions")->default_val(500);

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

    print_vector(numbers, "random Values");

    auto start = std::chrono::system_clock::now();
    std::sort(numbers.begin(), numbers.end());
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    print_vector(numbers, "random Values (sorted)");
    fmt::print("time of sorting process: {} ms\n", elapsed.count());

    return 0; /* exit gracefully*/
}
