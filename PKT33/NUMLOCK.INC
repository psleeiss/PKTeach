function numlock : boolean;

{ This function tells whether or not the numlock key is set.  True means set }

var
  status_byte : byte absolute $0000:$0417;

begin
  if (status_byte and $20) <> 0
  then numlock := true
  else numlock := false;
end;