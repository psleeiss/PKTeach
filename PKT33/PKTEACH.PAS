{$F+}
program pkteach;

{ Larger stack size }
{$M 42768,30000,655360}

uses
  graph,
  Drivers,
  Fonts,
  OpDos,
  OpCrt,
  OpExtMem,
  OpMouse,
  OpString,
  wins,
  misc,
  robot,
  robot2,
  everobj,
  pktmain;

  var
    response      : word;
    NewP          : string;
    exitsave      : pointer;
    test          : word;
    status        : integer;
    M             : HugePtr;

{ Exit procedure for the TEACH program.  Note that EXITSAVE is a gobal pointer }
{$F+}
procedure teacherr;     {$F-}

var
  any_char : word;

begin

  exitproc := exitsave;

  { If the copy protection result was bad, do not display any message (this
    would have been done by secure_msg).  }
  if everlock.get_last_result <> 0
  then exit;

  { See if an error occurred.  If so, prevent the Pascal error message }
  if exitcode = 0
  then exit;

  delay(5000);

  win[1]^.Select;

  clrscr;
  keyflush;
  HiddenCursor;
  HideMouse;
  gotoxy(1,5);
  writeln('              An unexpected error has occured.  Please do the following: ');
  writeln;
  writeln;
  writeln('                 1) Press the RESET button ON THE ROBOT.');
  writeln;
  writeln;
  writeln('                 2) Inform your instructor that you got error # ',exitcode,'.');
  writeln('                    at program address: ',hexptr(erroraddr));
  writeln;
  writeln;
  if mouseinstalled then
  writeln('                 3) Press any mouse button to exit the PK-TEACH program.')
  else
  writeln('                 3) Press any key to exit the PK-TEACH program.');
  any_char := ReadKeyOrButton;
  NormalCursor;
  win[1]^.Erase;
  win[1]^.Done;
  erroraddr := nil;
  clrscr;
end;

procedure Abort(Msg : string);
begin
  Writeln(Msg, ': ', GraphErrorMsg(GraphResult));
  Halt(1);
end;

begin

  clrscr;

  { Set EVERLOCK disk type and calling parameters }
  everlock.init(unprotected_program,'PKTEACH.EXE');

  { Set up new exit handler }
  exitsave := exitproc;
  exitproc := @teacherr;

  { If everlock protected, then do a security check }
  if everlock.check_copy_protection <> passed_protection_check
  then security_msg;

  InitWins;
  { Set the version }
  pk_version := 'Version 3.3';

  { Display title screen }
  title;

  { Call the Main procedure }
  pktmenu;

end.
