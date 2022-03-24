function saveprog : boolean;

{ This function returns TRUE if the user wishes to save his/her program }

var
  win          : WindowPtr;
  answer       : boolean;
  time_to_quit : boolean;

begin

  New(win, InitCustom(22, 10, 57, 14, MenuColors, wBordered+wClear);
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Enter Y or N ', heBC);
  win^.Draw;

  time_to_quit := false;
  while not time_to_quit do
  begin
    clrscr;
    gotoxy(8,2);
    write('Save your program? ');
    answer := yorn;
    if answer = true
    then time_to_quit := true;
  end;

  if answer = true
  then saveprog := true
  else saveprog := false;

  win^.Erase;
  dispose(win,done);

end;
