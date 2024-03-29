#pragma once

#include <Windows.h>

#include "Hero.h"
#include "Monster.h"
#include "Boss.h"

enum GAME_STATUS
{
	GAMING,
	PAUSE,
	WIN,
	GAMEOVER,
};

class GameManager
{
public:
	GameManager();

	void start();
	
	~GameManager();
private:
	void initialGame();
	void createBuf();
	void initialHero();
	void initialBoss();

	void getMonster(int rand);

	void testKey();

	void clearImpactBox();
	void updateALL();

	void updateHero();
	void updateMonster();
	void updateBoss();
	void updateBullet();

	void clearBuf();
	void displayALL();

	void displayUI();
	void displayScore();
	void displayHeroHP();
	void displayBossHP();
	void displayHero();
	void displayBoss();
	void displayMonster();
	void displayBullet();

	void emptyShooter();
	void end();
	
	HANDLE outputCache;
	HANDLE output;

	SMALL_RECT srWindowRect;
	COORD coordBufSize;

	GAME_STATUS gameStatus;

	Hero * myHero;
	Boss * boss;
	vector <Monster> monster;

	int HeroLife;
	bool isAlive;
	long increaseHeroLife_score;
	//int deathcount;

	bool isBoss;
	int killMonsterCount;

	bool b_UP;
	bool b_DOWN;
	bool b_LEFT;
	bool b_RIGHT;
	
	bool b_FIRE;
	bool b_ESCAPE;
	bool b_SLOW;

	DWORD t_fire;
	DWORD t_monstermove;
	int hero_shooter_count;

	vector <Shooter *> totalShooter;
};

