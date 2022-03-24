procedure revmove;

var
  win      : WindowPtr;
  Status   : Word;
  M        : Menu;      {menu system}
  {Filename : string;}
  finished : boolean;
  any_char : char;
begin
  filename := 'test';
  ClrScr;
  Status := InitSTATUS;
    if Status <> 0 then begin
    WriteLn('Error initializing menu: ', Status);
    Halt(1);
  end;

  {$IFDEF UseMouse}
  if MouseInstalled then
    with MenuColors do begin
      {activate mouse cursor}
      SoftMouseCursor($0000, (ColorMono(MouseColor, MouseMono) shl 8)+
                             Byte(MouseChar));
      ShowMouse;
      {enable mouse support}
      MenuCommands.cpOptionsOn(cpEnableMouse);
    end;
  {$ENDIF}
  repeat
  if not M.IsCurrent then
  M.Draw;
  M.Process;
  {Skeleton for menu choice handling}

  if M.GetLastCommand = ccSelect then
    case M.MenuChoice of
      miClose1        : if gripclos
                        then begin
                        if not proccom('C', limit_err)
                        then begin
                        writeln('Could not process the command!!!');
                        halt(1);
                        end;
                        updtabsr(abs_pos);
                        updtrelr(rel_pos);
                        updtcomr('C');
                        roboinit(rel_pos);
                        roboinit(com_pos);
                        fileit('C');
                        if robot_mode = edit_prog
                        then need_save := true;
                        end;
      miOpen2         : if gripopen
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
                        fileit('O');
                        if robot_mode = edit_prog
                        then need_save := true;
           end;
      miDelay3        : if tdelay(command)
                        then begin
                        if not proccom(command,limit_err)
                        then begin
                        writeln('Could not process the command!!!');
                        halt(1);
                        end;
                        updtcomr(command);
                        fileit(command);
                        if robot_mode = edit_prog
                        then need_save := true;
                        end;
      miFastSlow4     : if speed(command)
                        then begin
                        if not proccom(command,limit_err)
                        then begin
                        writeln('Could not process the command!!!');
                        halt(1);
                        end;
                        updtcomr(command);
                        fileit(command);
                        if robot_mode = edit_prog
                        then need_save := true;
                        end;
      miNest5         : if nest
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
                        fileit('N')
                        if robot_mode = edit_prog
                        then need_save := true;
                        end;
      miMovement6     : rvbwrite;
      miRemove7       : if robot_mode = edit_prog
                        then begin

                          if cur_ptr = nil
                          then delnocom
                          else begin
                            if remcon = 'Y'
                            then begin

                              { Delete the command }
                              lstdel;
                              if robot_mode = edit_prog
                              then need_save := true;
                              if cur_ptr <> nil
                              then begin

                                { Find the needed robot command }
                                command := revert(cur_ptr);

                                if not proccom(command,limit_err)
                                then begin
                                  if limit_err <> ' '
                                  then rangeout(limit_err)
                                  else invalcom;
                                end
                              end;

                              { Update and all that jazz }
                              roboinit(com_pos);
                              roboinit(rel_pos);
                              updtabsr(abs_pos);
                              updtrelr(rel_pos);
                              updtcomr(command);
                              writeln (' This is the end of -R- COmmand ');
                            end;
                          end;
                        end;
      miUpwardPrev9,
      miLoad8         : if robot_mode = edit_prog
                        then begin

                          { See if this is a load next or load previous }
                          load_command_error := false;
                          if any_char = 'L'
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
                            if any_char = 'U'
                            then command := revert(cur_ptr);

                            { Display the command in the command window }
                            if any_char = 'L'
                            then updtcomr(command)
                            else updtcomr(command);

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
                                     cursroff;
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
                                      end;

                                  else begin
                                    New(win, initcustom(2,2,79,24, MenuColors, WinOpts));
                                    win^.setcursor(cuhidden);
                                    win^.Draw;
                                    writeln('Bad news from REVISE.INC.  No valid command');
                                    finished := true;
                                  end;
                              end;  { Case statement }
                            end;  { Else clause from proccom }
                          end;   { Then clause (not load_command_error) }
                          fastwrite(' readkey in  the end of miLoad in REVMOVE ', 24, 1, yellow);
                          any_char := readkey;
                          dispose(win,done);
                        end;   { Case statement portion }

      miexit10        : if verfexit = 'Y'
                        then finished := true
                        else finished := false;
                    (*    if robot_mode = write_new
                        then begin
                          if writexit = 'Y'
                          then finished := true;
                        end
                        else if revexit = 'Y'
                             then finished := true
                             else finished := false;  *)
  end;
  until finished;
  M.select;
  M.Erase;
  M.Done;

  {$IFDEF UseMouse}
  HideMouse;
  {$ENDIF}
end;