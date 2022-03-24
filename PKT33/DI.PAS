{$F+}
{$I OPDEFINE.INC}
unit di;

interface

uses
  dos,
  opstring,
  opcrt,
  oproot,
  opdir,
  opcmd,
  {$IFDEF USEMOUSE}
  OpMouse,
  {$ENDIF}
  opcolor,
  opframe,
  opwindow,
  oppick,
  opmenu;


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

  procedure noprogs;
  function filepick(title, trailer : string) : string;

implementation

procedure noprogs;

{ This procedure informs the user that no programs are available }

var
  win       : WindowPtr;
  answer    : word;

begin
  HideMouse;
  New(win, InitCustom(22, 15, 57, 18, Menucolors, wbordered+wClear));
  win^.setcursor(cuhidden);
  win^.wFrame.AddHeader(' Whoops! ', heTC);
  win^.wFrame.AddHeader(' Press any Key ', heBC);
  win^.Draw;

  gotoxy(2,2);
  write(' No programs found on the disk ');
  answer := ReadKeyOrButton;

  win^.Erase;
  dispose(win,done);

end;


function Filepick(title, trailer : string) : string;

var
  dir     : dirlist;
  DiOpts  : Longint;
  file1   : string;
  finished: boolean;
  any_char: char;
  Status  : word;


begin

  DiOpts := wBordered+wClear+wResizeable+wSetMouse;

  if not dir.initcustom(18, 5, 68, 20, MenuColors,
                                       DiOpts,
                                       maxavail,
                                       pickhorizontal,
                                       SingleFile)
   then begin
   writeln(' Failed dirlist, status = ', initstatus);
   halt;
 end;

 dir.wFrame.AddHeader(title, heTC);
 dir.wFrame.AddHeader(trailer, heBC);

{ The following code was commented out because it caused the mouse to
  stop being able to pick elements off of the screen.         }

   if MouseInstalled then
    begin
        InitializeMouse;
        EnableEventHandling;
        SoftMouseCursor($FF00, $7704);
        PickCommands.cpOptionsOn(cpEnableMouse);
        ShowMouse;
    end;
 dir.setposlimits(1,1,screenwidth, screenheight-1);
 dir.diOptionsOn(dioptimizesize);
 dir.pkOptionsOn(pkProcessZero);
 dir.setsortorder(sortname);
 dir.setmask('*.prg', 0);

 dir.PreLoadDirList;
 if dir.GetMatchingFileCount = 0 then
   begin
     HideMouse;
     noprogs;
     FilePick := '';
     dir.Done;
     Exit;
   end;
 finished := false;
 repeat
   dir.Process;
   case dir.GetLastCommand of

     ccSelect :  begin
                   FilePick := TrimSpaces(dir.GetSelectedFile);
                   finished := true;
                 end;

     ccError  : FastWrite('Error '+Long2Str(dir.GetLastError),
                          ScreenHeight,1,Yellow);
     ccQuit   : begin
                  finished := true;
                  FilePick := '';
                end;

     else FastWrite(' ERROR, Inform Your Instructor ', 14, 5, white);
   end;

 until finished;
   FullMouseWindow;
   HideMouse;
   dir.erase;
   dir.Done;

end;
end.



