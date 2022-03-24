procedure rangeout(axis : char);

{ This procedure informs the user that the robot's arm has gone out of range }

var
  win       : WindowPtr;
  WinOpts   : Longint;
  answer    : Word;


begin
  WinOpts := wBordered+wClear;
  New(win, initcustom(3, 10, 78, 14, MenuColors, WinOpts));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Robot Is Unable to Do That ',heTC);
  win^.wFrame.AddHeader(' Press any Key or Mouse Button to continue ',heBC);
  win^.Draw;

  axis := upcase(axis);
  gotoxy(26,2);
  case axis of
    'B':write('   Robot Base out of range');
    'S':write(' Robot Shoulder out of range');
    'E':write('  Robot Elbow out of range');
    'P':write('Robot Wrist Pitch out of range');
    'R':write('Robot Wrist Roll out of range');
    'G':write('  Robot Gripper out of range');
    else whistle;
  end;   { Case statement }
  answer := ReadKeyOrButton;

  win^.Erase;
  dispose(win,done);
end;
