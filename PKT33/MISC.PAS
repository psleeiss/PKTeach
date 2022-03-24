{$F+}
unit misc;

{                  Copyright (C) 2022 by Peter S. Lee                   }
{                             All Rights Reserved.                      }

{ This unit contains several general purpose routines that just don't fit }
{ under any other heading very well, or not at all!                       }

{$O+}

interface
uses dos,opcrt,OpDir,OpWindow,sounds;

{$I miscdef.inc}

{ This function writes a command to the printer.  Note that the BIOS printer }
{ services are used to send characters out to the printer port.  This is   }
{ done to avoid a "printer timeout" error which can occur using Pascal's   }
{ WRITELN(prn,string) statement if there is a problem with the printer.  }
{ Basically, the BIOS routines are used so that we can "trap" a }
{ printer timeout without the program coming to a halt. }
procedure biosprnt ( command : string);

{ Remover leading and trailing blanks from any string }
procedure blnkchop( var in_str );

{ Returns TRUE if a string (any size) is blank or null }
function blnkstr( var in_str) : boolean;

{ This function tells whether or not the cap-lock key is set.  True means set }
function caplock : boolean;

{ This function is passed a structure that contains the date in "date_def" }
{ record format, and returns a string[8] value that is MM/DD/YY.           }
function datestr(today : date_def) : str8;

{ This function deletes the given file from the disk.  If all goes well, the }
{ function returns true.  Otherwise, it will return false.                 }
function delfile ( filename : string ) : boolean;

{ Disable interrupts }
procedure disable;

{ Display a file from disk created by screen-builder }
procedure dispscrn( scrnname : str66);

{ Querry user for mask and then present a DOS DIRECTORY }
procedure dosdir;

{ Display a portion of a character array }
procedure dspchrar( var char_arr ;
                        arr_len  : byte);

{ Enable interrupts }
procedure enable;

{ This function checks to see if the given file name (which may include a }
{ pathname) exists or not.  If it exists, the function returns TRUE.      }
function filexist( filename : string) : boolean;

{ Get a byte from the keyboard without I/O errors }
function getbyte : byte;

{ This procedure returns the date as strings instead of words (Pascal GETDATE) }
procedure getdates( var year_str        : string;
                    var month_str       : string;
                    var day_str         : string;
                    var day_of_week_str : string);

{ Get an integer from the keyboard without I/O errors }
function getintg : integer ;

{ Get a real from the keyboard without I/O errors }
function getreal : real;

{ Get a Y or N response from the keyboard without I/O errors }
function getyesno : char;

{ This function takes any integer and converts it to a string }
function inttostr( in_integer : longint) : string;

{ This procedure is called to flush the keyboard buffer.  One would typically }
{ Use it just before a keyboard input routine where buffered input is not
{ practical or desired. It uses BIOS interrupt 22 dec (16 hex) services. }
procedure keyflush;

{ This function tells whether or not the numlock key is set.  True means set }
function numlock : boolean;

{ Get one keystroke from the user, do not allow extended keystrokes }
function onekey : char;

{ Open a file on disk with option to create if not found }
function openfile( var data_file : file;
                       create    : boolean) : boolean;

{ Function:         OPENTEXT
{
{ Programmer:       Peter S. Lee                Date: Oct 2, 1987
{
{ Purpose:          To attempt to open a text file.
{
{ Input Parameters:
{    text_file      This is a file variable for the file to be openned.
{
{    create         If this flag is set to TRUE and the text_file cannot be
{                   openned, then this procedure will attempt to create the
{                   file.
{
{ Output Parameters:
{    opendata       The value of the function is TRUE only if the file was
{                   successfully openned.
}
function opentext( var text_file : text;
                       create    : boolean) : boolean;

{ This function tells whether or not the scroll-lock key is set.  True means set }
function scrlock : boolean;

{ Display a screen on any graphics adapter }
procedure scrnup(var a_screen);

{ This procedure sets the CGA border color to the color specified by the }
{ input parameter.                                                       }
procedure setbordr( bord_color : byte );

{ Set a dos path }
procedure setdir(var cur_directory : str66);

{ Convert a string to an integer safely }
function str2intg(     in_string : str66;
                   var answer    : integer) : boolean ;

{ Convert a string to a real safely }
function str2real(     in_string : str66;
                   var answer    : real) : boolean ;

{ This function receives a filename and strips off the extension if one exists }
function strfext( filename : string) : string;

{ Calculate pixel location given text x or y location }
function textpixl( inval : integer) : integer;

{ This function is passed a structure that contains the time in "time_def" }
{ record format, and returns a string[8] value that is HH:MM:SS.           }
function timestr(today : time_def) : str8;

{ Convert a string from lower to upper case }
function upperstr( in_str : string) : string;

{ Get the current video mode }
function vidmode : byte;

{ This function checks a filename to see if it contains wildcards '*' or '?' }
{ If wildcards are present in the name then the function returns TRUE.     }
function wildcard( filename : string) : boolean;

implementation

{ Setup exit code }
var
  exitsave : pointer;


{$I biosprnt.inc}
{$I blnkchop.inc}
{$I blnkstr.inc}
{$I caplock.inc}
{$I datestr.inc}
{$I delfile.inc}
{$I disable.inc}
{$I dispscrn.inc}
{$I dosdir.inc}
{$I dspchrar.inc}
{$I enable.inc}
{$I filexist.inc}
{$I getbyte.inc}
{$I getdates.inc}
{$I getintg.inc}
{$I getreal.inc}
{$I getyesno.inc}
{$I inttostr.inc}
{$I keyflush.inc}
{$I miscexit.inc}
{$I numlock.inc}
{$I onekey.inc}
{$I openfile.inc}
{$I opentext.inc}
{$I scrlock.inc}
{$I scrnshot.inc}
{$I scrnup.inc}
{$I setbordr.inc}
{$I setdir.inc}
{$I str2intg.inc}
{$I str2real.inc}
{$I strfext.inc}
{$I textpixl.inc}
{$I timestr.inc}
{$I upperstr.inc}
{$I vidmode.inc}
{$I wildcard.inc}

begin
  exitsave := exitproc;
  exitproc := @miscexit;

  max_real := 1.7e+37;
  mono_and_color_monitors := false;

end.
