#pragma once
#include<string>
#include<array>
#include<vector>

#include"Block.h"

#include<Sound.h>
#include<Values.h>
#include<FrameTimer.h>

class MusicalScoreManager 
{
private:
	MusicalScoreManager() {}
	~MusicalScoreManager() {}

	void LoadHumen(const std::wstring& musicFolderPath);
	void CheckBlockMoveStart();

	/// <summary>
	/// �Ȃƕ��ʂ̃Y����ǂݍ��݁B
	/// </summary>
	void LoadDelayTime();

	/// <summary>
	/// �Ȃ̍Đ�
	/// </summary>
	void PlayMusic();

	/// <summary>
	/// ���ʂ̍Đ�
	/// </summary>
	void PlayHumen();

private:
	const std::string SOUND_KEY = "Music";


	// �e���|
	float bpm = 0;
	// 16���̎���
	DWORD haku16Time = 0;
	// �Ō�ɕ��ʂ��m�F(�m�[�c�����邩�m�F)��������
	DWORD humenCheckTime = 0;
	// ���݂̎���
	DWORD nowTime = 0;
	// �O�t���[���̎���
	DWORD preTime = 0;
	// �Ō�Ɋm�F�������ʂ̏c��̓Y����
	unsigned int currentHumenIndex = 0;

	// ���ꂪMax�ɂȂ�����Ȃ��Đ�
	MelLib::FrameTimer musicDelayTimer;
	MelLib::FrameTimer humenDelayTimer;

	// �Ȗ�
	std::wstring musicName;
	// ��ȎҖ�
	std::wstring artistName;

	// ���ʃf�[�^
	std::vector<std::array<std::unique_ptr<Block>, 2>> humen;
	// �u���b�N�̔z��ԍ�(���ɔ�������u���b�N�̎w��p)
	std::vector<MelLib::Value2<unsigned int>>blockIndex;
	unsigned int nextBlockIndex = 0;
	
	// ���ɃL�[�����������ɔ�������u���b�N
	// ����������������Ȃ炱��z��ɂ��邱��
	Block* pNextBlock = nullptr;

	// ���ʂ��Ō�܂œǂݍ��ݏI��������ǂ���
	bool changeNextBlockEnd = false;
	bool lastBlockPush = false;

	// �ړ����I�����u���b�N���i�[����z��B�v���C���[���������̂Ɏg�p
	std::vector<Block*>moveEndBlock;

	// �L�[���������Ƀ~�X�ɂȂ������ǂ���
	bool notPushMiss = false;

	bool easy = false;

	// �f���[�Ɣԍ�
	int dPos = 0;
public:
	MusicalScoreManager(MusicalScoreManager& m) = delete;
	MusicalScoreManager operator=(MusicalScoreManager & m) = delete;
	static MusicalScoreManager* GetInstance();

	void SetMusicData( const std::wstring& musicName, const std::wstring& artistName, const float& bpm,const bool easy);

	/// <summary>
	/// �Ȃƕ��ʂ̃��[�h�����܂��B���g���C��������Ăяo���Ă��������B
	/// </summary>
	/// <param name="musicFolderPath"></param>
	void Load();

	
	
	void BlockMoveStart();

	/// <summary>
	/// ��~�B�I���A�|�[�Y���Ɏ~�߂�p
	/// </summary>
	void Stop();

	void Update();
	void Draw();

	/// <summary>
	/// �ǂݍ��񂾕��ʏ����폜���܂�
	/// </summary>
	void Finalize();

	void Play();

	// �����̃m�[�c�̌��݂̈ʒu�ƃW���X�g�^�C�~���O�Ƃ̍������擾���܂��B(����̖߂�l�𔻒�m�F�Ɏg��)
	short GetLeftTimingDifferenceFrame();
	// ��̊֐��̉E����
	short GetRigthTimingDifferenceFrame();

	// �L�[���������Ƃ��ɔ�������u���b�N�̐؂�ւ�
	void  ChangeNextBlock();

	bool GetHumenEnd() const { return changeNextBlockEnd;}
	bool GetLastBlockPush() const { return lastBlockPush;}

	const std::vector<Block*>& GetMoveEndBlock() { return moveEndBlock; }

	void TrueBlockMissFlag()const { pNextBlock->TrueMiss(); }

	/// <summary>
	/// �u���b�N�̐����擾���܂�
	/// </summary>
	/// <returns></returns>
	size_t GetBlockIndexNum()const { return blockIndex.size(); }

	bool GetNotPushMiss()const { return notPushMiss; }

	std::wstring GetMusicName() { return musicName; }
};

