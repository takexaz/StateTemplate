#include <StateControllerExtension.h>
#include "_StateTemplate.h"

int stxRegister(TPFILE* tpf, MUGEN_SC_DATA_EX* scdx, MUGEN_PLAYER_INFO* pinfo) {
    ST_TEMPLATE* temp = new ST_TEMPLATE;
    scdx->SCX->params = temp;

    const char* parseEnd;
    const char* ptr;
    int num;
    ptr = TPGetValue(tpf, "value");
    if (ptr) {
        num = SCtrlReadExpList(ptr, "i", pinfo, &parseEnd, &temp->value);
    }
    else {
        setErrorText("Missing value parameter for template");
        return FALSE;
    }

    if (!GetQuotedStringEx(tpf, "text", temp->text, sizeof(temp->text))) {
        return FALSE;
    }

    constExpN(&temp->param, 0);
    ptr = TPGetValue(tpf, "param");
    if (ptr) {
        num = SCtrlReadExpList(ptr, "n", pinfo, &parseEnd, &temp->param);
    }
    return TRUE;
}