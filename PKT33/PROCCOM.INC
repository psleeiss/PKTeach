function proccom(     in_str    : string;
                  var limit_err : char) : boolean;

{ This function processes a command given by the input string.  If the string
{ cannot be processed for any reason, the function returns a value of false.
{ If the function returns false AND limit_err is not blank, that means that the
{ requested operation would take an axis past it's limit.  The axis that would
{ Be exceeded is returned in limit.  It is the first character of the axis name.  }

var
  com_char : char;
  cmd      : string;
  temps1   : string[9];
  temps2   : string[9];
  temps3   : string[9];
  temps4   : string[9];
  temps5   : string[9];
  temps6   : string[9];
  h_str    : string;
  m1       : integer;
  m2       : integer;
  m3       : integer;
  m4       : integer;
  m5       : integer;
  m6       : integer;
  m7       : integer;
  roll     : integer;    { Used as a flag in "move".  If set to 1, then roll }
  pitch    : integer;    { is added in (m4 is multiplied by this value).  M5 }
                         { works the same way.             }


any_char : char;
begin

  { Be optomistic }
  proccom := true;
  limit_err := ' ';

  { Parse the command }
  if not comparse(in_str,cmd,m1,m2,m3,m4,m5,m6,m7)
  then begin
    proccom := false;
    exit;
  end;

  { get a character for case statement }
  move(cmd[1],com_char,1);

  case upcase(com_char) of
         { Close command }
    'C': begin
           rel_pos.gripper := -abs_pos.gripper;
           com_pos.gripper := -abs_pos.gripper;
           abs_pos.gripper := 0;
         end;

         { Delay...nothing to do for this one }
    'D': begin
         end;

    'G': begin

           { Parse the command }
(*           h_str := robo_mem[m1];       *)
           if blnkstr(h_str) or
              (not comparse(h_str,cmd,m1,m2,m3,m4,m5,m6,m7))
           then begin
             win[1]^.ChangeHeader(1, '');
             win[1]^.Select;
             textattr := 15;
             writeln('h_str is ',h_str);delay(3000);
             proccom := false;
             exit;
           end;

           { Find relative move needed to get to desired position }
           rel_pos.base     := m1 - abs_pos.base;
           rel_pos.shoulder := m2 - abs_pos.shoulder;
           rel_pos.elbow    := m3 - seratio(rel_pos.shoulder) - abs_pos.elbow;
           rel_pos.wrist_r  := m4 - abs_pos.wrist_r;
           rel_pos.wrist_p  := m5 - swratio(rel_pos.shoulder)
                                  - ewratio(rel_pos.elbow)
                                  - abs_pos.wrist_p;
           rel_pos.gripper  := m6 - abs_pos.gripper;

           { Set absolute position }
           abs_pos.base     := m1;
           abs_pos.shoulder := m2;
           abs_pos.elbow    := m3;
           abs_pos.wrist_r  := m4;
           abs_pos.wrist_p  := m5;
           abs_pos.gripper  := m6;

           { Send command to the robot }
           str(rel_pos.base,temps1);
           str(rel_pos.shoulder,temps2);
           str(rel_pos.elbow,temps3);
           str(rel_pos.wrist_r,temps4);
           str(rel_pos.wrist_p,temps5);
           str(rel_pos.gripper,temps6);
           h_str := 'M' + temps1 + ',' + temps2 + '.' + temps3 + ',' +
                    temps4 + ',' + temps5 + ',' + temps6;


         end;

         { HERE command.  Save an absolute location }
    'H': begin
           str(abs_pos.base,temps1);
           str(abs_pos.shoulder,temps2);
           str(abs_pos.elbow,temps3);
           str(abs_pos.wrist_r,temps4);
           str(abs_pos.wrist_p,temps5);
           str(abs_pos.gripper,temps6);
           h_str := 'M'+temps1+','+temps2+','+temps3+','+temps4+','+temps5+','+temps6;
(*           robo_mem[m1] := h_str;      *)
         end;

    'M': begin

           { Set one axis at a time }
           if abs(abs_pos.base + m1) > max_ranges.base
           then limit_err := 'B';
           if abs(abs_pos.shoulder + m2) > max_ranges.shoulder
           then limit_err := 'S';
           if abs(abs_pos.elbow + seratio(m2) + m3) > max_ranges.elbow
           then limit_err := 'E';

           { See if both the roll and the pitch have been set at the same time. }
           { Without this line errors occur when running the program. }
           roll := 0;
           pitch := 0;
           if abs(m4) <> abs(m5)
           then begin

             { Try separating out the pitch and roll from one another }
             m5 := (m5 - m4) div 2;
             m4 := m5 + m4;
             roll := 1;
             pitch := 1;

           end
           else if ( (m4 > 0) and (m5 > 0) ) or
                   ( (m4 < 0) and (m5 < 0) )
                then roll := 1
                else pitch := 1;

           { Keep roll and pitch separate from m4 and m5 }
           if ( (m4 > 0) and (m5 > 0) ) or
              ( (m4 < 0) and (m5 < 0) )
           then begin
                  if abs(abs_pos.wrist_r + (m4 * roll)) > max_ranges.wrist_r
                  then limit_err := 'R';
                end;

           if ( (m4 < 0) and (m5 > 0) ) or
              ( (m4 > 0) and (m5 < 0) ) or
              ( m2 <> 0)                or
              ( m3 <> 0)
           then if abs(abs_pos.wrist_p + swratio(m2) + ewratio(m3) + (m5 * pitch)) > max_ranges.wrist_p
                then limit_err := 'P';

           if ((abs_pos.gripper + m6) < -max_ranges.gripper ) or
              ((abs_pos.gripper + m6) > 0 )
           then limit_err := 'G';

           if limit_err <> ' '
           then begin
             proccom := false;
             exit;
           end;


           abs_pos.base := abs_pos.base + m1;
           rel_pos.base := rel_pos.base + m1;
           abs_pos.shoulder := abs_pos.shoulder + m2;
           rel_pos.shoulder := rel_pos.shoulder + m2;
           abs_pos.elbow := abs_pos.elbow + seratio(m2) + m3;
           rel_pos.elbow := rel_pos.elbow + seratio(m2) + m3;

           { Remember that M4 <> wrist roll!!! }
           if ( (m4 > 0) and (m5 > 0) ) or
              ( (m4 < 0) and (m5 < 0) ) or
              ( abs(m4) <> abs(m5) )
           then begin
             abs_pos.wrist_r := abs_pos.wrist_r + (m4 * roll);
             rel_pos.wrist_r := rel_pos.wrist_r + (m4 * roll);
           end;

           { Remember that M5 <> wrist pitch!!! }
           if ( (m4 > 0) and (m5 < 0) ) or
              ( (m4 < 0) and (m5 > 0) ) or
              ( abs(m4) <> abs(m5) )    or
              ( m2 <> 0)                or
              ( m3 <> 0)
           then begin
             abs_pos.wrist_p := abs_pos.wrist_p + swratio(m2) + ewratio(m3) +
                                (m5 * pitch);
             rel_pos.wrist_p := rel_pos.wrist_p + swratio(m2) + ewratio(m3) +
                                (m5 * pitch);
           end;

           abs_pos.gripper := abs_pos.gripper + m6;
           rel_pos.gripper := rel_pos.gripper + m6;

           { Set the com_pos structure for building of the commands }
           com_pos.base     := com_pos.base + m1;
           com_pos.shoulder := com_pos.shoulder + m2;
           com_pos.elbow    := com_pos.elbow + m3;
           com_pos.wrist_r  := com_pos.wrist_r + m4;
           com_pos.wrist_p  := com_pos.wrist_p + m5;
           com_pos.gripper  := com_pos.gripper + m6;

         end;

    'N': begin
           rel_pos.base     := -abs_pos.base;
           rel_pos.shoulder := -abs_pos.shoulder;
           rel_pos.elbow    := -abs_pos.elbow;
           rel_pos.wrist_r  := -abs_pos.wrist_r;
           rel_pos.wrist_p  := -abs_pos.wrist_p;
           rel_pos.gripper  := -abs_pos.gripper;
           roboinit(com_pos);
           roboinit(abs_pos);
         end;

    'O': begin
           rel_pos.gripper := -2000-abs_pos.gripper;
           com_pos.gripper := -2000-abs_pos.gripper;
           abs_pos.gripper := -2000;
         end;

         { Tricky on undo! }
    'S': begin
         end;

    'Z': begin
           roboinit(abs_pos);
           roboinit(rel_pos);
           roboinit(com_pos);
         end;

    else begin
      proccom := false;
      exit;
    end;

  end;    { Case Statement }


    { Execute the command  }
    robowrit(in_str);

    { Cheat on the gripper being closed or open }
    if (abs_pos.gripper = 0) and addclose
    then robowrit('C');

    if (abs_pos.gripper = max_ranges.gripper) and addopen
    then robowrit('O');

end;
