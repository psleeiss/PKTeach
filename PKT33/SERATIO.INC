function seratio( shoulder : integer) : integer;

{ Calculate the needed elbow displacement when the shoulder is moved }

begin
  seratio := - (shoulder*6) div 10;
end;