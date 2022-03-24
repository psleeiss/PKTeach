procedure robomrng ( var robot : robot_pos);

{ This procedure initializes the robots max range structure }

begin
  robot.base     := 1000;
  robot.shoulder := 600;
  robot.elbow    := 500;
  robot.wrist_r  := 7200;
  robot.wrist_p  := 900;
  robot.gripper  := 2000;

end;
