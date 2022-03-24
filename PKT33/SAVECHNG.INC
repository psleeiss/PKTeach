function savechng : boolean;

{ This function returns TRUE if the user wishes to save his/her changes }

var
  win           : WindowPtr;
  answer        : boolean;
  time_to_quit  : boolean;
  restore_mouse : boolean;


begin
  New(win, initcustom(22, 10, 57, 14, MenuColors, wBordered+wClear));
  win^.setcursor(cuhidden);
  if MouseInstalled
  then begin
    restore_mouse := MouseCursorOn;
    hidemouse;
    win^.wframe.AddHeader(' Press Left (yes) or Right (no) ',heBC);
  end
  else begin
    win^.wframe.AddHeader(' Enter Y or N ',heBC);
  end;
  win^.Draw;

  time_to_quit := false;
  while not time_to_quit do
  begin
    clrscr;
    gotoxy(8,2);
    if robot_mode = write_new
    then write('Save your program? ')
    else write('Save your changes? ');
    answer := yorn;
    if (answer = true) or (answer = false)
    then time_to_quit := true;
  end;

  if (MouseInstalled AND restore_mouse)
  then showmouse;

  if answer = true
  then savechng := true
  else savechng := false;

  win^.Erase;
  dispose(win,done);

end;
