procedure rvbwrite;

{ This procedure moves the robot and updates the relative and absolute positions }

var
  any_char       : char;
  time_to_quit   : boolean;
  command        : string;
  limit_err      : char;

begin
  fastvert(' You are is RVBWRITE ', 1, 79, yellow);

  { Check to see if the numlock is set }
  numlocch;

  { Get the response }
    rvbmenu;

end;