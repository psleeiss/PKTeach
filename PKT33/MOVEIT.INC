procedure moveit( Axis : char);

{ This procedure handles the moving and possible resetting of an axis }

var
  any_char        : char;
  temp_str        : string;
  time_to_quit    : boolean;
  valid_sel       : boolean;
  valid_inc       : boolean;
  limit_err       : char;
  ord_char        : integer;
  u_arr           : char;
  d_arr           : char;
  l_arr           : char;
  r_arr           : char;
  cmd_str         : string;


begin
  WinOpts := wBordered+wClear;
  { Set up graphic arrows }
  u_arr := chr(24);
  d_arr := chr(25);
  l_arr := chr(27);
  r_arr := chr(26);

  { Make sure we have a valid axis }
  axis := upcase(axis);
  if not (axis in ['B','S','E','R','P','G'])
  then exit;

  updtcomr(' ');

    case axis of
      'B': title := ' Move Base ';
      'S': title := ' Move Shoulder ';
      'E': title := ' Move Elbow ';
      'R': title := ' Move Wrist Roll ';
      'P': title := ' Move Wrist Pitch ';
      'G': title := ' Move Gripper ';
    end;
    trailer     := ' Press ''X'' to exit ';

  win[ax]^.wFrame.AddHeader(title, heTC);
  win[ax]^.wFrame.AddHeader(trailer, heBC);
  win[ax]^.Draw;

  case upcase(axis) of
    'B': begin

           { Display the data }
           basemoit;

           { Get their input }
           valid_sel := false;
           while not valid_sel do
           begin

             { Get the user's input.  Do not allow buffering of input. }
             keyflush;
             any_char := upcase(readkey);


             if any_char = #0
             then ord_char := ord(readkey) + 1000
             else ord_char := ord(any_char);
             case ord_char of

               { Left arrow }
               left: begin
                       str(robo_steps.base,temp_str);
                       cmd_str := 'M' + temp_str + ',0,0,0,0,0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       cursroff;
                       {data_win.Draw;}

                       { Process the command }
                       if not proccom(cmd_str,limit_err)
                       then if limit_err <> ' '
                            then rangeout(limit_err)
                            else begin
                              writeln('Bad command');
                              halt(1);
                            end;
                      end;  { Left_arrow case clause }

               { right arrow }
               right:begin
                       str(robo_steps.base,temp_str);
                       cmd_str := 'M-' + temp_str + ',0,0,0,0,0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       cursroff;
                       {data_win.Draw;}


                       { Process the command }
                       if not proccom(cmd_str,limit_err)
                       then if limit_err <> ' '
                            then rangeout(limit_err)
                            else begin
                              writeln('Bad command');
                              halt(1);
                            end;
                      end;  { Left_arrow case clause }

                    { Increment reset }
               82 : begin
                      clrscr;
                      gotoxy(4,2);
                      writeln('Current increment setting = ',robo_steps.base:5);

                      valid_inc := false;
                      while not valid_inc do
                      begin

                        { Get a new range }
                        cursron;
                        gotoxy(7,4);
                        writeln('Valid range is 1 - ',max_ranges.base);
                        gotoxy(7,5);
                        write('Enter new increment: ');
                        robo_steps.base := getint;

                        if (robo_steps.base > 0)  and
                           (robo_steps.base <= max_ranges.base)
                        then begin
                          valid_inc := true;
                          clrscr;
                          basemoit;
                          cursroff;
                        end
                        else begin
                          gotoxy(7,7);
                          write('Enter a value in range please');
                        end;
                      end;   { While statement }
                    end;

                    { Exit...'X' }
               88 : valid_sel := true;

               else valid_sel := false;

             end;  { Case statement }

             updtabsr(abs_pos);
             cursroff;
             {data_win.Draw;}

           end;   { While statement }
       end;

    'S': begin

           { Display the data }
           sholmoit;

           { Get their input }
           valid_sel := false;
           while not valid_sel do
           begin

             { Get the user's input.  Do not allow buffering of input. }
             keyflush;
             any_char := upcase(readkey);


             if any_char = #0
             then ord_char := ord(readkey) + 1000
             else ord_char := ord(any_char);
             case ord_char of

               { upward  }
               up  : begin
                       str(robo_steps.shoulder,temp_str);
                       cmd_str := 'M0,' + temp_str + ',0,0,0,0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       cursroff;
                       {data_win.Draw;}

                       { Process the command }
                       if not proccom(cmd_str,limit_err)
                       then if limit_err <> ' '
                            then rangeout(limit_err)
                            else begin
                              writeln('Bad command');
                              halt(1);
                            end;
                      end;  { Left_arrow case clause }

               { down arrow }
               down :begin
                       str(robo_steps.shoulder,temp_str);
                       cmd_str := 'M0,-' + temp_str + ',0,0,0,0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       cursroff;
                       data.win.Draw;

                       { Process the command }
                       if not proccom(cmd_str,limit_err)
                       then if limit_err <> ' '
                            then rangeout(limit_err)
                            else begin
                              writeln('Bad command');
                              halt(1);
                            end;
                      end;  { Left_arrow case clause }

                    { Increment reset }
               82 : begin
                      clrscr;
                      gotoxy(4,2);
                      writeln('Current increment setting = ',robo_steps.shoulder:5);

                      valid_inc := false;
                      while not valid_inc do
                      begin

                        { Get a new range }
                        cursron;
                        gotoxy(7,4);
                        writeln('Valid range is 1 - ',max_ranges.shoulder);
                        gotoxy(7,5);
                        write('Enter new increment: ');
                        robo_steps.shoulder := getint;

                        if (robo_steps.shoulder > 0)  and
                           (robo_steps.shoulder <= max_ranges.shoulder)
                        then begin
                          valid_inc := true;
                          clrscr;
                          sholmoit;
                          cursroff;
                        end
                        else begin
                          gotoxy(7,7);
                          write('Enter a value in range please');
                        end;
                      end;   { While statement }
                    end;

                    { Exit...'X' }
               88 : valid_sel := true;

               else valid_sel := false;

             end;  { Case statement }

             updtabsr(abs_pos);
             cursroff;
             {data_win.Draw;}

           end;   { While statement }
       end;

    'E': begin

           { Display the data }
           elbomoit;

           { Get their input }
           valid_sel := false;
           while not valid_sel do
           begin

             { Get the user's input.  Do not allow buffering of input. }
             keyflush;
             any_char := upcase(readkey);


             if any_char = #0
             then ord_char := ord(readkey) + 1000
             else ord_char := ord(any_char);
             case ord_char of

               { upward  }
               up  : begin
                       str(robo_steps.elbow,temp_str);
                       cmd_str := 'M0,0,' + temp_str + ',0,0,0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       cursroff;
                       {data_win.Draw;}

                       { Process the command }
                       if not proccom(cmd_str,limit_err)
                       then if limit_err <> ' '
                            then rangeout(limit_err)
                            else begin
                              writeln('Bad command');
                              halt(1);
                            end;
                      end;  { Left_arrow case clause }

               { down arrow }
               down :begin
                       str(robo_steps.elbow,temp_str);
                       cmd_str := 'M0,0,-' + temp_str + ',0,0,0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       cursroff;
                       {data_win.draw;}

                       { Process the command }
                       if not proccom(cmd_str,limit_err)
                       then if limit_err <> ' '
                            then rangeout(limit_err)
                            else begin
                              writeln('Bad command');
                              halt(1);
                            end;
                      end;  { Left_arrow case clause }

                    { Increment reset }
               82 : begin
                      clrscr;
                      gotoxy(4,2);
                      writeln('Current increment setting = ',robo_steps.elbow:5);

                      valid_inc := false;
                      while not valid_inc do
                      begin

                        { Get a new range }
                        cursron;
                        gotoxy(7,4);
                        writeln('Valid range is 1 - ',max_ranges.elbow);
                        gotoxy(7,5);
                        write('Enter new increment: ');
                        robo_steps.elbow := getint;

                        if (robo_steps.elbow > 0)  and
                           (robo_steps.elbow <= max_ranges.elbow)
                        then begin
                          valid_inc := true;
                          clrscr;
                          elbomoit;
                          cursroff;
                        end
                        else begin
                          gotoxy(7,7);
                          write('Enter a value in range please');
                        end;
                      end;   { While statement }
                    end;

                    { Exit...'X' }
               88 : valid_sel := true;

               else valid_sel := false;

             end;  { Case statement }

             updtabsr(abs_pos);
             cursroff;
             {data_win.draw;}

           end;   { While statement }
       end;

    'R': begin

           { Display the data }
           rollmoit;

           { Get their input }
           valid_sel := false;
           while not valid_sel do
           begin

             { Get the user's input.  Do not allow buffering of input. }
             keyflush;
             any_char := upcase(readkey);


             if any_char = #0
             then ord_char := ord(readkey) + 1000
             else ord_char := ord(any_char);
             case ord_char of

               { ccw  }
               left: begin
                       str(robo_steps.wrist_r,temp_str);
                       cmd_str := 'M0,0,0,' + temp_str + ',' + temp_str + ',0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       cursroff;
                       {data_win.Draw;}

                       { Process the command }
                       if not proccom(cmd_str,limit_err)
                       then if limit_err <> ' '
                            then rangeout(limit_err)
                            else begin
                              writeln('Bad command');
                              halt(1);
                            end;
                      end;  { Left_arrow case clause }

               { right arrow }
               right:begin
                       str(robo_steps.wrist_r,temp_str);
                       cmd_str := 'M0,0,0,-' + temp_str + ',-' + temp_Str + ',0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       cursroff;
                       {data_win.Draw;}

                       { Process the command }
                       if not proccom(cmd_str,limit_err)
                       then if limit_err <> ' '
                            then rangeout(limit_err)
                            else begin
                              writeln('Bad command');
                              halt(1);
                            end;
                      end;  { Left_arrow case clause }

                    { Increment reset }
               82 : begin
                      clrscr;
                      gotoxy(4,2);
                      writeln('Current increment setting = ',robo_steps.wrist_r:5);

                      valid_inc := false;
                      while not valid_inc do
                      begin

                        { Get a new range }
                        cursron;
                        gotoxy(7,4);
                        writeln('Valid range is 1 - ',max_ranges.wrist_r);
                        gotoxy(7,5);
                        write('Enter new increment: ');
                        robo_steps.wrist_r := getint;

                        if (robo_steps.wrist_r > 0)  and
                           (robo_steps.wrist_r <= max_ranges.wrist_r)
                        then begin
                          valid_inc := true;
                          clrscr;
                          rollmoit;
                          cursroff;
                        end
                        else begin
                          gotoxy(7,7);
                          write('Enter a value in range please');
                        end;
                      end;   { While statement }
                    end;

                    { Exit...'X' }
               88 : valid_sel := true;

               else valid_sel := false;

             end;  { Case statement }

             updtabsr(abs_pos);
             cursroff;
             {data_win.Draw;}

           end;   { While statement }
       end;

    'P': begin

           { Display the data }
           pitcmoit;

           { Get their input }
           valid_sel := false;
           while not valid_sel do
           begin

             { Get the user's input.  Do not allow buffering of input. }
             keyflush;
             any_char := upcase(readkey);


             if any_char = #0
             then ord_char := ord(readkey) + 1000
             else ord_char := ord(any_char);
             case ord_char of

               { upward  }
               up  : begin
                       str(robo_steps.wrist_p,temp_str);
                       cmd_str := 'M0,0,0,-' + temp_str + ',' + temp_str + ',0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       cursroff;
                       {data_win.Draw;}

                       { Process the command }
                       if not proccom(cmd_str,limit_err)
                       then if limit_err <> ' '
                            then rangeout(limit_err)
                            else begin
                              writeln('Bad command');
                              halt(1);
                            end;
                      end;  { Left_arrow case clause }

               { down arrow }
               down :begin
                       str(robo_steps.wrist_p,temp_str);
                       cmd_str := 'M0,0,0,' + temp_str + ',-' + temp_Str + ',0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       cursroff;
                       {data_win.Draw;}

                       { Process the command }
                       if not proccom(cmd_str,limit_err)
                       then if limit_err <> ' '
                            then rangeout(limit_err)
                            else begin
                              writeln('Bad command');
                              halt(1);
                            end;
                      end;  { Left_arrow case clause }

                    { Increment reset }
               82 : begin
                      clrscr;
                      gotoxy(4,2);
                      writeln('Current increment setting = ',robo_steps.wrist_p:5);

                      valid_inc := false;
                      while not valid_inc do
                      begin

                        { Get a new range }
                        cursron;
                        gotoxy(7,4);
                        writeln('Valid range is 1 - ',max_ranges.wrist_p);
                        gotoxy(7,5);
                        write('Enter new increment: ');
                        robo_steps.wrist_p := getint;

                        if (robo_steps.wrist_p > 0)  and
                           (robo_steps.wrist_p <= max_ranges.wrist_p)
                        then begin
                          valid_inc := true;
                          clrscr;
                          pitcmoit;
                          cursroff;
                        end
                        else begin
                          gotoxy(7,7);
                          write('Enter a value in range please');
                        end;
                      end;   { While statement }
                    end;

                    { Exit...'X' }
               88 : valid_sel := true;

               else valid_sel := false;

             end;  { Case statement }

             updtabsr(abs_pos);
             cursroff;
             {data_win.Draw;}

           end;   { While statement }
       end;

    'G': begin

           { Display the data }
           gripmoit;

           { Get their input }
           valid_sel := false;
           while not valid_sel do
           begin

             { Get the user's input.  Do not allow buffering of input. }
             keyflush;
             any_char := upcase(readkey);


             if any_char = #0
             then ord_char := ord(readkey) + 1000
             else ord_char := ord(any_char);
             case ord_char of

               { left  }
               left: begin
                       str(robo_steps.gripper,temp_str);
                       cmd_str := 'M0,0,0,0,0,-' + temp_str;

                       { Display command in command window }
                       updtcomr(cmd_str);
                       cursroff;
                       {data_win.Draw;}

                       { Process the command }
                       if not proccom(cmd_str,limit_err)
                       then if limit_err <> ' '
                            then rangeout(limit_err)
                            else begin
                              writeln('Bad command');
                              halt(1);
                            end;
                      end;  { Left_arrow case clause }

               { right arrow }
               right:begin
                       str(robo_steps.gripper,temp_str);
                       cmd_str := 'M0,0,0,0,0,' + temp_str;

                       { Display command in command window }
                       updtcomr(cmd_str);
                       cursroff;
                       data.win.Draw;

                       { Process the command }
                       if not proccom(cmd_str,limit_err)
                       then if limit_err <> ' '
                            then rangeout(limit_err)
                            else begin
                              writeln('Bad command');
                              halt(1);
                            end;
                      end;  { Left_arrow case clause }

                    { Increment reset }
               82 : begin
                      clrscr;
                      gotoxy(4,2);
                      writeln('Current increment setting = ',robo_steps.gripper:5);

                      valid_inc := false;
                      while not valid_inc do
                      begin

                        { Get a new range }
                        cursron;
                        gotoxy(7,4);
                        writeln('Valid range is 1 - ',max_ranges.gripper);
                        gotoxy(7,5);
                        write('Enter new increment: ');
                        robo_steps.gripper := getint;

                        if (robo_steps.gripper > 0)  and
                           (robo_steps.gripper <= max_ranges.gripper)
                        then begin
                          valid_inc := true;
                          clrscr;
                          gripmoit;
                          cursroff;
                        end
                        else begin
                          gotoxy(7,7);
                          write('Enter a value in range please');
                        end;
                      end;   { While statement }
                    end;

                    { Exit...'X' }
               88 : valid_sel := true;

               else valid_sel := false;

             end;  { Case statement }

             updtabsr(abs_pos);
             cursroff;
             {data_win.Draw;}

           end;   { While statement }
       end;


   end;  { Case Statement }

   repeat
     win := wStack.UnStackTop;
     if win <> nil then begin
       Dispose(win, Done);
       Delay(1000);
     until win = nil;


  robot_com_win := window_down;}

  { Update the absolute screen again }
  updtabsr(abs_pos);

end;