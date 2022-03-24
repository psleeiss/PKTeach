function wnfilenm( var filename : string) : boolean;

{ This function will popup a menu and querry the user for a filename. }
{ The user may call for a directory from here, and the user may back  }
{ out by hitting escape.  If escape is hit, the function will return  }
{ a value of false.  Otherwise, the filename is returned in parameter }
{ and the function returns a value of true.                           }

var
  win           : WindowPtr;
  WinOpts       : Longint;
  time_to_quit  : boolean;
  cursor_save   : word;
  file2,
  title,
  trailer       : string;
  any_char      : char;
  restore_mouse : boolean;

begin
  WinOpts := wBordered+wCLear;
  NormalCursor;
  keyflush;
  if MouseInstalled and mouseCursorOn
  then begin
    restore_mouse := MouseCursorOn;
    hidemouse;
  end;
  New(win, InitCustom(3, 8, 78, 10, MenuColors, WinOpts));
  win^.wFrame.AddHeader(' Enter a filename ',heTC);
  win^.wFrame.AddHeader(' ?<Enter> for Directory or <ENTER> for Main Menu ', heBC);
  win^.Draw;
  time_to_quit := false;
  while not time_to_quit do
  begin
    clrscr;
    writeln;
    write(' Filename (1-8 characters): ');
    readln(filename);
    blnkchop(filename);
    if blnkstr(filename)
    then begin
           wnfilenm := false;
           win^.Erase;
           win^.Done;
           Exit;
         end
    else if filename = '?'
    then begin
           dosdirwn;
           time_to_quit := false;
         end
    else time_to_quit := true;
  end;                    { End while loop }
    { Remove the window }
    win^.Erase;
    dispose(win,done);

    if MouseInstalled and restore_mouse
    then showmouse;
    HiddenCursor;
    wnfilenm := true;
end;