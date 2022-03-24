function gripclos : boolean;

{ This function verifies that the user wants to close the gripper }

var
  win       : WindowPtr;
  answer    : boolean;


  begin
    If MouseInstalled then
      HideMouse;

    New(win, InitCustom(3, 16, 40, 20, MenuColors, wBordered+wClear));
    win^.setcursor(cuhidden);
    win^.wFrame.AddHeader(' Verification ', heTC);
    win^.wFrame.AddHeader(' Enter Y or N ', heBC);
    if not win^.IsActive then
    win^.Draw;

    gotoxy(3,2);
    write('Close the gripper?');
    answer := yorn;

    win^.Erase;
    dispose(win,done);

    if answer = true
     then gripclos := true
       else gripclos := false;

  end;
