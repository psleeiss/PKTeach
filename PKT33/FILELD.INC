procedure fileld( var the_file : pk_file );

{ This function loads a file of commands into memory. }

var
  count       : longint;
  temp_ptr    : pk_ptr;

begin

  { Set the pointer to the top of the file }
  seek(the_file,0);

  { Clear the linked list in memory (free-up memory) }
  lstclear;

  for count := 0 to filesize(the_file) - 1
  do begin

    { Read create a com_structure, read the file and build the linked list }
    new(temp_ptr);
    read(the_file,temp_ptr^);
    lstins(temp_ptr);

  end;  { For - loop }

  { The condition when cur_ptr is NIL signals that we are before the TOP of }
  { the list.  This means that the cur_ptr can never be allowed to be NIL   }
  { when the end-of-list condition occurs.                                  }
  cur_ptr := nil;

end;

