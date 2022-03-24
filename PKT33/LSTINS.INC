procedure lstins( temp_ptr : pk_ptr);

{ This procedure inserts a command into the command list. }
{ NOTE that if the cur_ptr is set to NIL, then we assume  }
{ that the current pointer is at the TOP of the list (before }
{ the first command) rather than anywhere else.          }


begin

  { If on the odd chance that temp_ptr is nil, exit }
  if temp_ptr = nil
  then exit;

  { If the top of list pointer is set to nil then add to top of list }
  if top_ptr = nil
  then begin
    temp_ptr^.next_ptr := nil;
    temp_ptr^.prev_ptr := nil;
    top_ptr := temp_ptr;
    cur_ptr := top_ptr;
    exit;
  end;

  { If the cur_ptr is nil, then we have yet to read in any commands.  }
  { Therefore, this record goes in the top of the list.               }
  if cur_ptr = nil
  then begin
    temp_ptr^.next_ptr := top_ptr;
    temp_ptr^.prev_ptr := top_ptr^.prev_ptr;
    top_ptr^.prev_ptr  := temp_ptr;
    top_ptr := temp_ptr;
    cur_ptr := temp_ptr;
    exit;
  end;

  { Insert somewhere in the middle of the list }
  temp_ptr^.next_ptr := cur_ptr^.next_ptr;
  temp_ptr^.prev_ptr := cur_ptr;
  cur_ptr^.next_ptr  := temp_ptr;
  cur_ptr            := temp_ptr;

  if temp_ptr^.next_ptr <> nil
  then temp_ptr^.next_ptr^.prev_ptr := temp_ptr;


end;
