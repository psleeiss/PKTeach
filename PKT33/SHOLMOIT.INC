procedure sholmoit;

{ This procedure displays the "moveit" window for the shoulder }

var
  up_arrow  : char;
  down_arrow : char;

begin
  HideMouse;
  up_arrow := chr(24);
  down_arrow := chr(25);

  clrscr;

    If MouseInstalled then
    begin
      HideMouse;
      gotoxy(3,2);
      write('Current increment setting = ',robo_steps.shoulder:5);
      gotoxy(3,4);
      writeln('LEFT Button moves SHOULDER up');
      gotoxy(3,5);
      writeln('RIGHT Button moves SHOULDER down');
      gotoxy(3,6);
      writeln('BOTH Buttons to Reset increment');
    end
  else
    begin
      gotoxy(4,2);
      write('Current increment setting = ',robo_steps.shoulder:5);
      gotoxy(6,4);
      writeln(up_arrow,'    to move SHOULDER upward');
      gotoxy(6,5);
      writeln(down_arrow,'    to move SHOULDER downward');
      gotoxy(6,6);
      writeln(     'R    to Reset increment');
    end;
    win[ax]^.ChangeHeader(0, '');
end;