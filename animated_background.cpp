# SFML-Animated-Background-Player
A simple SFML C++ project that demonstrates frame-based animation for an animated background and a player sprite using multiple textures.

#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include<string>
using namespace std;
using namespace sf;

int main() {

	// Create the main window
	RenderWindow window(VideoMode(1000, 800), "SFML BackgroundFramers");
	//Add your code here...
	window.setFramerateLimit(60);
	//Load Background Texture
	vector<Texture> BackTexture(8);
	for (int i = 0; i < 8; i++) {
		if (!BackTexture[i].loadFromFile("Back/" + to_string(i + 1) + "bin.png")) {
			cout << "Erorr loding Background" << endl;
		}

		// Apply sooth filter
		BackTexture[i].setSmooth(true);

	}

	//Create Backgriund Sprite
	Sprite BackSprite(BackTexture[0]);
	//Scale Background to fit window
	BackSprite.setScale(
		float(window.getSize().x) / BackTexture[0].getSize().x,
		float(window.getSize().y) / BackTexture[0].getSize().y
	);

	//Animation variables
	float BackDuration = 0.09f;
	int Backcurrent = 0;
	Clock BackClock;

	// load Player Texture
	vector<Texture>PlayerTexture(20);
	for (int i = 0; i < 20; i++) {
		if (!PlayerTexture[i].loadFromFile("Sprite/" + to_string(i + 1) + "bac.png")) {
			cout << "Eroor loading texture" << i + 1 << endl;
		}
		// Apply smooth filter
		PlayerTexture[i].setSmooth(true);
	}

	// Create Player Sprite
	Sprite PlayerSprite(PlayerTexture[0]);
	PlayerSprite.setScale(0.8f, 0.8f);
	FloatRect BoundSprite = PlayerSprite.getLocalBounds();
	PlayerSprite.setOrigin(BoundSprite.width / 2, BoundSprite.height / 2);
	PlayerSprite.setPosition(540, 636);

	// Animation variables
	float FrameDuration = 0.12f;
	int Spritecurrent = 0;
	Clock SpriteClock;

	// Start the game loop
	while (window.isOpen()) {
		// Process event
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		//Update animations
		float Backelasped = BackClock.getElapsedTime().asSeconds();
		if (Backelasped >= BackDuration) {
			Backcurrent = (Backcurrent + 1) % BackTexture.size();
			BackSprite.setTexture(BackTexture[Backcurrent]);
			BackClock.restart();
		}

		//Update Player Sprite animation
		float elasped = SpriteClock.getElapsedTime().asSeconds();
		if (elasped >= FrameDuration) {
			Spritecurrent = (Spritecurrent + 1) % PlayerTexture.size();
			PlayerSprite.setTexture(PlayerTexture[Spritecurrent]);
			SpriteClock.restart();
		}

		// Clear screen and draw the sprites
		window.clear();
		window.draw(BackSprite);
		window.draw(PlayerSprite);
		window.display();


	}




	return 0;
}

