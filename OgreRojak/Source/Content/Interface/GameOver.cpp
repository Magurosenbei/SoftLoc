
#include "stdafx.h"
#include "GameOver.h"

Content_Screen_GameOver :: Content_Screen_GameOver()
: Content_Screen(), m_fDisplayTime(0.0f)
{

}

Content_Screen_GameOver :: ~Content_Screen_GameOver()
{
	delete m_pText;
}

void	Content_Screen_GameOver :: Show()
{
	m_pText->m_pOverlay->show();
	m_fDisplayTime = 0.0f;
}

void	Content_Screen_GameOver :: Hide()
{
	m_pText->m_pOverlay->hide();
}

bool	Content_Screen_GameOver :: IsVisible()
{
	return m_pText->m_pOverlay->isVisible();
}

void Content_Screen_GameOver :: SetTimeText(const float & Elapsed)
{
	std::string Text = System_Utility::FormatText("Elpased Time : %i seconds", static_cast<int>(Elapsed));
	m_pTimeText->setCaption(Text);
}

bool Content_Screen_GameOver :: Initialize(const std::string	&	ScriptFile)
{
	m_pText =	new System_OverlayText("GameOver_Screen_Txt", "bluehigh");
	m_pText->AddTextBox("ConGrates", "You completed the Level", 150, 200, 36, Ogre::ColourValue::White); 
	m_pTimeText = m_pText->AddTextBox("Time", "TimeElapsedFromStart : %f", 150, 250, 36, Ogre::ColourValue::White);
	m_pText->m_pOverlay->hide();
	return true;
}

void Content_Screen_GameOver :: Step(const float &Interval)
{
	m_fDisplayTime += Interval * 0.001f;
	if(m_fDisplayTime > 5.0f)
	{
		Hide();
	}
}