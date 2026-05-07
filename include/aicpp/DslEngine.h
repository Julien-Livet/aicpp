#ifndef AICPP_DSLENGINE_H
#define AICPP_DSLENGINE_H

#include "aicpp/Connection.h"

namespace aicpp
{
    class DslEngine
    {
        public:
            template <typename T> Connection learn(T const& target)
            {
                //...
            }
    };
}

#endif // AICPP_DSLENGINE_H
