#ifndef __HEADER_INPUT_H
#define __HEADER_INPUT_H

#include "main.h"

//プロトタイプ宣言
HRESULT InitInput(void);
void UninitInput(void);
void UpdateInput(void);
//void DrawInput(void);
// 入力の描画は不要、ただし格ゲーや開発途中で入力内容の確認機能があると便利

//キーが押されているか
bool IsPressInput(BYTE nVertKey);
//キーが押されたとき
bool IsTriggerInput(BYTE nVertKey);
//キーから離れたとき
bool IsReleaseInput(BYTE nVertKey);
//リピート入力
bool IsRepeatInput(BYTE nVertKey);


#endif //__HEADER_INPUT_H