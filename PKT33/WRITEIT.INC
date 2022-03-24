procedure writeit( Axis : char);

{ This procedure handles the moving and possible resetting of an axis }

const
  left = 19200;
  right = 19712;
  up = 18432;
  down = 20480;

var
  time_to_quit,
  valid_sel,
  valid_inc,
  redraw,
  one_move        : boolean;
  ord_char        : integer;
  any_char        : char;
  limit_err,
  u_arr,
  d_arr,
  l_arr,
  r_arr           : char;
  cmd_str,
  temp_str,
  trailer         : string;
  NeedToAddHeader : boolean;
(*  TPI             : byte;
  BottomIndex     : byte; *)

begin
  If MouseInstalled then
    HideMouse;
  { Set up graphic arrows }
  u_arr := chr(24);
  d_arr := chr(25);
  l_arr := chr(27);
  r_arr := chr(26);

  { check to see if a move is actually ever made }
  one_move := false;

  { Make sure we have a valid axis }
  if not (upcase(axis) in ['B','S','E','R','P','G'])
  then exit;

  { Display the necessary windows }
  updtcomr(' ');

    NeedToAddHeader := (win[ax]^.wFrame.GetLastHeaderIndex = 255); {none}

    case axis of
      'B': begin
             if NeedToAddHeader
             then begin
               win[ax]^.wFrame.AddHeader(' Move Base ', heTC);
               TPI := win[ax]^.wFrame.GetLastHeaderIndex;
             end;
             win[ax]^.wFrame.DisableHeader(TPI, False);
           end;
      'S': begin
             if NeedToAddHeader
             then begin
               win[ax]^.wFrame.AddHeader(' Move Shoulder ', heTC);
               TPI := win[ax]^.wFrame.GetLastHeaderIndex;
             end;
             win[ax]^.wFrame.DisableHeader(TPI, False);
           end;
      'E': begin
             if NeedToAddHeader
             then begin
               win[ax]^.wFrame.AddHeader(' Move Elbow ', heTC);
               TPI := win[ax]^.wFrame.GetLastHeaderIndex;
             end;
             win[ax]^.wFrame.DisableHeader(TPI, False);
           end;
      'P': begin
             if NeedToAddHeader
             then begin
               win[ax]^.wFrame.AddHeader(' Move Wrist Pitch ', heTC);
               TPI := win[ax]^.wFrame.GetLastHeaderIndex;
             end;
             win[ax]^.wFrame.DisableHeader(TPI, False);
           end;
      'R': begin
             if NeedToAddHeader
             then begin
               win[ax]^.wFrame.AddHeader(' Move Wrist Roll ', heTC);
               TPI := win[ax]^.wFrame.GetLastHeaderIndex;
             end;
             win[ax]^.wFrame.DisableHeader(TPI, False);
           end;
      'G': begin
             if NeedToAddHeader
             then begin
               win[ax]^.wFrame.AddHeader(' Move Gripper ', heTC);
               TPI := win[ax]^.wFrame.GetLastHeaderIndex;
             end;
             win[ax]^.wFrame.DisableHeader(TPI, False);
           end;
      else exit;
    end;   { Case Statement }
    if MouseInstalled then
      trailer     := ' Use Center Button to Exit '
    else
      trailer     := ' X to Exit ';
   if NeedToAddHeader
   then begin
     win[ax]^.wFrame.AddHeader(trailer, heBC);
     BottomIndex := win[ax]^.wFrame.GetLastHeaderIndex;  { Save for changing }
   end;

   win[ax]^.select;
   case upcase(axis) of
    'B': begin

           { Display the data }
           basemoit;
           win[ax]^.SaveContents;
           { Get their input }
           valid_sel := false;
           while not valid_sel do
           begin

             { Get the user's input.  Do not allow buffering of input. }
             keyflush;
             ord_char := integer(ReadKeyOrButton);
             case ord_char of

               { Left arrow }
       integer(MouseLft),
              left : begin
                       one_move := true;
                       str(robo_steps.base,temp_str);
                       cmd_str := 'M' + temp_str + ',0,0,0,0,0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       HiddenCursor;
                       HideMouse;
                       win[ax]^.Select;

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
          integer(MouseRt),
             right : begin
                       one_move := true;
                       str(robo_steps.base,temp_str);
                       cmd_str := 'M-' + temp_str + ',0,0,0,0,0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       HiddenCursor;
                       HideMouse;
                       win[ax]^.Select;

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
 integer(MouseBoth),
             4946,
             4978 : begin
                      win[ax]^.select;
                      win[ax]^.wFrame.DisableHeader(BottomIndex,TRUE);
                      win[ax]^.wFrame.UpdateFrame;
                      clrscr;
                      gotoxy(4,2);
                      writeln('Current increment setting = ',robo_steps.base:2);

                      valid_inc := false;
                      while not valid_inc do
                      begin

                        { Get a new range }
                        NormalCursor;
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
                          HiddenCursor;
                          HideMouse;
                        end
                        else begin
                          gotoxy(7,7);
                          write('Enter a value in range please');
                        end;
                      end;   { While statement }
                      win[ax]^.wFrame.DisableHeader(BottomIndex,FALSE);
                      win[ax]^.wFrame.UpdateFrame;
                    end;
 integer(MouseCtr),
             11608,       { Exit...'X' }
             11640 : valid_sel := true;
                     else valid_sel := false;

             end;  { Case statement }

             updtabsr(abs_pos);
             updtrelr(rel_pos);
             HiddenCursor;

             win[ax]^.Select;

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
             ord_char := integer(ReadKeyOrButton);
             case ord_char of

               { upward  }
    integer(MouseLft),
               up  : begin
                       one_move := true;
                       str(robo_steps.shoulder,temp_str);
                       cmd_str := 'M0,' + temp_str + ',0,0,0,0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       HiddenCursor;
                       HideMouse;
                       win[ax]^.Select;

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
            integer(MouseRt),
               down :begin
                       one_move := true;
                       str(robo_steps.shoulder,temp_str);
                       cmd_str := 'M0,-' + temp_str + ',0,0,0,0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       HiddenCursor;
                       HideMouse;
                       win[ax]^.Select;

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
 integer(MouseBoth),
               4978,
               4946 : begin
                      win[ax]^.select;
                      win[ax]^.wFrame.DisableHeader(BottomIndex,TRUE);
                      win[ax]^.wFrame.UpdateFrame;
                      clrscr;
                      gotoxy(4,2);
                      writeln('Current increment setting = ',robo_steps.shoulder:2);

                      valid_inc := false;
                      while not valid_inc do
                      begin

                        { Get a new range }
                        NormalCursor;
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
                          HiddenCursor;
                          HideMouse;
                        end
                        else begin
                          gotoxy(7,7);
                          write('Enter a value in range please');
                        end;
                      end;   { While statement }
                      win[ax]^.wFrame.DisableHeader(BottomIndex,FALSE);
                      win[ax]^.wFrame.UpdateFrame;
                    end;

       integer(MouseCtr),             { Exit...'X' }
               11608,
               11640 : valid_sel := true;

               else valid_sel := false;

             end;  { Case statement }

             updtabsr(abs_pos);
             updtrelr(rel_pos);
             HiddenCursor;
             HideMouse;
             win[ax]^.Select;

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
             ord_char := integer(ReadKeyOrButton);
             case ord_char of
               { upward  }
      integer(MouseLft),
               up  : begin
                       one_move := true;
                       str(robo_steps.elbow,temp_str);
                       cmd_str := 'M0,0,' + temp_str + ',0,0,0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       HiddenCursor;
                       HideMouse;
                       win[ax]^.Select;

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
        integer(MouseRt),
               down :begin
                       one_move := true;
                       str(robo_steps.elbow,temp_str);
                       cmd_str := 'M0,0,-' + temp_str + ',0,0,0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       HiddenCursor;
                       HideMouse;
                       win[ax]^.Select;

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
 integer(MouseBoth),
               4946,
               4978 : begin
                      win[ax]^.select;
                      win[ax]^.wFrame.DisableHeader(BottomIndex,TRUE);
                      win[ax]^.wFrame.UpdateFrame;
                      clrscr;
                      gotoxy(4,2);
                      writeln('Current increment setting = ',robo_steps.elbow:2);

                      valid_inc := false;
                      while not valid_inc do
                      begin

                        { Get a new range }
                        NormalCursor;
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
                          HiddenCursor;
                          HideMouse;
                        end
                        else begin
                          gotoxy(7,7);
                          write('Enter a value in range please');
                        end;
                      end;   { While statement }
                      win[ax]^.wFrame.DisableHeader(BottomIndex,FALSE);
                      win[ax]^.wFrame.UpdateFrame;
                    end;

          integer(MouseCtr),          { Exit...'X' }
               11604,
               11640 : valid_sel := true;

               else valid_sel := false;

             end;  { Case statement }

             updtabsr(abs_pos);
             updtrelr(rel_pos);
             HiddenCursor;
             HideMouse;
             win[ax]^.Select;

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
             ord_char := integer(ReadKeyOrButton);
             case ord_char of

               { ccw  }
       integer(MouseLft),
               left: begin
                       one_move := true;
                       str(robo_steps.wrist_r,temp_str);
                       cmd_str := 'M0,0,0,' + temp_str + ',' + temp_str + ',0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       HiddenCursor;
                       HideMouse;
                       win[ax]^.Select;

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
        integer(MouseRt),
               right:begin
                       one_move := true;
                       str(robo_steps.wrist_r,temp_str);
                       cmd_str := 'M0,0,0,-' + temp_str + ',-' + temp_Str + ',0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       HiddenCursor;
                       HideMouse;
                       win[ax]^.Select;

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
 integer(MouseBoth),
               4946,
               4978 : begin
                      win[ax]^.select;
                      win[ax]^.wFrame.DisableHeader(BottomIndex,TRUE);
                      win[ax]^.wFrame.UpdateFrame;
                      clrscr;
                      gotoxy(4,2);
                      writeln('Current increment setting = ',robo_steps.wrist_r:2);

                      valid_inc := false;
                      while not valid_inc do
                      begin

                        { Get a new range }
                        NormalCursor;
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
                          HiddenCursor;
                        end
                        else begin
                          gotoxy(7,7);
                          write('Enter a value in range please');
                        end;
                      end;   { While statement }
                      win[ax]^.wFrame.DisableHeader(BottomIndex,FALSE);
                      win[ax]^.wFrame.UpdateFrame;
                    end;

         integer(MouseCtr),
               11608,     { Exit...'X' }
               11640 : valid_sel := true;

               else valid_sel := false;

             end;  { Case statement }

             updtabsr(abs_pos);
             updtrelr(rel_pos);
             HiddenCursor;
             HideMouse;
             win[ax]^.Select;

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
             ord_char := integer(ReadKeyOrButton);
             case ord_char of

               { upward  }
      integer(MouseLft),
               up  : begin
                       one_move := true;
                       str(robo_steps.wrist_p,temp_str);
                       cmd_str := 'M0,0,0,-' + temp_str + ',' + temp_str + ',0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       HiddenCursor;
                       HideMouse;
                       win[ax]^.Select;

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
      integer(MouseRt),
               down :begin
                       one_move := true;
                       str(robo_steps.wrist_p,temp_str);
                       cmd_str := 'M0,0,0,' + temp_str + ',-' + temp_Str + ',0';

                       { Display command in command window }
                       updtcomr(cmd_str);
                       HiddenCursor;
                       HideMouse;
                       win[ax]^.Select;

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
 integer(MouseBoth),
               4946,
               4978 : begin
                      win[ax]^.select;
                      win[ax]^.wFrame.DisableHeader(BottomIndex,TRUE);
                      win[ax]^.wFrame.UpdateFrame;
                      clrscr;
                      gotoxy(4,2);
                      writeln('Current increment setting = ',robo_steps.wrist_p:2);

                      valid_inc := false;
                      while not valid_inc do
                      begin

                        { Get a new range }
                        NormalCursor;
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
                          HiddenCursor;
                          HideMouse;
                        end
                        else begin
                          gotoxy(7,7);
                          write('Enter a value in range please');
                        end;
                      end;   { While statement }
                      win[ax]^.wFrame.DisableHeader(BottomIndex,FALSE);
                      win[ax]^.wFrame.UpdateFrame;
                    end;

         integer(MouseCtr),
               11608,     { Exit...'X' }
               11640 : valid_sel := true;

               else valid_sel := false;

             end;  { Case statement }

             updtabsr(abs_pos);
             updtrelr(rel_pos);
             HiddenCursor;
             HideMouse;
             win[ax]^.Select;

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
             ord_char := integer(ReadKeyOrButton);

             case ord_char of

               { left  }
         integer(MouseLft),
              left : begin
                       one_move := true;
                       str(robo_steps.gripper,temp_str);
                       cmd_str := 'M0,0,0,0,0,-' + temp_str;

                       { Display command in command window }
                       updtcomr(cmd_str);
                       HiddenCursor;
                       HideMouse;
                       win[ax]^.Select;

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
       integer(MouseRt),
             right : begin
                       one_move := true;
                       str(robo_steps.gripper,temp_str);
                       cmd_str := 'M0,0,0,0,0,' + temp_str;

                       { Display command in command window }
                       updtcomr(cmd_str);
                       HiddenCursor;
                       HideMouse;
                       win[ax]^.Select;

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
 integer(MouseBoth),
               4946,
               4978 : begin
                      win[ax]^.select;
                      win[ax]^.wFrame.DisableHeader(BottomIndex,TRUE);
                      win[ax]^.wFrame.UpdateFrame;
                      clrscr;
                      gotoxy(4,2);
                      writeln('Current increment setting = ',robo_steps.gripper:2);

                      valid_inc := false;
                      while not valid_inc do
                      begin

                        { Get a new range }
                        NormalCursor;
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
                          HiddenCursor;
                          HideMouse;
                        end
                        else begin
                          gotoxy(7,7);
                          write('Enter a value in range please');
                        end;
                      end;   { While statement }
                      win[ax]^.wFrame.DisableHeader(BottomIndex,FALSE);
                      win[ax]^.wFrame.UpdateFrame;
                    end;

         integer(MouseCtr),           { Exit...'X' }
               11608,
               11640 : valid_sel := true;

               else valid_sel := false;

             end;  { Case statement }

             updtabsr(abs_pos);
             updtrelr(rel_pos);
             HiddenCursor;
             HideMouse;
             win[ax]^.Select;

           end;   { While statement }
       end;


   end;  { Case Statement }

  { Restore the robot move window if a move occured }
  win[ax]^.select;
  win[ax]^.erase;
  win[ax]^.wFrame.DisableHeader(TPI,True);

  if one_move
  then updtcomr(cmd_str);

  { Update the absolute screen again }
  updtabsr(abs_pos);
  updtrelr(rel_pos);
end;