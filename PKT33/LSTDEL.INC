procedure lstdel;

{ This procedure deletes an item out of the memory-resident linked list }

var
  temp_ptr   : pk_ptr;

begin

  { If on the odd chance that cur_ptr is nil or list empty, exit }
  if (cur_ptr = nil) or (top_ptr = nil)
  then exit;

  { If we are at the top of the list to delete }
  if cur_ptr = top_ptr
  then begin
    top_ptr := cur_ptr^.next_ptr;

    { See if there is another record in the list }
    if top_ptr <> nil
    then top_ptr^.prev_ptr := nil;

    dispose(cur_ptr);
    (*cur_ptr := nil;*)   { Remember that cur_ptr = NIL means before first command }
    cur_ptr := top_ptr;
  end
  else begin

    { If we are in the middle of the list somewhere... }
    temp_ptr := cur_ptr;
    cur_ptr := cur_ptr^.prev_ptr;
    cur_ptr^.next_ptr := temp_ptr^.next_ptr;

    { Watch out for end of list }
    if temp_ptr^.next_ptr <> nil
    then temp_ptr^.next_ptr^.prev_ptr := cur_ptr;
    dispose(temp_ptr);
  end;

end;
