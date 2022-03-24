function getint : integer ;


var
  ok       : boolean;
  answer   : integer;
  xsave    : byte;
  x2       : byte;
  ysave    : byte;
  count    : byte;
  answer_s : string;

begin
  {$I-}  {Disable I/O errors }

  ok := false;
  while not ok do
  begin

    xsave := wherex;
    ysave := wherey;
    answer_s := '      ';
    buffinpt(wherex,wherey,5,answer_s[1]);
    gotoxy(xsave,ysave);
    if chr2intg(answer_s[1],length(answer_s),answer)
    then ok := true
    else ok := false;

  end;    { WHILE stmt }

  getint := answer;
  {$I+}    { Enable I/O error checking }

end;  { Function }