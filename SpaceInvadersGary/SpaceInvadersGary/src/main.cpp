#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <string>
#include "Inputs.h"
#include "Alien.h"
#include "Ship.h"
#include "Bullet.h"
#include "Block.h"

using namespace std;

int main()
{
	//Setting up the sfml window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Space Invaders Clone", sf::Style::Default);
	window.setFramerateLimit(60);
	sf::Sound Sound;

	//Current menuing stage (0:Title Screen 1: Play Screen 2: Settings Screen)
	int MenuStage = 0;
	bool bResetted = true;

	//Vectors of menu objects so that it can be loaded in later at once
	sf::Text MenuText[4];
	sf::RectangleShape MenuButtons[3];

	//boolean values for muting the music and the sfx
	bool bMuteMusic = false;
	bool bMuteSFX = false;
	//when this turns on the user can rebind their controls to a different key
	bool bRebinding = false;

	//Player inputs for the ship (This can be changed through the Inputs class rebind function)
	Inputs ShipInputs;
	sf::Keyboard::Key Left = ShipInputs.getleft(); //The SFML keyboard key which is defaulted to the left key
	sf::Keyboard::Key Right = ShipInputs.getright(); //The SFML keyboard key which is defaulted to the Right key
	sf::Keyboard::Key Shoot = ShipInputs.getshoot(); //The SFML keyboard key which is defaulted to the Space key
	string saKeys[101] = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z",
		"Num0","Num1","Num2","Num3","Num4","Num5","Num6","Num7","Num8","Num9",
		"Escape","LControl","LShift","LAlt","LSystem","RControl","RShift","RAlt","RSystem","Menu",
		"LBracket","RBracket","SemiColon","Comma","Period","Quote","Slash","BackSlash",
		"Tilde","Equal","Dash","Space","Return","BackSpace","Tab","PageUp","PageDown",
		"End","Home","Insert","Delete","Add","Subtract","Multiply","Divide","Left","Right","Up","Down",
		"Numpad0","Numpad1","Numpad2","Numpad3","Numpad4","Numpad5","Numpad6","Numpad7","Numpad8","Numpad9",
		"F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12","F13","F14","F15",
		"Pause", };//I put all the sfml keycode enums in string form so that when the user rebinds their key it will show the string instead of enum value

	//Ship sprites and movement values
	PlayerShip Player;
	sf::Sprite PlrSprite = Player.DrawShip(0);
	float fMoveSpeed = Player.GetSpeed();
	float fxLeft = 0; //The speed of the ship going left if its 0 then its not moving if its -1 it will be moving
	float fxRight = 0; //Same as ixLeft but with ixRight where 0 not moving and 1 for moving

	//Bullets for aliens and the ship
	Bullet ShipBullet, AlienBullet;
	sf::Sprite BBullet;		sf::Sprite ABullet;

	//Drawing the ships lives left
	unsigned int uiLives = 3;
	bool bDead = false;
	float fDeathWait = 0;
	PlayerShip LivesOne, LivesTwo, LivesThree;
	sf::Sprite LOne = LivesOne.DrawShip(0); LOne.setPosition(0, 580); LOne.setScale(0.5f, 0.5f);
	sf::Sprite LTwo = LivesTwo.DrawShip(0); LTwo.setPosition(35, 580); LTwo.setScale(0.5f, 0.5f);
	sf::Sprite LThree = LivesThree.DrawShip(0); LThree.setPosition(70, 580); LThree.setScale(0.5f, 0.5f);
	sf::Sprite aLives[3] = { LOne,LTwo,LThree };

	//Creating the blocks for the ship to use as cover
	Block BlockOne, BlockTwo, BlockThree, BlockFour;
	Block aBlocks[4] = { BlockOne,BlockTwo,BlockThree,BlockFour };
	unsigned int uiStateOne = 0; sf::Sprite BOne = BlockOne.DrawBlock(uiStateOne); BOne.setPosition(250, 475);
	unsigned int uiStateTwo = 0; sf::Sprite BTwo = BlockOne.DrawBlock(uiStateTwo); BTwo.setPosition(350, 475);
	unsigned int uiStateThree = 0; sf::Sprite BThree = BlockOne.DrawBlock(uiStateThree); BThree.setPosition(450, 475);
	unsigned int uiStateFour = 0; sf::Sprite BFour = BlockOne.DrawBlock(uiStateFour); BFour.setPosition(550, 475);
	sf::Sprite aBlocksSpr[4] = { BOne,BTwo,BThree,BFour }; unsigned int uiaStates[4] = { uiStateOne,uiStateTwo,uiStateThree,uiStateFour };

	//Setting up the aliens to be used later
	Alien Aliens;
	Aliens.StoreAliens();
	int aiAlienAlive[3][10] = //1 is where the alien is alive and the sprite will still be there
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
	};
	int iAlienMSDiv = 31; //This number slows the aliens movement but speeds up as there are less aliens on screen
	bool bDirection = false;//false goes right, true goes left for the aliens moving side to side
	bool bAliensKilled = false;
	int iAnimState = 0;//<24 it will show the first sprite >24 it will show the second sprite

	//Setting up the sounds for aliens and the ship
	//Ship sounds
	sf::SoundBuffer ShipShoot, ShipHit;
	sf::Sound SBulletSound, ShipHitSound;
	if (ShipShoot.loadFromFile(".\\assets\\sounds\\ShipBullet.wav")) SBulletSound.setBuffer(ShipShoot);;
	if (ShipHit.loadFromFile(".\\assets\\sounds\\ShipHit.wav")) ShipHitSound.setBuffer(ShipHit);

	//Alien sounds
	sf::SoundBuffer AlienShoot, AlienHit;
	sf::Sound ABulletSound, AlienHitSound;
	if (AlienHit.loadFromFile(".\\assets\\sounds\\InvaderHit.wav")) ABulletSound.setBuffer(AlienShoot);
	if (AlienShoot.loadFromFile(".\\assets\\sounds\\InvaderBullet.wav")) AlienHitSound.setBuffer(AlienHit);

	//Setting up the game music
	sf::Music TitleMusic, InvaderHome;
	if (TitleMusic.openFromFile(".\\assets\\sounds\\01_Title Screen.wav"));
	if (InvaderHome.openFromFile(".\\assets\\sounds\\12_Invader Homeworld.wav"));

	//Fonts
	sf::Font UniFont;
	if (!UniFont.loadFromFile(".\\assets\\fonts\\unifont.ttf")) return 0;

	//A text telling the player to press escape to go back to the title screen when the player is in a game
	sf::Text ExitText;
	ExitText.setFont(UniFont);
	ExitText.setCharacterSize(16);
	ExitText.setString("Esc to quit to menu");
	ExitText.setFillColor(sf::Color::White);

	//Setting up menu buttons
	//Text for the buttons to show the user what each button does
	sf::Text PlayGame;							sf::Text Settings;							sf::Text Exit;							sf::Text Title;
	PlayGame.setFont(UniFont);					Settings.setFont(UniFont);					Exit.setFont(UniFont);					Title.setFont(UniFont);
	PlayGame.setString("Start");				Settings.setString("Settings");				Exit.setString("Quit");					Title.setString("Alien Invaders");
	PlayGame.setCharacterSize(32);				Settings.setCharacterSize(32);				Exit.setCharacterSize(32);				Title.setCharacterSize(64);
	PlayGame.setFillColor(sf::Color::White);	Settings.setFillColor(sf::Color::White);	Exit.setFillColor(sf::Color::White);	Title.setFillColor(sf::Color::White);
	PlayGame.setPosition(400, 300);				Settings.setPosition(375, 400);				Exit.setPosition(405, 500);				Title.setPosition(215, 100);
	PlayGame.setOrigin(32, 32);					Settings.setOrigin(32, 32);					Exit.setOrigin(32, 32);					Title.setOrigin(32, 32);
	MenuText[0] = PlayGame;						MenuText[1] = Settings;						MenuText[2] = Exit;						MenuText[3] = Title;

	//Creating the text boxes where the texts itself will be inside to create a button for the user to click on
	sf::RectangleShape StartBox;							sf::RectangleShape SettingsBox;								sf::RectangleShape QuitBox;
	StartBox.setSize(sf::Vector2f(200, 50));				SettingsBox.setSize(sf::Vector2f(200, 50));					QuitBox.setSize(sf::Vector2f(200, 50));
	StartBox.setPosition(310, 265);							SettingsBox.setPosition(310, 365);							QuitBox.setPosition(310, 465);
	StartBox.setFillColor(sf::Color::Black);				SettingsBox.setFillColor(sf::Color::Black);					QuitBox.setFillColor(sf::Color::Black);
	StartBox.setOutlineColor(sf::Color::White);				SettingsBox.setOutlineColor(sf::Color::White);				QuitBox.setOutlineColor(sf::Color::White);
	StartBox.setOutlineThickness(1);						SettingsBox.setOutlineThickness(1);							QuitBox.setOutlineThickness(1);
	sf::FloatRect PBounds = StartBox.getGlobalBounds();		sf::FloatRect SBounds = SettingsBox.getGlobalBounds();		sf::FloatRect QBounds = QuitBox.getGlobalBounds();
	MenuButtons[0] = StartBox;								MenuButtons[1] = SettingsBox;								MenuButtons[2] = QuitBox;

	//Creating the settings text for the settings buttons and the back button
	sf::Text MuteMusic;										sf::Text MuteSFX;											sf::Text Back;
	MuteMusic.setFont(UniFont);								MuteSFX.setFont(UniFont);									Back.setFont(UniFont);
	MuteMusic.setString("Music: On");						MuteSFX.setString("SFX: On");								Back.setString("Back");
	MuteMusic.setCharacterSize(32);							MuteSFX.setCharacterSize(32);								Back.setCharacterSize(32);
	MuteMusic.setFillColor(sf::Color::White);				MuteSFX.setFillColor(sf::Color::White);						Back.setFillColor(sf::Color::White);
	MuteMusic.setPosition(150, 100);						MuteSFX.setPosition(150, 150);								Back.setPosition(380, 525);
	sf::FloatRect MMBounds = MuteMusic.getGlobalBounds();	sf::FloatRect MSFXBounds = MuteSFX.getGlobalBounds();		sf::FloatRect BackBounds = Back.getGlobalBounds();

	//Creating the settings text for the key rebinds
	sf::Text LeftText;										sf::Text RightText;										sf::Text ShootText;
	LeftText.setFont(UniFont);								RightText.setFont(UniFont);								ShootText.setFont(UniFont);
	LeftText.setString("Left: Left");						RightText.setString("Right: Right");					ShootText.setString("Shoot: Space");
	LeftText.setCharacterSize(32);							RightText.setCharacterSize(32);							ShootText.setCharacterSize(32);
	LeftText.setFillColor(sf::Color::White);				RightText.setFillColor(sf::Color::White);				ShootText.setFillColor(sf::Color::White);
	LeftText.setPosition(500, 100);							RightText.setPosition(500, 150);						ShootText.setPosition(500, 200);
	sf::FloatRect LButBounds = LeftText.getGlobalBounds();	sf::FloatRect RButBounds = RightText.getGlobalBounds();	sf::FloatRect SBBounds = ShootText.getGlobalBounds();

	//Black rectangle shape that the user shouldn't see used to interact with the menu buttons
	sf::RectangleShape MouseDot;
	MouseDot.setSize(sf::Vector2f(1, 1));
	MouseDot.setFillColor(sf::Color::Black);

	//Win or game over text
	sf::Text Win;
	Win.setFont(UniFont);
	Win.setString("Winner! Press esc to quit");
	Win.setCharacterSize(30);
	Win.setFillColor(sf::Color::White);
	Win.setPosition(250, 100);
	Win.setOrigin(32, 32);

	//Invisible walls that aliens collide so it moves down and change direction
	sf::RectangleShape RightWall;								sf::RectangleShape LeftWall;
	RightWall.setSize(sf::Vector2f(10, 600));					LeftWall.setSize(sf::Vector2f(10, 600));
	RightWall.setFillColor(sf::Color::Black);					LeftWall.setFillColor(sf::Color::Black);
	RightWall.setPosition(700, 0);								LeftWall.setPosition(90, 0);
	sf::FloatRect RWallBounds = RightWall.getGlobalBounds();	sf::FloatRect LWallBounds = LeftWall.getGlobalBounds();

	//Invisible line that when the aliens touch it the player will lose
	sf::RectangleShape LoseBar;
	LoseBar.setSize(sf::Vector2f(800, 10));
	LoseBar.setFillColor(sf::Color::Black);
	LoseBar.setPosition(0, 450);
	sf::FloatRect LBBounds = LoseBar.getGlobalBounds();

	//A while loop that keeps the sfml window open
	while (window.isOpen())
	{
		//Playing music depending which part of the game it is
		if (!bMuteMusic)
		{
			switch (MenuStage)
			{
			case 0:
				if (TitleMusic.getStatus() != sf::Music::Playing)//Checks if the title music is already playing so it doesn't overlap the music and cause lag
				{
					TitleMusic.play();
					InvaderHome.stop();
				}
				break;
			case 1:
				if (InvaderHome.getStatus() != sf::Music::Playing)//Checks if the game music is already playing so it doesn't overlap the music and cause lag
				{
					InvaderHome.play();
					TitleMusic.stop();
				}
				break;
			case 2:
				if (TitleMusic.getStatus() != sf::Music::Playing)//Checks if the title music is already playing so it doesn't overlap the music and cause lag
				{
					TitleMusic.play();
					InvaderHome.stop();
				}
				break;
			}
		}
		else if ((TitleMusic.getStatus() == sf::Music::Playing || InvaderHome.getStatus() == sf::Music::Playing) && bMuteMusic)//if the game is muted it will stop playing the music
		{
			TitleMusic.stop();
			InvaderHome.stop();
		}

		//The in game pointer is set to the position of the user's cursor so that the user can click on the buttons
		sf::FloatRect MouseDotBounds = MouseDot.getGlobalBounds();
		MouseDot.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
		sf::Clock Timer; //Timer is used to keep track of the alien sprites animation
		sf::Clock DeathTimer; //Pause period whenever the player dies so theres no shooting going on by the aliens
		srand(time(NULL)); //This is used to setup the random number generator so the alien shoots at random intervals

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)//Closes the sfml window when the user clicks the X button on the top right
			{
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed && MenuStage == 0)//Checks if the user clicked a mouse button
			{
				if (event.mouseButton.button == sf::Mouse::Left && QBounds.intersects(MouseDotBounds))//If the user clicks the quit button it closes the window
				{
					window.close();
				}
				else if (event.mouseButton.button == sf::Mouse::Left && PBounds.intersects(MouseDotBounds))//If the user clicks the play button it will start the game
				{
					MenuStage = 1;
				}
				else if (event.mouseButton.button == sf::Mouse::Left && SBounds.intersects(MouseDotBounds))//If the user clicks the play button it will start the game
				{
					MenuStage = 2;
				}
			}
			if (event.type == sf::Event::KeyPressed && MenuStage == 1)
			{
				if (event.key.code == Left) fxLeft = -1; //Sets it to -1 since it is used in the sfml move method to move the ship to the left
				else if (event.key.code == Right) fxRight = 1;//same as the condition above but to go right instead
				if (event.key.code == sf::Keyboard::Escape) { MenuStage = 0; bResetted = true; }
				if (event.key.code == Shoot && BBullet.getPosition().y < 0 && !bDead)//player can shoot a bullet if the ship is not dead and the bullet is offscreen
				{
					cout << saKeys[Shoot] << endl;
					BBullet = ShipBullet.ShootBullet(PlrSprite.getPosition().x + 27, PlrSprite.getPosition().y - 20);//shoots at the centre of the ship on its tip
					if (!bMuteSFX) SBulletSound.play();
				}
			}
			if (event.type == sf::Event::KeyReleased && MenuStage == 1)
			{
				if (event.key.code == Left) fxLeft = 0, cout << saKeys[Left] << endl; //Makes the fxLeft 0 which makes the ship stop moving left
				else if (event.key.code == Right) fxRight = 0, cout << saKeys[Right] << endl;//does the same as fxleft but makes the ship stop moving right
			}
			if (event.type == sf::Event::MouseButtonPressed && MenuStage == 2)
			{
				if (event.mouseButton.button == sf::Mouse::Left && BackBounds.intersects(MouseDotBounds) && bRebinding == false)//The user can only go back to the title screen if the they are not rebinding their controls
				{
					MenuStage = 0;
				}
				else if (event.mouseButton.button == sf::Mouse::Left && MMBounds.intersects(MouseDotBounds))//If the user clicked the mute music button it will either turn the music on or off depending on the previous setting
				{
					bMuteMusic = (bMuteMusic == false) ? bMuteMusic = true : bMuteMusic = false;
					MuteMusic.setString((bMuteMusic == false) ? "Music: On" : "Music: Off");
				}
				else if (event.mouseButton.button == sf::Mouse::Left && MSFXBounds.intersects(MouseDotBounds))//Does the same as mute music but to mute the sfx instead
				{
					bMuteSFX = (bMuteSFX == false) ? bMuteSFX = true : bMuteSFX = false;
					MuteSFX.setString((bMuteSFX == false) ? "SFX: On" : "SFX: Off");
				}
				else if (event.mouseButton.button == sf::Mouse::Left && LButBounds.intersects(MouseDotBounds) && bRebinding == false)//This enables the user to rebind their key for the left movement button
				{
					bRebinding = true;
					LeftText.setString("Left: Input Key");//Changes the string to "Left: Input Key" to let the user know they can rebind their key
				}
				else if (event.mouseButton.button == sf::Mouse::Left && RButBounds.intersects(MouseDotBounds) && bRebinding == false)//This enables the user to rebind their key for the right movement button
				{
					bRebinding = true;
					RightText.setString("Right: Input Key");//Changes the string to "Right: Input Key" to let the user know they can rebind their key
				}
				else if (event.mouseButton.button == sf::Mouse::Left && SBBounds.intersects(MouseDotBounds) && bRebinding == false)//This enables the user to rebind their key for the shoot button
				{
					bRebinding = true;
					ShootText.setString("Shoot: Input Key");//Changes the string to "Shoot: Input Key" to let the user know they can rebind their key
				}
			}
			if (event.type == sf::Event::KeyPressed && MenuStage == 2 && bRebinding == true)//This is the main rebind block of code
			{
				for (int i = sf::Keyboard::Key::A; i <= sf::Keyboard::Pause; i++)//iterates through every enumeration value inside sfml keyboard keys
				{
					if (event.key.code == i)//If it matches the one user pressed it will start rebinding
					{
						if (LeftText.getString() == "Left: Input Key" && i != Shoot && i != Right)//It will rebind to a new key only if the shoot key and the right key are not occupied
						{
							bRebinding = false;
							Left = ShipInputs.rebind("Left", sf::Keyboard::Key(i));//Calls the object method to rebind the key for the left button
							LeftText.setString("Left: " + saKeys[ShipInputs.getleft()]);//Changes the text to the corresponding key
						}
						else if (RightText.getString() == "Right: Input Key" && i != Shoot && i != Left)//It will rebind to a new key only if the shoot key and the left key are not occupied
						{
							bRebinding = false;
							Right = ShipInputs.rebind("Right", sf::Keyboard::Key(i));//Calls the object method to rebind the key for the right button
							RightText.setString("Right: " + saKeys[ShipInputs.getright()]);//Changes the text to the corresponding key
						}
						else if (ShootText.getString() == "Shoot: Input Key" && i != Left && i != Right)//It will rebind to a new key only if the left key and the right key are not occupied
						{
							bRebinding = false;
							Shoot = ShipInputs.rebind("Shoot", sf::Keyboard::Key(i));//Calls the object method to rebind the key for the shoot button
							ShootText.setString("Shoot: " + saKeys[ShipInputs.getshoot()]);//Changes the text to the corresponding key
						}//bRebinding is set to false so that the user can rebind their keys again
					}
				}
			}
		}
		//Increments the IAnimState variable by 1 every 1/24 seconds which swaps the aliens sprites every second
		sf::Time elapsedTime = Timer.getElapsedTime();
		sf::Time eDeathTime = DeathTimer.getElapsedTime();
		if (elapsedTime.asSeconds() > 1 / 24)
		{
			Timer.restart();
			if (iAnimState < 48)
			{
				iAnimState++;
			}
			else
			{
				iAnimState = 0;
			}
		}

		//Sprite wrapping so that the ship cannot go offscreen which is the screens resolution
		if (PlrSprite.getPosition().x < -60)
		{
			PlrSprite.setPosition(740, 550);
		}
		else if (PlrSprite.getPosition().x > 800)
		{
			PlrSprite.setPosition(0, 550);
		}

		/*This is a switch to change the display to different parts of the game between the title screen, the game screen and the settings screen
		  The for loops inside draws all the things that are part of the section of the game*/
		switch (MenuStage)
		{
		case 0://The code for creating the menu
			for (sf::RectangleShape& MTextBox : MenuButtons)
			{
				window.draw(MTextBox);
			}
			for (sf::Text& MTexts : MenuText)
			{
				window.draw(MTexts);
			}
			break;
		case 1://The code for creating the main game with the aliens and ship
			if (bResetted)//This resets everything back to how it started when the plays clicks the play button
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 10; j++)//resets the positions of the aliens and makes them alive again
					{
						aiAlienAlive[i][j] = 1;
						Aliens.ResetPositions(i, j);
					}
				}
				for (int i = 0; i < 4; i++)
				{
					uiaStates[i] = 0;
					aBlocksSpr[i] = aBlocks[i].DrawBlock(0);//reset the state of the blocks
					aBlocksSpr[i].setPosition(250 + (i * 100), 475);//reset their positions
				}
				PlrSprite.setPosition(375, 550);//reset player position
				uiLives = 3;//lives are back to 3
				BBullet.setPosition(0, -10);//this is at the top of the screen so that the player can fire the bullet right away
				ABullet.setPosition(0, 600);//this is at the bottom of the screen so the aliens can fire right away
				bDead = false;
				iAlienMSDiv = 31;
				Win.setString("Winner! Press esc to quit");
				bResetted = false;
			}
			if (bDead && fDeathWait > 1000)//This makes the player press a button to continue playing
			{
				bDead = false; //sets it to false so that the player ship appears again
				uiLives--; //remove one life
				PlrSprite.setPosition(375, 550);//reset position to normal
				BBullet.setPosition(0, -10);//reset bullet position
				DeathTimer.restart();//restart death timer to 0
				fDeathWait = 0;//reset the total timer
				for (int i = 0; i < 3; i++)//resets the positions of the aliens
				{
					for (int j = 0; j < 10; j++)
					{
						Aliens.ResetPositions(i, j);
					}
				}
			}
			else if (bDead)
			{
				fDeathWait += eDeathTime.asMicroseconds();
			}
			if (uiLives == 0)
			{
				Win.setPosition(230, 100);
				Win.setString("Game Over, press esc to quit");
			}
			bAliensKilled = true;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					//Moving the alien sprites left right and down
					if (bDirection) { Aliens.MoveAlien(-0.5 / iAlienMSDiv, 0); }
					else { Aliens.MoveAlien(0.5 / iAlienMSDiv, 0); }
					//Draws all the aliens alive and stops drawing if it is dead or the player has 0 lives left
					if (iAnimState <= 24 && aiAlienAlive[i][j] == 1 && uiLives != 0)
					{
						window.draw(Aliens.DrawAlien(i, j, 1));
						bAliensKilled = false;
					}
					//This part is for the second set of sprites for alien sprite animation, does the same thing as the condition above but for different sprites
					else if (iAnimState > 24 && aiAlienAlive[i][j] == 1 && uiLives != 0)
					{
						window.draw(Aliens.DrawAlien(i, j, 2));
						bAliensKilled = false;
					}
					//This is collision detection between the player bullet and the alien, if the bullet hits an alien it will kill it by setting tha aiAlienAlive to 0 and won't display the sprite on screen
					if (Aliens.GetHitBox(i, j).intersects(BBullet.getGlobalBounds()) && aiAlienAlive[i][j] == 1)
					{
						aiAlienAlive[i][j] = 0;
						BBullet.setPosition(0, -20);
						if (!bMuteSFX) AlienHitSound.play();
						iAlienMSDiv--;
					}
					else if (ABullet.getGlobalBounds().intersects(PlrSprite.getGlobalBounds()))//Collision detection for the player ship if the player collides with the alien, bullet killing it
					{
						bDead = true;
						ABullet.setPosition(0, 620);
						if (!bMuteSFX) ShipHitSound.play();
					}
					else if (Aliens.GetHitBox(i, j).intersects(RWallBounds) && aiAlienAlive[i][j] == 1)//Collision of the alien with the wall to go down once and then switch direction
					{
						Aliens.MoveAlien(0, 10);//The aliens move down by 10
						bDirection = true;//Aliens move left now
					}
					else if (Aliens.GetHitBox(i, j).intersects(LWallBounds) && aiAlienAlive[i][j] == 1)
					{
						Aliens.MoveAlien(0, 10);//Aliens move down by 10
						bDirection = false;//Aliens move right now
					}
					else if (Aliens.GetHitBox(i, j).intersects(LBBounds) && aiAlienAlive[i][j] == 1)//Collision when the alien touches the ship lose bounds
					{
						bDead = true;//The player automatically loses a life
						for (int i = 0; i < 3; i++)//Alien positions are reset but the dead aliens stay dead
						{
							for (int j = 0; j < 10; j++)
							{
								Aliens.ResetPositions(i, j);
							}
						}
					}
					for (int x = 0; x < 4; x++)
					{
						if (uiaStates[x] < 3 && ABullet.getGlobalBounds().intersects(aBlocksSpr[x].getGlobalBounds()))//collision detection for the blocks with alien bullet
						{
							ABullet.setPosition(0, 600);//changes alien bullet position to offscreen
							uiaStates[x]++;//increments the blocks state to indicate it has been damaged
							aBlocksSpr[x] = aBlocks[x].DrawBlock(uiaStates[x]);//updates the block sprite
							aBlocksSpr[x].setPosition(250 + (x * 100), 475);//resets the position
						}
						else if (uiaStates[x] < 3 && BBullet.getGlobalBounds().intersects(aBlocksSpr[x].getGlobalBounds()))//collision detection for the blocks with ship bullet
						{
							BBullet.setPosition(0, -20);//changes the ship bullet positon to above the screen
							uiaStates[x]++;//increments the blocks state to indicate it has been damaged
							aBlocksSpr[x] = aBlocks[x].DrawBlock(uiaStates[x]);//updates the block sprite
							aBlocksSpr[x].setPosition(250 + (x * 100), 475);//resets the position
						}
					}
					if (ABullet.getPosition().y > 600 && !bDead)//Alien has a chance to fire when the bullet goes offscreen and the player is still alive
					{
						if (aiAlienAlive[2][j] == 1 && rand() % 40 + 1 == 10)//Each alien from every row going from bottom to top has a 1/40 chance to shoot every frame
						{
							ABullet = AlienBullet.ShootBullet(Aliens.GetSprite(2, j).getPosition().x + 20, Aliens.GetSprite(2, j).getPosition().y + 30);
							if (!bMuteSFX) ABulletSound.play();
						}
						else if (aiAlienAlive[1][j] == 1 && rand() % 40 + 1 == 10 && aiAlienAlive[2][j] == 0)//The last condition checks if the aliens below itself are dead if so it can shoot
						{
							ABullet = AlienBullet.ShootBullet(Aliens.GetSprite(1, j).getPosition().x + 20, Aliens.GetSprite(1, j).getPosition().y + 30);
							if (!bMuteSFX) ABulletSound.play();
						}
						else if (aiAlienAlive[0][j] == 1 && rand() % 40 + 1 == 10 && aiAlienAlive[1][j] == 0)//The last condition checks if the aliens below itself are dead if so it can shoot
						{
							ABullet = AlienBullet.ShootBullet(Aliens.GetSprite(0, j).getPosition().x + 20, Aliens.GetSprite(0, j).getPosition().y + 30);
							if (!bMuteSFX) ABulletSound.play();
						}
					}
				}
			}
			if (bAliensKilled || uiLives == 0)//Draws the text if the user lost all lives or all the aliens have been killed
			{
				window.draw(Win);//for 0 lives the string has been changed to a game over earlier in the code and is displayed otherwise it will display the win text which is its default value
				window.draw(ExitText);
			}
			else
			{
				if (!bDead) { window.draw(PlrSprite); }//Draws the ship if the ship didn't get hit by an alien bullet yet
				//Draws everything that the game screen needs
				window.draw(BBullet);
				window.draw(ABullet);
				PlrSprite.move((fxLeft + fxRight) * fMoveSpeed, 0);
				BBullet.move(0, -10);
				ABullet.move(0, 5);
				PlrSprite.getGlobalBounds();
				for (int i = 0; i < uiLives; i++)
				{
					window.draw(aLives[i]);
				}
				for (int i = 0; i < 4; i++)//Only draws the blocks if it is a fullblock, okblock or a weakblock
				{
					if (uiaStates[i] < 3)
					{
						window.draw(aBlocksSpr[i]);
					}
				}
				window.draw(ExitText);
			}
			break;
		case 2://Code for the settings screen
			window.draw(MuteMusic);//Draws everything that the setting screen needs
			window.draw(MuteSFX);
			window.draw(LeftText);
			window.draw(RightText);
			window.draw(ShootText);
			window.draw(Back);
			break;
		}
		window.display();
		window.clear();
	}
	return 0;
}