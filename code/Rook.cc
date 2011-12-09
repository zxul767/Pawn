/*=============================================================================
  Class name: Rook

  Responsabilities: 
  -Provide the set of moves a rook can make from any square on the board.

  Collaborations:

  Version: 0.1

  Date: September 01, 2007
  =============================================================================*/
#include "Rook.h"

Rook::Rook ()
{
   compute_moves ();
}

Rook::~Rook ()
{

}

/*=============================================================================
  Get all moves from SQUARE in the current BOARD assumming it is PLAYER'S turn
  to move (moves that may leave the king in check are also included)

  See ATTACKS_algorithm.txt for a graphic explanation of the algorithm used 
  here.
  ============================================================================*/
bitboard
Rook::get_moves (u_int square, Piece::Player player, const Board* board) const
{
   bitboard          attacks = 0;
   bitboard          blocking_pieces;
   bitboard          all_pieces;
   Board::Squares    blocker; // First blocking piece

   all_pieces = board->get_all_pieces ();

   // Compute attacks to each of the possible directions a rook can point to
   for (RowColumn ray = NORTH; ray <= WEST; ++ray)
   {
      blocking_pieces = get_ray (Board::Squares (square), ray) & all_pieces;
      
      if (ray == NORTH || ray == WEST)
         blocker = Board::Squares (Util::MSB_position (blocking_pieces));
      else
         blocker = Board::Squares (Util::LSB_position (blocking_pieces));

      attacks |= 
         get_ray (Board::Squares (square), ray) ^ 
         (blocking_pieces ? get_ray (blocker, ray) : 0);
   }
   attacks &= ~board->get_pieces (player);
   return attacks;
}

/*=============================================================================
  Return all possible moves from SQUARE, assuming the board is empty.
  ============================================================================*/
bitboard
Rook::get_potential_moves (u_int square, Player player) const
{
   if (Board::is_inside_board (square))
      return all_moves_from[square];

   return 0;
}

/*=============================================================================
  Compute all moves a bishop can make from every square on the board assuming
  the board is empty.
  ============================================================================*/
void
Rook::compute_moves ()
{
   int       dx[Piece::RAYS] = {  0, +1,  0, -1 };
   int       dy[Piece::RAYS] = { -1,  0, +1,  0 };
   
   for (Board::Squares square = Board::a8; square <= Board::h1; ++square)
   {
      for (u_int ray = 0; ray < Piece::RAYS; ++ray)
         moves_from[square][ray] = 0;
      all_moves_from[square] = 0;
   }

   for (u_int row = 0; row < Board::SIZE; ++row)
      for (u_int col = 0; col < Board::SIZE; ++col)
      {
         Board::Squares square = Board::Squares (row * Board::SIZE + col);
         RowColumn ray;

         /*==================================================================== 
           Traverse all four directions a rook can move to

                 N   
                 |           N : North
           W ____|____ E     E : East
                 |           S : South
                 |           W : West
                 S
           ===================================================================*/
         for (ray = Piece::NORTH; ray <= Piece::WEST; ++ray)
         {
            int y = row;
            int x = col;
            while (Board::is_inside_board (y + dy[ray], x + dx[ray]))
            {
               y += dy[ray];
               x += dx[ray];           
               moves_from[square][ray] |= (Util::one << (y * Board::SIZE + x));
            }
            all_moves_from[square] |= moves_from[square][ray];
         }
      }
}


/*=============================================================================
  Return all possible moves from SQUARE following DIRECTION, assuming the
  board is empty.
  ============================================================================*/
bitboard 
Rook::get_ray (Board::Squares square, 
               RowColumn      direction) const
{
   if (Board::is_inside_board (square))
      return moves_from[square][direction];

   return 0;
}
