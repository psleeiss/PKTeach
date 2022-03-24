{ This file contains all of the definitions and declarations for the }
{ PK ROBO-TEACH program.                                             }


type

  robot_pos = record
                base          : integer;
                shoulder      : integer;
                elbow         : integer;
                wrist_p       : integer;
                wrist_r       : integer;
                gripper       : integer;
              end;


  win_attr  = record
                win_num  : array[1..20] of byte;
              end;

  str41 = string[41];

  robo_memory = array[0..100] of str41;