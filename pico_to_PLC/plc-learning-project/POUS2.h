void PROGRAM0_init__(PROGRAM0 *data__, BOOL retain) {
  __INIT_LOCATED(BOOL,__QX0_25,data__->LED,retain)
  __INIT_LOCATED_VALUE(data__->LED,__BOOL_LITERAL(FALSE))
  TON_init__(&data__->TON0,retain);
  TOF_init__(&data__->TOF0,retain);
}

// Code part
void PROGRAM0_body__(PROGRAM0 *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->TON0.,IN,,!(__GET_LOCATED(data__->LED,)));
  __SET_VAR(data__->TON0.,PT,,__time_to_timespec(1, 0, 1, 0, 0, 0));
  TON_body__(&data__->TON0);
  __SET_VAR(data__->TOF0.,IN,,__GET_VAR(data__->TON0.Q,));
  __SET_VAR(data__->TOF0.,PT,,__time_to_timespec(1, 0, 1, 0, 0, 0));
  TOF_body__(&data__->TOF0);
  __SET_LOCATED(data__->,LED,,__GET_VAR(data__->TOF0.Q,));

  goto __end;

__end:
  return;
} // PROGRAM0_body__() 





