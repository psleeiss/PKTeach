function getyn : char;


var
  answer : char;

begin
  answer := ' ';
  write('    Enter Y or N');
  while ((upcase(answer) <> 'Y') and (upcase(answer) <> 'N')) do
  begin
    answer := readkey;
    { Erase the keystroke }
  end;

getyn := upcase(answer);

end;