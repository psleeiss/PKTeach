procedure pitcmoit;

{ This procedure displays the "moveit" window for the wrist pitch }

var
  up_arrow  : char;
  down_arrow : char;

begin

  up_arrow := chr(24);
  down_arrow := chr(25);

  clrscr;

    If MouseInstalled then
    begin
      gotoxy(3,2);
      write('Current increment setting = ',robo_steps.wrist_p:5);
      gotoxy(3,4);
      writeln('LEFT Button moves WRIST PITCH   ',up_arrow);
      gotoxy(3,5);
      writeln('RIGHT Button moves WRIST PITCH  ',down_arrow);
      gotoxy(3,6);
      writeln('BOTH Buttons to Reset increment');
    end
  else
    begin
      gotoxy(3,2);
      write('Current increment setting = ',robo_steps.wrist_p:5);
      gotoxy(4,4);
      writeln(up_arrow,'    to move WRIST PITCH upward');
      gotoxy(4,5);
      writeln(down_arrow,'    to move WRIST PITCH downward');
      gotoxy(4,6);
      writeln(     'R    to Reset increment');
    end;
    win[ax]^.ChangeHeader(0, '');
end;