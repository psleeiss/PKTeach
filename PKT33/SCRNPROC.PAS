unit scrnproc;

{ This unit allows the user to process screens.  See the data type SCREEN_BUF }
{ which is used for most of the procedures.                                   }

{$F+}

interface
uses dos,opcrt,misc,sounds;

{ Include the types used }
{$I scrpcdef.inc }

var
  max_blank_string : string[255];

{ Get input from an edit buffer.  Return causes it to end }
procedure buffinpt(    xpos      : integer;    { x position of buffer start }
                       ypos      : integer;    { y position of buffer start }
                       buff_len  : byte;       { Length of buffer           }
                   var data_buff);             { Buffer for data            }


{ This function converts a character array to an integer }
function chr2intg( var in_char         ;
                       chr_len   : byte;
                   var answer    : integer) : boolean ;


{ This function converts a character array to a real }
function chr2real( var in_char         ;
                       chr_len   : byte;
                   var answer    : real) : boolean ;

{ Display and inert screen buffer record }
procedure dspscrbf( screen : screen_buf);

{ Initialize a screen_buf data structure }
procedure initscbf( var screen : screen_buf);

{ Convert an integer to a character array }
procedure inttochr(     in_int : integer;
                    var out_char;
                        char_len : byte);

{ Left justify a character array withing the array }
procedure leftjust(    buff_len : byte;
                   var data_buff        );

{ Do a "readln" fuction with a character array as input variable }
procedure readchar( var data_buf;
                        buff_len : byte);

{ This function handles the input from one buffer from a screen record }
function  scbufinp(    xpos      : integer;    { x position of buffer start }
                       ypos      : integer;    { y position of buffer start }
                       buff_len  : byte;       { Length of buffer           }
                   var data_buff          ;    { Buffer for data            }
                       esc_ok    : boolean;
                       pgup_ok   : boolean;
                       pgdn_ok   : boolean;    { TRUE means key can be used }
                       F1_ok     : boolean;    { to exit the screen.        }
                       F2_ok     : boolean;
                       F3_ok     : boolean;
                       F4_ok     : boolean;
                       F5_ok     : boolean;
                       F6_ok     : boolean;
                       F7_ok     : boolean;
                       F8_ok     : boolean;
                       F9_ok     : boolean;
                       F10_ok    : boolean )
                                 : integer;

{ This function processes in total a screen_buf record }
function scrnprc ( var in_screen : screen_buf) : integer;

{ This procedure does the equivelant of a "WRITE" call with a character array }
procedure writchar( var data_buf;
                        buff_len : byte);

{ This function will verify that a character has a valid yes/no answer }
{ It will also make the buffer contents look prettier if possible.     }
function yesnochk( var in_char         ;
                       chr_len   : byte;
                   var answer    : boolean) : boolean ;



implementation

var
  count              : integer;
  initialized_screen : screen_buf;


{$I buffinpt.inc}
{$I chr2intg.inc}
{$I chr2real.inc}
{$I dspscrbf.inc}
{$I initscbf.inc}
{$I inttochr.inc}
{$I leftjust.inc}
{$I readchar.inc}
{$I scbufinp.inc}
{$I scrnprc.inc}
{$I writchar.inc}
{$I yesnochk.inc}

{ Begin initialization part.  We will initialize a maximum length blank string }
{ and also initialize a screen buffer structure.  The latter is done so that   }
{ when an application program calls the INITSCBUF procedure, all that procedure }
{ needs to do is MOVE the initialized screen buffer structure onto the applica- }
{ tion's structure.  This should tremendously speed up this process.            }

begin

  { Create a maximum length blank string }
  fillchar(max_blank_string,sizeof(max_blank_string),' ');
  max_blank_string[0] := #255;

  { Initialize a screen_buf structure to improve performance of INITSCBUF }
  initialized_screen.num_used := 0;
  initialized_screen.esc_allowed := true;
  initialized_screen.pgup_allowed := false;
  initialized_screen.pgdn_allowed := false;
  initialized_screen.F1_allowed := false;
  initialized_screen.F2_allowed := false;
  initialized_screen.F3_allowed := false;
  initialized_screen.F4_allowed := false;
  initialized_screen.F5_allowed := false;
  initialized_screen.F6_allowed := false;
  initialized_screen.F7_allowed := false;
  initialized_screen.F8_allowed := false;
  initialized_screen.F9_allowed := false;
  initialized_screen.F10_allowed := true;
  initialized_screen.current_buffer := 1;

  for count := 1 to max_scrn_buffers do
  begin
    initialized_screen.buffers[count].len := 0;
    initialized_screen.buffers[count].xpos := 0;
    initialized_screen.buffers[count].ypos := 0;
    initialized_screen.buffers[count].buff_type := 'C';
    initialized_screen.buffers[count].int_buf := 0;
    initialized_screen.buffers[count].real_buf := 0.0;

    { initialize the data buffer }
    move(max_blank_string[1],initialized_screen.buffers[count].data_buff,80);

  end;

end.