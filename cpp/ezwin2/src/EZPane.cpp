// EZPane.cpp: implementation of the EZPane class.
//
//////////////////////////////////////////////////////////////////////

#include <EZPane.h>
#include <ezevent.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EZPane::EZPane()
{
}

bool EZPane::create(EZWindow *parent, const EZRect &rect)
{
	return EZWindow::create(parent,"",0,rect,-1);
}

EZPane::~EZPane()
{

}

void EZPane::onPreCreate(CREATESTRUCT *cs)
{
	cs->style |= (WS_VISIBLE);
}


