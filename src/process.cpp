#include <StateControllerExtension.h>
#include "_StateTemplate.h"

void stxProcess(PLAYER* p, STATE_INFO* sinfo) {
    ST_TEMPLATE* temp = (ST_TEMPLATE*)sinfo->params;
    int value = EvalExpression(p, &temp->value, 0);
    if (value < 0) {
        VWarn(p, "template value too small: %d", value);
    }
    else {
        Warn(p, temp->text);
    }
    return;
}