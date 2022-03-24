function remcon : char;

{ This function verifies that the user wishes to remove a command.}

var
  win       : WindowPtr;
  answer    : boolean;
  winopts   : longint;


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

  gotoxy(2,2);
  write('Remove Command?');

  answer := yorn;

  win^.erase;
  dispose(win,done);

  if answer = true then
  remcon := 'Y'
  else if answer = false then
  remcon := 'N';

end;
