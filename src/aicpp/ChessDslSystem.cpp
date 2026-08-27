#include "aicpp/ChessDslSystem.h"
#include "aicpp/Chess.h"

using namespace aicpp;

std::map<std::string, Neuron> aicpp::chessDslVariableNeurons()
{
    std::map<std::string, Neuron> neurons;

    neurons.emplace("Zero", Neuron{"Zero", [] (std::vector<std::any> const&) -> std::any { return chess::Zero; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("One", Neuron{"One", [] (std::vector<std::any> const&) -> std::any { return chess::One; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Two", Neuron{"Two", [] (std::vector<std::any> const&) -> std::any { return chess::Two; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Three", Neuron{"Three", [] (std::vector<std::any> const&) -> std::any { return chess::Three; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Four", Neuron{"Four", [] (std::vector<std::any> const&) -> std::any { return chess::Four; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Five", Neuron{"Five", [] (std::vector<std::any> const&) -> std::any { return chess::Five; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Six", Neuron{"Six", [] (std::vector<std::any> const&) -> std::any { return chess::Six; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Seven", Neuron{"Seven", [] (std::vector<std::any> const&) -> std::any { return chess::Seven; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Eight", Neuron{"Eight", [] (std::vector<std::any> const&) -> std::any { return chess::Eight; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Nine", Neuron{"Nine", [] (std::vector<std::any> const&) -> std::any { return chess::Nine; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Ten", Neuron{"Ten", [] (std::vector<std::any> const&) -> std::any { return chess::Ten; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Eleven", Neuron{"Eleven", [] (std::vector<std::any> const&) -> std::any { return chess::Eleven; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Twelve", Neuron{"Twelve", [] (std::vector<std::any> const&) -> std::any { return chess::Twelve; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Thirteen", Neuron{"Thirteen", [] (std::vector<std::any> const&) -> std::any { return chess::Thirteen; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Fourteen", Neuron{"Fourteen", [] (std::vector<std::any> const&) -> std::any { return chess::Fourteen; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Fifteen", Neuron{"Fifteen", [] (std::vector<std::any> const&) -> std::any { return chess::Fifteen; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("sixteen", Neuron{"sixteen", [] (std::vector<std::any> const&) -> std::any { return chess::sixteen; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("seventeen", Neuron{"seventeen", [] (std::vector<std::any> const&) -> std::any { return chess::seventeen; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("eighteen", Neuron{"eighteen", [] (std::vector<std::any> const&) -> std::any { return chess::eighteen; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("nineteen", Neuron{"nineteen", [] (std::vector<std::any> const&) -> std::any { return chess::nineteen; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Twenty", Neuron{"Twenty", [] (std::vector<std::any> const&) -> std::any { return chess::Twenty; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Twenty_one", Neuron{"Twenty_one", [] (std::vector<std::any> const&) -> std::any { return chess::Twenty_one; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Twenty_two", Neuron{"Twenty_two", [] (std::vector<std::any> const&) -> std::any { return chess::Twenty_two; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Twenty_three", Neuron{"Twenty_three", [] (std::vector<std::any> const&) -> std::any { return chess::Twenty_three; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Twenty_four", Neuron{"Twenty_four", [] (std::vector<std::any> const&) -> std::any { return chess::Twenty_four; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Twenty_five", Neuron{"Twenty_five", [] (std::vector<std::any> const&) -> std::any { return chess::Twenty_five; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Twenty_six", Neuron{"Twenty_six", [] (std::vector<std::any> const&) -> std::any { return chess::Twenty_six; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Twenty_seven", Neuron{"Twenty_seven", [] (std::vector<std::any> const&) -> std::any { return chess::Twenty_seven; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Twenty_eight", Neuron{"Twenty_eight", [] (std::vector<std::any> const&) -> std::any { return chess::Twenty_eight; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Twenty_nine", Neuron{"Twenty_nine", [] (std::vector<std::any> const&) -> std::any { return chess::Twenty_nine; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Thirty", Neuron{"Thirty", [] (std::vector<std::any> const&) -> std::any { return chess::Thirty; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Thirty_one", Neuron{"Thirty_one", [] (std::vector<std::any> const&) -> std::any { return chess::Thirty_one; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Thirty_two", Neuron{"Thirty_two", [] (std::vector<std::any> const&) -> std::any { return chess::Thirty_two; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Thirty_three", Neuron{"Thirty_three", [] (std::vector<std::any> const&) -> std::any { return chess::Thirty_three; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Thirty_four", Neuron{"Thirty_four", [] (std::vector<std::any> const&) -> std::any { return chess::Thirty_four; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Thirty_five", Neuron{"Thirty_five", [] (std::vector<std::any> const&) -> std::any { return chess::Thirty_five; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Thirty_six", Neuron{"Thirty_six", [] (std::vector<std::any> const&) -> std::any { return chess::Thirty_six; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Thirty_seven", Neuron{"Thirty_seven", [] (std::vector<std::any> const&) -> std::any { return chess::Thirty_seven; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Thirty_eight", Neuron{"Thirty_eight", [] (std::vector<std::any> const&) -> std::any { return chess::Thirty_eight; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Thirty_nine", Neuron{"Thirty_nine", [] (std::vector<std::any> const&) -> std::any { return chess::Thirty_nine; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Forty", Neuron{"Forty", [] (std::vector<std::any> const&) -> std::any { return chess::Forty; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Forty_one", Neuron{"Forty_one", [] (std::vector<std::any> const&) -> std::any { return chess::Forty_one; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Forty_two", Neuron{"Forty_two", [] (std::vector<std::any> const&) -> std::any { return chess::Forty_two; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Forty_three", Neuron{"Forty_three", [] (std::vector<std::any> const&) -> std::any { return chess::Forty_three; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Forty_four", Neuron{"Forty_four", [] (std::vector<std::any> const&) -> std::any { return chess::Forty_four; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Forty_five", Neuron{"Forty_five", [] (std::vector<std::any> const&) -> std::any { return chess::Forty_five; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Forty_six", Neuron{"Forty_six", [] (std::vector<std::any> const&) -> std::any { return chess::Forty_six; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Forty_seven", Neuron{"Forty_seven", [] (std::vector<std::any> const&) -> std::any { return chess::Forty_seven; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Forty_eight", Neuron{"Forty_eight", [] (std::vector<std::any> const&) -> std::any { return chess::Forty_eight; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Forty_nine", Neuron{"Forty_nine", [] (std::vector<std::any> const&) -> std::any { return chess::Forty_nine; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Fifty", Neuron{"Fifty", [] (std::vector<std::any> const&) -> std::any { return chess::Fifty; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Fifty_one", Neuron{"Fifty_one", [] (std::vector<std::any> const&) -> std::any { return chess::Fifty_one; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Fifty_two", Neuron{"Fifty_two", [] (std::vector<std::any> const&) -> std::any { return chess::Fifty_two; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Fifty_three", Neuron{"Fifty_three", [] (std::vector<std::any> const&) -> std::any { return chess::Fifty_three; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Fifty_four", Neuron{"Fifty_four", [] (std::vector<std::any> const&) -> std::any { return chess::Fifty_four; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Fifty_five", Neuron{"Fifty_five", [] (std::vector<std::any> const&) -> std::any { return chess::Fifty_five; }, std::vector<std::type_index>{}, typeid(chess::Integer)});

    neurons.emplace("initialBoard", Neuron{"initialBoard", [] (std::vector<std::any> const&) -> std::any { return std::function<std::any(std::vector<std::any> const&)>(chess::initialBoard); }, std::vector<std::type_index>{}, typeid(std::function<std::any(std::vector<std::any> const&)>)});
    neurons.emplace("inPlayerSet", Neuron{"inPlayerSet", [] (std::vector<std::any> const&) -> std::any { return std::function<std::any(std::vector<std::any> const&)>(chess::inPlayerSet); }, std::vector<std::type_index>{}, typeid(std::function<std::any(std::vector<std::any> const&)>)});
    neurons.emplace("outPlayerSet", Neuron{"outPlayerSet", [] (std::vector<std::any> const&) -> std::any { return std::function<std::any(std::vector<std::any> const&)>(chess::outPlayerSet); }, std::vector<std::type_index>{}, typeid(std::function<std::any(std::vector<std::any> const&)>)});
    neurons.emplace("pieceMoves", Neuron{"pieceMoves", [] (std::vector<std::any> const&) -> std::any { return std::function<std::any(std::vector<std::any> const&)>(chess::pieceMoves); }, std::vector<std::type_index>{}, typeid(std::function<std::any(std::vector<std::any> const&)>)});
    neurons.emplace("movePiece", Neuron{"movePiece", [] (std::vector<std::any> const&) -> std::any { return std::function<std::any(std::vector<std::any> const&)>(chess::movePiece); }, std::vector<std::type_index>{}, typeid(std::function<std::any(std::vector<std::any> const&)>)});
    neurons.emplace("at", Neuron{"at", [] (std::vector<std::any> const&) -> std::any { return std::function<std::any(std::vector<std::any> const&)>(chess::at); }, std::vector<std::type_index>{}, typeid(std::function<std::any(std::vector<std::any> const&)>)});

    return neurons;
}

std::map<std::string, Neuron> aicpp::chessDslPrimitiveNeurons()
{
    std::map<std::string, Neuron> neurons;

    neurons.emplace("initialBoard0", Neuron{"initialBoard", chess::initialBoard, std::vector<std::type_index>{}, typeid(chess::Board)});
    neurons.emplace("inPlayerSet0", Neuron{"inPlayerSet", chess::inPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Color>)});
    neurons.emplace("inPlayerSet1", Neuron{"inPlayerSet", chess::inPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Position>)});
    neurons.emplace("inPlayerSet2", Neuron{"inPlayerSet", chess::inPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Types::Kind>)});
    neurons.emplace("outPlayerSet0", Neuron{"outPlayerSet", chess::outPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Color>)});
    neurons.emplace("outPlayerSet1", Neuron{"outPlayerSet", chess::outPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Position>)});
    neurons.emplace("outPlayerSet2", Neuron{"outPlayerSet", chess::outPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Types::Kind>)});
    neurons.emplace("pieceMoves0", Neuron{"pieceMoves", chess::pieceMoves, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Position>)});
    neurons.emplace("pieceMoves1", Neuron{"pieceMoves", chess::pieceMoves, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Position)}, typeid(std::set<chess::Position>)});
    neurons.emplace("pieceMoves2", Neuron{"pieceMoves", chess::pieceMoves, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Types::Kind)}, typeid(std::set<chess::Position>)});
    neurons.emplace("movePiece0", Neuron{"movePiece", chess::movePiece, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color), typeid(chess::Position)}, typeid(chess::Board)});
    neurons.emplace("movePiece1", Neuron{"movePiece", chess::movePiece, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Position), typeid(chess::Position)}, typeid(chess::Board)});
    neurons.emplace("movePiece2", Neuron{"movePiece", chess::movePiece, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Types::Kind), typeid(chess::Position)}, typeid(chess::Board)});
    neurons.emplace("at0", Neuron{"at", chess::at, std::vector<std::type_index>{typeid(std::set<chess::Color>), typeid(chess::Integer)}, typeid(chess::Color)});
    neurons.emplace("at1", Neuron{"at", chess::at, std::vector<std::type_index>{typeid(std::set<chess::Position>), typeid(chess::Integer)}, typeid(chess::Position)});
    neurons.emplace("at2", Neuron{"at", chess::at, std::vector<std::type_index>{typeid(std::set<chess::Types::Kind>), typeid(chess::Integer)}, typeid(chess::Types::Kind)});
    neurons.emplace("at3", Neuron{"at", chess::at, std::vector<std::type_index>{typeid(std::set<chess::Position>), typeid(chess::Integer)}, typeid(chess::Position)});

    return neurons;
}
