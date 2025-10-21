#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

int globalVar = 1;

void foo() {
    fmt::print("Hello from foo!\n");
}

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
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

    fmt::print("\n=== Part 1: Global Variable (Data Segment) ===\n");
    fmt::print("Value of globalVar: {}\n", globalVar);
    fmt::print("Address of globalVar: {}\n\n", fmt::ptr(&globalVar));

    fmt::print("=== Part 2: Local Variable (Stack) ===\n");
    int localVar = 2;
    fmt::print("Value of localVar: {}\n", localVar);
    fmt::print("Address of localVar: {}\n\n", fmt::ptr(&localVar));

    fmt::print("=== Part 3: Dynamically Allocated Variable (Heap) ===\n");
    int* heapVar = new int(3);
    fmt::print("Value of *heapVar: {}\n", *heapVar);
    fmt::print("Address stored in heapVar (heap memory location): {}\n", fmt::ptr(heapVar));
    delete heapVar;  
    fmt::print("Heap memory released.\n\n");

    fmt::print("=== Part 4: Function (Code Segment) ===\n");
    foo();
    fmt::print("Address of function foo: {}\n", fmt::ptr(&foo));

    return 0; /* exit gracefully*/
}
