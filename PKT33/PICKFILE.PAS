{============================================================================}
{ PickFile.Pas - A unit that returns a filename selected by the user using    }
{                the point and shoot method.                                  }
{                You are free to modify and freely distribute the following   }
{                source code in any way you feel neccessary.                  }
{                I plan on using it in some of my database programs in order  }
{                for the user to select a databases for Him/Her to use.       }
{ Author : Jim Luckas (76630,370)                                             }
{                                                                             }
{ P.S. this is my first attempt at TP V4.0 (What a wonderfull experiance!)    }
{=============================================================================}

unit pickfile;

{$F+}

interface
uses dos,opcrt;

const
  shadow   = 1;
  noshadow = 0;

Function Select_File(Path        : string;
                     BorderColor,WinColor,
                     TopX,TopY,Deep,Shadow : Byte ) : string;


implementation

{-----------------------------------------------------------------------------}
{ This is the Function that you call from your main program.                  }
{ Path        = Search Path example. '*.pas'                                  }
{ Deep        = Set the max screen line you want the border to extend to      }
{ Shadow      = 1 yes, 0 no                                                   }
{ This function returns the filename without the extension.                   }
{ Sample call : WriteLn(Select_File('*.pas',$0f,$1f,10,10,23,1))              }
{-----------------------------------------------------------------------------}

{--------------------------- Globals to be used by program -------------------}

Type
  Stack_Ptr  = String[13];

Var
  HeapTop   : ^Integer;
  PtrArray  : Array[1..256] of ^Stack_Ptr;
  NuOfFiles,
  BotY,RecNum,Ypos : Byte;

Function Select_File(Path        : string;
                     BorderColor,WinColor,
                     TopX,TopY,Deep,Shadow : Byte ) : string;


{-----------------------------------------------------------------------------}
{ Draw the Display Box for the filenames                                      }
{-----------------------------------------------------------------------------}

    Procedure Draw_Frame;
    begin
      If NuOfFiles > (Deep-TopY) then           {<- Decide How   }
        BotY := Deep                            {   Long to make }
      else BotY := (TopY + 1) + NuOfFiles;      {   Display Box  }
      If Shadow = 1 then                            {<- Check to see if  }
        Begin                                       {   we want a shodow }
          Window(TopX+1,TopY+1,TopX+13,BotY + 1);   {<- Window the       }
          TextAttr := $07;                          {   shadow image     }
          ClrScr;                                   {   and clear it     }
        end;
      TextAttr := BorderColor;                   {<- Set the Frame color }
      Window(TopX,TopY,TopX+11,BotY+1);          {<- Window the file box }
      Inc(TopY); dec(BotY);
      Write('ÚÄÄÄÄÄÄÄÄÄÄ¿');                        {     Now     }
      For Ypos := TopY to BotY do                   {   Draw the  }
        Write('³          ³');                      {     Box     }
      Write('ÀÄÄÄÄÄÄÄÄÄÄÙ');                        {    image    }
      Inc(TopX);
      Deep := BotY - TopY;                       {<- Change to inside depth }
      GotoXY(6,Deep+3);
      If NuOfFiles > Deep+1 then                 {<- Let the user Know   }
        Write(' more ');                         {   theres more to come }
    end;

{-----------------------------------------------------------------------------}
{ Store the FileNames in memory for now                                       }
{-----------------------------------------------------------------------------}

  Function Get_Files : Boolean;
    Var
      DirInfo : SearchRec;                      { Turbo's FileName Rec }

    begin
      NuOfFiles := 0;                           {<- Set Number of Files to 0 }
      FindFirst(Path,$20, DirInfo);             {<- Thanks Turbo Pascal 4.0 }
      Get_Files := True;                        {<- Set Return to True }
      If DosError = 0 then                      {<- Check to see if any files }
        While DosError = 0 do
          begin
            inc(NuOfFiles);                       {<- Increment File Counter }
            New(PtrArray[NuOfFiles]);             {<- Get new pointer }
            PtrArray[NuOfFiles]^ := DirInfo.Name; {<- Store the FileName }
            FindNext(DirInfo);                    {<- Thanks Again }
          end
      else Get_Files := False;            {<- If no files found Return False }
    end;

{-----------------------------------------------------------------------------}
{ Function that returns a parsed file name. exp.(Test.pas would return Test)  }
{-----------------------------------------------------------------------------}

  Function ParsedFile( FileToParse : string) : string;   { File name Passed }
    Var
      X : byte;
    begin
      X := Pos('.',FileToParse);                   {<- Check for delimiter }
      If x > 0 then                                {<- If Found }
        FileToParse[0] := Char(x-1);               {<- Change string length }
      ParsedFile := FileToParse;                   {<- Return Parsed FileName }
    end;

{-----------------------------------------------------------------------------}
{ Draw the initial Display of FileNames                                       }
{-----------------------------------------------------------------------------}

  Procedure Draw_Files;
    begin
      Window(TopX,TopY,TopX+9,BotY);     {<- First we need to Clear }
      TextAttr := WinColor;              {   The Display box to our }
      ClrScr;                            {   selected color         }
      For RecNum := 1 to deep+1 do       {<- Fill Display to Bottom }
        begin
          GotoXY(2,RecNum);
          Write(ParsedFile(PtrArray[RecNum]^));    {<- Write FileName }
        end;
      Window(1,1,80,25);                 {<- Set to default window }
    end;

{-----------------------------------------------------------------------------}
{ Procedure to scroll window                                                  }
{-----------------------------------------------------------------------------}
  Procedure Scroll(Direction : Char;
                   X,Y,Width,Deep,Lines,Attr : Byte);
    Var
      Reg : Registers;
    begin
      dec(X);                                     { Assembly  }
      dec(Y);                                     { is not    }
      inc(Deep,Y);                                { one of my }
      inc(Width,X);                               { favorite  }
      If Direction = 'D' then                     { things    }
        Reg.ah := 7                               { But must  }
      else Reg.ah := 6;                           { be done   }
      Reg.al := Lines;                            { sometimes }
      Reg.bh := Attr;                             { to save   }
      Reg.ch := Y;                                { on code   }
      reg.cl := X;
      reg.dh := Deep;
      Reg.dl := Width ;
      Intr(16,Reg);
    end;

{-----------------------------------------------------------------------------}
{ Here's we we actually start to pick the FileName                            }
{-----------------------------------------------------------------------------}

  Procedure Pick_File;
    Var CH       : Char;
        filename : String[10];
    begin
      Ypos := TopY;                             {<- Start selection at top }
      RecNum := 1;                              {<- and with the First file }
      repeat
          GotoXY(TopX,Ypos);
          TextAttr := $70;                      {<- HighLight attributte }
          FileName := '          ';             {<- Clear 10 spc. FileName }
          Insert(ParsedFile(PtrArray[RecNum]^),FileName,2);
          Write(FileName);                      {<- Now Write HighLight Bar }
          CH := upcase(ReadKey);                {<- Wait for Keystroke }
          If CH = #0 then                       {<- Is it an extended  }
            CH := ReadKey;                      {<- If so Read second Half }
          GotoXY(TopX,Ypos);                    {<- Rewrite FileName }
          TextAttr := WinColor;                 {   in Normal        }
          Write(FileName);                      {   Attributte       }
          Case CH of
            #80 : begin                         {<- Down Arrow Key }
                    inc(Ypos);
                    inc(RecNum);
                  end;
            #72 : Begin                         {<- Up Arrow Key }
                    dec(Ypos);
                    dec(RecNum);
                  end;
     {'X'}  #27 : PtrArray[RecNum]^ := '';      {<- If ESC the Return Null }
          end;
          If Ypos > BotY then                   {<- Did we reach the }
            begin                               {   Bottom of the    }
              dec(Ypos);                        {   Display and need }
              If RecNum <= NuOfFiles then       {   to Scroll Up     }
                Scroll('U',TopX,TopY,9,deep,1,WinColor)
              else RecNum := NuOfFiles;
            end;
          If Ypos < TopY then                   {<- Did we reach the }
            begin                               {   Top of the       }
              inc(Ypos);                        {   Display and need }
              If RecNum > 0 then                {   to Scroll Down   }
                Scroll('D',TopX,TopY,9,Deep,1,WinColor)
              Else RecNum := 1;
            end;
        until (CH = #13) or (CH = #27 {'X'});      {<- Break out If Return or Esc }
      end;

{-----------------------------------------------------------------------------}
{ This is where main function Select_File Starts                              }
{-----------------------------------------------------------------------------}

begin
  Mark(HeapTop);                                {<- Mark HeapTop             }
  If Get_Files then                             {<- if Files Found Continue  }
    begin
      Draw_Frame;                               {<- Draw the Display Frame   }
      Draw_Files;                               {<- Fill Display with Files  }
      Pick_File;                                {<- Pick a FileName          }
      Select_File := PtrArray[RecNum]^;         {<- Return a FileName        }
    end
  else Select_File := '?';                      {<- No Files Found Ret '?'   }
  Release(HeapTop);                             {<- Release the memory used  }
end;

Begin
End.