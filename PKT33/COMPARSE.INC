function comparse(     in_str  : string;
                   var command : string;
                   var n1      : integer;
                   var n2      : integer;
                   var n3      : integer;
                   var n4      : integer;
                   var n5      : integer;
                   var n6      : integer;
                   var n7      : integer  )   : boolean;

{ This function receives a robot command line and breaks it up into its }
{ component pieces.  If an error occurs the function returns a value of }
{ of false.  Otherwise it returns a value of true.                      }

var
  comma_pos    : byte;
  com_char     : char;
  m1,m2,m3,m4,m5,m6,m7 : string;


begin

  { Assume the best }
  comparse := true;

  if (blnkstr(in_str)) or
     (copy(in_str,length(in_str),1) = ',')
  then begin
         comparse := false;
         exit;
       end;

  { Remove leading and trailing blanks }
  blnkchop(in_str);

  command := copy(in_str,1,1);
  move(command[1],com_char,1);

  case upcase(com_char) of
    'C','N',
    'O','Z': if length(in_str) > 1
             then comparse := false
             else comparse := true;

    'D','G',
    'H','S': begin
               { More there? }
               if (length(in_str)  <= 1)    or
                  (pos(',',in_str) <> 0)
               then begin
                 comparse := false;
                 exit;
               end;

               { Get the next part }
               m1 := copy(in_str,2,length(in_str)-1);

               if not str2intg(m1,n1) then comparse := false;

             end;

     'M'    : begin
                { Check for minimum number of characters }
                if (length(in_str) < 12)
                then begin
                  comparse := false;
                  exit;
                end;

               { Get the next part }
               comma_pos := pos(',',in_str);
               if comma_pos = 0
               then begin
                 comparse := false;
                 exit;
               end;
               m1 := copy(in_str,2,comma_pos-2);
               in_str := copy(in_str,comma_pos+1,length(in_str)+comma_pos+1);

               { Get the next part }
               comma_pos := pos(',',in_str);
               if comma_pos = 0
               then begin
                 comparse := false;
                 exit;
               end;
               m2 := copy(in_str,1,comma_pos-1);
               in_str := copy(in_str,comma_pos+1,length(in_str)+comma_pos+1);



               { Get the next part }
               comma_pos := pos(',',in_str);
               if comma_pos = 0
               then begin
                 comparse := false;
                 exit;
               end;
               m3 := copy(in_str,1,comma_pos-1);
               in_str := copy(in_str,comma_pos+1,length(in_str)+comma_pos+1);

               { Get the next part }
               comma_pos := pos(',',in_str);
               if comma_pos = 0
               then begin
                 comparse := false;
                 exit;
               end;
               m4 := copy(in_str,1,comma_pos-1);
               in_str := copy(in_str,comma_pos+1,length(in_str)+comma_pos+1);

               { Get the next part }
               comma_pos := pos(',',in_str);
               if comma_pos = 0
               then begin
                 comparse := false;
                 exit;
               end;
               m5 := copy(in_str,1,comma_pos-1);
               in_str := copy(in_str,comma_pos+1,length(in_str)+comma_pos+1);

               { Get the next part }
               comma_pos := pos(',',in_str);
               if comma_pos <> 0
               then begin
                 comparse := false;
                 exit;
               end;
               m6 := in_str;

               if not str2intg(m1,n1) then comparse := false;
               if not str2intg(m2,n2) then comparse := false;
               if not str2intg(m3,n3) then comparse := false;
               if not str2intg(m4,n4) then comparse := false;
               if not str2intg(m5,n5) then comparse := false;
               if not str2intg(m6,n6) then comparse := false;

             end;

     'P'    : begin
                { Check for minimum number of characters }
                if (length(in_str) < 12)
                then begin
                  comparse := false;
                  exit;
                end;

               { Get the next part }
               comma_pos := pos(',',in_str);
               if comma_pos = 0
               then begin
                 comparse := false;
                 exit;
               end;
               m1 := copy(in_str,2,comma_pos-2);
               in_str := copy(in_str,comma_pos+1,length(in_str)+comma_pos+1);

               { Get the next part }
               comma_pos := pos(',',in_str);
               if comma_pos = 0
               then begin
                 comparse := false;
                 exit;
               end;
               m2 := copy(in_str,1,comma_pos-1);
               in_str := copy(in_str,comma_pos+1,length(in_str)+comma_pos+1);

               { Get the next part }
               comma_pos := pos(',',in_str);
               if comma_pos = 0
               then begin
                 comparse := false;
                 exit;
               end;
               m3 := copy(in_str,1,comma_pos-1);
               in_str := copy(in_str,comma_pos+1,length(in_str)+comma_pos+1);

               { Get the next part }
               comma_pos := pos(',',in_str);
               if comma_pos = 0
               then begin
                 comparse := false;
                 exit;
               end;
               m4 := copy(in_str,1,comma_pos-1);
               in_str := copy(in_str,comma_pos+1,length(in_str)+comma_pos+1);

               { Get the next part }
               comma_pos := pos(',',in_str);
               if comma_pos = 0
               then begin
                 comparse := false;
                 exit;
               end;
               m5 := copy(in_str,1,comma_pos-1);
               in_str := copy(in_str,comma_pos+1,length(in_str)+comma_pos+1);

               { Get the next part }
               comma_pos := pos(',',in_str);
               if comma_pos = 0
               then begin
                 comparse := false;
                 exit;
               end;
               m6 := copy(in_str,1,comma_pos-1);
               in_str := copy(in_str,comma_pos+1,length(in_str)+comma_pos+1);

               { Get the next part }
               comma_pos := pos(',',in_str);
               if comma_pos <> 0
               then begin
                 comparse := false;
                 exit;
               end;
               m7 := in_str;

               if not str2intg(m1,n1) then comparse := false;
               if not str2intg(m2,n2) then comparse := false;
               if not str2intg(m3,n3) then comparse := false;
               if not str2intg(m4,n4) then comparse := false;
               if not str2intg(m5,n5) then comparse := false;
               if not str2intg(m6,n6) then comparse := false;
               if not str2intg(m7,n7) then comparse := false;

             end;


    else comparse := false;

  end;   { case statement }

  command := upperstr(command);

end;