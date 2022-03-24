procedure Pendent2;

var
  PenWin2  : WindowPtr;
  axis     : word;
  finished : boolean;
  com      : integer;

  begin
    New(Penwin2, InitCustom(3, 14, 25, 23, MenuColors, wBordered+wClear));
    if PenWin2 = nil then
    begin
      writeln(' Failed to initialize PenWin2 ');
      Halt;
    end;
    PenWin2^.setcursor(cuhidden);
    PenWin2^.wFrame.AddHeader(' Pendent control panel ', heTC);
    PenWin2^.wFrame.AddHeader(' Dbl Click Ctr to exit ', heBC);

    {updtabsr(abs_pos);
    rangeup;
    updtrelr(rel_pos);
    updtcomr(' ');}
    finished := false;
    repeat
      HiddenCursor;
      HideMouse;
      PenWin2^.Draw;
        if robot_mode <> Move_only then
        begin
        gotoxy(2,2);
        Writeln('Add Point  - Lft');
        gotoxy(2,3);
        Writeln('Nest       - Rt');
        if Robot_Mode = Edit_Prog then
        begin
          gotoxy(2,5);
          Writeln('Next Point - LftRt');
          gotoxy(2,6);
          Writeln('Prev Point - LftCtr');
          gotoxy(2,7);
          Writeln('Delete Pt  - CtrRt');
        end;
      end;

      gotoxy(2,4);
      writeln('Gripper    - Ctr');
      gotoxy(2,8);
      Writeln('Delay      - F3');
      gotoxy(2,9);
      Writeln('Speed      - F4');

      if robot_mode = move_only then
      begin
        gotoxy(2,3);
        Writeln('Zero       - LftCtrRt');
      end;
      axis := ReadKeyOrButton;
      PenWin2^.Erase;
      com := integer(axis);
      case com of

       integer(MouseLft) : if robot_mode <> move_only
                                  then begin
                                         raddpt;
                                         if robot_mode = edit_prog
                                         then need_save := true;
                                         updtrelr(rel_pos);
                                       end;
       integer(MouseCtr) : if dblclick(axis) = true
                           then begin
                                  finished := true;
                                end
                           else pendent3;
       Integer(MouseRt):   begin
                             if not proccom('N',limit_err)
                             then begin
                                    writeln('Could not process the command!!!');
                                    halt(1);
                                  end;
                                  updtabsr(abs_pos);
                                  updtrelr(rel_pos);
                                  roboinit(rel_pos);
                                  updtcomr('N');
                                  fileit('N');
                                  if robot_mode = edit_prog
                                  then need_save := true;
                           end;
      integer(MouseBoth),
      integer(MouseLftCtr): if robot_mode = edit_prog
                            then begin

                              { See if this is a load next or load previous }
                              load_command_error := false;
                              if axis = MouseBoth
                              then begin
                                if not lstnext
                                then begin
                                  eofcom;
                                  load_command_error := true;
                                end;
                              end
                              else begin
                                if not lstprev
                                then begin
                                  tofcom;
                                  load_command_error := true;
                                end;
                              end;

                              if not load_command_error
                              then begin
                                { Process the command }
                                if not pktostr(cur_ptr,command)
                                then begin
                                  invalcom;
                                  exit;
                                end;

                                { If we are "backing up", force to go to last position }
                                if axis = MouseLftCtr
                                then command := revert(cur_ptr);

                                { Display the command in the command window }
                                updtcomr(command);

                                { Process the command }
                                if not proccom(command,limit_err)
                                then begin
                                  if limit_err <> ' '
                                  then rangeout(limit_err)
                                  else begin
                                    invalcom;
                                    error_occured := true;
                                    finished := true;
                                  end;
                                end
                                else begin
                                  case command[1] of
                                    'C': begin
                                           updtabsr(abs_pos);
                                           updtrelr(rel_pos);
                                           roboinit(rel_pos);
                                           roboinit(com_pos);
                                         end;
                                    'D': begin end;
                                    'M': begin
                                           updtabsr(abs_pos);
                                           updtrelr(rel_pos);
                                           roboinit(com_pos);
                                           roboinit(rel_pos);
                                           HiddenCursor;
                                         end;
                                    'N': begin
                                           updtabsr(abs_pos);
                                           updtrelr(rel_pos);
                                           roboinit(rel_pos);
                                         end;
                                    'O': begin
                                           updtabsr(abs_pos);
                                           updtrelr(rel_pos);
                                           roboinit(rel_pos);
                                           roboinit(com_pos);
                                         end;
                                    'S': begin end;
                                    'Z': begin
                                           updtabsr(abs_pos);
                                           updtrelr(rel_pos);
                                         end
                                         else begin
                                                writeln('Bad news from REVISE.INC.  No valid command');
                                                finished := true;
                                              end;
                                  end;  { Case statement }
                                end;  { Else clause from proccom }
                              end;   { Then clause (not load_command_error) }
                            end;   { Case statement portion }

    integer(MouseRtCtr) : if robot_mode = edit_prog
                           then begin
                                  if cur_ptr = nil
                                  then delnocom
                                  else begin
                                         if remcon = 'Y'
                                         then begin
                                         { Delete the command }
                                                lstdel;
                                                need_save := true;
                                                if cur_ptr <> nil
                                                then begin
                                                       { Find the needed robot command }
                                                       command := revert(cur_ptr);
                                                       if not proccom(command,limit_err)
                                                       then begin
                                                              if limit_err <> ' '
                                                              then rangeout(limit_err)
                                                              else invalcom;
                                                            end;
                                                      end;
                                                { Update and all that jazz }
                                                roboinit(com_pos);
                                                roboinit(rel_pos);
                                                updtabsr(abs_pos);
                                                updtrelr(rel_pos);
                                                updtcomr(command);
                                              end;
                                       end;
                                end;
         $3E00                :  if speed(command) then
                                 begin
                                   if not proccom(command,limit_err) then
                                   begin
                                     writeln('Could not process the command!!!');
                                     halt(1);
                                   end;
                                   updtcomr(command);
                                   fileit(command);
                                   if robot_mode = edit_prog
                                   then need_save := true;
                                 end;
         $3D00                :  if tdelay(command) then
                                 begin
                                   if not proccom(command,limit_err) then
                                   begin
                                     writeln('Could not process the command!!!');
                                     halt(1);
                                   end;
                                   updtcomr(command);
                                   fileit(command);
                                   if robot_mode = edit_prog
                                   then need_save := true;
                                 end;

         integer(MouseThree)  : if robot_mode = move_only
                                  then if zverify
                                    then begin
                                           robowrit('Z');
                                           roboinit(abs_pos);
                                           roboinit(rel_pos);
                                           roboinit(com_pos);
                                           updtabsr(abs_pos);
                                           updtrelr(rel_pos);
                                         end;

      end;

    until (finished = true);

    PenWin2^.Erase;
    dispose(penwin2,done);

    {$IFDEF USEMOUSE}
    HideMouse;
    {$ENDIF};
  end;
