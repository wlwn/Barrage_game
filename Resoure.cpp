#include "Resoure.h"

#include <fstream>
#include <iostream>
using namespace std;

Resoure::Resoure()
{
	rf = ".rf";
	cl=".color";

	setHeroGraph();
	setBossGraph();
	setMonsterGraph();
}

void Resoure::reset()
{
	setBossGraph();
	setHeroGraph();
	setMonsterGraph();
}

Graph Resoure::getHeroGraph(int num)
{
	if (num <= Hero.size() && num > 0)
		return Hero[num - 1];
	return Hero[0];
}

Graph Resoure::getBossGraph(int num)
{
	if (num <= Boss.size() && num > 0)
		return Boss[num - 1];
	return Boss[0];
}

Graph Resoure::getMonsterGraph(int num)
{
	if (num <= Monster.size() && num > 0)
		return Monster[num - 1];
	return Monster[0];
}

int Resoure::getHeroGraphCount()
{
	return Hero.size();
}

int Resoure::getBossGraphCount()
{
	return Boss.size();
}

int Resoure::getMonsterGraphCount()
{
	return Monster.size();
}

Resoure::~Resoure()
{
	Hero.clear();
	Boss.clear();
	Monster.clear();
}

void Resoure::setHeroGraph()
{
	string path = ".\\Resoure\\Hero\\Hero_";
	string temp;
	for (int i = 1;; i++)
	{
		ss.clear();
		ss << i;
		ss >> temp;
		temp = path + temp;
		ifstream getgraph(temp + rf , ios::in);
		ifstream getcolor(temp + cl , ios::in | ios::binary);
		if (getgraph && getcolor)
		{
			Graph graph;
			graph.the_num_of_ch = 0;
			graph.data.clear();

			char ch_buf = 0;
			WORD color_buf;
			record data_buf;

			short x = 0, y = 0;
			for (; getgraph.peek() != EOF; y++)
			{
				x = 0;
				for (; ch_buf != '\n'; x++)
				{
					ch_buf = getgraph.get();

					if (ch_buf != '\n')
						getcolor.read(reinterpret_cast<char*>( &color_buf ), sizeof(WORD));
					if (ch_buf != ' ' && ch_buf != '\n')
					{
						graph.the_num_of_ch++;
						data_buf.ch = ch_buf;
						data_buf.color = color_buf;
						data_buf.chPos = { x,y };
						//data_buf.impactbox.isHero = true;
						graph.data.push_back(data_buf);
						if (color_buf == (FOREGROUND_RED | FOREGROUND_INTENSITY))
							graph.centerPos = { x,y };
					}
				}
				ch_buf = 0;
			}
			graph.size = { x - 1,y };
			Hero.push_back(graph);
		}
		else
			break;
	}
}

void Resoure::setBossGraph()
{
	string path = ".\\Resoure\\Boss\\Boss_";
	string temp;
	for (int i = 1;; i++)
	{

		ss.clear();
		ss << i;
		ss >> temp;
		temp = path + temp;
		ifstream getgraph(temp + rf, ios::in);
		ifstream getcolor(temp + cl, ios::in | ios::binary);
		if (getgraph && getcolor)
		{
			Graph graph;
			graph.the_num_of_ch = 0;
			graph.data.clear();

			char ch_buf = 0;
			WORD color_buf;
			record data_buf;

			short x = 0, y = 0;
			for (; getgraph.peek() != EOF; y++)
			{
				x = 0;
				for (; ch_buf != '\n'; x++)
				{
					ch_buf = getgraph.get();

					if (ch_buf != '\n')
						getcolor.read(reinterpret_cast<char*>( &color_buf ), sizeof(WORD));
					if (ch_buf != ' ' && ch_buf != '\n')
					{
						graph.the_num_of_ch++;
						data_buf.ch = ch_buf;
						data_buf.color = color_buf;
						data_buf.chPos = { x,y };
						//data_buf.impactbox.isMonster = true;
						graph.data.push_back(data_buf);
					}
				}
				ch_buf = 0;
			}
			
			graph.size = { x - 1,y };
			graph.centerPos.X = ( graph.size.X - 1 ) / 2;
			graph.centerPos.Y = ( graph.size.Y - 1 ) / 2;
			Boss.push_back(graph);
		}
		else
			break;
	}
}

void Resoure::setMonsterGraph()
{
	string path = ".\\Resoure\\Monster\\Monster_";
	string temp;
	for (int i = 1;; i++)
	{
		ss.clear();
		ss << i;
		ss >> temp;
		temp = path + temp;
		ifstream getgraph(temp + rf, ios::in);
		ifstream getcolor(temp + cl, ios::in | ios::binary);
		if (getgraph && getcolor)
		{
			Graph graph;
			graph.the_num_of_ch = 0;
			graph.data.clear();

			char ch_buf = 0;
			WORD color_buf;
			record data_buf;

			short x = 0, y = 0;
			for (; getgraph.peek() != EOF; y++)
			{
				x = 0;
				for (; ch_buf != '\n'; x++)
				{
					ch_buf = getgraph.get();

					if (ch_buf != '\n')
						getcolor.read(reinterpret_cast<char*>( &color_buf ), sizeof(WORD));
					if (ch_buf != ' ' && ch_buf != '\n')
					{
						graph.the_num_of_ch++;
						data_buf.ch = ch_buf;
						data_buf.color = color_buf;
						data_buf.chPos = { x,y };
						//data_buf.impactbox.isMonster = true;
						graph.data.push_back(data_buf);
					}
				}
				ch_buf = 0;
			}

			graph.size = { x - 1,y };
			graph.centerPos.X = ( graph.size.X - 1 ) / 2;
			graph.centerPos.Y = ( graph.size.Y - 1 ) / 2;
			Monster.push_back(graph);
		}
		else
			break;
	}
}
