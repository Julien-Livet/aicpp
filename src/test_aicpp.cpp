#include <gtest/gtest.h>

#include "aicpp/Connection.h"
#include "aicpp/Hodel.h"
#include "aicpp/Neuron.h"

TEST(NeuronTest, CallsNativeFunction)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron neuron{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    EXPECT_EQ(neuron.function()(20, 22), 42);
}

TEST(NeuronTest, StoresName)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron neuron{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    EXPECT_EQ(neuron.name(), "add");
}

TEST(NeuronTest, ExposesReturnType)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    static_assert(
        std::is_same_v<
            AddNeuron::ReturnType,
            hodel::Integer
        >
    );
}

TEST(NeuronTest, ExposesArity)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    EXPECT_EQ(AddNeuron::Arity, 2);
}

TEST(NeuronTest, CallsUnaryNativeFunction)
{
    using IncrementNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&
    >;

    IncrementNeuron neuron{
        "increment",
        static_cast<IncrementNeuron::Function>(
            &hodel::increment
        )
    };

    EXPECT_EQ(neuron.function()(41), 42);
}

TEST(NeuronTest, InvokeAcceptsCorrectInputs)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron neuron{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    std::vector<std::any> inputs{
        hodel::Integer{20},
        hodel::Integer{22}
    };

    auto result = neuron.invoke(inputs);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(
        std::any_cast<hodel::Integer>(result),
        42
    );
}

TEST(NeuronTest, InvokeRejectsWrongArity)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron neuron{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    std::vector<std::any> inputs{
        hodel::Integer{20}
    };

    EXPECT_THROW(
        neuron.invoke(inputs),
        std::invalid_argument
    );
}

TEST(NeuronTest, InvokeRejectsWrongInputType)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron neuron{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    std::vector<std::any> inputs{
        hodel::Integer{20},
        hodel::Boolean{true}
    };

    EXPECT_THROW(
        neuron.invoke(inputs),
        std::bad_any_cast
    );
}

TEST(NeuronTest, ExposesCorrectTypeMetadata)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron neuron{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    EXPECT_EQ(
        neuron.returnType(),
        std::type_index(typeid(hodel::Integer))
    );

    auto inputs = neuron.inputTypes();

    ASSERT_EQ(inputs.size(), 2);

    EXPECT_EQ(
        inputs[0],
        std::type_index(typeid(hodel::Integer))
    );

    EXPECT_EQ(
        inputs[1],
        std::type_index(typeid(hodel::Integer))
    );
}

TEST(NeuronTest, SelectsCorrectOverload)
{
    using ScalarAdd = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    using TupleAdd = aicpp::Neuron<
        hodel::IntegerTuple,
        hodel::IntegerTuple const&,
        hodel::Integer const&
    >;

    ScalarAdd scalarAdd{
        "add",
        static_cast<ScalarAdd::Function>(
            static_cast<hodel::Integer (*)(
                hodel::Integer const&,
                hodel::Integer const&
            )>(&hodel::add)
        )
    };

    TupleAdd tupleAdd{
        "add",
        static_cast<TupleAdd::Function>(
            static_cast<hodel::IntegerTuple (*)(
                hodel::IntegerTuple const&,
                hodel::Integer const&
            )>(&hodel::add)
        )
    };

    EXPECT_EQ(
        scalarAdd.function()(2, 3),
        5
    );

    hodel::IntegerTuple tuple{2, 3};

    auto result = tupleAdd.function()(tuple, 1);

    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 4);
}

TEST(ConnectionTest, EvaluatesPrimitive)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    aicpp::Connection connection{
        &add,
        {
            std::any{hodel::Integer{20}},
            std::any{hodel::Integer{22}}
        }
    };

    auto result = connection.output();

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(
        std::any_cast<hodel::Integer>(result),
        42
    );
}

TEST(ConnectionTest, EvaluatesNestedExpression)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    using IncrementNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    IncrementNeuron increment{
        "increment",
        static_cast<IncrementNeuron::Function>(
            &hodel::increment
        )
    };

    aicpp::Connection addition{
        &add,
        {
            std::any{hodel::Integer{20}},
            std::any{hodel::Integer{21}}
        }
    };

    aicpp::Connection expression{
        &increment,
        {
            std::any{addition}
        }
    };

    auto result = expression.output();

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(
        std::any_cast<hodel::Integer>(result),
        42
    );
}
