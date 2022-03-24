function pkexit : boolean;

{ This function asks the question "Are You Sure?" and returns the Y or N answer.}

var
  win       : WindowPtr;
  answer    : boolean;


begin

  New(win, InitCustom(22, 10, 57, 14, MenuColors, wBordered+wClear));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Verification ', heTC);
  if MouseInstalled then
    begin
      HideMouse;
      win^.wFrame.AddHeader(' Left<Y> or Right<N> ', heBC)
    end
  else
    win^.wFrame.AddHeader(' Y or N ', heBC);
  win^.Draw;

  gotoxy(11,3);
  write('Exit PK Teach ?');
  answer := yorn;

  win^.Erase;
  dispose(win,done);

  if answer = true then
  pkexit := true
  else pkexit := false;

end;
