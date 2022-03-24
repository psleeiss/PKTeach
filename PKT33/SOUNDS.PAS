unit sounds;

{ This unit is dedicated to sound utilities (that is, utilities that produce }
{ sounds from the computer }

{$F+,O+}

interface
uses dos,opcrt;

{ This procedure produces a loud and long alarm }
procedure alarm1;

{ This procedure produces two very short "chirps" out of the speaker }
procedure chirp;

{ This procedure gives the user the "raspberry" }
procedure raspbery;

{ The purpose of this procedure is to get the user's attention with an }
{ audible sound.  Seeing as most people get irritated at a "beep", I   }
{ now use this whistle routine.                                        }
procedure whistle;



implementation

procedure alarm1;

{ This procedure produces one very short "chirp" out of the speaker }

const
  Low_freq  = 6000;
  high_freq = 10000;

var
  count1 : word;
  count2 : word;
  count3 : word;

begin
(*
  for count3 := 1 to 10
  do begin

    for count1 := low_freq to high_freq
    do sound(count1);
    for count2 := low_freq to high_freq
    do sound(high_freq + 1 -count2);
  end; *)

  sound(4000);
  delay(10000);

  nosound;

end;

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
end;

procedure raspbery;

{ This procedure gives the user the "raspberry" }

var
  count : integer;

begin

  for count := 1 to 5
  do begin
    sound(25);
    delay(50);
    sound(30);
    delay(50);
  end;

  nosound;

end;

procedure whistle;

{ The purpose of this procedure is to get the user's attention with an }
{ audible sound.  Seeing as most people get irritated at a "beep", I   }
{ now use this whistle routine.                                        }

var
  count : integer;

begin
  sound(1000);
  delay(100);
  for count := 1000 downto 500
  do sound(count);

  for count := 500 to 1500
  do sound(count);

  nosound;

end;



begin
end.



