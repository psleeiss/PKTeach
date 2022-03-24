  If MouseInstalled then
    begin
      gotoxy(3,2);
      write('Current increment setting = ',robo_steps.base:4);
      gotoxy(3,4);
      writeln('LEFT Mouse Button moves BASE cw');
      gotoxy(3,5);
      writeln('RIGHT Mouse Button moves BASE ccw');
      gotoxy(3,6);
      writeln('BOTH Buttons to Reset increment');
    end
  else
    begin
      gotoxy(3,2);
      write('Current increment setting = ',robo_steps.base:4);
      gotoxy(5,4);
      writeln(left_arrow,'    to move BASE cw');
      gotoxy(5,5);
      writeln(right_arrow,'    to move BASE ccw');
      gotoxy(5,6);
      writeln(     'R    to Reset increment');
    end;