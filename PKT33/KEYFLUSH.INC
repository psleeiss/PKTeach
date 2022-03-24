procedure keyflush;

{ This procedure is called to flush the keyboard buffer.  One would typically }
{ Use it just before a keyboard input routine where buffered input is not
{ practical or desired.                                   }

var
  any_char : char;

begin
  while keypressed do any_char := readkey;
end;
