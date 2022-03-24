function nest : boolean;

{ This function verifies that the user wants to nest the robot }

var
  win    : WindowPtr;
  answer : boolean;


  begin
    New(win, initcustom(4, 16, 40, 20, MenuColors, wBordered+wClear));
    win^.setcursor(cuhidden);
    win^.wFrame.AddHeader(' Nest (return to zero) ', heTC);
    win^.wFrame.AddHeader(' Enter Y or N ', heBC);
    win^.Draw;

  gotoxy(3,2);
  write('Nest the robot?');
  answer := yorn;

  win^.Erase;
  dispose(win,done);

  if answer = true
  then nest := true
  else nest := false;

end;
