#include "GameLib/Framework.h"
#include "Vector3.h"

#include <sstream>
using namespace std;


namespace GameLib {
	void Framework::update() {
		setFrameRate(60);
		
		Vector3 lightVector; //平行光源
		Vector3 lightColor; //太陽の光の色
		Vector3 diffuseColor; //三角形の色
		Vector3 ambientColor; //環境光の色
		Vector3 triangleVertex[3]; //三角形の頂点
		Vector3 color; //結果

		//三角形の法線ベクトルを求める
		Vector3 normal, a, b;
		a.setSub(triangleVertex[1], triangleVertex[0]);
		b.setSub(triangleVertex[2], triangleVertex[0]);
		normal.cross(&a, &b);
		//法線ベクトル正規化
		normal.normalize();
		//光源ベクトル正規化
		lightVector.normalize();

		//法線ベクトルと光源ベクトルの内積をとる
		double cos = lightVector.dot(normal);
		if (cos < 0) {
			cos = 0;
		}

		color.x = ambientColor.x + lightColor.x * diffuseColor.x * cos;
		color.y = ambientColor.y + lightColor.y * diffuseColor.y * cos;
		color.z = ambientColor.z + lightColor.z * diffuseColor.z * cos;


	}

}
