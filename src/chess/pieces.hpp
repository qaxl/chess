#pragma once

#include <cstdint>

namespace ftd
{
    enum class ChessPieces : uint8_t {
        Empty,
        Pawn,
        Bishop,
        Knight,
        Rook,
        Queen,
        King,
    };

    constexpr void chess_piece_tex_coord(bool black, ChessPieces type, float& x, float& y) {
        y = black ? 0.5f : 0.0f;

        switch (type) {
        case ChessPieces::Empty:
            throw "empty cannot be drawn!";
            break;

        case ChessPieces::Pawn:
            x = 300.0f / 360.0f;
            break;

        case ChessPieces::Bishop:
            x = 240.0f / 360.0f;
            break;

        case ChessPieces::Knight:
            x = 180.0f / 360.0f;
            break;

        case ChessPieces::Rook:
            x = 120.0f / 360.0f;
            break;

        case ChessPieces::Queen:
            x = 0.0f / 360.0f;
            break;

        case ChessPieces::King:
            x = 60.0f / 360.0f;
            break;
        }
    }
}
