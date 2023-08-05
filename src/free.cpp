#include <StateControllerExtension.h>
#include "_StateTemplate.h"

void stxFree(MUGEN_SC_DATA_EX* scdx) {
    ST_TEMPLATE* temp = (ST_TEMPLATE*)scdx->SCX->params;
    FreeExpression(&temp->value);
    FreeExpression(&temp->param);
    delete temp;
    return;
}