REM Copy Ogre binaries
copy %OGRE_HOME%\bin\Release\OgreMain.dll Build\Release\OgreMain.dll
copy %OGRE_HOME%\bin\Debug\OgreMain_d.dll Build\Debug\OgreMain_d.dll

REM Copy OIS binaries
copy %OGRE_HOME%\bin\Release\OIS.dll Build\Release\OIS.dll
copy %OGRE_HOME%\bin\Debug\OIS_d.dll Build\Debug\OIS_d.dll

REM Copy CEGUI binaries
copy %OGRE_HOME%\bin\Release\CEGUIBase.dll Build\Release\CEGUIBase.dll
copy %OGRE_HOME%\bin\Release\CEGUIExpatParser.dll Build\Release\CEGUIExpatParser.dll
copy %OGRE_HOME%\bin\Release\CEGUIFalagardWRBase.dll Build\Release\CEGUIFalagardWRBase.dll
copy %OGRE_HOME%\bin\Release\OgreGUIRenderer.dll Build\Release\OgreGUIRenderer.dll

copy %OGRE_HOME%\bin\Debug\CEGUIBase_d.dll Build\Debug\CEGUIBase_d.dll
copy %OGRE_HOME%\bin\Debug\CEGUIExpatParser_d.dll Build\Debug\CEGUIExpatParser_d.dll
copy %OGRE_HOME%\bin\Debug\CEGUIFalagardWRBase_d.dll Build\Debug\CEGUIFalagardWRBase_d.dll
copy %OGRE_HOME%\bin\Debug\OgreGUIRenderer_d.dll Build\Debug\OgreGUIRenderer_d.dll


REM DirectX binaries
copy %OGRE_HOME%\bin\Release\RenderSystem_Direct3D9.dll Build\Release\Plugins\RenderSystem_Direct3D9.dll
copy %OGRE_HOME%\bin\Debug\RenderSystem_Direct3D9_d.dll Build\Debug\Plugins\RenderSystem_Direct3D9_d.dll

REM OpenGL binaries
copy %OGRE_HOME%\bin\Release\Plugin_ParticleFX.dll Build\Release\Plugins\Plugin_ParticleFX.dll
copy %OGRE_HOME%\bin\debug\Plugin_ParticleFX_d.dll Build\Debug\Plugins\Plugin_ParticleFX_d.dll



