procedure dspchrar( var char_arr ;
                        arr_len  : byte);

{ This procedure displays a portion of a character array specified by arr_len }
{ It is assumed that all color and cursor postioning has already been taken   }
{ care of by the calling routine.                                             }

var
  temp_str : string[255];
  str_len  : byte absolute temp_str;

begin
  move(char_arr,temp_str[1],arr_len);
  str_len := arr_len;
  write(temp_str);

end;