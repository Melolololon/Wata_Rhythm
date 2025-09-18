#pragma once
#include<GameObject.h>
#include<GuiValue.h>
#include<Sprite2D.h>

class Player :
    public MelLib::GameObject
{

private:
	static float frameMoveVec;
	bool isDrop = false;

	// �A�j���[�V�����̃��[�v�J�n�n�_
	int animLoopStartPoint = 0;
public:
	static void SetFrameMoveVec(const float vec) { frameMoveVec = vec; }

	Player();
	
	// �X�V
    void Update()override;
    
	//�`��
	void Draw()override;
    
	/// <summary>
	/// �����������ɌĂ΂��֐�
	/// </summary>
	/// <param name="object">�Փ˂����I�u�W�F�N�g�̎Q��</param>
	/// <param name="shapeType">����ƏՓ˂��������̓����蔻��̌`��</param>
	/// <param name="shapeName">����ƏՓ˂��������̓����蔻��̖��O</param>
	/// <param name="hitObjShapeType">�Փ˂����I�u�W�F�N�g�̓����蔻��̌`��</param>
	/// <param name="hitShapeName">�Փ˂����I�u�W�F�N�g�̔���̖��O</param>
	void Hit
	(
		const GameObject& object,
		const MelLib::ShapeType3D shapeType,
		const std::string& shapeName,
		const MelLib::ShapeType3D hitObjShapeType,
		const std::string& hitShapeName
	)override;

	std::shared_ptr<MelLib::GameObject> GetNewPtr()override;

	void SetParent(std::shared_ptr<Player> player) { parent = player; }

	static void LoadRes();


	void Move();


	/// <summary>
	/// �u���b�N�������������ɗ����鏈��
	/// </summary>
	void Drop();

	void SetClearAnimation();
private:
	// 
	// �O�ɂ���v���C���[
	std::shared_ptr<Player> parent = nullptr;
};

