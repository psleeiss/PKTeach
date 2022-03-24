program pktclone;

{ This program is used in settint the PK Teach Serial Number }

uses opcrt, dos, opdos, opinline, opstring, oproot, opclone;

procedure GetSerialNum(var number : longint);
begin
  writeln;
    write('Enter new serial #: ');
    {$I-}
    readln(number);
    {$I+}
    writeln;
    writeln;
end;

type
  serial_num_rec = record
                     key_string  : string[13];
                     serial_num  : longint;
                   end;

const
  my_rec : serial_num_rec = (key_string : 'Snuggle Bunny';
                             Serial_Num : 0);


var
  my_clone     : cloner;
  time_to_quit : boolean;
  first_time   : boolean;
  in_char      : char;
  valid_char   : boolean;
  the_drive    : char;


begin
  first_time := true;
  writeln;
  writeln('PK Teach Cloner Software ');
  writeln('Copyright (C) 1992 by Inspired Software Solutions, Inc.');
  writeln('All rights reserved.');
  writeln;
  writeln;
  writeln('About to update the serial number for PKTEACH.EXE');
  writeln;
  writeln;

  time_to_quit := false;
  while not time_to_quit
  do begin

    if first_time
    then begin
      GetSerialNum(my_rec.serial_num);
      repeat
        write('Which drive? (A or B): ');
        the_drive := upcase(readkey);
        writeln;
        writeln;
      until (the_drive in ['A','B']);
    end
    else inc(my_rec.serial_num);

    if ioresult <> 0
    then begin
      writeln('Invalid serial number!  Program halting.');
      writeln;
      halt(1);
    end;

    { Update the EXE file }
    if not my_clone.InitCustom('PKTEACH.EXE',updatenone,defbufsize)
    then begin
      writeln('Unable to update PKTEACH.EXE!');
      writeln;
    end
    else begin
      if not my_clone.findDefaultsEnd(my_rec.key_string,
                                      sizeof(my_rec.key_string),0)
      then begin
        writeln;
        writeln('Could not find the serial # in PKTEACH.EXE!');
        writeln;
      end
      else begin
        my_clone.StoreDefaults(My_clone.GetPos,my_rec,sizeof(my_rec));
        if my_clone.GetLastError <> 0
        then begin
          writeln('Could not successfully update the Serial Number.')
        end
        else begin
          if ExecDos('Copy *.* '+the_drive+':',true,noexecdosproc) <> 0
          then halt(1);

          first_time := false;
          write(#7);
          writeln('Serial Number ',my_rec.serial_num,' successfully updated.');
          writeln;
          writeln;
          valid_char := false;
          while not valid_char
          do begin
            write('Type ''Y'' for another, ''Q'' for quit, ''N'' for new number: ');
            in_char := upcase(readkey);
            if in_char in ['Y','Q','N']
            then begin
              valid_char := true;
              if in_char = 'Q' then time_to_quit := true;
              if in_char = 'N' then first_time := true;
            end;
          end;

        end;
        writeln;
      end;

      my_clone.done;
    end;

(*    write('Do you wish to clone another? [Y or N]: ');
    writeln;
    writeln;
    if upcase(readkey) = 'N'
    then time_to_quit := true;*)
  end;

end.