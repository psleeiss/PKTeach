{$F+}
unit robot2;

{ This unit contains all of the necessary code for the teach program for }
{ the robot.                                                             }

interface
uses
  Dos,
  OpDos,
  OpDate,
  OpDir,
  OpCrt,
  misc,
  OPColor,
  OpString,
  opframe,
  opmouse,
  opwindow,
  wins,
  scrnproc,
  filing,
  Di,
  sounds,
  everobj;


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

{public declarations }
{$I robopbdf.inc}
{$I roboprdf.inc}


{ Public variable declarations }
const
  window_down = 0;
  printer_1   = 0;
  printer_2   = 1;

var
  pk_version    : string;    { Software version number }
  printer_number: byte;      { 0 means LPT1, 1 means LPT2 }

  robot_rel_win : word;      { Used to tell whether window is up }
  robot_abs_win : word;      { Used to tell whether window is up }
  robot_com_win : word;
  rel_pos       : robot_pos;  { Tracks the robot's position rel to last point }
  abs_pos       : robot_pos;  { Tracks the robot's absolute position (from nest) }
  com_pos       : robot_pos;  { Don't remember what this is }
  max_ranges    : robot_pos;   { Maximum range a motor can move }
  robo_steps    : robot_pos;   { Current step increment for robot motors }

  need_save     : boolean;    { Used during "edit" to see if changes made }
  robot_mode    : pkteach_mode;


{ This procedure informs the user that no commands can be deleted }
procedure delnocom;

{ This procedure displays an error message stating that the user has selected }
{ the "load from file" command when the file is at the EOF condition.         }
procedure eofcom;

{ This procedure displays an error message stating that the user has selected }
{ the "load prev com from file" command when the file is at the TOF condition.}
procedure tofcom;

{ This procedure takes as input a string, and then proceeds to insert a }
{ robot command into the mem-resident linked list using the absolute    }
{ position coordinates and the input string to build a command structure }
procedure fileit( in_str : string );

{ This procedure displays a warning message to the user about the NUM-LOCK }
{ key being set. }
procedure numlocch;

{ This function writes a command to the robot }
procedure robowrit ( command : string);

{ This function determines how many seconds the time delay should be }
function tdelay( var command : string) : boolean;

{ This function determines how many seconds the time delay should be }
function speed( var command : string) : boolean;

{ This function verifies that the user wants to nest the robot }
function nest : boolean;

{ Get a yes or no response from the user }
function yorn : boolean;

{ Get an integer from the user }
function getint : integer ;

{ Get an integer from the user...exit on 'X' }
function xgetint : integer;

{ This function explains that the user has just attempted to back out of the
{ menu without saving his program and does he want to save the point.   }
function savechk : boolean;

{ This function verifies that the user wants to close the gripper }
function gripclos : boolean;

{ This function verifies that the user wants to open the gripper }
function gripopen : boolean;

{ This function explains to the user that they need to have the robot zeroed
{ and asks them if they have taken care of it .                   }
function zquest : boolean;

{ This function explains to the user just what the ZERO command does and asks }
{ him/her to verify that this is what they really want.                       }
function zverify : boolean;

{ This function displays a popup-menu and querries the user to find out if }
{ the robot has been "zeroed".  If yes, the function returns a TRUE value. }
{ Otherwise it will return with a value of FALSE. }
function iszero : boolean;

{ This procedure displays the "moveit" window for the base }
procedure basemoit;

{ This procedure displays the "moveit" window for the shoulder }
procedure sholmoit;

{ This procedure displays the "moveit" window for the shoulder }
procedure elbomoit;

{ This procedure displays the "Max Ranges" window }
procedure rangeup;

{ This procedure displays the "moveit" window for the wrist roll }
procedure rollmoit;

{ This procedure displays the "moveit" window for the wrist pitch }
procedure pitcmoit;

{ This procedure displays the "moveit" window for the gripper }
procedure gripmoit;

{ This procedure is like the DOSDIR procedure in MISC unit except that it }
{ can halt the screen display if the SCROLL-LOCK key is down, and it auto-}
{ matically will give a directory of *.PRG .               }
procedure dirprg;

{ This procedure informs the user that they have entered an invalid filename }
procedure invalfil;

{ This procedure informs the user that an invalid command has been read }
procedure invalcom;

{ This procedure informs the user that they have entered an duplicate filename }
procedure dupfname;

{ This function creates a new file for the user to write commands into. }
{ If it cannot create the file, then it returns a value of false.       }
function newfile(var afile    : pk_file;
                     filename : string) : boolean;

{ This procedure initializes a robot_pos structure }
procedure roboinit ( var robot : robot_pos);

{ This procedure adds a robot position point to the global variable FILE1
{ which must have been already openned.  It also will give a confirmation
{ that the point was saved or that no movement took place. It also resets
{ com_pos and rel_pos structures (due to the fact that they should now
{ be zeroed out.  }
procedure addpt;

{ This function processes a command given by the input string.  If the string
{ cannot be processed for any reason, the function returns a value of false.
{ If the function returns false AND limit_err is not blank, that means that the
{ requested operation would take an axis past it's limit.  The axis that would
{ Be exceeded is returned in limit.  It is the first character of the axis name.  }
function proccom(     in_str    : string;
                  var limit_err : char) : boolean;

{ This procedure informs the user that the robot's arm has gone out of range }
procedure rangeout(axis : char);

{ This function will popup a menu and querry the user for a filename. }
{ The user may call for a directory from here, and the user may back  }
{ out by hitting escape.  If escape is hit, the function will return  }
{ a value of false.  Otherwise, the filename is returned in parameter }
{ and the function returns a value of true.                           }
function wnfilenm( var filename : string) : boolean;

{ This procedure initializes the robots max range structure }
procedure robomrng ( var robot : robot_pos);

{ This procedure initializes the robot step increments structure }
procedure robostep ( var robot : robot_pos);

{ This function returns TRUE if the user wishes to save his/her changes }
function savechng : boolean;

{ This procedure updates the robot's current position relative to zero window }
{ Note that the structure being displayed is a private global structure. }
procedure updtabsr( robot : robot_pos);

{ This procedure updates the robot's current position relative to the }
{ last point recorded.                                                }
procedure updtrelr( robot      : robot_pos);

{ This procedure displays the current command in the command window }
procedure updtcomr( com_str : string);

{ This procedure adds a robot position point to the global variable FILE1
{ which must have been already openned.  It also will give a confirmation
{ that the point was saved or that no movement took place. It also resets
{ com_pos and rel_pos structures (due to the fact that they should now
{ be zeroed out.  }
procedure raddpt;

{ This function receieves as input a PK_PTR variable and will then return in
{ the variable COMMAND a string which contains the necessary command to
{ bring the robot to the state stored in the in_ptr^ variable.  If the function
{ returns a value of TRUE, then the processing occured without any problems.   }
function pktostr(    in_ptr  : pk_ptr;
                 var command : string) : boolean;

{ This function takes as input a pointer to a pk_structure (as in PKTEACH file
{ structure) and converts it into a command string to be passed to PROCCOM }
function revert( in_com : pk_ptr) : string;

{ This function returns TRUE if an OPEN command should be added after the  }
{ current command.  If the previous command does not have the gripper      }
{ completely open, and the current or following commands are not "OPEN"    }
{ commands, and the current command needs the gripper all the way open,    }
{ then this function returns true.                                         }
function addopen : boolean;

{ This function returns TRUE if a CLOSE command should be added after the }
{ current command.  Basically, if the previous command did not have the gripper }
{ completely closed, and the current command does, and the current command }
{ and the next command are not CLOSE commands, then the function returns true. }
function addclose : boolean;
function pendentmode : boolean;

{ Displays the proper message for a copy protection error and then halts }
procedure security_msg;

implementation

{$I addopen.inc}
{$I addclose.inc}
{$I fileit.inc}
{$I eofcom.inc}
{$I tofcom.inc}
{$I numlocch.inc}
{$I rangeup.inc}
{$I robowrit.inc}
{$I tdelay.inc}
{$I speed.inc}
{$I nest.inc}
{$I yorn.inc}
{$I getint.inc}
{$I xbufinpt.inc}
{$I xgetint.inc}
{$I savechng.inc}
{$I invalcom.inc}
{$I rangeout.inc}
{$I delnocom.inc}
{$I savechk.inc}
{$I gripclos.inc}
{$I gripopen.inc}
{$I zquest.inc}
{$I zverify.inc}
{$I iszero.inc}
{$I seratio.inc}
{$I swratio.inc}
{$I ewratio.inc}
{$I revert.inc}
{$I pktostr.inc}
{$I basemoit.inc}
{$I sholmoit.inc}
{$I elbomoit.inc}
{$I rollmoit.inc}
{$I pitcmoit.inc}
{$I gripmoit.inc}
{$I comparse.inc}
{$I dirprg.inc}
{$I invalfil.inc}
{$I dupfname.inc}
{$I newfile.inc}
{$I roboinit.inc}
{$I addpt.inc}
{$I proccom.inc}
{$I dosdirwn.inc}
{$I wnfilenm.inc}
{$I robomrng.inc}
{$I robostep.inc}
{$I updtabsr.inc}
{$I updtrelr.inc}
{$I updtcomr.inc}
{$I raddpt.inc}
{$I pendentm.inc}

{ This procedure is called in PK Teach when a copy protection check fails.
  It will examine the last return code, print an appropriate message, and
  then shut down the program (halt).  }
procedure security_msg;
var
  security_file : text;    { For output of error code }
begin
  window(1,1,screenwidth,screenheight);
  textattr := 15;
  hiddencursor;
  clrscr;
  framewindow(1,1,screenwidth,screenheight,7,7,' Copy Protection Violation! ');

  fasttext('A copy protection check against this copy of your program failed',5,5);
  fasttext('due to the following reason:',6,5);

  case everlock.get_last_result of
    0: begin
         fasttext('A programming error in PK Teach has caused this embarrassing',8,5);
         fasttext('message to be displayed at the wrong time.  Sorry about that.',9,5);
       end;
    invalid_scb_error
     : begin
         fasttext('The copy protection data structure in memory has been corrupted.',8,5);
       end;
    not_enough_memory_error
     : begin
         fasttext('There is insufficient memory available for performing a',8,5);
         fasttext('copy protection check.',9,5);
       end;
    else begin
      fasttext('A general copy protection error occurred. This means that ',8,5);
      fasttext('you have most likely failed to install the program properly.',9,5);
      fasttext('You would also see this message if you are using an unauthorized',11,5);
      fasttext('copy of PK Teach.',12,5);
    end;
  end; { Case Statement }

  fasttext('Be certain that you have correctly installed this software.',15,5);
  fasttext('Program ending.................Press any key....',19,5);

  if readkey ='' then;
  normalcursor;
  textattr := 7;
  clrscr;

  {$I-}
  assign(security_file,'Security.bad');
  rewrite(security_file);
  writeln(security_file,todaystring('mm/dd/yyyy'));
  writeln(security_file,currenttimestring('hh:mm:ss te'));
  writeln(Security_file,'Security Return Code = ',
          long2str(everlock.get_last_result));
  close(security_file);
  if ioresult <> 0 then;
  {$I+}

  halt(2);
end;

begin
  robot_rel_win := window_down;
  robot_abs_win := window_down;
  robot_com_win := window_down;
  roboinit(rel_pos);
  roboinit(abs_pos);
  roboinit(com_pos);
  robomrng(max_ranges);
  robostep(robo_steps);

  printer_number := printer_1;

end.