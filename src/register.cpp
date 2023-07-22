#include <StateControllerExtension.h>
#include "_StateTemplate.h"

int stxRegister(TPFILE* tpf, STATE_INFO* sinfo, PLAYER_CACHE* pcache) {
    ST_TEMPLATE* temp = new ST_TEMPLATE;
    sinfo->params = temp;

    DWORD NEXT;
    const char* ptr;
    int num;
    ptr = TPGetValue(tpf, "value");
    if (ptr) {
        num = SCtrlReadExpList(ptr, "i", pcache, &NEXT, &temp->value);
    }
    else {
        setErrorText("Missing value parameter for template");
        return FALSE;
    }

    if (!GetQuotedString(tpf, "text", temp->text, sizeof(temp->text))) {
        return FALSE;
    }

    return TRUE;
}