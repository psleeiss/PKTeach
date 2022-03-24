procedure numlocch;

{ This procedure displays a warning message to the user about the NUM-LOCK }
{ key being set. }

var
  win           : WindowPtr;
  answer        : word;
  restore_mouse : boolean;

begin
  if numlock = true then
  begin;
    New(win, initcustom(7, 5, 73, 19, MenuColors, wBordered+wClear));
    win^.setcursor(cuhidden);
    win^.wFrame.AddHeader(' For your information ', heTC);
    if MouseInstalled
    then begin
      restore_mouse := mousecursoron;
      hidemouse;
      win^.wFrame.AddHeader(' Press any Mouse Button ', heBC)
    end
    else
    win^.wFrame.AddHeader(' Press any Key ', heBC);
    win^.Draw;

    writeln;
    writeln;
    writeln;
    writeln;
    writeln('  This is to inform you that you currently have the NUM-LOCK');
    writeln('  key set (the light should be on).  In this part of PK-TEACH');
    writeln('  you will be moving the robot by using the arrow keys.  The ');
    writeln('  NUM-LOCK key must be turned off for the arrows to work.');

    answer := ReadKeyOrButton;

    if mouseInstalled and restore_mouse
    then showmouse;

    win^.erase;
    dispose(win,done);
  end;
end;