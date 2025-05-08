#pragma once

template <class T>
class Abstract_Single
{
protected:
	static SmartPtr <T> m_pInstance;
	std::string Label;
public:
	virtual bool Initialize() = 0;
	static T * Instance() 
	{ 
		if(!m_pInstance.get())
		{
			 m_pInstance = SmartPtr<T>(new T);
			 if(!m_pInstance->Initialize())
			 {
				 std::string Text("Error Occuered in " + m_pInstance->Label + " Program will now exit");
				 MessageBoxA(NULL, Text.c_str(), "Initialization Error", MB_ICONERROR | MB_OK);
				 exit(0);
			 }	 
		}
		return m_pInstance.get();
	}
};
