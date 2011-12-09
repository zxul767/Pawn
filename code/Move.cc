/*=============================================================================
  Class name: Move

  Responsabilities: 
  -Specify the initial and final coordinates of a moving piece
  -Specify the nature of the move (CAPTURE, PAWN PROMOTION, etc.)

  Collaborations: This class is used by MoveGenerator, MoveReader, Board,

  Version: 0.1

  Date: August 25, 2007
  ============================================================================*/
#include "Move.h"
#include "Board.h"
#include <cctype>
#include <cstdlib>

/*=============================================================================
  Create a move given an algebraic chess notation. 

  For instance, the notation e2e4 denotes the movement of the king's pawn from 
  its initial square to the center of the board.
  ============================================================================*/
Move::Move (const string& move_notation)
{   
   if (!translate_to_square (move_notation.substr (0, 2), start) ||
       !translate_to_square (move_notation.substr (2, 2), end))
   {
      // Create a null move if NOTATION was incorrect
      score = 0;
      start = end = Board::a8;
      type  = NULL_MOVE;
      moving_piece = Piece::NULL_PIECE;
      captured_piece = Piece::NULL_PIECE;
   }
}

/*=============================================================================
  Create a dummy move.

  This constructor is called when we declare a variable of type Move just to 
  assign a value to it from another one.
  =============================================================================*/
Move::Move ()
{
   score = 0;
   start = Board::a1;
   end   = Board::a1;
   type  = NULL_MOVE;
   moving_piece = Piece::NULL_PIECE;
   captured_piece = Piece::NULL_PIECE;
}

Move::Move (const Move& move)
{
   score = move.score;
   start = move.start;
   end = move.end;
   type = move.type;
   moving_piece = move.moving_piece;
   captured_piece = move.captured_piece;
}

/*=============================================================================
  Create a move without specifying its type. 
  
  This is done this way  since the kind of move is usually known only after some 
  processing which requires only the START and END squares
  ============================================================================*/
Move::Move (Board::Squares start,
            Board::Squares end)
{
   score = 0;
   this->start = start;
   this->end = end;
   type = NULL_MOVE;
   moving_piece = Piece::NULL_PIECE;
   captured_piece = Piece::NULL_PIECE;
}


/*=============================================================================
  Return TRUE if THIS is a null move; return FALSE otherwise
  ============================================================================*/
bool 
Move::is_null () const
{
   return (type == NULL_MOVE);
}

/*=============================================================================
  Output information regarding MOVE to the stream OUT
  ============================================================================*/
ostream& 
operator << (ostream& out, const Move& move)
{
   if (move.get_type () != Move::NULL_MOVE)
   {      
      string initial, final;
      Move::translate_to_notation (move.from (), initial);
      Move::translate_to_notation (move.to (), final);
      
      if (move.get_moving_piece () != Piece::NULL_PIECE)
      {
         out << Piece::pieceString (move.get_moving_piece ());
      }
      out << "\t" << initial << " - " << final;          
   }
   return out;
}

bool
operator == (const Move& m1, const Move& m2)
{
   return (m1.start == m2.start && 
           m1.end == m2.end);
}

bool 
operator < (const Move& m1, const Move& m2)
{
   return m1.score < m2.score;
}

Board::Squares
Move::from () const 
{
   return start;
}

Board::Squares
Move::to () const
{
   return end;
}

Move::Type 
Move::get_type () const
{
   return type;
}

void 
Move::set_type (Move::Type type)
{
   this->type = type;
}

Piece::Type
Move::get_moving_piece () const
{
   return moving_piece;
}

Piece::Type
Move::get_captured_piece () const
{
   return captured_piece;
}

void
Move::set_moving_piece (Piece::Type piece)
{
   this->moving_piece = piece;
}

void
Move::set_captured_piece (Piece::Type piece)
{
   this->captured_piece = piece;
}

void 
Move::set_score (int score)
{
   this->score = score;
}

int 
Move::get_score () const
{
   return score;
}

/*============================================================================
 *                                CLASS METHODS                              *
 *===========================================================================*/


/*=============================================================================
  Return TRUE if NOTATION was correctly translated into a number in the range
  [0..Board::SQUARES); return FALSE otherwise.

  The function mapping chess notation to squares is as follows:

  f(A8) -> 0, f(H8) -> 7, 
  f(A7) -> 8, ...
  ...
  ...
  f(A1) -> 56, f(H1) -> 63
  ============================================================================*/
bool
Move::translate_to_square (const string&   notation,
                           Board::Squares& square)
{
   if (is_valid_notation (notation))
   {
      u_short column = toupper (notation[0]) - 'A';
      u_short row    = (Board::SIZE - 1) - (notation[1] - '1');
       
      square = (Board::Squares) (row * Board::SIZE + column);
      return true;
   }        
   return false;
}

/*=============================================================================
  Inverse function of translate_to_square
  ============================================================================*/
bool
Move::translate_to_notation (Board::Squares square, string& notation)
{
   if (!Board::is_inside_board (square))
      return false;

   notation.clear ();
   notation += (char) ('a' + (square % Board::SIZE));
   notation += (char) ('8' - (square / Board::SIZE));

   return true;
}

/*=============================================================================
  Return TRUE if NOTATION represents a valid algebraic chess notation square;
  return FALSE otherwise.
  
  For instance, A8 is a valid notation, whereas B10 is not.
  ============================================================================*/
bool 
Move::is_valid_notation (const string &notation)
{
   if (notation.length () != 2)
      return false;
        
   if (toupper (notation[0]) >= 'A' && toupper (notation[0]) <= 'H')
      if (notation[1] >= '1' && notation[1] <= '8')
         return true;
        
   return false;
}