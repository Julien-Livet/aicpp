#include <boost/algorithm/string/join.hpp>

#include "aicpp/DslType.h"
#include "aicpp/Hodel.h"

using namespace aicpp;

std::string DslType::string() const
{
    std::vector<std::string> args;
    args.reserve(inputs().size());

    for (auto const& input : inputs())
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
