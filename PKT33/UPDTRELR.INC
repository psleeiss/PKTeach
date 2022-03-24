procedure updtrelr( robot      : robot_pos);

{ This procedure updates the robot's current position relative to the }
{ last point recorded.                                                }

begin

  { Get rid of the cursor }
  HiddenCursor;
  if MouseInstalled then
    HideMouse;
  win[relr]^.wFrame.AddHeader(' Relative Position ',heTC);
  win[relr]^.Select;
     { Display the titles }
     gotoxy(2,2);
     write('Base          - ');
     gotoxy(2,3);
     write('Shoulder      - ');
     gotoxy(2,4);
     write('Elbow         - ');
     gotoxy(2,5);
     write('Wrist Roll    - ');
     gotoxy(2,6);
     write('Wrist Pitch   - ');
     gotoxy(2,7);
     write('Gripper       - ');


  { Update the robot postion portion of the screen }
  gotoxy(18,2);
  write(robot.base:5);
  gotoxy(18,3);
  write(robot.shoulder:5);
  gotoxy(18,4);
  write(robot.elbow:5);
  gotoxy(18,5);
  write(robot.wrist_r:5);
  gotoxy(18,6);
  write(robot.wrist_p:5);
  gotoxy(18,7);
  write(robot.gripper:5);


end;