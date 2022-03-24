
{           Copyright (c) 1985, 87 by Borland International, Inc.            }

unit Fonts;
{ Sample unit to accompany GRLINK.PAS. This unit links all the BGI graphics
  fonts into a single TPU file. This makes it easy to incorporate the font
  files directly into an .EXE file. See GRLINK.PAS for more information.
}

{$F+,O+}

interface
uses graph;

procedure GothicFontProc;
procedure SansSerifFontProc;
procedure SmallFontProc;
procedure TriplexFontProc;

implementation

procedure GothicFontProc; external;
{$L GOTH.OBJ }

procedure SansSerifFontProc; external;
{$L SANS.OBJ }

procedure SmallFontProc; external;
{$L LITT.OBJ }

procedure TriplexFontProc; external;
{$L TRIP.OBJ }


begin

  { Register all the fonts }
  if RegisterBGIfont(@GothicFontProc) < 0
  then begin
    writeln('Font loading error: ',grapherrormsg(graphresult));
    halt(1);
  end;
  if RegisterBGIfont(@SansSerifFontProc) < 0
  then begin
    writeln('Font loading error: ',grapherrormsg(graphresult));
    halt(1);
  end;
  if RegisterBGIfont(@SmallFontProc) < 0
  then begin
    writeln('Font loading error: ',grapherrormsg(graphresult));
    halt(1);
  end;
  if RegisterBGIfont(@TriplexFontProc) < 0
  then begin
    writeln('Font loading error: ',grapherrormsg(graphresult));
    halt(1);
  end;

end.
