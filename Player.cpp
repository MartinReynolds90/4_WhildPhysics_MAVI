#include "Player.h"

Player::Player() {
	tx_player = new Texture;
	sp_player = new Sprite;
	tx_player->loadFromFile("mira.png");
	sp_player->setTexture(*tx_player);
	sp_player->setOrigin(32, 32);

}

Player::~Player() {
	delete tx_player;
	delete sp_player;
}

void Player::set_position(Vector2f pos_mouse) {
	sp_player->setPosition(pos_mouse);
}

Sprite Player::get_sprite() {
	return *sp_player;
}