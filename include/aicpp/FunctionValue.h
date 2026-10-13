#ifndef AICPP_FUNCTION_VALUE_H
#define AICPP_FUNCTION_VALUE_H

#include "aicpp/Connection.h"

namespace aicpp
{
    struct FunctionValue
    {
        Connection connection;

        std::any apply(std::any const& argument) const
        {
            return connection.apply(argument);
        }
    };
}

#endif // AICPP_FUNCTION_VALUE_H
