function lstnext : boolean;

{ This function moves cur_ptr forward one command in the linked list.  If
{ we are at the end of the list (which includes having an empty list), then
{ the function will return a value of FALSE.  Otherwise, it returns TRUE. }

begin

  { Check to see if we have an empty list }
  if top_ptr = nil
  then begin
    lstnext := false;
    exit;
  end;

  { Check to see if this is the first command to be loaded. }
  if cur_ptr = nil
  then begin
    cur_ptr := top_ptr;
    lstnext := true;
    exit;
  end;

  { See if we are at the end of the list }
  if cur_ptr^.next_ptr = nil
  then begin
    lstnext := false;
    exit;
  end
  else begin
    cur_ptr := cur_ptr^.next_ptr;
    lstnext := true;
  end;

end;

