#pragma once

#ifndef VECTORS_H
#define VECTORS_H

namespace SemperGL
{

	typedef struct
	{
		float x, y;
	}Vec2f;	
	
	typedef struct
	{
		float x, y, z;
	}Vec3f;

	typedef struct
	{
		float x, y, z, w;
	}Vec4f;	

}

#endif // VECTORS_H