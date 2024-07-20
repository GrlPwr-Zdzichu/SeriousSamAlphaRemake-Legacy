#include "stdafx.h"	
#include "ExtFonts.h"
#include <Engine/Build.h>
#include <Engine/CurrentVersion.h>
#include <Game/LCDDrawing.h>

extern CFontData _pfdTest;

	void SetFontTest(CDrawPort *pdp)
	{
     pdp->SetFont( &_pfdTest);
     pdp->SetTextScaling( 1.0f * pdp->GetWidth() /640 *pdp->dp_fWideAdjustment);
     pdp->SetTextAspect(0.75f);
	}

/*	void InitializeTestFont(void)
	{
	_pfdTest.Load_t(  CTFILENAME( "Fonts\\FontTest.fnt"));
	_pfdTest.SetCharSpacing(-1);
    _pfdTest.SetLineSpacing( 0);
    _pfdTest.SetSpaceWidth(0.4f);
	}*/

	



