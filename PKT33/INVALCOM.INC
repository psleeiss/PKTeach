procedure invalcom;

{ This procedure informs the user that an invalid command has been read }

var
  win       : WindowPtr;
  answer    : Word;


begin
  New(win, initcustom(22, 10, 57, 14, MenuColors, wBordered+wClear));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Trouble ', heTC);
  win^.wFrame.AddHeader(' Press any key to continue ', heBC);
  win^.Draw;

  gotoxy(10,2);
  write('Invalid Command');
  answer := ReadKeyOrButton;

  win := wStack.UnStackTop;

end;
