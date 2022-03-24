procedure filebe;

{ This procedure ensures that the begining and the end of program file will have
{ is a "Z" command and a "N" command at each end, respectively.             }

var
  temp_string : string;
  temp_ptr    : pk_ptr;

begin

  { Note that it is save to change the cur_ptr and top_ptr seeing as this is }
  { just prior to a file write.                                              }
  cur_ptr := top_ptr;

  { If the list is empty, don't even bother }
  if cur_ptr = nil
  then exit;

  { Check for leading "Z" command }
  temp_string := Upperstr(cur_ptr^.cmd_str);
  temp_string := TrimSpaces(temp_string);
  if temp_string <> 'Z'
  then begin

    { Create the structure to add into the command list }
    new(temp_ptr);
    with temp_ptr^ do
    begin
      cmd_str  := 'Z';
      base     := 0;
      shoulder := 0;
      elbow    := 0;
      wrist_p  := 0;
      wrist_r  := 0;
      gripper  := 0;
      next_ptr := nil;
      prev_ptr := nil;
    end;

    { We now have to insert a Z command }
    cur_ptr := nil;          { This means before the first command! }
    lstins(temp_ptr);
  end;

  { Find the last command in the list }
  cur_ptr := top_ptr;
  while cur_ptr^.next_ptr <> nil
  do cur_ptr := cur_ptr^.next_ptr;

  { Cur_ptr now points to the end of the list of commands }
  temp_string := upperstr(cur_ptr^.cmd_str);
  temp_string := TrimSpaces(temp_string);
  if temp_string <> 'N'
  then begin

    { Create the structure to add into the command list }
    new(temp_ptr);
    with temp_ptr^ do
    begin
      cmd_str  := 'N';
      base     := 0;
      shoulder := 0;
      elbow    := 0;
      wrist_p  := 0;
      wrist_r  := 0;
      gripper  := 0;
      next_ptr := nil;
      prev_ptr := nil;
    end;

    { We now have to insert an N command }
    temp_ptr^.cmd_str := 'N';
    lstins(temp_ptr);
  end;

end;
