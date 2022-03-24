procedure initscbf( var screen : screen_buf);

{ This procedure initializes a screen_buf data structure }

begin

  { Use the screen_buf that was initialized by the unit initialization code }
  move(initialized_screen,screen,sizeof(screen));

end;