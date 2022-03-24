function onekey : char;

{ This procedure gets one key-stroke from the user and returns it as }
{ the value in char.                                                 }

var
  temp : char;

begin
  repeat
    temp := readkey;        { Read the keyboard }
    if temp = #0            { Check for, and don't allow, special keys }
    then begin
      temp := readkey;      { If special key, get another key }
      temp := #0;
      whistle;              { Get the user's attention }
    end;

  until temp <> #0;

  onekey := temp;

end;

