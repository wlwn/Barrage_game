#pragma once

#include <Windows.h>
#include <sstream>
#include <vector>
using namespace std;

struct ImpactBox
{
	bool isHero = false;
	bool isMonster = false;
	bool isHeroBullet = false;
	bool isMonsterBullet = false;
	bool isWall = false;
};

struct record
{
	COORD chPos;
	char ch;
	WORD color;
};

struct Graph
{
	COORD size;
	COORD centerPos;
	int the_num_of_ch;
	vector <record> data;
};


class Resoure
{
public:
	Resoure();

	void reset();

	Graph getHeroGraph(int num);
	Graph getBossGraph(int num);
	Graph getMonsterGraph(int num);

	int getHeroGraphCount();
	int getBossGraphCount();
	int getMonsterGraphCount();

	~Resoure();
private:
	void setHeroGraph();
	void setBossGraph();
	void setMonsterGraph();

	string rf;
	string cl;
	stringstream ss;

	vector <Graph> Hero;
	vector <Graph> Boss;
	vector <Graph> Monster;
};

