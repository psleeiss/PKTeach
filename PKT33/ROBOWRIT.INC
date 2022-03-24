procedure robowrit ( command : string);

{ This function writes a command to the robot.  Note that the BIOS printer }
{ services are used to send characters out to the printer port.  This is   }
{ done to avoid a "printer timeout" error which can occur using Pascal's   }
{ WRITELN(prn,string) statement if the robot is executing a slow or complex }
{ movement.  Basically, the BIOS routines are used so that we can "trap" a }
{ printer (really robot) timeout without the program coming to a halt. }



{ Robowrit's variables }
const
  printer_services = 23;
  max_BIOS_tries   = 3;
  printer_lpt1     = 0;

var

  count        : integer;
  retries      : byte;
  myregs       : registers;
  command_len  : byte;
  time_to_quit : boolean;
  temp_string  : string[1];
  command2     : string;
  command_byte : array[0..255] of byte absolute command2;


begin

  command2 := command;
  blnkchop(command2);

  { Append a carriage return/line feed to end of command (expected by robot) }
  command2 := command2 + #13 + #10;
  command_len := length(command2);


  if command_len = 0
  then exit;

  { Using the BIOS printer services (which will inform us if a timeout occurs )}
  { output one character at a time.         }
  for count := 1 to command_len do
  begin

    retries := 0;
    while (retries <= max_bios_tries) do
    begin
      myregs.ah := 0;
      myregs.al := command_byte[count];
      myregs.dx := printer_lpt1;
      intr(printer_services,myregs);

      { Check the results to see if we had a timeout arise }
      if (myregs.ah and $09) <> 0
      then retries := retries + 1
      else retries := max_bios_tries + 1;
    end;
  end;


end;