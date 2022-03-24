function timestr(today : time_def) : str8;

{ This function is passed a structure that contains the time in "time_def" }
{ record format, and returns a string[8] value that is HH:MM:SS.           }

var
  return_str     : str8;
  temp           : word;

begin

  return_str := '        ';

  { Get the seconds }
  temp := today.second mod 10;
  insert(inttostr(temp),return_str,1);
  today.second := today.second - temp;

  temp := (today.second mod 100) div 10;
  insert(inttostr(temp),return_str,1);

  { Add the colon }
  insert(':',return_str,1);

  { Get the minutes }
  temp := today.minute mod 10;
  insert(inttostr(temp),return_str,1);
  today.minute := today.minute - temp;

  temp := (today.minute mod 100) div 10;
  insert(inttostr(temp),return_str,1);

  { Insert the next colon }
  insert(':',return_str,1);

  { Get the hour }
  temp := today.hour mod 10;
  insert(inttostr(temp),return_str,1);
  today.hour := today.hour - temp;

  temp := (today.hour mod 100) div 10;
  insert(inttostr(temp),return_str,1);

  timestr := return_str;

end;


