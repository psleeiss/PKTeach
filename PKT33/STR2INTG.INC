function str2intg(     in_string : str66;
                   var answer    : integer) : boolean ;

var
  ok          : boolean;
  temp_answer : longint;
  val_rc      : integer;

begin
  {$R-}  {Disable RANGE CHECKING errors (see VAL) }

  { Convert the string and check for an error.  See the notes about VAL }
  { regarding how it handles errors involving integers.                 }
  val(in_string,temp_answer,val_rc);
  if (val_rc <> 0) or
     ( (temp_answer < -maxint) or (temp_answer > maxint) )
  then ok := false
  else begin
    ok := true;
    answer := temp_answer;
  end;


  str2intg := ok;
  {$R+}    { Enable RANGE CHECKING errors }

end;  { Function }