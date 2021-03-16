#pragma once

typedef enum {      //�񋓌^
	Scene_Menu,    //���j���[���
	Scene_Game,    //�Q�[�����
	Scene_Stop,    //�ꎞ��~���
} eScene;


//��ʂ̏���
class Menu
{
private:
	//���݂̉��(�V�[��)
	int Scene;
	//�Q�[����蒼���t���O
	bool restart_flag;
	//�T�E���h�n���h��
	int topsound;     //�g�b�v�ɖ߂�
	int gamestartsound;  //�Q�[���J�n
	int stopsound;  //�ꎞ��~
	//�n���h�����Ȃ炷���ǂ����̃t���O
	bool topsound_flag;
	bool gamestartsound_flag;
	bool stopsound_flag;

private:
	void SoundAll();//��ʈړ��̎��̉��̏���
    void UpdateScene();//��ʂ̍X�V
	void Top();//���j���[���
    void Game();//�Q�[�����
	void Stop();//�ꎞ��~���
public:
	Menu();//�R���X�g���N�^
	void  All();//Main�ŌĂяo���֐�
};

