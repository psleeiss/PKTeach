procedure rangeup;

{ This procedure displays the "Max Ranges" window }

 begin
   HiddenCursor;
   If MouseInstalled then
     HideMouse;

     begin
       win[range]^.wFrame.AddHeader(' Max Ranges ', heTC);
       win[range]^.Select;
       { Display the titles }
        gotoxy(4,2);
        write('B  - ', max_ranges.base:6);
        gotoxy(4,3);
        write('S  - ', max_ranges.shoulder:6);
        gotoxy(4,4);
        write('E  - ', max_ranges.elbow:6);
        gotoxy(4,5);
        write('WR - ', max_ranges.wrist_r:6);
        gotoxy(4,6);
        write('WP - ', max_ranges.wrist_p:6);
        gotoxy(4,7);
        write('G  - ', max_ranges.gripper:6);
      end;
 end;