procedure updtcomr( com_str : string);


{ This procedure displays the current command in the command window }

begin

  { Remove the cursor }
  HiddenCursor;
  If MouseInstalled then
    HideMouse;
  win[com]^.wFrame.AddHeader(' Robot Command ',heTC);
  win[com]^.Select;

  { Display the command }
  clrscr;
  gotoxy(5,1);
  write(com_str);

end;