procedure elbomoit;

{ This procedure displays the "moveit" window for the shoulder }

var
  up_arrow  : char;
  down_arrow : char;

begin

  up_arrow := chr(24);
  down_arrow := chr(25);

  clrscr;

    If MouseInstalled then
    begin
      HideMouse;
      gotoxy(3,2);
      write('Current increment setting = ',robo_steps.elbow:5);
      gotoxy(3,4);
      writeln('LEFT Button moves ELBOW up cw');
      gotoxy(3,5);
      writeln('RIGHT Button moves ELBOW down ccw');
      gotoxy(3,6);
      writeln('BOTH Buttons to Reset increment');
    end
  else
    begin
      gotoxy(4,2);
      write('Current increment setting = ',robo_steps.elbow:5);
      gotoxy(6,4);
      writeln(up_arrow,'    to move ELBOW upward');
      gotoxy(6,5);
      writeln(down_arrow,'    to move ELBOW downward');
      gotoxy(6,6);
      writeln(     'R    to Reset increment');
    end;
end;