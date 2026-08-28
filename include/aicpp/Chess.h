#ifndef AICPP_CHESS_H
#define AICPP_CHESS_H

#include <any>
#include <cstdint>
#include <set>
#include <utility>
#include <vector>

namespace chess
{
    typedef uint Integer;

    enum Kind_ : Integer
    {
        Pawn = 0,
        Knight = 1,
        Bishop = 2,
        Rook = 3,
        Queen = 4,
        King = 5
    };

    enum Column_ : Integer
    {
        A = 1,
        B = 2,
        C = 3,
        D = 4,
        E = 5,
        F = 6,
        G = 7,
        H = 8
    };

    enum Row_ : Integer
    {
        One = 1,
        Two = 2,
        Three = 3,
        Four = 4,
        Five = 5,
        Six = 6,
        Seven = 7,
        Eight = 8
    };

    enum Color_ : bool
    {
        White = true,
        Black = false
    };

    typedef Column_ Column;
    typedef Row_ Row;
    typedef Color_ Color;
    typedef Kind_ Kind;

    using Position_ = std::pair<Column, Row>;

    typedef Position_ Position;

    using Piece_ = std::tuple<Color, Kind, Position>;

    typedef Piece_ Piece;

    using Set = std::set<Piece>;
    using Board_ = std::pair<Set, Set>;

    typedef Board_ Board;

    Piece piece(Board const& board, Position const& position);
    std::set<Position> movablePieces(Board const& board, Color const& color);

    //Board initialBoard();
    std::any initialBoard(std::vector<std::any> const& args);
    //Position pos(Column, Row)
    std::any pos(std::vector<std::any> const& args);
    //std::set<Piece> removedPieces(Board, Color)
    std::any removedPieces(std::vector<std::any> const& args);
    //std::set<Position> mvs(Board, Position)
    std::any mvs(std::vector<std::any> const& args);
    //Board mv(Board, Position, Position)
    std::any mv(std::vector<std::any> const& args);
}

#endif // AICPP_CHESS_H
