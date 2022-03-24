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
  );