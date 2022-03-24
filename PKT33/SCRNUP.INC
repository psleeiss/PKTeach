procedure scrnup(var a_screen);

{ This procedure takes as input a 4K block of memory and dumps it to the }
{ appropriate part of memory (video ram) based on the current video mode.}
{ If the global constant MONO_AND_COLOR_MONITORS is true, then this      }
{ procedure will dump the screen contents to both video ram locations.   }

var
  CGA_screen  : array[1..4000] of char absolute $B800:$0000;
  HERC_screen : array[1..4000] of char absolute $B000:$0000;

begin

  { See if we are in Hercules Monochrome Graphics text mode }
  if vidmode = 7
  then move(a_screen,HERC_screen,4000)
  else move(a_screen,CGA_screen,4000);

  if mono_and_color_monitors
  then if vidmode = 7
       then move(a_screen,CGA_screen,4000)
       else move(a_screen,HERC_screen,4000);

end;