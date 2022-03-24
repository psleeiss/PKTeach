procedure writenew;

{ This procedure handles the writing of a new program }

var
  popup_win    : popup_rec;
  popup_winb   : popup_rec;
  any_char     : char;
  time_to_quit : boolean;
  limit_err    : char;
  dummy_boolean: boolean;
  filename     : string;
  noext        : string;
  command      : string;
  good_name    : boolean;

begin

  { See if the robot is in the zero position }
  robowrit('N');
  roboinit(abs_pos);
  roboinit(rel_pos);
  roboinit(com_pos);
  if not zquest
  then exit;

  { Display the windows }
  with popup_winb do
  begin
    window_attr := win_color[nextwin];
    frame_type  := single;
    x1          := 1;
    y1          := 1;
    x2          := 80;
    y2          := 25;
    title       := '';
    trailer     := '';
  end;

  if popup(popup_winb,true) < 1
  then begin
    wereport('Could not display background window');
    halt(1);
  end;

  { Get the filename from the user }
  good_name := false;
  while not good_name do
  begin

    if not wnfilenm(filename)
    then if not popdown(popup_win)
         then begin
           wereport('Could not remove the create background window');
           halt(1);
         end
         else exit;

    noext := upperstr(filename);
    filename := upperstr(filename) + '.PRG';

    { Open the file }
    if newfile(file1,filename)
    then begin
           writeln(file1,'Z');
           good_name := true;
         end;

  end;   { While statement }

  with popup_win do
  begin
    window_attr := win_color[nextwin];
    frame_type  := double;
    x1          := 1;
    y1          := 12;
    x2          := 35;
    y2          := 24;
    title       := ' Creating ' + noext + ' ';
    trailer     := ' Press ''X'' to exit';
  end;

  if popup(popup_win,true) < 1
  then begin
    wereport('Could not display main create menu');
    halt(1);
  end;

  writeln;
  writeln;
  writeln(' C - Close        N - Nest');
  writeln(' D - Delay        O - Open');
  writeln(' F - Fast/slow    T - goTo ');
  writeln(' H - Here                  ');
  writeln;
  writeln(' M - Movement (point to point)');

  updtabsr(abs_pos);
  rangeup;
  updtrelr(abs_pos);
  updtcomr(' ');


  time_to_quit := false;
  while not time_to_quit do
  begin

    cursroff;
    any_char := readkey;
    Case upcase(any_char) of
      'C':if gripclos
          then begin
            if not proccom('C',limit_err)
            then begin
              writeln('Could not process the command!!!');
              halt(1);
            end;
            updtabsr(abs_pos);
            updtrelr(rel_pos);
            updtcomr('C');
            roboinit(rel_pos);
            roboinit(com_pos);
            writeln(file1,'C');
          end;

      'D':if tdelay(command)
          then begin
            if not proccom(command,limit_err)
            then begin
              writeln('Could not process the command!!!');
              halt(1);
            end;
            updtcomr(command);
            writeln(file1,command);
          end;

      'T':if cgoto(command)
          then begin
            if not proccom(command,limit_err)
            then begin
              window(1,1,80,25);
              textattr := 15;
              writeln('Could not process the goto command!!!');
              halt(1);
            end;
            updtabsr(abs_pos);
            updtrelr(abs_pos);
            updtcomr(command);
            roboinit(com_pos);
            roboinit(rel_pos);
            writeln(file1,command);
            cursroff;
          end;

      'H':if here(command)
          then begin
            if not proccom(command,limit_err)
            then begin
              writeln('Could not process the here command!!!');
              halt(1);
            end;
            updtabsr(abs_pos);
            updtrelr(rel_pos);
            updtcomr(command);
            writeln(file1,command);
            cursroff;
          end;

      'M':robwrite;
      'N':if nest
          then begin
            if not proccom('N',limit_err)
            then begin
              writeln('Could not process the command!!!');
              halt(1);
            end;
            updtabsr(abs_pos);
            updtrelr(rel_pos);
            roboinit(rel_pos);
            updtcomr('N');
            writeln(file1,'N')
          end;

      'O':if gripopen
          then begin
            if not proccom('O',limit_err)
            then begin
              writeln('Could not process the command!!!');
              halt(1);
            end;
            updtabsr(abs_pos);
            updtrelr(rel_pos);
            roboinit(rel_pos);
            roboinit(com_pos);
            updtcomr('O');
            writeln(file1,'O');
          end;

{      'P':robwrite;  }
      'F':if speed(command)
          then begin
            if not proccom(command,limit_err)
            then begin
              writeln('Could not process the command!!!');
              halt(1);
            end;
            updtcomr(command);
            writeln(file1,command);
          end;
      'X':if writexit = 'Y'
          then time_to_quit := true;

      else time_to_quit := false;
    end;
  end;

  { Force last command to be nest }
  If last_command <> 'N'
  then begin
    writeln(file1,'N');
    robowrit('N');
  end;
  roboinit(abs_pos);
  roboinit(rel_pos);
  roboinit(com_pos);
  robostep(robo_steps);

  { Close the file }
  close(file1);

  if not popdown(popup_win)
  then begin
    wereport('Could not remove the robot command menu');
    halt(1);
  end;
  robot_com_win := window_down;

  if not popdown(popup_win)
  then begin
    wereport('Could not remove the relative position menu');
    halt(1);
  end;
  robot_rel_win := window_down;

  if not popdown(popup_win)
  then begin
    wereport('Could not remove the max ranges menu');
    halt(1);
  end;

  if not popdown(popup_win)
  then begin
    wereport('Could not remove the absolute position menu');
    halt(1);
  end;
  robot_abs_win := window_down;

  if not popdown(popup_win)
  then begin
    wereport('Could not remove the command menu');
    halt(1);
  end;

  if not popdown(popup_win)
  then begin
    wereport('Could not remove the command background menu');
    halt(1);
  end;

end;