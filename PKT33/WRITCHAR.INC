procedure writchar( var data_buf;
                        buff_len : byte);

{ This procedure does the equivelant of a "write" call except that it }
{ takes a character array as its input argument.                      }

var
  big_string : str255;
  string_len : byte absolute big_string;

begin

  { Initialize the big_string }
  big_string := max_blank_string;

  { move character array into string so it can be written }
  move(data_buf,big_string[1],buff_len);
  string_len := buff_len;

  write(big_string);

end;