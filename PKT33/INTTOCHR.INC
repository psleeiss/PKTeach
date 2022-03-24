procedure inttochr(     in_int : integer;
                    var out_char;
                        char_len : byte);

{ Convert an integer to a character array }

var
  temp_string : string[255];

begin
  temp_string := max_blank_string;
  str(in_int,temp_string);
  move(temp_string[1],out_char,char_len);

end;