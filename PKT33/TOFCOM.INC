procedure tofcom;

{ This procedure displays an error message stating that the user has selected }
{ the "load prev com from file" command when the file is at the TOF condition.}

var
  win       : WindowPtr;
  answer    : word;
  WinOpts   : Longint;

begin

  WinOpts := wBordered+wClear;
  New(win, InitCustom(21, 10, 60, 16, MenuColors, WinOpts));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Whoops! ',heTC);
  win^.wFrame.AddHeader(' Press any key ', heBC);
  win^.Draw;
  HideMouse;
  writeln;
  writeln('    You are currently at the top');
  writeln('       of the list of commands.');
  writeln('   "Upward (previous)" not allowed.');
  answer := ReadKeyOrButton;

  win := wStack.UnStackTop;

end;
