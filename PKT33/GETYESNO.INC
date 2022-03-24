function getyesno : char;


var
  answer : char;

begin
  answer := ' ';
  while ((upcase(answer) <> 'Y') and (upcase(answer) <> 'N')) do
  begin
    write('     Enter Y or N: ');
    answer := readkey;
    writeln;
  end;

getyesno := upcase(answer);

end;