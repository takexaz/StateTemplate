/*
ヘッダーのインクルードとライブラリのプリプロセッサディレクティブ
----------------------------------------------------------------------------
- Mebius.h
ZoomなどMUGENの処理の根幹に関わる改変をするステートを作る場合に使用
HookやwriteBytesToROMなど、バイナリを編集する関数が定義されている
本テンプレートでは使用しない

- StateControllerExtension.h
ステートコントローラーを作る場合には必須
実装に使用する関数や構造体が定義されている

- Mebius.lib
Mebiusを使用する場合はリンクが必要

- StateControllerExtension.lib
StateControllerExtensionを使用する場合はリンクが必要
*/
#include "pch.h"
#include <Mebius.h>
#include <StateControllerExtension.h>
#pragma comment(lib, "Mebius.lib")
#pragma comment(lib, "StateControllerExtension.lib")



/*
ステートの処理関数のプロトタイプ宣言
----------------------------------------------------------------------------
名称の変更は自由だが、引数の変更はできない

- stcReg(TPFILE*, STATE_INFO*, PLAYER_CACHE*)
ステートのパラメータをパースし、ステートとして登録する

- stcProc(PLAYER*, STATE_INFO*)
ステートの処理を行う

- stcFree(STATE_INFO*)
ステートのメモリ解放を行う
*/
int stcReg(TPFILE*, STATE_INFO*, PLAYER_CACHE*);
void stcProc(PLAYER*, STATE_INFO*);
void stcFree(STATE_INFO*);



/*
ステートのパラメータの構造体宣言
----------------------------------------------------------------------------
メンバ名は自由
EVAL_EXP構造体はint型,float型に使用する
char型は""に囲まれた文字列を格納する場合に使用する
*/
struct MYSTATE {
    EVAL_EXP INT_REQ;
    EVAL_EXP INT_OPT;
    EVAL_EXP FLOAT_REQ;
    EVAL_EXP FLOAT_OPT;
    EVAL_EXP MULTI_INT01, MULTI_INT02;
    EVAL_EXP MULTI_FLOAT01, MULTI_FLOAT02;
    EVAL_EXP MULTI_FLOAT, MULTI_INT;
    char TEXT[256] = "";
};

// FALSE=Error
int stcReg(TPFILE* tpf, STATE_INFO* sinfo, PLAYER_CACHE* pcache) {

    MYSTATE* mystate = new MYSTATE;
    sinfo->params = mystate;
    DWORD TEMP;

    constExp(&mystate->value, 100);
    const char* value = TPGetValue(tpf, "value");
    if (value) {
        SCtrlReadExpList(value, "i", pcache, &TEMP, &mystate->value);
    }

    GetQuotedString(tpf, "text", mystate->x, sizeof(mystate->x));
    return TRUE;
}

void stcProc(PLAYER* p, STATE_INFO* sinfo) {
    MYSTATE* mystate = (MYSTATE*)sinfo->params;
    int life = EvalExpression(p,&mystate->value, 0);
    p->life = life;
    return;
}

void stcFree(STATE_INFO* sinfo) {
    MYSTATE* mystate = (MYSTATE*)sinfo->params;
    FreeExpression(&mystate->value);
    delete mystate;
    return;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        STX mystate = STX{
            "mystate",
            stcReg,
            stcProc,
            stcFree, 
        };
        addState(mystate);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

