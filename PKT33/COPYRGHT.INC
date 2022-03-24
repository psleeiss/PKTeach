procedure copyrght;

{ Display the title screen }

begin
  HiddenCursor;

  win[1]^.ChangeHeader(0,' Notice ');
  win[1]^.ChangeHeader(1,'');
  win[1]^.Draw;
  win[1]^.ClearContents;
(*  { Check for copyright notice }
  if distribution_disk_type = working_copy
  then begin
  writeln;
  writeln;
  writeln;
  writeln;
  writeln('        This software is protected by United States Copyright Law.  It is');
  writeln('        against the law to copy this software onto cassette, tape, disk or');
  writeln('        any other medium for any purpose other than for back-up or archival');
  writeln('        purposes.  You may not distribute, modify, or disassemble this');
  writeln('        software without the expressed written consent of Peter S. Lee. ');
  writeln('        If you have any questions or');
  writeln('        problems concerning these restrictions, please feel free to contact');
  writeln('        Peter S. Lee directly.');
  end;
*)
  writeln;
  writeln;
  writeln;
  writeln('                  Copyright (C) 2022 by Peter S. Lee');
  writeln('                              All Rights Reserved');

  HiddenCursor;
  delay(4000);
  win[1]^.Erase;
  NormalCursor;

end;



