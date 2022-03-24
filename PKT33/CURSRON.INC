procedure cursron;

var
  myregs : registers;
  display_mode : byte;

begin

  { Cursor size depends on video mode so get current video mode via BIOS }
  myregs.ah := 15;
  intr($10,myregs);

  if myregs.al <= 3 { If a CGA adapter mode being used }
  then begin
    myregs.ch := 6;       { Default for CGA }
    myregs.cl := 7;       { Default for CGA }
  end
  else begin
    myregs.ch := 11;      { Hercules/EGA default }
    myregs.cl := 12;      { Hercules/EGA default }
  end;

  { Reset cursor }
  myregs.ah := 1;
  intr($10,myregs);

end;