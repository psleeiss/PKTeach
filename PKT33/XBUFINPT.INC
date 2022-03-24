function xbufinpt(   xpos      : integer;    { x position of buffer start }
                     ypos      : integer;    { y position of buffer start }
                     buff_len  : byte;       { Length of buffer           }
                 var data_buff): boolean;    { Buffer for data            }


{ This procedure is passed an x,y position for a character buffer to begin
{ at, the length of that buffer and a variable to hold the input data.
{ This procedure then gets the desired input from the keyboard, echos it to
{ the screen and returns it in the data_buff variable. Note that all colors
{ should be set prior to calling this routine, as well as cursor status.   }

{ This hacked version returns on any 'X' as input.  It will return false if so }

type
  bigchar = array[1..200] of char;

var
  cur_pos      : integer;
  cursor_x     : integer;
  cursor_y     : integer;
  time_to_quit : boolean;
  in_char      : char;
  second_char  : char;
  char_num     : integer;
  temp_string  : string[255];
  end_seek     : integer;
  in_word      : word;


  { This variable is used to set the length of TEMP_STRING after characters }
  { have been copied to it by the MOVE command.                             }
  string_leng  : byte absolute temp_string;


begin

  xbufinpt := true;

  { Initialize }
  cursor_x := xpos;
  cursor_y := ypos;
  gotoxy(cursor_x,cursor_y);
  cur_pos := 1;
  time_to_quit := false;

  { Get input string and display }
  move(data_buff,temp_string[1],buff_len);
  string_leng := buff_len;
  write(temp_string);
  gotoxy(cursor_x,cursor_y);


  while (not time_to_quit) do
  begin

    { Get the user's input.  Don't allow most kinds of extended scan codes }
(*    in_char := readkey;*)
    in_word := readkeyorbutton;
(*    char_num := ord(in_char);  *)
    char_num := lo(in_word);

    if char_num = 0   { If an extended code character get code & add 1000}
    then char_num := hi(in_word) + 1000;

    { Act on user's input }
    case char_num of

      { An X or right mouse button (1238)}
      88,120,1238: begin
                     xbufinpt := false;
                     time_to_quit := true;
                   end;

      { Normal key characters }
      32..87,89..119,
      121..126   : begin
                     write(chr(char_num));
                     bigchar(data_buff)[cur_pos] := chr(char_num);
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
       8,1083    : begin

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
            13   : time_to_quit := true;

      { Left arrow }
          1075   : begin
                     if cur_pos > 1
                     then begin
                       cur_pos := cur_pos - 1;
                       cursor_x := cursor_x -1;
                     end;
                   end;

      { Right arrow }
           1077  : begin
                     if cur_pos < buff_len
                     then begin
                       cur_pos := cur_pos + 1;
                       cursor_x := cursor_x + 1;
                     end;
                   end;

      { END key }
          1079   : if cur_pos < buff_len
                   then begin

                     { Find logical end of string }
                     end_seek := buff_len;
                     while ((end_seek > 0) and (temp_string[end_seek] = ' '))
                     do end_seek := end_seek - 1;

                     { set cursor position }
                     cur_pos := end_seek + 1;
                     cursor_x := xpos + end_seek;
                   end;

      { HOME key }
          1071   : begin
                     cur_pos := 1;
                     cursor_x := xpos;
                   end;
      else begin
           end;

    end;  { CASE stmt }

    gotoxy(cursor_x,cursor_y);

  end;   { WHILE stmt }


  { Save buffer back to variable }
  move(temp_string[1],data_buff,buff_len);

end;    { Procedure }
