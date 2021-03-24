#include "SceneMgr.h"
#include "Control.h"
#include "define.h"

//�ŏ��̓��j���[��ʂɂ���
eScene SceneMgr::NextScene = eScene::Scene_None;
eScene SceneMgr::Scene = eScene::Scene_Menu;

//�R���X�g���N�^
SceneMgr::SceneMgr() {
    //�C���X�^���X
    menu = new Menu;
    config = new Config;
    result = new Result;
    //���C�u�����ŉ��f�[�^�̓ǂݍ���
    topsound = LoadSoundMem("MUSIC/bagtop.ogg");     //�g�b�v�ɖ߂�
    gamestartsound = LoadSoundMem("MUSIC/start.ogg");//�Q�[���J�n
    stopsound = LoadSoundMem("MUSIC/Stop.ogg");//�ꎞ��~
    selectother_sound = LoadSoundMem("MUSIC/otherselect.ogg"); //�Q�[���J�n�ȊO�̍��ڑI��
    //�n���h�����Ȃ炷���ǂ����̃t���O������
    topsound_flag = false;
    gamestartsound_flag = false;
    stopsound_flag = false;
    selectothersound_flag = false;

}

//������
void SceneMgr::Initialize(eScene scene) {
    //Control�N���X�̎Q��
    Control& control = Control::Instance();

    switch (scene) {          //�V�[���ɂ���ď����𕪊�

    case eScene::Scene_Menu:       //�w���ʂ����j���[��ʂȂ�
        menu->Initialize();                 //���j���[��ʂ̏���������������
        break;
    case eScene::Scene_Game:       //�w���ʂ��Q�[����ʂȂ�
        control.Initialize();           //�Q�[����ʂ̏���������������             
        break;
    case eScene::Scene_Config:     //�w���ʂ��ݒ��ʂȂ�
        config->Initialize();          //�ݒ��ʂ̏���������������
        break;
    case eScene::Scene_Howto:     //�w���ʂ��V�ѕ���ʂȂ�
        howto = new Howto;          //�V�ѕ���ʂ̏���������������
        break;
    case eScene::Scene_Stop:     //�w���ʂ��ꎞ��~��ʂȂ�
        stop = new Stop;          //�ꎞ��~��ʂ̏���������������
        break;
    case eScene::Scene_Result:
        result->Initialize();
        break;
    default:
        break;
    }
}
//�I���̏���
void SceneMgr::Finalize(eScene scene) {
    //Control�N���X�̎Q��
    Control& control = Control::Instance();
    switch (scene) {          //�V�[���ɂ���ď����𕪊�
    case eScene::Scene_Menu:     //�w���ʂ����j���[��ʂȂ�
        menu->Finalize() ;                //���j���[��ʂ̏I���̏���������
        break;
    case eScene::Scene_Game:    //�w���ʂ��Q�[����ʂȂ�
        control.Finalize();         //�Q�[����ʂ̏I���̏���
        break;
    case eScene::Scene_Config:  //�w���ʂ��ݒ��ʂȂ�
        config->Finalize();            //�ݒ��ʂ̏I���̏���
        break;
    case eScene::Scene_Howto:  //�w���ʂ��V�ѕ���ʂȂ�
        delete howto;             //�V�ѕ���ʂ̏I���̏���
        break;  
    case eScene::Scene_Stop:  //�w���ʂ��ꎞ��~��ʂȂ�
        delete stop;             //�ꎞ��~��ʂ̏I���̏���
         break;
    case eScene::Scene_Result:  //�w���ʂ����ʉ�ʂȂ�
        result->Finalize();             //���ʉ�ʂ̏I���̏���
        break;
    default:
        break;

    }
}
//���̃V�[���������̃V�[���ɐݒ�(���N���X����Ăяo�����)
void SceneMgr::ChangeScene(eScene scene) {
    //���̃V�[���Ɉ����̃V�[�������
    NextScene = scene;

    //���̃t���O�𗧂Ă�
    if (scene == eScene::Scene_Stop) {
        stopsound_flag = true;
    }
    if (scene == eScene::Scene_Menu) {
        topsound_flag = true;
    }
    if (scene == eScene::Scene_Game) {
        gamestartsound_flag = true;
    }
    if (scene == eScene::Scene_Howto || scene == eScene::Scene_Config|| scene == eScene::Scene_Result) {
        selectothersound_flag = true;
    }
}

//���̏���
void SceneMgr::SoundAll() {
    //���C�u�����ł��ꂼ��̃t���O�������Ă���Ȃ特���o��
    if (topsound_flag)PlaySoundMem(topsound, DX_PLAYTYPE_BACK, TRUE);
    if (gamestartsound_flag)PlaySoundMem(gamestartsound, DX_PLAYTYPE_BACK, TRUE);
    if (stopsound_flag)PlaySoundMem(stopsound, DX_PLAYTYPE_BACK, TRUE);
    if (selectothersound_flag)PlaySoundMem(selectother_sound, DX_PLAYTYPE_BACK, TRUE);

}

//��ʂ̍X�V
void SceneMgr::Update() {

    //���̓Q�[����ʂŎ��ɂ����̂��ꎞ��~��ʂ����ʉ�ʂȂ��(���̃V�[�����I�������Ȃ��j
    if (NextScene == eScene::Scene_Stop || NextScene==eScene::Scene_Result) {

        //���̃V�[���Ɏ��̗\��̃V�[��������
        Scene = NextScene;
        //�\��̃V�[���͏��������Ă���
        NextScene = eScene::Scene_None;
        //���̃V�[���i�\�肳��Ă����V�[���j��������������
        Initialize(Scene);
    }
    //�ꎞ��~��ʂ���Q�[����ʂɍs���Ȃ�΁i���̃V�[���������������Ȃ��j
    else if (Scene == eScene::Scene_Stop && NextScene == eScene::Scene_Game) {
        //���̉�ʂ͏I������
        Finalize(Scene);
        //��ʂ͓���ւ�
        Scene = NextScene;
        //�\��̃V�[���͏�����
        NextScene = eScene::Scene_None;
    }
    //�ꎞ��~���(or���ʉ�ʁj���烁�j���[�ɂ����̂Ȃ�(���ɃQ�[�����������j
    else if ((Scene == eScene::Scene_Stop|| Scene==eScene::Scene_Result) && NextScene == eScene::Scene_Menu) {
        //���̉�ʂ͏I������
        Finalize(Scene);
        Finalize(eScene::Scene_Game);
        //��ʂ͓���ւ�
        Scene = NextScene;
        //�\��̃V�[���͏�����
        NextScene = eScene::Scene_None;
        //���̃V�[���i�\�肳��Ă����V�[���j��������������
        Initialize(Scene);


    }
    //���̏ꍇ�̉�ʈړ��Ȃ��
    else if (NextScene != eScene::Scene_None) {
        //���̉�ʂ͏I������
            Finalize(Scene);
            //��ʂ͓���ւ�
            Scene = NextScene;
            //�\��̃V�[���͏�����
            NextScene = eScene::Scene_None;
            //���̃V�[���i�\�肳��Ă����V�[���j��������������
            Initialize(Scene);
    }
  
    //Control�N���X�̎Q��
    Control& control = Control::Instance();

    //��ʂ��X�V���閽�߂����邩����
    switch (Scene) {       //�V�[���ɂ���ď����𕪊�
    case eScene::Scene_Menu:    //���݂̉�ʂ����j���[�Ȃ�
        menu->Update();            //���j���[��ʂ̍X�V�֐�
        break;//�ȉ���
    case eScene::Scene_Game:    //���݂̉�ʂ��Q�[���Ȃ�
        control.Update();          //�Q�[����ʂ̍X�V�֐�
        break;
    case eScene::Scene_Config:  //���݂̉�ʂ��ݒ�Ȃ�
        config->Update();          //�ݒ�̍X�V�֐�
        break;
    case eScene::Scene_Howto:  //���݂̉�ʂ��V�ѕ������Ȃ�
        howto->Update();           //�V�ѕ��̍X�V�֐�
        break;
    case eScene::Scene_Stop:     //���݂̉�ʂ��ꎞ��~��ʂȂ�
        stop->Update();            //�ꎞ��~�̍X�V�֐�
        break;
    case eScene::Scene_Result:     //���݂̉�ʂ����ʉ�ʂȂ�
        result->Update();            //���ʂ̍X�V�֐�
        break;
    default:
        break;

    }

}


//���e�̎��s
void SceneMgr::All() {
    //Control�N���X�̎Q��
    Control& control = Control::Instance();


    switch (Scene) {      //�V�[���ɂ���ď����𕪊�
    case eScene::Scene_Menu:   //���݂̉�ʂ����j���[��ʂȂ�
        menu->All();              //���j���[��ʂ̏���������
        break;//�ȉ���
    case eScene::Scene_Game: //���݂̉�ʂ��Q�[����ʂȂ�
        control.All();            //�Q�[���̏���������
        break;
    case eScene::Scene_Config:   //���݂̉�ʂ��ݒ��ʂȂ�
        config->All();             //�ݒ�̏���������
        break;
    case eScene::Scene_Howto:    //���݂̉�ʂ��V�ѕ���ʂȂ�
        howto->All();              //�V�ѕ���ʂ̏���������
        break;
    case eScene::Scene_Stop: //���݂̉�ʂ��ꎞ��~��ʂȂ�
        stop->All();             //�ꎞ��~�̏���������
        break;
    case eScene::Scene_Result: //���݂̉�ʂ����ʉ�ʂȂ�
        result->All();             //���ʂ̏���������
        break;
    }
}

//Main�ŌĂяo�����֐�
void SceneMgr::Loop() {
    //�T�E���h�t���O��������
    topsound_flag = false;
    gamestartsound_flag = false;
    stopsound_flag = false;
    selectothersound_flag = false;

    //�X�V
    Update();
    //���s
    All();
    //�����o��
    if(Config::select_sound==ON) SoundAll();
}