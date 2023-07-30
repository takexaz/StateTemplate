#include <StateControllerExtension.h>
#include "_StateTemplate.h"

int stxRegister(TPFILE* tpf, STATE_INFO* sinfo, PLAYER_CACHE* pcache) {
    ST_TEMPLATE* temp = new ST_TEMPLATE;
    sinfo->params = temp;

    const char* parseEnd;
    const char* ptr;
    int num;
    ptr = TPGetValue(tpf, "value");
    if (ptr) {
        num = SCtrlReadExpList(ptr, "i", pcache, &parseEnd, &temp->value);
    }
    else {
        setErrorText("Missing value parameter for template");
        return FALSE;
    }

    if (!GetQuotedString(tpf, "text", temp->text, sizeof(temp->text))) {
        return FALSE;
    }

    constExp(&temp->param, 0);
    ptr = TPGetValue(tpf, "param");
    if (ptr) {
        num = SCtrlReadExpList(ptr, "n", pcache, &parseEnd, &temp->param);
    }
    return TRUE;
}