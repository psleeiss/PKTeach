{ This include contains all of the definitions needed by the scrnproc unit }

const
  backsp           = 8;
  esc              = 27;
  retrn            = 13;
  end_key          = 1079;
  home             = 1071;
  pgup             = 1073;
  pgdn             = 1081;
  up               = 1072;
  down             = 1080;
  left             = 1075;
  right            = 1077;
  del_key          = 1083;
  F1               = 1059;
  F2               = 1060;
  F3               = 1061;
  F4               = 1062;
  F5               = 1063;
  F6               = 1064;
  F7               = 1065;
  F8               = 1066;
  F9               = 1067;
  F10              = 1068;
  max_scrn_buffers = 50;

type

  buffer = record
             len        : byte;       { Length of data_buff used }
             xpos       : integer;    { Position on screen }
             ypos       : integer;    { Position on screen }
             buff_type  : char;       { 'I'=integer, 'R'=real, 'C'=character }
                                      { 'V'=view only  'Y'= YES/NO (or abbrev)}
             data_buff  : array[1..80] of char;
             int_buf    : integer;
             real_buf   : real;
             y_n_buf    : boolean;
           end;

  screen_buf = record
                 num_used       : integer;  { Number of array slots used }
                 esc_allowed    : boolean;
                 pgup_allowed   : boolean;
                 pgdn_allowed   : boolean;
                 F1_allowed     : boolean;
                 F2_allowed     : boolean;
                 F3_allowed     : boolean;
                 F4_allowed     : boolean;
                 F5_allowed     : boolean;
                 F6_allowed     : boolean;
                 F7_allowed     : boolean;
                 F8_allowed     : boolean;
                 F9_allowed     : boolean;
                 F10_allowed    : boolean;
                 current_buffer : integer;
                 buffers        : array[1..max_scrn_buffers] of buffer;
               end;
