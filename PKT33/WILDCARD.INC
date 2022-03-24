function wildcard( filename : string) : boolean;

{ This function checks a filename to see if it contains wildcards '*' or '?' }
{ If wildcards are present in the name then the function returns TRUE.     }


begin

  if ( length(filename)  > 0 )    and
     ( pos('*',filename) = 0 )    and
     ( pos('?',filename) = 0 )
  then wildcard := false
  else wildcard := true;

end;