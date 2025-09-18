#pragma once
#include <Scene.h>
#include"Sprite2D.h"
#include<unordered_map>
#include"FrameTimer.h"
class MusicSelect :
    public MelLib::Scene
{
private:
	MelLib::FrameTimer addTimer;

	std::unordered_map<unsigned short, std::wstring>musicNames;
	short selectMusicNum = 0;
	short musicCount = 0;
	// [�Ȗ�][bpm]
	std::unordered_map<std::wstring, float>bpms;
	std::unordered_map<std::wstring, std::wstring>artistNames;
	MelLib::Sprite2D arrow;
	MelLib::Sprite2D arrow2;

	bool easy = false;
private:
	void LoadMusicData();
	// ���̕ӋȑI���ł��ǂݍ��ނ���ʃN���X(�ȑI���V�[��)�Ƃ��ɏ������ق�����������
	void LoadBPM(const std::wstring& musicFolderPath,float& bpm);
	/// <summary>
	/// �Ȗ��A�A�[�e�B�X�g���Ȃǂ̓��{���ǂݍ��ނ��߂̊֐�
	/// </summary>
	/// <param name="musicFolderPath"></param>
	/// <param name="format"></param>
	/// <param name="refStr"></param>
	void LoadName(const std::wstring& musicFolderPath, const std::wstring& format, std::wstring& refStr,bool file);

public:
	MusicSelect();
	~MusicSelect();
	void Initialize()override;//������
	void Update()override;
	void Draw()override;
	void Finalize()override;//�I������
	Scene* GetNextScene()override;//���̃V�[���̎w��

};

