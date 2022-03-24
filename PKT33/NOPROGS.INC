procedure noprogs;

{ This procedure informs the user that no programs are available }

var
  win       : WindowPtr;
  answer    : word;

begin
  HideMouse;
  New(win, InitCustom(22, 15, 57, 18, Menucolors, wbordered+wClear));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Whoops! ', heTC);
  win^.wFrame.AddHeader(' Press any Key ', heBC);
  win^.Draw;

  gotoxy(2,2);
  write(' No programs found on the disk ');
  answer := ReadKeyOrButton;

  win^.Erase;
  dispose(win,done);

end;
