procedure lsttest;

var
  run_ptr      : pk_ptr;
  d_ptr        : pk_Ptr;

begin
  window(1,1,80,25);
  clrscr;
  writeln('                        List Test ');
  run_ptr := top_ptr;
  while run_ptr <> nil
  do begin
    writeln('Running down the list...com= ',run_ptr^.cmd_str);
    d_ptr := run_ptr;
    run_ptr := run_ptr^.next_ptr;
  end;
  writeln;
  while d_ptr <> nil
  do begin
    writeln('Running up the list...com= ',d_ptr^.cmd_str);
    d_ptr := d_ptr^.prev_ptr;
  end;
  writeln(readkey);

end;