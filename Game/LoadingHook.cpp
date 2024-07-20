
#include "stdafx.h"
#include "LCDDrawing.h"
#include <locale.h>

#define USECUSTOMTEXT 0

extern CGame *_pGame;

#if USECUSTOMTEXT
  static CTString _strCustomText = "";
#endif
static CDrawPort *_pdpLoadingHook = NULL;  // drawport for loading hook
extern BOOL _bUserBreakEnabled;

#define REFRESHTIME (0.1f)

static void LoadingHook_t(CProgressHookInfo *pphi)
{
  // if user presses escape
  ULONG ulCheckFlags = 0x8000;
  if (pphi->phi_fCompleted>0) {
    ulCheckFlags |= 0x0001;
  }
  if (_bUserBreakEnabled && (GetAsyncKeyState(VK_ESCAPE)&ulCheckFlags)) {
    // break loading
    throw TRANS("User break!");
  }

#if USECUSTOMTEXT
  // if no custom loading text
  if (_strCustomText=="") {
    // load it
    try {
      _strCustomText.Load_t(CTFILENAME("Data\\LoadingText.txt"));
    } catch (char *strError) {
      _strCustomText = strError;
    }
  }
#endif

  // measure time since last call
  static CTimerValue tvLast(0I64);
  CTimerValue tvNow = _pTimer->GetHighPrecisionTimer();

  // if not first or final update, and not enough time passed
  if (pphi->phi_fCompleted!=0 && pphi->phi_fCompleted!=1 &&
     (tvNow-tvLast).GetSeconds() < REFRESHTIME) {
    // do nothing
    return;
  }
  tvLast = tvNow;

  // if cannot lock drawport
  CDrawPort *pdp = _pdpLoadingHook;
  ASSERT(pdp!=NULL);
  CDrawPort dpHook(pdp, TRUE);
    // Diffrent font test
    CFontData _fdMedium;
    _fdMedium.Load_t( CTFILENAME( "Fonts\\Display3-normal.fnt"));
    _fdMedium.SetCharSpacing(+1);
    _fdMedium.SetLineSpacing( 0);
    _fdMedium.SetSpaceWidth(0.4f);

  if(!dpHook.Lock()) {
    // do nothing
    return;
  }

  // clear screen
  dpHook.Fill(C_BLACK|255);

  // get session properties currently loading
  CSessionProperties *psp = (CSessionProperties *)_pNetwork->GetSessionProperties();
  ULONG ulLevelMask = psp->sp_ulLevelsMask;
  INDEX iLevel = -1;
  if (psp->sp_bCooperative) {
    INDEX iLevel = -1;
    INDEX iLevelNext = -1;
    CTString strLevelName = _pNetwork->ga_fnmWorld.FileName();
    CTString strNextLevelName = _pNetwork->ga_fnmNextLevel.FileName();
    strLevelName.ScanF("%02d_", &iLevel);
    strNextLevelName.ScanF("%02d_", &iLevelNext);
    if (iLevel>0) {
      ulLevelMask|=1<<(iLevel-1);
    }
    if (iLevelNext>0) {
      ulLevelMask|=1<<(iLevelNext-1);
    }
  }

  if (ulLevelMask!=0 && !_pNetwork->IsPlayingDemo()) {
    // map hook
    extern void RenderMap( CDrawPort *pdp, ULONG ulLevelMask, CProgressHookInfo *pphi);
    RenderMap(&dpHook, ulLevelMask, pphi);

    // finish rendering
    dpHook.Unlock();
    dpHook.dp_Raster->ra_pvpViewPort->SwapBuffers();
    return;
  }

  // get sizes
  PIX pixSizeI = dpHook.GetWidth();
  PIX pixSizeJ = dpHook.GetHeight();
  CFontData *pfd = _pfdConsoleFont;
  PIX pixCharSizeI = pfd->fd_pixCharWidth  + pfd->fd_pixCharSpacing;
  PIX pixCharSizeJ = pfd->fd_pixCharHeight + pfd->fd_pixLineSpacing;

  PIX pixBarSizeJ = 25;//*pixSizeJ/480;

  COLOR colBcg = LerpColor(C_BLACK, C_YELLOW, 0.30f)|0xff;
  COLOR colBar = LerpColor(C_BLACK, C_YELLOW, 0.45f)|0xff;
  COLOR colLines = colBar; //C_vdGREEN|0xff;
  COLOR colText = LerpColor(C_BLACK, C_YELLOW, 0.85f)|0xff;
  COLOR colEsc = C_WHITE|0xFF;

  dpHook.Fill(0, pixSizeJ-pixBarSizeJ, pixSizeI, pixBarSizeJ, colBcg);
  dpHook.Fill(0, pixSizeJ-pixBarSizeJ, pixSizeI*pphi->phi_fCompleted, pixBarSizeJ, colBar);
  dpHook.DrawBorder(0, pixSizeJ-pixBarSizeJ, pixSizeI, pixBarSizeJ, colLines);

  dpHook.SetFont( _pfdDisplayFont);
  dpHook.SetTextScaling( 1.0f);
  dpHook.SetTextAspect( 1.0f);
  // print status text
  setlocale(LC_ALL, "");
  //CTString strDesc(0, "%s", pphi->phi_strDescription);  strupr((char*)(const char*)strDesc);
  CTString strDesc = "^i^f7Loading...";
  setlocale(LC_ALL, "C");
  CTString strPerc(0, "%3.0f%%", pphi->phi_fCompleted*100);
  dpHook.PutText(strDesc, pixCharSizeI/2, pixSizeJ/1.01-pixBarSizeJ-2-pixCharSizeJ, C_YELLOW|255);
  //dpHook.PutTextCXY(strPerc, pixSizeI/2, pixSizeJ-pixBarSizeJ/2+1, C_GREEN|255);
  //dpHook.PutText(strDesc, pixCharSizeI/2, pixSizeJ-pixBarSizeJ+pixCharSizeJ/2, colText);
    dpHook.SetFont(_pfdDisplayFont);
    dpHook.SetTextScaling( 2.0f);
    dpHook.SetTextAspect( 1.0f);

	dpHook.PutTextC( TRANS( "^iAlpha Remake build 184"), pixSizeI/1.95, pixCharSizeJ/3, C_YELLOW|255);
	dpHook.SetFont( _pfdDisplayFont);
    dpHook.SetTextScaling( 1.0f);
    dpHook.SetTextAspect( 1.0f);
    //dpHook.PutTextC( TRANS( "If you found any bugs or problems,send private message to facebook page."), pixSizeI/1.95, pixSizeJ/8, C_WHITE|255);
	//dpHook.PutTextC( TRANS( "Facebook.com/SeriousSamAlphaRemake"), pixSizeI/1.95, pixSizeJ/6, C_WHITE|255);
    dpHook.PutTextC( TRANS( "SSA-RM 2015-2020. Created by ^i^c0099ffZdzichu^cffffff.\n"), pixSizeI/1.3, pixSizeJ/1.1, C_WHITE|255);
	dpHook.SetFont( _pfdDisplayFont);
    dpHook.SetTextScaling( 1.0f);
    dpHook.SetTextAspect( 1.0f);
    dpHook.PutTextR(strPerc, pixSizeI-pixCharSizeI/2, pixSizeJ/1.024-pixBarSizeJ+pixCharSizeJ/2, colText);


	// final
    /*dpHook.PutTextC( TRANS( "^iSerious Sam Alpha Remake"), pixSizeI/1.95, pixCharSizeJ/3, C_YELLOW|255);
	dpHook.SetFont( _pfdDisplayFont);
    dpHook.SetTextScaling( 1.0f);
    dpHook.SetTextAspect( 1.0f);
    dpHook.PutTextC( TRANS( "If you found any bugs or problems,send private message to facebook page."), pixSizeI/1.95, pixSizeJ/8, C_WHITE|255);
	dpHook.PutTextC( TRANS( "Facebook.com/SeriousSamAlphaRemake"), pixSizeI/1.95, pixSizeJ/6, C_WHITE|255);
    dpHook.PutTextC( TRANS( "SSA-RM 2015-2018. Created by ^i^c0099ffZdzichu^cffffff.\n"), pixSizeI/1.3, pixSizeJ/1.1, C_WHITE|255);
	dpHook.SetFont( _pfdDisplayFont);
    dpHook.SetTextScaling( 1.0f);
    dpHook.SetTextAspect( 1.0f);
    dpHook.PutTextR(strPerc, pixSizeI-pixCharSizeI/2, pixSizeJ/1.024-pixBarSizeJ+pixCharSizeJ/2, colText);*/
	// final

  if (_bUserBreakEnabled && !_pGame->gm_bFirstLoading) {
    dpHook.PutTextC( TRANS( "PRESS ESC TO ABORT"), pixSizeI/2, pixSizeJ-pixBarSizeJ-2-pixCharSizeJ, colEsc);
  }

/*  
  //LCDPrepare(1.0f);
  //LCDSetDrawport(&dpHook);
  
  // fill the box with background dirt and grid
  //LCDRenderClouds1();
  //LCDRenderGrid();

  // draw progress bar
  PIX pixBarCentI = pixBoxSizeI*1/2;
  PIX pixBarCentJ = pixBoxSizeJ*3/4;
  PIX pixBarSizeI = pixBoxSizeI*7/8;
  PIX pixBarSizeJ = pixBoxSizeJ*3/8;
  PIX pixBarMinI = pixBarCentI-pixBarSizeI/2;
  PIX pixBarMaxI = pixBarCentI+pixBarSizeI/2;
  PIX pixBarMinJ = pixBarCentJ-pixBarSizeJ/2;
  PIX pixBarMaxJ = pixBarCentJ+pixBarSizeJ/2;

  dpBox.Fill(pixBarMinI, pixBarMinJ, 
    pixBarMaxI-pixBarMinI, pixBarMaxJ-pixBarMinJ, C_BLACK|255);
  dpBox.Fill(pixBarMinI, pixBarMinJ, 
    (pixBarMaxI-pixBarMinI)*pphi->phi_fCompleted, pixBarMaxJ-pixBarMinJ, C_GREEN|255);

  // put more dirt
  LCDRenderClouds2Light();

  // draw borders
  COLOR colBorders = LerpColor(C_GREEN, C_BLACK, 200);
  LCDDrawBox(0,-1, PIXaabbox2D(
    PIX2D(pixBarMinI, pixBarMinJ), 
    PIX2D(pixBarMaxI, pixBarMaxJ)), 
    colBorders|255);
  LCDDrawBox(0,-1, PIXaabbox2D(
    PIX2D(0,0), PIX2D(dpBox.GetWidth(), dpBox.GetHeight())), 
    colBorders|255);

  // print status text
  dpBox.SetFont( _pfdDisplayFont);
  dpBox.SetTextScaling( 1.0f);
  dpBox.SetTextAspect( 1.0f);
  // print status text
  CTString strRes;
  strRes.PrintF( "%s", pphi->phi_strDescription);
  //strupr((char*)(const char*)strRes);
  dpBox.PutTextC( strRes, 160, 17, C_GREEN|255);
  strRes.PrintF( "%3.0f%%", pphi->phi_fCompleted*100);
  dpBox.PutTextCXY( strRes, pixBarCentI, pixBarCentJ, C_GREEN|255);
  dpBox.Unlock();

  if( Flesh.gm_bFirstLoading) {
#if USECUSTOMTEXT
    FLOAT fScaling = (FLOAT)slSizeI/640.0f;
    dpHook.Lock();
    dpHook.SetFont( _pfdDisplayFont);
    dpHook.SetTextScaling( fScaling);
    dpHook.SetTextAspect( 1.0f);
    //dpHook.Fill( 0, 0, slSizeI, pixCenterJ, C_vdGREEN|255, C_vdGREEN|255, C_vdGREEN|0, C_vdGREEN|0);
    dpHook.PutTextC( TRANS( "SERIOUS SAM - TEST VERSION"), pixCenterI, 5*fScaling, C_WHITE|255);
    dpHook.PutTextC( TRANS( "THIS IS NOT A DEMO VERSION, THIS IS A COMPATIBILITY TEST!"), pixCenterI, 25*fScaling, C_WHITE|255);
    dpHook.PutTextC( TRANS( "Serious Sam (c) 2000 Croteam LLC, All Rights Reserved.\n"), pixCenterI, 45*fScaling, C_WHITE|255);
    dpHook.PutText( _strCustomText, 1*fScaling, 85*fScaling, C_GREEN|255);
    dpHook.Unlock();
#endif
  } else if (_bUserBreakEnabled) {
    FLOAT fScaling = (FLOAT)slSizeI/640.0f;
    dpHook.Lock();
    dpHook.SetFont( _pfdDisplayFont);
    dpHook.SetTextScaling( fScaling);
    dpHook.SetTextAspect( 1.0f);
    //dpHook.Fill( 0, 0, slSizeI, pixCenterJ, C_vdGREEN|255, C_vdGREEN|255, C_vdGREEN|0, C_vdGREEN|0);
    dpHook.PutTextC( TRANS( "PRESS ESC TO ABORT"), pixCenterI, pixCenterJ+pixBoxSizeJ+5*fScaling, C_WHITE|255);
  }
  */

  dpHook.Unlock();
  // finish rendering
  dpHook.dp_Raster->ra_pvpViewPort->SwapBuffers();
}

// loading hook functions
void CGame::EnableLoadingHook(CDrawPort *pdpDrawport)
{
  _pdpLoadingHook = pdpDrawport;
  SetProgressHook(LoadingHook_t);
}

void CGame::DisableLoadingHook(void)
{
  SetProgressHook(NULL);
  _pdpLoadingHook = NULL;
}
