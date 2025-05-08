del /q *.ncb
del /s /q *.pdb
del /s /q *.ilk
del /s /q *.exe
for /d %%G in ("*") do rmdir /s /q "%%G/Garbage/"

rmdir /s /q "Installer/Debug/"
rmdir /s /q "Installer/Release"

del /s /q OgreMain.dll
del /s /q OgreMain_d.dll

del /s /q OIS.dll
del /s /q OIS_d.dll

del /s /q CEGUIBase.dll
del /s /q CEGUIBase_d.dll

del /s /q CEGUIExpatParser.dll
del /s /q CEGUIExpatParser_d.dll

del /s /q CEGUIFalagardWRBase.dll
del /s /q CEGUIFalagardWRBase_d.dll

del /s /q OgreGUIRenderer.dll
del /s /q OgreGUIRenderer_d.dll

del /s /q RenderSystem_Direct3D9.dll
del /s /q RenderSystem_Direct3D9_d.dll

del /s /q Plugin_ParticleFX.dll
del /s /q Plugin_ParticleFX_d.dll