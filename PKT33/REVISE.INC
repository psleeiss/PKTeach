procedure revise;

{ This procedure handles the revising of a program }

label alldone;

var
  W,win1             : WindowPtr;
  any_char           : char;
  finished           : boolean;
  limit_err          : char;
  dummy_boolean      : boolean;
  error_occured      : boolean;
  noext              : string;
  filename           : string;
  Redraw,
  valid_filename     : boolean;
  load_command_error : boolean;
  command            : string;
  file1              : pk_file;
  title, trailer     : string;
  I                  : integer;
  wnum, key          : word;

begin
  error_occured := false;
  need_save     := false;  { Set to true if program file was changed }

  { Copy protection check }
  if everlock.check_copy_protection <> passed_protection_check
  then security_msg;

  { See if the robot is in the zero position if we are not in MOVE }
  robowrit('N');
  roboinit(abs_pos);
  roboinit(rel_pos);
  roboinit(com_pos);
  command      := '';
  if numlock = true then
    numlocch;
  if robot_mode <> move_only
  then if not zquest
       then exit;

  { If we have entered this procedure because the user selected "M" (move) }
  { off of the main menu, then simply give them the movement screens and   }
  { then exit.                                                             }
  if robot_mode = move_only
  then begin
    { Display the background window }
    win[coverup]^.draw;
    { Display the status windows }
    updtabsr(abs_pos);
    rangeup;
    updtrelr(rel_pos);
    updtcomr(' ');
    {Handle movement of axes }
    if MouseInstalled then
      begin
        if pendentmode then
          pendent
        else rvbmenu;
      end
    else rvbmenu;
    { Return the robot to the home position }
    robostep(robo_steps);
    robowrit('N');

    goto alldone;
  end;

  { Clear the memory-resident linked list of commands to store }
  lstclear;

  if robot_mode = write_new
  then begin

    { Loop until a valid filename is given or exit is signalled }
    valid_filename := false;
    while not valid_filename
    do begin
         { Display window and get filename from user }
         if wnfilenm(filename)
         then begin
           filename := StUpCase(filename) + '.PRG';  { Put in a message for invalid }
           if newfile(file1,filename)                { file name                    }
           then valid_filename := true;
         end
         else exit;
       end;  { While loop }
    if MouseInstalled then
      begin
        if pendentmode then
          pendent
        else revmove(filename);
      end
    else revmove(filename);
    robowrit('N');
  end
  else begin
         { Display list of files if user types '?' or exit if ' ' }
         HiddenCursor;
         { Check for no files found }
         title := ' Program List ';
         if MouseInstalled then
           trailer := 'LEFT to pick, RIGHT to exit'
         else
           trailer := 'Use arrows <ENTER>, ESC to EXIT';
         filename := FilePick(title, trailer);
       {end;}
       if filename = '' then
         exit;
    { Open the file }
    assign(file1,filename);
    if not pkopen(file1,false)
      then begin
             invalfil;
             exit;
           end;

    { Load the file into memory.  We are in edit...cheat and don't let }
    { the user be able to insert before the Z command (could be trouble) }
    fileld(file1);
    if not lstnext
    then begin  end;
    robowrit('Z');

    if MouseInstalled then
      begin
        if pendentmode then
          pendent
        else revmove(filename);
      end
    else revmove(filename);
    robowrit('N');
  end;  { Else clause }
(*  if (need_save) or
     (robot_mode = write_new)
  then begin *)
    if savechng = true then
      begin
        rewrite(file1);
        filestor(file1);
        close(file1);
      end
    else if robot_mode = write_new then
    {$I-} erase(file1) {$I+};
(*  end; *)

  { Pop all of the windows off the windows stack }
alldone:
  win[com]^.select;
  win[com]^.erase;
  win[relr]^.select;
  win[relr]^.erase;
  win[range]^.select;
  win[range]^.erase;
  win[absr]^.select;
  win[absr]^.erase;
  win[coverup]^.select;
  win[coverup]^.erase;

end;