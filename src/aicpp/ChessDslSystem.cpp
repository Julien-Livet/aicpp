#include "aicpp/ChessDslSystem.h"
#include "aicpp/Chess.h"

using namespace aicpp;

std::map<std::string, Neuron> aicpp::chessDslVariableNeurons()
{
    std::map<std::string, Neuron> neurons;

    neurons.emplace("A", Neuron{"A", [] (std::vector<std::any> const&) -> std::any { return chess::A; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("B", Neuron{"B", [] (std::vector<std::any> const&) -> std::any { return chess::B; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("C", Neuron{"C", [] (std::vector<std::any> const&) -> std::any { return chess::C; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("D", Neuron{"D", [] (std::vector<std::any> const&) -> std::any { return chess::D; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("E", Neuron{"E", [] (std::vector<std::any> const&) -> std::any { return chess::E; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("F", Neuron{"F", [] (std::vector<std::any> const&) -> std::any { return chess::F; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("G", Neuron{"G", [] (std::vector<std::any> const&) -> std::any { return chess::G; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("H", Neuron{"H", [] (std::vector<std::any> const&) -> std::any { return chess::H; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("One", Neuron{"One", [] (std::vector<std::any> const&) -> std::any { return chess::One; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Two", Neuron{"Two", [] (std::vector<std::any> const&) -> std::any { return chess::Two; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Three", Neuron{"Three", [] (std::vector<std::any> const&) -> std::any { return chess::Three; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Four", Neuron{"Four", [] (std::vector<std::any> const&) -> std::any { return chess::Four; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Five", Neuron{"Five", [] (std::vector<std::any> const&) -> std::any { return chess::Five; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Six", Neuron{"Six", [] (std::vector<std::any> const&) -> std::any { return chess::Six; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Seven", Neuron{"Seven", [] (std::vector<std::any> const&) -> std::any { return chess::Seven; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Eight", Neuron{"Eight", [] (std::vector<std::any> const&) -> std::any { return chess::Eight; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Pawn", Neuron{"Pawn", [] (std::vector<std::any> const&) -> std::any { return chess::Pawn; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Knight", Neuron{"Knight", [] (std::vector<std::any> const&) -> std::any { return chess::Knight; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Bishop", Neuron{"Bishop", [] (std::vector<std::any> const&) -> std::any { return chess::Bishop; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Rook", Neuron{"Rook", [] (std::vector<std::any> const&) -> std::any { return chess::Rook; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("Queen", Neuron{"Queen", [] (std::vector<std::any> const&) -> std::any { return chess::Queen; }, std::vector<std::type_index>{}, typeid(chess::Integer)});
    neurons.emplace("King", Neuron{"King", [] (std::vector<std::any> const&) -> std::any { return chess::King; }, std::vector<std::type_index>{}, typeid(chess::Integer)});

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
    neurons.emplace("inPlayerSet1", Neuron{"inPlayerSet", chess::inPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Integer>)});
    neurons.emplace("inPlayerSet2", Neuron{"inPlayerSet", chess::inPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Position>)});
    neurons.emplace("outPlayerSet0", Neuron{"outPlayerSet", chess::outPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Color>)});
    neurons.emplace("outPlayerSet1", Neuron{"outPlayerSet", chess::outPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Integer>)});
    neurons.emplace("outPlayerSet2", Neuron{"outPlayerSet", chess::outPlayerSet, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Position>)});
    neurons.emplace("pieceMoves0", Neuron{"pieceMoves", chess::pieceMoves, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color)}, typeid(std::set<chess::Position>)});
    neurons.emplace("pieceMoves1", Neuron{"pieceMoves", chess::pieceMoves, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Integer)}, typeid(std::set<chess::Position>)});
    neurons.emplace("pieceMoves2", Neuron{"pieceMoves", chess::pieceMoves, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Position)}, typeid(std::set<chess::Position>)});
    neurons.emplace("movePiece0", Neuron{"movePiece", chess::movePiece, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Color), typeid(chess::Position)}, typeid(chess::Board)});
    neurons.emplace("movePiece1", Neuron{"movePiece", chess::movePiece, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Integer), typeid(chess::Position)}, typeid(chess::Board)});
    neurons.emplace("movePiece2", Neuron{"movePiece", chess::movePiece, std::vector<std::type_index>{typeid(chess::Board), typeid(chess::Position), typeid(chess::Position)}, typeid(chess::Board)});

    return neurons;
}
