function savechk : boolean;

{ This function explains that the user has just attempted to back out of the
{ menu without saving his program and does he want to save the point.   }

var
  win       : WindowPtr;
  answer    : boolean;


begin
  HiddenCursor;
  New(win, initcustom(7, 5, 73, 19, MenuColors, wBordered+wClear));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Verification ', heTC);
  if MouseInstalled then
  win^.wFrame.AddHeader(' Left Button<YES> or Right Button<NO> ', heBC)
  else win^.wFrame.AddHeader(' Press Y or N ', heBC);
  win^.Draw;

  writeln;
  writeln;
  writeln;
  writeln;
  writeln;
  writeln('  NOTE: You have not "added" the last point to the program file.');
  writeln('        Do you wish to have it inserted for you now?');

  answer := yorn;

  win^.Erase;
  dispose(win,done);

  if answer = true
  then savechk := true
  else savechk := false;

end;
