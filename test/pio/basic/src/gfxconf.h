#define GFX_USE_OS_FREERTOS     TRUE

// As mandated apparently for FREERTOS
#define GFX_OS_NO_INIT          TRUE

//#define GFX_USE_OS_CHIBIOS                           FALSE
//#define GFX_USE_OS_FREERTOS                          FALSE
//    #define GFX_FREERTOS_USE_TRACE                   FALSE
//#define GFX_USE_OS_WIN32                             FALSE
//#define GFX_USE_OS_LINUX                             FALSE
//#define GFX_USE_OS_OSX                               FALSE
//#define GFX_USE_OS_ECOS                              FALSE
//#define GFX_USE_OS_RAWRTOS                           FALSE
//#define GFX_USE_OS_ARDUINO                           FALSE
//#define GFX_USE_OS_KEIL                              FALSE
//#define GFX_USE_OS_CMSIS                             FALSE
//#define GFX_USE_OS_RAW32                             FALSE
//#define GFX_USE_OS_NIOS                              FALSE
//#define GFX_USE_OS_QT                                FALSE

#define GFX_USE_GDISP                                TRUE

/* Features for the GDISP sub-system.  Lifted from 'basic' demo */
#define GDISP_NEED_VALIDATION	TRUE
#define GDISP_NEED_CLIP			TRUE

#define GDISP_NEED_AUTOFLUSH    TRUE