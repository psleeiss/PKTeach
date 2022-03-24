procedure chirp;

{ This procedure produces one very short "chirp" out of the speaker }

begin
  sound(1760);
  delay(50);
  nosound;
  delay(50);
  sound(1760);
  delay(50);
  nosound;
end;