function verfexit : char;

{ This function verifies that the user wishes to exit the revise system.}

var
  win           : WindowPtr;
  WinOpts       : Longint;
  answer        : boolean;
  restore_mouse : boolean;


begin
  WinOpts := wBordered+wClear;

  New(win, InitCustom(22, 10, 57, 14, MenuColors, WinOpts));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Verification ', heTC);
  if MouseInstalled
  then begin
    restore_mouse := MouseCursorOn;
    hidemouse;
    win^.wframe.AddHeader(' Press Left (yes) or Right (no) ',heBC);
  end
  else begin
    win^.wframe.AddHeader(' Press Y or N ',heBC);
  end;
  win^.Draw;

  gotoxy(2,2);
  if robot_mode = move_only
  then write('  Exit MOVE?')
  else if robot_mode = write_new
       then write('Exit WRITE NEW?')
       else if robot_mode = edit_prog
            then write('  Exit EDIT?')
            else write('  Whoops! in VERFEXIT! ');
  answer := yorn;

  If MouseInstalled and restore_mouse
  then showmouse;

  win^.Erase;
  dispose(win,done);

  if answer = true then
  verfexit := 'Y'
  else if answer = false
  then verfexit := 'N';

end;
