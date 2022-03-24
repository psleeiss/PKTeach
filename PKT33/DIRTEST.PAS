program dirtest;

uses
  dos,
  opstring,
  opcrt,
  oproot,
  opdir,
  opcmd,
  OpMouse,
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

 dir.wFrame.AddHeader('The title', heTC);
 dir.wFrame.AddHeader('The trailer', heBC);
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
 dir.setsortorder(sortname);
 dir.setmask('*.zzz', 0);
 dir.PreLoadDirList;
 if dir.GetMatchingFileCount = 0 then
   begin
     HideMouse;
     dir.Done;
     Exit;
   end;
 dir.process;

end.