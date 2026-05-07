#include "aicpp/DslSystem.h"
#include "aicpp/Hodel.h"

using namespace aicpp;

std::map<std::string, Neuron> aicpp::dslVariableNeurons()
{
    std::map<std::string, Neuron> neurons;

    neurons["F"] = Neuron{"F", [] (std::vector<std::any> const&) -> std::any { return hdl::F; }, std::vector<std::type_index>{}, typeid(hdl::Boolean)};
    neurons["T"] = Neuron{"T", [] (std::vector<std::any> const&) -> std::any { return hdl::T; }, std::vector<std::type_index>{}, typeid(hdl::Boolean)};
    neurons["ZERO"] = Neuron{"ZERO", [] (std::vector<std::any> const&) -> std::any { return hdl::ZERO; }, std::vector<std::type_index>{}, typeid(hdl::Integer)};
    neurons["ONE"] = Neuron{"ONE", [] (std::vector<std::any> const&) -> std::any { return hdl::ONE; }, std::vector<std::type_index>{}, typeid(hdl::Integer)};
    neurons["TWO"] = Neuron{"TWO", [] (std::vector<std::any> const&) -> std::any { return hdl::TWO; }, std::vector<std::type_index>{}, typeid(hdl::Integer)};
    neurons["THREE"] = Neuron{"THREE", [] (std::vector<std::any> const&) -> std::any { return hdl::THREE; }, std::vector<std::type_index>{}, typeid(hdl::Integer)};
    neurons["FOUR"] = Neuron{"FOUR", [] (std::vector<std::any> const&) -> std::any { return hdl::FOUR; }, std::vector<std::type_index>{}, typeid(hdl::Integer)};
    neurons["FIVE"] = Neuron{"FIVE", [] (std::vector<std::any> const&) -> std::any { return hdl::FIVE; }, std::vector<std::type_index>{}, typeid(hdl::Integer)};
    neurons["SIX"] = Neuron{"SIX", [] (std::vector<std::any> const&) -> std::any { return hdl::SIX; }, std::vector<std::type_index>{}, typeid(hdl::Integer)};
    neurons["SEVEN"] = Neuron{"SEVEN", [] (std::vector<std::any> const&) -> std::any { return hdl::SEVEN; }, std::vector<std::type_index>{}, typeid(hdl::Integer)};
    neurons["EIGHT"] = Neuron{"EIGHT", [] (std::vector<std::any> const&) -> std::any { return hdl::EIGHT; }, std::vector<std::type_index>{}, typeid(hdl::Integer)};
    neurons["NINE"] = Neuron{"NINE", [] (std::vector<std::any> const&) -> std::any { return hdl::NINE; }, std::vector<std::type_index>{}, typeid(hdl::Integer)};
    neurons["TEN"] = Neuron{"TEN", [] (std::vector<std::any> const&) -> std::any { return hdl::TEN; }, std::vector<std::type_index>{}, typeid(hdl::Integer)};
    neurons["DOWN"] = Neuron{"DOWN", [] (std::vector<std::any> const&) -> std::any { return hdl::DOWN; }, std::vector<std::type_index>{}, typeid(hdl::Direction)};
    neurons["RIGHT"] = Neuron{"RIGHT", [] (std::vector<std::any> const&) -> std::any { return hdl::RIGHT; }, std::vector<std::type_index>{}, typeid(hdl::Direction)};
    neurons["UP"] = Neuron{"UP", [] (std::vector<std::any> const&) -> std::any { return hdl::UP; }, std::vector<std::type_index>{}, typeid(hdl::Direction)};
    neurons["LEFT"] = Neuron{"LEFT", [] (std::vector<std::any> const&) -> std::any { return hdl::LEFT; }, std::vector<std::type_index>{}, typeid(hdl::Direction)};
    neurons["ORIGIN"] = Neuron{"ORIGIN", [] (std::vector<std::any> const&) -> std::any { return hdl::ORIGIN; }, std::vector<std::type_index>{}, typeid(hdl::Direction)};
    neurons["UNITY"] = Neuron{"UNITY", [] (std::vector<std::any> const&) -> std::any { return hdl::UNITY; }, std::vector<std::type_index>{}, typeid(hdl::Direction)};
    neurons["NEG_UNITY"] = Neuron{"NEG_UNITY", [] (std::vector<std::any> const&) -> std::any { return hdl::NEG_UNITY; }, std::vector<std::type_index>{}, typeid(hdl::Direction)};
    neurons["UP_RIGHT"] = Neuron{"UP_RIGHT", [] (std::vector<std::any> const&) -> std::any { return hdl::UP_RIGHT; }, std::vector<std::type_index>{}, typeid(hdl::Direction)};
    neurons["DOWN_LEFT"] = Neuron{"DOWN_LEFT", [] (std::vector<std::any> const&) -> std::any { return hdl::DOWN_LEFT; }, std::vector<std::type_index>{}, typeid(hdl::Direction)};
    neurons["ZERO_BY_TWO"] = Neuron{"ZERO_BY_TWO", [] (std::vector<std::any> const&) -> std::any { return hdl::ZERO_BY_TWO; }, std::vector<std::type_index>{}, typeid(hdl::Size)};
    neurons["TWO_BY_ZERO"] = Neuron{"TWO_BY_ZERO", [] (std::vector<std::any> const&) -> std::any { return hdl::TWO_BY_ZERO; }, std::vector<std::type_index>{}, typeid(hdl::Size)};
    neurons["TWO_BY_TWO"] = Neuron{"TWO_BY_TWO", [] (std::vector<std::any> const&) -> std::any { return hdl::TWO_BY_TWO; }, std::vector<std::type_index>{}, typeid(hdl::Size)};
    neurons["THREE_BY_THREE"] = Neuron{"THREE_BY_THREE", [] (std::vector<std::any> const&) -> std::any { return hdl::THREE_BY_THREE; }, std::vector<std::type_index>{}, typeid(hdl::Size)};

    return neurons;
}

std::map<std::string, Neuron> aicpp::dslPrimitiveNeurons()
{
    std::map<std::string, Neuron> neurons;

    neurons["identity"] = Neuron{"identity", hdl::identity, std::vector<std::type_index>{typeid(hdl::Any)}, typeid(hdl::Any)};
    neurons["add"] = Neuron{"add", hdl::add, std::vector<std::type_index>{typeid(hdl::Numerical), typeid(hdl::Numerical)}, typeid(hdl::Numerical)};
    neurons["subtract"] = Neuron{"subtract", hdl::subtract, std::vector<std::type_index>{typeid(hdl::Numerical), typeid(hdl::Numerical)}, typeid(hdl::Numerical)};
    neurons["multiply"] = Neuron{"multiply", hdl::multiply, std::vector<std::type_index>{typeid(hdl::Numerical), typeid(hdl::Numerical)}, typeid(hdl::Numerical)};
    neurons["divide"] = Neuron{"divide", hdl::divide, std::vector<std::type_index>{typeid(hdl::Numerical), typeid(hdl::Numerical)}, typeid(hdl::Numerical)};
    neurons["invert"] = Neuron{"invert", hdl::invert, std::vector<std::type_index>{typeid(hdl::Numerical)}, typeid(hdl::Numerical)};
    neurons["even"] = Neuron{"even", hdl::even, std::vector<std::type_index>{typeid(hdl::Boolean)}, typeid(hdl::Integer)};
    neurons["double_"] = Neuron{"double_", hdl::double_, std::vector<std::type_index>{typeid(hdl::Integer)}, typeid(hdl::Integer)};
    neurons["halve"] = Neuron{"halve", hdl::halve, std::vector<std::type_index>{typeid(hdl::Integer)}, typeid(hdl::Integer)};
    neurons["flip"] = Neuron{"flip", hdl::flip, std::vector<std::type_index>{typeid(hdl::Boolean)}, typeid(hdl::Boolean)};
    neurons["equality"] = Neuron{"equality", hdl::equality, std::vector<std::type_index>{typeid(hdl::Any)}, typeid(hdl::Any)};
    neurons["contained"] = Neuron{"contained", hdl::contained, std::vector<std::type_index>{typeid(hdl::Any), typeid(hdl::Container)}, typeid(hdl::Boolean)};
    neurons["combine"] = Neuron{"combine", hdl::combine, std::vector<std::type_index>{typeid(hdl::Container), typeid(hdl::Container)}, typeid(hdl::Container)};
    neurons["intersection"] = Neuron{"intersection", hdl::intersection, std::vector<std::type_index>{typeid(hdl::FrozenSet), typeid(hdl::FrozenSet)}, typeid(hdl::FrozenSet)};
    neurons["difference"] = Neuron{"difference", hdl::difference, std::vector<std::type_index>{typeid(hdl::FrozenSet), typeid(hdl::FrozenSet)}, typeid(hdl::FrozenSet)};
    neurons["dedupe"] = Neuron{"dedupe", hdl::dedupe, std::vector<std::type_index>{typeid(hdl::Tuple)}, typeid(hdl::Tuple)};
    neurons["order"] = Neuron{"order", hdl::order, std::vector<std::type_index>{typeid(hdl::Container), typeid(hdl::Callable)}, typeid(hdl::Tuple)};
    neurons["repeat"] = Neuron{"repeat", hdl::repeat, std::vector<std::type_index>{typeid(hdl::Any), typeid(hdl::Integer)}, typeid(hdl::Tuple)};
    neurons["greater"] = Neuron{"greater", hdl::greater, std::vector<std::type_index>{typeid(hdl::Integer), typeid(hdl::Integer)}, typeid(hdl::Boolean)};
    neurons["size"] = Neuron{"size", hdl::size, std::vector<std::type_index>{typeid(hdl::Container)}, typeid(hdl::UnsignedInteger)};
    neurons["maximum"] = Neuron{"maximum", hdl::maximum, std::vector<std::type_index>{typeid(hdl::IntegerSet)}, typeid(hdl::Integer)};
    neurons["minimum"] = Neuron{"minimum", hdl::minimum, std::vector<std::type_index>{typeid(hdl::IntegerSet)}, typeid(hdl::Integer)};
    neurons["initset"] = Neuron{"initset", hdl::initset, std::vector<std::type_index>{typeid(hdl::Any)}, typeid(hdl::FrozenSet)};
    neurons["both"] = Neuron{"both", hdl::both, std::vector<std::type_index>{typeid(hdl::Boolean), typeid(hdl::Boolean)}, typeid(hdl::Boolean)};
    neurons["either"] = Neuron{"either", hdl::either, std::vector<std::type_index>{typeid(hdl::Boolean), typeid(hdl::Boolean)}, typeid(hdl::Boolean)};
    neurons["increment"] = Neuron{"increment", hdl::increment, std::vector<std::type_index>{typeid(hdl::Numerical)}, typeid(hdl::Numerical)};
    neurons["decrement"] = Neuron{"decrement", hdl::decrement, std::vector<std::type_index>{typeid(hdl::Numerical)}, typeid(hdl::Numerical)};
    neurons["crement"] = Neuron{"crement", hdl::crement, std::vector<std::type_index>{typeid(hdl::Numerical)}, typeid(hdl::Numerical)};
    neurons["sign"] = Neuron{"sign", hdl::sign, std::vector<std::type_index>{typeid(hdl::Numerical)}, typeid(hdl::Numerical)};
    neurons["positive"] = Neuron{"positive", hdl::positive, std::vector<std::type_index>{typeid(hdl::Numerical)}, typeid(hdl::Boolean)};
    neurons["toivec"] = Neuron{"toivec", hdl::toivec, std::vector<std::type_index>{typeid(hdl::Integer)}, typeid(hdl::IntegerTuple)};
    neurons["tojvec"] = Neuron{"tojvec", hdl::tojvec, std::vector<std::type_index>{typeid(hdl::Integer)}, typeid(hdl::IntegerTuple)};
    neurons["totuple"] = Neuron{"totuple", hdl::totuple, std::vector<std::type_index>{typeid(hdl::FrozenSet)}, typeid(hdl::Tuple)};
    neurons["first"] = Neuron{"first", hdl::first, std::vector<std::type_index>{typeid(hdl::Container)}, typeid(hdl::Any)};
    neurons["last"] = Neuron{"last", hdl::last, std::vector<std::type_index>{typeid(hdl::Container)}, typeid(hdl::Any)};
    neurons["interval"] = Neuron{"interval", hdl::interval, std::vector<std::type_index>{typeid(hdl::Integer), typeid(hdl::Integer), typeid(hdl::Integer)}, typeid(hdl::Tuple)};
    neurons["astuple"] = Neuron{"astuple", hdl::astuple, std::vector<std::type_index>{typeid(hdl::Integer), typeid(hdl::Integer)}, typeid(hdl::IntegerTuple)};

    return neurons;
}
