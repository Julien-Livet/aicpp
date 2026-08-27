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

    namespace Types
    {
        enum Kind : Integer
        {
            Pawn = 0,
            Knight,
            Bishop,
            Rook,
            Queen,
            King
        };

        enum Column : Integer
        {
            A = 1,
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
            One = 1,
            Two,
            Three,
            Four,
            Five,
            Six,
            Seven,
            Eight
        };
    }

    typedef std::pair<Types::Column, Types::Row> Position;
    typedef bool Color;
    typedef std::tuple<Color, Types::Kind, Position> Piece;
    typedef std::set<Piece> Set;
    typedef std::pair<Set, Set> Board;

    Integer constexpr Zero = 0;
    Integer constexpr One = 1;
    Integer constexpr Two = 2;
    Integer constexpr Three = 3;
    Integer constexpr Four = 4;
    Integer constexpr Five = 5;
    Integer constexpr Six = 6;
    Integer constexpr Seven = 7;
    Integer constexpr Eight = 8;
    Integer constexpr Nine = 9;
    Integer constexpr Ten = 10;
    Integer constexpr Eleven = 11;
    Integer constexpr Twelve = 12;
    Integer constexpr Thirteen = 13;
    Integer constexpr Fourteen = 14;
    Integer constexpr Fifteen = 15;
    Integer constexpr sixteen = 16;
    Integer constexpr seventeen = 17;
    Integer constexpr eighteen = 18;
    Integer constexpr nineteen = 19;
    Integer constexpr Twenty = 20;
    Integer constexpr Twenty_one = 21;
    Integer constexpr Twenty_two = 22;
    Integer constexpr Twenty_three = 23;
    Integer constexpr Twenty_four = 24;
    Integer constexpr Twenty_five = 25;
    Integer constexpr Twenty_six = 26;
    Integer constexpr Twenty_seven = 27;

    Color constexpr White = true;
    Color constexpr Black = false;

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
    //Piece at(std::set<Piece>, Integer)
    //Position at(std::set<Position>, Integer)
    std::any at(std::vector<std::any> const& args);
}

#endif // AICPP_CHESS_H
