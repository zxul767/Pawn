/*==============================================================================
 | Class name: Board                                                           |
 |                                                                             |
 | Responsabilities:                                                           |
 | -Provide an interface for a chess board using bitboards as the basic data   |
 |  structure                                                                  |
 |                                                                             |
 | Date: September 1, 2007                                                     |
 ==============================================================================*/

#include "Board.h"

Board::Board ()
{
}

Board::~Board ()
{
}

bool 
Board::is_inside_board (int row, int col)
{
   return (row >= 0 && row < (int)SIZE) && (col >= 0 && col < (int)SIZE);
}

bool 
Board::is_inside_board (u_int row, u_int col)
{
   return (row < SIZE) && (col < SIZE);
}

bool 
Board::is_inside_board (u_int square)
{
   return (square < SQUARES);
}

ostream& 
operator << (ostream& out, const Board& board)
{
   static const u_int nplayers = Board::PLAYERS;

   static const string 
      piece_to_string[][nplayers] = { { "  P  ", " *P* " },
                                      { "  N  ", " *N* " },
                                      { "  B  ", " *B* " },
                                      { "  R  ", " *R* " },
                                      { "  Q  ", " *Q* " },
                                      { "  K  ", " *K* " },
      };
   
   out << "  -------------------------------------------------" << endl;
   for (u_int row = 0; row < Board::SIZE; ++row)
   {
      out << "  |     |     |     |     |     |     |     |     |" << endl;
      out << (Board::SIZE - row) << ' ';

      for (u_int col = 0; col < Board::SIZE; ++col)
      {
         out << '|';
         
         Board::Squares square = (Board::Squares) (row * Board::SIZE + col);
         Piece::Player  player = board.get_piece_color (square);
         Piece::Type    piece  = board.get_piece (square);

         if ((player != Piece::NULL_PLAYER) && (piece != Piece::NULL_PIECE))
         {
            out << piece_to_string[piece][player];
         }
         else
            // If there is nothing in (row, col) just output an empty square
            out << "     ";

      }
      out << '|' << endl;
      out << "  -------------------------------------------------" << endl;
   }
   
   // Display algebraic coordinates
   out << "     a     b     c     d     e     f     g     h   " << endl;

   return out;
}