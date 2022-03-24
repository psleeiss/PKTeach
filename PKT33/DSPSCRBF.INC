procedure dspscrbf( screen : screen_buf);

{ This procedure displays the supplied screen buffer }

var
  count : integer;

begin

  { If none used then simply return }
  if screen.num_used < 1
  then exit;

  for count := 1 to screen.num_used do
  begin
    gotoxy(screen.buffers[count].xpos,screen.buffers[count].ypos);
    dspchrar(screen.buffers[count].data_buff,screen.buffers[count].len);

  end;

end;