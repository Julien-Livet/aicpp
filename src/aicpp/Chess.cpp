#include <stdexcept>

#include "aicpp/Chess.h"

chess::Piece chess::piece(Board const& board, Position const& position)
{
    for (auto const& p : board.first)
    {
        if (std::get<2>(p) == position)
            return p;
    }

    for (auto const& p : board.second)
    {
        if (std::get<2>(p) == position)
            return p;
    }

    throw std::runtime_error{"Wrong value"};
}

std::set<chess::Piece> chess::movablePieces(Board const& board, Color const& color)
{
    Set set;

    for (auto const& piece : board.second)
    {
        if (std::get<0>(piece) == color)
        {
            if (!std::any_cast<std::set<Position> >(pieceMoves({board, piece})).empty())
                set.emplace(piece);
        }
    }

    return set;
}

std::any chess::initialBoard(std::vector<std::any> const& args)
{
    if (args.size() != 0)
        throw std::runtime_error{"Wrong value"};

    Board board;

    for (unsigned char j{0}; j < 2; ++j)
    {
        Color const color{j == 0};

        for (Integer i = A; i < H + 1; ++i)
            board.first.emplace(Piece{color, Pawn, Position{Column{i}, Row{color ? 2u : 7u}}});

        board.first.emplace(Piece{color, Rook, Position{A, Row{color ? 1u : 8u}}});
        board.first.emplace(Piece{color, Rook, Position{H, Row{color ? 1u : 8u}}});
        board.first.emplace(Piece{color, Knight, Position{B, Row{color ? 1u : 8u}}});
        board.first.emplace(Piece{color, Knight, Position{G, Row{color ? 1u : 8u}}});
        board.first.emplace(Piece{color, Bishop, Position{C, Row{color ? 1u : 8u}}});
        board.first.emplace(Piece{color, Bishop, Position{F, Row{color ? 1u : 8u}}});
        board.first.emplace(Piece{color, Queen, Position{D, Row{color ? 1u : 8u}}});
        board.first.emplace(Piece{color, King, Position{E, Row{color ? 1u : 8u}}});
    }

    return board;
}

std::any chess::position(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const column{args[0]};
    auto const row{args[1]};

    if (column.type() == typeid(Column) && row.type() == typeid(Row))
    {
        auto const column_{std::any_cast<Column>(column)};
        auto const row_{std::any_cast<Row>(row)};
        
        return Position{column_, row_};
    }

    throw std::runtime_error{"Wrong value"};
}

std::any chess::removedPieces(std::vector<std::any> const& args)
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
    auto const position{args[1]};

    if (board.type() == typeid(Board) && position.type() == typeid(Position))
    {
        auto const board_{std::any_cast<Board>(board)};
        auto const position_{std::any_cast<Position>(position)};
        auto const p{piece(board_, position_)};
        auto const color_{std::get<0>(p)};
        auto const kind_{std::get<1>(p)};

        std::set<Position> positions;

        if (board_.second.contains(p))
            return positions;

        auto validPosition = [] (int column, int row) -> bool
        {
            return column >= A && column <= H && row >= One && row <= Eight;
        };

        auto pieceAt = [&board_] (Position const& position) -> Piece const*
        {
            for (auto const& piece : board_.first)
            {
                if (std::get<2>(piece) == position)
                    return &piece;
            }

            return nullptr;
        };

        auto addPosition = [&] (int column, int row)
        {
            if (!validPosition(column, row))
                return;

            Position const candidate{Column{static_cast<Integer>(column)}, Row{static_cast<Integer>(row)}};

            auto const target = pieceAt(candidate);

            if (target == nullptr || std::get<0>(*target) != color_)
                positions.emplace(candidate);
        };

        auto addRay = [&] (int dc, int dr)
        {
            int column = static_cast<int>(std::get<0>(position_));
            int row = static_cast<int>(std::get<1>(position_));

            while (true)
            {
                column += dc;
                row += dr;

                if (!validPosition(column, row))
                    break;

                Position const candidate{Column{static_cast<Integer>(column)}, Row{static_cast<Integer>(row)}};
                auto const target = pieceAt(candidate);

                if (target == nullptr)
                {
                    positions.emplace(candidate);
                    continue;
                }

                if (std::get<0>(*target) != color_)
                    positions.emplace(candidate);

                break;
            }
        };

        int const column = static_cast<int>(std::get<0>(position_));
        int const row = static_cast<int>(std::get<1>(position_));

        switch (kind_)
        {
            case Pawn:
            {
                int const direction = color_ == White ? 1 : -1;
                auto const nextRow = static_cast<Integer>(row + direction);

                if (validPosition(column, nextRow))
                {
                    Position const candidate{Column{static_cast<Integer>(column)}, Row{nextRow}};

                    if (pieceAt(candidate) == nullptr)
                    {
                        positions.emplace(candidate);

                        bool const initialRow = (color_ == White && row == Two) || (color_ == Black && row == Seven);

                        if (initialRow)
                        {
                            auto const doubleRow = static_cast<Integer>(row + 2 * direction);

                            Position const doubleCandidate{Column{static_cast<Integer>(column)}, Row{doubleRow}};

                            if (pieceAt(doubleCandidate) == nullptr)
                                positions.emplace(doubleCandidate);
                        }
                    }
                }

                for (int dc : {-1, 1})
                {
                    auto const captureColumn = static_cast<Integer>(column + dc);
                    auto const captureRow = static_cast<Integer>(row + direction);

                    if (!validPosition(captureColumn, captureRow))
                        continue;

                    Position const candidate{Column{captureColumn}, Row{captureRow}};
                    auto const target = pieceAt(candidate);

                    if (target != nullptr && std::get<0>(*target) != color_)
                        positions.emplace(candidate);
                }

                break;
            }

            case Knight:
            {
                static constexpr int offsets[][2] = {
                    { 1,  2},
                    { 2,  1},
                    { 2, -1},
                    { 1, -2},
                    {-1, -2},
                    {-2, -1},
                    {-2,  1},
                    {-1,  2}
                };

                for (auto const& offset : offsets)
                    addPosition(column + offset[0], row + offset[1]);

                break;
            }

            case Bishop:
            {
                addRay( 1,  1);
                addRay( 1, -1);
                addRay(-1,  1);
                addRay(-1, -1);

                break;
            }

            case Rook:
            {
                addRay( 1,  0);
                addRay(-1,  0);
                addRay( 0,  1);
                addRay( 0, -1);

                break;
            }

            case Queen:
            {
                addRay( 1,  0);
                addRay(-1,  0);
                addRay( 0,  1);
                addRay( 0, -1);

                addRay( 1,  1);
                addRay( 1, -1);
                addRay(-1,  1);
                addRay(-1, -1);

                break;
            }

            case King:
            {
                for (int dc = -1; dc <= 1; ++dc)
                {
                    for (int dr = -1; dr <= 1; ++dr)
                    {
                        if (dc != 0 || dr != 0)
                            addPosition(column + dc, row + dr);
                    }
                }

                break;
            }

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
    auto const from{args[1]};
    auto const to{args[2]};

    if (board.type() == typeid(Board) && from.type() == typeid(Position) && to.type() == typeid(Position))
    {
        auto board_{std::any_cast<Board>(board)};
        auto const from_{std::any_cast<Position>(from)};
        auto const to_{std::any_cast<Position>(to)};
        auto const p{piece(board_, from_)};
        auto const moves{std::any_cast<std::set<Position> >(pieceMoves({board, from_}))};

        if (!moves.contains(to_))
            throw std::runtime_error{"Wrong value"};

        auto const itPiece{board_.first.find(p)};

        if (itPiece == board_.first.end())
            throw std::runtime_error{"Wrong value"};

        board_.first.erase(p);

        for (auto it{board_.first.begin()}; it != board_.first.end(); ++it)
        {
            if (std::get<2>(*it) == to_)
            {
                board_.second.emplace(*it);
                board_.first.erase(it);

                break;
            }
        }

        board_.first.emplace(std::get<0>(p), std::get<1>(p), to_);

        return board_;
    }

    throw std::runtime_error{"Wrong value"};
}
