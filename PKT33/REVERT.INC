function revert( in_com : pk_ptr) : string;

{ This function takes as input a pointer to a pk_structure (as in PKTEACH file
{ structure) and converts it into a command string to be passed to PROCCOM }

var
  temp_pos      : robot_pos;
  temps1        : string;
  temps2        : string;
  temps3        : string;
  temps4        : string;
  temps5        : string;
  temps6        : string;
  roll_hold     : integer;

begin

  { Because REVERT can be called directly from REVISE when loading previous }
  { command, should the desired position be the home position, send back a  }
  { NEST command rather than an offset string.                              }
  if (in_com^.base = 0)       and
     (in_com^.shoulder = 0)   and
     (in_com^.elbow = 0)      and
     (in_com^.wrist_p = 0)    and
     (in_com^.wrist_r = 0)    and
     (in_com^.gripper = 0)
  then begin
    revert := 'N';
    exit;
  end;

  { Find relative move needed to get to desired position }
  temp_pos.base     := in_com^.base - abs_pos.base;
  temp_pos.shoulder := in_com^.shoulder - abs_pos.shoulder;
  temp_pos.elbow    := in_com^.elbow - seratio(temp_pos.shoulder)
                                     - abs_pos.elbow;
  temp_pos.wrist_r  := in_com^.wrist_r - abs_pos.wrist_r;
  temp_pos.wrist_p  := in_com^.wrist_p - swratio(temp_pos.shoulder)
                                       - ewratio(temp_pos.elbow)
                                       - abs_pos.wrist_p;
  temp_pos.gripper  := in_com^.gripper - abs_pos.gripper;

  { Adjust for the fact that pitch and roll both use motors 4 and 5 }
  roll_hold := temp_pos.wrist_r;
  temp_pos.wrist_r := - temp_pos.wrist_p;
  temp_pos.wrist_p := temp_pos.wrist_p + roll_hold;
  temp_pos.wrist_r := temp_pos.wrist_r + roll_hold;

  { Send command to the robot }
  str(temp_pos.base,temps1);
  str(temp_pos.shoulder,temps2);
  str(temp_pos.elbow,temps3);
  str(temp_pos.wrist_r,temps4);
  str(temp_pos.wrist_p,temps5);
  str(temp_pos.gripper,temps6);
  revert := 'M' + temps1 + ',' + temps2 + ',' + temps3 + ',' +
             temps4 + ',' + temps5 + ',' + temps6;

end;