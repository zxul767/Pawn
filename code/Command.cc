/*==============================================================================
 | Class name: Command                                                         |
 |                                                                             |
 | Responsabilities:                                                           |
 | -Represent a command issued by the user and provide the information         |
 |  associated with it, e.g. a command to move a piece should also provide the |
 |  start and end squares.                                                     |
 |                                                                             |
 | Date: September 1, 2007                                                     |
 ==============================================================================*/

#include "Command.h"
#include "Move.h"

/*==============================================================================
 | STATIC INITIALIZATION BLOCK                                                 |
 ==============================================================================*/
map<string, Command::Value> Command::commands;
map<Command::Value, string> Command::commandStrings;

const bool Command::commands_loaded = Command::load_commands ();

Command::Command ()
{
   value = UNKNOWN;
   command = "";
}

Command::Command (Value command_value)
{
   value = command_value;
   command = commandStrings[value];
}

Command::Command (string& command)
{
   this->command = command;  

   if (Command::commands.find (command) != Command::commands.end ())
      value = commands[command];

   else if (command.find ("usermove") != string::npos && 
            command.find ("accepted") == string::npos)
   {
      value = USER_MOVE;
   }
   else if (!Move (command).is_null ())
      value = MOVE;

   else
      value = UNKNOWN;
}

bool
Command::load_commands ()
{
   commands["xboard"]     = XBOARD_MODE;
   commands["protover 2"] = FEATURES;
   commands["new"]        = NEW_GAME;
   commands["quit"]       = QUIT;
   commands["think"]      = THINK;
   commands["undo"]       = UNDO_MOVE;
   commands["see moves"]  = SEE_MOVES;
   commands["usermove"]   = USER_MOVE,
   commands["remove"]     = REMOVE;
   commands["train"]      = TRAIN;
   commands["auto"]  = COMPUTER_PLAY;

   commandStrings[XBOARD_MODE]   = "xboard";
   commandStrings[FEATURES]      = "protover 2";
   commandStrings[NEW_GAME]      = "new";
   commandStrings[QUIT]          = "quit";
   commandStrings[THINK]         = "think";
   commandStrings[UNDO_MOVE]     = "undo";
   commandStrings[SEE_MOVES]     = "see moves";
   commandStrings[USER_MOVE]     = "usermove";
   commandStrings[REMOVE]        = "remove";
   commandStrings[TRAIN]         = "train";
   commandStrings[COMPUTER_PLAY] = "auto";

   return true;
}

bool
Command::is_quit () const
{
   return (value == QUIT);
}

bool
Command::is_move () const
{
   return (value == MOVE);
}

Command::Value
Command::get_value () const
{
   return value;
}

string
Command::get_notation () const
{
   return command;
}