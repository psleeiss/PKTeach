function yorn : boolean;

var
  keyword    :  integer;
  any_char   :  char absolute keyword;
  valid_key,
  ok         :  boolean;

  begin
    hiddencursor;
    valid_key := false;
    EnableEventHandling;
    repeat
      KeyWord := integer(ReadKeyOrButton);
      If any_char = #0 then
        begin
          if KeyWord = integer(MouseLft) then
            begin
              ok := true;
              valid_key := true;
            end
          else if KeyWord = integer(MouseRt) then
            begin
              ok := false;
              valid_key := true;
            end
            else valid_key := false;
        end
        else
        begin
          any_char := UpCase(any_char);
          if any_char = 'Y' then
            begin
              ok := true;
              valid_key := true;
            end
           else if any_char = 'N' then
             begin
               ok := false;
               valid_key := true;
             end
             else valid_key := false;
        end;
     until (valid_key = true);
     yorn := ok;
  end;