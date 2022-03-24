function zverify : boolean;

{ This function explains to the user just what the ZERO command does and asks }
{ him/her to verify that this is what they really want.                       }

var
  win           : WindowPtr;
  answer        : boolean;
  restore_mouse : boolean;


begin
  New(win, InitCustom(7, 5, 73, 19, MenuColors, WinOpts));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Verification ',heTC);
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

  writeln;
  writeln;
  writeln;
  writeln('  NOTE: This option DOES NOT tell the robot to go back to ');
  writeln('        the zero position.  This option tells the robot to');
  writeln('        consider its current position to be the zero position.');
  writeln;
  writeln('            Do you wish to have the current position');
  write  ('            be the zero position?');
  answer := yorn;

  if MouseInstalled and restore_mouse
  then begin
    showmouse;
  end;

  win^.Erase;
  dispose(win,done);

  if answer = true
  then zverify := true
  else zverify := false;

end;
