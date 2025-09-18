#pragma once
#include <Scene.h>
#include<FrameTimer.h>
#include<Sprite2D.h>
#include<Sprite3D.h>
#include<ModelObject.h>

#include"CheckPushKey.h"


class Play :
	public MelLib::Scene
{
private:
	enum class GAME_STATE
	{
		BEFORE_PLAY,
		PLAY,
		GAMEOVER,
		CLEAR,
		TUTORIAL
	};
	GAME_STATE gameState = GAME_STATE::BEFORE_PLAY;
	const bool TUTORIAL = false;

	MelLib::ModelObject startObj;
	MelLib::ModelObject goalObj;
	MelLib::Sprite3D waterSprite;

	// ���ʂ�����n�߂�܂ł̎���
	MelLib::FrameTimer startTimer;

	// ����
	CheckPushKey::JudgmentType judgmentType = CheckPushKey::JudgmentType::NONE;
	// �`�悷�锻��@�����̓s���㕪���Ă�
	CheckPushKey::JudgmentType drawJudgment = CheckPushKey::JudgmentType::NONE;
	// ����\�����Ԃ𑪒肷��^�C�}�[
	MelLib::FrameTimer judgmentDrawTimer;

	// ����̋L�^
	std::unordered_map<CheckPushKey::JudgmentType, unsigned short>judgmentNum;

	bool dropCheck = false;

	// �J�����̈ړ���
	float cameraMoveVec = 0.0f;
	// ���̈ړ��ʕ��ړ����������m�F���邽�߂̕ϐ�
	float cameraOneMoveCheckCounter = 0.0f;

	const float START_CAMERA_POS_Z = -10.0f;
	// �J�����̈��̈ړ�()
	const float CAMERA_ONE_MOVE_POS = 1.0f;
	// 1�t���[���̈ړ���
	const float FRAME_MOVE_POS = 1.0f;

	// ���݊m�F����u���b�N �v���C���[�𗎉������邩�ǂ����Ɏg�p
	unsigned int currentCheckBlock = 0;

	// �u���b�N�������Ă��v���C���[�������Ă����痎�����ɐi�ނ悤�ɂ��邽�߂̃t���O
	std::vector<bool>dropPlayerFlag;

	// �N���A��Ƀv���C���[�ƃJ�����𖼓��������Ɏg������
	MelLib::FrameTimer clearPlayerMoveTime;
	bool clearMoveEnd = false;

	// �������t���[�����ǂ���
	bool keyTrrigerFrame = false;
	bool notPushMissFrame = false;

	// �I����Ƀ��C�t�̌v�Z���s�����߂̃^�C�}�[
	MelLib::FrameTimer lifeCheckTimer;

	float clearCameraMoveVec = 0.0f;

#pragma region �R���{
	void ComboCount(bool isCombo);

	int comboCountNum = 0;


#pragma endregion

	// ����X�v���C�g
	std::unordered_map<CheckPushKey::JudgmentType, MelLib::Sprite2D >judgmentSprite;
	std::unordered_map<CheckPushKey::JudgmentType, MelLib::Sprite2D >judgmentCountSprite;

	std::unordered_map<BYTE, MelLib::Sprite2D >keyNakamiSprite;
	std::unordered_map<BYTE, MelLib::Sprite2D >keyWakuSprite;

	const float SUB_ALPHA = 5.0f;

	MelLib::Sprite2D readySprite;
	float readySubAlpha = 0.0f;


	MelLib::FrameTimer clearSpriteDrawTimer;
	MelLib::Sprite2D clearSprite;
	float clearSubAlpha = 100.0f;

	MelLib::Sprite2D gameoverSprite;
	MelLib::FrameTimer gameoverSpriteDrawTimer;

	//���ڂ̃`���[�g���A�����b�Z�[�W��
	int tutorialNum = 0;

	std::unordered_map<int, std::wstring>tutorialText;

	MelLib::FrameTimer sceneChangeTimer;

	bool stopMusic = false;
private:
	/// <summary>
	/// ���Q�[�̃v���C�Ɋ֌W���Ă镔���̏������܂Ƃ߂��֐�
	/// </summary>
	void PlayUpdate();

	/// <summary>
	/// ����J�E���g
	/// </summary>
	void CountJudgmentNum();

	/// <summary>
	/// �J�����̈ړ��ʂ����Z
	/// </summary>
	void AddCameraMovePos();

	/// <summary>
	/// �J�����ړ�
	/// </summary>
	void MoveCamera();

	void UpdatePlayer();

	/// <summary>
	/// �v���C���[�ړ�
	/// </summary>
	void MovePlayer();


	void CheckDropPlayer();
	void GameoverUpdate();
	void ClearUpdate();
	void TutorialUpdate();


public:
	Play(const bool tutorial);
	~Play();
	void Initialize()override;//������
	void Update()override;
	void Draw()override;
	void Finalize()override;//�I������
	Scene* GetNextScene()override;//���̃V�[���̎w��

};

