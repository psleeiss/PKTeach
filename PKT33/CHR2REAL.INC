function chr2real( var in_char         ;
                       chr_len   : byte;
                   var answer    : real) : boolean ;

{ This procedure will check to see if the character array passed in contains }
{ a valid real number.  If the leading element is a decimal point, a zero is }
{ added to it (assuming it is otherwise valid).                              }

var
  ok          : boolean;
  val_rc      : integer;
  temp_string : string[255];
  fail_safe   : string[255];
  str_len     : byte absolute temp_string;

begin

  { Copy character array to string }
  move(in_char,temp_string[1],chr_len);
  str_len := chr_len;


  { remove blanks before test }
  blnkchop(temp_string);

  { Add a leading zero if first character is decimal point }
  fail_safe := temp_string;
  if temp_string[1] = '.'
  then temp_string := '0' + temp_string;

  {$R-}  {Disable RANGE CHECKING errors (see VAL) }

  { Convert the string and check for an error.  See the notes about VAL }
  { regarding how it handles errors involving reals.                    }
  val(temp_string,answer,val_rc);

  if (val_rc <> 0)
  then ok := false
  else ok := true;

  chr2real := ok;

  if not ok
  then begin
    temp_string := max_blank_string;
    move(fail_safe[2],temp_string[1],length(fail_safe)-1);
    str_len := length(fail_safe) - 1;
  end;

  {$R+}    { Enable RANGE CHECKING errors }

  move(temp_string[1],in_char,chr_len);

end;  { Function }