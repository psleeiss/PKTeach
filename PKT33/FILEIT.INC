procedure fileit( in_str : string );

{ This procedure takes as input a string, and then proceeds to insert a }
{ robot command into the mem-resident linked list using the absolute    }
{ position coordinates and the input string to build a command structure }

var
  com_ptr      : pk_ptr;
  temp_string  : string;

begin

  { Remove leading and trailing blanks from input string }
  temp_string := TrimSpaces(in_str);

  { Create a new structure and fill it }
  new(com_ptr);
  com_ptr^.next_ptr    := nil;
  com_ptr^.prev_ptr    := nil;
  com_ptr^.cmd_str     := in_str;
  com_ptr^.base        := abs_pos.base;
  com_ptr^.shoulder    := abs_pos.shoulder;
  com_ptr^.elbow       := abs_pos.elbow;
  com_ptr^.wrist_p     := abs_pos.wrist_p;
  com_ptr^.wrist_r     := abs_pos.wrist_r;
  com_ptr^.gripper     := abs_pos.gripper;

  { Insert into the mem-resident linked list }
  lstins(com_ptr);

end;