procedure exeprog;

{ This procedure runs a program }


var
  W             : WindowPtr;
  any_char      : word;
  Dir           : DirList;
  path          : PathStr;
  filename      : pathstr;
  robot         : robot_pos;
  command       : string;
  limit_err     : char;
  good_name     : boolean;
  data_win      : byte;
  file1         : pk_file;
  Status        : Word;
  title, trailer: string;
  I             : integer;

begin

  { Check copy protection }
  if everlock.check_copy_protection <> passed_protection_check
  then security_msg;

  limit_err := ' ';

  { Nest the robot and verify that it is in the "zero" position }
  robowrit('N');
  roboinit(abs_pos);
  roboinit(rel_pos);
  roboinit(com_pos);
  if not zquest
  then exit;
  win[1]^.Select;
  win[1]^.ClearContents;
  HiddenCursor;
  title :=  ' Select A Program to run ';
  if mouseinstalled then
  trailer := ' LEFT to pick or RIGHT to exit '
  else
  trailer := ' Use '#24', '#25', <Enter>, or ESC (to exit) ';
  FileName := FilePick(title, trailer);
  if filename = '' then
      exit;
  { Attempt to open the file }
  assign(file1,filename);
  if not pkopen(file1,false)
  then begin
    writeln('                        Unable to Open File ');
    writeln;
    writeln;
    writeln('                      Press any key to continue');
    any_char := ReadKeyOrButton;
    win[1]^.Erase;
    exit;
  end;
  { Load the file into memory and then close the file.  Let them load }
  { the file even if this is a demonstration disk. }
  fileld(file1);
  close(file1);

  { Read the file and execute }

  { Display the command windows }
  roboinit(robot);
  win[run]^.wFrame.AddHeader(' Running ' + strfext(filename) + ' ', heTC);
  updtabsr(abs_pos);
  rangeup;
  updtrelr(rel_pos);
  HiddenCursor;
  HideMouse;
  win[run]^.Select;
  win[run]^.ClearContents;

  { Read the commands and execute }
  while lstnext do
  begin

    { Translate the command }
    if not pktostr(cur_ptr,command)
    then invalcom
    else begin

      { Make it look pretty }
      writeln;
      writeln;
      writeln;
      writeln;
      writeln('                           ',command);
      delay(700);
      if not proccom(command,limit_err)
      then if limit_err <> ' '
           then rangeout(limit_err)
           else invalcom;

      updtabsr(abs_pos);
      rangeup;
      updtrelr(rel_pos);
      HiddenCursor;
      HideMouse;
      if command[1] in ['M','Z','C','N','G','O']
      then roboinit(rel_pos);
      win[run]^.Select;

    end;  { Else clause }

  end;  { While loop }

  { Exit and nest the robot for good measure }
  HiddenCursor;
  writeln;
  writeln('                      Press any key to return to Main Menu ');

  robowrit('N');
  roboinit(abs_pos);
  roboinit(rel_pos);
  roboinit(com_pos);
  updtabsr(abs_pos);
  updtrelr(rel_pos);
  HiddenCursor;
  HideMouse;
  any_char := ReadKeyOrButton;

  HiddenCursor;
  HideMouse;
  I := 5;
  {W := Win[I]; }
  repeat
    if W <> nil then
      W := wStack.UnStackTop;
      Dec(I);
  until (I = 1);
end;

