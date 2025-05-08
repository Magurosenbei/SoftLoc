REM Copy Ogre binaries
copy C:\OgreSDK\bin\Release\OgreMain.dll Build\Release\OgreMain.dll
copy C:\OgreSDK\bin\Debug\OgreMain_d.dll Build\Debug\OgreMain_d.dll

REM Copy OIS binaries
copy C:\OgreSDK\bin\Release\OIS.dll Build\Release\OIS.dll
copy C:\OgreSDK\bin\Debug\OIS_d.dll Build\Debug\OIS_d.dll

copy C:\OgreSDK\bin\Release\CEGUIBase.dll Build\Release\CEGUIBase.dll
copy C:\OgreSDK\bin\Release\CEGUIExpatParser.dll Build\Release\CEGUIExpatParser.dll
copy C:\OgreSDK\bin\Release\CEGUIFalagardWRBase.dll Build\Release\CEGUIFalagardWRBase.dll
copy C:\OgreSDK\bin\Release\OgreGUIRenderer.dll Build\Release\OgreGUIRenderer.dll

copy C:\OgreSDK\bin\Debug\CEGUIBase_d.dll Build\Debug\CEGUIBase_d.dll
copy C:\OgreSDK\bin\Debug\CEGUIExpatParser_d.dll Build\Debug\CEGUIExpatParser_d.dll
copy C:\OgreSDK\bin\Debug\CEGUIFalagardWRBase_d.dll Build\Debug\CEGUIFalagardWRBase_d.dll
copy C:\OgreSDK\bin\Debug\OgreGUIRenderer_d.dll Build\Debug\OgreGUIRenderer_d.dll

REM DirectX binaries
copy C:\OgreSDK\bin\Release\RenderSystem_Direct3D9.dll Build\Release\Plugins\RenderSystem_Direct3D9.dll
copy C:\OgreSDK\bin\Debug\RenderSystem_Direct3D9_d.dll Build\Debug\Plugins\RenderSystem_Direct3D9_d.dll

REM OpenGL binaries
copy C:\OgreSDK\bin\Release\Plugin_ParticleFX.dll Build\Release\Plugins\Plugin_ParticleFX.dll
copy C:\OgreSDK\bin\debug\Plugin_ParticleFX_d.dll Build\Debug\Plugins\Plugin_ParticleFX_d.dll



