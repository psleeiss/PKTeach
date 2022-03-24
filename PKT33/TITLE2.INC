procedure title2;

{ Display the title screen }
const
  pk_version = 'version 3.3';

var
  any_key        : word;
  serial_num_str : string[20];
  dv, dm         : integer;

begin
  if MouseInstalled then
    EnableEventHandling;

  { Convert serial number into a string we can display }
  str(everlock.get_serial_number,serial_num_str);
  HideMouse;
  HiddenCursor;
  Win[1]^.Draw;
  gotoxy(28,4);
  Write('Marcraft International');
  gotoxy(35,8);
  Write('Presents');
  gotoxy(28,12);
  Write('PK-TEACH ('+pk_version+')');
  gotoxy(12,17);
  Write('Copyright (C) 1991 by Inspired Software Solutions, Inc');
  gotoxy(30,18);
  write('All rights reserved');
  gotoxy(30,22);
  write('Serial # PKT'+ serial_num_str);

  HiddenCursor;
  any_key := ReadKeyOrButton;

  { Close the window }
  win[1]^.clear;
  win[1]^.erase;
  NormalCursor;

end;


