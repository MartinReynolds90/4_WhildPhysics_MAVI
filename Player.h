#include "SFML/Graphics.hpp"
using namespace sf;

class Player {

private:
	Sprite* sp_player;
	Texture* tx_player;
	Vector2f pos_mira;

public:
	Player();
	~Player();
	void set_position(Vector2f);
	Sprite get_sprite();
};

