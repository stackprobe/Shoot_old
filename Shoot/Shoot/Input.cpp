/*
	n�t���[���ԃ{�^���������� ... 0, 0, 0... 0, 1, 2... (n-2), (n-1), n, -1, 0, 0, 0... �ƂȂ�B

	FreezeInput()�ɂ��r���X�L�b�v���邱�Ƃ�����̂ŁA
	���1��������Ƃ��A(-1)�̒��O�͏��1�ȏ�Ƃ��A�Ō�͏��(-1)�ɂȂ�Ƃ��z�肷��̂͊댯�I

	... 0, 0, 0, 1, 2, 0, 4, 5, -1, 0, 0, 0...
	                   ^
	              FreezeInput();

	... 0, 0, 0, 1, 2, 3, 4, 0, -1, 0, 0, 0...
	                         ^
	                    FreezeInput();

	... 0, 0, 0, 1, 2, 3, 4, 5, 0, 0, 0, 0...
	                            ^
	                       FreezeInput();

	�߂�l�̌^�̎g������

	int aInp1 = GetInput(INP_A);
	BOOL aInp2 = 1 <= GetInput(INP_A);
*/

#include "all.h"

static int InputStatus[INP_MAX];

static void MixInput(int inpId, int keyId, int btnId)
{
	BOOL keyDown = 1 <= GetKeyInput(keyId);
	BOOL btnDown = 1 <= GetPadInput(Gnd.PrimaryPadId, btnId);

	updateInput(InputStatus[inpId], keyDown || btnDown);
}
void InputEachFrame(void)
{
	MixInput(INP_DIR_2, KEY_INPUT_DOWN, Gnd.PadBtnId.Dir_2);
	MixInput(INP_DIR_4, KEY_INPUT_LEFT, Gnd.PadBtnId.Dir_4);
	MixInput(INP_DIR_6, KEY_INPUT_RIGHT, Gnd.PadBtnId.Dir_6);
	MixInput(INP_DIR_8, KEY_INPUT_UP, Gnd.PadBtnId.Dir_8);
	MixInput(INP_A, KEY_INPUT_Z, Gnd.PadBtnId.A);
	MixInput(INP_B, KEY_INPUT_X, Gnd.PadBtnId.B);
	MixInput(INP_C, KEY_INPUT_C, Gnd.PadBtnId.C);
	MixInput(INP_D, KEY_INPUT_V, Gnd.PadBtnId.D);
	MixInput(INP_E, KEY_INPUT_B, Gnd.PadBtnId.C);
	MixInput(INP_F, KEY_INPUT_N, Gnd.PadBtnId.D);
	MixInput(INP_L, KEY_INPUT_A, Gnd.PadBtnId.L);
	MixInput(INP_R, KEY_INPUT_S, Gnd.PadBtnId.R);
	MixInput(INP_PAUSE, KEY_INPUT_A, Gnd.PadBtnId.Pause);
	MixInput(INP_START, KEY_INPUT_S, Gnd.PadBtnId.Start);
}
int GetInput(int inpId)
{
	errorCase(inpId < 0 || INP_MAX <= inpId);

	return FreezeInputFrame ? 0 : InputStatus[inpId];
}
int GetPound(int inpId)
{
	errorCase(inpId < 0 || INP_MAX <= inpId);

	return FreezeInputFrame ? 0 : isPound(InputStatus[inpId]);
}
