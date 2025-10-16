TEMPLATE	=   lib
CONFIG		+=  debug  c++11 
CONFIG		+=  qt
TARGET		=   PluginAbaqus
QT          +=  core xml gui widgets printsupport
DEFINES     +=  PLUGINABAQUS_API

include(./PluginAbaqus.pri)
include(../vtk.pri)

win32{

  INCLUDEPATH	+=  ./ \
                    ../ \

  Release:DESTDIR         = ../../output/bin/plugins 
  Release:MOC_DIR         = ./release/moc 
  Release:RCC_DIR         = ./release/rcc
  Release:UI_DIR          = ./release/qui
  Release:OBJECTS_DIR     = ./release/obj
  Release:LIBS +=  \
  -L../../output/bin -lPluginManager \
  -L../../output/bin -lModelData \
  -L../../output/bin -lModuleBase \
  -L../../output/bin -lDataProperty \
  -L../../output/bin -lProjectTree \
  -L../../output/bin -lMainWidgets \
  -L../../output/bin -lProjectTreeExtend \
  -L../../output/bin -lMeshData \
  -L../../output/bin -lIO \
  -L../../output/bin -lSelfDefObject \
  -L../../output/bin -lPostWidgets \
  
 
  Debug:CONFIG	    	+=  console
  Debug:DESTDIR         = ../../output/bin_d/plugins
  Debug:MOC_DIR         = ./debug/moc 
  Debug:RCC_DIR         = ./debug/rcc 
  Debug:UI_DIR          = ./debug/qui 
  Debug:OBJECTS_DIR     = ./debug/obj 
  Debug:LIBS +=  \
  -L../../output/bin_d -lPluginManager \
  -L../../output/bin_d -lModelData \
  -L../../output/bin_d -lModuleBase \
  -L../../output/bin_d -lDataProperty \
  -L../../output/bin_d -lProjectTree \
  -L../../output/bin_d -lMainWidgets \
  -L../../output/bin_d -lProjectTreeExtend \
  -L../../output/bin_d -lMeshData \
  -L../../output/bin_d -lIO \
  -L../../output/bin_d -lSelfDefObject \
  -L../../output/bin_d -lPostWidgets \
  

  
  message("Windows PluginAbaqus build")
  
}


unix{
    INCLUDEPATH	+=   ./ \
		      ../ \
					 
  CONFIG          += plugin
  DESTDIR         = ../../output/bin
  MOC_DIR         = ./release/moc
  UI_DIR          = ./release/qui
  RCC_DIR         = ./release/rcc
  OBJECTS_DIR     = ./release/obj
  LIBS += \
  -L../../output/bin -lDataProperty \
	
  message("Linux PluginAbaqus build")
  
}
RESOURCES += ./resource/resource.qrc \


TRANSLATIONS += ./resource/translation/pluginabaqus_zh.ts