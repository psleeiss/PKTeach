procedure gripmoit;

{ This procedure displays the "moveit" window for the gripper }

var
  Left_arrow  : char;
  right_arrow : char;

begin

  left_arrow := chr(27);
  right_arrow := chr(26);

  clrscr;

    If MouseInstalled then
    begin
      HideMouse;
      gotoxy(3,2);
      write('Current increment setting = ',robo_steps.gripper:5);
      gotoxy(3,4);
      writeln('LEFT Button to open GRIPPER');
      gotoxy(3,5);
      writeln('RIGHT Button to close GRIPPER');
      gotoxy(3,6);
      writeln('BOTH Buttons to Reset increment');
    end
  else
    begin
      gotoxy(4,2);
      write('Current increment setting = ',robo_steps.gripper:5);
      gotoxy(6,4);
      writeln(left_arrow,'    to open GRIPPER');
      gotoxy(6,5);
      writeln(right_arrow,'    to close GRIPPER');
      gotoxy(6,6);
      writeln(     'R    to Reset increment');
    end;
    win[ax]^.ChangeHeader(0, '');
end;