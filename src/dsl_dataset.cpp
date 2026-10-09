#include <cassert>
#include <fstream>
#include <iostream>
#include <mutex>
#include <optional>
#include <print>
#include <random>
#include <set>
#include <thread>

#include <boost/timer/progress_display.hpp>

#include "aicpp/Hodel.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <depth> <count>" << std::endl;

        return 1;
    }

    size_t const depth{static_cast<size_t>(std::stoi(argv[1]))};
    size_t const count{static_cast<size_t>(std::stoi(argv[2]))};

    //TODO: ...

    return 0;
}
