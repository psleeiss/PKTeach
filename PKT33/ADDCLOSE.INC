function addclose : boolean;

{ This function returns TRUE if a CLOSE command should be added after the }
{ current command.  Basically, if the previous command did not have the gripper }
{ completely closed, and the current command does, and the current command }
{ and the next command are not CLOSE commands, then the function returns true. }

begin

  { Expect the worst }
  addclose := false;

  { Check for an empty list or a close command }
  if (cur_ptr = nil) or (cur_ptr^.cmd_str[1] = 'C')
  then exit;

  { If first command, the gripper should already be closed (nest position) }
  if cur_ptr^.prev_ptr = nil
  then exit;

  { Was previous position with gripper closed? }
  if cur_ptr^.prev_ptr^.gripper = 0
  then exit;

  { Is the following command (if any) a close already? }
  if cur_ptr^.next_ptr <> nil
  then if (cur_ptr^.next_ptr^.cmd_str[1] = 'C') or
          (cur_ptr^.next_ptr^.cmd_str[1] = 'N')
       then exit;

  addclose := true;

end;