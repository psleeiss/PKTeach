function upperstr( in_str : string) : string;

var
  temp : string;
  count : integer;

begin
  temp := '';
  for count := 1 to length(in_str)
      do temp := temp + upcase(in_str[count]);

  upperstr := temp;

end;