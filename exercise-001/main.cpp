#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

void changeValueByParameter(int value) {
    fmt::print("  [In changeValueByParameter] Original parameter value: {}\n", value);
    value = 99;
    fmt::print("  [In changeValueByParameter] New parameter value (changed locally only): {}\n", value);
}

void changeValueByReference(int& ref) {
    fmt::print("  [In changeValueByReference] Original value: {}\n", ref);
    ref = 77;
    fmt::print("  [In changeValueByReference] New value (original changed!): {}\n", ref);
}

auto main(int argc, char **argv) -> int
{

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tfe24::PROJECT_NAME);

    int x = 10;
    int& r = x;

    fmt::print("Part 1: Basics of References\n");
    fmt::print("x = {}, r = {}\n", x, r);

    r = 42;
    fmt::print("After modification through reference: x = {}, r = {}\n\n", x, r);

    fmt::print("Part 2 & 3: Functions with References\n");

    int y = 5;
    fmt::print("Before changeValueByParameter(y): y = {}\n", y);
    changeValueByParameter(y);
    fmt::print("After changeValueByParameter(y): y = {}\n\n", y);

    fmt::print("Before changeValueByReference(y): y = {}\n", y);
    changeValueByReference(y);
    fmt::print("After changeValueByReference(y): y = {}\n", y);


    return 0; /* exit gracefully*/
}
