procedure dupfname;

{ This procedure informs the user that they have entered an duplicate filename }

var
  win       : WindowPtr;
  answer    : word;
  WinOpts   : Longint;

begin

  WinOpts := wBordered+wClear;

  HiddenCursor;
  HideMouse;
  New(win, InitCustom(22, 10, 57, 14, MenuColors, WinOpts));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Whoops! ',heTC);
  if MouseInstalled then
     win^.wFrame.AddHeader(' Press any Mouse Button to Continue ', heBC)
  else win^.wFrame.AddHeader(' Press any key to continue ', heBC);
  win^.Draw;

  gotoxy(8,2);
  write('Duplicate filename');
  answer := ReadKeyOrButton;

  win^.erase;
  dispose(win,done);

end;
