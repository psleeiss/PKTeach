function strfext( filename : string) : string;

{ This function receives a filename and strips off the extension if one exists }

var
  dot_pos    : byte;

begin

  { Attempt to locate the "dot" in the filename }
  blnkchop(filename);
  dot_pos := pos('.',filename);

  { If no extension, then return the same value as was passed in }
  if dot_pos < 2
  then begin
         strfext := filename;
         exit;
       end;

  strfext := copy(filename,1,dot_pos-1);

end;
