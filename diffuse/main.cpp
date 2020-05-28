#include "GameLib/Framework.h"
#include "Vector3.h"

#include <sstream>
using namespace std;


namespace GameLib {
	void Framework::update() {
		setFrameRate(60);
		
		Vector3 lightVector; //���s����
		Vector3 lightColor; //���z�̌��̐F
		Vector3 diffuseColor; //�O�p�`�̐F
		Vector3 ambientColor; //�����̐F
		Vector3 triangleVertex[3]; //�O�p�`�̒��_
		Vector3 color; //����

		//�O�p�`�̖@���x�N�g�������߂�
		Vector3 normal, a, b;
		a.setSub(triangleVertex[1], triangleVertex[0]);
		b.setSub(triangleVertex[2], triangleVertex[0]);
		normal.cross(&a, &b);
		//�@���x�N�g�����K��
		normal.normalize();
		//�����x�N�g�����K��
		lightVector.normalize();

		//�@���x�N�g���ƌ����x�N�g���̓��ς��Ƃ�
		double cos = lightVector.dot(normal);
		if (cos < 0) {
			cos = 0;
		}

		color.x = ambientColor.x + lightColor.x * diffuseColor.x * cos;
		color.y = ambientColor.y + lightColor.y * diffuseColor.y * cos;
		color.z = ambientColor.z + lightColor.z * diffuseColor.z * cos;


	}

}
