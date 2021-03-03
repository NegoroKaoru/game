#ifndef __HEADER_INPUT_H
#define __HEADER_INPUT_H

#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitInput(void);
void UninitInput(void);
void UpdateInput(void);
//void DrawInput(void);
// ���͂̕`��͕s�v�A�������i�Q�[��J���r���œ��͓��e�̊m�F�@�\������ƕ֗�

//�L�[��������Ă��邩
bool IsPressInput(BYTE nVertKey);
//�L�[�������ꂽ�Ƃ�
bool IsTriggerInput(BYTE nVertKey);
//�L�[���痣�ꂽ�Ƃ�
bool IsReleaseInput(BYTE nVertKey);
//���s�[�g����
bool IsRepeatInput(BYTE nVertKey);


#endif //__HEADER_INPUT_H