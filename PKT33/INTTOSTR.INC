function inttostr( in_integer : longint) : string;

{ This function takes any integer and converts it to a string }

var
  temp_string  : string;

begin
  str(in_integer,temp_string);
  inttostr := temp_string;

end;