procedure lstclear;

{ This procedure clears the memory-resident linked list of commands }

begin

  { Step through list and free up each record }
  while top_ptr <> nil
  do begin
    cur_ptr := top_ptr^.next_ptr;
    dispose(top_ptr);
    top_ptr := cur_ptr;
  end;

end;
