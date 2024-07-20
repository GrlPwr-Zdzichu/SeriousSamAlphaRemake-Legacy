#include "stdafx.h"
#include "LCDDrawing.h"

static CTextureObject atoIcons[46];
static CTextureObject _toPathDot;
static CTextureObject _toMapBcgLD;
static CTextureObject _toMapBcgLU;
static CTextureObject _toMapBcgRD;
static CTextureObject _toMapBcgRU;

PIX aIconCoords[][2] =
{
  {175,404},  // 00: Hatshepsut
  {60,381},   // 01: Sand Canyon
  {50,300},   // 02: Ramses
  {171,304},  // 03: Canyon
  {190,225},  // 04: Waterfall
  {303,305},  // 05: Oasis
  {361,296},  // 06: Dunes
  {362,222},  // 07: Suburbs
  {321,211},  // 08: Sewers
  {316,156},  // 09: Metropolis
  {194,157},  // 10: Sphynx
  {160,111},  // 11: Karnak
  {167,61},   // 12: Luxor
  {50,53},    // 13: Sacred
  {185,0},    // 14: Pyramid
  {0,0},    // 15: CityEnter
  {0,-15},    // 16: CityMidlle
  {0,-15},    // 17: CityObelisk
  {0,-15},    // 18: EnterCave
  {0,-15},    // 19: KingValley
  {0,-15},    // 20: TombofMenes
  {0,-15},    // 21: TombofRamses
  {0,-15},    // 22: SecretTomb
  {0,-15},    // 23: MentalTomb
  {0,-15},    // 24: KingValleyExit
  {0,-15},    // 25: KarnakEnter
  {0,-15},    // 26: KarnakEnterComplex
  {0,-15},    // 27: KarnakTemple
  {0,-15},    // 28: KarnakLake&Alley
  {0,-15},    // 29: BabilonTemple
  {0,-15},    // 30: Hatshepsut Alpha
  {0,-15},    // 31: Pyramid valley
  {0,-15},    // 32: WaterPlanetIntro
  {0,-15},    // 33: WaterPlanetValley
  {0,-15},    // 34: WaterPlanetTerra
  {0,-15},    // 35: WaterPlanetEnd
  {0,-15},    // 36: LavaPlanetValley
  {0,-15},    // 37: LavaPlanetCanyon
  {0,-15},    // 38: LavaPlanetVulcan
  {0,-15},    // 39: GreenPlanet
  {0,-15},    // 40: IcePlanet
  {0,-15},    // 41: IcePlanetEnd
  {0,-15},    // 42 Tropic Planet
  {0,-15},    // 43 Tropic Planet end
  {0,-15},    // 44: RockPlanet
  {0,-15},    // 45: SpaceCrusader
};

#define HATSHEPSUT_BIT 0
#define SAND_BIT 1
#define RAMSES_BIT 2
#define CANYON_BIT 3
#define WATERFALL_BIT 4
#define OASIS_BIT 5
#define DUNES_BIT 6
#define SUBURBS_BIT 7
#define SEWERS_BIT 8
#define METROPOLIS_BIT 9
#define SPHYNX_BIT 10
#define KARNAK_BIT 11
#define LUXOR_BIT 12
#define SACRED_BIT 13
#define PYRAMID_BIT 14
#define CITYENTER_BIT 15
#define CITYMIDLLE_BIT 16
#define CITYOBELISK_BIT 17
#define ENTERCAVE_BIT 18
#define KINGVALLEY_BIT 19
#define TOMBOFMENES_BIT 20
#define TOMBOFRAMSESII_BIT 21
#define SECRETTOMB_BIT 22
#define MENTALTOMB_BIT 23
#define KINGVALLEYEXIT_BIT 24
#define KARNAKENTER_BIT 25
#define KARNAKENTERCOMPLEX_BIT 26
#define KARNAKTEMPLE_BIT 27
#define KARNAKLAKEANDALLEY_BIT 28
#define BABILONTEMPLE_BIT 29
#define HATSHEPSUTALPHA_BIT 30
#define PYRAMIDVALLEY_BIT 31
#define WATERPLANETINTRO_BIT 32
#define WATERPLANETVALLEY_BIT 33
#define WATERPLANETTERRA_BIT 34
#define WATERPLANETEND_BIT 35
#define LAVAPLANETVALLEY_BIT 36
#define LAVAPLANETCANYON_BIT 37
#define LAVAPLANETVULCAN_BIT 38
#define GREENPLANET_BIT 39
#define ICEPLANET_BIT 40
#define ICEPLANETEND_BIT 41
#define TROPICPLANET_BIT 42
#define TROPICPLANETEND_BIT 43
#define ROCKPLANET_BIT 44
#define SPACECRUSADER_BIT 45

INDEX  aPathPrevNextLevels[][2] = 
{
  {HATSHEPSUT_BIT, SAND_BIT},     // 00
  {SAND_BIT, RAMSES_BIT},         // 01
  {RAMSES_BIT, CANYON_BIT},       // 02
  {CANYON_BIT, WATERFALL_BIT},    // 03
  {CANYON_BIT, OASIS_BIT},        // 04
  {WATERFALL_BIT, OASIS_BIT},     // 05
  {OASIS_BIT, DUNES_BIT},         // 06
  {DUNES_BIT, SUBURBS_BIT},       // 07
  {SUBURBS_BIT, SEWERS_BIT},      // 08
  {SEWERS_BIT, METROPOLIS_BIT},   // 09
  {METROPOLIS_BIT, SPHYNX_BIT},   // 10
  {SPHYNX_BIT, KARNAK_BIT},       // 11
  {KARNAK_BIT, LUXOR_BIT},        // 12
  {LUXOR_BIT, SACRED_BIT},        // 13
  {SACRED_BIT, PYRAMID_BIT},      // 14
  {LUXOR_BIT, PYRAMID_BIT},       // 15
  {CITYENTER_BIT, CITYMIDLLE_BIT},	// 16
  {CITYMIDLLE_BIT, CITYOBELISK_BIT},	// 17
  {CITYOBELISK_BIT, ENTERCAVE_BIT},	// 18
  {ENTERCAVE_BIT, KINGVALLEY_BIT},	// 19
  {KINGVALLEY_BIT, TOMBOFMENES_BIT},	// 20
  {TOMBOFMENES_BIT, TOMBOFRAMSESII_BIT},	// 21
  {TOMBOFRAMSESII_BIT, SECRETTOMB_BIT},	// 22
  {SECRETTOMB_BIT, KINGVALLEYEXIT_BIT},	// 23
  {KINGVALLEYEXIT_BIT, KARNAKENTER_BIT},	// 24
  {KARNAKENTER_BIT, KARNAKENTERCOMPLEX_BIT},	// 25
  {KARNAKENTERCOMPLEX_BIT, KARNAKTEMPLE_BIT},	// 26
  {KARNAKTEMPLE_BIT, KARNAKLAKEANDALLEY_BIT},	// 27
  {KARNAKLAKEANDALLEY_BIT, BABILONTEMPLE_BIT},	// 28
  {BABILONTEMPLE_BIT, HATSHEPSUTALPHA_BIT},	// 29
  {HATSHEPSUTALPHA_BIT, PYRAMIDVALLEY_BIT},	// 30
  {PYRAMIDVALLEY_BIT, WATERPLANETINTRO_BIT},	// 31
  {WATERPLANETINTRO_BIT, WATERPLANETVALLEY_BIT},	// 32
  {WATERPLANETVALLEY_BIT, WATERPLANETTERRA_BIT},	// 33
  {WATERPLANETTERRA_BIT, WATERPLANETEND_BIT},	// 34
  {WATERPLANETEND_BIT, LAVAPLANETVALLEY_BIT},	// 35
  {LAVAPLANETVALLEY_BIT, LAVAPLANETCANYON_BIT},	// 36
  {LAVAPLANETCANYON_BIT, LAVAPLANETVULCAN_BIT},// 37
  {LAVAPLANETVULCAN_BIT, GREENPLANET_BIT},	// 38
  {GREENPLANET_BIT, ICEPLANET_BIT},	// 39
  {ICEPLANET_BIT, ICEPLANETEND_BIT},	// 40
  {ICEPLANETEND_BIT, TROPICPLANET_BIT},	// 41
  {TROPICPLANET_BIT, TROPICPLANETEND_BIT},	// 42
  {TROPICPLANETEND_BIT, ROCKPLANET_BIT},	// 43
  {ROCKPLANET_BIT, SPACECRUSADER_BIT},	// 44
  {MENTALTOMB_BIT, SPACECRUSADER_BIT},	// 44
};

PIX aPathDots[][10][2] = 
{
  // 00: Hatshepsut - Sand
  {
    {207,435},
    {196,440},
    {184,444},
    {172,443},
    {162,439},
    {156,432},
    {-1,-1},
  },
  
  // 01: Sand - Ramses
  {
    {115,388},
    {121,382},
    {128,377},
    {136,371},
    {-1,-1},
  },

  // 02: Ramses - Canyon
  {
    {148,368},
    {159,370},
    {169,374},
    {177,379},
    {187,381},
    {200,380},
    {211,376},
    {-1,-1},
  },

  // 03: Canyon - Waterfall
  {
    {273,339},
    {276,331},
    {278,322},
    {280,313},
    {279,305},
    {273,298},
    {266,293},
    {260,288},
    {-1,-1},
  },

  // 04: Canyon - Oasis
  {
    {288,360},
    {295,355},
    {302,360},
    {310,364},
    {319,367},
    {328,368},
    {-1,-1},
  },

  // 05: Waterfall - Oasis
  {
    {294,279},
    {302,282},
    {310,287},
    {316,294},
    {320,302},
    {323,310},
    {327,318},
    {332,326},
    {337,333},
    {-1,-1},
  },

  // 06: Oasis - Dunes
  {
    {384,360},
    {394,358},
    {405,353},
    {414,347},
    {421,339},
    {426,329},
    {-1,-1},
  },

  // 07: Dunes - Suburbs
  {
    {439,305},
    {434,300},
    {429,293},
    {-1,-1},
  },

  // 08: Suburbs - Sewers
  {
    {403,250},
    {402,244},
    {401,238},
    {398,232},
    {-1,-1},
  },

  // 09: Sewers - Metropolis
  {
    {372,266},
    {371,221},
    {370,216},
    {-1,-1},
  },

  // 10: Metropolis - Alley
  {
    {317,211},
    {310,215},
    {302,219},
    {293,222},
    {283,222},
    {273,221},
    {265,218},
    {-1,-1},
  },

  // 11: Alley - Karnak
  {
    {260,189},
    {259,181},
    {255,174},
    {249,168},
    {241,165},
    {233,164},
    {-1,-1},
  },

  // 12: Karnak - Luxor
  {
    {228,143},
    {228,136},
    {226,129},
    {221,123},
    {-1,-1},
  },

  // 13: Luxor - Sacred
  {
    {175,101},
    {169,106},
    {162,111},
    {154,113},
    {145,113},
    {136,112},
    {-1,-1},
  },

  // 14: Sacred - Pyramid
  {
    {126,59},
    {134,55},
    {142,52},
    {151,49},
    {160,47},
    {170,47},
    {179,48},
    {188,51},
    {-1,-1},
  },

  // 15: Luxor - Pyramid
  {
    {212,71},
    {217,66},
    {225,63},
    {234,63},
    {244,63},
    {253,62},
    {261,59},
    {-1,-1},
  },

    // 16: CityEnter - CityMidlle
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 17: CityMidlle - CityObelisk
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 18: CityObelisk - EnterCave
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 19: EnterCave - KingValley
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 20: KingValley - TombofMenes
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 21: TombofMenes - TombofRamsesII
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 22: TombofRamsesII - SecretTomb
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 23: SecretTomb - KingValleyExit
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 24: KingValleyExit - KarnakEnter
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 25:KarnakEnter - KarnakEnterComplex
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 26: KarnakEnterComplex - KarnakTemple
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 27: KarnakTemple -KarnakLakeandAlley
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 28: KarnakLakeandAlley - BabilonTemple
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 29: BabilonTemple - Hatshepsut Alpha
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 30: Hatshepsut Alpha - Pyramid Valley
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },


     // 31: Pyramid Valley - WaterPlanetIntro
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 32: WaterPlanetIntro - WaterPlanetTerra
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 33: WaterPlanetTerra - WaterPlanetEnd
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 34: WaterPlanetEnd - LavaPlanetValley
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 35: LavaPlanetValley - LavaPlanetCanyon
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 36: LavaPlanetCanyon - LavaPlanetVulcan
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 37: LavaPlanetVulcan - GreenPlanet
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 38: GreenPlanet - IcePlanet
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 39: IcePlanet - IcePlanetEnd
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

       // 40: IcePlanetEnd - TropicPlanet
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

       // 41: TropicPlanet - TropicPlanetEnd
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

       // 42: TropicPlanetEnd - RockPlanet
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

     // 43: RockPlanet - SpaceCrusader
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },

       // 44: mentaltomb - SpaceCrusader
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {-1,-1},
  },
};

BOOL ObtainMapData(void)
{
  try {
    atoIcons[ 0].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level00.tex"));
    atoIcons[ 1].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level01.tex"));
    atoIcons[ 2].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level02.tex"));
    atoIcons[ 3].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level03.tex"));
    atoIcons[ 4].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level04.tex"));
    atoIcons[ 5].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level05.tex"));
    atoIcons[ 6].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level06.tex"));
    atoIcons[ 7].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level07.tex"));
    atoIcons[ 8].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level08.tex"));
    atoIcons[ 9].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level09.tex"));
    atoIcons[10].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level10.tex"));
    atoIcons[11].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level11.tex"));
    atoIcons[12].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level12.tex"));
    atoIcons[13].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level13.tex"));
    atoIcons[14].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level14.tex"));
	atoIcons[15].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level15.tex"));
	atoIcons[16].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level16.tex"));
	atoIcons[17].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level17.tex"));
	atoIcons[18].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level18.tex"));
	atoIcons[19].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level19.tex"));
	atoIcons[20].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level20.tex"));
	atoIcons[21].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level21.tex"));
	atoIcons[22].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level22.tex"));
	atoIcons[23].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level23.tex"));
	atoIcons[24].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level24.tex"));
	atoIcons[25].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level25.tex"));
	atoIcons[26].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level26.tex"));
	atoIcons[27].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level27.tex"));
	atoIcons[28].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level28.tex"));
	atoIcons[29].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level29.tex"));
	atoIcons[30].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level30.tex"));
	atoIcons[31].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level31.tex"));
	atoIcons[32].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level32.tex"));
	atoIcons[33].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level33.tex"));
	atoIcons[34].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level34.tex"));
	atoIcons[35].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level35.tex"));
	atoIcons[36].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level36.tex"));
	atoIcons[37].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level37.tex"));
	atoIcons[38].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level38.tex"));
	atoIcons[39].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level39.tex"));
	atoIcons[40].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level40.tex"));
	atoIcons[41].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level41.tex"));
	atoIcons[42].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level42.tex"));
	atoIcons[43].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level43.tex"));
	atoIcons[44].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level44.tex"));
	atoIcons[45].SetData_t(CTFILENAME("Textures\\Computer\\Map\\Level45.tex"));
    _toPathDot  .SetData_t(CTFILENAME("Textures\\Computer\\Map\\PathDot.tex"));
    _toMapBcgLD .SetData_t(CTFILENAME("Textures\\Computer\\Map\\MapBcgLD.tex"));
    _toMapBcgLU .SetData_t(CTFILENAME("Textures\\Computer\\Map\\MapBcgLU.tex"));
    _toMapBcgRD .SetData_t(CTFILENAME("Textures\\Computer\\Map\\MapBcgRD.tex"));
    _toMapBcgRU .SetData_t(CTFILENAME("Textures\\Computer\\Map\\MapBcgRU.tex"));
    // force constant textures
    ((CTextureData*)atoIcons[ 0].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[ 1].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[ 2].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[ 3].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[ 4].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[ 5].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[ 6].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[ 7].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[ 8].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[ 9].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[10].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[11].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[12].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[13].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[14].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[15].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)atoIcons[16].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[17].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[18].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[19].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[20].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[21].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[22].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[23].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[24].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[25].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[26].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[27].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[28].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[29].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[30].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[31].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[32].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[33].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[34].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[35].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[36].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[37].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[38].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[39].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[40].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[41].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[42].GetData())->Force(TEX_CONSTANT);
	((CTextureData*)atoIcons[43].GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toPathDot  .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toMapBcgLD .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toMapBcgLU .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toMapBcgRD .GetData())->Force(TEX_CONSTANT);
    ((CTextureData*)_toMapBcgRU .GetData())->Force(TEX_CONSTANT);
  } 
  catch (char *strError) {
    CPrintF("%s\n", strError);
    return FALSE;
  }
  return TRUE;
}

void ReleaseMapData(void)
{
  atoIcons[0].SetData(NULL);
  atoIcons[1].SetData(NULL);
  atoIcons[2].SetData(NULL);
  atoIcons[3].SetData(NULL);
  atoIcons[4].SetData(NULL);
  atoIcons[5].SetData(NULL);
  atoIcons[6].SetData(NULL);
  atoIcons[7].SetData(NULL);
  atoIcons[8].SetData(NULL);
  atoIcons[9].SetData(NULL);
  atoIcons[10].SetData(NULL);
  atoIcons[11].SetData(NULL);
  atoIcons[12].SetData(NULL);
  atoIcons[13].SetData(NULL);
  atoIcons[14].SetData(NULL);
  atoIcons[15].SetData(NULL);
  atoIcons[16].SetData(NULL);
  atoIcons[17].SetData(NULL);
  atoIcons[18].SetData(NULL);
  atoIcons[19].SetData(NULL);
  atoIcons[20].SetData(NULL);
  atoIcons[21].SetData(NULL);
  atoIcons[22].SetData(NULL);
  atoIcons[23].SetData(NULL);
  atoIcons[24].SetData(NULL);
  atoIcons[25].SetData(NULL);
  atoIcons[26].SetData(NULL);
  atoIcons[27].SetData(NULL);
  atoIcons[28].SetData(NULL);
  atoIcons[29].SetData(NULL);
  atoIcons[30].SetData(NULL);
  atoIcons[31].SetData(NULL);
  atoIcons[32].SetData(NULL);
  atoIcons[33].SetData(NULL);
  atoIcons[34].SetData(NULL);
  atoIcons[35].SetData(NULL);
  atoIcons[36].SetData(NULL);
  atoIcons[37].SetData(NULL);
  atoIcons[38].SetData(NULL);
  atoIcons[39].SetData(NULL);
  atoIcons[40].SetData(NULL);
  atoIcons[41].SetData(NULL);
  atoIcons[42].SetData(NULL);
  atoIcons[43].SetData(NULL);
  atoIcons[44].SetData(NULL);
  atoIcons[45].SetData(NULL);
  _toPathDot.SetData(NULL);
  _toMapBcgLD.SetData(NULL);
  _toMapBcgLU.SetData(NULL);
  _toMapBcgRD.SetData(NULL);
  _toMapBcgRU.SetData(NULL);
}

void RenderMap( CDrawPort *pdp, ULONG ulLevelMask, CProgressHookInfo *pphi)
{
  if( !ObtainMapData())
  {
    ReleaseMapData();
    return;
  }

  // For alpha maps, we are using 1024x512 textures
  // Textures must fill entire screen
  static PIXaabbox2D _LoadingTX;
  PIX ModX = pdp->GetWidth();
  PIX ModY = pdp->GetHeight();
  _LoadingTX = PIXaabbox2D (PIX2D(0,0), PIX2D(ModX, ModY));

  // Regular icon mapping for tfe
  PIX pixdpw = pdp->GetWidth();
  PIX pixdph = pdp->GetHeight();
  PIX imgw = 512;
  PIX imgh = 480;
  FLOAT fStretch = 2.5f;
    //FLOAT fAlphaStretch = 2.0f;
  
  // determine max available picture stretch
  if( pixdpw>=imgw*2 && pixdph>=imgh*2) {
    fStretch = 2.1f;
  } else if(pixdpw>=imgw && pixdph>=imgh) {
    fStretch = 1.0f;
  } else if(pixdpw>=imgw/2 && pixdph>=imgh/2) {
    fStretch = 1.0f;
  } 

  // calculate LU offset so picture would be centerd in dp
  PIX pixSX = (pixdpw-imgw*fStretch)/2;
  PIX pixSY = Max( PIX((pixdph-imgh*fStretch)/2), PIX(0));

  // render pale map bcg
  PIX pixC1S = pixSX;                  // column 1 start pixel
  PIX pixR1S = pixSY;                  // raw 1 start pixel
  PIX pixC1E = pixSX+256*fStretch;     // column 1 end pixel
  PIX pixR1E = pixSY+256*fStretch;     // raw 1 end pixel
  PIX pixC2S = pixC1E-fStretch;        // column 2 start pixel
  PIX pixR2S = pixR1E-fStretch;        // raw 2 start pixel
  PIX pixC2E = pixC2S+256*fStretch;    // column 2 end pixel
  PIX pixR2E = pixR2S+256*fStretch;    // raw 2 end pixel
  pdp->PutTexture( &_toMapBcgLU, PIXaabbox2D( PIX2D(pixC1S,pixR1S), PIX2D(pixC1E,pixR1E)), C_WHITE|255);
  pdp->PutTexture( &_toMapBcgRU, PIXaabbox2D( PIX2D(pixC2S,pixR1S), PIX2D(pixC2E,pixR1E)), C_WHITE|255);
  pdp->PutTexture( &_toMapBcgLD, PIXaabbox2D( PIX2D(pixC1S,pixR2S), PIX2D(pixC1E,pixR2E)), C_WHITE|255);
  pdp->PutTexture( &_toMapBcgRD, PIXaabbox2D( PIX2D(pixC2S,pixR2S), PIX2D(pixC2E,pixR2E)), C_WHITE|255);
 
  // render icons
  for( INDEX iIcon=0; iIcon<ARRAYCOUNT(aIconCoords); iIcon++)
  {
    // if level's icon should be rendered
    if( ulLevelMask & (1UL<<iIcon))
    {
      PIX pixX = aIconCoords[iIcon][0]*fStretch+pixC1S;
      PIX pixY = aIconCoords[iIcon][1]*fStretch+pixR1S;
      CTextureObject *pto = &atoIcons[iIcon];
      PIX pixImgW = ((CTextureData *)pto->GetData())->GetPixWidth()*fStretch;
      PIX pixImgH = ((CTextureData *)pto->GetData())->GetPixHeight()*fStretch;
      pdp->PutTexture( pto, /*PIXaabbox2D( PIX2D(pixX, pixY), PIX2D(pixX+pixImgW, pixY+pixImgH))*/_LoadingTX, C_WHITE|255);
    }
  }
  
  // render paths
  for( INDEX iPath=0; iPath<ARRAYCOUNT(aPathPrevNextLevels); iPath++)
  {
    INDEX iPrevLevelBit = aPathPrevNextLevels[iPath][0];
    INDEX iNextLevelBit = aPathPrevNextLevels[iPath][1];
    
    // if path dots should be rendered:
    // if path src and dst levels were discovered and secreet level isn't between ot hasn't been discovered
    if( ulLevelMask&(1UL<<iPrevLevelBit) &&
        ulLevelMask&(1UL<<iNextLevelBit) &&
        ((iNextLevelBit-iPrevLevelBit)==1 || !(ulLevelMask&(1UL<<(iNextLevelBit-1)))))
    {
      for( INDEX iDot=0; iDot<10; iDot++)
      {
        PIX pixDotX=pixC1S+aPathDots[iPath][iDot][0]*fStretch;
        PIX pixDotY=pixR1S+aPathDots[iPath][iDot][1]*fStretch;
        if(aPathDots[iPath][iDot][0]==-1) break;
        pdp->PutTexture( &_toPathDot, PIXaabbox2D( PIX2D(pixDotX, pixDotY), PIX2D(pixDotX+8*fStretch, pixDotY+8*fStretch)),
          C_WHITE|255);
      }
    }
  }

  if( pphi != NULL)
  {
    // set font
    pdp->SetFont( _pfdDisplayFont);
    pdp->SetTextScaling(fStretch);
    pdp->SetTextAspect( 1.0f);
    // set coordinates
    PIX pixhtcx = pixC1S+105*fStretch;          // hook text center x
    PIX pixhtcy = pixR1S+460*fStretch;          // hook text center y
	CTString strDescription = "Loading screen to be re-designed";

    COLOR colText = RGBToColor(200,128,56)|CT_OPAQUE;
    pdp->PutTextC( /*pphi->phi_strDescription*/strDescription, pixhtcx, pixhtcy, colText);
    for( INDEX iProgresDot=0; iProgresDot<64; iProgresDot+=1)
    {
      PIX pixDotX=pixC1S+(48+iProgresDot*8)*fStretch;
      PIX pixDotY=pixR1S+489*fStretch;

      COLOR colDot = C_WHITE|255;
      if(iProgresDot>pphi->phi_fCompleted*64)
      {
        colDot = C_WHITE|64;
      }
      pdp->PutTexture( &_toPathDot, PIXaabbox2D( PIX2D(pixDotX, pixDotY), 
        PIX2D(pixDotX+8*fStretch, pixDotY+8*fStretch)), colDot);
    }
  }

  // free textures used in map rendering
  ReleaseMapData();
}
