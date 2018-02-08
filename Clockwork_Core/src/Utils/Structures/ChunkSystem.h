#pragma once
/*************************************************************************
* Clockwork-Engine
* A C++/Opengl/GLFW3 game engine
* Website: clock-work.tk
*------------------------------------------------------------------------
* Copyright (C) 20017-2018 Niko Miklis <clock-work@gmx.de> - All Rights Reserved
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
* You can use this software under the following License: https://github.com/Clock-work/Clockwork-Engine/blob/master/LICENSE
*************************************************************************/
#include <iostream>
#include <vector>
#include "src\Maths\MathFunctions.h"
#include "LinkedList.h"

class ChunkSystem
{

public:
	struct Pos
	{
		float x, y, z;
		Pos(float x, float y, float z) noexcept
			:x(x), y(y), z(z)
		{}
		Pos() noexcept
			:x(0), y(0), z(0)
		{}

		friend Pos operator+(Pos pos1, const Pos& pos2) noexcept
		{
			pos1.x += pos2.x;
			pos1.y += pos2.y;
			pos1.z += pos2.z;
			return pos1;
		}
		friend Pos operator+(Pos pos, float val) noexcept
		{
			pos.x += val;
			pos.y += val;
			pos.z += val;
			return pos;
		}
		friend bool operator<(const Pos& pos1, const Pos& pos2) noexcept
		{
			float val1 = pos1.x + pos1.y + pos1.z;
			float val2 = pos2.x + pos2.y + pos2.z;
			return val1 < val2;
		}

	};

private:
	class Chunk
	{

	private:
		friend class ChunkSystem;

	public:
		class ChunkObject
		{
			Chunk* m_chunk;
			virtual ~ChunkObject() noexcept = default;
			virtual float getChunkpositionX() noexcept = 0;
			virtual float getChunkpositionY() noexcept = 0;
			virtual float getChunkpositionZ() noexcept = 0;
			virtual void render() noexcept = 0;
			virtual bool tick(double time) noexcept = 0;
		};

	private:
		Pos min, max;
		union
		{
			struct { Chunk* left, *right, *top, *bot, *front, *back; };//left-right: x ; top-bot: y ; front-back: z
			Chunk* near1[6];
		};

	public:
		Chunk(Pos bordermin, Pos bordermax, unsigned int xcount, unsigned int ycount, unsigned int zcount, Pos chunksize) noexcept
		{
			//für tick/render nicht enden speichern, sondern immer eine bestimmte länge für tick/render mitgeben und dann den würfel in reihen, oder so durchgehen und nur eine bestimmte länge, sonst xcount/ycount/etc aus der chunksystem klasse nehmen, damit es nicht unendlich ist
			this->min = bordermin;
			this->max = clockwork::maths::MathFunctions<ChunkSystem::Pos>::min((min + chunksize), bordermax);

			--zcount;//zrow start
			if (zcount > 0)
			{
				float tempz = (max.z + chunksize.z) < bordermax.z ? (max.z + chunksize.z) : bordermax.z;
				front = new Chunk(Pos(min.x, min.y, min.z + chunksize.z), Pos(max.x, max.y, tempz), bordermax, xcount, ycount, zcount, chunksize, this, this, 10);
			}
			else
			{
				back = this;
				front = this;
			}

			--xcount;//xrow start
			if (xcount > 0)
			{
				float tempx = (max.x + chunksize.x) < bordermax.x ? (max.x + chunksize.x) : bordermax.x;
				right = new Chunk(Pos(min.x + chunksize.x, min.y, min.z), Pos(tempx, max.y, max.z), bordermax, xcount, ycount, chunksize, this, this);
			}
			else
			{
				left = this;
				right = this;
			}

			--ycount;//yrow start
			if (ycount > 0)
			{
				float tempy = (max.y + chunksize.y) < bordermax.y ? (max.y + chunksize.y) : bordermax.y;
				top = new Chunk(Pos(min.x, min.y + chunksize.y, min.z), Pos(max.x, tempy, max.z), bordermax, xcount, ycount, chunksize, this, this, false);
				top->connectYRow(this, this, 1);//y-row connect left-right
				if (right != this)
					right->connectXRow(this);//for each x-row y-row connect left-right
			}
			else
			{
				bot = this;
				top = this;
			}

			if (zcount > 0)//z-row connect
			{
				connectZRow(this, this);
			}

		}

	private:
		void firstFirst() noexcept
		{

		}

		Chunk(Pos min, Pos max, const Pos& limit, unsigned int xcount ,unsigned int ycount, unsigned int zcount, const Pos& chunksize, Chunk* prevz, Chunk* startz,int isZ) noexcept//X-Y-start | plate | Z-row
		{
			this->min = min;
			this->max = max;

			--zcount;//zrow start
			if (zcount > 0)
			{
				float tempz = (max.z + chunksize.z) < limit.z ? (max.z + chunksize.z) : limit.z;
				back = prevz;
				front = new Chunk(Pos(min.x, min.y, min.z + chunksize.z), Pos(max.x, max.y, tempz), limit, xcount, ycount, zcount, chunksize, this, startz, isZ);
			}
			else
			{
				back = prevz;
				front = startz;
				startz->back = this;
			}

			--xcount;//xrow start
			if (xcount > 0)
			{	
				float tempx = (max.x + chunksize.x) < limit.x ? (max.x + chunksize.x) : limit.x;
				right = new Chunk(Pos(min.x + chunksize.x, min.y, min.z), Pos(tempx, max.y, max.z), limit, xcount, ycount, chunksize, this, this);
			}
			else
			{
				left = this;
				right = this;
			}

			--ycount;//yrow start
			if (ycount > 0)
			{
				float tempy = (max.y + chunksize.y) < limit.y ? (max.y + chunksize.y) : limit.y;
				top = new Chunk(Pos(min.x, min.y + chunksize.y, min.z), Pos(max.x, tempy, max.z), limit, xcount, ycount, chunksize, this, this, false);
				top->connectYRow(this, this, 1);//yrow connect left-right
				if (right != this)
					right->connectXRow(this);//for each xrow yrow connect left-right
			}
			else
			{
				bot = this;
				top = this;
			}
		}
		Chunk(Pos min, Pos max, const Pos& limit, unsigned int xcount, unsigned int ycount, const Pos& chunksize, Chunk* prev, Chunk* start) noexcept//X-row left-right
		{
			this->min = min;
			this->max = max;

			front = this;
			back = this;

			--xcount;//xrow created left-right connected
			if (xcount > 0)
			{
				float tempx = (max.x + chunksize.x) < limit.x ? (max.x + chunksize.x) : limit.x;
				left = prev;
				right = new Chunk(Pos(min.x + chunksize.x, min.y, min.z), Pos(tempx, max.y, max.z), limit, xcount,ycount, chunksize, this, start);
			}
			else
			{
				left = prev;
				right = start;
				start->left = this;
			}

			--ycount;//for each xrow yrow start
			if (ycount > 0)
			{
				float tempy = (max.y + chunksize.y) < limit.y ? (max.y + chunksize.y) : limit.y;
				top = new Chunk(Pos(min.x, min.y + chunksize.y, min.z), Pos(max.x, tempy, max.z), limit, xcount, ycount, chunksize, this, this, false);
			}
			else
			{
				bot = this;
				top = this;
			}
		}
		Chunk(Pos min, Pos max, const Pos& limit, unsigned int xcount, unsigned int ycount, const Pos& chunksize, Chunk* prev, Chunk* start, bool bottom) noexcept//Y-row down-top
		{
			this->min = min;
			this->max = max;

			front = this;
			back = this;

			--ycount;//y-row created, top-bot connected
			if (ycount > 0)
			{
				float tempy = (max.y + chunksize.y) < limit.y ? (max.y + chunksize.y) : limit.y;
				bot = prev;
				top = new Chunk(Pos(min.x, min.y + chunksize.y, min.z), Pos(max.x, tempy, max.z), limit, xcount, ycount, chunksize, this, start, false);
			}
			else
			{
				bot = prev;
				top = start;
				start->bot = this;
			}
		}
		void connectXRow(Chunk* start) noexcept
		{
			top->connectYRow(this, start, 1);
			if (right != start)
				right->connectXRow(start);
		}
		void connectYRow(Chunk* startx, Chunk* start, unsigned int height) noexcept
		{
			if (start->right!=start)
			{
				Chunk* templeft = startx->left;
				Chunk* tempright = startx->right;
				for (unsigned int i = 0; i < height; i++)
				{
					templeft = templeft->top;
					tempright = tempright->top;
				}
				left = templeft;
				right = tempright;
				if (top != startx)
					top->connectYRow(startx, start, height + 1);
			}
			else
			{
				left = this;
				right = this;
				if (top != startx)
					top->connectYRow(startx, start, height + 1);
			}
		}
		void connectZRow(Chunk* startz, Chunk* startoverall) noexcept
		{
			connectXToZRow(startz, startz, 0);
			if (startz->front != startoverall)
				connectZRow(startz->front, startoverall);
		}
		void connectXToZRow(Chunk* startx, Chunk* startz, unsigned int xpos) noexcept
		{
			Chunk* tempfront = startz->front;
			Chunk* tempback = startz->back;
			for (unsigned int i = 0; i < xpos; i++)
			{
				tempfront = tempfront->right;
				tempback = tempback->right;
			}
			startx->front = tempfront;
			startx->back = tempback;

			if (startx->right != startz)
				connectXToZRow(startx->right, startz, xpos + 1);

			if (startx->top != startx)
				connectYToZRow(startx, startx->top, startz, xpos, 1);//ypos 1, because first row with 0 is already done

		}
		void connectYToZRow(Chunk* startx, Chunk* starty, Chunk* startz, unsigned int xpos, unsigned int ypos) noexcept
		{
			Chunk* tempfront = startz->front;
			Chunk* tempback = startz->back;
			for (unsigned int i = 0; i < xpos; i++)
			{
				tempfront = tempfront->right;
				tempback = tempback->right;
			}
			for (unsigned int i = 0; i < ypos; i++)
			{
				tempfront = tempfront->top;
				tempback = tempback->top;
			}
			starty->front = tempfront;
			starty->back = tempback;

			if (starty->top != startx)
				connectYToZRow(startx, starty->top, startz, xpos, ypos + 1);
		}

	public:


	};
	
private:
	unsigned int xcount, ycount, zcount;
	Pos chunksize;
	Chunk* start;

public:
	ChunkSystem(Pos& min, Pos& max, Pos& chunksize) noexcept
		: chunksize(chunksize)
	{
		xcount = clockwork::maths::ceil(( clockwork::maths::abs(min.x) + clockwork::maths::abs(max.x)) / chunksize.x);
		ycount = clockwork::maths::ceil(( clockwork::maths::abs(min.y) + clockwork::maths::abs(max.y)) / chunksize.y);
		zcount = clockwork::maths::ceil(( clockwork::maths::abs(min.z) + clockwork::maths::abs(max.z)) / chunksize.z);
		start = new Chunk(min, max, xcount, ycount, zcount, chunksize);
	}
	ChunkSystem(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, float sizeX, float sizeY, float sizeZ) noexcept
		: ChunkSystem(Pos(minX, minY, minZ), Pos(maxX, maxY, maxZ), Pos(sizeX, sizeY, sizeZ))
	{}
	ChunkSystem() noexcept
		: ChunkSystem(Pos(0, 0, 0), Pos(100000, 100000, 100000), Pos(10000, 10000, 10000))
	{}

public:
	inline Chunk* const getStart() const noexcept { return start; }
	unsigned long long getBytes() const noexcept
	{
		unsigned long long size{ 0 };
		Chunk* tempz = start;
		Chunk* tempx;
		Chunk* tempy;
		for (unsigned int z = 0; z < zcount; z++)
		{
			tempx = tempz;
			for (unsigned int x = 0; x < xcount; x++)
			{
				tempy = tempx;
				for (unsigned int y = 0; y < ycount; y++)
				{
					size += sizeof(tempy);
					tempy = tempy->top;
				}
				tempx = tempx->right;
			}
			tempz = tempz->front;
		}
		return size;
	}
	void sendToAll(void* (*fp)(Chunk* ch)) noexcept
	{
		Chunk* tempz = start;
		Chunk* tempx;
		Chunk* tempy;
		for (unsigned int z = 0; z < zcount; z++)
		{
			tempx = tempz;
			for (unsigned int x = 0; x < xcount; x++)
			{
				tempy = tempx;
				for (unsigned int y = 0; y < ycount; y++)
				{
					fp(tempy);
					tempy = tempy->top;
				}
				tempx = tempx->right;
			}
			tempz = tempz->front;
		}
	}
	friend void chunktest() noexcept;

};

static void chunktest() noexcept
{
	//ChunkSystem chunky(ChunkSystem::Pos(0.0f,0.0f,0.0f), ChunkSystem::Pos(5001.0f,5001.0f,5001.0f),1000);
	ChunkSystem chunk(0,0,0,10000,10000,10000,1000,1000,1000);
	std::cout << chunk.getBytes() << " Bytes \n";
	//in jedem chunk verschiedene linkedlisten für render, key, mouse, tick, etc machen und in jedem state ein chunksystem haben 
	//mainmenu hat dann z.b. nur ein chunksystem, aber dafür ein großes
}