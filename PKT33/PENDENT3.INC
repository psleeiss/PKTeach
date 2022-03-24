procedure Pendent3;

var
  penwin3  : WindowPtr;
  axis     : word;
  finished : boolean;
  com_in   : integer;

  begin
    New(penwin3, InitCustom(13, 17, 35, 20, Axcolor, wBordered+wClear));
    if penwin3 = nil then
    begin
      writeln(' Failed to initialize penwin3 ');
      Halt;
    end;
    penwin3^.setcursor(cuhidden);
    penwin3^.wFrame.AddHeader(' Gripper control panel ', heTC);
    penwin3^.wFrame.AddHeader(' Press Right to exit ', heBC);

    finished := false;
    repeat
      HiddenCursor;
      HideMouse;
      penwin3^.Draw;

      gotoxy(4,2);
      writeln('Open       - Lft');
      gotoxy(4,3);
      writeln('Close      - Ctr');

      axis := ReadKeyOrButton;
      penwin3^.Erase;
      com_in := integer(axis);
      case com_in of

       integer(MouseLft) : if gripopen
                           then begin
                             if not proccom('O',limit_err)
                             then begin
                               writeln('Could not process the command!');
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
                             finished := true;
                           end;
       integer(MouseCtr) : if gripclos
                           then begin
                             if not proccom('C',limit_err)
                             then begin
                               writeln('Could not process the command!!!');
                               halt(1);
                             end;
                             updtrelr(rel_pos);
                             roboinit(rel_pos);
                             roboinit(com_pos);
                             updtcomr('C');
                             fileit('C');
                             if robot_mode = edit_prog
                             then need_save := true;
                             finished := true;
                           end;
       integer(MouseRt)  : finished := true;

      end; { Case statement }

    until (finished = true);

    penwin3^.Erase;
    dispose(penwin3,done);

    {$IFDEF USEMOUSE}
    HideMouse;
    {$ENDIF};
  end;





