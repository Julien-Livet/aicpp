#include "aicpp/ChessDslSystem.h"
#include "aicpp/Chess.h"

using namespace aicpp;

std::map<std::string, Neuron> aicpp::chessDslVariableNeurons()
{
    std::map<std::string, Neuron> neurons;


    neurons.emplace("initialBoard", Neuron{"initialBoard", [] (std::vector<std::any> const&) -> std::any { return std::function<std::any(std::vector<std::any> const&)>(chess::initialBoard); }, std::vector<std::type_index>{}, typeid(std::function<std::any(std::vector<std::any> const&)>)});
    neurons.emplace("inPlayerSet", Neuron{"inPlayerSet", [] (std::vector<std::any> const&) -> std::any { return std::function<std::any(std::vector<std::any> const&)>(chess::inPlayerSet); }, std::vector<std::type_index>{}, typeid(std::function<std::any(std::vector<std::any> const&)>)});
    neurons.emplace("outPlayerSet", Neuron{"outPlayerSet", [] (std::vector<std::any> const&) -> std::any { return std::function<std::any(std::vector<std::any> const&)>(chess::outPlayerSet); }, std::vector<std::type_index>{}, typeid(std::function<std::any(std::vector<std::any> const&)>)});
    neurons.emplace("pieceMoves", Neuron{"pieceMoves", [] (std::vector<std::any> const&) -> std::any { return std::function<std::any(std::vector<std::any> const&)>(chess::pieceMoves); }, std::vector<std::type_index>{}, typeid(std::function<std::any(std::vector<std::any> const&)>)});
    neurons.emplace("movePiece", Neuron{"movePiece", [] (std::vector<std::any> const&) -> std::any { return std::function<std::any(std::vector<std::any> const&)>(chess::movePiece); }, std::vector<std::type_index>{}, typeid(std::function<std::any(std::vector<std::any> const&)>)});

    return neurons;
}

std::map<std::string, Neuron> aicpp::chessDslPrimitiveNeurons()
{
    std::map<std::string, Neuron> neurons;

    neurons.emplace("initialBoard0", Neuron{"initialBoard", chess::initialBoard, std::vector<std::type_index>{}, typeid(chess::Board)});
    neurons.emplace("inPlayerSet0", Neuron{"inPlayerSet", chess::inPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Color>)});
    neurons.emplace("inPlayerSet1", Neuron{"inPlayerSet", chess::inPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Kind>)});
    neurons.emplace("inPlayerSet2", Neuron{"inPlayerSet", chess::inPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Position>)});
    neurons.emplace("outPlayerSet0", Neuron{"outPlayerSet", chess::outPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Color>)});
    neurons.emplace("outPlayerSet1", Neuron{"outPlayerSet", chess::outPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Kind>)});
    neurons.emplace("outPlayerSet2", Neuron{"outPlayerSet", chess::outPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Position>)});
    neurons.emplace("pieceMoves0", Neuron{"pieceMoves", chess::pieceMoves, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Position>)});
    neurons.emplace("pieceMoves1", Neuron{"pieceMoves", chess::pieceMoves, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Kind)}, typeid(std::set<chess::Position>)});
    neurons.emplace("pieceMoves2", Neuron{"pieceMoves", chess::pieceMoves, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Position)}, typeid(std::set<chess::Position>)});
    neurons.emplace("movePiece0", Neuron{"movePiece", chess::movePiece, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color), typeid(chess::Position)}, typeid(chess::Board)});
    neurons.emplace("movePiece1", Neuron{"movePiece", chess::movePiece, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Kind), typeid(chess::Position)}, typeid(chess::Board)});
    neurons.emplace("movePiece2", Neuron{"movePiece", chess::movePiece, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Position), typeid(chess::Position)}, typeid(chess::Board)});

    return neurons;
}
