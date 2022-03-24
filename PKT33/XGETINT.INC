function xgetint : integer ;


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

    if xbufinpt(wherex,wherey,5,answer_s[1])
    then begin
      if chr2intg(answer_s[1],length(answer_s),answer)
      then ok := true
      else ok := false;
    end
    else begin
      answer := -255;
      ok := true;
    end;
    gotoxy(xsave,ysave);

  end;    { WHILE stmt }

  xgetint := answer;
  {$I+}    { Enable I/O error checking }

end;  { Function }