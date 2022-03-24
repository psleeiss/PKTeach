function addopen : boolean;

{ This function returns TRUE if an OPEN command should be added after the  }
{ current command.  If the previous command does not have the gripper      }
{ completely open, and the current or following commands are not "OPEN"    }
{ commands, and the current command needs the gripper all the way open,    }
{ then this function returns true.                                         }

begin

  { Expect the worst }
  addopen := true;

  { If empty list, force an open...should have been at "nest" position }
  if (cur_ptr = nil)
  then exit;

  { If at top of list, add open }
  if cur_ptr^.prev_ptr = nil
  then exit;

  if cur_ptr^.prev_ptr^.gripper <> max_ranges.gripper
  then if cur_ptr^.cmd_str = 'O'
       then exit
       else if cur_ptr^.next_ptr <> nil
            then if cur_ptr^.next_ptr^.cmd_str = 'O'
                 then exit;

  addopen := true;

end;