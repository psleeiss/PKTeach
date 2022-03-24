function getkey(Win : integer) : char;

label

  win_down;

var
  win1       : RawWindow;
  WinOpts    : Longint;
  any_char   : char;
  filename   : filestr;
  title,
  trailer    : string;


begin

  WinOpts := wBordered+wClear;

  if Not win1.InitCustom(3, 14, 35, 23, Menucolors, WinOpts)
    then begin
           writeln (' Could Not Draw Prompt Window ');
           exit;
         end;
  if robot_mode = edit_prog
  then title := ' Editing ' + strfext(filename) + ''
  else title := ' Writing ' + strfext(filename) + '';
  win1.wFrame.AddHeader(title, heTC);
  win1.wFrame.AddHeader(' Press ''X'' to exit ', heBC);
  if Win = 0 then
  win1.Draw
  else goto win_down;
  if robot_mode <> edit_prog
  then writeln;
  writeln;
  writeln(' C - Close        N - Nest');
  writeln(' D - Delay        O - Open');
  writeln(' F - Fast/slow');
  writeln;
  writeln(' M - Movement (point to point)');

  { Adjust menu based on the mode we are in }
  if robot_mode = edit_prog
  then begin
    writeln;
    writeln(' R - Remove point from file');
    writeln(' L - Load next point');
    writeln(' U - Upward (previous) point');
  end;

  any_Char := readkey;

  getkey := any_char;

  win_down:

       win1.done;

end;