#pragma once

/*	This is just an Interface for easy access to ogre's overlay							*/
/*	All Overlay should be loaded only once since there isn't really alot of 2D elements	*/
/*	Let all loading of 2D be handled and sorted by a handler e.g Screen, LoadingScreen	*/

class System_Overlay
{
protected:
	SmartPtr<Ogre::OverlayManager>	m_pOverlayManger;
public:
	Ogre::OverlayContainer *		m_pPanel;
	SmartPtr<Ogre::Overlay>			m_pOverlay;

	System_Overlay(const std::string & Label);
	virtual ~System_Overlay(); 
};

class System_Overlay2D : public System_Overlay
{
protected:
	btAlignedObjectArray <Ogre::OverlayElement *>	m_Elements;
public:
	System_Overlay2D(const std::string & Label);
	virtual ~System_Overlay2D();
	
	// Material Name = Element Name
	Ogre::OverlayElement	*	AddElement(	const std::string & Material,
											const std::string label,
											const float & PosX, const float & PosY,
											const float & SizeX, const float & SizeY);

};


class System_OverlayText : public System_Overlay
{
	std::string										m_FontName;
	std::map<std::string, Ogre::OverlayElement *>	m_Elements;
public:
	System_OverlayText(const std::string & Label, const std::string & Font);
	virtual ~System_OverlayText();

	Ogre::TextAreaOverlayElement *	AddTextBox(	const std::string & Key, const std::string & Text, 
												const float & PosX, const float & PosY,
												const float & Size,
												const Ogre::ColourValue & Color);

/*	void	RemoveTextBox(const std::string & Key);

	void	SetText(const std::string & Key, const std::string & Text);	*/			
};