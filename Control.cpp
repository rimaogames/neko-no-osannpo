#include "Control.h"
#include "define.h"
#include <fstream>
#include<string>
#include <sstream>
//#include "pch.h"
using namespace std;

Control::Control() {
	//各クラスのインスタンス
	player = new Player;
	back = new Back;
	score = new Score;
	boss = new Boss;

	for(int i = 0; i < GRAZE_NUM; i++) {
		graze[i] = new Graze;
	}
	for (int i = 0; i < ITEM_NUM; i++) {
		item[i] = new Item;
	}

	//Enemyクラスのデータをクラスのインスタンスに入れる
	FILE* fp;//ファイルポインタ
	char buf[100];
	int s;
	int row = 0;
	int col=1;
	bool flag = false;
	memset(buf, 0, sizeof(buf));
	//読み取り専用でファイルを開ける
	if ((fopen_s(&fp,"enemydata.csv", "r"))!=0) MSG("エラー");
	
	while (fgetc(fp) != '\n'){};//1行目は何もしない
	
	while(1){//読み取り終わるまでループ

		while (1) {//1つのデータを読み取るまでループ

			s = fgetc(fp);//1文字だけ読み取り

			if(s == EOF){//もし末尾ならばフラグを立ててこのループを抜ける
				flag = true;
				break;
			}

			if (s != ',' && s != '\n') {//コンマや改行になるまでbufに文字を入れる
				strcat_s(buf, (const char*)&s);
			}
			else {//コンマや改行ならこのループを抜ける
				break;
			}
		}
		if(flag)  break;//フラグが立っているならファイル読み取り終わり

		// 今、bufにはExcelのセル1個分のデータが入ってる
				switch (col) {//今何列目？
				case 1: data[row].type = atoi(buf); break;//atoiで今の行のtypeにデータを数値として入れる
				case 2: data[row].shottype = atoi(buf); break;
				case 3:	data[row].move_pattern = atoi(buf); break;
				case 4: data[row].shot_pattern = atoi(buf); break;
				case 5: data[row].speed = atoi(buf); break;
				case 6:data[row].intime = atoi(buf); break;
				case 7:data[row].stoptime = atoi(buf); break;
				case 8:data[row].shottime = atoi(buf); break;
				case 9:data[row].outtime = atoi(buf); break;
				case 10:data[row].x = atoi(buf); break;
				case 11:data[row].y = atoi(buf); break;
				case 12:data[row].hp = atoi(buf); break;
				case 13:data[row].item = atoi(buf); break;
				}
				memset(buf, 0, sizeof(buf));//bufを初期化
				++col;//列をずらす
		if (s == '\n') {//行が終わったら
			col = 1;//列を1列目に戻す
			++row;//行をずらす
		}
		}
	//敵クラスを作る
	for (int i=0; i < ENEMY_NUM; i++) {
		enemy[i] = new Enemy(data[i].type, data[i].shottype, data[i].move_pattern, data[i].shot_pattern, data[i].speed, data[i].intime, data[i].stoptime, data[i].shottime, data[i].outtime, data[i].x, data[i].y, data[i].hp, data[i].item);

	}

	//音声ファイル読み込み
	sound_eshot = LoadSoundMem("enemyshot.mp3");
	sound_pshot = LoadSoundMem("playershot.mp3");
	sound_pdamage = LoadSoundMem("playerdamage.mp3");
	sound_edeath = LoadSoundMem("enemydeath.mp3");
	sound_graze = LoadSoundMem("graze.mp3");
	sound_item = LoadSoundMem("item.mp3");
	bgm=LoadSoundMem("bgm.ogg");
	eshot_flag = false;//音声フラグ初期化
	pshot_flag = false;
	pdamage_flag = false;
	edeath_flag = false;
	graze_flag = false;
	itemsound_flag = false;
	//他初期化
	end_flag = false;
	game_over = false;
	gameclear = false;
	deathenemy_num = 0;
	eefe_flag = false;
	pefe_flag = false;
	befe_flag = false;
	gameclear = false;
	eefecount = 0;
	pefecount = 0;
	//player死亡エフェクト読み込み
	if (LoadDivGraph("pdeath_efe1.png", 8, 8, 1, 120,120,pdeath_efegh) == -1) {
		MSG("エラー発生");
	}
	if (LoadDivGraph("edeath_efe1.png", 10, 5, 2, 320, 320, edeath_efegh) == -1) {
		MSG("エラー発生");
	}
	pefewidth = 120;
	pefeheight = 120;
	deathenemy_x = 0; deathenemy_y = 0;

	gameovergh = LoadGraph("over1.png");
	backmenu = LoadGraph("over2.png");
	cleargh= LoadGraph("clear.png");
	title=LoadGraph("title.png");
	bgmgh = LoadGraph("bgm.png");
	image = LoadGraph("image.png");

}



Control::~Control()
{
	//各クラスの解放
	delete player;
	delete back;
	//グレイズクラスの解放
	for (int i = 0; i < GRAZE_NUM; ++i) {
		delete graze[i];
	}

	delete score;

	//アイテムクラスの解放
	for (int i = 0; i < ITEM_NUM; ++i) {
		delete item[i];
	}
	delete boss;
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy[i] != NULL) {//まだ消滅してないenemyがあったらdelete
			delete enemy[i];
		}
	}

}

void Control::PlayerCoordinate(double* x, double* y) {
	double tempx=0,tempy=0;

	player->GetCoordinate(&tempx, &tempy);//座標を取得

	*x = tempx;//xに与える
	*y = tempy;//yに与える
}

void Control::EnemyCoordinate(int index, double* x, double* y) {
	double tempx=0, tempy=0;
	
	enemy[index]->GetCoordinate(&tempx, &tempy);//添字indexの敵の座標を取得

	*x = tempx;//xに与える
	*y = tempy;//yに与える
}
void Control::BossCoordinate(int index, double* x, double* y){
	double tempx = 0, tempy = 0;
	boss->GetCoordinate(&tempx, &tempy);
	*x = tempx;
	*y = tempy;
}
bool Control::CircleJudge(double pcir, double ecir, double pcir_x, double ecir_x, double pcir_y, double ecir_y) {
	double sum_radius = pcir + ecir;//半径の合計
	double x_length = pcir_x - ecir_x;
	double y_length = pcir_y - ecir_y;

	//ピタゴラスの定理からplayerと敵の距離が円形の半径の合計より短ければtrue
	if (sum_radius * sum_radius >= (x_length * x_length) + (y_length * y_length)) {
		return true;
	}else {
		return false;
	}
}


void Control::All() {
	
	if (CheckHitKey(KEY_INPUT_M) != 0) {//Menuに戻る時にクラスのインスタンスを初期化させて一番始めの状態にする
		game_count = 0;
		//各クラスの解放
		delete player;
		delete back;
		//グレイズクラスの解放
		for (int i = 0; i < GRAZE_NUM; ++i) {
			delete graze[i];
		}
		delete score;

		//アイテムクラスの解放
		for (int i = 0; i < ITEM_NUM; ++i) {
			delete item[i];
		}
		delete boss;
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (enemy[i] != NULL) {//まだ消滅してないenemyがあったらdelete
				delete enemy[i];
			}
		}

		player = new Player;
		back = new Back;
		score = new Score;
		boss = new Boss;
		for (int i = 0; i < GRAZE_NUM; i++) {
			graze[i] = new Graze;
		}
		for (int i = 0; i < ITEM_NUM; i++) {
			item[i] = new Item;
		}
		for (int i = 0; i < ENEMY_NUM; i++) {
			enemy[i] = new Enemy(data[i].type, data[i].shottype, data[i].move_pattern, data[i].shot_pattern, data[i].speed, data[i].intime, data[i].stoptime, data[i].shottime, data[i].outtime, data[i].x, data[i].y, data[i].hp, data[i].item);

		}
		game_over = false;
		gameclear = false;

		score->SetScore(SCOREDATA::HIGH_SCORE, hiscore);
	}


	eshot_flag = false;//サウンドフラグを初期化
	pshot_flag = false;
	edeath_flag = false;
	pdamage_flag = false;
	graze_flag = false;
	itemsound_flag = false;

	back->All();//先に背景
	player->All();//プレイヤーキャラ

	//フラグがたっているならサウンドフラグを立てる
	if (player->GetSoundshot()) {
		pshot_flag = true;
	}


	if (!boss->GetFlag()) {//まだbossいない
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (enemy[i] != NULL) {//インスタンスが生成されているならば
				//フラグがたっているならサウンドフラグを立てる
				if (enemy[i]->GetSoundshot() == true) {
					eshot_flag = true;
				}

				if (enemy[i]->All() == true) {//endflag=trueならば
					delete enemy[i];//クラス消滅
					enemy[i] = NULL;
				}
			}
			
		}
		EnemyAllJudge();
	}
	else {//Boss出現
		boss->All();
		if (boss->GetSoundshot()) eshot_flag=true;
		BossAllJudge();
	}

	if (game_count==BOSSTIME) boss->SetFlag(true);

	//グレイズの描画
	for (int i = 0; i < GRAZE_NUM; i++) {
		graze[i]->All();
	}
	//Itemの描画
	for (int i = 0; i < ITEM_NUM; i++) {
		if(item[i]->Getflag()) item[i]->All();
	}

	if (player->GetLife() == 0) { //プレイヤのHP=0 ゲームオーバーのフラグ
		game_over = true; 
	}
	



	back->All2();
	score->All();
	DrawGraph(SCORE_X, 360, title, TRUE);
	DrawGraph(SCORE_X, 390, bgmgh, TRUE);
	DrawGraph(SCORE_X, 420, image, TRUE);
	if (game_over) {
		player->SetLiveFlag();
		DrawGraph(20, 100, gameovergh, TRUE);
		DrawGraph(20, 150, backmenu, TRUE);
		int temp1=0, temp2=0;
		temp1 = score->GetScore(SCOREDATA::SCORE);
		temp2 = score->GetScore(SCOREDATA::HIGH_SCORE);
		if (temp2 <= temp1);
		score->SetScore(SCOREDATA::HIGH_SCORE, temp1);
	}else if (gameclear) {
		DrawGraph(20, 100, cleargh, TRUE);
		DrawGraph(20, 150, backmenu, TRUE);
		int temp1=0, temp2=0;
		temp1 = score->GetScore(SCOREDATA::SCORE);
		temp2 = score->GetScore(SCOREDATA::HIGH_SCORE);
		if (temp2 <= temp1);
		score->SetScore(SCOREDATA::HIGH_SCORE, temp1);
	
	}
	EFECTALL();
	SoundAll();
	++game_count;



}

void Control::EnemyAllJudge() {
	double px, py, ex, ey;//敵とplayerの弾の座標

	//playerの弾と敵の当たり判定
	
	  for (int i = 0; i < PLAYERSHOT_NUM; i++) {//弾の数だけチェック
		if (player->GetshotCoordinate(i, &px, &py)) {//playerの弾が画面にあるならば座標を貰って
			for (int s = 0; s < ENEMY_NUM; s++) {//敵の数だけ
				if (enemy[s] != NULL && !enemy[s]->GetDeathflag()) {//添字sのenemyがNULLじゃないかつ、死んでいない、帰還していない
					enemy[s]->GetCoordinate(&ex, &ey);//敵の座標を貰う
					if (CircleJudge(PLAYSHOT_RADIUS, ENEMY_RADIUS, px, ex, py, ey)) {//円形の当たり判定がtrueならば
						enemy[s]->SetDeathflag();//死亡フラグを立てる
						player->SetShotflag(i, false);//当たった弾のフラグを戻して
						edeath_flag = true;//敵死亡音フラグ
						SetenemyEffect(s);//エフェクトを設定
						eefe_flag = true;//エフェクトのフラグを立てる
						enemy[s]->GetCoordinate(&deathenemy_x, &deathenemy_y);//敵の死亡位置を取得
						score->SetScore(SCOREDATA::SCORE, 100);//一回倒したら100point
						for (int j = 0; j < ITEM_NUM; j++) {//アイテムを出現させる
							if (!item[j]->Getflag()) {//添え字jのアイテムが出現していない
								item[j]->Setflag(ex, ey, enemy[s]->GetItem());//アイテムをセットする
								break;
							}
						}
					}
				}
			}
		}
	   
	}
	double  px2,py2,ex2, ey2;//Playerと敵の弾の座標
	bool dam_tempflag = false;//ダメージを受けたらtrue
	bool gra_tempflag = false;//グレイズが当たったならtrue
	//敵の弾とplayerの当たり判定
	if (player->GetDamageflag() == false) {//今は生きており点滅していない

		player->GetCoordinate(&px2, &py2);//playerの座標を貰って
		for (int i = 0; i < ENEMY_NUM; i++) {//敵の数だけ
			if (enemy[i] != NULL) {//添字iのenemyがNULLじゃない(死んでても弾は残ってるからdeathflagはいらない）
				for (int s = 0; s < ENEMYSHOT_NUM; s++) {
					if (enemy[i]->GetshotCoordinate(s, &ex2, &ey2)){//敵（添字)の弾が画面にあるならば座標を貰う
						switch (enemy[i]->GetShottype()) {//弾の種類で変更
						case 0://弾1
							//当たり判定の前にグレイズ判定を行う
							if (CircleJudge(GRAZE_RADIUS, ENESHOT1_RADIOUS, px2, ex2, py2, ey2)) { //円形の当たり判定がtrueならば
								gra_tempflag = true;
							}
							//円形の当たり判定がtrueならば
							 if (CircleJudge(PLAYER_RADIUS, ENESHOT1_RADIOUS, px2, ex2, py2, ey2)) {//円形の当たり判定がtrueならば
								dam_tempflag = true;

							}
							break;
						case 1://弾2
							//当たり判定の前にグレイズ判定を行う
							if (CircleJudge(GRAZE_RADIUS, ENESHOT2_RADIOUS, px2, ex2, py2, ey2)) { //円形の当たり判定がtrueならば
								gra_tempflag = true;
							}
							//円形の当たり判定がtrueならば
							 if (CircleJudge(PLAYER_RADIUS, ENESHOT1_RADIOUS, px2, ex2, py2, ey2)) {//円形の当たり判定がtrueならば
								dam_tempflag = true;

							}
							break;
						case 2://弾3
							//当たり判定の前にグレイズ判定を行う
							if (CircleJudge(GRAZE_RADIUS, ENESHOT2_RADIOUS, px2, ex2, py2, ey2)) {//円形の当たり判定がtrueならば
								gra_tempflag = true;
							}
							//円形の当たり判定がtrueならば
							if (CircleJudge(PLAYER_RADIUS, ENESHOT3_RADIOUS, px2, ex2, py2, ey2)) { //円形の当たり判定がtrueならば
								dam_tempflag = true;
							}
							break;
						}
						if (gra_tempflag) {//グレイズ当たった
							if (!enemy[i]->GetGrazeflag(s)) {//その弾のフラグが立ってないなら立てる
								enemy[i]->SetGrazeflag(s);
								//フラグが立ってないグレイズのフラグを立てて座標を設定
								for (int j = 0; j < GRAZE_NUM; j++) {
									if (!graze[j]->Getflag()) {
										graze[j]->Setflag(px2, py2);
										break;//ループを抜ける
									}
								}
								//スコアを加算
								score->SetScore(SCOREDATA::GRAZE_SCORE, 1);
								score->SetScore(SCOREDATA::SCORE, 10);
								graze_flag = true;//グレイズの音フラグを立てる
							}
							gra_tempflag = false;//グレイズ判定フラグを戻す

						}

						if (dam_tempflag) {//ダメージをうけた
							player->SetDamageflag();//ダメージフラグを立てる
							enemy[i]->SetShotflag(s, false);//当たった弾のフラグを戻す
							pdamage_flag = true;//ダメージ音フラグ
							pefe_flag = true;//ダメージエフェクトフラグ
							dam_tempflag = false;
						}
					}

				}
			}
		}
		//playerとアイテムの当たり判定
		double ix, iy;//アイテムの位置を取得用
		for (int i = 0; i < ITEM_NUM; i++) {
			if (item[i]->Getflag()) {//フラグが立っている（出現中）アイテムが会ったら
				item[i]->Get_Position(&ix, &iy);//座標を取得
				if (CircleJudge(PLAYER_RADIUS, ITEM_RADIOUS, px2, ix, py2, iy)) {//判定がtrueだったら
					switch (item[i]->GetType()) {//タイプで湧ける
					case 0://スコアアイテム
						score->SetScore(SCOREDATA::SCORE, 500);//500点加算
						break;
					case 1://powerアイテム
						player->SetPower(1);
						score->SetScore(SCOREDATA::POWER,player->GetPower());//パワー増加
						break;
					}
					item[i]->DeleteItem();//アイテム消す
					itemsound_flag = true;//サウンドハンドルをセット
				}
			}
		}
			

	}//if(playerが今は生きており点滅していない)の終わり
	


	score->SetScore(SCOREDATA::LIFE, player->GetLife());
}
void Control::BossAllJudge() {
	double px, py, bx, by;//Bossの弾とplayerの座標
	int boss_hp;//BossのHP
	int item_number = 0;//Bossが出すアイテム
	int setix, setiy;//アイテムの座標を設定する用変数

	//playerの弾と敵の当たり判定
	if (!boss->GetNodamageFlag()) {//ボスは今は無敵ではない
		for (int i = 0; i < PLAYERSHOT_NUM; i++) {//弾の数だけチェック
			if (player->GetshotCoordinate(i, &px, &py)) {//playerの弾が画面にあるならば座標を貰って
				if (boss->GetFlag()) {//bossが生きている
					boss->GetCoordinate(&bx, &by);//bossの座標を貰う
					if (CircleJudge(PLAYSHOT_RADIUS, BOSS_RADIUS, px, bx, py, by)) {//円形の当たり判定がtrueならば
						boss_hp = boss->SetHP(1);
						player->SetShotflag(i, false);//当たった弾のフラグを戻して
						score->SetScore(SCOREDATA::SCORE, 50);//一回100point


						if (BOSS_HP * 2 / 3 >= boss_hp && boss->GetPreHP() > BOSS_HP * 2 / 3) {//HPが2/3になった
			
							befe_flag = true;//ダメージエフェクトフラグ
							edeath_flag = true;//弾当たり音フラグ
							score->SetScore(SCOREDATA::SCORE, 5000);//5000point
							for (int j = 0; j < ITEM_NUM; j++) {//アイテムを出現させる
								if (!item[j]->Getflag()) {//添え字jのアイテムが出現していない
									setix = (rand() % 151 - 75) + bx;
									setiy = (rand() % 151 - 75) + by;
									item[j]->Setflag(setix, setiy, 0);//スコアアイテムをセットする
									++item_number;
									if (item_number == 7)break;//アイテム7コ出したら終わり
								}
							}
							boss->SetDamage();
						}
						else if (BOSS_HP * 1 / 3 >= boss_hp && boss->GetPreHP() > BOSS_HP * 1 / 3) {//HPが1/3になった
							befe_flag = true;//ダメージエフェクトフラグ
							edeath_flag = true;//弾当たり音フラグ
							score->SetScore(SCOREDATA::SCORE, 5000);//5000point
							for (int j = 0; j < ITEM_NUM; j++) {//アイテムを出現させる
								if (!item[j]->Getflag()) {//添え字jのアイテムが出現していない
									setix = (rand() % 151 - 75) + bx;
									setiy = (rand() % 151 - 75) + by;
									item[j]->Setflag(setix, setiy, 0);//スコアアイテムをセットする
									++item_number;
									if (item_number == 7)break;//アイテム7コ出したら終わり
								}
							}
							boss->SetDamage();
						}
						else if (boss_hp < 0) {//hpが0になったら
							gameclear = true;
							boss->SetFlag(false);//敵死亡
							befe_flag = true;//ダメージエフェクトフラグ
							edeath_flag = true;//弾当たり音フラグ
							score->SetScore(SCOREDATA::SCORE, 10000);//10000point
							for (int j = 0; j < ITEM_NUM; j++) {//アイテムを出現させる
								if (!item[j]->Getflag()) {//添え字jのアイテムが出現していない
									setix = (rand() % 151 - 75) + bx;
									setiy = (rand() % 151 - 75) + by;
									item[j]->Setflag(setix, setiy, 0);//スコアアイテムをセットする
									++item_number;
									if (item_number == 15)break;//アイテム15コ出したら終わり
								}
							}
						}
					}
				}
			}
		}
	}

		double  px2, py2, bx2, by2;//Bossの弾とPlayerの座標
		int shot_pattern;
		bool dam_tempflag = false;//ダメージを受けたらtrue
		bool gra_tempflag = false;//グレイズが当たったならtrue

		//Bossの弾とplayerの当たり判定
		if (player->GetDamageflag() == false) {//今は生きており点滅していない

			player->GetCoordinate(&px2, &py2);//playerの座標を貰って
			for (int s = 0; s < BOSSSHOT_NUM; s++) {//boss1の弾の数だけ
				if (boss->GetshotCoordinate(s, &bx2, &by2, &shot_pattern)) {
					;
					switch (shot_pattern) {//bssの弾の種類で変更(bossは弾の種類=打ち方の種類だからtypeでなくpatternで済む)
					case 0://弾1
						//当たり判定の前にグレイズ判定を行う
						if (CircleJudge(GRAZE_RADIUS, ENESHOT1_RADIOUS, px2, bx2, py2, by2)) { //円形の当たり判定がtrueならば
							gra_tempflag = true;
						}
						//円形の当たり判定がtrueならば
						if (CircleJudge(PLAYER_RADIUS, ENESHOT1_RADIOUS, px2, bx2, py2, by2)) {//円形の当たり判定がtrueならば
							dam_tempflag = true;

						}
						break;
					case 1://弾2
						//当たり判定の前にグレイズ判定を行う
						if (CircleJudge(GRAZE_RADIUS, ENESHOT2_RADIOUS, px2, bx2, py2, by2)) { //円形の当たり判定がtrueならば
							gra_tempflag = true;
						}
						//円形の当たり判定がtrueならば
						if (CircleJudge(PLAYER_RADIUS, ENESHOT1_RADIOUS, px2, bx2, py2, by2)) {//円形の当たり判定がtrueならば
							dam_tempflag = true;

						}
						break;
					case 2://弾3
						//当たり判定の前にグレイズ判定を行う
						if (CircleJudge(GRAZE_RADIUS, ENESHOT2_RADIOUS, px2, bx2, py2, by2)) {//円形の当たり判定がtrueならば
							gra_tempflag = true;
						}
						//円形の当たり判定がtrueならば
						if (CircleJudge(PLAYER_RADIUS, ENESHOT3_RADIOUS, px2, bx2, py2, by2)) { //円形の当たり判定がtrueならば
							dam_tempflag = true;
						}
						break;
					}
					if (gra_tempflag) {//グレイズ当たった
						if (!boss->GetGrazeflag(s)) {//その弾のフラグが立ってないなら立てる
							boss->SetGrazeflag(s);
							//フラグが立ってないグレイズのフラグを立てて座標を設定
							for (int j = 0; j < GRAZE_NUM; j++) {
								if (!graze[j]->Getflag()) {
									graze[j]->Setflag(px2, py2);
									break;//ループを抜ける
								}
							}
							//スコアを加算
							score->SetScore(SCOREDATA::GRAZE_SCORE, 1);
							score->SetScore(SCOREDATA::SCORE, 10);
							graze_flag = true;//グレイズの音フラグを立てる
						}
						gra_tempflag = false;//グレイズ判定フラグを戻す

					}

					if (dam_tempflag) {//ダメージをうけた
						player->SetDamageflag();//ダメージフラグを立てる
						boss->SetShotflag(s, false);//当たった弾のフラグを戻す
						pdamage_flag = true;//ダメージ音フラグ
						dam_tempflag = false;
						break;//他の弾は判定する必要はないから抜ける
					}
				}

			}

			//playerとアイテムの当たり判定
			double ix, iy;//アイテムの位置を取得用
			for (int i = 0; i < ITEM_NUM; i++) {
				if (item[i]->Getflag()) {//フラグが立っている（出現中）アイテムが会ったら
					item[i]->Get_Position(&ix, &iy);//座標を取得
					if (CircleJudge(PLAYER_RADIUS, ITEM_RADIOUS, px2, ix, py2, iy)) {//判定がtrueだったら
						switch (item[i]->GetType()) {//タイプで湧ける
						case 0://スコアアイテム
							score->SetScore(SCOREDATA::SCORE, 500);//500点加算
							break;
						case 1://powerアイテム
							player->SetPower(1);
							score->SetScore(SCOREDATA::POWER, player->GetPower());//パワー増加
							break;
						}
						item[i]->DeleteItem();//アイテム消す
						itemsound_flag = true;//サウンドハンドルをセット
					}
				}
			}

		}//if(playerが今は生きており点滅していない)の終わり

		score->SetScore(SCOREDATA::LIFE, player->GetLife());
	}

void Control::SetenemyEffect(int i){
	switch (enemy[i]->GetEnemytype()) {
	case 0: if (LoadDivGraph("edeath_efe1.png", 10, 5, 2, 320, 320, edeath_efegh) == -1) {
		       MSG("エラー発生");
	         }
		  eefewidth = 320;
		  eefeheight = 320;
		  break;
	}
}


void Control::EFECTALL() {
	int temp1,temp2;
	double px,py,bx,by;

	if (eefe_flag) {
		temp1 = eefecount;
		DrawGraph((int)deathenemy_x - eefewidth / 2, (int)deathenemy_y - eefeheight / 2, edeath_efegh[temp1], TRUE);
		++eefecount;
		if (eefecount == 10) { eefecount = 0; eefe_flag = false;  }
	}

	if (pefe_flag) {
		player->GetCoordinate(&px, &py);
		temp2 = pefecount % 40 / 5;
		DrawGraph((int)px - pefewidth / 2, (int)py - pefeheight / 2, pdeath_efegh[temp2], TRUE);
		++pefecount;
		if (pefecount == 40) { pefecount = 0; pefe_flag = false; }
	}
	if(befe_flag) {
		boss->GetCoordinate(&bx, &by);
		temp1 = eefecount;
		DrawGraph((int)bx - eefewidth / 2, (int)bx - eefeheight / 2, edeath_efegh[temp1], TRUE);
		++eefecount;
		if (eefecount == 10) { eefecount = 0; befe_flag = false; }
	}
}

int Control::GetHiscore() {
	return score->GetScore(SCOREDATA::HIGH_SCORE);
}
void Control::SoundAll() {
	//ライブラリ、ifのフラグが立ったなら第一引数の音声データをバックグラウンド再生
	if (pshot_flag) PlaySoundMem(sound_pshot, DX_PLAYTYPE_BACK);
	if (eshot_flag) PlaySoundMem(sound_eshot, DX_PLAYTYPE_BACK);
	if (pdamage_flag)PlaySoundMem(sound_pdamage, DX_PLAYTYPE_BACK);
	if (edeath_flag)PlaySoundMem(sound_edeath, DX_PLAYTYPE_BACK);
	if (graze_flag)PlaySoundMem(sound_graze, DX_PLAYTYPE_BACK);
	if (itemsound_flag)PlaySoundMem(sound_item, DX_PLAYTYPE_BACK);
	if (game_count == 5) PlaySoundMem(bgm, DX_PLAYTYPE_BACK);
	if (CheckHitKey(KEY_INPUT_M) != 0)StopSoundMem(bgm);
}


