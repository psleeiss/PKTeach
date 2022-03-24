{$F+}
procedure securchk(everlock_parm : ever_send_rec);     {$F-}

{ This procedure provides a call to EVCHKNA.OBJ }

begin

  { See if copy protection is being used }
  if everlock_protection = unprotected_copy
  then exit;

  { Save the state of the ICA and set up call to evchk }
  move(everlock_call,ica_save,sizeof(ica_save));
  move(everlock_parm,everlock_call,sizeof(everlock_parm));

  { Call the copy protection check routine }
  evchk;

  { Display the appropriate copy protection message (if any) }
  case everlock_rc.status of

    protection_check_successful : begin

                                    { Restore ICA }
                                    move(ica_save,everlock_call,sizeof(ica_save));
                                    exit;

                                  end;
    drive_not_ready             : everdisk;
    else everfail;

  end;  { Case statement }

  halt(0);

end;