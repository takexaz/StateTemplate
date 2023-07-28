#include <StateControllerExtension.h>
#include "_StateTemplate.h"

void stxFree(STATE_INFO* sinfo) {
    ST_TEMPLATE* temp = (ST_TEMPLATE*)sinfo->params;
    FreeExpression(&temp->value);
    FreeExpression(&temp->param);
    delete temp;
    return;
}