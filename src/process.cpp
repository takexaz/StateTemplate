#include <StateControllerExtension.h>
#include "_StateTemplate.h"

void stxProcess(MUGEN_PLAYER* player, MUGEN_SC_DATA_EX* scdx) {
    ST_TEMPLATE* temp = (ST_TEMPLATE*)scdx->SCX->params;
    int value = EvalExpressionN(player, &temp->value, 0);
    if (value < 0) {
        VWarn(player, "template value too small: %d", value);
    }
    else {
        Warn(player, temp->text);
    }

    int iparam;
    float fparam;
    switch (EvalExpressionN(player, &temp->param, &iparam, &fparam))
    {
    case EVAL_TYPE_INT:
        VWarn(player, "INT DETECTED: %d", iparam);
        break;
    case EVAL_TYPE_FLOAT:
        VWarn(player, "FLOAT DETECTED: %f", fparam);
        break;
    default:
        break;
    }


    return;
}