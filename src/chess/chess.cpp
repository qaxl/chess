#include "chess.hpp"
#include "chess/pieces.hpp"
#include "graphics/gl/batch_renderer.hpp"

namespace ftd {
ChessBoard::ChessBoard() : tex_("assets/textures/pieces.png"), renderer_(tex_) {
  // initial setting

  for (size_t row = 0; row < 8; ++row) {
    if (row == 0 || row == 7) {
      for (size_t i = 0; i < 8; ++i) {
        if (i == 0 || i == 7) {
          pieces_[(row * 8) + i] = Piece{ChessPieces::Rook, row == 7};
        } else if (i == 1 || i == 6) {
          pieces_[(row * 8) + i] = Piece{ChessPieces::Knight, row == 7};
        } else if (i == 2 || i == 5) {
          pieces_[(row * 8) + i] = Piece{ChessPieces::Bishop, row == 7};
        } else if (i == 3) {
          pieces_[(row * 8) + i] = Piece{ChessPieces::Queen, row == 7};
        } else {
          pieces_[(row * 8) + i] = Piece{ChessPieces::King, row == 7};
        }
      }
    } else if (row == 1 || row == 6) {
      for (size_t i = 0; i < 8; ++i) {
        pieces_[(row * 8) + i] = Piece{ChessPieces::Pawn, row == 6};
      }
    }
  }
}

void ChessBoard::draw() {
  int x = 0, y = 0;
  static float d = 0.0f;

  // printf("%zu\n", pieces_.size());

  renderer_.begin();
  for (size_t i = 0; i < pieces_.size(); ++i) {
    if (i % 8 == 0 && i != 0) {
      y += 60;
      x = 0;
    }

    int oldy = y;

    if (pieces_[i].type != ChessPieces::Empty) {
      // if (pieces_[i].type == ChessPieces::Pawn)
      // printf("pawn %zu %d:%d\n", i, x, y);

      float tx, ty;
      chess_piece_tex_coord(pieces_[i].black, pieces_[i].type, tx, ty);
      renderer_.draw(x, y, tx, ty, 60.0f, 60.0f, &pieces_[i] == current_piece_);
    }

    if (pieces_[i].highlight) {
      renderer_.draw(x, y, 0, 0, 60.0f, 60.0f, true, false);
    }

    x += 60;
    y = oldy;
  }
  renderer_.flush();
}

void ChessBoard::move(int x, int y) {
  x /= 60;
  y /= 60;

  printf("clicked at %d:%d; %d\n", x, y, y * 8 + x);

  if (current_piece_) {
    if (pieces_[y * 8 + x].type != ChessPieces::Empty) {
      printf("ate a piece of type: %d\n", (int)pieces_[y * 8 + x].type);
    }

    pieces_[y * 8 + x] = {current_piece_->type, current_piece_->black, false};
    current_piece_->black = false;
    current_piece_->type = ChessPieces::Empty;
    current_piece_ = nullptr;
  } else {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
      printf("Invalid move\n");
      return;
    }

    switch (pieces_[y * 8 + x].type) {
    case ChessPieces::Empty:
      break;
    case ChessPieces::Pawn:
      if (pieces_[y * 8 + x].black) {
        if (y - 1 < 8) {
          pieces_[(y - 1) * 8 + x].highlight = true;
        }
      } else {
        if (y + 1 < 8) {
          pieces_[(y + 1) * 8 + x].highlight = true;
        }
      }
      break;
    case ChessPieces::Bishop:
      break;
    case ChessPieces::Knight:
    case ChessPieces::Rook:
    case ChessPieces::Queen:
    case ChessPieces::King:
      break;
    }

    if (pieces_[y * 8 + x].type != ChessPieces::Empty) {
      current_piece_ = &pieces_[y * 8 + x];
    }
  }
}
} // namespace ftd
