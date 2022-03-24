procedure delnocom;

{ This procedure informs the user that no commands can be deleted }

var
  win       : WindowPtr;
  WinOpts   : Longint;
  answer    : word;


begin

  HiddenCursor;
  (*New(win, initcustom(22, 10, 57, 14, defaultcolorset, wAltFrame));*)
  WinOpts := wBordered+wClear;
  New(win, InitCustom(22, 10, 57, 14, MenuColors, WinOpts));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' NOTE ', heTC);
  win^.wFrame.AddHeader(' Press any key to continue ', heBC);
  if not win^.IsActive then
  win^.Draw;

  gotoxy(8,2);
  write('No command to remove');
  answer := readkeyorbutton;

  win^.erase;

end;
