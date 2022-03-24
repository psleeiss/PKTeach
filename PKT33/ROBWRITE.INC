procedure robwrite;

{ This procedure moves the robot and updates the relative and absolute positions }

var
  win            : WindowPtr;
  any_char       : char;
  time_to_quit   : boolean;
  one_point      : boolean;

begin

  { Display the proper menus }

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
  write(  '         A - Add point to file');


  { Check to see if the numlock is set }
  numlocch;

  { Record if at least one point is saved }
  one_point := false;

  { Get the response }
  time_to_quit := false;
  while not time_to_quit do
  begin

    cursroff;
    any_char := readkey;

    { Process the input }
    case upcase(any_char) of
      'B' : writeit('B');
      'S' : writeit('S');
      'E' : writeit('E');
      'R' : writeit('R');
      'P' : writeit('P');
      'G' : writeit('G');
      'A' : begin
              addpt;
              updtcomr(' ');
              updtrelr(rel_pos);
              one_point := true;
            end;
      'X' : time_to_quit := true;
      else  time_to_quit := false;
    end;

  end;   { While statement }

(*  win := wStack.UnStackTop; *)

  { See if the point should be saved if one is still in process }
  if (rel_pos.base <> 0) or
     (rel_pos.shoulder <> 0) or
     (rel_pos.elbow <> 0) or
     (rel_pos.wrist_r <> 0) or
     (rel_pos.wrist_p <> 0) or
     (rel_pos.gripper <> 0)
  then if savechk
       then addpt
       else reststat;

  updtcomr(' ');
  updtabsr(abs_pos);
  updtrelr(rel_pos);

  win^.Draw;

end;