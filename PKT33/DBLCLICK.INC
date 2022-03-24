function dblclick(click1 : word) : boolean;

var
  status   : boolean;
  count,
  click2   : word;
  LastX,
  LastY    : Byte;
  Time,
  Start,
  Stop     : longint;
  Elapsed  : integer;

  begin
    Start := TimeMs;
    repeat
      if MousePressed = true then
        begin
          click2 := MouseKeyWord;
          Stop := TimeMs;
          dblclick := true;
        end
      else stop := TimeMs;
      Elapsed := (Stop - Start);
      until ((click2 = click1) and (Elapsed <= 160)) or (Elapsed > 160);

  end;