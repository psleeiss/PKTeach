procedure filestor( var the_file : pk_file);

{ This procedure writes the memory_resident linked-list to the file }

var
  temp_ptr : pk_ptr;
  any_char : char;

begin

  { Make sure begining of file has a "Zero" command and end has a Nest }
  filebe;

  { Step through the linked list writing everything to disk }
  temp_ptr := top_ptr;
  while temp_ptr <> nil
  do begin
    seek(the_file,filesize(the_file));  { Insert }
    write(the_file,temp_ptr^);
    temp_ptr := temp_ptr^.next_ptr;
  end;

end;