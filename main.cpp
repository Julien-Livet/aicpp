#include <iostream>

#include "Brain.h"

template <typename... Ts>
std::map<std::string, size_t> generateAllCasts(Brain& brain)
{
    std::map<std::string, size_t> neuronIds;

    (..., ([&] {
         using S = Ts;

         (..., ([&] {
              using T = Ts;

              if constexpr (!std::is_same_v<S, T>)
              {
                  auto const m{brain.addCast<S, T>()};
                  neuronIds.insert(m.begin(), m.end());
              }
          }(), 0));
     }(), 0));

    return neuronIds;
}

int main()
{
    Brain brain;

    std::map<std::string, size_t> neuronIds;

    {
        auto const m{brain.addInts<char>()};
        neuronIds.insert(m.begin(), m.end());
    }

    {
        auto const m{brain.addInts<int>()};
        neuronIds.insert(m.begin(), m.end());
    }

    {
        auto const m{brain.addInts<long>()};
        neuronIds.insert(m.begin(), m.end());
    }

    {
        auto const m{brain.addReals<double>()};
        neuronIds.insert(m.begin(), m.end());
    }

    {
        auto const m{brain.addReals<float>()};
        neuronIds.insert(m.begin(), m.end());
    }

    {
        auto const m{brain.addMatrices<Eigen::MatrixXd>()};
        neuronIds.insert(m.begin(), m.end());
    }

    {
        auto const m{brain.addMatrices<Eigen::MatrixXf>()};
        neuronIds.insert(m.begin(), m.end());
    }

    {
        auto const m{brain.addMatrices<Eigen::MatrixXi>()};
        neuronIds.insert(m.begin(), m.end());
    }

    {
        auto const m{generateAllCasts<char, double, float, int, long>(brain)};
        neuronIds.insert(m.begin(), m.end());
    }

    int x{16};
    int y{25};
    int z{34};

    neuronIds["x"] = brain.addNeuron(Neuron<int>([&x] () { return x; }, "x"));
    neuronIds["y"] = brain.addNeuron(Neuron<int>([&y] () { return y; }, "y"));
    neuronIds["z"] = brain.addNeuron(Neuron<int>([&z] () { return z; }, "z"));

    //auto const connections{brain.learn(x * y)};
    auto const connections{brain.learn(x * y + z)};

    std::cout << "Given output: " << x * y + z << std::endl;
    std::cout << "Found output: " << std::any_cast<int>(brain.connectionOutput(connections.front())) << std::endl;

    bool xProvided{false};
    bool yProvided{false};
    bool zProvided{false};

    std::get<Neuron<int> >(brain.neuron(neuronIds["x"])).function =
        [&x, &xProvided] () -> int
        {
            if (xProvided)
                return x;

            std::cout << "x? ";
            std::cin >> x;
            xProvided = true;

            return x;
        };
    std::get<Neuron<int> >(brain.neuron(neuronIds["y"])).function =
        [&y, &yProvided] () -> int
        {
            if (yProvided)
                return y;

            std::cout << "y? ";
            std::cin >> y;
            yProvided = true;

            return y;
        };
    std::get<Neuron<int> >(brain.neuron(neuronIds["z"])).function =
        [&z, &zProvided]() -> int
        {
            if (zProvided)
                return z;

            std::cout << "z? ";
            std::cin >> z;
            zProvided = true;

            return z;
        };

    std::cout << "New output: " << std::any_cast<int>(brain.connectionOutput(connections.front())) << std::endl;
/*
    Connection const connection{std::vector<Connection::Input>{brain.neuron(neuronIds["x"]), 2}, neuronIds["add_i"]};

    std::cout << std::any_cast<int>(brain.connectionOutput(connection)) << std::endl;

    x = 5;

    std::cout << std::any_cast<int>(brain.connectionOutput(connection)) << std::endl;

    std::get<Neuron<int> >(brain.neuron(neuronIds["x"])).function =
        [] () -> int
        {
            std::cout << "x? ";
            int x;
            std::cin >> x;

            return x;
        };

    std::cout << std::any_cast<int>(brain.connectionOutput(connection)) << std::endl;
*/
    return 0;
}
