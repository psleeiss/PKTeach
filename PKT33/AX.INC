New(win, InitCustom(3, 12, 35, 23, MenuColors, WinOpts));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Select Axis to Move ',heTC);
  win^.wFrame.AddHeader(' Press ''X'' to exit ', heBC);
  win^.Draw;

  { Check for NUM-LOCK depressed }
  numlocch;

  writeln;
  writeln;
  writeln('         B - Base             ');
  writeln('         S - Shoulder         ');
  writeln('         E - Elbow            ');
  writeln('         R - Roll  (wrist)    ');
  writeln('         P - Pitch (wrist)    ');
  writeln('         G - Gripper          ');
  writeln;
  write(  '         Z - Zero the robot');
