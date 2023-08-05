#pragma once
#include <StateControllerExtension.h>
struct ST_TEMPLATE {
    MUGEN_EVAL_VALUE value;
    MUGEN_EVAL_VALUE param;
    char text[256] = "";
};

int stxRegister(TPFILE*, MUGEN_SC_DATA_EX*, MUGEN_PLAYER_INFO*);
void stxProcess(MUGEN_PLAYER*, MUGEN_SC_DATA_EX*);
void stxFree(MUGEN_SC_DATA_EX*);