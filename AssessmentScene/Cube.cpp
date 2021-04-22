#include "Cube.h"
#include <iostream>
#include <fstream>
#include <string>

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	rotating = true;
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0.0f;
}

void Cube::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->Indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnable(GL_NORMAL_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);

		InitMaterial();
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
		glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);
		glPushMatrix();
			glTranslatef(_position.x, _position.y, _position.z);
			glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void Cube::InitMaterial()
{
	_material = new Material();
	_material->Ambient.x = 0.8; _material->Ambient.y = 0.05; _material->Ambient.z = 0.05;
	_material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.05; _material->Diffuse.z = 0.05;
	_material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0;
	_material->Specular.w = 1.0;
	_material->Shininess = 100.0f;
}

void Cube::Update()
{
	if (rotating)
	{
		if (_rotation >= 360.0f)
			_rotation = 0.04;

		_rotation += 0.1;
	}
}

void Cube::repositionCube(int value)
{
	if (value == 0)
		_position.x += 0.01;

	if (value == 1)
		_position.x -= 0.01;

	if (value == 2)
		_position.y += 0.01;

	if (value == 3)
		_position.y -= 0.01;
}

Cube::~Cube()
{

}