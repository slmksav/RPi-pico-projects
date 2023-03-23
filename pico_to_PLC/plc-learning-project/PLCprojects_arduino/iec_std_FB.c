/*
File : iec_std_FB.h
Beremiz runtime
Copyright : Benoit BOUCHEZ 2022

MatIEC provides two files for standard Function Blocks :
- iec_std_FB.h
- iec_std_FB_no_ENENO.h

These two include files have C functions bodies which is a bit strange
The files have been modified in order to have only defintions in the .h
and functions bodies in this .c file
The same file is also used whatever DISABLE_EN_ENO_PARAMETERS is defined or not

Other changes:
- all useless goto __end have been removed (no idea if compiler generates dead code or is able to optimize)
- all useless return at the end of functions removed
*/

#include "iec_std_lib.h"

void R_TRIG_init__(R_TRIG *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CLK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->M,__BOOL_LITERAL(FALSE),1)
}
/* ------------------------------------------------- */

void R_TRIG_body__(R_TRIG *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CLK,) && !(__GET_VAR(data__->M,))));
  __SET_VAR(data__->,M,,__GET_VAR(data__->CLK,));
} // R_TRIG_body__() 
/* ------------------------------------------------- */

void F_TRIG_init__(F_TRIG *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
 #endif
  __INIT_VAR(data__->CLK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->M,__BOOL_LITERAL(FALSE),1)
}
/* ------------------------------------------------- */

void F_TRIG_body__(F_TRIG *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->,Q,,(!(__GET_VAR(data__->CLK,)) && !(__GET_VAR(data__->M,))));
  __SET_VAR(data__->,M,,!(__GET_VAR(data__->CLK,)));
} // F_TRIG_body__() 
/* ------------------------------------------------- */

void SR_init__(SR *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->S1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q1,__BOOL_LITERAL(FALSE),retain)
}
/* ------------------------------------------------- */

void SR_body__(SR *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->,Q1,,(__GET_VAR(data__->S1,) || (!(__GET_VAR(data__->R,)) && __GET_VAR(data__->Q1,))));
} // SR_body__() 
/* ------------------------------------------------- */

void RS_init__(RS *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->S,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q1,__BOOL_LITERAL(FALSE),retain)
}
/* ------------------------------------------------- */

void RS_body__(RS *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->,Q1,,(!(__GET_VAR(data__->R1,)) && (__GET_VAR(data__->S,) || __GET_VAR(data__->Q1,))));
} // RS_body__() 
/* ------------------------------------------------- */

void CTU_init__(CTU *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}
/* ------------------------------------------------- */

void CTU_body__(CTU *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
} // CTU_body__() 
/* ------------------------------------------------- */

void CTU_DINT_init__(CTU_DINT *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}
/* ------------------------------------------------- */

void CTU_DINT_body__(CTU_DINT *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
} // CTU_DINT_body__() 
/* ------------------------------------------------- */

void CTU_LINT_init__(CTU_LINT *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS	
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}
/* ------------------------------------------------- */

void CTU_LINT_body__(CTU_LINT *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
} // CTU_LINT_body__() 
/* ------------------------------------------------- */

void CTU_UDINT_init__(CTU_UDINT *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}
/* ------------------------------------------------- */

void CTU_UDINT_body__(CTU_UDINT *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
} // CTU_UDINT_body__() 
/* ------------------------------------------------- */

void CTU_ULINT_init__(CTU_ULINT *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}
/* ------------------------------------------------- */

void CTU_ULINT_body__(CTU_ULINT *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
} // CTU_ULINT_body__() 
/* ------------------------------------------------- */

void CTD_init__(CTD *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}
/* ------------------------------------------------- */

void CTD_body__(CTD *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) <= 0));
} // CTD_body__() 
/* ------------------------------------------------- */

void CTD_DINT_init__(CTD_DINT *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}
/* ------------------------------------------------- */

void CTD_DINT_body__(CTD_DINT *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) <= 0));
} // CTD_DINT_body__() 
/* ------------------------------------------------- */

void CTD_LINT_init__(CTD_LINT *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}
/* ------------------------------------------------- */

void CTD_LINT_body__(CTD_LINT *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) <= 0));
} // CTD_LINT_body__() 
/* ------------------------------------------------- */

void CTD_UDINT_init__(CTD_UDINT *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}
/* ------------------------------------------------- */

void CTD_UDINT_body__(CTD_UDINT *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) <= 0));
} // CTD_UDINT_body__() 
/* ------------------------------------------------- */

void CTD_ULINT_init__(CTD_ULINT *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}
/* ------------------------------------------------- */

void CTD_ULINT_body__(CTD_ULINT *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) <= 0));
} // CTD_ULINT_body__() 
/* ------------------------------------------------- */

void CTUD_init__(CTUD *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}
/* ------------------------------------------------- */

void CTUD_body__(CTUD *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q,) && __GET_VAR(data__->CD_T.Q,)))) {
      if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
  __SET_VAR(data__->,QD,,(__GET_VAR(data__->CV,) <= 0));
} // CTUD_body__() 
/* ------------------------------------------------- */

void CTUD_DINT_init__(CTUD_DINT *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}
/* ------------------------------------------------- */

void CTUD_DINT_body__(CTUD_DINT *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q,) && __GET_VAR(data__->CD_T.Q,)))) {
      if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
  __SET_VAR(data__->,QD,,(__GET_VAR(data__->CV,) <= 0));
} // CTUD_DINT_body__() 
/* ------------------------------------------------- */

void CTUD_LINT_init__(CTUD_LINT *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}
/* ------------------------------------------------- */

void CTUD_LINT_body__(CTUD_LINT *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q,) && __GET_VAR(data__->CD_T.Q,)))) {
      if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
  __SET_VAR(data__->,QD,,(__GET_VAR(data__->CV,) <= 0));
} // CTUD_LINT_body__() 
/* ------------------------------------------------- */

void CTUD_UDINT_init__(CTUD_UDINT *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}
/* ------------------------------------------------- */

void CTUD_UDINT_body__(CTUD_UDINT *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q,) && __GET_VAR(data__->CD_T.Q,)))) {
      if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
  __SET_VAR(data__->,QD,,(__GET_VAR(data__->CV,) <= 0));
} // CTUD_UDINT_body__() 
/* ------------------------------------------------- */

void CTUD_ULINT_init__(CTUD_ULINT *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}
/* ------------------------------------------------- */

void CTUD_ULINT_body__(CTUD_ULINT *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q,) && __GET_VAR(data__->CD_T.Q,)))) {
      if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
  __SET_VAR(data__->,QD,,(__GET_VAR(data__->CV,) <= 0));
} // CTUD_ULINT_body__() 
/* ------------------------------------------------- */

void TP_init__(TP *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PT,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ET,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->PREV_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CURRENT_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->START_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}  /* TP_init__ */
/* ------------------------------------------------- */

void TP_body__(TP *data__) 
{
 #ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
__SET_VAR(data__->,CURRENT_TIME,,__CURRENT_TIME)
  #undef GetFbVar
  #undef SetFbVar
;
  if ((((__GET_VAR(data__->STATE,) == 0) && !(__GET_VAR(data__->PREV_IN,))) && __GET_VAR(data__->IN,))) {
    __SET_VAR(data__->,STATE,,1);
    __SET_VAR(data__->,Q,,__BOOL_LITERAL(TRUE));
    __SET_VAR(data__->,START_TIME,,__GET_VAR(data__->CURRENT_TIME,));
  } else if ((__GET_VAR(data__->STATE,) == 1)) {
    if (LE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __time_add(__GET_VAR(data__->START_TIME,), __GET_VAR(data__->PT,)), __GET_VAR(data__->CURRENT_TIME,))) {
      __SET_VAR(data__->,STATE,,2);
      __SET_VAR(data__->,Q,,__BOOL_LITERAL(FALSE));
      __SET_VAR(data__->,ET,,__GET_VAR(data__->PT,));
    } else {
      __SET_VAR(data__->,ET,,__time_sub(__GET_VAR(data__->CURRENT_TIME,), __GET_VAR(data__->START_TIME,)));
    };
  };
  if (((__GET_VAR(data__->STATE,) == 2) && !(__GET_VAR(data__->IN,)))) {
    __SET_VAR(data__->,ET,,__time_to_timespec(1, 0, 0, 0, 0, 0));
    __SET_VAR(data__->,STATE,,0);
  };
  __SET_VAR(data__->,PREV_IN,,__GET_VAR(data__->IN,));
} // TP_body__() 
/* ------------------------------------------------- */

void TON_init__(TON *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PT,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ET,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->PREV_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CURRENT_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->START_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}  // TON_init__
/* ------------------------------------------------- */

void TON_body__(TON *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
__SET_VAR(data__->,CURRENT_TIME,,__CURRENT_TIME)
  #undef GetFbVar
  #undef SetFbVar
;
  if ((((__GET_VAR(data__->STATE,) == 0) && !(__GET_VAR(data__->PREV_IN,))) && __GET_VAR(data__->IN,))) {
    __SET_VAR(data__->,STATE,,1);
    __SET_VAR(data__->,Q,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,START_TIME,,__GET_VAR(data__->CURRENT_TIME,));
  } else {
    if (!(__GET_VAR(data__->IN,))) {
      __SET_VAR(data__->,ET,,__time_to_timespec(1, 0, 0, 0, 0, 0));
      __SET_VAR(data__->,Q,,__BOOL_LITERAL(FALSE));
      __SET_VAR(data__->,STATE,,0);
    } else if ((__GET_VAR(data__->STATE,) == 1)) {
      if (LE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __time_add(__GET_VAR(data__->START_TIME,), __GET_VAR(data__->PT,)), __GET_VAR(data__->CURRENT_TIME,))) {
        __SET_VAR(data__->,STATE,,2);
        __SET_VAR(data__->,Q,,__BOOL_LITERAL(TRUE));
        __SET_VAR(data__->,ET,,__GET_VAR(data__->PT,));
      } else {
        __SET_VAR(data__->,ET,,__time_sub(__GET_VAR(data__->CURRENT_TIME,), __GET_VAR(data__->START_TIME,)));
      };
    };
  };
  __SET_VAR(data__->,PREV_IN,,__GET_VAR(data__->IN,));
} // TON_body__() 
/* ------------------------------------------------- */

void TOF_init__(TOF *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PT,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ET,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->PREV_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CURRENT_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->START_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}  // TOF_init__
/* ------------------------------------------------- */

void TOF_body__(TOF *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
__SET_VAR(data__->,CURRENT_TIME,,__CURRENT_TIME)
  #undef GetFbVar
  #undef SetFbVar
;
  if ((((__GET_VAR(data__->STATE,) == 0) && __GET_VAR(data__->PREV_IN,)) && !(__GET_VAR(data__->IN,)))) {
    __SET_VAR(data__->,STATE,,1);
    __SET_VAR(data__->,START_TIME,,__GET_VAR(data__->CURRENT_TIME,));
  } else {
    if (__GET_VAR(data__->IN,)) {
      __SET_VAR(data__->,ET,,__time_to_timespec(1, 0, 0, 0, 0, 0));
      __SET_VAR(data__->,STATE,,0);
    } else if ((__GET_VAR(data__->STATE,) == 1)) {
      if (LE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __time_add(__GET_VAR(data__->START_TIME,), __GET_VAR(data__->PT,)), __GET_VAR(data__->CURRENT_TIME,))) {
        __SET_VAR(data__->,STATE,,2);
        __SET_VAR(data__->,ET,,__GET_VAR(data__->PT,));
      } else {
        __SET_VAR(data__->,ET,,__time_sub(__GET_VAR(data__->CURRENT_TIME,), __GET_VAR(data__->START_TIME,)));
      };
    };
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->IN,) || (__GET_VAR(data__->STATE,) == 1)));
  __SET_VAR(data__->,PREV_IN,,__GET_VAR(data__->IN,));
} // TOF_body__() 
/* ------------------------------------------------- */

void DERIVATIVE_init__(DERIVATIVE *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->RUN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->XIN,0,retain)
  __INIT_VAR(data__->CYCLE,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->XOUT,0,retain)
  __INIT_VAR(data__->X1,0,retain)
  __INIT_VAR(data__->X2,0,retain)
  __INIT_VAR(data__->X3,0,retain)
}
/* ------------------------------------------------- */

void DERIVATIVE_body__(DERIVATIVE *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  if (__GET_VAR(data__->RUN,)) {
    __SET_VAR(data__->,XOUT,,((((3.0 * (__GET_VAR(data__->XIN,) - __GET_VAR(data__->X3,))) + __GET_VAR(data__->X1,)) - __GET_VAR(data__->X2,)) / (10.0 * TIME_TO_REAL((BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (TIME)__GET_VAR(data__->CYCLE,)))));
    __SET_VAR(data__->,X3,,__GET_VAR(data__->X2,));
    __SET_VAR(data__->,X2,,__GET_VAR(data__->X1,));
    __SET_VAR(data__->,X1,,__GET_VAR(data__->XIN,));
  } else {
    __SET_VAR(data__->,XOUT,,0.0);
    __SET_VAR(data__->,X1,,__GET_VAR(data__->XIN,));
    __SET_VAR(data__->,X2,,__GET_VAR(data__->XIN,));
    __SET_VAR(data__->,X3,,__GET_VAR(data__->XIN,));
  };
} // DERIVATIVE_body__() 
/* ------------------------------------------------- */

void HYSTERESIS_init__(HYSTERESIS *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS	
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->XIN1,0,retain)
  __INIT_VAR(data__->XIN2,0,retain)
  __INIT_VAR(data__->EPS,0,retain)
  __INIT_VAR(data__->Q,0,retain)
}
/* ------------------------------------------------- */

void HYSTERESIS_body__(HYSTERESIS *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  if (__GET_VAR(data__->Q,)) {
    if ((__GET_VAR(data__->XIN1,) < (__GET_VAR(data__->XIN2,) - __GET_VAR(data__->EPS,)))) {
      __SET_VAR(data__->,Q,,0);
    };
  } else if ((__GET_VAR(data__->XIN1,) > (__GET_VAR(data__->XIN2,) + __GET_VAR(data__->EPS,)))) {
    __SET_VAR(data__->,Q,,1);
  };
} // HYSTERESIS_body__() 
/* ------------------------------------------------- */

void INTEGRAL_init__(INTEGRAL *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->RUN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->XIN,0,retain)
  __INIT_VAR(data__->X0,0,retain)
  __INIT_VAR(data__->CYCLE,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->XOUT,0,retain)
}
/* ------------------------------------------------- */

void INTEGRAL_body__(INTEGRAL *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->,Q,,!(__GET_VAR(data__->R1,)));
  if (__GET_VAR(data__->R1,)) {
    __SET_VAR(data__->,XOUT,,__GET_VAR(data__->X0,));
  } else if (__GET_VAR(data__->RUN,)) {
    __SET_VAR(data__->,XOUT,,(__GET_VAR(data__->XOUT,) + (__GET_VAR(data__->XIN,) * TIME_TO_REAL((BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (TIME)__GET_VAR(data__->CYCLE,)))));
  };
} // INTEGRAL_body__() 
/* ------------------------------------------------- */

void PID_init__(PID *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->AUTO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->SP,0,retain)
  __INIT_VAR(data__->X0,0,retain)
  __INIT_VAR(data__->KP,0,retain)
  __INIT_VAR(data__->TR,0,retain)
  __INIT_VAR(data__->TD,0,retain)
  __INIT_VAR(data__->CYCLE,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->XOUT,0,retain)
  __INIT_VAR(data__->ERROR,0,retain)
  INTEGRAL_init__(&data__->ITERM,retain);
  DERIVATIVE_init__(&data__->DTERM,retain);
}
/* ------------------------------------------------- */

void PID_body__(PID *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->,ERROR,,(__GET_VAR(data__->PV,) - __GET_VAR(data__->SP,)));
  __SET_VAR(data__->ITERM.,RUN,,__GET_VAR(data__->AUTO,));
  __SET_VAR(data__->ITERM.,R1,,!(__GET_VAR(data__->AUTO,)));
  __SET_VAR(data__->ITERM.,XIN,,__GET_VAR(data__->ERROR,));
  __SET_VAR(data__->ITERM.,X0,,(__GET_VAR(data__->TR,) * (__GET_VAR(data__->X0,) - __GET_VAR(data__->ERROR,))));
  __SET_VAR(data__->ITERM.,CYCLE,,__GET_VAR(data__->CYCLE,));
  INTEGRAL_body__(&data__->ITERM);
  __SET_VAR(data__->DTERM.,RUN,,__GET_VAR(data__->AUTO,));
  __SET_VAR(data__->DTERM.,XIN,,__GET_VAR(data__->ERROR,));
  __SET_VAR(data__->DTERM.,CYCLE,,__GET_VAR(data__->CYCLE,));
  DERIVATIVE_body__(&data__->DTERM);
  __SET_VAR(data__->,XOUT,,(__GET_VAR(data__->KP,) * ((__GET_VAR(data__->ERROR,) + (__GET_VAR(data__->ITERM.XOUT,) / __GET_VAR(data__->TR,))) + (__GET_VAR(data__->DTERM.XOUT,) * __GET_VAR(data__->TD,)))));
} // PID_body__() 
/* ------------------------------------------------- */

void RAMP_init__(RAMP *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->RUN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->X0,0,retain)
  __INIT_VAR(data__->X1,0,retain)
  __INIT_VAR(data__->TR,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->CYCLE,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->XOUT,0.0,retain)
  __INIT_VAR(data__->XI,0,retain)
  __INIT_VAR(data__->T,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}
/* ------------------------------------------------- */

void RAMP_body__(RAMP *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->,BUSY,,__GET_VAR(data__->RUN,));
  if (__GET_VAR(data__->RUN,)) {
    if (GE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __GET_VAR(data__->T,), __GET_VAR(data__->TR,))) {
      __SET_VAR(data__->,BUSY,,0);
      __SET_VAR(data__->,XOUT,,__GET_VAR(data__->X1,));
    } else {
      __SET_VAR(data__->,XOUT,,(__GET_VAR(data__->XI,) + (((__GET_VAR(data__->X1,) - __GET_VAR(data__->XI,)) * TIME_TO_REAL((BOOL)__BOOL_LITERAL(TRUE),
        NULL,
        (TIME)__GET_VAR(data__->T,))) / TIME_TO_REAL((BOOL)__BOOL_LITERAL(TRUE),
        NULL,
        (TIME)__GET_VAR(data__->TR,)))));
      __SET_VAR(data__->,T,,__time_add(__GET_VAR(data__->T,), __GET_VAR(data__->CYCLE,)));
    };
  } else {
    __SET_VAR(data__->,XOUT,,__GET_VAR(data__->X0,));
    __SET_VAR(data__->,XI,,__GET_VAR(data__->X0,));
    __SET_VAR(data__->,T,,__time_to_timespec(1, 0, 0, 0, 0, 0));
  };
} // RAMP_body__() 
/* ------------------------------------------------- */

void RTC_init__(RTC *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PDT,__dt_to_timespec(0, 0, 0, 1, 1, 1970),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CDT,__dt_to_timespec(0, 0, 0, 1, 1, 1970),retain)
  __INIT_VAR(data__->PREV_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OFFSET,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->CURRENT_TIME,__dt_to_timespec(0, 0, 0, 1, 1, 1970),retain)
}
/* ------------------------------------------------- */

void RTC_body__(RTC *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
__SET_VAR(data__->,CURRENT_TIME,,__CURRENT_TIME)
  #undef GetFbVar
  #undef SetFbVar
;
  if (__GET_VAR(data__->IN,)) {
    if (!(__GET_VAR(data__->PREV_IN,))) {
      __SET_VAR(data__->,OFFSET,,__time_sub(__GET_VAR(data__->PDT,), __GET_VAR(data__->CURRENT_TIME,)));
    };
    __SET_VAR(data__->,CDT,,__time_add(__GET_VAR(data__->CURRENT_TIME,), __GET_VAR(data__->OFFSET,)));
  } else {
    __SET_VAR(data__->,CDT,,__GET_VAR(data__->CURRENT_TIME,));
  };
  __SET_VAR(data__->,Q,,__GET_VAR(data__->IN,));
  __SET_VAR(data__->,PREV_IN,,__GET_VAR(data__->IN,));
} // RTC_body__() 
/* ------------------------------------------------- */

void SEMA_init__(SEMA *data__, BOOL retain) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
#endif
  __INIT_VAR(data__->CLAIM,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RELEASE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q_INTERNAL,__BOOL_LITERAL(FALSE),retain)
}
/* ------------------------------------------------- */

void SEMA_body__(SEMA *data__) 
{
#ifndef  DISABLE_EN_ENO_PARAMETERS
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
#endif

  __SET_VAR(data__->,Q_INTERNAL,,(__GET_VAR(data__->CLAIM,) || (__GET_VAR(data__->Q_INTERNAL,) && !(__GET_VAR(data__->RELEASE,)))));
  __SET_VAR(data__->,BUSY,,__GET_VAR(data__->Q_INTERNAL,));
} // SEMA_body__() 
/* ------------------------------------------------- */
