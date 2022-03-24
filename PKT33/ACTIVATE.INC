function activate( window_num : byte) : boolean;

{ This function activates a window on the popup window stack }
{ It is passed the window number of the window on the stack to activate. }
{ If a problem occurs, the function returns with a value of FALSE.  Otherwise }
{ it returns with a value of TRUE.  It does set the WINDOWS unit error flags }
{ It is currently the programmers responsibility to ensure that the windows }
{ being activated in this manner are not overlapped by another window.      }

var
  current_win       : word;
  window_num_string : string;

begin

  { Reset all of the WINDOWS unit error flags }
  werreset;

  { Get the current window number }
  current_win := window_stack.current_window;

  { See if the desired window exists in the stack }
  if ( window_num < 1 )  or
     ( window_num > window_stack.stack_pos)
  then begin
    activate := false;
    window_error := true;
    str(window_num,window_num_string);
    window_err_msg := 'Attempt to activate a non-existant window number.  Number = '
                       + window_num_string;
    window_err_routine := 'ACTIVATE';
    exit;
  end;

  { Save the current state of the current window }
  if current_win = window_stack.stack_pos
  then begin
    window_stack.act_cursor_x    := wherex;
    window_stack.act_cursor_y    := wherey;
    window_stack.act_cursor_size := rom_cursor_size;
    window_stack.act_colors      := textattr;
    window_stack.act_window_min    := windmin;
    window_stack.act_window_max    := windmax;
  end
  else begin

    { Save the current state of the active window on the stack }
    window_stack.save_cursor_x[current_win+1]    := wherex;
    window_stack.save_cursor_y[current_win+1]    := wherey;
    window_stack.save_cursor_size[current_win+1] := rom_cursor_size;
    window_stack.save_colors[current_win+1]      := textattr;
  end;

  { Activate the desired window }
  if window_num <> window_stack.stack_pos
  then begin

    windmax := window_stack.save_window_max[window_num+1];
    windmin := window_stack.save_window_min[window_num+1];
    rom_cursor_size := window_stack.save_cursor_size[window_num+1];
    textattr := window_stack.save_colors[window_num+1];
    gotoxy(window_stack.save_cursor_x[window_num+1],
           window_stack.save_cursor_y[window_num+1]);
  end
  else begin
    windmax := window_stack.act_window_max;
    windmin := window_stack.act_window_min;
    rom_cursor_size := window_stack.act_cursor_size;
    textattr := window_stack.act_colors;
    gotoxy(window_stack.act_cursor_x,window_stack.act_cursor_y);
  end;

  { Reset the current_window pointer }
  window_stack.current_window := window_num;

  { If we made it this far then all must be well }
  activate := true;

end;