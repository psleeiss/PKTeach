procedure roboinit ( var robot : robot_pos);

{ This procedure initializes a robot_pos structure }

begin
  robot.base     := 0;
  robot.shoulder := 0;
  robot.elbow    := 0;
  robot.wrist_p  := 0;
  robot.wrist_r  := 0;
  robot.gripper  := 0;

end;
