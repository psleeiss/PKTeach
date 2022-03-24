procedure Pendent;

var
  PenWin   : WindowPtr;
  axis     : word;
  finished : boolean;
  menu_com : integer;
  WinOpts  : LongInt;

  begin
    WinOpts := wBordered+wClear;
    New(PenWin, InitCustom(3, 13, 25, 23, MenuColors, wBordered+wClear));
    if PenWin = nil then
    begin
      writeln(' Failed to initialize PenWin ');
      Halt;
    end;
    PenWin^.setcursor(cuhidden);
    PenWin^.wFrame.AddHeader(' Pendent control panel ', heTC);
    PenWin^.wFrame.AddHeader(' RIGHT button to exit ', heBC);
    updtabsr(abs_pos);
    rangeup;
    updtrelr(rel_pos);
    updtcomr(' ');
    finished := false;
    repeat
      HideMouse;
      HiddenCursor;
      PenWin^.Draw;
      gotoxy(3,3);
      Writeln('Base     - Lft');
      gotoxy(3,4);
      Writeln('Shoulder - Ctr');
      gotoxy(3,5);
      Writeln('Elbow    - LftRt');
      gotoxy(3,6);
      Writeln('Roll     - LftCtr');
      gotoxy(3,7);
      Writeln('Pitch    - CtrRt');
      gotoxy(3,8);
      Writeln('Gripper  - LftCtrRt');
      gotoxy(3,10);
      Writeln('Double click Center');
      gotoxy(3,11);
      Writeln('  for next window.');
      axis := ReadKeyOrButton;
      PenWin^.Erase;
      menu_com := integer(axis);
      case menu_com of

         integer(MouseLft)    : writeit('B');

         integer(MouseCtr)    : begin
                                  if dblclick(axis) = true then
                                  pendent2
                                  else writeit('S');
                                end;

         integer(MouseBoth)   : writeit('E');

         integer(MouseLftCtr) : writeit('R');

         integer(MouseRtCtr)  : writeit('P');

         integer(MouseThree)  : writeit('G');


         integer(MouseRt)     : begin
                               (*   finished := true; *)
                                  if verfexit = 'Y'
                                  then finished := true
                                  else finished := false;
                               (*   if robot_mode = write_new
                                  then begin
                                    if writexit = 'Y'
                                    then finished := true
                                    else finished := false;
                                  end
                                  else if revexit = 'Y'
                                       then finished := true
                                       else finished := false; *)

                                  { Execute only if we are exiting }
                                  if finished
                                  then begin
                                    if robot_mode <> move_only
                                    then begin
                                           if (rel_pos.base <> 0) or
                                           (rel_pos.shoulder <> 0) or
                                           (rel_pos.elbow <> 0) or
                                           (rel_pos.wrist_r <> 0) or
                                           (rel_pos.wrist_p <> 0) or
                                           (rel_pos.gripper <> 0)
                                    then if savechk
                                    then raddpt
                                    else if cur_ptr = nil   { If cur_ptr is NIL, then no points saved yet }
                                    then robowrit('N')
                                    else begin
                                           command := revert(cur_ptr);
                                           if not proccom(command,limit_err)
                                           then begin
                                                  whistle;
                                                  writeln('Fatal Error from RVBWRITE!');
                                                  delay(1000);
                                                  halt(1);
                                                end;
                                         end;
                                         end;
                                  end;
                            end;

         else begin
           (*   fastwrite(' There is trouble in the case statement ', 1, 24, white);
                exit;  *)
              end;
      end;



  until (finished = true);

  PenWin^.select;
  dispose(PenWin,done);
end;





