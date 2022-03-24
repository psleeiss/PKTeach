{$F+}
unit wins;

interface

uses
  OpCrt,
  OpColor,
  OpFrame,
  OpWindow;

{Color set used by PKteach window system}
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

  AbsRel : ColorSet = (
    TextColor    : BlackOnCyan;        TextMono        : LtGrayOnBlack;
    CtrlColor    : WhiteOnMagenta;     CtrlMono        : WhiteOnBlack;
    FrameColor   : YellowOnCyan;       FrameMono       : LtGrayOnBlack;
    HeaderColor  : BlueOnCyan;         HeaderMono      : BlackOnLtGray
  );

  AxColor : ColorSet = (
    TextColor    : WhiteOnMagenta;     TextMono        : LtGrayOnBlack;
    CtrlColor    : WhiteOnMagenta;     CtrlMono        : WhiteOnBlack;
    FrameColor   : YellowOnMagenta;    FrameMono       : LtGrayOnBlack;
    HeaderColor  : LtGrayOnMagenta;    HeaderMono      : BlackOnLtGray
  );

  ComColor : ColorSet = (
    TextColor    : WhiteOnGreen;     TextMono        : LtGrayOnBlack;
    CtrlColor    : YellowOnGreen;    CtrlMono        : WhiteOnBlack;
    FrameColor   : BlackOnGreen;     FrameMono       : LtGrayOnBlack;
    HeaderColor  : BlueOnGreen;    HeaderMono      : BlackOnLtGray
  );

  RangeColor : ColorSet = (
    TextColor    : BlackOnBrown;     TextMono        : LtGrayOnBlack;
    CtrlColor    : YellowOnBrown;    CtrlMono        : WhiteOnBlack;
    FrameColor   : WhiteOnBrown;     FrameMono       : LtGrayOnBlack;
    HeaderColor  : BlueOnBrown;      HeaderMono      : BlackOnLtGray
  );

  MainColor : ColorSet = (
    TextColor    : BlackOnLtGray;    TextMono        : LtGrayOnBlack;
    CtrlColor    : RedOnLtGray;      CtrlMono        : WhiteOnBlack;
    FrameColor   : RedOnLtGray;      FrameMono       : LtGrayOnBlack;
    HeaderColor  : BlueOnLtGray;     HeaderMono      : BlackOnLtGray
  );

  var
    win       : array[1..11] of StackWindowPtr;
    WinOpts2,
    WinOpts3,
    WinOpts   : Longint;
    message,
    absr,
    ax,
    com,
    range,
    run,
    relr,
    shellwin,
    coverup      : Integer;

  procedure InitWins;

  implementation

  procedure InitWins;

  begin

    WinOpts  := wBordered+wClear+wSaveContents;
    WinOpts2 := wBordered+wClear;
    WinOpts3 := wClear+wSaveContents;

    New(win[1], InitCustom(2, 2, 79, 23, MainColor, WinOpts));
    win[1]^.setcursor(cuhidden);
    absr := 2;
    New(win[absr], InitCustom(3, 3, 28, 10, AbsRel, WinOpts));
    win[absr]^.setcursor(cuhidden);
    range := 3;
    New(win[range], InitCustom(32, 3, 49, 10, RangeColor, WinOpts));
    win[range]^.setcursor(cuhidden);
    relr := 4;
    New(win[relr], InitCustom(53, 3, 78, 10, AbsRel, WinOpts));
    win[relr]^.setcursor(cuhidden);
    com := 5;
    New(win[com], InitCustom(42, 15, 78, 17, ComColor, WinOpts));
    win[com]^.setcursor(cuhidden);
    ax := 6;
    New(win[ax], InitCustom(3, 15, 38, 23, AxColor, WinOpts));
    win[ax]^.setcursor(cuhidden);
    run := 7;
    New(win[run], InitCustom(3, 14, 78, 23, MenuColors, WinOpts));
    win[run]^.setcursor(cuhidden);
    message := 8;
    New(win[message], InitCustom(5, 5, 76, 7, Menucolors, WinOpts));
    win[message]^.setcursor(cuhidden);
    coverup := 9;
    New(win[coverup],Initcustom(2,2,79,23,Maincolor,WinOpts));
    win[coverup]^.setcursor(cuhidden);
    shellwin := 10;
    New(win[shellwin],Initcustom(1,1,80,25,defaultcolorset,WinOpts3));
  end;

begin
end.