function  scbufinp(    xpos      : integer;    { x position of buffer start }
                       ypos      : integer;    { y position of buffer start }
                       buff_len  : byte;       { Length of buffer           }
                   var data_buff          ;    { Buffer for data            }
                       esc_ok    : boolean;
                       pgup_ok   : boolean;
                       pgdn_ok   : boolean;
                       F1_ok     : boolean;
                       F2_ok     : boolean;
                       F3_ok     : boolean;
                       F4_ok     : boolean;
                       F5_ok     : boolean;
                       F6_ok     : boolean;
                       F7_ok     : boolean;
                       F8_ok     : boolean;
                       F9_ok     : boolean;
                       F10_ok    : boolean )
                                 : integer;


{ This function is passed an x,y position for a character buffer to begin
{ at, the length of that buffer and a variable to hold the input data.
{ The value returned by this function is the keystroke that caused it to exit.
{ Note that this function will exit on an ENTER, ESC, UP-ARROW, or DOWN-ARROW.
{ Also note that if the key was an extended key, it will have 1000 added to it.
{ This function then gets the desired input from the keyboard, echos it to
{ the screen and returns it in the data_buff variable. Note that all colors
{ should be set prior to calling this routine, as well as cursor status.   }


var
  cur_pos      : integer;
  cursor_x     : integer;
  cursor_y     : integer;
  time_to_quit : boolean;
  in_char      : char;
  second_char  : char;
  char_num     : integer;
  temp_string  : str255;
  end_seek     : integer;

  { This variable is used to set the length of TEMP_STRING after characters }
  { have been copied to it by the MOVE command.                             }
  string_leng  : byte absolute temp_string;


begin

  { Initialize }
  cursor_x := xpos;
  cursor_y := ypos;
  gotoxy(cursor_x,cursor_y);
  cur_pos := 1;
  time_to_quit := false;
  temp_string := max_blank_string;

  { Get input string and display }
  move(data_buff,temp_string[1],buff_len);
  string_leng := buff_len;
  write(temp_string);
  gotoxy(cursor_x,cursor_y);


  while (not time_to_quit) do
  begin

    { Get the user's input.  Don't allow most kinds of extended scan codes }
    in_char := readkey;
    char_num := ord(in_char);

    if in_char = #0   { If an extended code character get code & add 1000}
    then char_num := ord(readkey) + 1000;


    { Act on user's input }
    case char_num of

      { Normal key characters }
      32..126    : begin
                     write(chr(char_num));
                     temp_string[cur_pos] := chr(char_num);
                     if cur_pos < buff_len
                     then begin
                       cur_pos := cur_pos + 1;
                       cursor_x := cursor_x + 1;
                     end
                     else begin

                       { This gotoxy is done here so that the user doesn't }
                       { see the cursor move out of the buffer.            }
                       gotoxy(cursor_x,cursor_y);
                     end;
                   end;

      { Backspace or delete }
       backsp,del_key : begin

                     { Position cursor depending on key hit }
                     if (char_num = 8)   { backspace }
                     then begin
                       cur_pos := cur_pos - 1;
                       cursor_x := cursor_x - 1;
                     end;

                     { Detect backspace beyond buffer }
                     if (char_num = 8) and (cur_pos < 1)
                     then begin
                       cur_pos := 1;
                       cursor_x := xpos;
                       whistle;
                     end
                     else begin

                        { Delete the character }
                        delete(temp_string,cur_pos,1);
                        temp_string := temp_string + ' ';

                        { Redisplay the buffer }
                        gotoxy(xpos,ypos);
                        write(temp_string);
                     end;

                   end;

      { Return }
   up,down,retrn : time_to_quit := true;

      { ESC key }
          esc    : if esc_ok
                   then time_to_quit := true
                   else whistle;

      { Page up key }
          pgup   : if pgup_ok
                   then time_to_quit := true
                   else whistle;

      { Page down key}
          pgdn   : if pgdn_ok
                   then time_to_quit := true
                   else whistle;

      { Function keys }
          F1     : if F1_ok
                   then time_to_quit := true
                   else whistle;

          F2     : if F2_ok
                   then time_to_quit := true
                   else whistle;

          F3     : if F3_ok
                   then time_to_quit := true
                   else whistle;

          F4     : if F4_ok
                   then time_to_quit := true
                   else whistle;

          F5     : if F5_ok
                   then time_to_quit := true
                   else whistle;

          F6     : if F6_ok
                   then time_to_quit := true
                   else whistle;

          F7     : if F7_ok
                   then time_to_quit := true
                   else whistle;

          F8     : if F8_ok
                   then time_to_quit := true
                   else whistle;

          F9     : if F9_ok
                   then time_to_quit := true
                   else whistle;

          F10     : if F10_ok
                   then time_to_quit := true
                   else whistle;

      { Left arrow }
          left   : begin
                     if cur_pos > 1
                     then begin
                       cur_pos := cur_pos - 1;
                       cursor_x := cursor_x -1;
                     end
                     else whistle;
                   end;

      { Right arrow }
           right : begin
                     if cur_pos < buff_len
                     then begin
                       cur_pos := cur_pos + 1;
                       cursor_x := cursor_x + 1;
                     end
                     else whistle;
                   end;

      { END key }
        end_key  : if (cur_pos < buff_len) or (temp_string[cur_pos] = ' ')
                   then begin

                     { Find logical end of string }
                     end_seek := buff_len;
                     while ((end_seek > 0) and (temp_string[end_seek] = ' '))
                     do end_seek := end_seek - 1;

                     { set cursor position }
                     cur_pos := end_seek + 1;
                     cursor_x := xpos + end_seek;

                     { If the buffer was full, then we must back up one space }
                     if cur_pos > buff_len
                     then begin
                       cur_pos := cur_pos - 1;
                       cursor_x := cursor_x - 1;
                     end

                   end;

      { HOME key }
          home   : begin
                     cur_pos := 1;
                     cursor_x := xpos;
                   end;
      else whistle;

    end;  { CASE stmt }

    gotoxy(cursor_x,cursor_y);

  end;   { WHILE stmt }


  { Save buffer back to variable }
  move(temp_string[1],data_buff,buff_len);

  scbufinp := char_num;

end;    { Procedure }
