function blnkstr( var in_str ) : boolean;

{ This function is passed any length STRING and returns TRUE if that string }
{ is null or composed of all blanks.  This is a useful utility because Turbo }
{ Pascal considers two blank strings with different lengths to be unequal.}
{ NOTE:  This procedure expects IN_STR to be type STRING of any length!!! }

type
  one_byte = byte;

var
  count     : integer;
  temp_str  : string[255];
  temp_char : array[0..255] of char absolute temp_str;

begin

  { load the input string into temp_str }
  move(in_str,temp_str,one_byte(in_str) + 1);
  count := length(temp_str);
  if length(temp_str) = 0
  then begin
    blnkstr := true;
    exit;
  end;

  { See if it is entirely blank }
  for count := 1 to length(temp_str)
  do if temp_char[count] <> ''
     then begin
       blnkstr := false;
       exit
     end;

  blnkstr := true;

end;