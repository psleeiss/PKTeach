function zquest : boolean;

{ This function explains to the user that they need to have the robot zeroed
{ and asks them if they have taken care of it .                   }

var
  win           : WindowPtr;
  answer        : boolean;
  WInOpts       : Longint;
  restore_mouse : boolean;
  device_str    : string[8];

begin

  WinOpts := wBordered+wClear;
  New(win, InitCustom(7, 5, 73, 19, MenuColors, WinOpts));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Verification ',heTC);
  if MouseInstalled
  then begin
    restore_mouse := mouseCursorOn;
    hidemouse;
    win^.wframe.addheader(' Press Left (Yes) or Right (No) ',hebc);
    device_str := 'Mouse';
  end
  else begin
    win^.wFrame.AddHeader(' Enter Y or N ', heBC);
    device_str := 'Keyboard';
  end;
  win^.Draw;

  writeln;
  writeln;
  writeln;
  writeln('  At this time you need to make certain that the robot is ');
  writeln('  in its "zero" or "home" position.  That is, the arrows');
  writeln('  on the base and at various points on the arm should be  ');
  writeln('  lined up.  If this is the case, then you can proceed.');
  writeln('  If not, then go into the "Move Robot using ',device_str,'" option');
  writeln('  on the Main Menu to move the robot and set a new zero');
  writeln('  position.');
  writeln;
  write  ('  Is the robot in the zero position?');

  answer := yorn;

  if MouseInstalled and restore_mouse
  then showmouse;

  win^.Erase;
  dispose(win,done);

  if answer = true then
  zquest := true
  else zquest := false;

end;
