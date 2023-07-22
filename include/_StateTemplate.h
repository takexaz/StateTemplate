#include <StateControllerExtension.h>
struct ST_TEMPLATE {
    EVAL_EXP value;
    char text[256] = "";
};

int stxRegister(TPFILE*, STATE_INFO*, PLAYER_CACHE*);
void stxProcess(PLAYER*, STATE_INFO*);
void stxFree(STATE_INFO*);