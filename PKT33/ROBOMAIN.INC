procedure robomain;

{ This procedure handles the main menu for the PK Teach program }


var
  any_char     : char;
  popup_win    : popup_rec;
  popup_rc     : byte;
  time_to_quit : boolean;
  base_attr    : byte;

begin

  textcolor(white);
  textbackground(black);
  clrscr;

  { Copy protection check }
  if everlock.check_copy_protection <> passed_protection_check
  then security_msg;

  with popup_win do
  begin
    window_attr := win_color[nextwin];
    frame_type  := single;
    x1          := 1;
    y1          := 1;
    x2          := 80;
    y2          := 25;
    title       := ' PK-TEACH '+pk_version + ' Main Menu ';
    trailer     := ' Select by Letter ';
  end;

  popup_rc := popup(popup_win,true);  { Clear the window }
  if popup_rc < 1
  then begin
    writeln('Error from popup_window routines');
    writeln('Error was in: ',windrout);
    writeln(windemsg);
    halt(1);
  end;

  gotoxy(18,3);
  write('[W].......................Write a new program');
  gotoxy(18,wherey+2);
  write('[E].......................Edit a program');
  gotoxy(18,wherey+2);
  write('[R].......................Run a program');
  gotoxy(18,wherey+2);
  write('[D].......................Delete a program');
  gotoxy(18,wherey+2);
  write('[M].......................Move robot using keyboard');
  gotoxy(18,wherey+4);
  write('[T].......................Translate PK-TEACH file to ASCII ');
  gotoxy(18,wherey+2);
  write('[?].......................Directory of program files');
  gotoxy(18,wherey+2);
  write('[I].......................Product Information');
  gotoxy(18,wherey+2);
  write('[X].......................Exit PK-TEACH');

  { Turn off the cursor }
  cursroff;

  time_to_quit := false;
  while not time_to_quit do
  begin

    { In case we pop up of a lower level routine "abruptly", reset the windows }
    robot_rel_win := window_down;
    robot_abs_win := window_down;
    robot_com_win := window_down;

    any_char := readkey;
    cursroff;
    case upcase(any_char) of
      'M' : begin
              robot_mode := move_only;
              revise;
            end;

      'W' : begin
              robot_mode := write_new;
              revise;
            end;

            { Run a program }
      'R' : exeprog;

            { Delete program }
      'D' : delprog;

            { Edit a program }
      'E' : begin
              robot_mode := edit_prog;
              revise;
            end;

            { DOS directory }
      '?' : dosdirwn;

            { Translate a program to ASCII format }
      'T' : pktoasc;

            { Product information }
      'I' : prodinf;

            { Exit }
      'X' : if pkexit = 'Y'
            then time_to_quit := true;

      else time_to_quit := false;
    end;   { Case statement }
  end;    { while statement }


    { Restore the cursor }
    cursron;

    if not popdown(popup_win)
    then begin
      writeln('Error in popdown routine');
      halt(1);
    end;

    { Reset starting colors }
    textcolor(white);
    textbackground(black);
    clrscr;

end;
