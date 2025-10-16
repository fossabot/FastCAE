SET "PATH=C:\Qt\Qt5.4.2\5.4\msvc2013_64_opengl\bin;%PATH%"

lupdate -verbose PluginAbaqus.pro

lupdate -no-obsolete PluginAbaqus.pro

cd  resource/translation/
lrelease pluginabaqus_zh.ts

pause
