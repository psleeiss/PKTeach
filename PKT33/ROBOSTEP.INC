procedure robostep ( var robot : robot_pos);

{ This procedure initializes the robot step increments structure }

begin
  robot.base     := 100;
  robot.shoulder := 60;
  robot.elbow    := 60;
  robot.wrist_r  := 500;
  robot.wrist_p  := 90;
  robot.gripper  := 500;

end;
