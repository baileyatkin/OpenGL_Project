#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct face
{
	unsigned int v1, v2, v3;
};

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Vector4
{
	float x, y, z, w;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

struct TexCoord
{
	GLfloat u, v;
};

struct Mesh
{
	Vertex* Vertices;
	Vector3* Normals;
	TexCoord* TexCoords;
	GLushort* Indices;
	int VertexCount, NormalCount, IndexCount, TexCoordsCount;
};

struct NoTexMesh
{
	Vertex* Vertices;
	Color* Colours;
	GLushort* Indices;
	int VertexCount, ColorCount, IndexCount;

};

struct Lighting
{
	Vector4 Ambient, Diffuse, Specular;
};

struct Material
{
	Vector4 Ambient, Diffuse, Specular;
	GLfloat Shininess;
};

enum MENU_TABS
{
	MENU_0,
	MENU_1,
	MENU_2,
	MENU_3,
};