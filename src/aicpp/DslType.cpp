#include <boost/algorithm/string/join.hpp>

#include "aicpp/DslType.h"
#include "aicpp/Hodel.h"
#include "aicpp/Connection.h"

using namespace aicpp;

std::string DslType::string() const
{
    std::vector<std::string> args;
    auto const inputs{this->inputs()};
    args.reserve(inputs.size());

    for (auto const input : inputs)
    {
        try
        {
            args.emplace_back(hodel::types.at(input.nativeType()));
        }
        catch (std::exception const&)
        {
            args.emplace_back(input.nativeType().name());
        }
    }

    auto signature{"(" + boost::algorithm::join(args, ", ") + ") -> "};

    try
    {
        signature += hodel::types.at(output().nativeType());
    }
    catch (std::exception const&)
    {
        signature += output().nativeType().name();
    }

    return signature;
}

std::string aicpp::signature(std::vector<std::any> const& args)
{
    std::vector<std::string> v;
    v.reserve(args.size());

    for (auto const& arg : args)
    {
        if (arg.type() == typeid(Connection))
        {
            auto const connection{std::any_cast<Connection>(arg)};

            v.emplace_back(connection.signature().string());
        }
        else
        {
            try
            {
                v.emplace_back(hodel::types.at(arg.type()));
            }
            catch (std::exception const&)
            {
                v.emplace_back(arg.type().name());
            }
        }
    }

    return "(" + boost::algorithm::join(v, ", ") + ") -> ?";
}
