#ifndef LEGATO_INIT_SCHEME_H
#define LEGATO_INIT_SCHEME_H

#include "gfx/legato/legato.h"

extern const leBlendLookupTable schemeBlendTable_RGB565_FFFF_11CD;

extern const leScheme WhiteScheme;
extern const leScheme RedScheme;
extern const leScheme GreenScheme;
extern const leScheme BlueScheme;
extern const leScheme BackScheme;
extern const leScheme TextScheme;
extern const leScheme ListScheme;
extern const leScheme TextInactiveScheme;
extern const leScheme GraphScheme;
extern const leScheme BLEPanelScheme;
extern const leScheme WifiPanelScheme;
extern const leScheme InfoGraphicBackScheme;

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

void legato_initialize_schemes(void);

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LEGATO_INIT_SCHEME_H
