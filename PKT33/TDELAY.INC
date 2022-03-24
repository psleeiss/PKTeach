function tdelay( var command : string) : boolean;

{ This function determines how many seconds the time delay should be }

var
  win       : WindowPtr;
  temp_str  : string;
  answer    : integer;
  WinOpts   : Longint;

begin

  WinOpts := wBordered+wClear;

  HiddenCursor;

  New(win, InitCustom(3, 16, 38, 20, MenuColors, WinOpts));
  win^.wFrame.AddHeader(' Time Delay ',heTC);
  if MouseInstalled then
    win^.wFrame.AddHeader(' RIGHT button to exit ', heBC)
  else
    win^.wFrame.AddHeader(' Press ''X'' to exit ', heBC);
  win^.Draw;

  answer := -1;
  while ((answer < 1) or (answer > 99)) and (answer <> -255) do
  begin
    NormalCursor;
    clrscr;
    gotoxy(3,2);
    write('# of seconds? (1-99)?  ');
    answer := xgetint;
  end;
  HiddenCursor;

{ The following line was changed to the next 2 after changing allowing
  a right mouse button to exit.  Apparently the right mouse click changes
  the order of windows on the stack.  Without this change, the windows
  remained on the screen.    }
(*  win := wStack.UnStackTop;*)
  win^.Select;
  dispose(win,done);

  if answer = -255
  then begin
    tdelay := false;
    exit;
  end
  else tdelay := true;

  str(answer,temp_str);
  command := 'D'+temp_str;

end;
