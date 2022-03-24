{$F+}
{$I OPDEFINE.INC}

unit robot;

{ This unit contains all of the necessary code for the teach program for }
{ the robot.                                                             }

interface

uses
  Dos,
  graph,
  OpDos,
  OpInLine,
  OpString,
  OpRoot,
  OpCrt,
  OpCmd,
  OpMouse,
  OpColor,
  opframe,
  OpWindow,
  opdir,
  OpPick,
  Di,
  wins,
  misc,
  scrnproc,
  robot2,
  OpMenu,
  filing,
  everobj,
  sounds;


{$IFDEF UseMouse}
const
   MouseChar : Char = #04;
{$ENDIF}


{Color set used by menu system}
const

  MenuColors : ColorSet = (
    TextColor       : YellowOnBlue;       TextMono        : LtGrayOnBlack;
    CtrlColor       : YellowOnBlue;       CtrlMono        : WhiteOnBlack;
    FrameColor      : CyanOnBlue;         FrameMono       : LtGrayOnBlack;
    HeaderColor     : WhiteOnCyan;        HeaderMono      : BlackOnLtGray;
    ShadowColor     : DkGrayOnBlack;      ShadowMono      : WhiteOnBlack;
    HighlightColor  : WhiteOnRed;         HighlightMono   : BlackOnLtGray;
    PromptColor     : BlackOnCyan;        PromptMono      : LtGrayOnBlack;
    SelPromptColor  : BlackOnCyan;        SelPromptMono   : LtGrayOnBlack;
    ProPromptColor  : BlackOnCyan;        ProPromptMono   : LtGrayOnBlack;
    FieldColor      : YellowOnBlue;       FieldMono       : LtGrayOnBlack;
    SelFieldColor   : BlueOnCyan;         SelFieldMono    : WhiteOnBlack;
    ProFieldColor   : LtGrayOnBlue;       ProFieldMono    : LtGrayOnBlack;
    ScrollBarColor  : CyanOnBlue;         ScrollBarMono   : LtGrayOnBlack;
    SliderColor     : CyanOnBlue;         SliderMono      : WhiteOnBlack;
    HotSpotColor    : BlackOnCyan;        HotSpotMono     : BlackOnLtGray;
    BlockColor      : YellowOnCyan;       BlockMono       : WhiteOnBlack;
    MarkerColor     : WhiteOnMagenta;     MarkerMono      : BlackOnLtGray;
    DelimColor      : BlueOnCyan;         DelimMono       : WhiteOnBlack;
    SelDelimColor   : BlueOnCyan;         SelDelimMono    : WhiteOnBlack;
    ProDelimColor   : BlueOnCyan;         ProDelimMono    : WhiteOnBlack;
    SelItemColor    : YellowOnCyan;       SelItemMono     : BlackOnLtGray;
    ProItemColor    : LtGrayOnBlue;       ProItemMono     : LtGrayOnBlack;
    HighItemColor   : WhiteOnBlue;        HighItemMono    : WhiteOnBlue;
    AltItemColor    : WhiteOnBlue;        AltItemMono     : WhiteOnBlack;
    AltSelItemColor : WhiteOnCyan;        AltSelItemMono  : BlackOnLtGray;
    FlexAHelpColor  : WhiteOnBlue;        FlexAHelpMono   : WhiteOnBlack;
    FlexBHelpColor  : WhiteOnBlue;        FlexBHelpMono   : WhiteOnBlack;
    FlexCHelpColor  : LtCyanOnBlue;       FlexCHelpMono   : BlackOnLtGray;
    UnselXrefColor  : YellowOnBlue;       UnselXrefMono   : LtBlueOnBlack;
    SelXrefColor    : WhiteOnMagenta;     SelXrefMono     : BlackOnLtGray;
    MouseColor      : WhiteOnRed;         MouseMono       : BlackOnLtGray
  );

{Menu item constants for menu in Revise}
const
  miGripper1      = 1;
  miOpen2         = 2;
  miClose3        = 3;
  miDelay4        = 4;
  miFastSlow5     = 5;
  miNest6         = 6;
  miMovement7     = 7;
  miLoad8         = 8;
  miUpwardPrev9   = 9;
  miRemove10      = 10;
  miExit11        = 11;

{Menu item constants for axis menu}
const
  miBase1         = 1;
  miShoulder2     = 2;
  miElbow3        = 3;
  miRollWrist4    = 4;
  miPitchWrist5   = 5;
  miGripper6      = 6;
  miAddpoint7     = 7;
  miZero8         = 8;
  miExit9         = 9;

var
  REV, RVB           : Menu;
  limit_err          : char;
  command            : string;
  error_occured,
  load_command_error : boolean;

{public declarations }

{ Display the title screen }
procedure copyrght;

{ Display the title screen }
procedure title;
procedure title2;
{ This is the main procedure for the PK Teach program }
{procedure robomain;}  { Main Menu Revised 5/9/90. Now PKTmain.tpu }
procedure prodinf;
procedure dosdirwn;
function pkexit : boolean;
function delcon(filename : string) : char;
function remcon : char;
procedure noprogs;
function verfexit : char;
procedure writeit(axis : char);
procedure exeprog;
procedure delprog;
function InitRVB(var RVB : menu) : word ;
procedure revise;
procedure pktoasc;
procedure dirprg;
function InitMenu2(filename : string; var REV : Menu) : Word;
procedure revmove(filename : string);
procedure RVBMenu;
function dblclick(click1 : word) : boolean;
procedure pendent;
procedure pendent2;
procedure pendent3;

implementation

{ The following variables used by WRITEIT }
var
  TPI         : Byte;  {Top Index}
  BottomIndex : Byte;


{$I title.inc}
{$I title2.inc}
{$I copyrght.inc}
{$I prodinf.inc}
{$I dosdirwn.inc}
{$I pkexit.inc}
{$I delcon.inc}
{$I remcon.inc}
{$I noprogs.inc}
{$I verfexit.inc}
{$I exeprog.inc}
{$I delprog.inc}
{$I writeit.inc}
{$I revise.inc}
{$I pktoasc.inc}
{$I dirprg.inc}
{$I dblclick.inc}
{$I pendent.inc}
{$I pendent2.inc}
{$I pendent3.inc}

function InitMenu2(filename : string; var REV : Menu) : Word;
  {-Initialize menu system generated by MAKEMENU}
const
  {Frame constants}
  Frame1 = '’‘∏æÕÕ≥≥';
  Frame2 = '…»ªºÕÕ∫∫';

var
  title    : string;
  any_char : char;

begin
  with REV do begin
    if not InitCustom(3, 13, 26, 23, MenuColors,
                      wBordered+wClear+wUserContents,
                      Vertical) then begin
      InitMenu2 := InitStatus;
      Exit;
    end;
    mnOptionsOn(mnAlphaMatch+(*mnSelectOnMatch+*)mnArrowSelect+mnPopOnSelect+mnAllHotSpots+mnSelectOnClick);
    mnOptionsOff(mnAllowPending+mnUseItemForTopic+mnSelectOnMatch);
    wFrame.SetFrameType(Frame1);
    if robot_mode = edit_prog then
      AddHeaderColor(' Editing '+filename+' ', heTC, BlackOnLtGray, BlackOnLtGray)
    else
      AddHeaderColor(' Writing '+filename+' ', heTC, BlackOnLtGray, BlackOnLtGray);
      AddItem('     Gripper', 1, 6, miGripper1);
      AddFramedSubMenu(20, 14, 28, 15, Vertical, Frame2);
      SetSelectAttr(BrownOnLtGray, BrownOnLtGray);
      SetHighAttr(YellowOnBlack, YellowOnBlack);
      SetFrameAttr(DkGrayOnBlue, DkGrayOnBlue);
      AddItem(' Open', 1, 2, miOpen2);
      AddItem(' Close', 2, 2, miClose3);
      ItemsDone;
    AddItem('     Delay', 2, 6, miDelay4);
    AddItem('     Fast/Slow', 3, 6, miFastSlow5);
    AddItem('     Nest', 4, 6, miNest6);
    AddItem('     Movement', 6, 6, miMovement7);
    if robot_mode = edit_prog then
      begin
        AddItem('Load next point', 8, 1, miLoad8);
        AddItem('Upward(previous)point', 9, 1, miUpwardPrev9);
        AddItem('Remove point from file', 10, 1, miRemove10);
      end;
    AddItem('     Exit', 11, 7, miExit11);
    ItemsDone;
    InitMenu2 := GetLastError;
  end;
end;


function InitRVB(var RVB : menu) : Word;
  {-Initialize menu system generated by MAKEMENU}
const
  {Frame constants}
  Frame1 = '’‘∏æÕÕ≥≥';

var
  Status : Word;

begin
  with RVB do begin
    if not InitCustom(3, 14, 22, 23, MenuColors,
                      wBordered+wClear+wUserContents,
                      Vertical) then begin
      status := InitStatus;
      Exit;
    end;
    mnOptionsOn(mnAlphaMatch+mnSelectOnClick+mnArrowSelect+mnAllHotSpots);
    mnOptionsOff(mnAllowPending+mnPopOnSelect+mnUseItemForTopic+mnSelectOnMatch);
    wFrame.SetFrameType(Frame1);
    AddItem('Base', 1, 1, miBase1);
    AddItem('Shoulder', 2, 1, miShoulder2);
    AddItem('Elbow', 3, 1, miElbow3);
    AddItem('Roll(wrist)', 4, 1, miRollWrist4);
    AddItem('Pitch(wrist)', 5, 1, miPitchWrist5);
    AddItem('Gripper', 6, 1, miGripper6);
    if robot_mode <> move_only then
      AddItem('Addpoint to file', 8, 1, miAddpoint7)
    else if robot_mode = move_only then
      AddItem('Zero the robot', 8, 1, miZero8);
    AddItem('Exit', 10, 2, miExit9);
    ItemsDone;

    {SetErrorProc(ErrorHandler);}
    {MenuCommands.SetHelpProc(DisplayHelp);}
    {SetCustomStringProc(CustomizeItemString);}

    InitRVB := GetLastError;
  end;
end;

procedure revmove(filename : string);

var
  win                  : WindowPtr;
  WinOpts              : Longint;
  Status               : Word;
  REV                  : Menu;      {menu system}
  error_occured,
  load_command_error,
  finished             : boolean;
  limit_err,
  any_char             : char;
  command              : string;

begin
  WinOpts := wBordered+wClear;
  ClrScr;
  Status := InitMenu2(filename,REV);
    if Status <> 0 then begin
    WriteLn('Error initializing menu: ', Status);
    Halt(1);
  end;

  {$IFDEF UseMouse}
  if MouseInstalled then
    with MenuColors do begin
      {activate mouse cursor}
      SoftMouseCursor($0000, (ColorMono(MouseColor, MouseMono) shl 8)+
                             Byte(MouseChar));
      MouseWindow(3, 13, 26, 24);
      ShowMouse;
      {enable mouse support}
      MenuCommands.cpOptionsOn(cpEnableMouse);
    end;
  {$ENDIF}
  roboinit(abs_pos);
  roboinit(rel_pos);
  roboinit(com_pos);
  robostep(robo_steps);
  updtabsr(abs_pos);
  rangeup;
  updtrelr(rel_pos);
  updtcomr('Z');
  finished := false;
  repeat
  REV.Draw;
  REV.Process;
  REV.Erase;
  {Skeleton for menu choice handling}
  if REV.GetLastCommand = ccSelect then
    case REV.MenuChoice of
      miClose3        : if gripclos
                        then begin
                        if not proccom('C',limit_err)
                        then begin
                        writeln('Could not process the command!!!');
                        halt(1);
                        end;
                        updtabsr(abs_pos);
                        updtrelr(rel_pos);
                        roboinit(rel_pos);
                        roboinit(com_pos);
                        updtcomr('C');
                        fileit('C');
                        if robot_mode = edit_prog
                        then need_save := true;
                        end;
      miOpen2         : if gripopen
                        then begin
                        if not proccom('O',limit_err)
                        then begin
                        writeln('Could not process the command!!!');
                        halt(1);
                        end;
                        updtabsr(abs_pos);
                        updtrelr(rel_pos);
                        roboinit(rel_pos);
                        roboinit(com_pos);
                        updtcomr('O');
                        fileit('O');
                        if robot_mode = edit_prog
                        then need_save := true;
                        end;
      miDelay4        : if tdelay(command)
                        then begin
                        if not proccom(command,limit_err)
                        then begin
                        writeln('Could not process the command!!!');
                        halt(1);
                        end;
                        updtcomr(command);
                        fileit(command);
                        if robot_mode = edit_prog
                        then need_save := true;
                        end;
      miFastSlow5     : if speed(command)
                        then begin
                        if not proccom(command,limit_err)
                        then begin
                        writeln('Could not process the command!!!');
                        halt(1);
                        end;
                        updtcomr(command);
                        fileit(command);
                        if robot_mode = edit_prog
                        then need_save := true;
                        end;
      miNest6         : if nest
                        then begin
                        if not proccom('N',limit_err)
                        then begin
                        writeln('Could not process the command!!!');
                        halt(1);
                        end;
                        updtabsr(abs_pos);
                        updtrelr(rel_pos);
                        roboinit(rel_pos);
                        updtcomr('N');
                        fileit('N');
                        if robot_mode = edit_prog
                        then need_save := true;
                        end;
      miMovement7     : rvbmenu;
      miRemove10      : if robot_mode = edit_prog
                        then begin

                        if cur_ptr = nil
                        then delnocom
                        else begin
                               if remcon = 'Y'
                                  then begin

                                { Delete the command }
                                  lstdel;
                                  if robot_mode = edit_prog
                                  then need_save := true;
                                  if cur_ptr <> nil
                                  then begin

                                  { Find the needed robot command }
                                    command := revert(cur_ptr);

                                if not proccom(command,limit_err)
                                    then begin
                                    if limit_err <> ' '
                                    then rangeout(limit_err)
                                else invalcom;
                                end
                           end(*;*)
                           else command := ' ';

                   { Update and all that jazz }
                   roboinit(com_pos);
                   roboinit(rel_pos);
                   updtabsr(abs_pos);
                   updtrelr(rel_pos);
                   updtcomr(command);
                 end;
              end;
            end;
      miUpwardPrev9,
      miLoad8         : if robot_mode = edit_prog
                         then begin
                           { See if this is a load next or load previous }
                           load_command_error := false;
                           if REV.MenuChoice = 8
                           then begin

                             if not lstnext
                             then begin
                               eofcom;
                               load_command_error := true;
                             end;
                           end
                           else begin
                             if not lstprev
                             then begin
                               tofcom;
                               load_command_error := true;
                             end;
                           end;

                           if not load_command_error
                           then begin

                             need_save := true;
                             { Process the command }
                             if not pktostr(cur_ptr,command)
                             then begin
                               invalcom;
                               exit;
                             end;

                             { If we are "backing up", force to go to last position }
                             if REV.MenuChoice = 9
                             then command := revert(cur_ptr);

                             { Display the command in the command window }
                             updtcomr(command);

                             { Process the command }
                             if not proccom(command,limit_err)
                             then begin
                               if limit_err <> ' '
                               then rangeout(limit_err)
                               else begin
                                 invalcom;
                                 error_occured := true;
                                 finished := true;
                               end;
                             end
                             else begin

                               case command[1] of
                                 'C': begin
                                        updtabsr(abs_pos);
                                        updtrelr(rel_pos);
                                        roboinit(rel_pos);
                                        roboinit(com_pos);
                                      end;
                                 'D': begin end;
                                 'M': begin
                                        updtabsr(abs_pos);
                                        updtrelr(rel_pos);
                                        roboinit(com_pos);
                                        roboinit(rel_pos);
                                        HiddenCursor;
                                      end;
                                 'N': begin
                                        updtabsr(abs_pos);
                                        updtrelr(rel_pos);
                                        roboinit(rel_pos);
                                      end;
                                 'O': begin
                                        updtabsr(abs_pos);
                                        updtrelr(rel_pos);
                                        roboinit(rel_pos);
                                        roboinit(com_pos);
                                      end;
                                 'S': begin end;
                                 'Z': begin
                                        updtabsr(abs_pos);
                                        updtrelr(rel_pos);
                                      end;
                                   else begin
                                     {win[1]^.Select;}
                                     writeln('Bad news from REVISE.INC.  No valid command');
                                     finished := true;
                                   end;
                               end;  { Case statement }
                             end;  { Else clause from proccom }
                           end;   { Then clause (not load_command_error) }
                         end;   { Case statement portion }

                miexit11        : if verfexit = 'Y'
                                  then finished := true
                                  else finished := false;

            end;
  until finished;

  FullMouseWindow;
  REV.select;
  REV.Done;

  {$IFDEF UseMouse}
  HideMouse;
  {$ENDIF}
end;


procedure RVBMenu;  { Axis movement menu }

var

  Status   : Word;
  RVB      : Menu;      { Axis menu system }
  finished : boolean;
  Ichar,
  any_char : char;

begin
  ClrScr;

  Status := InitRVB(RVB);
  if Status <> 0 then begin
    WriteLn('Error initializing menu: ', Status);
    Halt(1);
  end;

  {$IFDEF UseMouse}
  if MouseInstalled then
    with MenuColors do begin
      {activate mouse cursor}
      SoftMouseCursor($0000, (ColorMono(MouseColor, MouseMono) shl 8)+
                             Byte(MouseChar));
      MouseWindow(3, 14, 22, 24);
      ShowMouse;
      {enable mouse support}
      MenuCommands.cpOptionsOn(cpEnableMouse);
    end;
  {$ENDIF}
  updtabsr(abs_pos);
  rangeup;
  updtrelr(rel_pos);
  updtcomr(' ');
  finished := false;
  repeat
  RVB.Draw;
  RVB.Process;
  RVB.Erase;

  if RVB.GetLastCommand = ccSelect then
    case RVB.MenuChoice of

      miBase1         : writeit('B');

      miShoulder2     : writeit('S');

      miElbow3        : writeit('E');

      miRollWrist4    : writeit('R');

      miPitchWrist5   : writeit('P');

      miGripper6      : writeit('G');

      miAddpoint7     : if robot_mode <> move_only
                        then begin
                               raddpt;
                               updtrelr(rel_pos);
                               need_save := true;
                               end;
      miZero8         : if robot_mode = move_only
                        then if zverify
                        then begin
                               robowrit('Z');
                               roboinit(abs_pos);
                               roboinit(rel_pos);
                               roboinit(com_pos);
                               updtabsr(abs_pos);
                               updtrelr(rel_pos);
                             end;
      miExit9          : begin
                           finished := true;
                           if robot_mode = move_only
                           then if verfexit = 'Y'
                                then finished := true
                                else finished := false;
                         (*  finished := true;
                           if robot_mode <> move_only
                           then begin
                                  if (rel_pos.base <> 0) or
                                  (rel_pos.shoulder <> 0) or
                                  (rel_pos.elbow <> 0) or
                                  (rel_pos.wrist_r <> 0) or
                                  (rel_pos.wrist_p <> 0) or
                                  (rel_pos.gripper <> 0)
                           then if savechk
                           then raddpt
                           else if cur_ptr = nil   { If cur_ptr is NIL, then no points saved yet }
                           then robowrit('N')
                           else begin
                                  command := revert(cur_ptr);
                                  if not proccom(command,limit_err)
                                  then begin
                                         whistle;
                                         writeln('Fatal Error from RVBWRITE!');
                                         delay(1000);
                                         halt(1);
                                       end;
                                end;
                                end; *)
                         end;
  end;

  until finished;

  FullMouseWindow;
(*  updtabsr(abs_pos);
  updtrelr(rel_pos);*)

(*  RVB.Erase;*)
  RVB.Done;
  {$IFDEF UseMouse}
  HideMouse;
  {$ENDIF}
end;
end.


