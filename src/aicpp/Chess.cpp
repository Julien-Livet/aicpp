#include <stdexcept>

#include "aicpp/Chess.h"

bool isInside(chess::Integer x, chess::Integer y)
{
    return x >= 1 && x <= 8 && y >= 1 && y <= 8;
}

chess::Position makePosition(chess::Integer x, chess::Integer y)
{
    if (!isInside(x, y))
        throw std::runtime_error{"Invalid position"};

    return {static_cast<chess::Column>(x), static_cast<chess::Row>(y)};
}

chess::Set pieces(chess::Board const& board, chess::Color color)
{
    chess::Set pieces;

    for (auto const& piece : board.first)
    {
        if (std::get<0>(piece) == color)
            pieces.emplace(piece);
    }

    return pieces;
}

chess::Piece const* findPiece(chess::Board const& board, chess::Position const& position, chess::Color color)
{
    auto const& set = pieces(board, color);

    for (auto const& piece : set)
    {
        if (std::get<2>(piece) == position)
            return &piece;
    }

    return nullptr;
}

bool chess::clearLine(chess::Board const& board, Position const& from, Position const& to)
{
    auto const x0 = static_cast<Integer>(from.first);
    auto const y0 = static_cast<Integer>(from.second);
    auto const x1 = static_cast<Integer>(to.first);
    auto const y1 = static_cast<Integer>(to.second);
    auto const dx = x1 - x0;
    auto const dy = y1 - y0;
    auto const sx = (dx > 0) - (dx < 0);
    auto const sy = (dy > 0) - (dy < 0);

    auto x = x0 + sx;
    auto y = y0 + sy;

    while (x != x1 || y != y1)
    {
        auto const p = makePosition(x, y);

        if (findPiece(board, p, White) ||
            findPiece(board, p, Black))
            return false;

        x += sx;
        y += sy;
    }

    return true;
}

bool chess::isAttacked(Board const& board, Position const& target, Color byColor)
{
    auto const& enemy = pieces(board, byColor);

    for (auto const& piece : enemy)
    {
        auto const kind = std::get<1>(piece);
        auto const position = std::get<2>(piece);
        auto const x0 = static_cast<Integer>(position.first);
        auto const y0 = static_cast<Integer>(position.second);
        auto const x1 = static_cast<Integer>(target.first);
        auto const y1 = static_cast<Integer>(target.second);
        auto const dx = x1 - x0;
        auto const dy = y1 - y0;
        auto const ax = dx < 0 ? -dx : dx;
        auto const ay = dy < 0 ? -dy : dy;

        switch (kind)
        {
            case Pawn:
            {
                auto const direction = byColor ? 1 : -1;

                if (dy == direction && (dx == 1 || dx == -1))
                    return true;

                break;
            }

            case Knight:
            {
                if ((ax == 1 && ay == 2) || (ax == 2 && ay == 1))
                    return true;

                break;
            }

            case King:
            {
                if (ax <= 1 && ay <= 1 && (ax != 0 || ay != 0))
                    return true;

                break;
            }

            case Bishop:
            {
                if (ax == ay && clearLine(board, position, target))
                    return true;

                break;
            }

            case Rook:
                if ((dx == 0 || dy == 0) && clearLine(board, position, target))
                    return true;
                
                break;

            case Queen:
                if (((dx == 0 || dy == 0) || (ax == ay)) && clearLine(board, position, target))
                    return true;

                break;
        }
    }

    return false;
}

chess::Position findKing( chess::Board const& board, chess::Color color)
{
    for (auto const& piece : pieces(board, color))
    {
        if (std::get<1>(piece) == chess::King)
            return std::get<2>(piece);
    }

    throw std::runtime_error{"King not found"};
}

bool chess::inCheck(Board const& board, Color color)
{
    auto const king = findKing(board, color);

    return isAttacked(board, king, Color{!static_cast<bool>(color)});
}

void castleMoves(chess::Board const& board, chess::Piece const& king, std::set<chess::Position>& positions)
{
    auto const color = std::get<0>(king);

    if (inCheck(board, color))
        return;

    using namespace chess;

    if (color == White)
    {
        // e1-g1
        if (board.whiteKingSideCastle &&
            findPiece(board, {H, One}, White) &&
            !findPiece(board, {F, One}, White) &&
            !findPiece(board, {G, One}, White) &&
            !isAttacked(board, {F, One}, Black) &&
            !isAttacked(board, {G, One}, Black))
        {
            positions.insert({G, One});
        }

        // e1-c1
        if (board.whiteQueenSideCastle &&
            findPiece(board, {A, One}, White) &&
            !findPiece(board, {B, One}, White) &&
            !findPiece(board, {C, One}, White) &&
            !findPiece(board, {D, One}, White) &&
            !isAttacked(board, {D, One}, Black) &&
            !isAttacked(board, {C, One}, Black))
        {
            positions.insert({C, One});
        }
    }
    else
    {
        // e8-g8
        if (board.blackKingSideCastle &&
            findPiece(board, {H, Eight}, Black) &&
            !findPiece(board, {F, Eight}, Black) &&
            !findPiece(board, {G, Eight}, Black) &&
            !isAttacked(board, {F, Eight}, White) &&
            !isAttacked(board, {G, Eight}, White))
        {
            positions.insert({G, Eight});
        }

        // e8-c8
        if (board.blackQueenSideCastle &&
            findPiece(board, {A, Eight}, Black) &&
            !findPiece(board, {B, Eight}, Black) &&
            !findPiece(board, {C, Eight}, Black) &&
            !findPiece(board, {D, Eight}, Black) &&
            !isAttacked(board, {D, Eight}, White) &&
            !isAttacked(board, {C, Eight}, White))
        {
            positions.insert({C, Eight});
        }
    }
}

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

std::set<chess::Position> chess::movablePieces(Board const& board, Color const& color)
{
    std::set<chess::Position> positions;

    for (auto const& piece : board.first)
    {
        if (std::get<0>(piece) == color)
        {
            if (!std::any_cast<std::set<Position> >(mvs({board, std::get<2>(piece)})).empty())
                positions.emplace(std::get<2>(piece));
        }
    }

    return positions;
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

std::any chess::pos(std::vector<std::any> const& args)
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

std::any chess::mvs(std::vector<std::any> const& args)
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

                if (board_.enPassantTarget)
                {
                    auto const x = static_cast<Integer>(position_.first);
                    auto const y = static_cast<Integer>(position_.second);
                    auto const target = *board_.enPassantTarget;
                    auto const targetX = static_cast<Integer>(target.first);
                    auto const targetY = static_cast<Integer>(target.second);

                    if (targetY == y + direction && (targetX == x - 1 || targetX == x + 1))
                        positions.insert(target);
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

        std::set<Position> legal;

        for (auto const& destination : positions)
        {
            try
            {
                auto const next = move(board_, std::get<2>(p), destination, false);

                if (!inCheck(next, color_))
                    legal.insert(destination);
            }
            catch (...)
            {
            }
        }
    
        return legal;
    }

    throw std::runtime_error{"Wrong value"};
}

bool isEnPassant(chess::Board const& board, chess::Piece const& piece, chess::Position const& destination)
{
    using namespace chess;

    if (std::get<1>(piece) != Pawn)
        return false;

    if (!board.enPassantTarget || destination != *board.enPassantTarget)
        return false;

    auto const color = std::get<0>(piece);
    auto const position = std::get<2>(piece);

    if (position.first == destination.first)
        return false;

    Position const capturedPosition{destination.first, position.second};

    Piece const captured{Color{!static_cast<bool>(color)}, Pawn, capturedPosition};

    auto const opponent = pieces(board, Color{!static_cast<bool>(color)});

    return opponent.contains(captured);
}

chess::Board chess::move(Board board, Position const& from, Position const& to, bool check)
{
    auto const p{piece(board, from)};

    if (check)
    {
        auto const moves{std::any_cast<std::set<Position> >(mvs({board, from}))};

        if (!moves.contains(to))
            throw std::runtime_error{"Wrong value"};
    }

    auto const itPiece{board.first.find(p)};

    if (itPiece == board.first.end())
        throw std::runtime_error{"Wrong value"};

    board.first.erase(p);

    for (auto it{board.first.begin()}; it != board.first.end(); ++it)
    {
        if (std::get<2>(*it) == to)
        {
            board.second.emplace(*it);
            board.first.erase(it);

            break;
        }
    }

    board.first.emplace(std::get<0>(p), std::get<1>(p), to);

    auto const& position = from;
    auto const& destination = to;

    if (isEnPassant(board, p, destination))
    {
        Position const capturedPosition{destination.first, std::get<2>(p).second};
        auto const& color = std::get<0>(p);
        Piece const capturedPiece{Color{!static_cast<bool>(color)}, Pawn, capturedPosition};

        board.second.emplace(capturedPiece);
        board.first.erase(capturedPiece);
    }

    board.enPassantTarget.reset();

    auto const& kind = std::get<1>(p);

    if (kind == Pawn)
    {
        auto const y0 = static_cast<int>(position.second);
        auto const y1 = static_cast<int>(destination.second);

        if (std::abs(y1 - y0) == 2)
        {
            auto middle = (y0 + y1) / 2;

            board.enPassantTarget = makePosition(static_cast<Integer>(position.first), middle);
        }
    }

    return board;
}

std::any chess::mv(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const board{args[0]};
    auto const from{args[1]};
    auto const to{args[2]};

    if (board.type() == typeid(Board) && from.type() == typeid(Position) && to.type() == typeid(Position))
    {
        auto const board_{std::any_cast<Board>(board)};
        auto const from_{std::any_cast<Position>(from)};
        auto const to_{std::any_cast<Position>(to)};
        
        return move(board_, from_, to_);
    }

    throw std::runtime_error{"Wrong value"};
}
