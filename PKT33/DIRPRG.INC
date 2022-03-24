procedure dirprg;

{ This procedure is like the DOSDIR procedure in MISC unit except that it }
{ can halt the screen display if the SCROLL-LOCK key is down, and it auto-}
{ matically will give a directory of *.PRG .               }

var
  mask     : str66;
  xpos     : array[1..4] of byte;
  file_rec : searchrec;
  count    : integer;
  kbd_stat : byte absolute $0000:$0417;

begin

  { Set up columns for output }
  xpos[1] := 3;
  xpos[2] := 20;
  xpos[3] := 37;
  xpos[4] := 54;

{  writeln;
  write('Enter mask [default is *.*]: ');
  readln(mask);
  writeln;  }
  mask := '*.PRG';

  { Set default if user wishes it }
  if blnkstr(mask) then mask := '*.*';
  mask := upperstr(mask);

{  writeln('Dos Directory with mask = ',mask);}
  writeln;
  writeln;


  findfirst(mask,anyfile,file_rec);

  count := 1;
  while doserror = 0 do
  begin
    gotoxy(xpos[count],wherey);

    { Don't print out the . and .. directories }
    if (file_rec.name <> '.') and (file_rec.name <> '..')
    then begin

      if file_rec.attr = directory
      then begin
        textcolor(black);
        textbackground(white);
        write(file_rec.name);
        textcolor(white);
        textbackground(black);
      end
      else write(strfext(file_rec.name));

      { Advance counter for number of entries on line }
      count := count + 1;
      if count > 4
      then begin
        count := 1;
        writeln;
      end;
    end;

    { Pause screen output if the scroll lock key is on }
    while (kbd_stat and $10) = $10
    do delay(100);

    findnext(file_rec);
  end;  { While loop }

end; { procedure }

