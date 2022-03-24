function swratio( shoulder : integer) : integer;

{ Compute the amount the wrist will pitch given the shoulder movement }
begin
  swratio:= - shoulder div 2;
end;
