function delcon(filename : string) : char;

{ This function verifies that the user wishes to delete a program.}

var
  win           : WindowPtr;
  answer        : boolean;
  WinOpts       : Longint;
  restore_mouse : boolean;

begin
  WinOpts := wBordered+wClear;
  HiddenCursor;

  New(win, InitCustom(22, 10, 57, 14, MenuColors, WinOpts));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Verification ', heTC);
  if mouseinstalled
  then begin
    restore_mouse := MouseCursorOn;
    hidemouse;
    win^.wframe.addheader(' Press Left (yes) or Right (no) ',hebc);
  end
  else begin
    win^.wframe.addheader(' Press Y or N ',hebc);
  end;
  win^.Draw;

  gotoxy(2,2);
  write('Delete ',strfext(filename),'?');
  answer := yorn;

  win^.erase;
  dispose(win,done);

  if MouseInstalled and restore_mouse
  then showmouse;

  if answer = true then
  delcon := 'Y'
  else if answer = false then
  delcon := 'N';

end;
