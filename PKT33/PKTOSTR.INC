function pktostr(    in_ptr  : pk_ptr;
                 var command : string) : boolean;

{ This function receieves as input a PK_PTR variable and will then return in
{ the variable COMMAND a string which contains the necessary command to
{ bring the robot to the state stored in the in_ptr^ variable.  If the function
{ returns a value of TRUE, then the processing occured without any problems.
{ Note that this function will NOT work properly if we are going BACKWARDS
{ through the list of commands. TWO commands would have to be returned.      }

var
  test_char     : char;

begin

  command := '';

  { Check to make sure in_ptr is valid }
  if in_ptr = nil
  then begin
    pktostr := false;
    exit;
  end;

  { Assume the best of all possibilities }
  pktostr := true;

  { Isolate the first character in the command string }
  move(in_ptr^.cmd_str[1],test_char,1);

  { Let us see what kind of command was entered }
  case upcase(test_char) of

         { For the case where we have a non-move command, simply return the }
         { command that was stored in the pk_ptr^ structure.                }
    'S','O','C','D',
    'N','Z' : command := in_ptr^.cmd_str;

          { We must process the MOVE commands to translate the motor values }
    'M' : command := revert(in_ptr);

    else pktostr := false;

  end;   { Case statement }

end;
