#include "scene.h"

using namespace std;

int main() {
	Scene* my_scene = new Scene(0.0, 0.0, 0.0, -1.0, -1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	my_scene->render();
}