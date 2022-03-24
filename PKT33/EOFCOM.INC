procedure eofcom;

{ This procedure displays an error message stating that the user has selected }
{ the "load from file" command when the file is at the EOF condition.         }

var
  win    : WindowPtr;
  answer : word;

begin

  HiddenCursor;

  New(win, InitCustom(21, 10, 60, 16, MenuColors, wBordered+wClear));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Whoops! ', heTC);
  if MouseInstalled then
    win^.wFrame.AddHeader(' Press any Mouse Button ', heBC)
  else win^.wFrame.AddHeader(' Press any Key ', heBC);
  win^.Draw;

  writeln;
  writeln('     There are no more commands ');
  writeln('     in the file to be read.    ');

  answer := ReadKeyOrButton;

  win^.Erase;
  dispose(win,done);

end;
