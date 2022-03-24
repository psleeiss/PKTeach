procedure dispscrn( scrnname : str66);

type
  bit_screen = array[1..4003] of byte;

var
  screen      : bit_screen;
  screen_file : file of bit_screen;
  filename    : string[66];
  io_rc       : word;

begin

  { Attach proper suffix to screen name }
  filename := copy(scrnname,1,length(scrnname)) + '.8d';

  { Open the file and read the data directly into video RAM }
  assign(screen_file,filename);
  {$I-}
  reset(screen_file);
  {$I+}

  io_rc := ioresult;

  if io_rc <> 0
  then begin
    whistle;
    writeln('Could not open the screen file:',filename);
    writeln('IOresult = ',io_rc);
    halt;

  end;

  read(screen_file,screen);
  close(screen_file);
  scrnup(screen);

end;