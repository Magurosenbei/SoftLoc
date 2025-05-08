#pragma once

class Content_Screen_GameOver	:	public Content_Screen
{
	System_OverlayText				*	m_pText;
	Ogre::TextAreaOverlayElement	*	m_pTimeText;
	float					m_fDisplayTime;
public:
	Content_Screen_GameOver();
	~Content_Screen_GameOver();

	virtual	void	Show();
	virtual void	Hide();
	virtual	bool	IsVisible();

	void			SetTimeText(const float & Elapsed);

	bool			Initialize(const std::string	&	ScriptFile);
	virtual void	Step(const float & Interval);
};