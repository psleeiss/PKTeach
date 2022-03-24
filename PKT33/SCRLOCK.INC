function scrlock : boolean;

{ This function tells whether or not the scroll-lock key is set.  True means set }

var
  status_byte : byte absolute $0000:$0417;

begin
  if (status_byte and $10) <> 0
  then scrlock := true
  else scrlock := false;
end;