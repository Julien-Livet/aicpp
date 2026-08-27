#include <stdexcept>

#include "aicpp/Chess.h"

std::any chess::initialBoard(std::vector<std::any> const& args)
{
    if (args.size() != 0)
        throw std::runtime_error{"Wrong value"};

    Board board;

    for (Color color{true}; color; color = !color)
    {
        for (Integer i = Types::A; i < Types::H + 1; ++i)
            board.first.emplace(Piece{color, Types::Pawn, Position{Types::Column{i}, Types::Row{color ? 2u : 7u}}});

        board.first.emplace(Piece{color, Types::Rook, Position{Types::A, Types::Row{color ? 1u : 8u}}});
        board.first.emplace(Piece{color, Types::Rook, Position{Types::H, Types::Row{color ? 1u : 8u}}});
        board.first.emplace(Piece{color, Types::Knight, Position{Types::B, Types::Row{color ? 1u : 8u}}});
        board.first.emplace(Piece{color, Types::Knight, Position{Types::G, Types::Row{color ? 1u : 8u}}});
        board.first.emplace(Piece{color, Types::Bishop, Position{Types::C, Types::Row{color ? 1u : 8u}}});
        board.first.emplace(Piece{color, Types::Bishop, Position{Types::F, Types::Row{color ? 1u : 8u}}});
        board.first.emplace(Piece{color, Types::Queen, Position{Types::D, Types::Row{color ? 1u : 8u}}});
        board.first.emplace(Piece{color, Types::King, Position{Types::E, Types::Row{color ? 1u : 8u}}});
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
        auto const& color{std::get<0>(piece_)};
        auto const& kind{std::get<1>(piece_)};
        auto const& position{std::get<2>(piece_)};

        std::set<Position> positions;

        //TODO: ...

        switch (kind)
        {
            case Types::Pawn:
                //TODO: ...
                break;

            case Types::Knight:
                //TODO: ...
                break;

            case Types::Bishop:
                //TODO: ...
                break;

            case Types::Rook:
                //TODO: ...
                break;

            case Types::Queen:
                //TODO: ...
                break;

            case Types::King:
                //TODO: ...
                break;

            default:
                throw std::runtime_error{"Wrong value"};
        }

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

        board_.first.emplace(std::get<0>(piece_), std::get<1>(piece_), position_);

        return board_;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any chess::at(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const container{args[0]};
    auto const index{args[1]};

    if (index.type() != typeid(Integer))
        throw std::runtime_error{"Wrong value"};

    auto const index_{std::any_cast<Integer>(index)};

    if (container.type() == typeid(std::set<Piece>))
    {
        auto const pieces_{std::any_cast<std::set<Piece> >(container)};
        std::vector<Piece> const v{pieces_.begin(), pieces_.end()};

        try
        {
            return v.at(index_);
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }
    else if (container.type() == typeid(std::set<Position>))
    {
        auto const positions_{std::any_cast<std::set<Position> >(container)};
        std::vector<Position> const v{positions_.begin(), positions_.end()};

        try
        {
            return v.at(index_);
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}
