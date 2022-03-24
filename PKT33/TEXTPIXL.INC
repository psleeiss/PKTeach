function textpixl( inval : integer) : integer;

{ Given a text location for x or y, this function returns the appropriate }
{ pixel location for the graphics screen OUTTEXTXY procedure.             }


begin
  textpixl := (inval - 1) * 8;
end;