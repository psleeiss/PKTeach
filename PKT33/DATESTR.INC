function datestr(today : date_def) : str8;

{ This function is passed a structure that contains the date in "date_def" }
{ record format, and returns a string[8] value that is MM/DD/YY.           }

var
  return_str     : str8;
  temp           : word;

begin

  return_str := '        ';

  { Get last two digits of date }
  temp := today.year mod 10;
  insert(inttostr(temp),return_str,1);
  today.year := today.year - temp;

  temp := (today.year mod 100) div 10;
  insert(inttostr(temp),return_str,1);

  { Add the slash }
  insert('/',return_str,1);

  { Get the day }
  temp := today.day mod 10;
  insert(inttostr(temp),return_str,1);
  today.year := today.year - temp;

  temp := (today.day mod 100) div 10;
  insert(inttostr(temp),return_str,1);

  { Insert the next slash }
  insert('/',return_str,1);

  { Get the month }
  temp := today.month mod 10;
  insert(inttostr(temp),return_str,1);
  today.year := today.month - temp;

  temp := (today.month mod 100) div 10;
  insert(inttostr(temp),return_str,1);

  datestr := return_str;

end;


