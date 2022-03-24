function chr2intg( var in_char         ;
                       chr_len   : byte;
                   var answer    : integer) : boolean ;


var
  ok          : boolean;
  temp_answer : longint;
  val_rc      : integer;
  temp_string : string[255];
  str_len     : byte absolute temp_string;

begin

  { Copy character array to string }
  move(in_char,temp_string[1],chr_len);
  str_len := chr_len;

  { remove blanks before test }
  blnkchop(temp_string);

  {$R-}  {Disable RANGE CHECKING errors (see VAL) }

  { Convert the string and check for an error.  See the notes about VAL }
  { regarding how it handles errors involving integers.                 }
  val(temp_string,temp_answer,val_rc);
  if (val_rc <> 0) or
     ( (temp_answer < -maxint) or (temp_answer > maxint) )
  then ok := false
  else begin
    ok := true;
    answer := temp_answer;
  end;


  chr2intg := ok;
  {$R+}    { Enable RANGE CHECKING errors }

end;  { Function }