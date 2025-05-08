#include "stdafx.h"
#include "OgreOverlay.h"

System_Overlay :: System_Overlay(const std::string & Label)
{
	m_pOverlayManger = SmartPtr<Ogre::OverlayManager>(Ogre::OverlayManager::getSingletonPtr());
	m_pOverlay = SmartPtr<Ogre::Overlay>(m_pOverlayManger->create(Label));
	if(!m_pOverlay.get())
		MessageBoxA(NULL, "OverLay", System_Utility::FormatText("Unable To Create %s OverLay", Label.c_str()).c_str(), MB_ICONERROR | MB_OK);

}

System_Overlay :: ~System_Overlay()
{ 		
	m_pOverlay.release();
	m_pOverlayManger.release();
}

System_Overlay2D::System_Overlay2D(const std::string & Label)
:	System_Overlay(Label)
{
	m_pPanel = static_cast<Ogre::OverlayContainer*>(m_pOverlayManger->createOverlayElement("Panel", Label));
	m_pPanel->setDimensions(1, 1);
	m_pPanel->setPosition(0, 0);
	m_pPanel->show();

	m_pOverlay->add2D(m_pPanel);
	m_pOverlay->hide();
}

System_Overlay2D :: ~System_Overlay2D()
{
	try
	{
		for(int i = 0; i < m_Elements.size(); i++)
		{
			m_pPanel->removeChild(m_Elements[i]->getName());
			m_pOverlayManger->destroyOverlayElement(m_Elements[i]);
			m_Elements[i] = NULL;
		}
		m_Elements.clear();
		m_pOverlayManger->destroyOverlayElement(m_pPanel);
		m_pPanel = NULL;
		m_pOverlayManger->destroy(m_pOverlay.get());
	}
	catch(std::exception & e)
	{
		UNREFERENCED_PARAMETER(e);
		WriteCommandLine("Problem -SysOgreOverlay Shutdown : \n%s", e.what());
	}
}

Ogre::OverlayElement	*	System_Overlay2D::AddElement	(const std::string &Material,
															 const std::string label,
															const float & PosX, const float & PosY,
															const float & SizeX, const float & SizeY)
{
	Ogre::OverlayElement	*	Element = m_pOverlayManger->createOverlayElement("Panel", label);
	Element->setMaterialName(Material);
	Element->setMetricsMode(Ogre::GMM_PIXELS);

	Element->setDimensions(SizeX, SizeY);
	Element->setWidth(SizeX);
	Element->setHeight(SizeY);
	Element->setUseIdentityView(true);

	Element->setPosition(PosX, PosY);
	m_Elements.push_back(Element);
	m_pPanel->addChild(Element);
	Element->show();
	return Element;
}


System_OverlayText :: System_OverlayText(const std::string &Label, const std::string & Font)
:System_Overlay(Label), m_FontName(Font)
{
	m_pPanel = static_cast<Ogre::OverlayContainer*>(m_pOverlayManger->createOverlayElement("Panel", Label + "_TextContainer"));
	m_pPanel->setDimensions(1, 1);
	m_pPanel->setPosition(0, 0);
	m_pPanel->show();

	m_pOverlay->add2D(m_pPanel);
	m_pOverlay->show();

	Ogre::FontPtr Fnt = Ogre::FontManager::getSingletonPtr()->getByName(Font);
	if(!Fnt.get())
	{
		Fnt = Ogre::FontManager::getSingletonPtr()->create(Font, "GUI");
		Fnt->setType(Ogre::FT_TRUETYPE);
		Fnt->setSource(Font + ".ttf");
		Fnt->setTrueTypeResolution(72);
		Fnt->setTrueTypeSize(36);
		//Fnt->addCodePointRange(Ogre::Font::CodePointRange(33, 255));
	}
}

System_OverlayText::~System_OverlayText()
{
	try
	{
		std::map<std::string, Ogre::OverlayElement *>::iterator it = m_Elements.begin();
		for(it; it != m_Elements.end(); it++)
		{
			m_pPanel->removeChild(it->second->getName());
			m_pOverlayManger->destroyOverlayElement(it->second);
			it->second = NULL;
		}
		m_Elements.clear();
		m_pOverlayManger->destroyOverlayElement(m_pPanel);
		m_pPanel = NULL;
		m_pOverlayManger->destroy(m_pOverlay.get());
	}
	catch(std::exception & e)
	{
		UNREFERENCED_PARAMETER(e);
		WriteCommandLine("Problem -SysOgreOverlayText Shutdown : \n%s", e.what());
	}
}

Ogre::TextAreaOverlayElement *	System_OverlayText :: AddTextBox(	const std::string & Key, const std::string & Text, 
																	const float & PosX, const float & PosY,
																	const float & Size,
																	const Ogre::ColourValue & Color)
{
	std::map<std::string, Ogre::OverlayElement *>::iterator it = m_Elements.find(Key);
	if(it != m_Elements.end())
	{
		WriteCommandLine("Text Box %s Already Existed", Key.c_str()); 
		return static_cast<Ogre::TextAreaOverlayElement *>(it->second);
	}
	Ogre::TextAreaOverlayElement * TextBox = static_cast<Ogre::TextAreaOverlayElement *>(m_pOverlayManger->createOverlayElement("TextArea", Key));

	TextBox->setMetricsMode(Ogre::GMM_PIXELS);
	TextBox->setPosition(PosX, PosY);
	TextBox->setCaption(Text);
	TextBox->setFontName(m_FontName);
	
	TextBox->setCharHeight(Size);
	TextBox->setColour(Color);
	m_pPanel->addChild(TextBox);
	TextBox->show();

	m_Elements.insert(std::make_pair(Key, TextBox));
	return TextBox;
}

//void	System_OverlayText :: RemoveTextBox(const std::string & Key)
//{
//	m_pPanel->removeChild(Key);
//	m_pOverlayManger->destroyOverlayElement(Key);
//}
//
//
//void	System_OverlayText :: SetText(const std::string & Key, const std::string & Text)
//{
//	Ogre::OverlayElement * TextBox = m_pOverlayManger->getOverlayElement(Key);
//	TextBox->setCaption(Text);
//}

