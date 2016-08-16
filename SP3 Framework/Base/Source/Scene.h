#ifndef SCENE_H
#define SCENE_H

class Scene {

public:
	//Virtual Function(s)
	virtual void Init() = 0;
	virtual void Update(const double& dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

	//Constructor(s) & Destructor
	Scene() {}
	virtual ~Scene() {}

};

#endif