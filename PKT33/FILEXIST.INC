function filexist( filename : string) : boolean;

{ This function checks to see if the given file name (which may include a }
{ pathname) exists or not.  If it exists, the function returns TRUE.      }


var
  file_rec   : searchrec;    { Declared in DOS unit }

begin

  findfirst(filename,anyfile,file_rec);

  if doserror <> 0
  then filexist := false
  else filexist := true;

end;

