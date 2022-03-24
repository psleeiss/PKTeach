procedure readchar( var data_buf;
                        buff_len : byte);

{ This procedure does the equivelant of a "readln" call except that it }
{ takes a character array as its input argument.                       }

var
  big_string : str255;

begin

  { Initialize the big_string }
  big_string := max_blank_string;

  readln(big_string);

  if (big_string = '') or (length(big_string) = 0)
  then big_string := max_blank_string;

  { move string into character array so it can be returned }
  move(big_string[1],data_buf,buff_len);


end;