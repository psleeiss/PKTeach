procedure invalfil;

{ This procedure informs the user that they have entered an invalid filename }

var
  win       : WindowPtr;
  answer    : word;
  WInOpts   : Longint;


  begin
    WinOpts := wBordered+wClear;

    New(win, InitCustom(22, 10, 57, 14, MenuColors, WinOpts));
    win^.setcursor(cuhidden);
    win^.wFrame.AddHeader(' Whoops! ', heTC);
    if MouseInstalled then
    win^.wFrame.AddHeader(' Press any Button to continue ', heBC)
    else
    win^.wFrame.AddHeader(' Press any Key to continue ', heBC);
    win^.Draw;

    gotoxy(10,3);
    write('Invalid filename');
    answer := ReadKeyOrButton;

    win := wStack.UnStackTop;

end;
