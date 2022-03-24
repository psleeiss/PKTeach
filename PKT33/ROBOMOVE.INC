procedure robomove;

{ This procedure moves the robot and updates the relative and absolute positions }

var
  win            : WindowPtr;
  win2           : WindowPtr;
  any_char       : char;
  time_to_quit   : boolean;
  WinOpts        : Longint;

begin
  WinOpts := wBordered+wClear;
  { Begin by "nesting" the robot }
  robowrit('N');
  roboinit(abs_pos);
  roboinit(rel_pos);
  roboinit(com_pos);

  New(win, InitCustom( 2, 2, 79, 23, MenuColors, WinOpts));
  win^.setcursor(cuhidden);
  win^.Draw;

  updtabsr(abs_pos);
  rangeup;
  updtrelr(rel_pos);

  New(win2, InitCustom(3, 12, 35, 23, MenuColors, WinOpts));
  win2^.setcursor(cuhidden);
  win2^.wFrame.AddHeader(' Select Axis to Move ',heTC);
  win2^.wFrame.AddHeader(' Press ''X'' to exit ', heBC);
  win2^.Draw;


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

  { Check for NUM-LOCK depressed }
  numlocch;

  { Get the response }
  time_to_quit := false;
  while not time_to_quit do
  begin

    cursroff;
    any_char := ReadKey;

    { Process the input }
    case upcase(any_char) of
      'B' : moveit('B');
      'S' : moveit('S');
      'E' : moveit('E');
      'R' : moveit('R');
      'P' : moveit('P');
      'G' : moveit('G');
      'Z' : if zverify
            then begin
              robowrit('Z');
              roboinit(abs_pos);
              roboinit(rel_pos);
              roboinit(com_pos);
              updtabsr(abs_pos);
              updtrelr(rel_pos);
            end;
      'X' : time_to_quit := true;
      else  time_to_quit := false;
    end;

  end;   { While statement }


  { Restore original step values }
  robostep(robo_steps);

  { Nest the robot }
  robowrit('N');
  roboinit(abs_pos);
  roboinit(rel_pos);
  roboinit(com_pos);

  win[com].erase;
  win[relr].erase;
  win[range].erase;
  win[absr].erase;
  dispose(win2,done);
  dispose(win,done);


(*  repeat
    win := wStack.UnStackTop;
    if win <> nil then
    Dispose(win, done);
  until win = nil;
*)

end;