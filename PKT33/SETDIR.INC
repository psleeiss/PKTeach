procedure setdir( var cur_directory : str66);

{ This procedure sets a new dos directory path given the old one }

const
  current_drive = 0;

var
  new_path    : str66;

begin
  writeln;
  write('Enter new Directory Path (blank to abort): ');
  readln(new_path);

  { Check for abort }
  if blnkstr(new_path) then exit;

  { Attempt to set the new path }
  {$I-}    { Disable I/O Checking }
  chdir(new_path);
  {$I+}    { Enable I/O Checking }

  if ioresult <> 0
  then begin
    writeln;
    writeln('Could not find directory: ',new_path);
  end
  else getdir(current_drive,cur_directory);

end;