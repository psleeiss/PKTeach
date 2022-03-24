{ This file contains the include for the PKTEACH file format }

const
  cur_cmd  = 0;
  next_cmd = 1;
  prev_cmd = 2;

type

  pk_ptr  = ^pk_type;
  pk_type = record
              next_ptr          : pk_ptr;
              prev_ptr          : pk_ptr;
              cmd_str           : string[41];
              base              : integer;
              shoulder          : integer;
              elbow             : integer;
              wrist_p           : integer;
              wrist_r           : integer;
              gripper           : integer;
            end;

   { The first record in the file has only a valid NEXT_PTR to point to the }
   { top of the list.                                      }
   pk_file = file of pk_type;