function delfile ( filename : string ) : boolean;

{ This function deletes the given file from the disk.  If all goes well, the }
{ function returns true.  Otherwise, it will return false.                 }

var
  the_file       : file;

begin

  { Attempt to open the file }
  assign(the_file,filename);
  {$I-}
  erase(the_file);

  if ioresult <> 0
  then delfile := false
  else delfile := true;

end;
