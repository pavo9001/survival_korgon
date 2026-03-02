#include <libdl/moby.h>
#include "game.h"

//--------------------------------------------------------------------------
void forceOnAllDemonBells(void) {
  Moby* m = mobyListGetStart();
  Moby* mEnd = mobyListGetEnd();
  while (m < mEnd) {
    m = mobyFindNextByOClass(m, DEMONBELL_MOBY_OCLASS);
    if (!m) break;

    struct DemonBellPVar* pvars = (struct DemonBellPVar*)m->PVar;
    if (pvars && !pvars->ForcedOn) {
      pvars->ForcedOn = 1;
      MapConfig.State->RoundDemonBellCount += 1;
    }

    ++m;
  }
}

//--------------------------------------------------------------------------
void gambitsPerfectChromeInit(void) {
  forceOnAllDemonBells();
}