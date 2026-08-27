#ifndef AICPP_CHESS_H
#define AICPP_CHESS_H

#include <any>
#include <cstdint>
#include <set>
#include <utility>
#include <vector>

namespace chess
{
    typedef int Integer;

    enum Kind : Integer
    {
        Pawn,
        Knight,
        Bishop,
        Rook,
        Queen,
        King
    };

    enum Column : Integer
    {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H
    };

    enum Row : Integer
    {
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight
    };

    typedef std::pair<Column, Row> Position;
    typedef bool Color;
    typedef std::tuple<Color, Kind, Position> Piece;
    typedef std::set<Piece> Set;
    typedef std::pair<Set, Set> Board;

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
