function speed( var command : string) : boolean;

{ This function determines how many seconds the time delay should be }

var
  win       : WindowPtr;
  temp_str  : string;
  answer    : integer;
  WinOpts   : Longint;
  any_key   : word;

begin
  HideMouse;
  WinOpts := wBordered+wClear;
  New(win, InitCustom(3, 16, 38, 21, MenuColors, WinOpts));
  win^.wFrame.AddHeader(' Speed ',heTC);
  if MouseInstalled then
  win^.wFrame.AddHeader(' RIGHT button to exit ', heBC)
  else
  win^.wFrame.AddHeader(' Press ''X'' to exit ', heBC);
  win^.Draw;

  answer := -1;
  while ((answer < 1) or (answer > 5)) and (answer <> -255) do
  begin
    NormalCursor;
    clrscr;
    gotoxy(3,2);
    writeln('  1 is the slowest');
    write('    New Speed? (1-5)?  ');
    answer := xgetint;
  end;
  HiddenCursor;

  if answer = -255
  then begin
    speed := false;
  end
  else begin
    speed := true;
    str(answer,temp_str);
    command := 'S'+temp_str;
  end;

  win^.select;
  win^.Erase;
  dispose(win,done);

end;
