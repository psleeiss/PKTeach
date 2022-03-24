procedure dosdirwn;

{ This procedure create a dos directory on the screen in a popup window. }
{ The user is querried as to what file mask should be used.              }

var
  win      : WindowPtr;
  any_char : word;
  WinOpts  : Longint;


  begin
    WinOpts := wBordered+wClear;
    ClrScr;
    New(win, InitCustom(5, 3, 75, 23, MenuColors, WinOpts));
    win^.setcursor(cuhidden);
    win^.wFrame.AddHeader(' Directory of Program Files ', heTC);
    if MouseInstalled then
      win^.wFrame.AddHeader(' Any Button to exit ', heBC)
    else
      win^.wFrame.AddHeader(' Any Key to exit ', heBC);
    win^.Draw;

  { Do the directory }
  dirprg;

  any_char := ReadKeyOrButton;

  win^.Erase;
  dispose(win,Done);
end;