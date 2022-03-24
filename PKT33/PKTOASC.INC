procedure pktoasc;

{ This procedure handles the conversion of a pkteach file to ascii }

var
  win                : WindowPtr;
  WInOpts            : Longint;
  any_char           : word;
  count              : integer;
  filename           : string;
  ascii_name         : string;
  command            : string;
  file1              : pk_file;
  file2              : text;
  title, trailer     : string;


begin
  WinOpts := wBordered+wClear;

  { Check copy protection }
  if everlock.check_copy_protection <> passed_protection_check
  then security_msg;

  { Clear the memory-resident linked list of commands to store }
  lstclear;

  { Get the filename from the user }
  title := ' Select a Program to Translate ';
  trailer := ' Use '#24','#25',<ENTER> or ''<ESC>'' (to exit) ';
  filename := FilePick(title, trailer);

  { Check for no files found }
  if filename = '' then
  exit;

  { Open the file }
  assign(file1,filename);
  if not pkopen(file1,false)
  then begin
    invalfil;
    exit;
  end;

  { Load the file into memory }
  fileld(file1);

  { Draw the background screen }

  New(win, InitCustom(2, 2, 79, 24, MenuColors, wBordered+wClear));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Translate ', heTC);
  win^.Draw;

  { Set up ASCII filename and open the file }
  ascii_name := strfext(filename) + '.ASC';
  assign(file2,ascii_name);
  if not opentext(file2,true)
  then begin
    gotoxy(1,12);
    writeln('                   Could not open the ASCII file for output!!! ');
  end
  else begin

    { Make sure that the file is open for output }
    rewrite(file2);

    gotoxy(17,9);
    writeln('Translating ',strfext(filename),' into ASCII file ',
             ascii_name,'.');

    { Display the status }
    count := 1;
    while lstnext
    do begin

      { Update the display }
      gotoxy(22,15);
      write('          Line # ',count:5);

      { Write the file }
      writeln(file2,cur_ptr^.cmd_str);

      { Check for the need to add open and/or close commands }
      if (cur_ptr^.gripper = 0) and addclose
      then writeln(file2,'C');

      if (cur_ptr^.gripper = max_ranges.gripper) and addopen
      then writeln(file2,'O');

      { Advance the line count }
      count := count + 1;

    end;  { While loop }

  end;   { Else clause }

  { Finish up as niceley as possible }
  writeln;
  writeln;
  writeln;
  writeln;
  writeln;
  writeln('                ...Press any key to return to main menu...');
  any_char := ReadKeyOrButton;

{ Close the files }
{$I-}
close(file1);
close(file2);
{$I+}

(* win := wStack.UnStackTop;*)
dispose(win,done);

end;