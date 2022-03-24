procedure delprog;

{ This procedure deletes a file from the disk }

var
  any_char      : word;
  filename      : string;
  file1         : pk_file;
  title,
  trailer       : string;
  wnum          : word;

begin
  if everlock.check_copy_protection <> passed_protection_check
  then security_msg;

  HiddenCursor;

  title := ' Select a program to delete ';
  if MouseInstalled then
    trailer := ' LEFT to pick or RIGHT to EXIT '
  else trailer := ' ESC to EXIT ';
  FileName := FilePick(title, Trailer);
  if FileName = '' then
  exit;
  clrscr;
  { Attept to open the file }
  assign(file1,filename);
  clrscr;
  if not pkopen(file1,false)
  then begin
    win[1]^.Select;
    writeln;
    writeln;
    writeln('                      Unable to Open File ');
    writeln;
    writeln;
    writeln('                    Press any key to continue');
    writeln;
    writeln;
    any_char := ReadKeyOrButton;
    win[1]^.ClearContents;

  end;
  if delcon(filename) = 'N'
     then exit;

  { Delete the file }
  {$I-} erase(file1); {$I+}

  if ioresult <> 0
  then begin
    win[1]^.Select;
    writeln;
    writeln;
    writeln('                       Unable to delete file ');
    writeln;
    writeln;
    writeln('                     Press any key to continue');
    writeln;
    writeln;
    any_char := ReadKeyOrButton;
    close(file1);
    win[1]^.ClearContents;
  end
  else exit;

  { Return }

end;
