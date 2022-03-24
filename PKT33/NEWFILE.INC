function newfile(var afile    : pk_file;
                     filename : string) : boolean;

{ This function creates a new file for the user to write commands into. }
{ If it cannot create the file, then it returns a value of false.       }
var
  found    : boolean;
  any_char : char;

begin
  { Check for valid filename }
  if (length(filename) > 12 )   or
     wildcard(filename)
  then begin
         if blnkstr(filename) then
           begin
             newfile := false;
             exit;
           end;
         invalfil;
         newfile := false;
         exit;
       end;

  { Try to open the file to see if we have a duplicate filename }
  found := ExistFile(filename);
  if found = true
    then begin
           dupfname;
           newfile := false;
           exit;
         end;

  { Try to create the file }
  assign(afile,filename);
  if not pkopen(afile,true)
    then begin
           {invalfil;}
           newfile := false;
           exit;
         end;

  newfile := true;

end;

