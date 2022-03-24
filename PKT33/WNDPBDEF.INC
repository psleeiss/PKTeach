{ This file contains all of the public definitions for the windows unit }

const
  window_error_occured = 0;    { an invalid window number }

type

  { These types are used to define a popup window }
  frame_style = (single,double);
  popup_rec = record
                window_attr        : byte;       { Text attribute for window }
                frame_type         : frame_style;
                x1                 : integer;    { Frame coordinates }
                y1                 : integer;
                x2                 : integer;
                y2                 : integer;
                title              : string;    { For top of frame }
                trailer            : string;    { For bottom of frame }
              end;

   { This structure will contain the default colors for the window levels }
   win_attr = array[1..20] of byte;