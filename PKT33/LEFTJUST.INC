procedure leftjust(    buff_len : byte;
                   var data_buff        );

{ The purpose of this procedure is to left justify a character string passed }
{ in through data_buff                                                       }

var
  temp_string           : str255;
  string_len            : byte absolute temp_string;

begin

  { Set the temporary string to 255 blanks so we know it starts "clean" }
  temp_string := max_blank_string;

  { Copy the data to the string variable }
  move(data_buff,temp_string[1],buff_len);
  string_len := buff_len;

  { See if the data_buff is blank.  If so, just leave }
  if blnkstr(temp_string)
  then exit;

  while (temp_string[1] = ' ')
  do delete(temp_string,1,1);

  { Put the data back into the data buffer }
  fillchar(data_buff,buff_len,' ');  { Prevents duplicating last character }
  move(temp_string[1],data_buff,length(temp_string));

  gotoxy(1,15);

end;