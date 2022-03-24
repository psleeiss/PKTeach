procedure cursroff;

var
  myregs : registers;

begin
  myregs.ah := 1;
  myregs.ch := $20;     { Binary 00100000 }
  intr(16,myregs);

end;
