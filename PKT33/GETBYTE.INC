function getbyte : byte;

{ This function gets a valid byte from the user without incurring a run-time }
{ error from Turbo Pascal if there happens to be an invalid entry made.      }

var
  response : byte;
  safe_response : integer;
  valid_response : boolean;

begin
  valid_response := false;

  while (not valid_response) do
  begin
    {$I-}   { Disable I/O error checking }
    read(safe_response);
    {$I+}    { Enable I/O error checking }

    If (ioresult <> 0) or (safe_response > 255) or (safe_response < 0 )
    then whistle
    else begin
      valid_response := true;
      response := safe_response;
    end;

  end;

  { Assign function a value }
  getbyte := response;

end;
