#include <gtest/gtest.h>

#include "aicpp/Connection.h"
#include "aicpp/Hodel.h"
#include "aicpp/Neuron.h"
#include "aicpp/DslType.h"
#include "aicpp/ComposeNeuron.h"
#include "aicpp/ChainNeuron.h"
#include "aicpp/ForkNeuron.h"
#include "aicpp/ExtractNeuron.h"
#include "aicpp/HodelRegister.h"
#include "aicpp/FunctionValue.h"
#include "aicpp/ApplyNeuron.h"
#include "aicpp/ArgminNeuron.h"
#include "aicpp/ValminNeuron.h"
#include "aicpp/FunctionAdapterNeuron.h"
#include "aicpp/RbindNeuron.h"
#include "aicpp/LbindNeuron.h"

TEST(NeuronTest, CallsNativeFunction)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron neuron{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<IncrementNeuron::PointerFunction>(
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<ScalarAdd::PointerFunction>(
            static_cast<hodel::Integer (*)(
                hodel::Integer const&,
                hodel::Integer const&
            )>(&hodel::add)
        )
    };

    TupleAdd tupleAdd{
        "add",
        static_cast<TupleAdd::PointerFunction>(
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    IncrementNeuron increment{
        "increment",
        static_cast<IncrementNeuron::PointerFunction>(
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    IncrementNeuron increment{
        "increment",
        static_cast<IncrementNeuron::PointerFunction>(
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    IncrementNeuron increment{
        "increment",
        static_cast<IncrementNeuron::PointerFunction>(
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    IncrementNeuron increment{
        "increment",
        static_cast<IncrementNeuron::PointerFunction>(
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    AddNeuron add2{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    AddNeuron add2{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    AddNeuron other{
        "other",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    AddNeuron add2{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };
    AddNeuron add2{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };
    IncrementNeuron increment{
        "increment",
        static_cast<IncrementNeuron::PointerFunction>(&hodel::increment)
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
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    UnaryNeuron unary{
        "operation",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::Connection expression{
        &add,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    EXPECT_FALSE(expression.replace(&unary));
    EXPECT_EQ(expression.neuron(), &add);
}

TEST(ConnectionTest, ReplaceNeuronUpdatesHash)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add1{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };
    AddNeuron add2{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    aicpp::Connection expression{
        &add1,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    ASSERT_TRUE(expression.replace(&add2));
    EXPECT_EQ(expression.neuron(), &add2);

    aicpp::Connection expected{
        &add2,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    EXPECT_EQ(expression.hash(), expected.hash());
}

TEST(ConnectionTest, ReplaceNeuronUpdatesHashRecursively)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add1{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };
    AddNeuron add2{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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

    ASSERT_TRUE(expression.replace(&add2));

    aicpp::Connection expectedLeft{
        &add2,
        {hodel::Integer{20}, hodel::Integer{21}}
    };
    aicpp::Connection expectedRight{
        &add2,
        {hodel::Integer{22}, hodel::Integer{23}}
    };
    aicpp::Connection expected{
        &add2,
        {expectedLeft, expectedRight}
    };

    EXPECT_EQ(expression.hash(), expected.hash());
}

TEST(ConnectionTest, EqualConnectionsHaveEqualHashesAfterReplace)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add1{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };
    AddNeuron add2{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    aicpp::Connection expression1{
        &add1,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    aicpp::Connection expression2{
        &add2,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    ASSERT_TRUE(expression1.replace(&add2));

    EXPECT_TRUE(expression1 == expression2);
    EXPECT_EQ(expression1.hash(), expression2.hash());
}

TEST(ConnectionTest, ApplyInputsRejectsWrongType)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    aicpp::Connection expression{
        &add,
        {std::type_index{typeid(int16_t)}, std::type_index{typeid(int16_t)}}
    };

    EXPECT_DEATH(
        expression.applyInputs(
            {
                std::type_index{typeid(std::string)},
                std::type_index{typeid(int16_t)}
            },
            true
        ),
        ""
    );
}

TEST(ConnectionTest, ApplyInputsChecksTypesRecursively)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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

    EXPECT_DEATH(
        expression.applyInputs(
            {
                std::string{"invalid"},
                hodel::Integer{1},
                hodel::Integer{2},
                hodel::Integer{3}
            },
            true
        ),
        ""
    );
}

TEST(ConnectionTest, ApplyInputsUpdatesHash)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    aicpp::Connection expression{
        &add,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    expression.applyInputs(
        {hodel::Integer{42}, hodel::Integer{43}}
    );

    aicpp::Connection expected{
        &add,
        {hodel::Integer{42}, hodel::Integer{43}}
    };

    EXPECT_EQ(expression.hash(), expected.hash());
}

TEST(ConnectionTest, ApplyInputsUpdatesHashRecursively)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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

    expression.applyInputs({
        hodel::Integer{40},
        hodel::Integer{41},
        hodel::Integer{42},
        hodel::Integer{43}
    });

    aicpp::Connection expectedLeft{
        &add,
        {hodel::Integer{40}, hodel::Integer{41}}
    };

    aicpp::Connection expectedRight{
        &add,
        {hodel::Integer{42}, hodel::Integer{43}}
    };

    aicpp::Connection expected{
        &add,
        {expectedLeft, expectedRight}
    };

    EXPECT_EQ(expression.hash(), expected.hash());
}

TEST(ConnectionTest, InputTypesHandlesNullaryNeuron)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    using ConstantNeuron = aicpp::Neuron<hodel::Integer>;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    ConstantNeuron constant{"one", &one};

    aicpp::Connection oneConnection{&constant, {}};

    aicpp::Connection expression{
        &add,
        {oneConnection, hodel::Integer{2}}
    };

    auto const types = expression.inputTypes();

    ASSERT_EQ(types.size(), 2);
    EXPECT_EQ(types[0], typeid(hodel::Integer));
    EXPECT_EQ(types[1], typeid(hodel::Integer));
}

TEST(ConnectionTest, InputTypesHandlesTwoNullaryNeurons)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    using ConstantNeuron = aicpp::Neuron<hodel::Integer>;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    ConstantNeuron oneNeuron{"one", &one};
    ConstantNeuron anotherOneNeuron{"another_one", &one};

    aicpp::Connection oneConnection{&oneNeuron, {}};
    aicpp::Connection anotherOneConnection{&anotherOneNeuron, {}};

    aicpp::Connection expression{
        &add,
        {oneConnection, anotherOneConnection}
    };

    auto const types = expression.inputTypes();

    ASSERT_EQ(types.size(), 2);
    EXPECT_EQ(types[0], typeid(hodel::Integer));
    EXPECT_EQ(types[1], typeid(hodel::Integer));
}

TEST(ConnectionTest, ApplyInputsRejectsWrongTypeForNullaryNeuron)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    using ConstantNeuron = aicpp::Neuron<hodel::Integer>;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    ConstantNeuron constant{"one", &one};

    aicpp::Connection oneConnection{&constant, {}};

    aicpp::Connection expression{
        &add,
        {oneConnection, hodel::Integer{2}}
    };

    EXPECT_DEATH(
        expression.applyInputs(
            {
                std::string{"invalid"},
                hodel::Integer{2}
            },
            true
        ),
        ""
    );
}

TEST(ConnectionTest, ExpectedInputTypesReturnsSignatureTypes)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    aicpp::Connection expression{
        &add,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    auto const types = expression.expectedInputTypes();

    ASSERT_EQ(types.size(), 2);
    EXPECT_EQ(types[0], typeid(hodel::Integer));
    EXPECT_EQ(types[1], typeid(hodel::Integer));
}

TEST(ConnectionTest, ExpectedInputTypesHandlesNestedConnections)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
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

    auto const types = expression.expectedInputTypes();

    ASSERT_EQ(types.size(), 4);

    for (auto const& type : types)
        EXPECT_EQ(type, typeid(hodel::Integer));
}

TEST(ConnectionTest, ExpectedInputTypesHandlesNullaryNeuron)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    using ConstantNeuron = aicpp::Neuron<hodel::Integer>;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    ConstantNeuron constant{"one", &one};

    aicpp::Connection oneConnection{&constant, {}};

    aicpp::Connection expression{
        &add,
        {oneConnection, hodel::Integer{2}}
    };

    auto const types = expression.expectedInputTypes();

    ASSERT_EQ(types.size(), 2);
    EXPECT_EQ(types[0], typeid(hodel::Integer));
    EXPECT_EQ(types[1], typeid(hodel::Integer));
}

TEST(ConnectionTest, ConstructorAcceptsValidInputs)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    std::vector<std::any> inputs{
        hodel::Integer{20},
        hodel::Integer{21}
    };

    aicpp::Connection connection{&add, inputs};

    EXPECT_EQ(connection.neuron(), &add);
    ASSERT_EQ(connection.inputs().size(), 2);
    EXPECT_EQ(
        std::any_cast<hodel::Integer>(connection.inputs()[0]),
        20
    );
    EXPECT_EQ(
        std::any_cast<hodel::Integer>(connection.inputs()[1]),
        21
    );
}

TEST(ConnectionTest, ConstructorAcceptsValidNestedConnection)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    aicpp::Connection left{
        &add,
        {hodel::Integer{20}, hodel::Integer{21}}
    };

    aicpp::Connection expression{
        &add,
        {left, hodel::Integer{22}}
    };

    ASSERT_EQ(expression.inputs().size(), 2);

    auto const nested =
        std::any_cast<aicpp::Connection>(expression.inputs()[0]);

    EXPECT_EQ(nested.neuron(), &add);
}

TEST(ConnectionTest, ConstructorAcceptsMatchingTypeIndexInputs)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    aicpp::Connection expression{
        &add,
        {
            std::type_index{typeid(hodel::Integer)},
            std::type_index{typeid(hodel::Integer)}
        }
    };

    ASSERT_EQ(expression.inputs().size(), 2);

    EXPECT_EQ(
        std::any_cast<std::type_index>(expression.inputs()[0]),
        typeid(hodel::Integer)
    );
}

TEST(ConnectionTest, ConstructorRejectsIncorrectNumberOfInputs)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    EXPECT_DEATH(
        (
            aicpp::Connection{
                &add,
                {hodel::Integer{20}}
            }
        ),
        ""
    );
}

static auto trueFunction()
{
    return hodel::Boolean{true};
}

TEST(ConnectionTest, ConstructorRejectsNestedConnectionWithIncorrectReturnType)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    using BooleanNeuron = aicpp::Neuron<hodel::Boolean>;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    BooleanNeuron booleanNeuron{
        "boolean",
        &trueFunction
    };

    aicpp::Connection booleanConnection{&booleanNeuron, {}};

    EXPECT_DEATH(
        (
            aicpp::Connection{
                &add,
                {booleanConnection, hodel::Integer{2}}
            }
        ),
        ""
    );
}

TEST(ConnectionTest, ConstructorRejectsIncorrectTypeIndex)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    EXPECT_DEATH(
        (
            aicpp::Connection{
                &add,
                {
                    std::type_index{typeid(hodel::Boolean)},
                    std::type_index{typeid(hodel::Integer)}
                }
            }
        ),
        ""
    );
}

TEST(ConnectionTest, ConstructorRejectsIncorrectConcreteInputType)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    EXPECT_DEATH(
        (
            aicpp::Connection{
                &add,
                {
                    std::string{"invalid"},
                    hodel::Integer{21}
                }
            }
        ),
        ""
    );
}

TEST(DslTypeTest, NativeTypesAreEqual)
{
    aicpp::DslType const integer1{typeid(hodel::Integer)};
    aicpp::DslType const integer2{typeid(hodel::Integer)};
    aicpp::DslType const boolean{typeid(hodel::Boolean)};

    EXPECT_EQ(integer1, integer2);
    EXPECT_NE(integer1, boolean);
}

TEST(DslTypeTest, FunctionTypesAreEqual)
{
    aicpp::DslType const integer{typeid(hodel::Integer)};
    aicpp::DslType const boolean{typeid(hodel::Boolean)};

    aicpp::DslType const predicate1{
        aicpp::DslType::function({integer}, boolean)
    };

    aicpp::DslType const predicate2{
        aicpp::DslType::function({integer}, boolean)
    };

    EXPECT_EQ(predicate1, predicate2);
}

TEST(DslTypeTest, FunctionTypesDifferByInput)
{
    aicpp::DslType const integer{typeid(hodel::Integer)};
    aicpp::DslType const boolean{typeid(hodel::Boolean)};

    aicpp::DslType const predicate{
        aicpp::DslType::function({integer}, boolean)
    };

    aicpp::DslType const booleanFunction{
        aicpp::DslType::function({boolean}, boolean)
    };

    EXPECT_NE(predicate, booleanFunction);
}

TEST(DslTypeTest, FunctionTypesDifferByOutput)
{
    aicpp::DslType const integer{typeid(hodel::Integer)};
    aicpp::DslType const boolean{typeid(hodel::Boolean)};

    aicpp::DslType const integerFunction{
        aicpp::DslType::function({integer}, integer)
    };

    aicpp::DslType const predicate{
        aicpp::DslType::function({integer}, boolean)
    };

    EXPECT_NE(integerFunction, predicate);
}

TEST(DslTypeTest, NestedFunctionTypesAreSupported)
{
    aicpp::DslType const integer{typeid(hodel::Integer)};
    aicpp::DslType const boolean{typeid(hodel::Boolean)};

    aicpp::DslType const predicate{
        aicpp::DslType::function({integer}, boolean)
    };

    aicpp::DslType const higherOrderFunction{
        aicpp::DslType::function({predicate}, integer)
    };

    EXPECT_TRUE(higherOrderFunction.isFunction());
    ASSERT_EQ(higherOrderFunction.inputs().size(), 1);
    EXPECT_EQ(higherOrderFunction.inputs()[0], predicate);
    EXPECT_EQ(higherOrderFunction.output(), integer);
}

TEST(DslTypeTest, IgnoresCppReferencesAndQualifiers)
{
    auto const integer = aicpp::makeDslType<hodel::Integer>();
    auto const integerRef = aicpp::makeDslType<hodel::Integer const&>();

    EXPECT_EQ(integer, integerRef);
}

TEST(NeuronTest, ExposesDslSignature)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron neuron{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    aicpp::DslType const integer{
        aicpp::makeDslType<hodel::Integer>()
    };

    aicpp::DslType const expected{
        aicpp::DslType::function(
            {integer, integer},
            integer)
    };

    EXPECT_EQ(neuron.signature(), expected);
}

TEST(NeuronTest, ExposesBooleanReturnType)
{
    using PredicateNeuron = aicpp::Neuron<
        hodel::Boolean,
        hodel::Integer const&
    >;

    PredicateNeuron neuron{"predicate", nullptr};

    aicpp::DslType const expected{
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Integer>()},
            aicpp::makeDslType<hodel::Boolean>())
    };

    EXPECT_EQ(neuron.signature(), expected);
}

TEST(NeuronTest, ExposesSignatureThroughNeuronBase)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron neuron{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    aicpp::NeuronBase const& base{neuron};

    aicpp::DslType const integer{
        aicpp::makeDslType<hodel::Integer>()
    };

    aicpp::DslType const expected{
        aicpp::DslType::function(
            {integer, integer},
            integer)
    };

    EXPECT_EQ(base.signature(), expected);
}

TEST(DslTypeTest, InfersComposeSignature)
{
    auto const integer = aicpp::makeDslType<hodel::Integer>();
    auto const boolean = aicpp::makeDslType<hodel::Boolean>();

    auto const isZero = aicpp::DslType::function(
        {integer},
        boolean);

    auto const negate = aicpp::DslType::function(
        {boolean},
        boolean);

    auto const expected = aicpp::DslType::function(
        {integer},
        boolean);

    EXPECT_EQ(
        aicpp::inferComposeSignature(negate, isZero),
        expected);
}

TEST(DslTypeTest, RejectsIncompatibleComposeTypes)
{
    auto const integer = aicpp::makeDslType<hodel::Integer>();
    auto const boolean = aicpp::makeDslType<hodel::Boolean>();

    auto const outer = aicpp::DslType::function(
        {boolean},
        boolean);

    auto const inner = aicpp::DslType::function(
        {integer},
        integer);

    EXPECT_THROW(
        aicpp::inferComposeSignature(outer, inner),
        std::invalid_argument);
}

TEST(DslTypeTest, RejectsNonUnaryOuterComposeFunction)
{
    auto const integer = aicpp::makeDslType<hodel::Integer>();

    auto const outer = aicpp::DslType::function(
        {integer, integer},
        integer);

    auto const inner = aicpp::DslType::function(
        {integer},
        integer);

    EXPECT_THROW(
        aicpp::inferComposeSignature(outer, inner),
        std::invalid_argument);
}

TEST(DslTypeTest, RejectsNonUnaryInnerComposeFunction)
{
    auto const integer = aicpp::makeDslType<hodel::Integer>();

    auto const outer = aicpp::DslType::function(
        {integer},
        integer);

    auto const inner = aicpp::DslType::function(
        {integer, integer},
        integer);

    EXPECT_THROW(
        aicpp::inferComposeSignature(outer, inner),
        std::invalid_argument);
}

TEST(DslTypeTest, RejectsNonFunctionComposeArguments)
{
    auto const integer = aicpp::makeDslType<hodel::Integer>();

    auto const function = aicpp::DslType::function(
        {integer},
        integer);

    EXPECT_THROW(
        aicpp::inferComposeSignature(integer, function),
        std::invalid_argument);

    EXPECT_THROW(
        aicpp::inferComposeSignature(function, integer),
        std::invalid_argument);
}

TEST(ComposeNeuron, InfersSignature)
{
    aicpp::ComposeNeuron compose;

    auto const outer = aicpp::DslType::function(
        {aicpp::makeDslType<bool>()},
        aicpp::makeDslType<bool>());

    auto const inner = aicpp::DslType::function(
        {aicpp::makeDslType<int>()},
        aicpp::makeDslType<bool>());

    auto const actual = compose.inferSignature({outer, inner});

    auto const expected = aicpp::DslType::function(
        {aicpp::makeDslType<int>()},
        aicpp::makeDslType<bool>());

    EXPECT_EQ(actual, expected);
}

TEST(ComposeNeuron, RejectsWrongNumberOfArguments)
{
    aicpp::ComposeNeuron compose;

    EXPECT_THROW(
        compose.inferSignature({}),
        std::invalid_argument);

    EXPECT_THROW(
        compose.inferSignature({
            aicpp::makeDslType<bool>()
        }),
        std::invalid_argument);
}

TEST(NeuronBase, NativeNeuronIsNotPolymorphic)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron neuron{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    EXPECT_FALSE(neuron.isPolymorphic());
}

TEST(ConnectionTest, SignatureReturnsNeuronSignature)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    aicpp::Connection expression{
        &add,
        {hodel::Integer{1}, hodel::Integer{2}}
    };

    auto const expected = aicpp::DslType::function(
        {
            aicpp::makeDslType<hodel::Integer const&>(),
            aicpp::makeDslType<hodel::Integer const&>()
        },
        aicpp::makeDslType<hodel::Integer>()
    );

    EXPECT_EQ(expression.signature(), expected);
}

TEST(ComposeNeuron, HasName)
{
    aicpp::ComposeNeuron compose;

    EXPECT_EQ(compose.name(), "compose");
}

TEST(PolymorphicNeuronTest, SignatureThrows)
{
    aicpp::ComposeNeuron compose;

    EXPECT_THROW(
        compose.signature(),
        std::logic_error);
}

TEST(ConnectionTest, PolymorphicComposeInfersSignature)
{
    using IntegerUnaryNeuron =
        aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    IntegerUnaryNeuron f{
        "f",
        static_cast<IntegerUnaryNeuron::PointerFunction>(&hodel::increment)
    };

    IntegerUnaryNeuron g{
        "g",
        static_cast<IntegerUnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection fConnection{&f, {std::type_index{typeid(hodel::Integer)}}};
    aicpp::Connection gConnection{&g, {std::type_index{typeid(hodel::Integer)}}};

    aicpp::Connection expression{
        &compose,
        {fConnection, gConnection}
    };

    EXPECT_EQ(
        expression.signature(),
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Integer const&>()},
            aicpp::makeDslType<hodel::Integer>()));
}

TEST(ConnectionTest, PolymorphicOutputPreservesExpression)
{
    aicpp::ComposeNeuron compose;

    using UnaryNeuron =
        aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    UnaryNeuron f{
        "f",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    UnaryNeuron g{
        "g",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::Connection fConnection{
        &f, {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection gConnection{
        &g, {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection expression{
        &compose, {fConnection, gConnection}
    };

    std::any result = expression.output();

    ASSERT_EQ(result.type(), typeid(aicpp::Connection));

    auto const& preserved =
        std::any_cast<aicpp::Connection const&>(result);

    EXPECT_EQ(preserved.neuron(), &compose);
    EXPECT_EQ(preserved.inputs().size(), 2u);
}

TEST(ConnectionTest, ApplyUnaryNativeFunction)
{
    using UnaryNeuron =
        aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::Connection expression{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    auto result = expression.apply(std::any{hodel::Integer{3}});

    ASSERT_EQ(result.type(), typeid(hodel::Integer));
    EXPECT_EQ(
        std::any_cast<hodel::Integer>(result),
        hodel::Integer{4});
}

TEST(ConnectionTest, ApplyRejectsIncompatibleArgumentType)
{
    using UnaryNeuron =
        aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::Connection expression{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    EXPECT_THROW(
        expression.apply(std::any{hodel::Boolean{true}}),
        std::invalid_argument);
}

TEST(ConnectionTest, ApplyComposedFunction)
{
    using UnaryNeuron =
        aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection expression{
        &compose,
        {f, g}
    };

    auto result = expression.apply(std::any{hodel::Integer{3}});

    ASSERT_EQ(result.type(), typeid(hodel::Integer));
    EXPECT_EQ(
        std::any_cast<hodel::Integer>(result),
        hodel::Integer{5});
}

TEST(ComposeNeuron, ApplyRejectsNonConnectionArguments)
{
    aicpp::ComposeNeuron compose;

    EXPECT_THROW(
        compose.apply(
            {std::any{1}, std::any{2}},
            std::any{hodel::Integer{3}}),
        std::invalid_argument);
}

TEST(ConnectionTest, ApplyComposedFunctionRejectsIncompatibleArgument)
{
    using IntegerUnaryNeuron =
        aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    IntegerUnaryNeuron increment{
        "increment",
        static_cast<IntegerUnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection expression{
        &compose,
        {f, g}
    };

    EXPECT_THROW(
        expression.apply(std::any{hodel::Boolean{true}}),
        std::invalid_argument);
}

namespace
{
    hodel::Boolean isPositive(hodel::Integer const& value)
    {
        return value > 0;
    }

    hodel::Integer booleanToInteger(hodel::Boolean const& value)
    {
        return value ? 1 : 0;
    }
}

TEST(ConnectionTest, ApplyComposedFunctionWithDifferentIntermediateTypes)
{
    using IntegerToBooleanNeuron =
        aicpp::Neuron<hodel::Boolean, hodel::Integer const&>;

    using BooleanToIntegerNeuron =
        aicpp::Neuron<hodel::Integer, hodel::Boolean const&>;

    IntegerToBooleanNeuron g{
        "isPositive",
        static_cast<IntegerToBooleanNeuron::PointerFunction>(&isPositive)
    };

    BooleanToIntegerNeuron f{
        "booleanToInteger",
        static_cast<BooleanToIntegerNeuron::PointerFunction>(&booleanToInteger)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection gConnection{
        &g, {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection fConnection{
        &f, {std::type_index{typeid(hodel::Boolean)}}
    };

    aicpp::Connection expression{
        &compose, {fConnection, gConnection}
    };

    EXPECT_EQ(
        expression.signature(),
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Integer const&>()},
            aicpp::makeDslType<hodel::Integer>()));

    auto result = expression.apply(std::any{hodel::Integer{3}});

    ASSERT_EQ(result.type(), typeid(hodel::Integer));
    EXPECT_EQ(
        std::any_cast<hodel::Integer>(result),
        hodel::Integer{1});
}

TEST(ConnectionTest, ExpressionSupportsPolymorphicNeuron)
{
    using UnaryNeuron =
        aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection expression{
        &compose,
        {f, g}
    };

    EXPECT_EQ(
        expression.expression(),
        "compose(increment(s), increment(s))");
}

TEST(ConnectionTest, InputTypesSupportsPolymorphicNeuron)
{
    using UnaryNeuron = aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection expression{&compose, {f, g}};

    auto const types = expression.inputTypes();

    ASSERT_EQ(types.size(), 2);
    EXPECT_EQ(types[0], typeid(hodel::Integer));
    EXPECT_EQ(types[1], typeid(hodel::Integer));
}

TEST(ConnectionTest, ImmediateInputTypesDoesNotFlattenNestedConnections)
{
    using UnaryNeuron = aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection inner{&compose, {f, g}};
    aicpp::Connection outer{&compose, {inner, f}};

    auto const types = outer.immediateInputTypes();

    ASSERT_EQ(types.size(), 2);
    EXPECT_EQ(types[0], typeid(hodel::Integer));
    EXPECT_EQ(types[1], typeid(hodel::Integer));
}

TEST(ConnectionTest, ExpectedInputTypesSupportsNestedPolymorphicNeuron)
{
    using UnaryNeuron = aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection inner{&compose, {f, g}};
    aicpp::Connection outer{&compose, {inner, f}};

    auto const types = outer.expectedInputTypes();

    ASSERT_EQ(types.size(), 3);
    EXPECT_EQ(types[0], typeid(hodel::Integer));
    EXPECT_EQ(types[1], typeid(hodel::Integer));
    EXPECT_EQ(types[2], typeid(hodel::Integer));
}

TEST(ConnectionTest, ExpectedInputTypesSupportsDifferentIntermediateTypes)
{
    using IntegerToBooleanNeuron =
        aicpp::Neuron<hodel::Boolean, hodel::Integer const&>;

    using BooleanToIntegerNeuron =
        aicpp::Neuron<hodel::Integer, hodel::Boolean const&>;

    IntegerToBooleanNeuron isPositive{
        "isPositive",
        [](hodel::Integer const& value) -> hodel::Boolean {
            return value > 0;
        }
    };

    BooleanToIntegerNeuron booleanToInteger{
        "booleanToInteger",
        [](hodel::Boolean const& value) -> hodel::Integer {
            return value ? 1 : 0;
        }
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection g{
        &isPositive,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection f{
        &booleanToInteger,
        {std::type_index{typeid(hodel::Boolean)}}
    };

    aicpp::Connection expression{&compose, {f, g}};

    auto const types = expression.expectedInputTypes();

    ASSERT_EQ(types.size(), 2);
    EXPECT_EQ(types[0], typeid(hodel::Boolean));
    EXPECT_EQ(types[1], typeid(hodel::Integer));
}

TEST(ConnectionTest, OutputEvaluatesNativeNeuronWithPolymorphicInput)
{
    using UnaryNeuron = aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection expression{&compose, {f, g}};

    auto const output = expression.output();

    ASSERT_EQ(output.type(), typeid(aicpp::Connection));

    auto const& preservedExpression = std::any_cast<aicpp::Connection const&>(output);

    EXPECT_EQ(preservedExpression.signature(), expression.signature());
}

TEST(ConnectionTest, OutputPreservesNestedPolymorphicComposition)
{
    using UnaryNeuron = aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection inner{&compose, {f, g}};
    aicpp::Connection outer{&compose, {inner, f}};

    auto const output = outer.output();

    ASSERT_EQ(output.type(), typeid(aicpp::Connection));

    auto const& preservedExpression =
        std::any_cast<aicpp::Connection const&>(output);

    EXPECT_EQ(preservedExpression.signature(), outer.signature());
}

TEST(ConnectionTest, ApplyEvaluatesNestedPolymorphicComposition)
{
    using UnaryNeuron = aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection inner{&compose, {f, g}};
    aicpp::Connection outer{&compose, {inner, f}};

    auto const result = outer.apply(std::any{hodel::Integer{3}});

    ASSERT_EQ(result.type(), typeid(hodel::Integer));
    EXPECT_EQ(std::any_cast<hodel::Integer>(result), 6);
}

TEST(ConnectionTest, ReplaceNeuronInsidePolymorphicComposition)
{
    using UnaryNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&
    >;

    UnaryNeuron increment1{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    UnaryNeuron increment2{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &increment1,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{
        &increment1,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection expression{&compose, {f, g}};

    auto const originalSignature = expression.signature();

    EXPECT_TRUE(expression.replace(&increment2));

    EXPECT_EQ(expression.neuron(), &compose);
    EXPECT_EQ(expression.signature(), originalSignature);

    auto const& inputs = expression.inputs();

    ASSERT_EQ(inputs.size(), 2);

    EXPECT_EQ(
        std::any_cast<aicpp::Connection const&>(inputs[0]).neuron(),
        &increment2
    );

    EXPECT_EQ(
        std::any_cast<aicpp::Connection const&>(inputs[1]).neuron(),
        &increment2
    );
}

TEST(ConnectionTest, ReplacePolymorphicNeuronWithMatchingSignature)
{
    using UnaryNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&
    >;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose1;
    aicpp::ComposeNeuron compose2;

    aicpp::Connection f{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection expression{&compose1, {f, g}};

    auto const originalSignature = expression.signature();

    EXPECT_TRUE(expression.replace(&compose2));
    EXPECT_EQ(expression.neuron(), &compose2);
    EXPECT_EQ(expression.signature(), originalSignature);
}

class DifferentComposeNeuron : public aicpp::PolymorphicNeuron
{
public:
    std::string const& name() const override
    {
        static const std::string neuronName{"compose"};
        return neuronName;
    }

    aicpp::DslType inferSignature(
        std::vector<aicpp::DslType> const& arguments
    ) const override
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("Expected two arguments");

        // Signature volontairement différente :
        // Integer -> Boolean, indépendamment de la signature de composition.
        return aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Integer>()},
            aicpp::makeDslType<hodel::Boolean>()
        );
    }

    std::any apply(
        std::vector<std::any> const&,
        std::any const&
    ) const override
    {
        throw std::logic_error("Not used in this test");
    }
};

TEST(ConnectionTest, ReplacePolymorphicNeuronRejectsDifferentSignature)
{
    using UnaryNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&
    >;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;
    DifferentComposeNeuron differentCompose;

    aicpp::Connection f{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection expression{&compose, {f, g}};

    auto const originalSignature = expression.signature();
    auto const originalHash = expression.hash();

    EXPECT_FALSE(expression.replace(&differentCompose));
    EXPECT_EQ(expression.neuron(), &compose);
    EXPECT_EQ(expression.signature(), originalSignature);
    EXPECT_EQ(expression.hash(), originalHash);
}

TEST(ConnectionTest, ToJsonSupportsPolymorphicNeuron)
{
    using UnaryNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&
    >;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection expression{&compose, {f, g}};

    auto const json = expression.toJson();

    ASSERT_TRUE(json.is_object());

    auto const& object = json.as_object();

    ASSERT_TRUE(object.contains("neuron"));
    ASSERT_TRUE(object.contains("inputs"));
    ASSERT_TRUE(object.contains("types"));

    auto const& neuron = object.at("neuron");

    ASSERT_TRUE(neuron.is_object());

    auto const& neuronObject = neuron.as_object();

    ASSERT_TRUE(neuronObject.contains("name"));
    EXPECT_EQ(neuronObject.at("name").as_string(), "compose");

    ASSERT_TRUE(neuronObject.contains("polymorphic"));
    EXPECT_TRUE(neuronObject.at("polymorphic").as_bool());

    EXPECT_EQ(object.at("inputs").as_array().size(), 2);
    EXPECT_EQ(object.at("types").as_array().size(), 2);
}

TEST(ConnectionTest, ToJsonSupportsNestedPolymorphicComposition)
{
    using UnaryNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&
    >;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection inner{&compose, {f, g}};
    aicpp::Connection outer{&compose, {inner, f}};

    auto const json = outer.toJson();

    ASSERT_TRUE(json.is_object());

    auto const& inputs = json.as_object().at("inputs").as_array();

    ASSERT_EQ(inputs.size(), 2);
    ASSERT_TRUE(inputs[0].is_object());

    auto const& innerJson = inputs[0].as_object();

    ASSERT_TRUE(innerJson.contains("neuron"));
    EXPECT_EQ(
        innerJson.at("neuron").as_object().at("name").as_string(),
        "compose"
    );

    EXPECT_EQ(innerJson.at("inputs").as_array().size(), 2);
}

TEST(NeuronTest, ToJsonContainsNameAndSignature)
{
    using AddNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&,
        hodel::Integer const&
    >;

    AddNeuron add{
        "add",
        static_cast<AddNeuron::PointerFunction>(&hodel::add)
    };

    auto const json = add.toJson();

    ASSERT_TRUE(json.is_object());

    auto const& object = json.as_object();

    ASSERT_TRUE(object.contains("name"));
    EXPECT_EQ(object.at("name").as_string(), "add");

    ASSERT_TRUE(object.contains("inputTypes"));
    EXPECT_EQ(object.at("inputTypes").as_array().size(), 2);

    ASSERT_TRUE(object.contains("outputType"));
    EXPECT_EQ(
        object.at("outputType").as_string(),
        std::string(typeid(hodel::Integer).name())
    );
}

TEST(ConnectionTest, DotSupportsPolymorphicComposition)
{
    using IncrementNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&
    >;

    IncrementNeuron increment{
        "increment",
        static_cast<IncrementNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection const connection{
        &compose,
        {
            aicpp::Connection{&increment, {hodel::Integer{0}}},
            aicpp::Connection{&increment, {hodel::Integer{0}}}
        }
    };

    auto const [dot, nextIndex] = connection.dot();

    EXPECT_NE(dot.find("compose"), std::string::npos);
    EXPECT_NE(dot.find("increment"), std::string::npos);
    EXPECT_GT(nextIndex, 0);
}

TEST(ConnectionTest, DotSupportsNestedPolymorphicComposition)
{
    using IncrementNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&
    >;

    IncrementNeuron increment{
        "increment",
        static_cast<IncrementNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    // inner(x) = increment(increment(x))
    aicpp::Connection const inner{
        &compose,
        {
            aicpp::Connection{&increment, {hodel::Integer{0}}},
            aicpp::Connection{&increment, {hodel::Integer{0}}}
        }
    };

    // outer(x) = inner(inner(x))
    aicpp::Connection const outer{
        &compose,
        {inner, inner}
    };

    auto const [dot, nextIndex] = outer.dot();

    EXPECT_NE(dot.find("compose"), std::string::npos);
    EXPECT_NE(dot.find("increment"), std::string::npos);
    EXPECT_GT(nextIndex, 0);
}

TEST(ConnectionTest, DotSupportsCompositionWithDifferentIntermediateTypes)
{
    using IsPositiveNeuron = aicpp::Neuron<
        hodel::Boolean,
        hodel::Integer const&
    >;

    using BooleanToIntegerNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Boolean const&
    >;

    IsPositiveNeuron isPositive{
        "isPositive",
        [](hodel::Integer const& value) {
            return value > 0;
        }
    };

    BooleanToIntegerNeuron booleanToInteger{
        "booleanToInteger",
        [](hodel::Boolean const& value) {
            return value ? hodel::Integer{1} : hodel::Integer{0};
        }
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection const connection{
        &compose,
        {
            aicpp::Connection{
                &booleanToInteger,
                {hodel::Boolean{false}}
            },
            aicpp::Connection{
                &isPositive,
                {hodel::Integer{0}}
            }
        }
    };

    auto const [dot, nextIndex] = connection.dot();

    auto const outputLabel = std::string{
        typeid(hodel::Integer).name()
    };

    EXPECT_NE(
        dot.find("label=\"" + outputLabel + "\""),
        std::string::npos
    );

    EXPECT_NE(dot.find("compose"), std::string::npos);
    EXPECT_NE(dot.find("isPositive"), std::string::npos);
    EXPECT_NE(dot.find("booleanToInteger"), std::string::npos);
    EXPECT_GT(nextIndex, 0);
}

TEST(ConnectionTest, ExpectedInputTypesHandlesNestedPolymorphicComposition)
{
    using UnaryNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&
    >;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection inner{&compose, {f, f}};
    aicpp::Connection outer{&compose, {inner, f}};

    auto const types = outer.expectedInputTypes();

    ASSERT_EQ(types.size(), 3);

    for (auto const& type : types)
        EXPECT_EQ(type, typeid(hodel::Integer));
}

TEST(ConnectionTest, ImmediateInputTypesHandlesDifferentIntermediateTypes)
{
    using IsPositiveNeuron = aicpp::Neuron<
        hodel::Boolean,
        hodel::Integer const&
    >;

    using BooleanToIntegerNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Boolean const&
    >;

    IsPositiveNeuron isPositive{
        "isPositive",
        [](hodel::Integer const& value) {
            return value > 0;
        }
    };

    BooleanToIntegerNeuron booleanToInteger{
        "booleanToInteger",
        [](hodel::Boolean const& value) {
            return value ? hodel::Integer{1} : hodel::Integer{0};
        }
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &booleanToInteger,
        {std::type_index{typeid(hodel::Boolean)}}
    };

    aicpp::Connection g{
        &isPositive,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection inner{&compose, {f, g}};
    aicpp::Connection outer{&compose, {inner, f}};

    auto const types = outer.immediateInputTypes();

    ASSERT_EQ(types.size(), 2);
    EXPECT_EQ(types[0], typeid(hodel::Integer));
    EXPECT_EQ(types[1], typeid(hodel::Integer));
}

TEST(ConnectionTest, ReplaceNeuronInsideNestedPolymorphicComposition)
{
    using UnaryNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&
    >;

    UnaryNeuron increment1{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    UnaryNeuron increment2{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection f{
        &increment1,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection g{&compose, {f, f}};
    aicpp::Connection expression{&compose, {g, f}};

    auto const originalSignature = expression.signature();

    EXPECT_TRUE(expression.replace(&increment2));

    EXPECT_EQ(expression.signature(), originalSignature);

    auto const inputs = expression.inputs();

    ASSERT_EQ(inputs.size(), 2);

    auto const& replacedInner =
        std::any_cast<aicpp::Connection const&>(inputs[0]);

    auto const& replacedOuterInput =
        std::any_cast<aicpp::Connection const&>(inputs[1]);

    EXPECT_EQ(replacedInner.neuron(), &compose);
    EXPECT_EQ(replacedOuterInput.neuron(), &increment2);

    auto const innerInputs = replacedInner.inputs();

    ASSERT_EQ(innerInputs.size(), 2);

    for (auto const& input : innerInputs)
    {
        auto const& connection =
            std::any_cast<aicpp::Connection const&>(input);

        EXPECT_EQ(connection.neuron(), &increment2);
    }

        aicpp::Connection expectedF{
        &increment2,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection expectedG{&compose, {expectedF, expectedF}};
    aicpp::Connection expectedExpression{&compose, {expectedG, expectedF}};

    EXPECT_EQ(expression.hash(), expectedExpression.hash());
    EXPECT_TRUE(expression == expectedExpression);
}

TEST(ConnectionTest, ApplySupportsNestedPolymorphicCompositionWithDifferentTypes)
{
    using IsPositiveNeuron = aicpp::Neuron<
        hodel::Boolean,
        hodel::Integer const&
    >;

    using BooleanToIntegerNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Boolean const&
    >;

    IsPositiveNeuron isPositive{
        "isPositive",
        [](hodel::Integer const& value) {
            return value > 0;
        }
    };

    BooleanToIntegerNeuron booleanToInteger{
        "booleanToInteger",
        [](hodel::Boolean const& value) {
            return value ? hodel::Integer{1} : hodel::Integer{0};
        }
    };

    aicpp::ComposeNeuron compose;

    // inner(x) = booleanToInteger(isPositive(x))
    aicpp::Connection const inner{
        &compose,
        {
            aicpp::Connection{
                &booleanToInteger,
                {std::type_index{typeid(hodel::Boolean)}}
            },
            aicpp::Connection{
                &isPositive,
                {std::type_index{typeid(hodel::Integer)}}
            }
        }
    };

    // outer(x) = inner(inner(x))
    aicpp::Connection const outer{
        &compose,
        {inner, inner}
    };

    EXPECT_EQ(outer.signature().inputs().size(), 1);
    EXPECT_EQ(
        outer.signature().inputs().front().nativeType(),
        typeid(hodel::Integer)
    );
    EXPECT_EQ(outer.signature().output().nativeType(), typeid(hodel::Integer));

    auto const result = outer.apply(std::any{hodel::Integer{5}});

    ASSERT_EQ(result.type(), typeid(hodel::Integer));
    EXPECT_EQ(std::any_cast<hodel::Integer>(result), 1);
}

TEST(ConnectionTest, ApplyRejectsWrongTypeForNestedPolymorphicComposition)
{
    using IsPositiveNeuron = aicpp::Neuron<
        hodel::Boolean,
        hodel::Integer const&
    >;

    using BooleanToIntegerNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Boolean const&
    >;

    IsPositiveNeuron isPositive{
        "isPositive",
        [](hodel::Integer const& value) {
            return value > 0;
        }
    };

    BooleanToIntegerNeuron booleanToInteger{
        "booleanToInteger",
        [](hodel::Boolean const& value) {
            return value ? hodel::Integer{1} : hodel::Integer{0};
        }
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection const inner{
        &compose,
        {
            aicpp::Connection{
                &booleanToInteger,
                {std::type_index{typeid(hodel::Boolean)}}
            },
            aicpp::Connection{
                &isPositive,
                {std::type_index{typeid(hodel::Integer)}}
            }
        }
    };

    aicpp::Connection const outer{
        &compose,
        {inner, inner}
    };

    EXPECT_THROW(
        outer.apply(std::any{hodel::Boolean{true}}),
        std::invalid_argument
    );
}

TEST(ConnectionTest, OutputPreservesNestedPolymorphicCompositionWithDifferentTypes)
{
    using IsPositiveNeuron = aicpp::Neuron<
        hodel::Boolean,
        hodel::Integer const&
    >;

    using BooleanToIntegerNeuron = aicpp::Neuron<
        hodel::Integer,
        hodel::Boolean const&
    >;

    IsPositiveNeuron isPositive{
        "isPositive",
        [](hodel::Integer const& value) {
            return value > 0;
        }
    };

    BooleanToIntegerNeuron booleanToInteger{
        "booleanToInteger",
        [](hodel::Boolean const& value) {
            return value ? hodel::Integer{1} : hodel::Integer{0};
        }
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection const inner{
        &compose,
        {
            aicpp::Connection{
                &booleanToInteger,
                {std::type_index{typeid(hodel::Boolean)}}
            },
            aicpp::Connection{
                &isPositive,
                {std::type_index{typeid(hodel::Integer)}}
            }
        }
    };

    aicpp::Connection const outer{
        &compose,
        {inner, inner}
    };

    auto const result = outer.output();

    ASSERT_EQ(result.type(), typeid(aicpp::Connection));

    auto const& outputConnection =
        std::any_cast<aicpp::Connection const&>(result);

    EXPECT_EQ(outputConnection.signature(), outer.signature());
}

TEST(ChainNeuron, InfersSignature)
{
    aicpp::ChainNeuron chain;

    auto const h = aicpp::DslType::function(
        {aicpp::makeDslType<int>()},
        aicpp::makeDslType<bool>());

    auto const g = aicpp::DslType::function(
        {aicpp::makeDslType<bool>()},
        aicpp::makeDslType<int>());

    auto const f = aicpp::DslType::function(
        {aicpp::makeDslType<int>()},
        aicpp::makeDslType<bool>());

    auto const actual = chain.inferSignature({h, g, f});

    auto const expected = aicpp::DslType::function(
        {aicpp::makeDslType<int>()},
        aicpp::makeDslType<bool>());

    EXPECT_EQ(actual, expected);
}

TEST(ChainNeuron, RejectsWrongNumberOfArguments)
{
    aicpp::ChainNeuron chain;

    EXPECT_THROW(
        chain.inferSignature({}),
        std::invalid_argument);

    EXPECT_THROW(
        chain.inferSignature({
            aicpp::makeDslType<bool>()
        }),
        std::invalid_argument);

    EXPECT_THROW(
        chain.inferSignature({
            aicpp::makeDslType<bool>(),
            aicpp::makeDslType<bool>()
        }),
        std::invalid_argument);
}

TEST(ChainNeuron, RejectsIncompatibleSignatures)
{
    aicpp::ChainNeuron chain;

    auto const h = aicpp::DslType::function(
        {aicpp::makeDslType<bool>()},
        aicpp::makeDslType<bool>());

    auto const g = aicpp::DslType::function(
        {aicpp::makeDslType<int>()},
        aicpp::makeDslType<int>());

    auto const f = aicpp::DslType::function(
        {aicpp::makeDslType<int>()},
        aicpp::makeDslType<bool>());

    EXPECT_THROW(
        chain.inferSignature({h, g, f}),
        std::invalid_argument);
}

TEST(ConnectionTest, ChainAppliesThreeFunctionsInOrder)
{
    using UnaryNeuron =
        aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    UnaryNeuron f{
        "f",
        [](hodel::Integer const& x) -> hodel::Integer {
            return x + 1;
        }
    };

    UnaryNeuron g{
        "g",
        [](hodel::Integer const& x) -> hodel::Integer {
            return x * 2;
        }
    };

    UnaryNeuron h{
        "h",
        [](hodel::Integer const& x) -> hodel::Integer {
            return x + 3;
        }
    };

    aicpp::Connection fConnection{
        &f, {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection gConnection{
        &g, {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection hConnection{
        &h, {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::ChainNeuron chain;

    aicpp::Connection expression{
        &chain,
        {hConnection, gConnection, fConnection}
    };

    auto result = expression.apply(std::any{hodel::Integer{1}});

    ASSERT_EQ(result.type(), typeid(hodel::Integer));
    EXPECT_EQ(
        std::any_cast<hodel::Integer>(result),
        hodel::Integer{7});
}

TEST(ForkNeuron, InfersSignature)
{
    aicpp::ForkNeuron fork;

    auto const outer = aicpp::DslType::function(
        {
            aicpp::makeDslType<bool>(),
            aicpp::makeDslType<int>()
        },
        aicpp::makeDslType<bool>());

    auto const a = aicpp::DslType::function(
        {aicpp::makeDslType<int>()},
        aicpp::makeDslType<bool>());

    auto const b = aicpp::DslType::function(
        {aicpp::makeDslType<int>()},
        aicpp::makeDslType<int>());

    auto const actual = fork.inferSignature({outer, a, b});

    auto const expected = aicpp::DslType::function(
        {aicpp::makeDslType<int>()},
        aicpp::makeDslType<bool>());

    EXPECT_EQ(actual, expected);
}

TEST(ForkNeuron, RejectsWrongNumberOfArguments)
{
    aicpp::ForkNeuron fork;

    EXPECT_THROW(
        fork.inferSignature({}),
        std::invalid_argument);

    EXPECT_THROW(
        fork.inferSignature({
            aicpp::makeDslType<bool>()
        }),
        std::invalid_argument);

    EXPECT_THROW(
        fork.inferSignature({
            aicpp::makeDslType<bool>(),
            aicpp::makeDslType<bool>()
        }),
        std::invalid_argument);
}

TEST(ConnectionTest, ForkAppliesBothBranchesToSameInput)
{
    using UnaryNeuron =
        aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    using BinaryNeuron =
        aicpp::Neuron<
            hodel::Integer,
            hodel::Integer const&,
            hodel::Integer const&
        >;

    UnaryNeuron a{
        "a",
        [](hodel::Integer const& x) -> hodel::Integer {
            return x + 1;
        }
    };

    UnaryNeuron b{
        "b",
        [](hodel::Integer const& x) -> hodel::Integer {
            return x * 2;
        }
    };

    BinaryNeuron outer{
        "outer",
        static_cast<BinaryNeuron::PointerFunction>(&hodel::add)
    };

    aicpp::Connection aConnection{
        &a, {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection bConnection{
        &b, {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection outerConnection{
        &outer,
        {
            std::type_index{typeid(hodel::Integer)},
            std::type_index{typeid(hodel::Integer)}
        }
    };

    aicpp::ForkNeuron fork;

    aicpp::Connection expression{
        &fork,
        {outerConnection, aConnection, bConnection}
    };

    auto result = expression.apply(std::any{hodel::Integer{3}});

    ASSERT_EQ(result.type(), typeid(hodel::Integer));
    EXPECT_EQ(
        std::any_cast<hodel::Integer>(result),
        hodel::Integer{10});
}

TEST(ExtractNeuron, InfersSignature)
{
    aicpp::ExtractNeuron extract;

    auto const container = aicpp::makeDslType<hodel::GridVector>();

    auto const condition = aicpp::DslType::function(
        {aicpp::makeDslType<hodel::Grid>()},
        aicpp::makeDslType<hodel::Boolean>());

    auto const actual = extract.inferSignature(
        {container, condition});

    auto const expected = aicpp::DslType::function(
        {aicpp::makeDslType<hodel::GridVector>()},
        aicpp::makeDslType<hodel::Grid>());

    EXPECT_EQ(actual, expected);
}

TEST(ExtractNeuron, RejectsWrongNumberOfArguments)
{
    aicpp::ExtractNeuron extract;

    EXPECT_THROW(
        extract.inferSignature({}),
        std::invalid_argument);

    EXPECT_THROW(
        extract.inferSignature({
            aicpp::makeDslType<hodel::GridVector>()
        }),
        std::invalid_argument);

    EXPECT_THROW(
        extract.inferSignature({
            aicpp::makeDslType<hodel::GridVector>(),
            aicpp::makeDslType<hodel::Boolean>(),
            aicpp::makeDslType<hodel::Grid>()
        }),
        std::invalid_argument);
}

TEST(ExtractNeuron, RejectsIncompatibleCondition)
{
    aicpp::ExtractNeuron extract;

    auto const container = aicpp::makeDslType<hodel::GridVector>();

    auto const wrongInput = aicpp::DslType::function(
        {aicpp::makeDslType<hodel::Integer>()},
        aicpp::makeDslType<hodel::Boolean>());

    EXPECT_THROW(
        extract.inferSignature({container, wrongInput}),
        std::invalid_argument);
}

TEST(ExtractNeuron, RejectsNonBooleanCondition)
{
    aicpp::ExtractNeuron extract;

    auto const container = aicpp::makeDslType<hodel::GridVector>();

    auto const wrongOutput = aicpp::DslType::function(
        {aicpp::makeDslType<hodel::Grid>()},
        aicpp::makeDslType<hodel::Integer>());

    EXPECT_THROW(
        extract.inferSignature({container, wrongOutput}),
        std::invalid_argument);
}

TEST(IntegrationTest, RegistryContains662c240aNeurons)
{
    auto registry = aicpp::makeNeuronRegistry();

    auto containsNeuron = [&registry](std::string const& name)
    {
        return std::any_of(
            registry.begin(),
            registry.end(),
            [&name](auto const& entry)
            {
                return entry.second->name() == name;
            });
    };

    EXPECT_TRUE(containsNeuron("vsplit"));
    EXPECT_TRUE(containsNeuron("equality"));
    EXPECT_TRUE(containsNeuron("dmirror"));
    EXPECT_TRUE(containsNeuron("identity"));
    EXPECT_TRUE(containsNeuron("fork"));
    EXPECT_TRUE(containsNeuron("compose"));
    EXPECT_TRUE(containsNeuron("flip"));
    EXPECT_TRUE(containsNeuron("extract"));
}

TEST(IntegrationTest, Build662c240aExpression)
{
    auto registry = aicpp::makeNeuronRegistry();

    auto findNeuron = [&registry](aicpp::DslType const& expected)
        -> aicpp::NeuronBase const*
    {
        auto it = std::find_if(
            registry.begin(),
            registry.end(),
            [&expected](auto const& entry)
            {
                return !entry.second->isPolymorphic()
                    && entry.second->signature() == expected;
            });

        if (it == registry.end())
        {
            throw std::runtime_error(
                "Neuron not found for expected signature");
        }

        return it->second;
    };

    using namespace hodel;

    auto const gridType = aicpp::makeDslType<Grid>();
    auto const booleanType = aicpp::makeDslType<Boolean>();

    auto const unaryGrid = aicpp::DslType::function(
        {gridType},
        gridType);

    auto const binaryGridToBoolean = aicpp::DslType::function(
        {gridType, gridType},
        booleanType);

    auto const unaryBoolean = aicpp::DslType::function(
        {booleanType},
        booleanType);

    auto const* equality = findNeuron(binaryGridToBoolean);
    auto const* dmirror = findNeuron(unaryGrid);
    auto const* identity = findNeuron(unaryGrid);
    auto const* flip = findNeuron(unaryBoolean);

    aicpp::Connection equalityConnection{
        equality,
        {
            std::type_index{typeid(Grid)},
            std::type_index{typeid(Grid)}
        }
    };

    aicpp::Connection dmirrorConnection{
        dmirror,
        {std::type_index{typeid(Grid)}}
    };

    aicpp::Connection identityConnection{
        identity,
        {std::type_index{typeid(Grid)}}
    };

    aicpp::ForkNeuron fork;

    aicpp::Connection x2{
        &fork,
        {
            equalityConnection,
            dmirrorConnection,
            identityConnection
        }
    };

    aicpp::Connection flipConnection{
        flip,
        {std::type_index{typeid(Boolean)}}
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection x3{
        &compose,
        {flipConnection, x2}
    };

    EXPECT_EQ(
        x2.signature(),
        aicpp::DslType::function({gridType}, booleanType));

    EXPECT_EQ(
        x3.signature(),
        aicpp::DslType::function({gridType}, booleanType));
}

TEST(IntegrationTest, Solve662c240aExample1)
{
    auto registry = aicpp::makeNeuronRegistry();

    // Recherche un neurone par son nom et sa signature exacte.
    auto findNeuron = [&registry](
        std::string const& name,
        aicpp::DslType const& expected)
        -> aicpp::NeuronBase const*
    {
        auto it = std::find_if(
            registry.begin(),
            registry.end(),
            [&name, &expected](auto const& entry)
            {
                return entry.second->name() == name
                    && !entry.second->isPolymorphic()
                    && entry.second->signature() == expected;
            });

        if (it == registry.end())
        {
            throw std::runtime_error(
                "Neuron not found: " + name);
        }

        return it->second;
    };

    auto const gridType =
        aicpp::makeDslType<hodel::Grid>();
    auto const gridVectorType =
        aicpp::makeDslType<hodel::GridVector>();
    auto const booleanType =
        aicpp::makeDslType<hodel::Boolean>();
    auto const integerType =
        aicpp::makeDslType<hodel::Integer>();

    auto const unaryGrid = aicpp::DslType::function(
        {gridType},
        gridType);

    auto const binaryGridToBoolean = aicpp::DslType::function(
        {gridType, gridType},
        booleanType);

    auto const unaryBoolean = aicpp::DslType::function(
        {booleanType},
        booleanType);

    auto const binaryGridIntegerToGridVector =
        aicpp::DslType::function(
            {gridType, integerType},
            gridVectorType);

    auto const* equality =
        findNeuron("equality", binaryGridToBoolean);
    auto const* dmirror =
        findNeuron("dmirror", unaryGrid);
    auto const* identity =
        findNeuron("identity", unaryGrid);
    auto const* flip =
        findNeuron("flip", unaryBoolean);
    auto const* vsplit =
        findNeuron("vsplit", binaryGridIntegerToGridVector);

    // x2 = fork(equality, dmirror, identity)
    aicpp::Connection equalityConnection{
        equality,
        {
            std::type_index{typeid(hodel::Grid)},
            std::type_index{typeid(hodel::Grid)}
        }
    };

    aicpp::Connection dmirrorConnection{
        dmirror,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::Connection identityConnection{
        identity,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::ForkNeuron fork;

    aicpp::Connection x2{
        &fork,
        {
            equalityConnection,
            dmirrorConnection,
            identityConnection
        }
    };

    // x3 = compose(flip, x2)
    aicpp::Connection flipConnection{
        flip,
        {std::type_index{typeid(hodel::Boolean)}}
    };

    aicpp::ComposeNeuron compose;

    aicpp::Connection x3{
        &compose,
        {flipConnection, x2}
    };

    hodel::Grid const input1{
        {2, 2, 2},
        {2, 2, 3},
        {2, 3, 3},
        {5, 7, 7},
        {7, 5, 5},
        {7, 5, 5},
        {8, 8, 1},
        {1, 8, 1},
        {1, 8, 1}
    };

    hodel::Grid const output1{
        {8, 8, 1},
        {1, 8, 1},
        {1, 8, 1}
    };

    // x1 = vsplit(input1, THREE)
    auto const splitResult = vsplit->invoke(
        {
            std::any{input1},
            std::any{hodel::Integer{3}}
        });

    ASSERT_EQ(splitResult.type(), typeid(hodel::GridVector));

    auto const grids =
        std::any_cast<hodel::GridVector>(splitResult);

    ASSERT_EQ(grids.size(), 3u);

    // O = extract(x1, x3)
    aicpp::ExtractNeuron extract;

    auto result = extract.apply(
        {std::any{grids}, std::any{x3}},
        std::any{grids}
    );

    ASSERT_EQ(result.type(), typeid(hodel::Grid));
    EXPECT_EQ(std::any_cast<hodel::Grid>(result), output1);
}

TEST(ConnectionTest, NativeFunctionCanBeStoredAndApplied)
{
    auto registry = aicpp::makeNeuronRegistry();

    // Recherche un neurone par son nom et sa signature exacte.
    auto findNeuron = [&registry](
        std::string const& name,
        aicpp::DslType const& expected)
        -> aicpp::NeuronBase const*
    {
        auto it = std::find_if(
            registry.begin(),
            registry.end(),
            [&name, &expected](auto const& entry)
            {
                return entry.second->name() == name
                    && !entry.second->isPolymorphic()
                    && entry.second->signature() == expected;
            });

        if (it == registry.end())
        {
            throw std::runtime_error(
                "Neuron not found: " + name);
        }

        return it->second;
    };

    // Arrange: find identity : Grid -> Grid in the registry.
    auto const& identity = findNeuron(
        "identity",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    // Build a Connection representing identity : Grid -> Grid.
    aicpp::Connection function{
        identity,
        {std::type_index{typeid(hodel::Grid)}}
    };

    // Act: store and recover the function through std::any.
    std::any stored = function;
    auto const& recovered = std::any_cast<aicpp::Connection const&>(stored);

    // Assert: the function signature is preserved.
    EXPECT_EQ(
        recovered.signature(),
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    // Assert: the recovered function can still be applied.
    hodel::Grid input{{1, 2}, {3, 4}};

    auto result = std::any_cast<hodel::Grid>(
        recovered.apply(std::any{input})
    );

    EXPECT_EQ(result, input);
}

TEST(FunctionValueTest, CanStoreAndApplyIdentity)
{
    auto registry = aicpp::makeNeuronRegistry();

    // Recherche un neurone par son nom et sa signature exacte.
    auto findNeuron = [&registry](
        std::string const& name,
        aicpp::DslType const& expected)
        -> aicpp::NeuronBase const*
    {
        auto it = std::find_if(
            registry.begin(),
            registry.end(),
            [&name, &expected](auto const& entry)
            {
                return entry.second->name() == name
                    && !entry.second->isPolymorphic()
                    && entry.second->signature() == expected;
            });

        if (it == registry.end())
        {
            throw std::runtime_error(
                "Neuron not found: " + name);
        }

        return it->second;
    };

    // Arrange: identity représente Grid -> Grid.
    auto const& identity = findNeuron(
        "identity",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    aicpp::Connection connection{
        identity,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::FunctionValue functionValue{connection};

    // Act: stocker et récupérer la valeur fonctionnelle.
    std::any stored{functionValue};

    auto const& recovered =
        std::any_cast<aicpp::FunctionValue const&>(stored);

    // Assert: la signature est conservée.
    EXPECT_EQ(
        recovered.connection.signature(),
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    // Assert: la fonction reste applicable.
    hodel::Grid input{{1, 2}, {3, 4}};

    auto result = std::any_cast<hodel::Grid>(
        recovered.connection.apply(std::any{input})
    );

    EXPECT_EQ(result, input);
}

TEST(FunctionValueTest, FunctionSetCanStoreMultipleFunctions)
{
    auto registry = aicpp::makeNeuronRegistry();

    // Recherche un neurone par son nom et sa signature exacte.
    auto findNeuron = [&registry](
        std::string const& name,
        aicpp::DslType const& expected)
        -> aicpp::NeuronBase const*
    {
        auto it = std::find_if(
            registry.begin(),
            registry.end(),
            [&name, &expected](auto const& entry)
            {
                return entry.second->name() == name
                    && !entry.second->isPolymorphic()
                    && entry.second->signature() == expected;
            });

        if (it == registry.end())
        {
            throw std::runtime_error(
                "Neuron not found: " + name);
        }

        return it->second;
    };

    // Arrange: retrieve identity : Grid -> Grid.
    auto const& identity = findNeuron(
        "identity",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    // Retrieve vmirror : Grid -> Grid.
    auto const& vmirror = findNeuron(
        "vmirror",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    // Build function connections.
    aicpp::Connection identityConnection{
        identity,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::Connection vmirrorConnection{
        vmirror,
        {std::type_index{typeid(hodel::Grid)}}
    };

    // Wrap the connections as function values.
    aicpp::FunctionValue identityValue{identityConnection};
    aicpp::FunctionValue vmirrorValue{vmirrorConnection};

    // Act: store both functions in a collection.
    hodel::FunctionSet functions;
    functions.emplace_back(identityValue);
    functions.emplace_back(vmirrorValue);

    // Assert: both functions are stored.
    ASSERT_EQ(functions.size(), 2);

    // Assert: identity retains its signature.
    EXPECT_EQ(
        functions[0].connection.signature(),
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    // Assert: vmirror retains its signature.
    EXPECT_EQ(
        functions[1].connection.signature(),
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );
}

TEST(FunctionValueTest, InitsetAndInsertBuildFunctionSet)
{
    auto registry = aicpp::makeNeuronRegistry();

    // Recherche un neurone par son nom et sa signature exacte.
    auto findNeuron = [&registry](
        std::string const& name,
        aicpp::DslType const& expected)
        -> aicpp::NeuronBase const*
    {
        auto it = std::find_if(
            registry.begin(),
            registry.end(),
            [&name, &expected](auto const& entry)
            {
                return entry.second->name() == name
                    && !entry.second->isPolymorphic()
                    && entry.second->signature() == expected;
            });

        if (it == registry.end())
        {
            throw std::runtime_error(
                "Neuron not found: " + name);
        }

        return it->second;
    };

    auto const& identity = findNeuron(
        "identity",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    auto const& vmirror = findNeuron(
        "vmirror",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    aicpp::Connection identityConnection{
        identity,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::Connection vmirrorConnection{
        vmirror,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::FunctionValue identityValue{identityConnection};
    aicpp::FunctionValue vmirrorValue{vmirrorConnection};

    // initset(identity)
    auto functions = hodel::initset(identityValue);

    ASSERT_EQ(functions.size(), 1);

    EXPECT_EQ(
        functions[0].connection.signature(),
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    // insert(vmirror, functions)
    functions = hodel::insert(vmirrorValue, functions);

    ASSERT_EQ(functions.size(), 2);

    EXPECT_EQ(
        functions[1].connection.signature(),
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );
}

TEST(FunctionValueTest, InitsetAcceptsIdentityConnection)
{
    auto registry = aicpp::makeNeuronRegistry();

    // Recherche un neurone par son nom et sa signature exacte.
    auto findNeuron = [&registry](
        std::string const& name,
        aicpp::DslType const& expected)
        -> aicpp::NeuronBase const*
    {
        auto it = std::find_if(
            registry.begin(),
            registry.end(),
            [&name, &expected](auto const& entry)
            {
                return entry.second->name() == name
                    && !entry.second->isPolymorphic()
                    && entry.second->signature() == expected;
            });

        if (it == registry.end())
        {
            throw std::runtime_error(
                "Neuron not found: " + name);
        }

        return it->second;
    };

    // Arrange: retrieve identity : Grid -> Grid.
    auto const& identity = findNeuron(
        "identity",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    // Build a function expression representing identity.
    aicpp::Connection identityConnection{
        identity,
        {std::type_index{typeid(hodel::Grid)}}
    };

    // Wrap the function expression as a function value.
    aicpp::FunctionValue identityValue{identityConnection};

    // Retrieve initset(FunctionValue).
    auto const& initset = findNeuron(
        "initset",
        aicpp::DslType::function(
            {aicpp::makeDslType<aicpp::FunctionValue>()},
            aicpp::makeDslType<hodel::FunctionSet>()
        )
    );

    // Build initset(identity).
    aicpp::Connection expression{
        initset,
        {std::any{identityValue}}
    };

    // Assert: the expression has the expected signature.
    EXPECT_EQ(
        expression.signature(),
        aicpp::DslType::function(
            {aicpp::makeDslType<aicpp::FunctionValue>()},
            aicpp::makeDslType<hodel::FunctionSet>()
        )
    );
}

TEST(FunctionValueTest, InsertAcceptsFunctionValueAndFunctionSet)
{
    auto registry = aicpp::makeNeuronRegistry();

    // Recherche un neurone par son nom et sa signature exacte.
    auto findNeuron = [&registry](
        std::string const& name,
        aicpp::DslType const& expected)
        -> aicpp::NeuronBase const*
    {
        auto it = std::find_if(
            registry.begin(),
            registry.end(),
            [&name, &expected](auto const& entry)
            {
                return entry.second->name() == name
                    && !entry.second->isPolymorphic()
                    && entry.second->signature() == expected;
            });

        if (it == registry.end())
        {
            throw std::runtime_error(
                "Neuron not found: " + name);
        }

        return it->second;
    };

    auto const& identity = findNeuron(
        "identity",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    auto const& vmirror = findNeuron(
        "vmirror",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    auto const& initset = findNeuron(
        "initset",
        aicpp::DslType::function(
            {aicpp::makeDslType<aicpp::FunctionValue>()},
            aicpp::makeDslType<hodel::FunctionSet>()
        )
    );

    auto const& insert = findNeuron(
        "insert",
        aicpp::DslType::function(
            {
                aicpp::makeDslType<aicpp::FunctionValue>(),
                aicpp::makeDslType<hodel::FunctionSet>()
            },
            aicpp::makeDslType<hodel::FunctionSet>()
        )
    );

    // Represent identity and vmirror as function expressions.
    aicpp::Connection identityConnection{
        identity,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::Connection vmirrorConnection{
        vmirror,
        {std::type_index{typeid(hodel::Grid)}}
    };

    // Wrap the functions as values.
    aicpp::FunctionValue identityValue{identityConnection};
    aicpp::FunctionValue vmirrorValue{vmirrorConnection};

    // Build initset(identity).
    aicpp::Connection initialSet{
        initset,
        {std::any{identityValue}}
    };

    // Build insert(vmirror, initset(identity)).
    aicpp::Connection expression{
        insert,
        {
            std::any{vmirrorValue},
            std::any{initialSet}
        }
    };

    // Assert: the resulting expression has the expected signature.
    EXPECT_EQ(
        expression.signature(),
        aicpp::DslType::function(
            {
                aicpp::makeDslType<aicpp::FunctionValue>(),
                aicpp::makeDslType<hodel::FunctionSet>()
            },
            aicpp::makeDslType<hodel::FunctionSet>()
        )
    );
}

TEST(FunctionValueTest, InitsetAndInsertPreserveFunctionsAtRuntime)
{
    auto registry = aicpp::makeNeuronRegistry();

    // Recherche un neurone par son nom et sa signature exacte.
    auto findNeuron = [&registry](
        std::string const& name,
        aicpp::DslType const& expected)
        -> aicpp::NeuronBase const*
    {
        auto it = std::find_if(
            registry.begin(),
            registry.end(),
            [&name, &expected](auto const& entry)
            {
                return entry.second->name() == name
                    && !entry.second->isPolymorphic()
                    && entry.second->signature() == expected;
            });

        if (it == registry.end())
        {
            throw std::runtime_error(
                "Neuron not found: " + name);
        }

        return it->second;
    };

    auto const& identity = findNeuron(
        "identity",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    auto const& vmirror = findNeuron(
        "vmirror",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    auto const& initset = findNeuron(
        "initset",
        aicpp::DslType::function(
            {aicpp::makeDslType<aicpp::FunctionValue>()},
            aicpp::makeDslType<hodel::FunctionSet>()
        )
    );

    auto const& insert = findNeuron(
        "insert",
        aicpp::DslType::function(
            {
                aicpp::makeDslType<aicpp::FunctionValue>(),
                aicpp::makeDslType<hodel::FunctionSet>()
            },
            aicpp::makeDslType<hodel::FunctionSet>()
        )
    );

    aicpp::Connection identityConnection{
        identity,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::Connection vmirrorConnection{
        vmirror,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::FunctionValue identityValue{identityConnection};
    aicpp::FunctionValue vmirrorValue{vmirrorConnection};

    aicpp::Connection initialSet{
        initset,
        {std::any{identityValue}}
    };

    aicpp::Connection expression{
        insert,
        {
            std::any{vmirrorValue},
            std::any{initialSet}
        }
    };

    // Evaluate the complete expression.
    auto result = expression.output();

    auto const& functions =
        std::any_cast<hodel::FunctionSet const&>(result);

    ASSERT_EQ(functions.size(), 2);

    // Both functions must remain applicable.
    hodel::Grid input{{1, 2}, {3, 4}};

    auto identityResult = std::any_cast<hodel::Grid>(
        functions[0].connection.apply(std::any{input})
    );

    EXPECT_EQ(identityResult, input);

    auto vmirrorResult = std::any_cast<hodel::Grid>(
        functions[1].connection.apply(std::any{input})
    );

    EXPECT_EQ(
        vmirrorResult,
        hodel::vmirror(input)
    );
}

TEST(FunctionValueTest, InitsetAcceptsFunctionConnectionDirectly)
{
    auto registry = aicpp::makeNeuronRegistry();

    // Recherche un neurone par son nom et sa signature exacte.
    auto findNeuron = [&registry](
        std::string const& name,
        aicpp::DslType const& expected)
        -> aicpp::NeuronBase const*
    {
        auto it = std::find_if(
            registry.begin(),
            registry.end(),
            [&name, &expected](auto const& entry)
            {
                return entry.second->name() == name
                    && !entry.second->isPolymorphic()
                    && entry.second->signature() == expected;
            });

        if (it == registry.end())
        {
            throw std::runtime_error(
                "Neuron not found: " + name);
        }

        return it->second;
    };

    auto const& identity = findNeuron(
        "identity",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    auto const& initset = findNeuron(
        "initset",
        aicpp::DslType::function(
            {aicpp::makeDslType<aicpp::FunctionValue>()},
            aicpp::makeDslType<hodel::FunctionSet>()
        )
    );

    aicpp::Connection identityConnection{
        identity,
        {std::type_index{typeid(hodel::Grid)}}
    };

    // Pass the function connection directly.
    aicpp::Connection expression{
        initset,
        {std::any{identityConnection}}
    };

    auto result = expression.output();

    auto const& functions =
        std::any_cast<hodel::FunctionSet const&>(result);

    ASSERT_EQ(functions.size(), 1);

    hodel::Grid input{{1, 2}, {3, 4}};

    auto applied = std::any_cast<hodel::Grid>(
        functions.front().connection.apply(std::any{input})
    );

    EXPECT_EQ(applied, input);
}

TEST(FunctionValueTest, InsertAcceptsFunctionConnectionsDirectly)
{
    auto registry = aicpp::makeNeuronRegistry();

    // Recherche un neurone par son nom et sa signature exacte.
    auto findNeuron = [&registry](
        std::string const& name,
        aicpp::DslType const& expected)
        -> aicpp::NeuronBase const*
    {
        auto it = std::find_if(
            registry.begin(),
            registry.end(),
            [&name, &expected](auto const& entry)
            {
                return entry.second->name() == name
                    && !entry.second->isPolymorphic()
                    && entry.second->signature() == expected;
            });

        if (it == registry.end())
        {
            throw std::runtime_error(
                "Neuron not found: " + name);
        }

        return it->second;
    };

    auto const& identity = findNeuron(
        "identity",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    auto const& vmirror = findNeuron(
        "vmirror",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    auto const& initset = findNeuron(
        "initset",
        aicpp::DslType::function(
            {aicpp::makeDslType<aicpp::FunctionValue>()},
            aicpp::makeDslType<hodel::FunctionSet>()
        )
    );

    auto const& insert = findNeuron(
        "insert",
        aicpp::DslType::function(
            {
                aicpp::makeDslType<aicpp::FunctionValue>(),
                aicpp::makeDslType<hodel::FunctionSet>()
            },
            aicpp::makeDslType<hodel::FunctionSet>()
        )
    );

    aicpp::Connection identityConnection{
        identity,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::Connection vmirrorConnection{
        vmirror,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::Connection initialSet{
        initset,
        {std::any{identityConnection}}
    };

    aicpp::Connection expression{
        insert,
        {
            std::any{vmirrorConnection},
            std::any{initialSet}
        }
    };

    auto result = expression.output();

    auto const& functions =
        std::any_cast<hodel::FunctionSet const&>(result);

    ASSERT_EQ(functions.size(), 2);

    hodel::Grid input{{1, 2}, {3, 4}};

    auto identityResult = std::any_cast<hodel::Grid>(
        functions[0].connection.apply(std::any{input})
    );

    EXPECT_EQ(identityResult, input);

    auto vmirrorResult = std::any_cast<hodel::Grid>(
        functions[1].connection.apply(std::any{input})
    );

    EXPECT_EQ(vmirrorResult, hodel::vmirror(input));
}

TEST(FunctionValueTest, ProductCombinesFunctionsAndIntegers)
{
    auto registry = aicpp::makeNeuronRegistry();

    // Recherche un neurone par son nom et sa signature exacte.
    auto findNeuron = [&registry](
        std::string const& name,
        aicpp::DslType const& expected)
        -> aicpp::NeuronBase const*
    {
        auto it = std::find_if(
            registry.begin(),
            registry.end(),
            [&name, &expected](auto const& entry)
            {
                return entry.second->name() == name
                    && !entry.second->isPolymorphic()
                    && entry.second->signature() == expected;
            });

        if (it == registry.end())
        {
            throw std::runtime_error(
                "Neuron not found: " + name);
        }

        return it->second;
    };

    // Arrange: create two functions.
    auto const& identity = findNeuron(
        "identity",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    auto const& vmirror = findNeuron(
        "vmirror",
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    aicpp::Connection identityConnection{
        identity,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::Connection vmirrorConnection{
        vmirror,
        {std::type_index{typeid(hodel::Grid)}}
    };

    hodel::FunctionSet functions{
        aicpp::FunctionValue{identityConnection},
        aicpp::FunctionValue{vmirrorConnection}
    };

    hodel::IntegerSet integers{2, 3};

    // Act: construct the Cartesian product.
    hodel::FunctionIntegerPairVector result;

    for (auto const& function : functions)
    {
        for (auto const integer : integers)
        {
            result.emplace_back(function, integer);
        }
    }

    // Assert: every function is paired with every integer.
    ASSERT_EQ(result.size(), 4);

    EXPECT_EQ(result[0].second, 2);
    EXPECT_EQ(result[1].second, 3);
    EXPECT_EQ(result[2].second, 2);
    EXPECT_EQ(result[3].second, 3);

    EXPECT_EQ(
        result[0].first.connection.signature(),
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );

    EXPECT_EQ(
        result[2].first.connection.signature(),
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Grid>()},
            aicpp::makeDslType<hodel::Grid>()
        )
    );
}

namespace
{
    hodel::IntegerVector integerVector123()
    {
        return {1, 2, 3};
    }
    
    hodel::BooleanVector booleanVector123()
    {
        return {true, false, true};
    }

    hodel::GridVector gridVectorExample()
    {
        return {
            {
                {1, 2},
                {3, 4}
            },
            {
                {5, 6},
                {7, 8}
            }
        };
    }

    hodel::GridVector emptyGridVector()
    {
        return {};
    }

    hodel::GridVector gridVectorPortraitExample()
    {
        return {
            {
                {1, 2},
                {3, 4},
                {5, 6}
            },
            {
                {1, 2, 3},
                {4, 5, 6}
            },
            {
                {7},
                {8},
                {9}
            }
        };
    }

    hodel::ObjectVector objectVectorPortraitExample()
    {
        hodel::Object tallObject{
            {1, hodel::IntegerTuple{0, 0}},
            {1, hodel::IntegerTuple{0, 1}},
            {1, hodel::IntegerTuple{0, 2}}
        };

        hodel::Object wideObject{
            {1, hodel::IntegerTuple{0, 0}},
            {1, hodel::IntegerTuple{1, 0}},
            {1, hodel::IntegerTuple{2, 0}}
        };

        return {tallObject, wideObject};
    }

    hodel::ObjectVector objectVectorDmirrorExample()
    {
        hodel::Object firstObject{
            {1, hodel::IntegerTuple{0, 1}},
            {2, hodel::IntegerTuple{1, 0}}
        };

        hodel::Object secondObject{
            {3, hodel::IntegerTuple{2, 4}},
            {4, hodel::IntegerTuple{5, 1}}
        };

        return {firstObject, secondObject};
    }

    hodel::ObjectVector emptyObjectVector()
    {
        return {};
    }
}

TEST(ApplyNeuronTest, AppliesIncrementToIntegerVector)
{
    using UnaryNeuron =
        aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    using VectorNeuron = aicpp::Neuron<hodel::IntegerVector>;

    VectorNeuron vector{
        "vector",
        static_cast<VectorNeuron::PointerFunction>(&integerVector123)
    };

    aicpp::Connection incrementConnection{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection vectorConnection{
        &vector,
        {}
    };

    aicpp::ApplyNeuron apply;

    aicpp::Connection expression{
        &apply,
        {incrementConnection, vectorConnection}
    };

    auto result = expression.output();

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.type(), typeid(hodel::IntegerVector));

    EXPECT_EQ(
        std::any_cast<hodel::IntegerVector>(result),
        (hodel::IntegerVector{2, 3, 4})
    );
}

TEST(ApplyNeuronTest, RejectsFunctionWithIncompatibleReturnType)
{
    auto integerToGrid = [](hodel::Integer const&) -> hodel::Grid {
        return {};
    };

    using UnaryNeuron =
        aicpp::Neuron<hodel::Grid, hodel::Integer const&>;

    UnaryNeuron predicate{"integerToGrid", integerToGrid};

    aicpp::Neuron<hodel::IntegerVector> vector{
        "vector",
        static_cast<aicpp::Neuron<hodel::IntegerVector>::PointerFunction>(
            &integerVector123)
    };

    aicpp::Connection predicateConnection{
        &predicate,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection vectorConnection{&vector, {}};

    aicpp::ApplyNeuron apply;

    EXPECT_THROW(
        (aicpp::Connection{
            &apply,
            {predicateConnection, vectorConnection}
        }),
        std::invalid_argument
    );
}

namespace
{
    hodel::Integer addIntegers(
        hodel::Integer const& lhs,
        hodel::Integer const& rhs)
    {
        return lhs + rhs;
    }
}

TEST(ApplyNeuronTest, RejectsNonUnaryFunction)
{
    using BinaryNeuron =
        aicpp::Neuron<
            hodel::Integer,
            hodel::Integer const&,
            hodel::Integer const&
        >;

    BinaryNeuron add{
        "add",
        static_cast<BinaryNeuron::PointerFunction>(&addIntegers)
    };

    using VectorNeuron = aicpp::Neuron<hodel::IntegerVector>;

    VectorNeuron vector{
        "vector",
        static_cast<VectorNeuron::PointerFunction>(&integerVector123)
    };

    aicpp::Connection addConnection{
        &add,
        {
            std::type_index{typeid(hodel::Integer)},
            std::type_index{typeid(hodel::Integer)}
        }
    };

    aicpp::Connection vectorConnection{
        &vector,
        {}
    };

    aicpp::ApplyNeuron apply;

    EXPECT_THROW(
        (aicpp::Connection{
            &apply,
            {addConnection, vectorConnection}
        }),
        std::invalid_argument
    );
}

namespace
{
    hodel::IntegerVector emptyIntegerVector()
    {
        return {};
    }
}

TEST(ApplyNeuronTest, AppliesIncrementToEmptyIntegerVector)
{
    using UnaryNeuron =
        aicpp::Neuron<hodel::Integer, hodel::Integer const&>;

    UnaryNeuron increment{
        "increment",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::increment)
    };

    using VectorNeuron = aicpp::Neuron<hodel::IntegerVector>;

    VectorNeuron vector{
        "emptyVector",
        static_cast<VectorNeuron::PointerFunction>(&emptyIntegerVector)
    };

    aicpp::Connection incrementConnection{
        &increment,
        {std::type_index{typeid(hodel::Integer)}}
    };

    aicpp::Connection vectorConnection{
        &vector,
        {}
    };

    aicpp::ApplyNeuron apply;

    aicpp::Connection expression{
        &apply,
        {incrementConnection, vectorConnection}
    };

    auto result = expression.output();

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.type(), typeid(hodel::IntegerVector));

    EXPECT_TRUE(
        std::any_cast<hodel::IntegerVector const&>(result).empty()
    );
}

TEST(ApplyNeuronTest, AppliesEvenToIntegerVector)
{
    aicpp::Neuron<hodel::Boolean, hodel::Integer const&> evenNeuron{
        "even",
        static_cast<hodel::Boolean (*)(hodel::Integer const&)>(&hodel::even)
    };

    aicpp::Neuron<hodel::IntegerVector> vectorNeuron{"vector", &integerVector123};

    std::vector<std::any> integerInputs{
        std::type_index{typeid(hodel::Integer)}
    };

    aicpp::Connection evenConnection{&evenNeuron, integerInputs};
    aicpp::Connection vectorConnection{&vectorNeuron, {}};

    aicpp::ApplyNeuron apply;

    aicpp::Connection expression{
        &apply,
        {evenConnection, vectorConnection}
    };

    auto result = expression.output();

    EXPECT_EQ(
        std::any_cast<hodel::BooleanVector>(result),
        (hodel::BooleanVector{false, true, false})
    );
}

TEST(ApplyNeuronTest, AppliesFlipToBooleanVector)
{
    using UnaryNeuron =
        aicpp::Neuron<hodel::Boolean, hodel::Boolean const&>;

    UnaryNeuron flipNeuron{
        "flip",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::flip)
    };

    aicpp::Neuron<hodel::BooleanVector> vectorNeuron{
        "vector",
        &booleanVector123
    };

    aicpp::Connection flipConnection{
        &flipNeuron,
        {std::type_index{typeid(hodel::Boolean)}}
    };

    aicpp::Connection vectorConnection{&vectorNeuron, {}};

    aicpp::ApplyNeuron apply;

    aicpp::Connection expression{
        &apply,
        {flipConnection, vectorConnection}
    };

    EXPECT_EQ(
        std::any_cast<hodel::BooleanVector>(expression.output()),
        (hodel::BooleanVector{false, true, false})
    );
}

TEST(ApplyNeuronTest, AppliesHorizontalMirrorToGridVector)
{
    using MirrorNeuron =
        aicpp::Neuron<hodel::Grid, hodel::Grid const&>;

    MirrorNeuron mirrorNeuron{
        "hmirror",
        static_cast<MirrorNeuron::PointerFunction>(&hodel::hmirror)
    };

    aicpp::Neuron<hodel::GridVector> vectorNeuron{
        "gridVector",
        &gridVectorExample
    };

    aicpp::Connection mirrorConnection{
        &mirrorNeuron,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::Connection vectorConnection{
        &vectorNeuron,
        {}
    };

    aicpp::ApplyNeuron apply;

    aicpp::Connection expression{
        &apply,
        {mirrorConnection, vectorConnection}
    };

    auto result = std::any_cast<hodel::GridVector>(expression.output());

    ASSERT_EQ(result.size(), 2u);

    EXPECT_EQ(
        result[0],
        (hodel::Grid{
            {3, 4},
            {1, 2}
        })
    );

    EXPECT_EQ(
        result[1],
        (hodel::Grid{
            {7, 8},
            {5, 6}
        })
    );
}

TEST(ApplyNeuronTest, AppliesHorizontalMirrorToEmptyGridVector)
{
    using MirrorNeuron =
        aicpp::Neuron<hodel::Grid, hodel::Grid const&>;

    MirrorNeuron mirrorNeuron{
        "hmirror",
        static_cast<MirrorNeuron::PointerFunction>(&hodel::hmirror)
    };

    aicpp::Neuron<hodel::GridVector> vectorNeuron{
        "emptyGridVector",
        &emptyGridVector
    };

    aicpp::Connection mirrorConnection{
        &mirrorNeuron,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::Connection vectorConnection{
        &vectorNeuron,
        {}
    };

    aicpp::ApplyNeuron apply;

    aicpp::Connection expression{
        &apply,
        {mirrorConnection, vectorConnection}
    };

    auto result = std::any_cast<hodel::GridVector>(
        expression.output());

    EXPECT_TRUE(result.empty());
}

TEST(ApplyNeuronTest, AppliesPortraitToGridVector)
{
    using PortraitNeuron =
        aicpp::Neuron<hodel::Boolean, hodel::Grid const&>;

    PortraitNeuron portraitNeuron{
        "portrait",
        static_cast<PortraitNeuron::PointerFunction>(&hodel::portrait)
    };

    aicpp::Neuron<hodel::GridVector> vectorNeuron{
        "gridVector",
        &gridVectorPortraitExample
    };

    aicpp::Connection portraitConnection{
        &portraitNeuron,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::Connection vectorConnection{
        &vectorNeuron,
        {}
    };

    aicpp::ApplyNeuron apply;

    aicpp::Connection expression{
        &apply,
        {portraitConnection, vectorConnection}
    };

    auto result = std::any_cast<hodel::BooleanVector>(
        expression.output());

    EXPECT_EQ(
        result,
        (hodel::BooleanVector{true, false, true})
    );
}

TEST(ApplyNeuronTest, AppliesPortraitToEmptyGridVector)
{
    using PortraitNeuron =
        aicpp::Neuron<hodel::Boolean, hodel::Grid const&>;

    PortraitNeuron portraitNeuron{
        "portrait",
        static_cast<PortraitNeuron::PointerFunction>(&hodel::portrait)
    };

    aicpp::Neuron<hodel::GridVector> vectorNeuron{
        "emptyGridVector",
        &emptyGridVector
    };

    aicpp::Connection portraitConnection{
        &portraitNeuron,
        {std::type_index{typeid(hodel::Grid)}}
    };

    aicpp::Connection vectorConnection{
        &vectorNeuron,
        {}
    };

    aicpp::ApplyNeuron apply;

    aicpp::Connection expression{
        &apply,
        {portraitConnection, vectorConnection}
    };

    auto result = std::any_cast<hodel::BooleanVector>(
        expression.output());

    EXPECT_TRUE(result.empty());
}

TEST(ApplyNeuronTest, AppliesPortraitToObjectsVector)
{
    using PortraitNeuron =
        aicpp::Neuron<hodel::Boolean, hodel::Object const&>;

    PortraitNeuron portraitNeuron{
        "portrait",
        static_cast<PortraitNeuron::PointerFunction>(
            static_cast<hodel::Boolean (*)(hodel::Object const&)>(
                &hodel::portrait))
    };

    aicpp::Neuron<hodel::ObjectVector> vectorNeuron{
        "ObjectVector",
        &objectVectorPortraitExample
    };

    aicpp::Connection portraitConnection{
        &portraitNeuron,
        {std::type_index{typeid(hodel::Object)}}
    };

    aicpp::Connection vectorConnection{
        &vectorNeuron,
        {}
    };

    aicpp::ApplyNeuron apply;

    aicpp::Connection expression{
        &apply,
        {portraitConnection, vectorConnection}
    };

    auto const result =
        std::any_cast<hodel::BooleanVector>(expression.output());

    EXPECT_EQ(result, (hodel::BooleanVector{false, true}));
}

TEST(ApplyNeuronTest, AppliesDiagonalMirrorToObjectVector)
{
    using DmirrorNeuron =
        aicpp::Neuron<hodel::Object, hodel::Object const&>;

    DmirrorNeuron dmirrorNeuron{
        "dmirror",
        static_cast<DmirrorNeuron::PointerFunction>(&hodel::dmirror)
    };

    aicpp::Neuron<hodel::ObjectVector> vectorNeuron{
        "objectVector",
        &objectVectorDmirrorExample
    };

    aicpp::Connection dmirrorConnection{
        &dmirrorNeuron,
        {std::type_index{typeid(hodel::Object)}}
    };

    aicpp::Connection vectorConnection{
        &vectorNeuron,
        {}
    };

    aicpp::ApplyNeuron apply;

    aicpp::Connection expression{
        &apply,
        {dmirrorConnection, vectorConnection}
    };

    auto const result =
        std::any_cast<hodel::ObjectVector>(expression.output());

    auto const input = objectVectorDmirrorExample();

    ASSERT_EQ(result.size(), input.size());

    for (std::size_t i = 0; i < input.size(); ++i)
    {
        EXPECT_EQ(result[i], hodel::dmirror(input[i]));
    }
}

TEST(ApplyNeuronTest, AppliesDiagonalMirrorToEmptyObjectVector)
{
    using DmirrorNeuron =
        aicpp::Neuron<hodel::Object, hodel::Object const&>;

    DmirrorNeuron dmirrorNeuron{
        "dmirror",
        static_cast<DmirrorNeuron::PointerFunction>(&hodel::dmirror)
    };

    aicpp::Neuron<hodel::ObjectVector> vectorNeuron{
        "emptyObjectVector",
        &emptyObjectVector
    };

    aicpp::Connection dmirrorConnection{
        &dmirrorNeuron,
        {std::type_index{typeid(hodel::Object)}}
    };

    aicpp::Connection vectorConnection{
        &vectorNeuron,
        {}
    };

    aicpp::ApplyNeuron apply;

    aicpp::Connection expression{
        &apply,
        {dmirrorConnection, vectorConnection}
    };

    auto const result = expression.output();

    ASSERT_EQ(result.type(), typeid(hodel::ObjectVector));

    auto const& objects =
        std::any_cast<hodel::ObjectVector const&>(result);

    EXPECT_TRUE(objects.empty());
}

TEST(ApplyNeuronTest, RejectsFunctionWithIncompatibleInputType)
{
    using UnaryNeuron =
        aicpp::Neuron<hodel::Boolean, hodel::Boolean const&>;

    UnaryNeuron flipNeuron{
        "flip",
        static_cast<UnaryNeuron::PointerFunction>(&hodel::flip)
    };

    aicpp::Neuron<hodel::IntegerVector> vectorNeuron{
        "integerVector",
        static_cast<aicpp::Neuron<hodel::IntegerVector>::PointerFunction>(
            &integerVector123)
    };

    aicpp::Connection flipConnection{
        &flipNeuron,
        {std::type_index{typeid(hodel::Boolean)}}
    };

    aicpp::Connection vectorConnection{
        &vectorNeuron,
        {}
    };

    aicpp::ApplyNeuron apply;

    EXPECT_THROW(
        (aicpp::Connection{
            &apply,
            {flipConnection, vectorConnection}
        }),
        std::invalid_argument
    );
}

TEST(IntegrationTest, ArgminIntegerVector)
{
    using namespace hodel;

    auto const integerType = aicpp::makeDslType<Integer>();
    auto const integerVectorType = aicpp::makeDslType<IntegerVector>();

    auto const unaryInteger = aicpp::DslType::function(
        {integerType},
        integerType);

    auto increment = aicpp::buildConnection("increment", {});

    aicpp::ArgminNeuron argmin;

    EXPECT_EQ(
        argmin.inferSignature({integerVectorType, unaryInteger}),
        aicpp::DslType::function(
            {integerVectorType},
            integerType));

    IntegerVector values{7, 3, 9, 1, 5};

    auto const result = argmin.apply(
        {
            std::type_index{typeid(IntegerVector)},
            increment
        },
        std::any{values});

    ASSERT_EQ(result.type(), typeid(Integer));
    EXPECT_EQ(std::any_cast<Integer>(result), 1);
}

TEST(IntegrationTest, ArgminRejectsIncompatibleFunction)
{
    using namespace hodel;

    auto const integerVectorType = aicpp::makeDslType<IntegerVector>();
    auto const booleanType = aicpp::makeDslType<Boolean>();

    auto const unaryBoolean = aicpp::DslType::function(
        {booleanType},
        booleanType);

    aicpp::ArgminNeuron argmin;

    EXPECT_THROW(
        argmin.inferSignature(
            {integerVectorType, unaryBoolean}),
        std::invalid_argument);
}

TEST(IntegrationTest, ArgminRejectsEmptyIntegerVector)
{
    using namespace hodel;

    auto increment = aicpp::buildConnection("increment", {});

    aicpp::ArgminNeuron argmin;

    EXPECT_THROW(
        argmin.apply(
            {
                std::type_index{typeid(IntegerVector)},
                increment
            },
            std::any{IntegerVector{}}),
        std::invalid_argument);
}

TEST(IntegrationTest, ValminIntegerVector)
{
    using namespace hodel;

    auto increment = aicpp::buildConnection("increment", {});

    aicpp::ValminNeuron valmin;

    IntegerVector values{7, 3, 9, 1, 5};

    auto const result = valmin.apply(
        {
            std::type_index{typeid(IntegerVector)},
            increment
        },
        std::any{values});

    ASSERT_EQ(result.type(), typeid(Integer));
    EXPECT_EQ(std::any_cast<Integer>(result), 2);
}

namespace
{
    hodel::Integer increment(hodel::Integer const& value)
    {
        return value + 1;
    }
}

TEST(FunctionAdapterNeuronTest, ExposesNativeSignature)
{
    using FunctionType =
        aicpp::Neuron<
            hodel::Integer,
            hodel::Integer const&>::PointerFunction;

    aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&> neuron{
            "increment",
            static_cast<FunctionType>(&increment)
        };

    aicpp::FunctionAdapterNeuron adapter{&neuron};

    auto const signature = adapter.inferSignature({});

    EXPECT_EQ(
        signature,
        aicpp::DslType::function(
            {aicpp::makeDslType<hodel::Integer>()},
            aicpp::makeDslType<hodel::Integer>()));
}

TEST(FunctionAdapterNeuronTest, AppliesNativeNeuron)
{
    using FunctionType =
        aicpp::Neuron<
            hodel::Integer,
            hodel::Integer const&>::PointerFunction;

    aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&> neuron{
            "increment",
            static_cast<FunctionType>(&increment)
        };

    aicpp::FunctionAdapterNeuron adapter{&neuron};

    auto const result = adapter.apply({}, std::any{hodel::Integer{41}});

    ASSERT_EQ(result.type(), typeid(hodel::Integer));
    EXPECT_EQ(std::any_cast<hodel::Integer>(result), 42);
}

TEST(FunctionAdapterNeuronTest, RejectsIncompatibleInputType)
{
    using FunctionType =
        aicpp::Neuron<
            hodel::Integer,
            hodel::Integer const&>::PointerFunction;

    aicpp::Neuron<
        hodel::Integer,
        hodel::Integer const&> neuron{
            "increment",
            static_cast<FunctionType>(&increment)
        };

    aicpp::FunctionAdapterNeuron adapter{&neuron};

    EXPECT_THROW(
        adapter.apply({}, std::any{hodel::Boolean{true}}),
        std::invalid_argument);
}

TEST(FunctionOverloadNeuronTest, BuildsOverloadedFunctionReference)
{
    auto const size = aicpp::buildConnection("size", {});

    EXPECT_EQ(size.name(), "size");
    EXPECT_TRUE(size.signature().isFunction());
}

TEST(ConnectionTest, BuildFunctionConnectionBinary)
{
    using namespace aicpp;

    auto const addSignature = DslType::function(
        {
            makeDslType<hodel::Integer>(),
            makeDslType<hodel::Integer>()
        },
        makeDslType<hodel::Integer>());

    auto const connection =
        buildFunctionConnection("add", addSignature);

    EXPECT_EQ(connection.signature(), addSignature);
    EXPECT_EQ(connection.name(), "add");
    EXPECT_EQ(connection.neuron()->returnType(), typeid(hodel::Integer));

    auto const inputTypes = connection.inputTypes();

    ASSERT_EQ(inputTypes.size(), 2);
    EXPECT_EQ(inputTypes[0], typeid(hodel::Integer));
    EXPECT_EQ(inputTypes[1], typeid(hodel::Integer));
}

TEST(ConnectionTest, BuildFunctionConnectionBinaryPreservesSignature)
{
    using namespace aicpp;

    auto const expectedSignature = DslType::function(
        {
            makeDslType<hodel::Integer>(),
            makeDslType<hodel::Integer>()
        },
        makeDslType<hodel::Integer>());

    auto const connection =
        buildFunctionConnection("add", expectedSignature);

    EXPECT_EQ(connection.signature(), expectedSignature);
    EXPECT_EQ(connection.name(), "add");

    ASSERT_NE(connection.neuron(), nullptr);
    EXPECT_EQ(connection.neuron()->signature(), expectedSignature);

    auto const inputs = connection.inputs();
    ASSERT_EQ(inputs.size(), 2);

    EXPECT_EQ(inputs[0].type(), typeid(std::type_index));
    EXPECT_EQ(inputs[1].type(), typeid(std::type_index));
}

TEST(ConnectionTest, BuildFunctionConnectionBinaryCannotBeEvaluatedWithoutArguments)
{
    using namespace aicpp;

    auto const signature = DslType::function(
        {
            makeDslType<hodel::Integer>(),
            makeDslType<hodel::Integer>()
        },
        makeDslType<hodel::Integer>());

    auto const connection =
        buildFunctionConnection("add", signature);

    EXPECT_THROW(connection.output(), std::bad_any_cast);
}

TEST(LbindNeuronTest, AppliesFixedFirstArgument)
{
    auto const addSignature = aicpp::DslType::function(
        {
            aicpp::makeDslType<hodel::Integer>(),
            aicpp::makeDslType<hodel::Integer>()
        },
        aicpp::makeDslType<hodel::Integer>());

    auto const fixed = aicpp::buildConnection("ONE", {});
    auto const function = aicpp::buildFunctionConnection("add", addSignature);

    aicpp::LbindNeuron lbind;

    aicpp::Connection bound{
        &lbind,
        {function, fixed}
    };

    auto const result{bound.apply(hodel::Integer{21})};

    EXPECT_EQ(
        std::any_cast<hodel::Integer>(result),
        hodel::Integer{22});
}

TEST(RbindNeuronTest, AppliesFixedSecondArgument)
{
    auto const addSignature = aicpp::DslType::function(
        {
            aicpp::makeDslType<hodel::Integer>(),
            aicpp::makeDslType<hodel::Integer>()
        },
        aicpp::makeDslType<hodel::Integer>());

    auto const fixed = aicpp::buildConnection("ONE", {});
    auto const function = aicpp::buildFunctionConnection("add", addSignature);

    aicpp::RbindNeuron rbind;

    aicpp::Connection bound{
        &rbind,
        {function, fixed}
    };

    auto const result{bound.apply(hodel::Integer{21})};

    EXPECT_EQ(
        std::any_cast<hodel::Integer>(result),
        hodel::Integer{22});
}

TEST(LbindNeuronTest, RejectsIncorrectNumberOfArguments)
{
    aicpp::LbindNeuron lbind;

    auto const integerType{
        aicpp::makeDslType<hodel::Integer>()};

    auto const functionSignature{
        aicpp::DslType::function(
            {integerType, integerType},
            integerType)};

    EXPECT_THROW(
        lbind.inferSignature({functionSignature}),
        std::invalid_argument);

    EXPECT_THROW(
        lbind.inferSignature(
            {functionSignature, integerType, integerType}),
        std::invalid_argument);
}

TEST(RbindNeuronTest, RejectsIncorrectNumberOfArguments)
{
    aicpp::RbindNeuron rbind;

    auto const integerType{
        aicpp::makeDslType<hodel::Integer>()};

    auto const functionSignature{
        aicpp::DslType::function(
            {integerType, integerType},
            integerType)};

    EXPECT_THROW(
        rbind.inferSignature({functionSignature}),
        std::invalid_argument);

    EXPECT_THROW(
        rbind.inferSignature(
            {functionSignature, integerType, integerType}),
        std::invalid_argument);
}

TEST(LbindNeuronTest, RejectsIncompatibleFixedArgumentType)
{
    aicpp::LbindNeuron lbind;

    auto const integerType{
        aicpp::makeDslType<hodel::Integer>()};

    auto const tupleType{
        aicpp::makeDslType<hodel::IntegerTuple>()};

    auto const functionSignature{
        aicpp::DslType::function(
            {integerType, integerType},
            integerType)};

    auto const fixedSignature{
        aicpp::DslType::function({}, tupleType)};

    EXPECT_THROW(
        lbind.inferSignature(
            {functionSignature, fixedSignature}),
        std::invalid_argument);
}

TEST(RbindNeuronTest, RejectsIncompatibleFixedArgumentType)
{
    aicpp::RbindNeuron rbind;

    auto const integerType{
        aicpp::makeDslType<hodel::Integer>()};

    auto const tupleType{
        aicpp::makeDslType<hodel::IntegerTuple>()};

    auto const functionSignature{
        aicpp::DslType::function(
            {integerType, integerType},
            integerType)};

    auto const fixedSignature{
        aicpp::DslType::function({}, tupleType)};

    EXPECT_THROW(
        rbind.inferSignature(
            {functionSignature, fixedSignature}),
        std::invalid_argument);
}

TEST(RbindNeuronTest, RejectsIncompatibleInputType)
{
    auto const addSignature = aicpp::DslType::function(
        {
            aicpp::makeDslType<hodel::Integer>(),
            aicpp::makeDslType<hodel::Integer>()
        },
        aicpp::makeDslType<hodel::Integer>());

    auto const fixed = aicpp::buildConnection("ONE", {});
    auto const function =
        aicpp::buildFunctionConnection("add", addSignature);

    aicpp::RbindNeuron rbind;

    aicpp::Connection bound{
        &rbind,
        {function, fixed}
    };

    EXPECT_THROW(
        bound.apply(std::any{std::string{"invalid"}}),
        std::invalid_argument);
}

TEST(LbindNeuronTest, BuildsConnectionThroughRegistry)
{
    auto const addSignature = aicpp::DslType::function(
        {
            aicpp::makeDslType<hodel::Integer>(),
            aicpp::makeDslType<hodel::Integer>()
        },
        aicpp::makeDslType<hodel::Integer>());

    auto const fixed = aicpp::buildConnection("ONE", {});
    auto const function =
        aicpp::buildFunctionConnection("add", addSignature);

    auto const bound =
        aicpp::buildConnection("lbind", {function, fixed});

    EXPECT_EQ(
        std::any_cast<hodel::Integer>(
            bound.apply(hodel::Integer{21})),
        hodel::Integer{22});
}

TEST(RbindNeuronTest, BuildsConnectionThroughRegistry)
{
    auto const addSignature = aicpp::DslType::function(
        {
            aicpp::makeDslType<hodel::Integer>(),
            aicpp::makeDslType<hodel::Integer>()
        },
        aicpp::makeDslType<hodel::Integer>());

    auto const fixed = aicpp::buildConnection("ONE", {});
    auto const function =
        aicpp::buildFunctionConnection("add", addSignature);

    auto const bound =
        aicpp::buildConnection("rbind", {function, fixed});

    EXPECT_EQ(
        std::any_cast<hodel::Integer>(
            bound.apply(hodel::Integer{21})),
        hodel::Integer{22});
}

TEST(LbindNeuronTest, PreservesFunctionReturnType)
{
    auto const integerType{
        aicpp::makeDslType<hodel::Integer>()};

    auto const booleanType{
        aicpp::makeDslType<hodel::Boolean>()};

    auto const functionSignature{
        aicpp::DslType::function(
            {integerType, integerType},
            booleanType)};

    auto const fixedSignature{
        aicpp::DslType::function({}, integerType)};

    aicpp::LbindNeuron lbind;

    auto const signature{
        lbind.inferSignature(
            {functionSignature, fixedSignature})};

    ASSERT_TRUE(signature.isFunction());
    ASSERT_EQ(signature.inputs().size(), 1);

    EXPECT_EQ(signature.inputs()[0], integerType);
    EXPECT_EQ(signature.output(), booleanType);
}

TEST(RbindNeuronTest, PreservesFunctionReturnType)
{
    auto const integerType{
        aicpp::makeDslType<hodel::Integer>()};

    auto const booleanType{
        aicpp::makeDslType<hodel::Boolean>()};

    auto const functionSignature{
        aicpp::DslType::function(
            {integerType, integerType},
            booleanType)};

    auto const fixedSignature{
        aicpp::DslType::function({}, integerType)};

    aicpp::RbindNeuron rbind;

    auto const signature{
        rbind.inferSignature(
            {functionSignature, fixedSignature})};

    ASSERT_TRUE(signature.isFunction());
    ASSERT_EQ(signature.inputs().size(), 1);

    EXPECT_EQ(signature.inputs()[0], integerType);
    EXPECT_EQ(signature.output(), booleanType);
}

TEST(LbindNeuronTest, AppliesIntegerTupleOverload)
{
    using IntegerTuple = hodel::IntegerTuple;

    auto const tupleType{
        aicpp::makeDslType<IntegerTuple>()};

    auto const signature{
        aicpp::DslType::function(
            {tupleType, tupleType},
            tupleType)};

    auto const function{
        aicpp::buildFunctionConnection("add", signature)};

    aicpp::Neuron<IntegerTuple> const fixedNeuron{
        "fixed",
        [] () -> IntegerTuple { return {1, 2}; }
    };

    aicpp::Connection const fixedConnection{
        &fixedNeuron,
        {}
    };

    auto const bound{
        aicpp::buildConnection("lbind", {function, fixedConnection})
    };

    auto const result{
        std::any_cast<IntegerTuple>(
            bound.apply(IntegerTuple{3, 4}))
    };

    EXPECT_EQ(result, IntegerTuple({4, 6}));
}

TEST(RbindNeuronTest, AppliesIntegerTupleOverload)
{
    using IntegerTuple = hodel::IntegerTuple;

    auto const tupleType{
        aicpp::makeDslType<IntegerTuple>()};

    auto const signature{
        aicpp::DslType::function(
            {tupleType, tupleType},
            tupleType)};

    auto const function{
        aicpp::buildFunctionConnection("add", signature)};

    aicpp::Neuron<IntegerTuple> const fixedNeuron{
        "fixed",
        [] () -> IntegerTuple { return {1, 2}; }
    };

    aicpp::Connection const fixedConnection{
        &fixedNeuron,
        {}
    };

    auto const bound{
        aicpp::buildConnection("rbind", {function, fixedConnection})
    };

    auto const result{
        std::any_cast<IntegerTuple>(
            bound.apply(IntegerTuple{3, 4}))
    };

    EXPECT_EQ(result, IntegerTuple({4, 6}));
}
