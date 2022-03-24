function scrnprc ( var in_screen : screen_buf) : integer;

{ This function processes a screen passed in to it.  This function returns }
{ the value of the key-stroke that caused it to terminate.  If an error    }
{ occurs within the screen processor, the return from scrnprc will be a    }
{ negative number.                                                         }

var
  max_buffer     : integer;
  last_key       : integer;
  in_type        : char;
  input_valid    : boolean;
  temp_str       : string;
  temp_str_len   : byte absolute temp_str;
  time_to_quit   : boolean;

begin

  max_buffer := in_screen.num_used;
  time_to_quit := false;

while  not time_to_quit do
begin

  input_valid := false;   { Guilty until proven otherwise }

  { Don't call SCBUFINP if it is a display only buffer }
  in_type := upcase(in_screen.buffers[in_screen.current_buffer].buff_type);

  { Edit the buffer }
  if in_type <> 'V'
  then last_key := scbufinp(in_screen.buffers[in_screen.current_buffer].xpos,
                            in_screen.buffers[in_screen.current_buffer].ypos,
                            in_screen.buffers[in_screen.current_buffer].len,
                            in_screen.buffers[in_screen.current_buffer].data_buff,
                            in_screen.esc_allowed,
                            in_screen.pgup_allowed,
                            in_screen.pgdn_allowed,
                            in_screen.F1_allowed,
                            in_screen.F2_allowed,
                            in_screen.F3_allowed,
                            in_screen.F4_allowed,
                            in_screen.F5_allowed,
                            in_screen.F6_allowed,
                            in_screen.F7_allowed,
                            in_screen.F8_allowed,
                            in_screen.F9_allowed,
                            in_screen.F10_allowed);

  { Make sure that input was valid }
  case in_type of

          { Buffer allows character input only }
    'C':  begin
            leftjust(in_screen.buffers[in_screen.current_buffer].len,
                     in_screen.buffers[in_screen.current_buffer].data_buff);

            { Redisplay buffer }
            gotoxy(in_screen.buffers[in_screen.current_buffer].xpos,
                   in_screen.buffers[in_screen.current_buffer].ypos);
            writchar(in_screen.buffers[in_screen.current_buffer].data_buff,
                     in_screen.buffers[in_screen.current_buffer].len);

            input_valid := true;
          end;

          { Buffer allows upper-case character input only }
    'U':  begin
            leftjust(in_screen.buffers[in_screen.current_buffer].len,
                     in_screen.buffers[in_screen.current_buffer].data_buff);

            { Move the data into a temporary string so that it can be }
            { converted to all upper-case.                            }
            temp_str_len := in_screen.buffers[in_screen.current_buffer].len;
            move(in_screen.buffers[in_screen.current_buffer].data_buff,
                 temp_str[1],in_screen.buffers[in_screen.current_buffer].len);

            { Convert to upper case and put back into screen buffer }
            temp_str := upperstr(temp_str);
            move(temp_str[1],
                 in_screen.buffers[in_screen.current_buffer].data_buff,
                 temp_str_len);

            { Redisplay buffer }
            gotoxy(in_screen.buffers[in_screen.current_buffer].xpos,
                   in_screen.buffers[in_screen.current_buffer].ypos);
            writchar(in_screen.buffers[in_screen.current_buffer].data_buff,
                     in_screen.buffers[in_screen.current_buffer].len);

            input_valid := true;
          end;

         { Buffer allows INTEGER input only }
    'I': if chr2intg(in_screen.buffers[in_screen.current_buffer].data_buff,
                     in_screen.buffers[in_screen.current_buffer].len,
                     in_screen.buffers[in_screen.current_buffer].int_buf)
         then begin

           { Redisplay the buffer field (should look prettier }
           input_valid := true;
           gotoxy(in_screen.buffers[in_screen.current_buffer].xpos,
                  in_screen.buffers[in_screen.current_buffer].ypos);
           writchar(in_screen.buffers[in_screen.current_buffer].data_buff,
                    in_screen.buffers[in_screen.current_buffer].len);
         end
         else whistle;

         { Buffer allows REAL input only }
    'R': if chr2real(in_screen.buffers[in_screen.current_buffer].data_buff,
                     in_screen.buffers[in_screen.current_buffer].len,
                     in_screen.buffers[in_screen.current_buffer].real_buf)
         then begin

           { Redisplay the buffer field (should look prettier }
           input_valid := true;
           gotoxy(in_screen.buffers[in_screen.current_buffer].xpos,
                  in_screen.buffers[in_screen.current_buffer].ypos);
           writchar(in_screen.buffers[in_screen.current_buffer].data_buff,
                    in_screen.buffers[in_screen.current_buffer].len);
         end
         else whistle;

         { Buffer allows a "YES or NO" input only }
    'Y': if yesnochk(in_screen.buffers[in_screen.current_buffer].data_buff,
                     in_screen.buffers[in_screen.current_buffer].len,
                     in_screen.buffers[in_screen.current_buffer].y_n_buf)
         then begin

           { Redisplay the buffer field (should look prettier }
           input_valid := true;
           gotoxy(in_screen.buffers[in_screen.current_buffer].xpos,
                  in_screen.buffers[in_screen.current_buffer].ypos);
           writchar(in_screen.buffers[in_screen.current_buffer].data_buff,
                    in_screen.buffers[in_screen.current_buffer].len);
         end
         else whistle;

         { Input is for viewing only...no user-input allowed }
    'V': begin

           { In the event of a view-only buffer, simulate a <RETURN> as the }
           { last key hit to advance the buffer pointer.                    }
           input_valid := true;
           last_key := retrn;
         end;

    else begin
      writeln;
      writeln('ERROR in SCRNPRC:  No valid buffer type');
      writeln('   Buffer # ',in_screen.current_buffer);
      writeln('   Buffer type = ',in_type);
      whistle;
      scrnprc := -1;
      exit;
    end;
  end;      { CASE stmt }


  { If input was valid, act on last user key-stroke }
  if input_valid
  then begin

    case last_key of

      retrn,down  : in_screen.current_buffer := in_screen.current_buffer + 1;

      up          : in_screen.current_buffer := in_screen.current_buffer - 1;

      esc,pgup,pgdn,
      F1..F10     : time_to_quit := true;

      else begin
        writeln;
        writeln('ERROR in SCRNPRC:  No valid return from SCBUFINP');
        writeln('     BUFFINP returned ',last_key);
        whistle;
        delay(2000);
        scrnprc := -1;
        exit;
      end;

    end;  { CASE stmt }

    { Make sure current_buffer is still in bounds }
    if in_screen.current_buffer < 1
    then in_screen.current_buffer := max_buffer
    else if in_screen.current_buffer > max_buffer
         then in_screen.current_buffer := 1;
  end;

end;  { While loop }

{ Set return value }
scrnprc := last_key;

end;   { function }
