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

    int iparam;
    float fparam;
    switch (EvalExpression(p, &temp->param, &iparam, &fparam))
    {
    case EVAL_INT:
        VWarn(p, "INT DETECTED: %d", iparam);
        break;
    case EVAL_FLOAT:
        VWarn(p, "FLOAT DETECTED: %f", fparam);
        break;
    default:
        break;
    }


    return;
}