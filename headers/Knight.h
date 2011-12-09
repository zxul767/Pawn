/*=============================================================================
  Class name: Knight

  Responsabilities: 
  -Provide the set of moves a knight can make from any square on the board.

  Date: September 01, 2007
  =============================================================================*/

#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include "Board.h"

class Knight : public Piece
{
 public:
   Knight ();
   ~Knight ();

   bitboard get_moves (u_int square, 
                       Player player, 
                       const Board* board) const;

   bitboard get_potential_moves (u_int square, Player player) const;

 private:


   void compute_moves ();

   bitboard moves_from[Board::SQUARES];
};

#endif 