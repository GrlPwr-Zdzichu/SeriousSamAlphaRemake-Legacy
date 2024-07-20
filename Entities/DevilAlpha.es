// debil Alpha
// have mercy cecil - i never had c++ lessons, just readed the code and tried to understand how it works
// literally everywhere this parctice is applied lol
// zdzichu 2021

350
%{
#include "StdH.h"
#include "Models/Enemies/DevilAlpha/Devil.h"
#include "Models/Enemies/DevilAlpha/Stick.h"
#include "Models/Enemies/DevilAlpha/Minigun.h"
%}

uses "Entities/EnemyBase";
uses "Entities/Projectile";
uses "Entities/Bullet";

enum DevilAlphaType {
  0 UGZ_EGYPT        "Egyptian",
  1 UGZ_PLANETOID    "Planetoidal",
  2 UGZ_SIRIUS       "Sirius" 
};


%{
#define EGYPT_SIZE 5.75f
#define PLANETOIDAL_SIZE 2.5f
#define SIRIUS_SIZE 2.75f
#define GUN_X  0.375f
#define GUN_Y  0.6f
#define GUN_Z -1.85f
#define LIGHT_ANIM_FIRE 3
#define LIGHT_ANIM_NONE 5

// info structure
static EntityInfo eiDevilAlpha = {
  EIBT_FLESH, 10000.0f,
  0.0f, 1.6f*EGYPT_SIZE, 0.0f,
  0.0f, 1.0f*EGYPT_SIZE, 0.0f,
  };

  // info structure
static EntityInfo eiDevilAlphaPlanetoidal = {
  EIBT_FLESH, 10000.0f,
  0.0f, 1.6f*PLANETOIDAL_SIZE, 0.0f,
  0.0f, 1.0f*PLANETOIDAL_SIZE, 0.0f,
  };

  // info structure
static EntityInfo eiDevilAlphaSirius = {
  EIBT_FLESH, 10000.0f,
  0.0f, 1.6f*SIRIUS_SIZE, 0.0f,
  0.0f, 1.0f*SIRIUS_SIZE, 0.0f,
};

#define KICK_DIST 2.0f
%}


class CDevilAlpha : CEnemyBase {
name      "DevilAlpha";
thumbnail "Thumbnails\\DevilAlpha.tbn";

properties:
  1 enum DevilAlphaType m_UgzType "Character" 'C' = UGZ_PLANETOID,
  2 BOOL m_bBeBoss  "Boss" 'B' = TRUE,
  3 INDEX m_bFireBulletCount = 0,       // fire bullet binary divider
  4 FLOAT m_fFireTime = 0.0f,           // time to fire bullets
  5 INDEX m_iSpawnEffect = 0,           // counter for spawn effect every 'x' times
  6 CEntityPointer m_penLastTouched,  // last touched
  7 FLOAT m_fLastTouchedTime = 0.0f,
  {
  CEntity *penBullet;     // bullet
  CLightSource m_lsLightSource;
}
  
components:
  0 class   CLASS_BASE             "Classes\\EnemyBase.ecl",
  1 class   CLASS_PROJECTILE    "Classes\\Projectile.ecl",
  2 class   CLASS_BULLET      "Classes\\Bullet.ecl",

  10 model   MODEL_DEVIL_ALPHA      "Models\\Enemies\\DevilAlpha\\Devil.mdl",
  11 model   MODEL_DEVIL_ALPHA_STICK      "Models\\Enemies\\DevilAlpha\\Stick.mdl",
  12 model   MODEL_DEVIL_ALPHA_SHIELD      "Models\\Enemies\\DevilAlpha\\Shield.mdl",
  13 model   MODEL_DEVIL_ALPHA_FLARE      "Models\\Enemies\\DevilAlpha\\Flare.mdl",
  14 model   MODEL_DEVIL_ALPHA_MINIGUN  "Models\\Enemies\\DevilAlpha\\Minigun.mdl",
  15 model   MODEL_MINIGUN_FLARE  "Models\\Effects\\Weapons\\Flare01\\Flare.mdl",

  20 texture TEXTURE_EGYPT          "Models\\Enemies\\DevilAlpha\\Devil2.tex",
  21 texture TEXTURE_PLANETOID      "Models\\Enemies\\DevilAlpha\\Devil.tex",
  22 texture TEXTURE_SIRIUS         "Models\\Enemies\\DevilAlpha\\Devil4.tex",
  23 texture TEXTURE_STICK         "Models\\Enemies\\DevilAlpha\\Stick.tex",
  24 texture TEXTURE_SHIELD         "Models\\Enemies\\DevilAlpha\\Shield.tex",
  25 texture TEXTURE_MINIGUN         "Models\\Weapons\\Minigun\\Minigun.tex",
  26 texture TEXTURE_FLARE         "Models\\Enemies\\DevilAlpha\\12.tex",
  27 texture   TEXTURE_MINIGUN_FLARE  "Models\\Effects\\Weapons\\Flare01\\Flare.tex",

// ************** SOUNDS **************
 50 sound   SOUND_IDLE      "Models\\Enemies\\DevilAlpha\\Sounds\\Idle.wav",
 51 sound   SOUND_SIGHT     "Models\\Enemies\\DevilAlpha\\Sounds\\Sight.wav",
 52 sound   SOUND_WOUND     "Models\\Enemies\\DevilAlpha\\Sounds\\Wound.wav",
 53 sound   SOUND_FIRE      "Models\\Enemies\\DevilAlpha\\Sounds\\Fire.wav",
 54 sound   SOUND_KICK      "Models\\Enemies\\DevilAlpha\\Sounds\\Kick.wav",
 55 sound   SOUND_DEATH     "Models\\Enemies\\DevilAlpha\\Sounds\\Death.wav",
 56 sound   SOUND_PROJECTILE     "Models\\Enemies\\DevilAlpha\\Sounds\\Projectile.wav",

functions:

  // describe how this enemy killed player
  virtual CTString GetPlayerKillDescription(const CTString &strPlayerName, const EDeath &eDeath)
  {
    CTString str;
    if (eDeath.eLastDamage.dmtType==DMT_CLOSERANGE) {
      str.PrintF(TRANS("Devil killed %s"), strPlayerName);
    } else if (m_UgzType == UGZ_PLANETOID && m_UgzType == UGZ_SIRIUS) {
      str.PrintF(TRANS("Devil sent %s to hell"), strPlayerName);
    } else {
      str.PrintF(TRANS("Devil poured lead into %s"), strPlayerName);
	  }
    return str;
  }
  

  /* Entity info */
  void *GetEntityInfo(void) {
    if (m_UgzType == UGZ_PLANETOID) {
      return &eiDevilAlphaPlanetoidal;
    } else if (m_UgzType == UGZ_SIRIUS) {
      return &eiDevilAlphaSirius;
    } else {
      return &eiDevilAlpha;
    }
  };

    virtual const CTFileName &GetComputerMessageName(void) const {
    static DECLARE_CTFILENAME(fnmEgypt, "Data\\Messages\\Enemies\\DevilEgyptian.txt");
    static DECLARE_CTFILENAME(fnmPlanetoid, "Data\\Messages\\Enemies\\DevilPlanetoidal.txt");
    static DECLARE_CTFILENAME(fnmSirius, "Data\\Messages\\Enemies\\DevilSirius.txt");
    switch(m_UgzType) {
    default: ASSERT(FALSE);
    case UGZ_EGYPT: return fnmEgypt;
    case UGZ_PLANETOID: return fnmPlanetoid;
    case UGZ_SIRIUS: return fnmSirius;
    }
  };

	// cannon balls should explode, expect Planetoidal one
    BOOL ForcesCannonballToExplode(void)
  {
    if (m_UgzType!=UGZ_PLANETOID) {
      return TRUE;
    }
    return CEnemyBase::ForcesCannonballToExplode();
  }

    void Precache(void) {
    CEnemyBase::Precache();
    PrecacheModel(MODEL_DEVIL_ALPHA);
    PrecacheTexture(TEXTURE_EGYPT);
    PrecacheTexture(TEXTURE_PLANETOID);
    PrecacheTexture(TEXTURE_SIRIUS);
    PrecacheTexture(TEXTURE_STICK);
    PrecacheTexture(TEXTURE_FLARE);
    PrecacheTexture(TEXTURE_SHIELD);
    PrecacheSound(SOUND_IDLE);
    PrecacheSound(SOUND_SIGHT);
    PrecacheSound(SOUND_WOUND);
    PrecacheSound(SOUND_FIRE);
    PrecacheSound(SOUND_KICK);
    PrecacheSound(SOUND_DEATH);
    PrecacheSound(SOUND_PROJECTILE);
  };

    /* Fill in entity statistics - for AI purposes only */
  BOOL FillEntityStatistics(EntityStats *pes)
  {
    CEnemyBase::FillEntityStatistics(pes);
    switch(m_UgzType) {
    case UGZ_EGYPT: { pes->es_strName+=" Egyptian"; } break;
    case UGZ_PLANETOID:   { pes->es_strName+=" Planetoidal"; } break;
    case UGZ_SIRIUS:   { pes->es_strName+=" Sirius"; } break;
    }
    return TRUE;
  }

  /* Receive damage */
  void ReceiveDamage(CEntity *penInflictor, enum DamageType dmtType,
    FLOAT fDamageAmmount, const FLOAT3D &vHitPoint, const FLOAT3D &vDirection) 
  {
    // Devil can't harm Debil
    if (!IsOfClass(penInflictor, "DevilAlpha")) {
      CEnemyBase::ReceiveDamage(penInflictor, dmtType, fDamageAmmount, vHitPoint, vDirection);
    }
  };


  // damage anim
  INDEX AnimForDamage(FLOAT fDamage) {
    INDEX iAnim;
    switch (IRnd()%3) {
      case 0: iAnim = DEVIL_ANIM_WOUND01SLIGHTFRONT; break;
      case 1: iAnim = DEVIL_ANIM_WOUND02SLIGHTBACK; break;
      case 2: iAnim = DEVIL_ANIM_WOUND03CRITICALFRONT; break;
      default: ASSERTALWAYS("Devil Alpha unknown damage");
    }
    StartModelAnim(iAnim, 0);
	MinigunOff();
    return iAnim;
  };

  // death
  INDEX AnimForDeath(void) {
    INDEX iAnim;
    switch (IRnd()%2) {
      case 0: iAnim = DEVIL_ANIM_DEATH; break;
      case 1: iAnim = DEVIL_ANIM_DEATH; break;
      default: ASSERTALWAYS("Devil Alpha unknown death");
    }
    StartModelAnim(iAnim, 0);
    return iAnim;
  };

  void DeathNotify(void) {
    ChangeCollisionBoxIndexWhenPossible(DEVIL_COLLISION_BOX_DEATH);
    en_fDensity = 500.0f;
  };

  // virtual anim functions
  void StandingAnim(void) {
    StartModelAnim(DEVIL_ANIM_STANDLOOP, AOF_LOOPING|AOF_NORESTART);
  };
  void WalkingAnim(void) {
    StartModelAnim(DEVIL_ANIM_WALK, AOF_LOOPING|AOF_NORESTART);
  };
  void RunningAnim(void) {
    StartModelAnim(DEVIL_ANIM_RUN, AOF_LOOPING|AOF_NORESTART);
  };
  void RotatingAnim(void) {
    StartModelAnim(DEVIL_ANIM_WALK, AOF_LOOPING|AOF_NORESTART);
  };

  // virtual sound functions
  void IdleSound(void) {
    PlaySound(m_soSound, SOUND_IDLE, SOF_3D);
  };
  void SightSound(void) {
    PlaySound(m_soSound, SOUND_SIGHT, SOF_3D);
  };
  void WoundSound(void) {
    PlaySound(m_soSound, SOUND_WOUND, SOF_3D);
  };
  void DeathSound(void) {
    PlaySound(m_soSound, SOUND_DEATH, SOF_3D);
  };

   // fire minigun on/off
  void MinigunOn(void)
  {
    //PlayLightAnim(LIGHT_ANIM_FIRE, AOF_LOOPING);
    CModelObject *pmoGun = &GetModelObject()->GetAttachmentModel(DEVIL_ATTACHMENT_MINIGUN)->
      amo_moModelObject;
    //pmoGun->PlayAnim(GUN_ANIM_FIRE, AOF_LOOPING);
    AddAttachmentToModel(this, *pmoGun, MINIGUN_ATTACHMENT_FLARE, MODEL_MINIGUN_FLARE, TEXTURE_MINIGUN_FLARE, 0, 0, 0);
  }
  void MinigunOff(void)
  {
    CModelObject *pmoGun = &GetModelObject()->GetAttachmentModel(DEVIL_ATTACHMENT_MINIGUN)->
      amo_moModelObject;
    pmoGun->RemoveAttachmentModel(MINIGUN_ATTACHMENT_FLARE);
  }

 /************************************************************
 *                   FIRE BULLET		             *
 ************************************************************/
  BOOL CanFireAtPlayer(void)
  {
    // get ray source and target
    FLOAT3D vSource, vTarget;
    GetPositionCastRay(this, m_penEnemy, vSource, vTarget);

    // bullet start position
    CPlacement3D plBullet;
    plBullet.pl_OrientationAngle = ANGLE3D(0,0,0);
    plBullet.pl_PositionVector = FLOAT3D(GUN_X, GUN_Y, 0);
    // offset are changed according to stretch factor
    if (m_UgzType == UGZ_EGYPT) {
      plBullet.pl_PositionVector*=EGYPT_SIZE;
    } else if (m_UgzType == UGZ_PLANETOID) {
      plBullet.pl_PositionVector*=PLANETOIDAL_SIZE;
    } else {
      plBullet.pl_PositionVector*=SIRIUS_SIZE;
    }
    plBullet.RelativeToAbsolute(GetPlacement());
    vSource = plBullet.pl_PositionVector;

    // cast the ray
    CCastRay crRay(this, vSource, vTarget);
    crRay.cr_ttHitModels = CCastRay::TT_NONE;     // check for brushes only
    crRay.cr_bHitTranslucentPortals = FALSE;
    en_pwoWorld->CastRay(crRay);

    // if hit nothing (no brush) the entity can be seen
    return (crRay.cr_penHit==NULL);     
  }

  void PrepareBullet(FLOAT fDamage) {
    // bullet start position
    CPlacement3D plBullet;
    plBullet.pl_OrientationAngle = ANGLE3D(0,0,0);
    plBullet.pl_PositionVector = FLOAT3D(GUN_X, GUN_Y, 0);
    // offset are changed according to stretch factor
    if (m_UgzType == UGZ_EGYPT) {
      plBullet.pl_PositionVector*=EGYPT_SIZE;
    } else if (m_UgzType == UGZ_PLANETOID) {
      plBullet.pl_PositionVector*=PLANETOIDAL_SIZE;
    } else {
      plBullet.pl_PositionVector*=UGZ_SIRIUS;
    }
    plBullet.RelativeToAbsolute(GetPlacement());
    // create bullet
    penBullet = CreateEntity(plBullet, CLASS_BULLET);
    // init bullet
    EBulletInit eInit;
    eInit.penOwner = this;
    eInit.fDamage = fDamage;
    penBullet->Initialize(eInit);
  };

  // fire bullet
  void FireBullet(void) {
    // binary divide counter
    m_bFireBulletCount++;
    if (m_bFireBulletCount>1) { m_bFireBulletCount = 0; }
    if (m_bFireBulletCount==1) { return; }
    // bullet
    PrepareBullet(3.0f);
    ((CBullet&)*penBullet).CalcTarget(m_penEnemy, 250);
    ((CBullet&)*penBullet).CalcJitterTarget(4);
    ((CBullet&)*penBullet).LaunchBullet( TRUE, TRUE, TRUE);
    ((CBullet&)*penBullet).DestroyBullet();
  };


  // adjust sound and watcher parameters here if needed
  void EnemyPostInit(void) 
  {
    // set sound default parameters
    m_soSound.Set3DParameters(160.0f, 50.0f, 1.0f, 1.0f);
  };



procedures:
/************************************************************
 *                A T T A C K   E N E M Y                   *
 ************************************************************/
  Fire(EVoid) : CEnemyBase::Fire {
      // Egyptian
    if (m_UgzType == UGZ_EGYPT) {
      autocall EgyptianDevilAttack() EEnd;
    // Planetoidal
    } else if (m_UgzType == UGZ_PLANETOID) {
      autocall PlanetoidalDevilAttack() EEnd;
    // Sirian
    } else if (m_UgzType == UGZ_SIRIUS) {
      autocall SirianDevilAttack() EEnd;
    }
	
    return EReturn();
  };

  EgyptianDevilAttack(EVoid) {
   if (!CanFireAtPlayer()) {
      return EReturn();
    }

	m_fFireTime = 14.0f;
	// to fire
    StartModelAnim(DEVIL_ANIM_FROMSTANDTOATTACK01POSITION, 0);
    m_fLockOnEnemyTime = GetModelObject()->GetAnimLength(DEVIL_ANIM_FROMSTANDTOATTACK01POSITION) + 0.5f + FRnd()/3;
    autocall CEnemyBase::LockOnEnemy() EReturn;

    // fire
    m_iSpawnEffect = 0;                         // effect every 'x' frames
    m_fFireTime += _pTimer->CurrentTick();
    m_bFireBulletCount = 0;
    PlaySound(m_soSound, SOUND_FIRE, SOF_3D|SOF_LOOP);
    MinigunOn();

    while (m_fFireTime > _pTimer->CurrentTick()) {
      m_fMoveFrequency = 0.1f;
      wait(m_fMoveFrequency) {
        on (EBegin) : {
          // make fuss
          AddToFuss();
          // fire bullet
          FireBullet();
          m_vDesiredPosition = m_penEnemy->GetPlacement().pl_PositionVector;
          // rotate to enemy
          if (!IsInPlaneFrustum(m_penEnemy, CosFast(5.0f))) {
            m_fMoveSpeed = 0.0f;
            m_aRotateSpeed = 4000.0f;
            StartModelAnim(DEVIL_ANIM_ATTACK01LOOPMINIGUN, AOF_LOOPING|AOF_NORESTART);
          // stand in place
          } else {
            m_fMoveSpeed = 0.0f;
            m_aRotateSpeed = 0.0f;
            StartModelAnim(DEVIL_ANIM_ATTACK01LOOPMINIGUN, AOF_LOOPING|AOF_NORESTART);
          }
          // adjust direction and speed
          SetDesiredMovement(); 
          resume;
        }
        on (ETimer) : { stop; }
      }
    }
    m_soSound.Stop();
    MinigunOff();
    // set next shoot time
    m_fShootTime = _pTimer->CurrentTick() + m_fAttackFireTime*(1.0f + FRnd()/3.0f);

    // from fire
    StartModelAnim(DEVIL_ANIM_FROMATTACK01TOSTANDPOSITION, 0);
    autowait(GetModelObject()->GetAnimLength(DEVIL_ANIM_FROMATTACK01TOSTANDPOSITION));
	


    MaybeSwitchToAnotherPlayer();
	return EEnd();
  };

    PlanetoidalDevilAttack(EVoid) {
	    // wait for a while
		StopMoving();
    // fire projectile
	StartModelAnim(DEVIL_ANIM_ATTACK03, 0);
	autowait(0.25f);
    ShootProjectile(PRT_DEVIL_ALPHA, FLOAT3D(0.0f, PLANETOIDAL_SIZE+4.5f, 0.5f), ANGLE3D(0, 0, 0));
    PlaySound(m_soSound, SOUND_PROJECTILE, SOF_3D);
    autowait(GetModelObject()->GetCurrentAnimLength());
	StartModelAnim(DEVIL_ANIM_ATTACK03, 0);
	autowait(0.25f);
	ShootProjectile(PRT_DEVIL_ALPHA, FLOAT3D(0.0f, PLANETOIDAL_SIZE+4.5f, 0.5f), ANGLE3D(0, 0, 0));
    PlaySound(m_soSound, SOUND_PROJECTILE, SOF_3D);
    autowait(GetModelObject()->GetCurrentAnimLength());
	MaybeSwitchToAnotherPlayer();
	return EEnd();
  };

    SirianDevilAttack(EVoid) {
	// wait for a while
	autowait(0.2f);
    // fire projectile
	StartModelAnim(DEVIL_ANIM_ATTACK03, 0);
	autowait(0.15f);
    ShootProjectile(PRT_DEVIL_ALPHA, FLOAT3D(0.0f, SIRIUS_SIZE+2.5f, 0.5f), ANGLE3D(0, 0, 0));
    PlaySound(m_soSound, SOUND_PROJECTILE, SOF_3D);
    autowait(GetModelObject()->GetCurrentAnimLength()/2);
	StartModelAnim(DEVIL_ANIM_ATTACK03, 0);
	autowait(0.15f);
	ShootProjectile(PRT_DEVIL_ALPHA, FLOAT3D(0.0f, SIRIUS_SIZE+2.5f, 0.5f), ANGLE3D(0, 0, 0));
    PlaySound(m_soSound, SOUND_PROJECTILE, SOF_3D);
    autowait(GetModelObject()->GetCurrentAnimLength()/2);
	StartModelAnim(DEVIL_ANIM_ATTACK03, 0);
	autowait(0.15f);
	ShootProjectile(PRT_DEVIL_ALPHA, FLOAT3D(0.0f, SIRIUS_SIZE+2.5f, 0.5f), ANGLE3D(0, 0, 0));
    PlaySound(m_soSound, SOUND_PROJECTILE, SOF_3D);
    autowait(GetModelObject()->GetCurrentAnimLength());
	if (CalcDist(m_penEnemy) < KICK_DIST) {
	StartModelAnim(DEVIL_ANIM_ATTACK02LOOPCLAWS, 0);
	PlaySound(m_soSound, SOUND_KICK, SOF_3D);
		StopMoving();
      FLOAT3D vDirection = m_penEnemy->GetPlacement().pl_PositionVector-GetPlacement().pl_PositionVector;
      vDirection.Normalize();
      InflictDirectDamage(m_penEnemy, this, DMT_CLOSERANGE, 20.0f, FLOAT3D(0, 0, 0), vDirection);
	  }
	  MaybeSwitchToAnotherPlayer();
	  return EReturn();
  };

/************************************************************
 *                       M  A  I  N                         *
 ************************************************************/
  Main(EVoid) {
    // declare yourself as a model
    InitAsModel();
    SetPhysicsFlags(EPF_MODEL_WALKING|EPF_HASLUNGS);
    SetCollisionFlags(ECF_MODEL);
    SetFlags(GetFlags()|ENF_ALIVE);0,
    SetHealth(6500.0f);
    m_fMaxHealth = 6500.0f;
    en_tmMaxHoldBreath = 5.0f;
    en_fDensity = 9000.0f;

    // set your appearance
    SetModel(MODEL_DEVIL_ALPHA);
	switch (m_UgzType) {
	case UGZ_EGYPT:
	m_bBoss = m_bBeBoss;
    SetModelMainTexture(TEXTURE_EGYPT);
	AddAttachment(DEVIL_ATTACHMENT_STICK, MODEL_DEVIL_ALPHA_STICK, TEXTURE_STICK);
	AddAttachment(DEVIL_ATTACHMENT_SHIELD, MODEL_DEVIL_ALPHA_SHIELD, TEXTURE_SHIELD);
	AddAttachment(DEVIL_ATTACHMENT_MINIGUN, MODEL_DEVIL_ALPHA_MINIGUN, TEXTURE_MINIGUN);
    StandingAnim();
    // setup moving speed
    m_fWalkSpeed = FRnd() + 1.5f;
    m_aWalkRotateSpeed = AngleDeg(FRnd()*10.0f + 25.0f);
    m_fAttackRunSpeed = FRnd()*2.0f + 7.0f;
    m_aAttackRotateSpeed = AngleDeg(FRnd()*50 + 245.0f);
    m_fCloseRunSpeed = FRnd()*2.0f + 7.0f;
    m_aCloseRotateSpeed = AngleDeg(FRnd()*50 + 245.0f);
    // setup attack distances
    m_fAttackDistance = 40.0f;
    m_fCloseDistance = 0.0f;
    m_fStopDistance = 10.0f;
    m_fAttackFireTime = 3.0f;
    m_fCloseFireTime = 10.0f;
    m_fIgnoreRange = 200.0f;
    // damage/explode properties
    m_fBlowUpAmount = 1200.0f;
    m_fBodyParts = 32;
    m_fDamageWounded = 1250.0f;
	m_iScore = 50000;
	GetModelObject()->StretchModel(FLOAT3D(EGYPT_SIZE, EGYPT_SIZE, EGYPT_SIZE));
    ModelChangeNotify();
	break;

	case UGZ_PLANETOID:
    SetModelMainTexture(TEXTURE_PLANETOID);
	AddAttachment(DEVIL_ATTACHMENT_MINIGUN, MODEL_DEVIL_ALPHA_MINIGUN, TEXTURE_MINIGUN);
	AddAttachment(DEVIL_ATTACHMENT_STICK, MODEL_DEVIL_ALPHA_STICK, TEXTURE_STICK);
	AddAttachment(DEVIL_ATTACHMENT_SHIELD, MODEL_DEVIL_ALPHA_SHIELD, TEXTURE_SHIELD);
    StandingAnim();
	SetHealth(1500.0f);
    m_fMaxHealth = 1500.0f;
    // setup moving speed
    m_fWalkSpeed = FRnd() + 1.5f;
    m_aWalkRotateSpeed = AngleDeg(FRnd()*10.0f + 25.0f);
    m_fAttackRunSpeed = FRnd()*2.0f + 7.0f;
    m_aAttackRotateSpeed = AngleDeg(FRnd()*50 + 245.0f);
    m_fCloseRunSpeed = FRnd()*2.0f + 7.0f;
    m_aCloseRotateSpeed = AngleDeg(FRnd()*50 + 245.0f);
    // setup attack distances
    m_fAttackDistance = 40.0f;
    m_fCloseDistance = 2.5f;
    m_fStopDistance = 10.0f;
    m_fAttackFireTime = 3.0f;
    m_fCloseFireTime = 1.0f;
    m_fIgnoreRange = 200.0f;
    // damage/explode properties
    m_fBlowUpAmount = 1200.0f;
    m_fBodyParts = 32;
    m_fDamageWounded = 350.0f;
	m_iScore = 7500;
	m_bBoss = m_bBeBoss;
	GetModelObject()->StretchModel(FLOAT3D(PLANETOIDAL_SIZE, PLANETOIDAL_SIZE, PLANETOIDAL_SIZE));
    ModelChangeNotify();
	break;

	case UGZ_SIRIUS:
    SetModelMainTexture(TEXTURE_SIRIUS);
	AddAttachment(DEVIL_ATTACHMENT_MINIGUN, MODEL_DEVIL_ALPHA_MINIGUN, TEXTURE_MINIGUN);
	AddAttachment(DEVIL_ATTACHMENT_STICK, MODEL_DEVIL_ALPHA_STICK, TEXTURE_STICK);
    StandingAnim();
	SetHealth(1850.0f);
    m_fMaxHealth = 1850.0f;
    // setup moving speed
    m_fWalkSpeed = FRnd() + 1.5f;
    m_aWalkRotateSpeed = AngleDeg(FRnd()*10.0f + 25.0f);
    m_fAttackRunSpeed = FRnd()*2.0f + 7.0f;
    m_aAttackRotateSpeed = AngleDeg(FRnd()*50 + 245.0f);
    m_fCloseRunSpeed = FRnd()*2.0f + 7.0f;
    m_aCloseRotateSpeed = AngleDeg(FRnd()*50 + 245.0f);
    // setup attack distances
    m_fAttackDistance = 40.0f;
    m_fCloseDistance = 2.0f;
    m_fStopDistance = 10.0f;
    m_fAttackFireTime = 3.0f;
    m_fCloseFireTime = 1.0f;
    m_fIgnoreRange = 200.0f;
    // damage/explode properties
    m_fBlowUpAmount = 1200.0f;
    m_fBodyParts = 32;
    m_fDamageWounded = 455.0f;
	m_iScore = 10000;
	m_bBoss = m_bBeBoss;
	GetModelObject()->StretchModel(FLOAT3D(SIRIUS_SIZE, SIRIUS_SIZE, SIRIUS_SIZE));
    ModelChangeNotify();
	break;
}
    // continue behavior in base class
    jump CEnemyBase::MainLoop();
  };
};
