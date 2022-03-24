procedure raddpt;

{ This procedure adds a robot position point to the global variable FILE1
{ which must have been already openned.  It also will give a confirmation
{ that the point was saved or that no movement took place. It also resets
{ com_pos and rel_pos structures (due to the fact that they should now
{ be zeroed out.  }

var
 s1,s2,s3,s4,s5,s6   : string;
 win                 : WindowPtr;
 any_char            : word;
 cur_command         : str41;


begin

  New(win, InitCustom(22, 10, 57, 14, MenuColors, wBordered+wClear));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Press any Key or Mouse Button', heBC);
  win^.Draw;

  str(com_pos.base,s1);
  str(com_pos.shoulder,s2);
  str(com_pos.elbow,s3);
  str(com_pos.wrist_r,s4);
  str(com_pos.wrist_p,s5);
  str(com_pos.gripper,s6);

  if (com_pos.base = 0) and
     (com_pos.shoulder = 0) and
     (com_pos.elbow = 0) and
     (com_pos.wrist_r = 0) and
     (com_pos.wrist_p = 0) and
     (com_pos.gripper = 0)
  then begin
    writeln;
    write('    No net change in position');
  end
  else begin
    { Simulate savestat without the H99 call because we have already executed }

    cur_command := 'M'+s1+','+s2+','+s3+','+s4+','+s5+','+s6;
    fileit(cur_command);
    roboinit(com_pos);
    roboinit(rel_pos);
    writeln;
    writeln('        Point has been added ');
  end;

  { Wait for response }
  any_char := ReadKeyOrButton;

  win^.Erase;
  dispose(win,done);
end;
