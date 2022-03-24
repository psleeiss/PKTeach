function lstprev : boolean;

{ This function is used to move the cur_ptr to the previous command in the
{ mem-resident linked list.  If the list is empty or if we are at the top
{ of the list, the function returns a value of FALSE.  Otherwise it will
{ return a value of TRUE.                                      }

begin


  { Check to see if we have an empty list }
  if top_ptr = nil
  then begin
    lstprev := false;
    exit;
  end;

  { See if any commands have been loaded yet }
  if cur_ptr = nil
  then begin
    lstprev := false;
    exit;
  end;

  { See if we are at the top of the list }
  { Note that this does NOT allow the student to previous before the Z }
  if cur_ptr^.prev_ptr = nil
  then begin
    lstprev := false;
    exit;
  end
  else begin
    cur_ptr := cur_ptr^.prev_ptr;
    lstprev := true;
  end;

end;

