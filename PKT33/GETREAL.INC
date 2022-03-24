function getreal : real;

var
  ok : boolean;
  answer : real;

begin
  {$I-}  {Disable I/O errors }

  ok := false;
  while not ok do
  begin

    read(answer);
    if ioresult = 0
    then ok := true
    else begin
      ok := false;
      whistle;
    end;

  end;    { WHILE stmt }

  getreal := answer;
  {$I+}    { Enable I/O error checking }

end;  { Function }