procedure printscr;

{ This procedure invokes the BIOS printscreen function }

var
  myregs : registers;

begin
  intr(5,myregs);
end;