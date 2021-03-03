#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "main.h"

//シーンの種類
enum SceneKind
{
	SCENE_TITTLE,	//タイトル
	SCENE_STAGESELECT,
	SCENE_GAME,		//ゲーム
	SCENE_RESULT,	//リザルト
};


HRESULT InitScene(void);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);

void ChangeScene(SceneKind scene);
void ResetScene(void);
void SetGameClear(void);
void SetStageNum(int num);
int GetStageNum();

#endif __SCENEMANAGER_H__
