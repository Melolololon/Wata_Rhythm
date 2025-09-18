#pragma once
#include"GameObject.h"
#include"Particle3D.h"

// �g����
// �p�[�e�B�N���N���X���쐬����
// �R���X�g���N�^�Ƀp�[�e�B�N���Ɛݒ��n��
// GameObjectManager�ɓ˂�����

namespace MelLib
{
    class Emitter3D :public GameObject
	{
    private:
        //std::vector<std::shared_ptr<Particle3D>>particles;
        std::vector<std::shared_ptr<Particle3D>>particles;

        // Update�ADraw���s�����ǂ����̃t���O
        std::vector<bool>particleUpdateDrawFlag;
        
        // ���o�Ԋu
        FrameTimer releaseTimer;
        // ���o��~�t���O
        bool isStop = false;

        // �ĕ��o�t���O
        bool reShot = true;
        // reShot��false�ɂ����o���Ȃ��悤�ɂȂ��Ă��邩�ǂ���
        bool reShotStop = false;

        bool allShotDead = false;
    private:

        void CheckChangeUpdateDrawFlag();

        /// <summary>
        /// �p�[�e�B�N���X�V����
        /// </summary>
        void ParticleUpdate();

    public:
       // Emitter3D(const std::vector<std::shared_ptr<Particle3D>>& pParticle, const Vector3& pos, unsigned int releaseTime);
        
        /// <summary>
        /// 
        /// </summary>
        /// <param name="pParticle">�p�[�e�B�N���̃C���X�^���X</param>
        /// <param name="allSHotDead">�S�Ẵp�[�e�B�N����isDead���Ă΂ꂽ��G�~�b�^�[���폜���邩�ǂ���</param>
        /// <param name="particleNum">������</param>
        /// <param name="releaseTime">�p�[�e�B�N���̔��˕p�x(�t���[���Ŏw��)</param>
        /// <param name="pos">�����ʒu</param>
        /// <param name="name">�E�B���h�E�̖��O</param>
        Emitter3D(const Particle3D& pParticle,bool allShotDead, unsigned int particleNum, unsigned int releaseTime, const Vector3& pos,const std::string& name);
        ~Emitter3D() {}

        void Update()override;
        void Draw()override;

        void SetIsStop(const bool flag) 
        {
            isStop = flag; 
            releaseTimer.SetStopFlag(flag);
        }

        void SetPosition(const Vector3& pos) override;
       
        void SetReShotFlag(bool flag);
        bool GetReShotFlag()const { return reShot; }
       /* void SetPosition(const Vector3& pos) { SetPosition(pos); }

        Vector3 GetPosition()const { return GetPosition(); }*/
	};
}

