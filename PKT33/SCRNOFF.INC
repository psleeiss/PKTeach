procedure scrnoff(flags,cs,ip,ax,bx,cx,dx,si,di,ds,es,bp: word); interrupt;

{$I enable.inc}       { Enable interrupts }


begin
  { In effect, we wish to do nothing to the video display }

  enable;    { enable interrupts }
end;
