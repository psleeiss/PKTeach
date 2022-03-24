procedure rollmoit;

{ This procedure displays the "moveit" window for the wrist roll }

var
  Left_arrow  : char;
  right_arrow : char;

begin

  left_arrow := chr(27);
  right_arrow := chr(26);

  clrscr;

    If MouseInstalled then
    begin
      gotoxy(3,2);
      write('Current increment setting = ',robo_steps.wrist_r:5);
      gotoxy(3,4);
      writeln('LEFT Button to ROLL WRIST ccw');
      gotoxy(3,5);
      writeln('RIGHT Button to ROLL WRIST cw');
      gotoxy(3,6);
      writeln('BOTH Buttons to Reset increment');
    end
  else
    begin
      gotoxy(4,2);
      write('Current increment setting = ',robo_steps.wrist_r:5);
      gotoxy(6,4);
      writeln(left_arrow,'    to ROLL WRIST ccw');
      gotoxy(6,5);
      writeln(right_arrow,'    to ROLL WRIST cw');
      gotoxy(6,6);
      writeln(     'R    to Reset increment');
    end;
    win[ax]^.ChangeHeader(0, '');
end;