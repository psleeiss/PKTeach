function str2real(     in_string : str66;
                   var answer    : real) : boolean ;

var
  ok          : boolean;
  val_rc      : integer;

begin
  {$R-}  {Disable RANGE CHECKING errors (see VAL) }

  { Convert the string and check for an error.  See the notes about VAL }
  { regarding how it handles errors involving integers.                 }
  val(in_string,answer,val_rc);
  if (val_rc <> 0)
  then ok := false
  else ok := true;


  str2real := ok;
  {$R+}    { Enable RANGE CHECKING errors }

end;  { Function }