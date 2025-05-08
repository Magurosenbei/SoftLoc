#include "stdafx.h"
#include "LoadingScreen.h"

Content_Screen_Loading :: Content_Screen_Loading()
: Content_Screen(), m_fSpinLogo(0.0f), m_fStepValue(0.130916f)
{
}

Content_Screen_Loading :: ~Content_Screen_Loading()
{
	delete m_pLogo;
	delete m_pText;
}

void	Content_Screen_Loading :: Show()
{
	m_pLogo->m_pOverlay->show();
	m_pText->m_pOverlay->show();
	memset(&m_fSpinLogo, 0, sizeof(m_fSpinLogo));
}

void	Content_Screen_Loading :: Hide()
{
	m_pLogo->m_pOverlay->hide();
	m_pText->m_pOverlay->hide();
}

bool	Content_Screen_Loading :: IsVisible()
{
	return m_pLogo->m_pOverlay->isVisible();
}


bool Content_Screen_Loading :: Initialize(const std::string	&	ScriptFile)
{
	m_pLogo	=	new System_Overlay2D("Load_Screen_Img");
	m_pLogo->AddElement("LoadScreen/Logo",	"Load" ,320,
											240,
											128, 128);

	m_pText =	new System_OverlayText("Load_Screen_Txt", "Hymmnos");
	m_pText->AddTextBox("Display_LoadText", "Please Wait", 500, 420, 36, Ogre::ColourValue::White); 
	return true;
}

void Content_Screen_Loading :: Step(const float &Interval)
{
	m_fSpinLogo	+=	m_fStepValue * Interval;
	m_pLogo->m_pOverlay->rotate(m_fStepValue * Interval);
}