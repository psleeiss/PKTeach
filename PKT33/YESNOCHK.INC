function yesnochk( var in_char         ;
                       chr_len   : byte;
                   var answer    : boolean) : boolean ;

{ This procedure will check to see if the character array passed in contains }
{ a valid Y/N answer.  That is, if the input contains a y, n, yes, or no,    }
{ then it is considered valid and answer will be set accordingly.            }

var
  ok          : boolean;
  temp_string : string[255];
  fail_safe   : string[255];
  str_len     : byte absolute temp_string;

begin

  { Copy character array to string }
  move(in_char,temp_string[1],chr_len);
  str_len := chr_len;


  { remove blanks before test }
  blnkchop(temp_string);


  { Convert the string to upper case and see if it is valid }
  temp_string := upperstr(temp_string);

  if (temp_string = 'Y') or (temp_string = 'YES')
  then begin
    ok := true;
    answer := true;
    temp_string := max_blank_string;
    if chr_len >= 3
    then temp_string := 'YES'
    else temp_string := 'Y';
  end
  else if (temp_string = 'N') or (temp_string = 'NO')
       then begin
         ok := true;
         answer := false;
         temp_string := max_blank_string;
         if chr_len >= 3
         then temp_string := 'NO '
         else temp_string := 'N';
       end
       else ok := false;


  { Put answer back }
  move(temp_string[1],in_char,chr_len);

  yesnochk := ok;

end;  { Function }