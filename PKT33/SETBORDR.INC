procedure setbordr( bord_color : byte );

{ This procedure sets the CGA border color to the color specified by the }
{ input parameter.                                                       }

const
  video_interrupt     = $10;  { Hex }
  set_color_pallette  = $B;   { Decimal 11 }

var
  myregs  :  registers;

begin

  myregs.ah := set_color_pallette;
  myregs.bx := bord_color;

  intr(video_interrupt,myregs);

end;

