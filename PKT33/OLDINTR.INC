procedure oldintr( interrupt_pointer : pointer);

{ This procedure is used from inside an interrupt to invoke the original }
{ interrupt.  Thus, if an application interrupt handler replaced interrupt }
{ 7B, then calling this procedure with the pointer to DOS's or the BIOS }
{ original interrupt vector will execute the original interrupt handler. }

{ Note that inline procedures act like assembly language macros and thus, }
{ cannot be placed into a unit.                                           }

inline( $5B/ $58/ $87/ $5E/ $0E/ $87/ $46/ $10/ $89/ $EC/ $5D/ $07/
        $1F/ $5F/ $5E/ $5A/ $59/ $CB);