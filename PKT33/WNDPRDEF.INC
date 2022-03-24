{ Declare private global window stack variables }
const
  max_wind_stack_size          = 20;
  max_snapshot_stack_size      = 20;
  max_popup_stack_size         = 20;
  max_snapshot_size            = 4000;    { 4k Text memory display }

type

  { These types are used by WINDSAVE and WINDREST to hold the     }
  { original window coordinates and cursor state.                 }
  window_stk = record
                 stack_pos       : byte;
                 current_window  : byte;
                 act_window_max  : word;   { These vars are for ACTIVATE's use }
                 act_window_min  : word;
                 act_cursor_x    : byte;
                 act_cursor_y    : byte;
                 act_cursor_size : word;
                 act_colors      : byte;
                 save_window_max : array[1..max_wind_stack_size] of word;
                 save_window_min : array[1..max_wind_stack_size] of word;
                 save_cursor_x   : array[1..max_wind_stack_size] of byte;
                 save_cursor_y   : array[1..max_wind_stack_size] of byte;
                 save_cursor_size: array[1..max_wind_stack_size] of word;
                 save_colors     : array[1..max_wind_stack_size] of byte;
               end;

  { These structures are used to hold screen snapshots }
  snapshot_ptr = ^scrn_snapshot;
  scrn_snapshot = record
                    snapshot : array[1..max_snapshot_size] of char;
                  end;
  snapshot_stk = record
                   stack_pos : byte;
                   table     : array[1..max_snapshot_stack_size] of snapshot_ptr;
                 end;


  { These types are used to process a popup window }
   popup_stk = record
                 stack_pos         : byte;
                 table             : array[1..max_popup_stack_size] of popup_rec;
               end;

  { This structure is used by the frame drawing routine (drawfram) to set }
  { what characters to be used for the window frame.  It makes adding     }
  { different kinds of windows very easy.                                 }
   frame_def = record
                 ul_corner         : char;
                 ur_corner         : char;
                 ll_corner         : char;
                 lr_corner         : char;
                 topside           : char;
                 bottomside        : char;
                 leftside          : char;
                 rightside         : char;
               end;

