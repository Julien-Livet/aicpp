#include <stdexcept>

#include "aicpp/Chess.h"

std::any chess::initialBoard(std::vector<std::any> const& args)
{
    if (args.size() != 0)
        throw std::runtime_error{"Wrong value"};

    Board board;

    for (Color color{true}; color; color = !color)
    {
        for (Integer i = A; i < H + 1; ++i)
            board.first.emplace(Piece{color, Pawn, Position{i, color ? 2 : 7}});

        board.first.emplace(Piece{color, Rook, Position{A, color ? 1 : 8}});
        board.first.emplace(Piece{color, Rook, Position{H, color ? 1 : 8}});
        board.first.emplace(Piece{color, Knight, Position{B, color ? 1 : 8}});
        board.first.emplace(Piece{color, Knight, Position{G, color ? 1 : 8}});
        board.first.emplace(Piece{color, Bishop, Position{C, color ? 1 : 8}});
        board.first.emplace(Piece{color, Bishop, Position{F, color ? 1 : 8}});
        board.first.emplace(Piece{color, Queen, Position{D, color ? 1 : 8}});
        board.first.emplace(Piece{color, King, Position{E, color ? 1 : 8}});
    }

    return board;
}

std::any chess::inPlayerSet(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const board{args[0]};
    auto const color{args[1]};

    if (board.type() == typeid(Board) && color.type() == typeid(Color))
    {
        auto const board_{std::any_cast<Board>(board)};
        auto const color_{std::any_cast<Color>(color)};

        Set set;

        for (auto const& piece : board_.first)
        {
            if (std::get<0>(piece) == color_)
                set.emplace(piece);
        }

        return set;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any chess::outPlayerSet(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const board{args[0]};
    auto const color{args[1]};

    if (board.type() == typeid(Board) && color.type() == typeid(Color))
    {
        auto const board_{std::any_cast<Board>(board)};
        auto const color_{std::any_cast<Color>(color)};

        Set set;

        for (auto const& piece : board_.second)
        {
            if (std::get<0>(piece) == color_)
                set.emplace(piece);
        }

        return set;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any chess::pieceMoves(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const board{args[0]};
    auto const piece{args[1]};

    if (board.type() == typeid(Board) && piece.type() == typeid(Piece))
    {
        auto const board_{std::any_cast<Board>(board)};
        auto const piece_{std::any_cast<Piece>(piece)};

        std::set<Position> positions;

        //TODO: ...

        return positions;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any chess::movePiece(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const board{args[0]};
    auto const piece{args[1]};
    auto const position{args[2]};

    if (board.type() == typeid(Board) && piece.type() == typeid(Piece) && position.type() == typeid(Position))
    {
        auto board_{std::any_cast<Board>(board)};
        auto const piece_{std::any_cast<Piece>(piece)};
        auto const position_{std::any_cast<Position>(position)};

        auto const moves{std::any_cast<std::set<Position> >(pieceMoves({board, piece}))};

        if (!moves.contains(position_))
            throw std::runtime_error{"Wrong value"};


        auto const itPiece{board_.first.find(piece_)};

        if (itPiece == board_.first.end())
            throw std::runtime_error{"Wrong value"};

        board_.first.erase(piece_);

        for (auto it{board_.first.begin()}; it != board_.first.end(); ++it)
        {
            if (std::get<2>(*it) == position_)
            {
                board_.second.emplace(*it);
                board_.first.erase(it);

                break;
            }
        }

        board_.first.emplace(std::get<0>(piece_), std::get<1>(piece_),position_);

        return board_;
    }

    throw std::runtime_error{"Wrong value"};
}
