#pragma once
#include "SceneBase.h"


//���ʉ�ʂ̃N���X
class Result :public SceneBase
{
private:

    int result_sound;//���ɍs���Ƃ��̉��n���h��
    int up_sound;//�n�C�X�R�A�X�V�T�E���h�n���h��
    bool resound_flag;//���ɍs���Ƃ��̉��n���h���@��炷���t���O
    bool upsound_flag;//�n�C�X�R�A�X�V�T�E���h�n���h���@��炷���t���O

    int upgh;//�͂��������X�V����
    int resultgh;//��ʂ̃O���t�B�b�N�n���h��
    int g_number[10];//�����̃O���t�B�b�N�n���h��
    int nextgh;//���֕���
    int endgh;//���j���[�֕���

    int rescore;//�X�R�A
    int regraze;//�O���C�Y
    int rehigh_score;//�n�C�X�R�A
    int count;//����G���^�[�L�[���������H
    bool endflag;//��ʂ̕\�����S�ďI��������ǂ���


private:
    void Draw();//�`��
    void SetResult();//���ʂ��Z�b�g����
    void SoundAll();//���̏���
public:
    Result();
    void Initialize();//������
    void Finalize();//�I���̏���
    void Update() ;//�I�[�o�[���C�h
    void All();//�I�[�o�[���C�h

};