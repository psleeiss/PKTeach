unit Drivers;
{ Sample unit to accompany GRLINK.PAS. This unit links all the BGI graphics
  driver into a single TPU file. This makes it easy to link the driver files
  directly into an .EXE file. See GRLINK.PAS for more information.
}

interface
uses graph;

procedure ATTDriverProc;
procedure CgaDriverProc;
procedure EgaVgaDriverProc;
procedure HercDriverProc;
procedure PC3270DriverProc;

implementation

procedure ATTDriverProc; external;
{$L ATT.OBJ }

procedure CgaDriverProc; external;
{$L CGA.OBJ }

procedure EgaVgaDriverProc; external;
{$L EGAVGA.OBJ }

procedure HercDriverProc; external;
{$L HERC.OBJ }

procedure PC3270DriverProc; external;
{$L PC3270.OBJ }

begin

  { Register all the drivers }
  if RegisterBGIdriver(@CGADriverProc) < 0
  then begin
    writeln('Graphics Driver error: ',grapherrormsg(graphresult));
    halt(1);
  end;
  if RegisterBGIdriver(@EGAVGADriverProc) < 0
  then begin
    writeln('Graphics Driver error: ',grapherrormsg(graphresult));
    halt(1);
  end;

  if RegisterBGIdriver(@HercDriverProc) < 0
  then begin
    writeln('Graphics Driver error: ',grapherrormsg(graphresult));
    halt(1);
  end;

  if RegisterBGIdriver(@ATTDriverProc) < 0
  then begin
    writeln('Graphics Driver error: ',grapherrormsg(graphresult));
    halt(1);
  end;

  if RegisterBGIdriver(@PC3270DriverProc) < 0
  then begin
    writeln('Graphics Driver error: ',grapherrormsg(graphresult));
    halt(1);
  end;

end.
