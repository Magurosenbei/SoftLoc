#pragma once

class Content_Screen
{
protected:
	bool	m_bUpdate;
public:
	Content_Screen(){}
	virtual ~Content_Screen(){}
	inline	bool	ShouldUpdate()	const {	return m_bUpdate;	}
	virtual	void	Show()	= 0;
	virtual void	Hide() = 0;
	virtual	bool	IsVisible()	= 0;
	virtual	void	Step(const float & Interval)	=	0;
};