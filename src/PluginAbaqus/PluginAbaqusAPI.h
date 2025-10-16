#ifndef _PLUGINABAQUSAPI_H__
#define _PLUGINABAQUSAPI_H__

#include <QtCore/QtGlobal>


#if defined(PLUGINABAQUS_API)
#define PLUGINABAQUSAPI Q_DECL_EXPORT
#else
#define  PLUGINABAQUSAPI Q_DECL_IMPORT
#endif

#endif
