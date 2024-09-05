#pragma once

#include "chess/pieces.hpp"
#include "graphics/gl/batch_renderer.hpp"
#include <array>

namespace ftd
{
    struct Piece {
        ChessPieces type;
        bool black = false;
    };

    class ChessBoard {
    public:
        ChessBoard();

        void draw(bool jump = false);
        void move(int x, int y);

    private:
        std::array<Piece, 64> pieces_{};

        gl::Texture tex_;
        gl::BatchRenderer renderer_;

        Piece* current_piece_ = nullptr;
    };
}
