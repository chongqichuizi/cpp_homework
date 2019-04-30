// EZNumberEdit.cpp: implementation of the EZNumberEdit class.
//
//////////////////////////////////////////////////////////////////////

#include <EZNumberEdit.h>
#include <ezevent.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EZNumberEdit::EZNumberEdit()
{
}

EZNumberEdit::~EZNumberEdit()
{

}

void EZNumberEdit::onPreCreate(CREATESTRUCT *cs)
{
  EZLineEdit::onPreCreate(cs);
}

int EZNumberEdit::getIntNumber()
{
  std::string text = getText();

  if(text.length()<=0) return 0;
  else
	  return atoi(text.c_str());
}

float EZNumberEdit::getFloatNumber()
{
  std::string text = getText();

  if(text.length()<=0) return 0.0f;
  else
	  return atof(text.c_str());
}

void EZNumberEdit::onChildControlAction(EZEvent *ev)
{
  EZControlActionEvent event(*ev);
  bool changed = false;

  if(event.getNotifyCode() == EN_UPDATE)
  {
	  std::string text = getText();
		
	  // do we have crap?
	  for(int i=0;i<text.length();i++)
	  {
         if((text[i] < '0' || text[i] > '9') && text[i] != '.')
		 {
			 changed = true;

			 // remove char
			 text.replace(i,1,"");
		 }
	  }
	  if(changed)
		  setText(text.c_str());
  }
}
