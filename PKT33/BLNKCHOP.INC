procedure blnkchop( var in_str );

{ NOTE:  This procedure expects IN_STR to be type STRING of any length!!! }

type
  one_byte = byte;

var
  count    : integer;
  temp_str : string;

begin

  { load the input string into temp_str }
  move(in_str,temp_str,one_byte(in_str) + 1);

  if ( (length(temp_str) = 0) or (temp_str = ' ') )
  then begin
    move(temp_str,in_str,length(temp_str) + 1);
    exit;
  end;

  { Kill all leading blanks }
  count := 1;
  while  ( ( count <= length(temp_str) ) and ( temp_str[count] = ' ') )
  do count := count + 1;

  { Now we have first non-blank character }
  temp_str := copy(temp_str,count,length(temp_str) - count + 1);

  { Find traling blanks }
  count := length(temp_str);
  while ( (count >= 1 ) and ( temp_str[count] = ' ') )
  do count := count - 1;

  { See if all remaining characters are non-blank }
  if count = length(temp_str)
  then begin
    move(temp_str,in_str,length(temp_str) + 1);
    exit;
  end;

  { Now we point to last character before trailing blanks }
  temp_str := copy(temp_str,1,count);

  { Put the string back }
  move(temp_str,in_str,length(temp_str) + 1);

end;