#ifndef AICPP_CHESS_H
#define AICPP_CHESS_H

#include <any>
#include <cstdint>
#include <set>
#include <utility>
#include <vector>

namespace chess
{
    typedef int8_t Integer;
    typedef std::pair<Integer, Integer> Position;
    typedef bool Color;
    typedef std::tuple<Color, Integer, Position> Piece;
    typedef std::set<Piece> Set;
    typedef std::pair<Set, Set> Board;

    Integer constexpr A = 1;
    Integer constexpr B = 2;
    Integer constexpr C = 3;
    Integer constexpr D = 4;
    Integer constexpr E = 5;
    Integer constexpr F = 6;
    Integer constexpr G = 7;
    Integer constexpr H = 8;

    Integer constexpr One = 1;
    Integer constexpr Two = 2;
    Integer constexpr Three = 3;
    Integer constexpr Four = 4;
    Integer constexpr Five = 5;
    Integer constexpr Six = 6;
    Integer constexpr Seven = 7;
    Integer constexpr Eight = 8;

    Integer constexpr Pawn = 0;
    Integer constexpr Knight = 1;
    Integer constexpr Bishop = 2;
    Integer constexpr Rook = 3;
    Integer constexpr Queen = 4;
    Integer constexpr King = 5;

    //Board initialBoard();
    std::any initialBoard(std::vector<std::any> const& args);
    //std::set<Piece> inPlayerSet(Board, Color)
    std::any inPlayerSet(std::vector<std::any> const& args);
    //std::set<Piece> outPlayerSet(Board, Color)
    std::any outPlayerSet(std::vector<std::any> const& args);
    //std::set<Position> pieceMoves(Board, Piece)
    std::any pieceMoves(std::vector<std::any> const& args);
    //Board movePiece(Board, Piece, Position)
    std::any movePiece(std::vector<std::any> const& args);
}

#endif // AICPP_CHESS_H
