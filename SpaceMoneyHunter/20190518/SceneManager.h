#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "main.h"

//�V�[���̎��
enum SceneKind
{
	SCENE_TITTLE,	//�^�C�g��
	SCENE_STAGESELECT,
	SCENE_GAME,		//�Q�[��
	SCENE_RESULT,	//���U���g
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
