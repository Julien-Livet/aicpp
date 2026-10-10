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

TEST(ConnectionTest, PrimitiveHasOneDepth)
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

    std::vector<std::any> inputs{
        hodel::Integer{20},
        hodel::Integer{22}
    };

    aicpp::Connection connection{&add, inputs};

    EXPECT_EQ(connection.depth(), 1);
}

TEST(ConnectionTest, NestedExpressionHasGreaterDepth)
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

    std::vector<std::any> additionInputs{
        hodel::Integer{20},
        hodel::Integer{21}
    };

    aicpp::Connection addition{&add, additionInputs};

    std::vector<std::any> incrementInputs{
        addition
    };

    aicpp::Connection expression{
        &increment,
        incrementInputs
    };

    EXPECT_EQ(expression.depth(), 2);
}

TEST(ConnectionTest, PrimitiveHasStableCost)
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

    std::vector<std::any> inputs{
        hodel::Integer{20},
        hodel::Integer{22}
    };

    aicpp::Connection connection{&add, inputs};

    EXPECT_EQ(connection.cost(), connection.cost());
}

TEST(ConnectionTest, CostCountsConstantInputs)
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

    std::vector<std::any> inputs{
        hodel::Integer{20},
        hodel::Integer{22}
    };

    aicpp::Connection connection{&add, inputs};

    EXPECT_EQ(connection.cost(), 2);
}

TEST(ConnectionTest, CostCountsNestedExpressions)
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

    std::vector<std::any> additionInputs{
        hodel::Integer{20},
        hodel::Integer{21}
    };

    aicpp::Connection addition{&add, additionInputs};

    std::vector<std::any> incrementInputs{
        addition
    };

    aicpp::Connection expression{
        &increment,
        incrementInputs
    };

    EXPECT_EQ(addition.cost(), 2);
    EXPECT_EQ(expression.cost(), 3);
}

TEST(ConnectionTest, DepthCountsConstantInputLevel)
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

    std::vector<std::any> inputs{
        hodel::Integer{20},
        hodel::Integer{22}
    };

    aicpp::Connection connection{&add, inputs};

    EXPECT_EQ(connection.depth(), 1);
}

TEST(ConnectionTest, DepthCountsNestedExpressions)
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

    std::vector<std::any> additionInputs{
        hodel::Integer{20},
        hodel::Integer{21}
    };

    aicpp::Connection addition{&add, additionInputs};

    std::vector<std::any> incrementInputs{
        addition
    };

    aicpp::Connection expression{
        &increment,
        incrementInputs
    };

    EXPECT_EQ(addition.depth(), 1);
    EXPECT_EQ(expression.depth(), 2);
}

TEST(ConnectionTest, EquivalentConnectionsUsingSameNeuronAreEqual)
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

    std::vector<std::any> inputs1{
        hodel::Integer{20},
        hodel::Integer{22}
    };

    std::vector<std::any> inputs2{
        hodel::Integer{20},
        hodel::Integer{22}
    };

    aicpp::Connection first{&add, inputs1};
    aicpp::Connection second{&add, inputs2};

    EXPECT_TRUE(first == second);
}

TEST(ConnectionTest, ConnectionsWithDifferentInputsAreUnequal)
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

    std::vector<std::any> inputs1{
        hodel::Integer{20},
        hodel::Integer{22}
    };

    std::vector<std::any> inputs2{
        hodel::Integer{20},
        hodel::Integer{23}
    };

    aicpp::Connection first{&add, inputs1};
    aicpp::Connection second{&add, inputs2};

    EXPECT_FALSE(first == second);
}

TEST(ConnectionTest, ConnectionsUsingDifferentNeuronInstancesAreUnequal)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add1{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    AddNeuron add2{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    std::vector<std::any> inputs{
        hodel::Integer{20},
        hodel::Integer{22}
    };

    aicpp::Connection first{&add1, inputs};
    aicpp::Connection second{&add2, inputs};

    EXPECT_FALSE(first == second);
}

TEST(ConnectionTest, EqualConnectionsHaveEqualHashes)
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

    std::vector<std::any> inputs1{
        hodel::Integer{20},
        hodel::Integer{22}
    };

    std::vector<std::any> inputs2{
        hodel::Integer{20},
        hodel::Integer{22}
    };

    aicpp::Connection first{&add, inputs1};
    aicpp::Connection second{&add, inputs2};

    ASSERT_TRUE(first == second);
    EXPECT_EQ(first.hash(), second.hash());
}

TEST(ConnectionTest, HashIsStable)
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

    std::vector<std::any> inputs{
        hodel::Integer{20},
        hodel::Integer{22}
    };

    aicpp::Connection connection{&add, inputs};

    EXPECT_EQ(connection.hash(), connection.hash());
}

TEST(ConnectionTest, LeafInputsReturnsTerminalConnections)
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

    aicpp::Connection expression{&add, {hodel::Integer{20}, hodel::Integer{21}}};

    auto const inputs(expression.leafInputs());

    ASSERT_EQ(inputs.size(), 2);

    ASSERT_EQ(inputs[0].type(), typeid(hodel::Integer));
    ASSERT_EQ(inputs[1].type(), typeid(hodel::Integer));
}
TEST(ConnectionTest, ApplyInputsReplacesConstantInputs)
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

    aicpp::Connection expression{
        &add,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    std::vector<std::any> inputs{
        hodel::Integer{42},
        hodel::Integer{43}
    };

    expression.applyInputs(inputs);

    auto const leaves(expression.leafInputs());

    ASSERT_EQ(leaves.size(), 2);
    EXPECT_EQ(std::any_cast<hodel::Integer>(leaves[0]), 42);
    EXPECT_EQ(std::any_cast<hodel::Integer>(leaves[1]), 43);
}

TEST(ConnectionTest, ApplyInputsReplacesNestedInputs)
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

    aicpp::Connection left{
        &add,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    aicpp::Connection right{
        &add,
        {hodel::Integer{22}, hodel::Integer{23}}
    };

    aicpp::Connection expression{&add, {left, right}};

    std::vector<std::any> inputs{
        hodel::Integer{40},
        hodel::Integer{41},
        hodel::Integer{42},
        hodel::Integer{43}
    };

    expression.applyInputs(inputs);

    auto const leaves(expression.leafInputs());

    ASSERT_EQ(leaves.size(), 4);
    EXPECT_EQ(std::any_cast<hodel::Integer>(leaves[0]), 40);
    EXPECT_EQ(std::any_cast<hodel::Integer>(leaves[1]), 41);
    EXPECT_EQ(std::any_cast<hodel::Integer>(leaves[2]), 42);
    EXPECT_EQ(std::any_cast<hodel::Integer>(leaves[3]), 43);
}

TEST(ConnectionTest, ApplyInputsAcceptsMatchingTypes)
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

    aicpp::Connection expression{
        &add,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    std::vector<std::any> inputs{
        hodel::Integer{42},
        hodel::Integer{43}
    };

    expression.applyInputs(inputs, true);

    auto const leaves(expression.leafInputs());

    ASSERT_EQ(leaves.size(), 2);
    EXPECT_EQ(std::any_cast<hodel::Integer>(leaves[0]), 42);
    EXPECT_EQ(std::any_cast<hodel::Integer>(leaves[1]), 43);
}

static auto one()
{
    return hodel::Integer{1};
}

TEST(ConnectionTest, ApplyInputsReplacesZeroArgumentNeuron)
{
    using ConstantNeuron = aicpp::Neuron<hodel::Integer>;

    ConstantNeuron constant{
        "ONE",
        &one
    };

    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    aicpp::Connection oneConnection{&constant, {}};

    aicpp::Connection expression{
        &add,
        {oneConnection, hodel::Integer{21}}
    };

    std::vector<std::any> inputs{
        hodel::Integer{42},
        hodel::Integer{43}
    };

    expression.applyInputs(inputs);

    auto const leaves(expression.leafInputs());

    ASSERT_EQ(leaves.size(), 2);
    EXPECT_EQ(std::any_cast<hodel::Integer>(leaves[0]), 42);
    EXPECT_EQ(std::any_cast<hodel::Integer>(leaves[1]), 43);
}

TEST(ConnectionTest, ReplaceNeuronWithMatchingSignature)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add1{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    AddNeuron add2{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    aicpp::Connection expression{
        &add1,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    EXPECT_TRUE(expression.replace(&add2));
    EXPECT_EQ(expression.neuron(), &add2);
}

TEST(ConnectionTest, ReplaceNeuronRejectsDifferentName)
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

    AddNeuron other{
        "other",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    aicpp::Connection expression{
        &add,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    EXPECT_FALSE(expression.replace(&other));
    EXPECT_EQ(expression.neuron(), &add);
}

TEST(ConnectionTest, ReplaceNeuronRecursively)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add1{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    AddNeuron add2{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    aicpp::Connection left{
        &add1,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    aicpp::Connection right{
        &add1,
        {hodel::Integer{22}, hodel::Integer{23}}
    };

    aicpp::Connection expression{&add1, {left, right}};

    EXPECT_TRUE(expression.replace(&add2));

    EXPECT_EQ(expression.neuron(), &add2);

    auto const leaves(expression.leafInputs());

    ASSERT_EQ(leaves.size(), 4);
    EXPECT_EQ(std::any_cast<hodel::Integer>(leaves[0]), 20);
    EXPECT_EQ(std::any_cast<hodel::Integer>(leaves[1]), 21);
    EXPECT_EQ(std::any_cast<hodel::Integer>(leaves[2]), 22);
    EXPECT_EQ(std::any_cast<hodel::Integer>(leaves[3]), 23);

    {
        ASSERT_EQ(expression.neuron(), &add2);

        auto const& rootInputs = expression.inputs();

        ASSERT_EQ(rootInputs.size(), 2);
        ASSERT_EQ(rootInputs[0].type(), typeid(aicpp::Connection));
        ASSERT_EQ(rootInputs[1].type(), typeid(aicpp::Connection));

        auto const& left = std::any_cast<aicpp::Connection const&>(rootInputs[0]);
        auto const& right = std::any_cast<aicpp::Connection const&>(rootInputs[1]);

        EXPECT_EQ(left.neuron(), &add2);
        EXPECT_EQ(right.neuron(), &add2);
    }
}

TEST(ConnectionTest, ReplaceNeuronInSubExpressionOnly)
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

    AddNeuron add1{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };
    AddNeuron add2{
        "add",
        static_cast<AddNeuron::Function>(&hodel::add)
    };
    IncrementNeuron increment{
        "increment",
        static_cast<IncrementNeuron::Function>(&hodel::increment)
    };

    aicpp::Connection addition{
        &add1,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    aicpp::Connection expression{&increment, {addition}};

    EXPECT_TRUE(expression.replace(&add2));

    EXPECT_EQ(expression.neuron(), &increment);

    auto const& inputs = expression.inputs();
    ASSERT_EQ(inputs.size(), 1);
    ASSERT_EQ(inputs[0].type(), typeid(aicpp::Connection));

    auto const& replacedAddition =
        std::any_cast<aicpp::Connection const&>(inputs[0]);

    EXPECT_EQ(replacedAddition.neuron(), &add2);
}

TEST(ConnectionTest, ReplaceNeuronWithDifferentSignature)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    using UnaryNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&
    >;

    AddNeuron add{
        "operation",
        static_cast<AddNeuron::Function>(&hodel::add)
    };

    UnaryNeuron unary{
        "operation",
        static_cast<UnaryNeuron::Function>(&hodel::increment)
    };

    aicpp::Connection expression{
        &add,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    EXPECT_FALSE(expression.replace(&unary));
    EXPECT_EQ(expression.neuron(), &add);
}
