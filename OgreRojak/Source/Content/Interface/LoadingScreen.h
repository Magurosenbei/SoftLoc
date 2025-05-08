#pragma once

class Content_Screen_Loading	:	public Content_Screen
{
	System_Overlay2D	*	m_pLogo;
	System_OverlayText	*	m_pText;

	Ogre::Radian			m_fSpinLogo;
	Ogre::Radian			m_fStepValue;
public:
	Content_Screen_Loading();
	~Content_Screen_Loading();

	virtual	void	Show();
	virtual void	Hide();
	virtual	bool	IsVisible();

	bool			Initialize(const std::string	&	ScriptFile);
	virtual void	Step(const float & Interval);
};