#include <libdl/moby.h>
#include <libdl/game.h>
#include <libdl/stdlib.h>
#include "game.h"
#include "interop.h"
#include "shared.h"

float mapGetCurrentDifficulty(void);

//--------------------------------------------------------------------------
void populateSpawnArgsFromConfigCustom(struct MobSpawnEventArgs* output, struct MobConfig* config, int spawnParamsIdx, int isBaseConfig, int spawnFlags) {
  GameSettings* gs = gameGetSettings();
  if (!gs) return;

  float speed = config->Speed;
  float health = config->Health;
  float difficulty = mapGetCurrentDifficulty();

  if (isBaseConfig) {    
    speed = speed * (1 + (MOB_BASE_SPEED_SCALE * config->SpeedScale * difficulty));
    health = health * powf(1 + (MOB_BASE_HEALTH_SCALE * config->HealthScale * difficulty), 2);
  }

  // enforce max values
  if (config->MaxSpeed > 0 && speed > config->MaxSpeed) speed = config->MaxSpeed;
  if (config->MaxHealth > 0 && health > config->MaxHealth) health = config->MaxHealth;
  
  output->SpawnParamsIdx = spawnParamsIdx;
  output->Bolts = config->Bolts;
  output->Xp = config->Xp;
  output->StartHealth = health;
  output->Bangles = (u16)config->Bangles;
  output->Damage = 10000;
  output->AttackRadiusEighths = (u8)(config->AttackRadius * 8);
  output->HitRadiusEighths = (u8)(config->HitRadius * 8);
  output->CollRadiusEighths = (u8)(config->CollRadius * 8);
  output->SpeedEighths = (u16)(speed * 8);
  output->ReactionTickCount = (u8)config->ReactionTickCount;
  output->AttackCooldownTickCount = (u8)config->AttackCooldownTickCount;
  output->DamageCooldownTickCount = (u16)config->DamageCooldownTickCount;
  output->MobAttribute = config->MobAttribute;
  output->Behavior = config->Behavior;
}

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

void gambitsPerfectChromeTick(void) {
  static int init = 0;
	if (!init && MapConfig.ClientsReady) {
		init = 1;
		MapConfig.Functions.ModePopulateSpawnArgsFunc = &populateSpawnArgsFromConfigCustom;
	}
}
