{ This holds miscellaneous definitions }

type
  time_def   = record
                 hour       : word;
                 minute     : word;
                 second     : word;
                 sec100     : word;
               end;

  date_def   = record
                 year       : word;
                 month      : word;
                 day        : word;
                 dayofwk    : word;
               end;

  str4        = string[4];
  str8        = string[8];
  str66       = filestr;
  str255      = string[255];


var
  max_real    : real;

  { This variable holds the current cursor size stored in low memory }
  rom_cursor_size      : word absolute $0000:0460;

  { This variable if set true tells SCRNUP to write to both color and }
  { monochrome video rams.                                            }
  mono_and_color_monitors : boolean;

