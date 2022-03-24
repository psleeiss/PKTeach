function caplock : boolean;

{ This function tells whether or not the cap-lock key is set.  True means set }

var
  status_byte : byte absolute $0000:$0417;

begin
  if (status_byte and $40) <> 0
  then caplock := true
  else caplock := false;
end;