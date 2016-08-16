#include "Camera2D.h"

Camera2D::Camera2D() {

	transform.SetRotation(0, 180, 0);
	SetOrtho();
	aspectRatio.Set(32, 24);
	SetOrthoSize(12.5);
	SetNearClippingPlane(-100);
	SetFarClippingPlane(100);

	player = nullptr;
	tileMap = nullptr;

}

Camera2D::~Camera2D() {
}

void Camera2D::SetPlayer(Player& player) {

	this->player = &player;

}

void Camera2D::RemovePlayer() {

	this->player = nullptr;

}

void Camera2D::SetTileMap(TileMap& tileMap) {

	this->tileMap = &tileMap;

}

void Camera2D::RemoveTileMap() {

	tileMap = nullptr;

}

void Camera2D::Update(const double& deltaTime) {

	if (tileMap == nullptr || player == nullptr) {
		cout << "No Player Or TileMap Attached. Unable to update camera 2." << endl;
		return;
	}

	transform.position.x = player->transform.position.x;
	transform.position.y = player->transform.position.y;

	float xRatio = (static_cast<float>(aspectRatio.x) / static_cast<float>(aspectRatio.y));
	float camWidth = xRatio * orthoSize; //Half of our camera's view width

	//Border of our camera's view
	float rightBorder = transform.position.x + camWidth;
	if (rightBorder > tileMap->GetRightBorder()) {
		transform.position.x = tileMap->GetRightBorder() - camWidth;
	}
	//Border of our camera's view
	float leftBorder = transform.position.x - camWidth;
	if (leftBorder < tileMap->GetLeftBorder()) {
		transform.position.x = tileMap->GetLeftBorder() + camWidth;
	}

	//Border of our camera's view
	float topBorder = transform.position.y + orthoSize;
	if (topBorder > tileMap->GetTopBorder()) {
		transform.position.y = tileMap->GetTopBorder() - orthoSize;
	}
	//Border of our camera's view
	float bottomBorder = transform.position.y - orthoSize;
	if (bottomBorder < tileMap->GetBottomBorder()) {
		transform.position.y = tileMap->GetBottomBorder() + orthoSize;
	}

}