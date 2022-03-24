function gripopen : boolean;

{ This function verifies that the user wants to open the gripper }

var
  win       : WindowPtr;
  answer    : boolean;
  WinOpts   : Longint;

  begin
    WinOpts := wBordered+wClear;

    New(win, InitCustom(3, 16, 40, 20, MenuColors, WinOpts));
    win^.setcursor(cuhidden);
    win^.wFrame.AddHeader(' Verificaton ', heTC);
    win^.wFrame.AddHeader(' Enter Y or N ', heBC);
    win^.Draw;

    gotoxy(3,2);
    write('Open the gripper?');
    answer := yorn;

    win^.Erase;
    dispose(win,done);

    if answer = true
     then gripopen := true
      else gripopen := false;

end;
