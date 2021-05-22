#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include <cstdlib> 
#include<fstream>
#include <sstream>
#include <ctime>
#include<string>
#include<vector>


using namespace std;
using namespace sf;

int twoplayers_bothloseindex = -5, twoplayers_pauseindex = -7, twoplayers_gameoverindex = -4, twoplayersindex = -3, gameoverindex = -2
, namescreenindex = -1, gameindex = 0, instructionindex = 1, profileindex = 2, highscoresindex = 3,
soundoptionsindex = 4, creditsindex = 5, exitindex = 6, pauseindex = 7, modemenuindex = 8, mainmenuindex = 10;

Font font;

//game Functions
void main_menu();
void instructions_menu();
void profile_options();
void outleaderboard();
void re_sort_score();
void topfive_set();
struct player {
	string name;
	int score;
} liveplayer;
bool scorecompare(player player1, player player2);
void sound_options();
void game_reset();

void twoplayers_mode_set();
void twoplayers_mode();
void twoplayers_pausemenu();
void character_pick();


bool r = false, colliderre = false, colliderre1 = false;
int highjcounter = 0;
//Start menu variables
int mouse_pos = 0;
int selectedItemIndex = 0, selecteditemorder = 10;
const int MENU_ITEMS = 7;
Text menu[MENU_ITEMS];
Sprite menubackg, cursor[11];
Event tostart;
Texture curs;

//instruction variables
string instruct_names[4] = { "instructions1.jpg","instructions2.jpg","instructions3.jpg" ,"instructions4.jpg" };
Texture instruct[4];
Sprite instructions[4];
int shown_instruct = 0;

//Profile variables
Texture trump_icon, icy_icon, dancer_icon;
Text inprofile_menu[2];
Sprite character[3];
int UD = 0, RL = 0;
int picked_char = 0;

//High score variables
// Files
string rest;
int resu;
int players_number = 0;
ofstream scoreboardout("Dashboard.txt", ios::app);
ifstream scoreboardin("Dashboard.txt");
//High scores menu
Text topfive[6][2];
ostringstream billboardconvertor;
vector<player>billboard;


//sound options variables
Sprite sound_level[12], music_level[12];
Text inSound_menu[3];
Sound sound, music;
int  musicpointer = 5, soundpointer = 5, soundmenuindex = 0;
Sound loswav;
Sound hoob;
Sound insid;
Sound alarm;

//mode selection variables
// 2 player name screen variables
Text entered_name;
Text modes[3];
Text character_choose;
string player1_name, player2_name;
RectangleShape pointer(Vector2f(80, 90));
CircleShape pointing(15);
Sprite characters[3];
int screennumber = 0;
int selectedplayersIndex = 0;
int player1_character, player2_character;

// 1 player name screen variables
Sprite namescreen;
long long livescore = 0;
string livename;
Text name_enter;
//Text entered_name;

//Pause Menu Select variables
const int PAUSED_ITEMS = 2;
Text pausetext[PAUSED_ITEMS];
int selectedPauseIndex = 0;
Sprite pause;

// *********************************************
//Game Main variable
// 1 player mode
Texture  trumpcharacter0, icycharacter0, dancercharacter0;
RectangleShape collider(Vector2f(9, 10));
Sprite icy[3];
Clock highjclock;
Vector2u clocksize;
IntRect clockanim;
Clock watch, scrollspeedclock;
Clock stopwatchclock;
Sprite stopwatch;

//Hurry UP
Texture hurry;
Sprite hurryT;

Clock hurryclock;
bool isHurry = false;

//Backgrounds
Texture back1, back2;
Sprite backg11, backg12, backg21, backg22;

//blocks
int blocksno = 0, blockcounter = 1, color_number = 0;
int hor, ver = 540;
int blockvalue[8];
int b_scale;
float arr[6] = { 0.5,0.6,0.7,0.8,0.9,1 };
string b_colors[5] = { "level 1.png","level 2.png" ,"level 3.png" ,"level 4.png" ,"level 5.png" };
string  levelsg_colors[5] = { "glevel 1.png","glevel 2.png" ,"glevel 3.png" ,"glevel 4.png" ,"glevel 5.png" };
Texture blockshape[5];
Texture levelsg[5];
Texture startg;
Sprite ground_b;
Sprite b_drawer[10];

//scrolling


//jump
Vector2f vi;
float g = 0;
int j = 0;
bool highj = false;

// 2 players mode variables
Sprite twoplayers_icy[3];
RectangleShape twoplayers_collider[3];
RectangleShape twoplayers_fightcollider[3];
Vector2f vi0[3];
bool twolastpc[3], twolastpc2[3];
float twodist[3];
float twolastp[3];
int jumpinghandler[3] = { 0 };
float gravity[3] = { 0 };
Clock highjclock2[3];

Text winner;
Text loser;
Texture winnerT;
Sprite winnerS;

Texture twoplayersloseT;
Sprite twoplayersloseS;


void main_menu() {
	//Keyboard Event
	/* Move Up */
	if (tostart.type == Event::KeyReleased) {
		if (tostart.key.code == Keyboard::Up) {
			if (selectedItemIndex - 1 >= 0) {
				menu[selectedItemIndex].setFillColor(Color::Black);
				cursor[mainmenuindex].move(0, -49);
				selectedItemIndex--;
				menu[selectedItemIndex].setFillColor(Color::Red);
			}
		}
		/* Move Down */
		if (tostart.key.code == Keyboard::Down) {
			if (selectedItemIndex + 1 < MENU_ITEMS) {
				menu[selectedItemIndex].setFillColor(Color::Black);
				cursor[mainmenuindex].move(0, 49);
				selectedItemIndex++;
				menu[selectedItemIndex].setFillColor(Color::Red);
			}
		}
	}
	//Mouse Event 
	if (tostart.type == Event::MouseMoved)
	{
		if (tostart.mouseMove.x >= 476 && tostart.mouseMove.x <= 760) {
			if (tostart.mouseMove.y >= 235 && tostart.mouseMove.y <= 600) {
				mouse_pos = (tostart.mouseMove.y - 235) / 50;
				selectedItemIndex = mouse_pos;
				for (int i = 0; i < MENU_ITEMS; i++)
					menu[i].setFillColor(Color::Black);

				menu[selectedItemIndex].setFillColor(Color::Red);
				cursor[mainmenuindex].setPosition(420, 235 + mouse_pos * 49);
			}
		}
	}
	if (tostart.type == Event::KeyPressed) {
		if (tostart.key.code == Keyboard::Space || tostart.key.code == Keyboard::Enter ||
			(tostart.type == Event::MouseButtonPressed && tostart.mouseButton.button == Mouse::Left)
			) {
			switch (selectedItemIndex) {
			case 0: selecteditemorder = modemenuindex;  screennumber = 0;       break;
			case 1: selecteditemorder = instructionindex;        break;
			case 2: selecteditemorder = profileindex;            break;
			case 3: selecteditemorder = highscoresindex;         break;
			case 4: selecteditemorder = soundoptionsindex;       break;
			case 5: selecteditemorder = creditsindex;            break;
			case 6: selecteditemorder = exitindex;               break;
			}
		}
	}
}


//Instructions
void instructions_menu() {
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		if (shown_instruct < 3)shown_instruct++;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left)) {
		if (shown_instruct > 0)shown_instruct--;
	}
}

//Profiles
//int UD , RL ;
void profile_options() {
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		UD = 1;
		cursor[profileindex].setPosition(430, 400);
		inprofile_menu[1].setFillColor(Color::Red);
		inprofile_menu[0].setFillColor(Color::Black);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up)) {
		UD = 0;
		cursor[profileindex].setPosition(430, 250);
		inprofile_menu[0].setFillColor(Color::Red);
		inprofile_menu[1].setFillColor(Color::Black);
	}
	if (UD == 0) {
		if (tostart.type == Event::KeyPressed) {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				if (RL < 2)
					RL++;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left)) {
				if (RL > 0)
					RL--;
			}
			if (tostart.key.code == Keyboard::Enter || tostart.key.code == Keyboard::Space) {
				switch (RL)
				{
				case 0:picked_char = 0; selecteditemorder = mainmenuindex;  break;
				case 1:picked_char = 1; selecteditemorder = mainmenuindex;  break;
				case 2:picked_char = 2; selecteditemorder = mainmenuindex;  break;
				}
			}
		}
	}
	else if (UD == 1) {
		if (tostart.type == Event::KeyPressed) {
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				selecteditemorder = mainmenuindex;
				cursor[profileindex].setPosition(430, 250);
				inprofile_menu[0].setFillColor(Color::Red);
				inprofile_menu[1].setFillColor(Color::Black);
				UD = 0;
			}
		}

	}
}

//High Scores
/*
High score options has been merged with name screen options in line 190
High score setup will start from line 242
due to the need of that
*/

//sound options
void sound_options() {
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		sound.play();
		if (soundmenuindex >= 2)cursor[soundoptionsindex].move(0, 0);
		else
		{
			cursor[soundoptionsindex].move(0, 100);  soundmenuindex++;
			inSound_menu[soundmenuindex].setFillColor(Color::Red);
			inSound_menu[soundmenuindex - 1].setFillColor(Color::Black);
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up)) {
		sound.play();
		if (soundmenuindex <= 0) cursor[soundoptionsindex].move(0, 0);
		else
		{
			cursor[soundoptionsindex].move(0, -100);   soundmenuindex--;
			inSound_menu[soundmenuindex].setFillColor(Color::Red);
			inSound_menu[soundmenuindex + 1].setFillColor(Color::Black);
		}
	}
	switch (soundmenuindex)
	{
	case 0:if (musicpointer <= 10) {
		if (Keyboard::isKeyPressed(Keyboard::Right))musicpointer++;
		if (Keyboard::isKeyPressed(Keyboard::Left) && musicpointer > 0)musicpointer--;
		music.setVolume(10 * musicpointer);
		insid.setVolume(10 * musicpointer);
	}
		  else musicpointer = 10;
		break;

	case 1:if (soundpointer <= 10) {
		if (Keyboard::isKeyPressed(Keyboard::Right))soundpointer++;
		if (Keyboard::isKeyPressed(Keyboard::Left) && soundpointer > 0)soundpointer--;
		sound.setVolume(10 * soundpointer);
		loswav.setVolume(10 * soundpointer);
		hoob.setVolume(10 * soundpointer);
		alarm.setVolume(10 * soundpointer);
	}
		  else soundpointer = 10;
		break;
	case 2:if (tostart.type == Event::KeyReleased) {
		if (tostart.key.code == Keyboard::Space) {
			cursor[soundoptionsindex].setPosition(430, 250);
			soundmenuindex = 0;
			inSound_menu[0].setFillColor(Color::Red);
			inSound_menu[2].setFillColor(Color::Black);
			selecteditemorder = 10;
			selectedItemIndex = 4;
		}
		break;
	}
	}
}

//mode select
// 1 player Namescreen
void name_enter_loop() {
	if (livename.size() < 10) {
		if (tostart.type == Event::TextEntered)
		{
			livename += tostart.text.unicode;
			entered_name.setString(livename);
		}
	}
}

// 2 platers Namescreen
void twoplayers_name_enter_loop() {
	if (screennumber == 1) {
		if (player1_name.size() < 10) {
			if (tostart.type == Event::TextEntered)
			{
				player1_name += tostart.text.unicode;
				entered_name.setString(player1_name);
			}
		}
	}
	if (screennumber == 3) {
		if (player2_name.size() < 10) {
			if (tostart.type == Event::TextEntered)
			{
				player2_name += tostart.text.unicode;
				entered_name.setString(player2_name);
			}
		}
	}
}

//players menu
void modeselection_menu() {
	if (tostart.type == Event::KeyReleased) {
		if (tostart.key.code == Keyboard::Down) {
			if (selectedplayersIndex + 1 < 3) {
				modes[selectedplayersIndex].setFillColor(Color::Black);
				cursor[modemenuindex].move(0, 70);
				selectedplayersIndex++;
				modes[selectedplayersIndex].setFillColor(Color::Red);
			}
		} //move up 
		else if (tostart.key.code == Keyboard::Up) {
			if (selectedplayersIndex - 1 >= 0) {
				modes[selectedplayersIndex].setFillColor(Color::Black);
				cursor[modemenuindex].move(0, -70);
				selectedplayersIndex--;
				modes[selectedplayersIndex].setFillColor(Color::Red);
			}
		}
	}
	if (tostart.type == Event::KeyPressed) {
		if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space)) {
			switch (selectedplayersIndex) {
			case 0: selecteditemorder = namescreenindex;
				entered_name.setString(livename);        break;
			case 1: screennumber = 1;
				entered_name.setString(player1_name);    break;

			case 2: selecteditemorder = mainmenuindex;           break;
			}
		}
	}
}
int pickno = 0;
void character_pick() {
	if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Right) {
		if (pickno < 2) {
			pickno++;
			pointer.move(120, 0);
			pointer.setFillColor(Color(0, 0, 0, 50));
		}
	}
	else if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Left) {
		if (pickno > 0) {
			pickno--;
			pointer.move(-120, 0);
			pointer.setFillColor(Color(0, 0, 0, 50));
		}
	}
	if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Enter) {
		if (screennumber == 2) {
			player1_character = pickno;
			pickno = 0;
			screennumber = 3;
			entered_name.setString(player2_name);
			pointer.setPosition(Vector2f(226, characters[0].getPosition().y - 1));
		}
		else if (screennumber == 4) {

			if (player1_character != pickno) {
				player2_character = pickno;
				twoplayers_mode_set();
				game_reset();
				pickno = 0;
				pointer.setPosition(Vector2f(226, characters[0].getPosition().y - 1));
				selecteditemorder = twoplayersindex;
			}
			else
				pointer.setFillColor(Color(255, 0, 0, 50));
		}
	}
}


//Game Over
Texture gameoverT;
Sprite gameover;
void game_over() {
	if (tostart.type == Event::KeyReleased) {
		if (tostart.key.code == Keyboard::Space)
			selecteditemorder = mainmenuindex;
	}
}

//Pause Menu Select
void pause_menu() {
	/* Move Left */
	if (tostart.type == Event::KeyReleased) {
		if (tostart.key.code == Keyboard::Left) {
			if (selectedPauseIndex - 1 >= 0) {
				pausetext[selectedPauseIndex].setFillColor(Color::Black);
				selectedPauseIndex--;
				pausetext[selectedPauseIndex].setFillColor(Color::Red);
			}
		}
		/* Move Right */
		if (tostart.key.code == Keyboard::Right) {
			if (selectedPauseIndex + 1 < PAUSED_ITEMS) {
				pausetext[selectedPauseIndex].setFillColor(Color::Black);
				selectedPauseIndex++;
				pausetext[selectedPauseIndex].setFillColor(Color::Red);
			}
		}

		if (tostart.key.code == Keyboard::Space || tostart.key.code == Keyboard::Enter) {
			switch (selectedPauseIndex) {
			case 0: selecteditemorder = gameindex;                            break;
			case 1:selecteditemorder = mainmenuindex; screennumber = 0;       break;
			}
		}
	}
}
// #4
void topfive_set() {
	for (int i = 1; i < 6; i++) {
		for (int j = 0; j < 2; j++) {
			topfive[i][j].setFillColor(Color::Black);
			topfive[i][j].setCharacterSize(45);
			topfive[i][0].setPosition(Vector2f(150, 180 + 50 * i));
			topfive[i][1].setPosition(Vector2f(505, 180 + 50 * i));
		}
	}
	for (int i = 1; i < 6; i++) {
		billboardconvertor.str("");
		topfive[i][0].setString(billboard[i - 1].name);
		billboardconvertor << billboard[i - 1].score;
		topfive[i][1].setString(billboardconvertor.str());
	}
}

// #3
bool scorecompare(player player1, player player2) {
	return player1.score > player2.score;
}
// #2
//score sort
void re_sort_score() {
	sort(billboard.begin(), billboard.end(), scorecompare);
}
// #5
// Last store Export
void outleaderboard() {
	liveplayer.score = livescore;
	billboard.push_back(liveplayer);
	scoreboardout << billboard[billboard.size() - 1].name;
	scoreboardout << " ";
	scoreboardout << billboard[billboard.size() - 1].score;
	re_sort_score();
	selecteditemorder = mainmenuindex;
}
// #1
//score restoring
void restorescore() {
	while (scoreboardin) {
		scoreboardin >> rest;
		scoreboardin >> resu;
		if (rest == "-1")
			break;
		liveplayer.name = rest;
		liveplayer.score = resu;
		billboard.push_back(liveplayer);
		players_number++;
	}
	scoreboardin.close();
	billboard.pop_back();

	re_sort_score();
}

//blocks
void blocks() {
	hor = 80 + rand() % 375;
	ver -= 100;
	b_scale = 0 + rand() % 6;
	blocksno++;
	blockcounter++;
}
int blok = 0;
Text blokno;
ostringstream convertblocks;
string inconvertblocks;


//scrolling
float remaining_time = 0, scrollspeed = 1;
bool isStart = false;
bool isscrolling = false;
int movespeed = 1;


void scrolling() {
	backg11.move(Vector2f(0, 0.3));
	backg12.move(Vector2f(0, scrollspeed * movespeed));
	backg21.move(Vector2f(0, 0.3));
	backg22.move(Vector2f(0, scrollspeed * movespeed));
	for (int i = 0; i < 8; i++) {
		b_drawer[i].move(Vector2f(0, scrollspeed * movespeed));
	}

	ground_b.move(Vector2f(0, scrollspeed * movespeed));
	blokno.move(Vector2f(0, scrollspeed * movespeed));
	if (backg21.getPosition().y >= 0 && backg21.getPosition().y <= 1) {
		isStart = true;
		backg11.setPosition(0, -599);
	}
	else if (backg11.getPosition().y >= 0 && backg11.getPosition().y <= 1 && isStart == true) {
		backg21.setPosition(0, -599);
	}
	if (backg22.getPosition().y >= 0 && backg22.getPosition().y <= 1.5 * (scrollspeed * movespeed)) {
		isStart = true;
		backg12.setPosition(0, -599);
	}
	else if (backg12.getPosition().y >= 0 && backg12.getPosition().y <= 1.5 * (scrollspeed * movespeed) && isStart == true) {
		backg22.setPosition(0, -599);
	}
	if (selecteditemorder == gameindex) {
		icy[picked_char].move(Vector2f(0, scrollspeed * movespeed));
		collider.move(Vector2f(0, scrollspeed * movespeed));

		if (icy[picked_char].getPosition().y < -2) {
			icy[picked_char].setPosition(Vector2f(icy[picked_char].getPosition().x, 1));
			collider.setPosition(Vector2f(collider.getPosition().x, 61));
		}
		else if (icy[picked_char].getPosition().y < 20)
			movespeed = 5;
		else if (icy[picked_char].getPosition().y > 100)
			movespeed = 1;
	}
	else if (selecteditemorder == twoplayersindex) {
		twoplayers_icy[player1_character].move(Vector2f(0, scrollspeed * movespeed));
		twoplayers_collider[player1_character].move(Vector2f(0, scrollspeed * movespeed));
		twoplayers_fightcollider[player1_character].move(Vector2f(0, scrollspeed * movespeed));

		twoplayers_icy[player2_character].move(Vector2f(0, scrollspeed * movespeed));
		twoplayers_collider[player2_character].move(Vector2f(0, scrollspeed * movespeed));
		twoplayers_fightcollider[player2_character].move(Vector2f(0, scrollspeed * movespeed));

		if (twoplayers_icy[player1_character].getPosition().y < -2) {
			twoplayers_icy[player1_character].setPosition(Vector2f(twoplayers_icy[player1_character].getPosition().x, 1));
			twoplayers_collider[player1_character].setPosition(Vector2f(twoplayers_collider[player1_character].getPosition().x, 61));
		}
		else if (twoplayers_icy[player1_character].getPosition().y < 30 ||
			twoplayers_icy[player2_character].getPosition().y < 30)
			movespeed = 5;
		else if (twoplayers_icy[player1_character].getPosition().y > 100 &&
			twoplayers_icy[player2_character].getPosition().y > 100)
			movespeed = 1;


		if (twoplayers_icy[player2_character].getPosition().y < -2) {
			twoplayers_icy[player2_character].setPosition(Vector2f(twoplayers_icy[player2_character].getPosition().x, 1));
			twoplayers_collider[player2_character].setPosition(Vector2f(twoplayers_collider[player2_character].getPosition().x, 61));
		}/*
		else if (twoplayers_icy[player2_character].getPosition().y < 30)
			movespeed = 5;
		else if (twoplayers_icy[player2_character].getPosition().y > 100)
			movespeed = 1;
			*/
	}
	for (int i = 0; i < 7; i++) {
		if (b_drawer[i].getPosition().y >= 600) {

			if (i == 0)ver = b_drawer[6].getPosition().y;
			else ver = b_drawer[i - 1].getPosition().y;
			blocks();
			b_drawer[i].setScale(arr[b_scale], 1);
			b_drawer[i].setPosition(Vector2f(hor, ver));
			blockvalue[i] = blocksno;
			b_drawer[i].setTexture(blockshape[color_number]);

			if (blockcounter == 10)
			{
				if (color_number < 4) {
					b_drawer[7].setTexture(levelsg[color_number + 1]);
					blok += 10;
					convertblocks << blok;
					inconvertblocks = convertblocks.str();
					blokno.setString(inconvertblocks);
					blokno.setPosition(400, ver + 10);
					blokno.setFont(font);
					blokno.setCharacterSize(20);
					blokno.setFillColor(Color::White);
					inconvertblocks.clear();
					convertblocks.str("");
				}
				else {
					b_drawer[7].setTexture(levelsg[0]);
					blok += 10;
					convertblocks << blok;
					inconvertblocks = convertblocks.str();
					blokno.setString(inconvertblocks);
					blokno.setPosition(400, ver + 10);
					blokno.setFont(font);
					blokno.setCharacterSize(20);
					blokno.setFillColor(Color::White);
					inconvertblocks.clear();
					convertblocks.str("");
				}
				b_drawer[7].setPosition(90, ver);


				blockvalue[7] = blocksno;
				blockcounter = 0;
				color_number++;
				if (color_number > 4)color_number = 0;
			}

			break;
		}

	}
}

//reset original game positions to re play
Text score[2];
//long long livescore = 0;
void game_reset() {
	backg11.setPosition(0, 0);
	backg12.setPosition(0, 0);
	backg21.setPosition(0, -599);
	backg22.setPosition(0, -599);

	icy[picked_char].setRotation(0);
	icy[picked_char].setOrigin(0, 0);
	icy[picked_char].setPosition(Vector2f(400, 480));
	collider.setPosition(Vector2f(435, 540));
	highj = false;
	ver = 540;
	blockcounter = 0;
	b_drawer[7].setPosition(90, 650);
	ground_b.setPosition(90, 540);
	blocksno = 0;
	j = 0;
	scrollspeed = 1;
	for (int i = 0; i < 7; i++) {
		blocks();
		b_drawer[i].setPosition(hor, ver);
		b_drawer[i].setScale(1.0f, 1.0f);
		b_drawer[i].scale(arr[b_scale], 1);
		blockvalue[i] = blocksno;
	}
	livescore = 0;
	ostringstream scoreconverter;  scoreconverter << livescore;
	string inscreenscore = scoreconverter.str();
	score[1].setString(inscreenscore);
	vi.y = 0; g = 0;
	isscrolling = false;
	clockanim.left = 0;
	stopwatch.setTextureRect(clockanim);
	color_number = 0;
	for (int i = 0; i < 7; i++)
		b_drawer[i].setTexture(blockshape[color_number]);
	blok = 0;

	inconvertblocks.clear();
	convertblocks.str("");
	isHurry = false;
}


int main() {

	restorescore();

	RenderWindow window(VideoMode(800, 600), "ICY TOWER GEN33");
	Image icon;
	icon.loadFromFile("cursor.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window.setFramerateLimit(120);

	curs.loadFromFile("cursor.png");
	for (int i = 0; i < 11; i++) {
		cursor[i].setTexture(curs);
		cursor[i].setScale(0.07, 0.09);
	}

	//starting menu
	Texture intro;
	intro.loadFromFile("intro-background.jpg");
	menubackg.setTexture(intro);
	/* Font */
	font.loadFromFile("ARABOLIC.ttf");

	/* Play */
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Red);
	menu[0].setString("Play Game");
	menu[0].setPosition({ 476.0f,235.0f });
	menu[0].setCharacterSize(45);
	cursor[mainmenuindex].setPosition(Vector2f(420.0f, 243.0f));

	//Mode selection
	//Text modes[3];
	for (int i = 0; i < 3; i++) {
		modes[i].setFont(font);
		modes[i].setFillColor(Color::Black);
		modes[i].setCharacterSize(45);
		modes[i].setPosition(476, 235 + (i * 70));
	}
	modes[0].setFillColor(Color::Red);
	modes[0].setString("one player");
	modes[1].setString("two players");
	modes[2].setString("Back");
	cursor[modemenuindex].setPosition(Vector2f(420.0f, 243.0f));
	Text twoplayers_headertext[2];
	for (int i = 0; i < 2; i++) {
		twoplayers_headertext[i].setFont(font);
		twoplayers_headertext[i].setCharacterSize(40);
		twoplayers_headertext[i].setPosition(Vector2f(130, 200));
		twoplayers_headertext[i].setFillColor(Color::Red);
	}
	twoplayers_headertext[0].setString("Enter player one Name:");
	twoplayers_headertext[1].setString("Enter player two Name:");

	character_choose.setFont(font);
	character_choose.setCharacterSize(40);
	character_choose.setPosition(Vector2f(145, 210));
	character_choose.setFillColor(Color::Red);
	character_choose.setString("Pick Your Character");
	icy_icon.loadFromFile("icy character.png"); trump_icon.loadFromFile("Trump character.png");
	dancer_icon.loadFromFile("icy character2.png");
	icy_icon.setSmooth(true); trump_icon.setSmooth(true); dancer_icon.setSmooth(true);
	characters[0].setTexture(trump_icon);    characters[0].setPosition(230, 330);
	characters[1].setTexture(icy_icon);      characters[1].setPosition(350, 330);
	characters[2].setTexture(dancer_icon);   characters[2].setPosition(470, 330);

	pointer.setFillColor(Color(0, 0, 0, 50));
	pointer.setPosition(226, 329);

	//Name screen
	Texture namescreen_backg;
	namescreen_backg.loadFromFile("namescreen.jpg");
	namescreen.setTexture(namescreen_backg);
	name_enter.setFont(font);                   name_enter.setCharacterSize(45);
	name_enter.setString("Enter Your Name:");    name_enter.setFillColor(Color::Red);
	name_enter.setPosition(Vector2f(130, 200));
	//Entered Name
	entered_name.setFont(font);                 entered_name.setCharacterSize(45);
	entered_name.setFillColor(Color::Black);
	entered_name.setPosition(Vector2f(175, 300));
	/*Pause Screen */
	Texture pausedd;
	pausedd.loadFromFile("pause.png");
	pause.setTexture(pausedd);
	pause.setPosition(134, 118);

	for (int i = 0; i < PAUSED_ITEMS; i++) {
		pausetext[i].setFont(font);
		pausetext[i].setCharacterSize(35);
	}
	pausetext[0].setFillColor(Color::Red);
	pausetext[0].setString("Continue");
	pausetext[0].setPosition(215, 338);
	pausetext[1].setString("Exit");
	pausetext[1].setPosition(523, 336);
	pausetext[1].setFillColor(Color::Black);

	/* instructions */
	menu[1].setFont(font);
	menu[1].setFillColor(Color::Black);
	menu[1].setString("Instructions");
	menu[1].setPosition({ 476.0f,285.0f });
	menu[1].setCharacterSize(45);

	for (int i = 0; i < 4; i++)
		instruct[i].loadFromFile(instruct_names[i]);

	for (int i = 0; i < 4; i++)
		instructions[i].setTexture(instruct[i]);


	/* Profile */
	menu[2].setFont(font);
	menu[2].setFillColor(Color::Black);
	menu[2].setString("Profile");
	menu[2].setPosition({ 476.0f,335.0f });
	menu[2].setCharacterSize(45);
	inprofile_menu[0].setString("CHARACTER");
	inprofile_menu[1].setString("BACK");
	for (int i = 0; i < 2; i++) {
		inprofile_menu[i].setFont(font);
		inprofile_menu[i].setCharacterSize(45);
		inprofile_menu[i].setFillColor(Color::Black);
		inprofile_menu[i].setPosition(Vector2f(470, 250 + (150 * i)));
	}
	inprofile_menu[0].setFillColor(Color::Red);
	//cursor
	cursor[profileindex].setPosition(430, 250);
	character[0].setTexture(trump_icon);    character[0].setPosition(550, 320);
	character[1].setTexture(icy_icon);      character[1].setPosition(550, 320);
	character[2].setTexture(dancer_icon);   character[2].setPosition(550, 320);

	/* highscores */
	menu[3].setFont(font);
	menu[3].setFillColor(Color::Black);
	menu[3].setString("High Scores");
	menu[3].setPosition({ 476.0f,385.0f });
	menu[3].setCharacterSize(45);
	//  Text topfive[6][2];
	//  ostringstream billboardconvertor;
	topfive[0][0].setFont(font);                    topfive[0][1].setFont(font);
	topfive[0][0].setFillColor(Color::Red);         topfive[0][1].setFillColor(Color::Red);
	topfive[0][0].setCharacterSize(40);             topfive[0][1].setCharacterSize(40);
	topfive[0][0].setString("Names:");             topfive[0][1].setString("Scores:");
	topfive[0][0].setPosition(Vector2f(150, 170));   topfive[0][1].setPosition(Vector2f(505, 170));
	for (int i = 1; i < 6; i++) {
		for (int j = 0; j < 2; j++) {
			topfive[i][j].setFont(font);
		}
	}

	topfive_set();

	/*Sound options */
	menu[4].setFont(font);
	menu[4].setFillColor(Color::Black);
	menu[4].setString("Sound Options");
	menu[4].setPosition({ 476.0f,435.0f });
	menu[4].setCharacterSize(45);
	menu[4].setScale(0.85, 1);
	Texture soundicon;
	soundicon.loadFromFile("volume.jpg");
	for (int i = 0; i < 11; i++) {
		sound_level[i].setTexture(soundicon);
		music_level[i].setTexture(soundicon);
	}
	int q = 0;
	for (int i = 0; i < 11; i++) {
		int x = 475 + q;
		music_level[i].setPosition(x, 300);
		sound_level[i].setPosition(x, 400);
		q += 25;
	}
	cursor[soundoptionsindex].setPosition(430, 250);
	//Text Sound_menu[3];
	inSound_menu[0].setString("MUSIC VOL");
	inSound_menu[1].setString("Sound VOL");
	inSound_menu[2].setString("BACK");
	for (int i = 0; i < 3; i++) {
		inSound_menu[i].setFont(font);
		inSound_menu[i].setFillColor(Color::Black);
		inSound_menu[i].setCharacterSize(45);
		inSound_menu[i].setPosition(Vector2f(470, 250 + (100 * i)));
	}
	inSound_menu[0].setFillColor(Color::Red);
	SoundBuffer musicbuffer, soundbuffer;
	soundbuffer.loadFromFile("move.wav");
	musicbuffer.loadFromFile("mainsong.wav");
	music.setBuffer(musicbuffer); sound.setBuffer(soundbuffer);
	music.setVolume(50); sound.setVolume(50);
	music.play();

	/* credits */
	Texture credit;
	credit.loadFromFile("credits.jpg");
	Sprite credits(credit);
	menu[5].setFont(font);
	menu[5].setFillColor(Color::Black);
	menu[5].setString("Credits");
	menu[5].setPosition({ 476.0f,485.0f });
	menu[5].setCharacterSize(45);

	/* Exit */
	menu[6].setFont(font);
	menu[6].setFillColor(Color::Black);
	menu[6].setString("Exit");
	menu[6].setPosition({ 476.0f,535.0f });
	menu[6].setCharacterSize(45);

	/* Cursor */
	//Texture curs;
	//curs.loadFromFile("cursor.png");

	//ICY Animation
	Texture icytanimtion;
	icytanimtion.loadFromFile("anim.png");
	Sprite icytanim(icytanimtion);
	icytanim.setPosition(95, 311);
	Vector2u icytanimsize = icytanimtion.getSize();
	icytanimsize.x /= 8;
	IntRect icanim(icytanimsize.x * 0, 0, icytanimsize.x, icytanimsize.y);
	icytanim.setTextureRect(icanim);
	Clock icywatch;


	//HurryUp
	hurry.loadFromFile("hurry.png");
	hurryT.setTexture(hurry);
	hurryT.setPosition(Vector2f(200, 620));

	//bloksno///////////////////////////////////////////


	//scrolling backgrounds
	if (!back1.loadFromFile("Backgroundnew1.jpg")) {
	}
	if (!back2.loadFromFile("Backgroundnew2.png")) {
	}
	backg11.setTexture(back1);
	backg12.setTexture(back2);
	backg21.setTexture(back1);
	backg22.setTexture(back2);
	backg21.setPosition(0, -599);
	backg22.setPosition(0, -599);

	//Main character
	if (!trumpcharacter0.loadFromFile("trump.png")) {
	}
	icycharacter0.loadFromFile("icysprite.png");
	dancercharacter0.loadFromFile("icysprite2.png");

	//Sprite trump;
	icy[0].setTexture(trumpcharacter0);
	icy[0].setScale(0.8, 0.8);
	icy[0].setPosition(Vector2f(400, 480));
	collider.setPosition(Vector2f(435, 540));
	//sprite icy
	icy[1].setTexture(icycharacter0);
	icy[1].setPosition(Vector2f(400, 480));
	icy[1].setScale(0.8, 0.8);
	//sprite raqm 3
	icy[2].setTexture(dancercharacter0);
	icy[2].setPosition(Vector2f(400, 480));
	icy[2].setScale(0.8, 0.8);

	Vector2u texturesize = trumpcharacter0.getSize();
	texturesize.x /= 6;
	texturesize.y /= 4;
	IntRect anim(texturesize.x * 0, texturesize.y * 0, texturesize.x, texturesize.y);
	icy[0].setTextureRect(anim);
	Clock clock;


	SoundBuffer hobs;
	hobs.loadFromFile("hoob3.wav");
	hoob.setBuffer(hobs);
	hoob.setVolume(50);

	SoundBuffer los;
	los.loadFromFile("loserwav.wav");
	loswav.setBuffer(los);
	loswav.setVolume(50);

	SoundBuffer inside;
	inside.loadFromFile("inside.wav");
	insid.setBuffer(inside);
	insid.setVolume(50);

	SoundBuffer alarmb;
	alarmb.loadFromFile("Alarm.wav");
	alarm.setBuffer(alarmb);
	alarm.setVolume(50);

	//blocks Drawer
	/*	string  levelsg_colors[5] = { "glevel 1.png","glevel 2.png" ,"glevel 3.png" ,"glevel 4.png" ,"glevel 5.png" };
		Texture levelsg[5];
		Texture blockshape[5];
		int color_number = 0;*/
	if (!startg.loadFromFile("glevel 1.png")) {
	}
	//level shapes upload
	//Grounds
	for (int i = 0; i < 5; i++)
		if (!levelsg[i].loadFromFile(levelsg_colors[i])) {

		}

	for (int i = 0; i < 5; i++)
		if (!blockshape[i].loadFromFile(b_colors[i])) {
		}
	ground_b.setTexture(startg);
	ground_b.setPosition(90, 540);
	for (int i = 0; i < 7; i++) {
		b_drawer[i].setTexture(blockshape[color_number]);
		blocks();
		b_drawer[i].setPosition(hor, ver);
		b_drawer[i].setScale(1.0f, 1.0f);
		b_drawer[i].scale(arr[b_scale], 1);
		blockvalue[i] = blocksno;
	}
	b_drawer[7].setTexture(startg);
	b_drawer[7].setPosition(90, 650);

	//side clock

	//Sprite stopwatch;
	Texture stopwatchT;
	stopwatchT.loadFromFile("clockspritesh.png");
	stopwatch.setTexture(stopwatchT);
	stopwatch.setScale(0.25, 0.25);
	stopwatch.setPosition(6, 17);
	clocksize = stopwatchT.getSize();
	clocksize.x /= 17;
	clockanim.left = 0;
	clockanim.width = clocksize.x;
	clockanim.height = clocksize.y;
	stopwatch.setTextureRect(clockanim);
	Clock watch, scrollspeedclock;
	Clock stopwatchclock;

	//game over setup
	gameoverT.loadFromFile("game over.png");
	gameover.setTexture(gameoverT);
	Text gameoverscore[2];
	for (int i = 0; i < 2; i++) {
		gameoverscore[i].setFont(font);
		gameoverscore[i].setFillColor(Color::White);
		gameoverscore[i].setPosition(Vector2f(272 + 200 * i, 400));
	}
	gameoverscore[0].setString("Your Score :");

	//jumping
/*	Vector2f vi;
	float g=0.002;
	*/

	Event insidegame;
	float lastp;
	bool lastpc = true, lastpc2 = true;
	float dist = 0;
	bool n = false;
	//long long livescore = 0;
	bool isscoretaken = false;

	//score
	//Text score[2];
	for (int i = 0; i < 2; i++) {
		score[i].setFont(font);
		score[i].setCharacterSize(35);
		score[i].setFillColor(Color::White);
	}
	score[0].setString("Score : ");
	score[0].setPosition(Vector2f(10, 550));
	//long long livescore
	ostringstream scoreconverter;  scoreconverter << livescore;
	string inscreenscore = scoreconverter.str();
	score[1].setString(inscreenscore);
	score[1].setPosition(Vector2f(140, 550));


	while (window.isOpen()) {
		//Main Menu
		if (selecteditemorder == 10) {
			insid.stop();
			if (music.getStatus() != sf::Music::Status::Playing)
				music.play();
			//Play Icy Animation
			if (icywatch.getElapsedTime().asSeconds() > 0.1f) {
				if (icanim.left == icytanimsize.x * 7) {
					icanim.left = 0;
				}
				else {
					icanim.left += icytanimsize.x;
				}
				icytanim.setTextureRect(icanim);
				icywatch.restart();

			}
			while (window.pollEvent(tostart)) {
				if (tostart.type == Event::Closed)window.close();
				else
					main_menu();
			}
		}

		//Exit
		else if (selecteditemorder == exitindex) {
			scoreboardout << "\n ";
			scoreboardout.close();
			window.close();
		}

		//credits
		else if (selecteditemorder == creditsindex) {
			while (window.pollEvent(tostart)) {
				if (tostart.type == Event::Closed)window.close();
				if (tostart.key.code == Keyboard::Escape)selecteditemorder = 10;
			}
		}

		//Sound Options
		else if (selecteditemorder == soundoptionsindex) {
			while (window.pollEvent(tostart)) {
				if (tostart.type == Event::Closed)window.close();
				else if (tostart.key.code == Keyboard::Escape)selecteditemorder = 10;
				else sound_options();
			}
		}

		//High scores
		else if (selecteditemorder == highscoresindex) {
			while (window.pollEvent(tostart)) {
				if (tostart.type == Event::Closed)window.close();
				if (tostart.key.code == Keyboard::Escape)selecteditemorder = 10;
			}
		}

		//profile
		else if (selecteditemorder == profileindex) {
			while (window.pollEvent(tostart)) {
				if (tostart.type == Event::Closed)window.close();
				else if (tostart.key.code == Keyboard::Escape)selecteditemorder = 10;
				else profile_options();
			}
		}

		//Instructions
		else if (selecteditemorder == instructionindex) {
			while (window.pollEvent(tostart)) {
				if (tostart.type == Event::Closed)window.close();
				else if (tostart.key.code == Keyboard::Escape) {
					shown_instruct = 0;
					selecteditemorder = 10;
				}
				else instructions_menu();
			}
		}

		//Start Game
		//Mode select
		else if (selecteditemorder == modemenuindex) {
			switch (screennumber) {
			case 0:
				while (window.pollEvent(tostart)) {
					if (tostart.type == Event::Closed)window.close();
					else if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Escape)
						selecteditemorder = mainmenuindex;
					else modeselection_menu();
				}  break;
			case 1:
				while (window.pollEvent(tostart)) {
					if (tostart.type == Event::Closed)window.close();
					else if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Escape) {
						screennumber = 0;
					}
					else if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Enter) {
						//screennumber = 2;
						screennumber = 2;
						entered_name.setString(player2_name);
					}
					else if (tostart.key.code == Keyboard::BackSpace) {
						if (player1_name.size() > 0) {
							player1_name.pop_back();
							entered_name.setString(player1_name);
						}
					}
					else twoplayers_name_enter_loop();
				}
				break;
			case 2:
				while (window.pollEvent(tostart)) {
					if (tostart.type == Event::Closed)window.close();
					else if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Escape) {
						screennumber = 1;
						entered_name.setString(player1_name);
					}
					else character_pick();
				}
				break;
			case 3:
				while (window.pollEvent(tostart)) {
					if (tostart.type == Event::Closed)window.close();
					else if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Escape) {
						screennumber = 2;
						entered_name.setString(player1_name);
					}
					else if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Enter) {
						//selecteditemorder = gameindex;
						screennumber = 4;
					}
					else if (tostart.key.code == Keyboard::BackSpace) {
						if (player2_name.size() > 0) {
							player2_name.pop_back();
							entered_name.setString(player2_name);
						}
					}
					else twoplayers_name_enter_loop();
				}
				break;
			case 4:
				while (window.pollEvent(tostart)) {
					if (tostart.type == Event::Closed)window.close();
					else if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Escape) {
						screennumber = 3;
						entered_name.setString(player2_name);
					}
					else character_pick();
				}
				break;
			}

		}

		//1Player Name enter
		else if (selecteditemorder == namescreenindex) {
			while (window.pollEvent(tostart)) {
				if (tostart.type == Event::Closed)window.close();
				else if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Escape) {
					selecteditemorder = modemenuindex;
					screennumber = 0;
				}
				else if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Enter) {
					players_number++;
					liveplayer.name = livename;
					livename.clear();
					entered_name.setString(livename);
					selecteditemorder = gameindex;
					game_reset();
				}
				else if (tostart.key.code == Keyboard::BackSpace) {
					if (livename.size() > 0) {
						livename.pop_back();
						entered_name.setString(livename);
					}
				}
				else name_enter_loop();
			}
		}
		//Pause Menu
		//1 player
		else if (selecteditemorder == pauseindex) {
			insid.stop();
			while (window.pollEvent(tostart)) {
				if (tostart.type == Event::Closed)
					window.close();
				else
					pause_menu();
			}
		}
		//2 player
		else if (selecteditemorder == twoplayers_pauseindex) {
			insid.stop();
			while (window.pollEvent(tostart)) {
				if (tostart.type == Event::Closed)
					window.close();
				else if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Escape)
					selecteditemorder = twoplayersindex;
				else {
					twoplayers_pausemenu();
				}
			}
		}
		//game over
		//1 player
		else if (selecteditemorder == gameoverindex) {
			insid.stop();
			while (window.pollEvent(tostart)) {
				if (tostart.type == Event::Closed)
					window.close();
				else game_over();
			}
		}
		//2 player
		else if (selecteditemorder == twoplayers_gameoverindex) {
			insid.stop();
			while (window.pollEvent(tostart)) {
				if (tostart.type == Event::Closed)
					window.close();
				else if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Space) {
					player1_name.clear();
					player2_name.clear();
					winner.setString(player1_name);
					loser.setString(player1_name);
					entered_name.setString(player1_name);
					selecteditemorder = mainmenuindex;
				}
			}
		}
		// 2 players (both lose) 
		else if (selecteditemorder == twoplayers_bothloseindex) {

			while (window.pollEvent(tostart)) {
				if (tostart.type == Event::Closed)
					window.close();
				else if (tostart.type == Event::KeyPressed && tostart.key.code == Keyboard::Space) {

					selecteditemorder = mainmenuindex;
				}
			}

		}
		//game start

		else if (selecteditemorder == twoplayersindex) {
			music.stop();
			if (insid.getStatus() != sf::Music::Status::Playing)
				insid.play();
			while (window.pollEvent(insidegame)) {
				if (insidegame.type == Event::Closed)window.close();
				if (insidegame.type == Event::LostFocus)
					selecteditemorder = twoplayers_pauseindex;
				if (insidegame.key.code == Keyboard::Escape)
					selecteditemorder = twoplayers_pauseindex;
			}
			twoplayers_mode();
		}

		else if (selecteditemorder == gameindex) {
			music.stop();
			if (insid.getStatus() != sf::Music::Status::Playing)
				insid.play();
			//scrolling
			if (isscrolling == true) {
				scrolling();
			}

			while (window.pollEvent(insidegame)) {
				if (insidegame.type == Event::Closed)window.close();
				else if (insidegame.type == Event::LostFocus)
					selecteditemorder = pauseindex;
				if (insidegame.key.code == Keyboard::Escape)
					selecteditemorder = pauseindex;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
				j++;
			}
			if (j == 1 && vi.y <= 0) {
				if (highjclock.getElapsedTime().asSeconds() < 0.02) {
					vi.y = -11;
					g = 0.2;
					dist = 0;
					highj = true;
					r = true;
					colliderre = true;
				}
				else {
					vi.y = -7 - dist / 200;
					g = 0.2;
					hoob.play();
					dist = 0;
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
				//Moving
				if (icy[picked_char].getPosition().x > 637) {
					icy[picked_char].move(0, 0);  collider.move(0, 0);
					vi.x = -3;
				}
				else if (icy[picked_char].getPosition().x < 637 && vi.x == 0) {
					icy[picked_char].move(5, 0);  collider.move(5, 0);
				}

				//Distance Check
				if (lastpc2 == true) {
					lastp = icy[picked_char].getPosition().x;
					lastpc2 = false;
				}
				if (icy[picked_char].getPosition().x > lastp) {
					dist += 5;
				}
				else {
					dist = 0;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
				//Moving
				if (icy[picked_char].getPosition().x < 73) {
					icy[picked_char].move(0, 0);  collider.move(0, 0);
					vi.x = 3;
				}
				else if (icy[picked_char].getPosition().x > 73 && vi.x == 0) {
					icy[picked_char].move(-5, 0);  collider.move(-5, 0);
				}
				//Distance Check
				if (lastpc == true) {
					lastp = icy[picked_char].getPosition().x;
					lastpc = false;
				}
				if (icy[picked_char].getPosition().x < lastp) {
					dist += 5;
				}
				else {
					dist = 0;
				}
			}
			if (!Keyboard::isKeyPressed(Keyboard::Key::Left) && !Keyboard::isKeyPressed(Keyboard::Key::Right)) {
				dist = 0;
				lastpc2 = true;
				lastpc = true;

			}
			//Animation

			if (highj) {
				anim.top = texturesize.y * 2;
				anim.left = texturesize.x * 3;
				icy[picked_char].setTextureRect(anim);
				icy[picked_char].setOrigin(texturesize.x / 2, texturesize.y / 2);
				icy[picked_char].rotate(6);
				if (r) {
					collider.move(-25, -40);
					r = false;
				}
				if (colliderre && colliderre1) {
					collider.move(25, 40);
					colliderre = false;
					colliderre1 = false;
				}
			}
			else {
				icy[picked_char].setRotation(0);
				if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
					icy[picked_char].setOrigin(0, 0);
					anim.top = texturesize.y;
					if (clock.getElapsedTime().asSeconds() > 0.1f) {
						if (anim.left == texturesize.x * 5) { anim.left = 0; }
						else anim.left += texturesize.x;
						icy[picked_char].setTextureRect(anim);
						clock.restart();
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
					icy[picked_char].setOrigin(0, 0);
					anim.top = texturesize.y * 3;
					if (clock.getElapsedTime().asSeconds() > 0.1f) {
						if (anim.left == texturesize.x * 5) {
							anim.left = 0;
						}
						else anim.left += texturesize.x;
						icy[picked_char].setTextureRect(anim);
						clock.restart();
					}
				}
				else if (!Keyboard::isKeyPressed(Keyboard::Key::Left) && !Keyboard::isKeyPressed(Keyboard::Key::Right)) {
					anim.top = 0;
					anim.left = texturesize.x * 5;
					icy[picked_char].setTextureRect(anim);

				}
			}

			if (icy[picked_char].getPosition().y <= 200)
				isscrolling = true;


			for (int i = 0; i < 8; i++) {
				if (collider.getGlobalBounds().intersects(b_drawer[i].getGlobalBounds()) == true) {
					if (collider.getPosition().y < b_drawer[i].getPosition().y && vi.y>0)
					{
						vi.y = 0;
						g = 0;
						j = 0;

						if (!isscoretaken) {
							livescore = blockvalue[i] * 10;
							isscoretaken = true;
							highj = false;
							icy[picked_char].setOrigin(0, 0);
							colliderre1 = true;

							highjclock.restart();

							inscreenscore.clear();
							scoreconverter.str("");
							score[1].setString(inscreenscore);
							scoreconverter << livescore;
							inscreenscore = scoreconverter.str();
							score[1].setString(inscreenscore);
						}

						break;
					}
				}
				else if (collider.getGlobalBounds().intersects(b_drawer[i].getGlobalBounds()) == false) { g = 0.2; }
			}
			if (vi.y > 0) {
				isscoretaken = false;
			}

			icy[picked_char].move(vi.x, vi.y);
			collider.move(vi.x, vi.y);
			if (vi.x <= 0.2 && vi.x >= -0.2) vi.x = 0;
			else if (vi.x > 0)vi.x -= 0.2;
			else if (vi.x < 0)vi.x += 0.2;

			if (!isscrolling) {
				if (icy[picked_char].getPosition().y < 480) {
					vi.y += g;
				}
				else {
					j = 0;
					vi.y = 0;
					livescore = 0;
					icy[picked_char].setRotation(0);
					icy[picked_char].setOrigin(0, 0);
					inscreenscore.clear();
					scoreconverter.str("");
					score[1].setString(inscreenscore);
					scoreconverter << livescore;
					inscreenscore = scoreconverter.str();
					score[1].setString(inscreenscore);
					icy[picked_char].setPosition(icy[picked_char].getPosition().x, 480);
					collider.setPosition(collider.getPosition().x, 540);
				}
			}
			else vi.y += g;

			//character death
			if (icy[picked_char].getPosition().y > 600) {
				outleaderboard();
				topfive_set();
				gameoverscore[1].setString(inscreenscore);
				anim.top = 0;
				anim.left = texturesize.x;
				icy[picked_char].setTextureRect(anim);
				selecteditemorder = gameoverindex;
				loswav.play();
				blokno.setPosition(400, 670);
			}

			//clock animation
			if (isscrolling) {
				if (stopwatchclock.getElapsedTime().asSeconds() > 3.5f) {
					if (clockanim.left == clocksize.x * 16) {
						clockanim.left = 0;
						scrollspeed += 0.3;
						isHurry = true;
						alarm.play();
					}
					else {
						clockanim.left += clocksize.x;

					}
					stopwatch.setTextureRect(clockanim);
					stopwatchclock.restart();
				}
			}
			if (isHurry == true) {
				if (hurryclock.getElapsedTime().asSeconds() > 0.02f) {
					if (hurryT.getPosition().y > -50) {
						hurryT.move(Vector2f(0, -10));
					}
					else {
						isHurry = false;
						alarm.stop();
						hurryT.setPosition(Vector2f(200, 620));
					}
					hurryclock.restart();
				}
			}
		}

		window.clear();
		//Mode selection
		if (selecteditemorder == modemenuindex) {
			if (screennumber == 0) {
				window.draw(menubackg);
				window.draw(cursor[modemenuindex]);
				for (int i = 0; i < 3; i++)
					window.draw(modes[i]);
			}
			else if (screennumber == 1) {
				window.draw(namescreen);
				window.draw(twoplayers_headertext[0]);
				window.draw(entered_name);
			}
			else if (screennumber == 2) {
				window.draw(namescreen);
				window.draw(character_choose);
				window.draw(pointer);
				for (int i = 0; i < 3; i++)
					window.draw(characters[i]);
			}
			else if (screennumber == 3) {
				window.draw(namescreen);
				window.draw(twoplayers_headertext[1]);
				window.draw(entered_name);
			}
			else if (screennumber == 4) {
				window.draw(namescreen);
				window.draw(character_choose);
				window.draw(pointer);
				for (int i = 0; i < 3; i++)
					window.draw(characters[i]);
			}
		}
		//Name window draw
		else if (selecteditemorder == namescreenindex) {
			window.draw(namescreen);
			window.draw(name_enter);
			window.draw(entered_name);
		}
		//Game Over Screen
		else if (selecteditemorder == gameoverindex) {
			window.draw(backg11);
			window.draw(backg21);
			window.draw(ground_b);
			for (int i = 0; i < 8; i++)
			{
				window.draw(b_drawer[i]);
			}
			window.draw(backg12);
			window.draw(backg22);
			window.draw(gameover);
			window.draw(gameoverscore[0]);
			window.draw(gameoverscore[1]);
		}
		//Main Game draw
		else if (selecteditemorder == gameindex) {
			window.draw(backg11);
			window.draw(backg21);
			window.draw(hurryT);
			window.draw(ground_b);

			for (int i = 0; i < 8; i++)
			{
				window.draw(b_drawer[i]);
			}

			window.draw(backg12);
			window.draw(backg22);
			window.draw(blokno);
			window.draw(icy[picked_char]);
			window.draw(score[0]);
			window.draw(score[1]);
			window.draw(stopwatch);
			//window.draw(collider);
		}
		else if (selecteditemorder == twoplayersindex) {
			window.draw(backg11);
			window.draw(backg21);
			window.draw(hurryT);
			window.draw(ground_b);
			for (int i = 0; i < 8; i++)
			{
				window.draw(b_drawer[i]);
			}
			window.draw(backg12);
			window.draw(backg22);
			window.draw(blokno);
			window.draw(twoplayers_icy[player1_character]);
			window.draw(twoplayers_icy[player2_character]);
			window.draw(stopwatch);

			/*	window.draw(twoplayers_fightcollider[player1_character]);
				window.draw(twoplayers_fightcollider[player2_character]); */
		}
		else if (selecteditemorder == twoplayers_gameoverindex) {
			window.draw(backg11);
			window.draw(backg21);
			window.draw(hurryT);
			window.draw(ground_b);
			for (int i = 0; i < 8; i++)
			{
				window.draw(b_drawer[i]);
			}
			window.draw(backg12);
			window.draw(backg22);
			window.draw(blokno);
			window.draw(twoplayers_icy[player1_character]);
			window.draw(twoplayers_icy[player2_character]);
			window.draw(stopwatch);
			window.draw(winnerS);
			window.draw(winner);
			window.draw(loser);
		}
		else if (selecteditemorder == twoplayers_bothloseindex) {
			window.draw(backg11);
			window.draw(backg21);
			window.draw(hurryT);
			window.draw(ground_b);
			for (int i = 0; i < 8; i++)
			{
				window.draw(b_drawer[i]);
			}
			window.draw(backg12);
			window.draw(backg22);
			window.draw(blokno);
			window.draw(twoplayers_icy[player1_character]);
			window.draw(twoplayers_icy[player2_character]);
			window.draw(stopwatch);
			window.draw(twoplayersloseS);
		}
		//Draw Pause Menu
		else if (selecteditemorder == pauseindex) {
			window.draw(backg11);
			window.draw(backg21);
			window.draw(ground_b);
			for (int i = 0; i < 8; i++)
				window.draw(b_drawer[i]);
			window.draw(ground_b);
			window.draw(backg12);
			window.draw(backg22);
			window.draw(icy[picked_char]);
			window.draw(score[0]);
			window.draw(score[1]);
			window.draw(stopwatch);
			window.draw(pause);
			for (int i = 0; i < PAUSED_ITEMS; i++) {
				window.draw(pausetext[i]);
			}
		}
		else if (selecteditemorder == twoplayers_pauseindex) {
			window.draw(backg11);
			window.draw(backg21);
			window.draw(hurryT);
			window.draw(ground_b);
			for (int i = 0; i < 8; i++)
			{
				window.draw(b_drawer[i]);
			}
			window.draw(backg12);
			window.draw(backg22);
			window.draw(blokno);
			window.draw(twoplayers_icy[player1_character]);
			window.draw(twoplayers_icy[player2_character]);
			window.draw(stopwatch);
			window.draw(pause);
			for (int i = 0; i < PAUSED_ITEMS; i++) {
				window.draw(pausetext[i]);
			}
		}
		//Instructions draw
		else if (selecteditemorder == instructionindex)
			window.draw(instructions[shown_instruct]);
		//Profile draw
		else if (selecteditemorder == profileindex) {
			window.draw(menubackg);
			for (int i = 0; i < 2; i++)
				window.draw(inprofile_menu[i]);
			window.draw(character[RL]);
			window.draw(cursor[profileindex]);
		}
		//High scores draw
		else if (selecteditemorder == highscoresindex) {
			window.draw(namescreen);
			for (int i = 0; i < 6; i++) {
				window.draw(topfive[i][0]);
				window.draw(topfive[i][1]);
			}
		}
		//Sound option draw
		else if (selecteditemorder == soundoptionsindex) {
			window.draw(menubackg);
			for (int i = 0; i < 3; i++)window.draw(inSound_menu[i]);
			for (int i = 0; i < musicpointer; i++)window.draw(music_level[i]);
			for (int i = 0; i < soundpointer; i++)window.draw(sound_level[i]);
			window.draw(cursor[soundoptionsindex]);
		}
		//credits draw
		else if (selecteditemorder == creditsindex)
			window.draw(credits);
		//Main menu draw
		else if (selecteditemorder == mainmenuindex) {
			window.draw(menubackg);
			for (int i = 0; i < MENU_ITEMS; i++) {
				window.draw(menu[i]);
			}
			window.draw(cursor[mainmenuindex]);
			window.draw(icytanim);
		}
		window.display();
	}

	return 0;
}
Vector2u texturesize;

IntRect twoplayers_anim[3];
Clock twoplayers_clock[3];
void twoplayers_mode_set() {
	isscrolling = false;
	twoplayers_icy[0].setTexture(trumpcharacter0);
	twoplayers_icy[0].setScale(0.8, 0.8);

	twoplayers_icy[1].setTexture(icycharacter0);
	twoplayers_icy[1].setScale(0.8, 0.8);

	twoplayers_icy[2].setTexture(dancercharacter0);
	twoplayers_icy[2].setScale(0.8, 0.8);

	twoplayers_collider[0].setSize(Vector2f(9, 10));
	twoplayers_collider[1].setSize(Vector2f(9, 10));
	twoplayers_collider[2].setSize(Vector2f(9, 10));
	twoplayers_fightcollider[0].setSize(Vector2f(32, 45));
	twoplayers_fightcollider[1].setSize(Vector2f(32, 45));
	twoplayers_fightcollider[2].setSize(Vector2f(32, 45));

	twoplayers_icy[player2_character].setPosition(Vector2f(300, 480));
	twoplayers_icy[player1_character].setPosition(Vector2f(500, 480));

	twoplayers_fightcollider[player2_character].setPosition(320, 500);
	twoplayers_fightcollider[player1_character].setPosition(520, 500);

	twoplayers_collider[player2_character].setPosition(Vector2f(335, 540));
	twoplayers_collider[player1_character].setPosition(Vector2f(535, 540));

	texturesize = trumpcharacter0.getSize();
	texturesize.x /= 6;
	texturesize.y /= 4;

	//Player 1 Animation

	twoplayers_anim[player1_character].left = texturesize.x * 0;
	twoplayers_anim[player1_character].top = texturesize.y * 0;
	twoplayers_anim[player1_character].width = texturesize.x;
	twoplayers_anim[player1_character].height = texturesize.y;

	//Player 2 Animation
	twoplayers_anim[player2_character].left = texturesize.x * 0;
	twoplayers_anim[player2_character].top = texturesize.y * 0;
	twoplayers_anim[player2_character].width = texturesize.x;
	twoplayers_anim[player2_character].height = texturesize.y;

	twoplayers_icy[0].setTextureRect(twoplayers_anim[player1_character]);
	twoplayers_icy[1].setTextureRect(twoplayers_anim[player1_character]);
	twoplayers_icy[2].setTextureRect(twoplayers_anim[player1_character]);

	winnerT.loadFromFile("win.png");
	winnerS.setTexture(winnerT);
	winner.setFont(font);
	winner.setCharacterSize(70);
	winner.setPosition(Vector2f(315, 85));
	loser.setFont(font);
	loser.setCharacterSize(30);
	loser.setPosition(Vector2f(245, 545));

	twoplayersloseT.loadFromFile("both.png");
	twoplayersloseS.setTexture(twoplayersloseT);
}

void twoplayers_pausemenu() {
	/* Move Left */
	if (tostart.type == Event::KeyReleased) {
		if (tostart.key.code == Keyboard::Left) {
			if (selectedPauseIndex - 1 >= 0) {
				pausetext[selectedPauseIndex].setFillColor(Color::Black);
				selectedPauseIndex--;
				pausetext[selectedPauseIndex].setFillColor(Color::Red);
			}
		}
		/* Move Right */
		if (tostart.key.code == Keyboard::Right) {
			if (selectedPauseIndex + 1 < PAUSED_ITEMS) {
				pausetext[selectedPauseIndex].setFillColor(Color::Black);
				selectedPauseIndex++;
				pausetext[selectedPauseIndex].setFillColor(Color::Red);
			}
		}

		if (tostart.key.code == Keyboard::Space || tostart.key.code == Keyboard::Enter) {
			switch (selectedPauseIndex) {
			case 0: selecteditemorder = twoplayersindex;                            break;
			case 1:selecteditemorder = mainmenuindex; screennumber = 0;             break;
			}
		}
	}
}

void twoplayers_mode() {
	if (twoplayers_icy[player1_character].getPosition().y <= 200 ||
		twoplayers_icy[player2_character].getPosition().y <= 200) {
		isscrolling = true;
	}
	if (isscrolling) {
		scrolling();
	}
	if (twoplayers_icy[player1_character].getPosition().x > 637) {
		vi0[player1_character].x = -0.6;
	}
	else if (twoplayers_icy[player1_character].getPosition().x < 73) {
		vi0[player1_character].x = 0.6;
	}
	if (twoplayers_icy[player2_character].getPosition().x > 637) {
		vi0[player2_character].x = -0.6;
	}
	else if (twoplayers_icy[player2_character].getPosition().x < 73) {
		vi0[player2_character].x = 0.6;
	}


	//player 1
	if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
		jumpinghandler[player1_character]++;
	}
	if (jumpinghandler[player1_character] == 1 && vi0[player1_character].y <= 0) {
		if (highjclock.getElapsedTime().asSeconds() < 0.05) {
			vi0[player1_character].y = -11;
			gravity[player1_character] = 0.2;
		}
		else {
			vi0[player1_character].y = -7 - twodist[player1_character] / 100;
			gravity[player1_character] = 0.2;
			twodist[player1_character] = 0;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
		if (twoplayers_fightcollider[player1_character].getGlobalBounds().intersects
		(twoplayers_fightcollider[player2_character].getGlobalBounds()) == true) {
			if (twodist[player2_character] < twodist[player1_character]) {
				vi0[player2_character].x = twodist[player1_character] / 50;
			}
		}
		else {

			if (twoplayers_icy[player1_character].getPosition().x > 637) {
				vi0[player1_character].x = -3;
			}
			else if (twoplayers_icy[player1_character].getPosition().x < 637 && vi0[player2_character].x == 0) {
				twoplayers_icy[player1_character].move(5, 0);
				twoplayers_collider[player1_character].move(5, 0);
				twoplayers_fightcollider[player1_character].move(5, 0);
			}
		}
		//Moving
		twoplayers_anim[player1_character].top = texturesize.y;
		if (twoplayers_clock[player1_character].getElapsedTime().asSeconds() > 0.1f) {
			if (twoplayers_anim[player1_character].left == texturesize.x * 5)
			{
				twoplayers_anim[player1_character].left = 0;
			}
			else twoplayers_anim[player1_character].left += texturesize.x;
			twoplayers_icy[player1_character].setTextureRect(twoplayers_anim[player1_character]);
			twoplayers_clock[player1_character].restart();
		}


		//Distance Check
		if (twolastpc2[player1_character] == true) {
			twolastp[player1_character] = twoplayers_icy[player1_character].getPosition().x;
			twolastpc2[player1_character] = false;
		}
		if (twoplayers_icy[player1_character].getPosition().x > twolastp[player1_character]) {
			twodist[player1_character] += 5;
		}
		else {
			twodist[player1_character] = 0;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
		if (twoplayers_fightcollider[player1_character].getGlobalBounds().intersects
		(twoplayers_fightcollider[player2_character].getGlobalBounds()) == true) {
			if (twodist[player2_character] < twodist[player1_character]) {
				vi0[player2_character].x = -1 * twodist[player1_character] / 50;
			}
		}
		else {
			if (twoplayers_icy[player1_character].getPosition().x < 73) {
				vi0[player1_character].x = 3;
			}
			else if (twoplayers_icy[player1_character].getPosition().x > 73 && vi0[player1_character].x == 0) {
				twoplayers_icy[player1_character].move(-5, 0);
				twoplayers_collider[player1_character].move(-5, 0);
				twoplayers_fightcollider[player1_character].move(-5, 0);
			}
		}

		//Moving
		twoplayers_anim[player1_character].top = texturesize.y * 3;
		if (twoplayers_clock[player1_character].getElapsedTime().asSeconds() > 0.1f) {
			if (twoplayers_anim[player1_character].left == texturesize.x * 5) {
				twoplayers_anim[player1_character].left = 0;
			}
			else twoplayers_anim[player1_character].left += texturesize.x;
			twoplayers_icy[player1_character].setTextureRect(twoplayers_anim[player1_character]);
			twoplayers_clock[player1_character].restart();
		}


		//Distance Check
		if (twolastpc[player1_character] == true) {
			twolastp[player1_character] = twoplayers_icy[player1_character].getPosition().x;
			twolastpc[player1_character] = false;
		}
		if (twoplayers_icy[player1_character].getPosition().x < twolastp[player1_character]) {
			twodist[player1_character] += 5;
		}
		else {
			twodist[player1_character] = 0;
		}
	}
	if (!Keyboard::isKeyPressed(Keyboard::Key::Left) && !Keyboard::isKeyPressed(Keyboard::Key::Right)) {
		if (twoplayers_fightcollider[player1_character].getGlobalBounds().intersects
		(twoplayers_fightcollider[player2_character].getGlobalBounds()) == true) {
			if (twoplayers_fightcollider[player1_character].getPosition().x <
				twoplayers_fightcollider[player2_character].getPosition().x) {
				twoplayers_icy[player2_character].move(0.2,0);
				twoplayers_collider[player2_character].move(0.2,0);
				twoplayers_fightcollider[player2_character].move(0.2,0);
			}
			else if (twoplayers_fightcollider[player2_character].getPosition().x >
				twoplayers_fightcollider[player1_character].getPosition().x) {
				twoplayers_icy[player2_character].move(-0.2, 0);
				twoplayers_collider[player2_character].move(-0.2, 0);
				twoplayers_fightcollider[player2_character].move(-0.2,0);
			}
		}
		twoplayers_anim[player1_character].top = 0;
		twoplayers_anim[player1_character].left = texturesize.x * 5;
		twoplayers_icy[player1_character].setTextureRect(twoplayers_anim[player1_character]);


		twodist[player1_character] = 0;
		twolastpc2[player1_character] = true;
		twolastpc[player1_character] = true;
	}
	twoplayers_icy[player1_character].move(vi0[player1_character].x, vi0[player1_character].y);
	twoplayers_collider[player1_character].move(vi0[player1_character].x, vi0[player1_character].y);
	twoplayers_fightcollider[player1_character].move(vi0[player1_character].x, vi0[player1_character].y);
	if (vi0[player1_character].x <= 0.2 && vi0[player1_character].x >= -0.2) vi0[player1_character].x = 0;
	else if (vi0[player1_character].x > 0)vi0[player1_character].x -= 0.2;
	else if (vi0[player1_character].x < 0)vi0[player1_character].x += 0.2;



	if (!isscrolling) {
		if (twoplayers_icy[player1_character].getPosition().y < 480) {
			vi0[player1_character].y += gravity[player1_character];
		}
		else {
			jumpinghandler[player1_character] = 0;
			vi0[player1_character].y = 0;
		}
	}
	else vi0[player1_character].y += gravity[player1_character];

	//Collider
	for (int i = 0; i < 8; i++) {
		if (twoplayers_collider[player1_character].getGlobalBounds().intersects(b_drawer[i].getGlobalBounds()) == true) {
			if (twoplayers_collider[player1_character].getPosition().y < b_drawer[i].getPosition().y && vi0[player1_character].y>0)
			{
				vi0[player1_character].y = 0;
				gravity[player1_character] = 0;
				jumpinghandler[player1_character] = 0;
				break;
			}
		}
		else if (twoplayers_collider[player1_character].getGlobalBounds().intersects(b_drawer[i].getGlobalBounds()) == false)
		{
			gravity[player1_character] = 0.2;
		}
	}

	//player 2
	if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
		jumpinghandler[player2_character]++;
	}
	if (jumpinghandler[player2_character] == 1 && vi0[player2_character].y <= 0) {
		if (highjclock.getElapsedTime().asSeconds() < 0.05) {
			vi0[player2_character].y = -11;
			gravity[player2_character] = 0.2;
			twodist[player2_character] = 0;
			highj = true;
			r = true;
			colliderre = true;
		}
		else {
			vi0[player2_character].y = -7 - twodist[player2_character] / 100;
			gravity[player2_character] = 0.2;
			twodist[player2_character] = 0;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::D)
		) {
		if (twoplayers_fightcollider[player2_character].getGlobalBounds().intersects
		(twoplayers_fightcollider[player1_character].getGlobalBounds()) == true) {
			if (twodist[player2_character] > twodist[player1_character]) {
				vi0[player1_character].x = twodist[player2_character] / 50;
			}
		}
		else {
			if (twoplayers_icy[player2_character].getPosition().x > 637) {
				vi0[player2_character].x = -3;
			}
			else if (twoplayers_icy[player2_character].getPosition().x < 637 && vi0[player2_character].x == 0) {
				twoplayers_icy[player2_character].move(5, 0);
				twoplayers_collider[player2_character].move(5, 0);
				twoplayers_fightcollider[player2_character].move(5, 0);
			}

		}
		//Moving
		twoplayers_anim[player2_character].top = texturesize.y;
		if (twoplayers_clock[player2_character].getElapsedTime().asSeconds() > 0.1f) {
			if (twoplayers_anim[player2_character].left == texturesize.x * 5) { twoplayers_anim[player2_character].left = 0; }
			else twoplayers_anim[player2_character].left += texturesize.x;
			twoplayers_icy[player2_character].setTextureRect(twoplayers_anim[player2_character]);
			twoplayers_clock[player2_character].restart();
		}

		//Distance Check
		if (twolastpc2[player2_character] == true) {
			twolastp[player2_character] = twoplayers_icy[player2_character].getPosition().x;
			twolastpc2[player2_character] = false;
		}
		if (twoplayers_icy[player2_character].getPosition().x > twolastp[player2_character]) {
			twodist[player2_character] += 5;
		}
		else {
			twodist[player2_character] = 0;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		if (twoplayers_fightcollider[player2_character].getGlobalBounds().intersects
		(twoplayers_fightcollider[player1_character].getGlobalBounds()) == true) {
			if (twodist[player2_character] > twodist[player1_character]) {
				vi0[player1_character].x = -1 * twodist[player2_character] / 50;
			}
		}
		else {
			if (twoplayers_icy[player2_character].getPosition().x < 73) {
				vi0[player2_character].x = 3;
			}
			else if (twoplayers_icy[player2_character].getPosition().x > 73 && vi0[player2_character].x == 0) {
				twoplayers_icy[player2_character].move(-5, 0);
				twoplayers_collider[player2_character].move(-5, 0);
				twoplayers_fightcollider[player2_character].move(-5, 0);
			}
		}
		//Moving
		twoplayers_anim[player2_character].top = texturesize.y * 3;
		if (twoplayers_clock[player2_character].getElapsedTime().asSeconds() > 0.1f) {
			if (twoplayers_anim[player2_character].left == texturesize.x * 5) {
				twoplayers_anim[player2_character].left = 0;
			}
			else twoplayers_anim[player2_character].left += texturesize.x;
			twoplayers_icy[player2_character].setTextureRect(twoplayers_anim[player2_character]);
			twoplayers_clock[player2_character].restart();
		}


		//Distance Check
		if (twolastpc[player2_character] == true) {
			twolastp[player2_character] = twoplayers_icy[player2_character].getPosition().x;
			twolastpc[player2_character] = false;
		}
		if (twoplayers_icy[player2_character].getPosition().x < twolastp[player2_character]) {
			twodist[player2_character] += 5;
		}
		else {
			twodist[player2_character] = 0;
		}
	}


	if (!Keyboard::isKeyPressed(Keyboard::Key::A) && !Keyboard::isKeyPressed(Keyboard::Key::D)) {
		if (twoplayers_fightcollider[player2_character].getGlobalBounds().intersects
		(twoplayers_fightcollider[player1_character].getGlobalBounds()) == true) {
			if (twoplayers_fightcollider[player2_character].getPosition().x <
				twoplayers_fightcollider[player1_character].getPosition().x) {
				twoplayers_icy[player1_character].move(0.2 , 0);
				twoplayers_collider[player1_character].move(0.2 , 0);
				twoplayers_fightcollider[player1_character].move(0.2 , 0);
		}
			else if (twoplayers_fightcollider[player2_character].getPosition().x >
				twoplayers_fightcollider[player1_character].getPosition().x) {
				twoplayers_icy[player1_character].move(-0.2 , 0);
				twoplayers_collider[player1_character].move(-0.2 , 0);
				twoplayers_fightcollider[player1_character].move(-0.2 , 0);
			}
		}
		twoplayers_anim[player2_character].top = 0;
		twoplayers_anim[player2_character].left = texturesize.x * 5;
		twoplayers_icy[player2_character].setTextureRect(twoplayers_anim[player2_character]);



		twodist[player2_character] = 0;
		twolastpc2[player2_character] = true;
		twolastpc[player2_character] = true;
	}
	twoplayers_icy[player2_character].move(vi0[player2_character].x, vi0[player2_character].y);
	twoplayers_collider[player2_character].move(vi0[player2_character].x, vi0[player2_character].y);
	twoplayers_fightcollider[player2_character].move(vi0[player2_character].x, vi0[player2_character].y);
	if (vi0[player2_character].x <= 0.2 && vi0[player2_character].x >= -0.2) vi0[player2_character].x = 0;
	else if (vi0[player2_character].x > 0)vi0[player2_character].x -= 0.2;
	else if (vi0[player2_character].x < 0)vi0[player2_character].x += 0.2;

	if (!isscrolling) {
		if (twoplayers_icy[player2_character].getPosition().y < 480) {
			vi0[player2_character].y += gravity[player2_character];
		}
		else {
			jumpinghandler[player2_character] = 0;
			vi0[player2_character].y = 0;
		}
	}
	else vi0[player2_character].y += gravity[player2_character];
	//Collider
	for (int i = 0; i < 8; i++) {
		if (twoplayers_collider[player2_character].getGlobalBounds().intersects(b_drawer[i].getGlobalBounds()) == true) {
			if (twoplayers_collider[player2_character].getPosition().y < b_drawer[i].getPosition().y && vi0[player2_character].y>0)
			{
				vi0[player2_character].y = 0;
				gravity[player2_character] = 0;
				jumpinghandler[player2_character] = 0;
				break;
			}
		}
		else if (twoplayers_collider[player2_character].getGlobalBounds().intersects(b_drawer[i].getGlobalBounds()) == false)
		{
			gravity[player2_character] = 0.2;
		}
	}
	if (twoplayers_icy[player1_character].getPosition().y > 590 && twoplayers_icy[player2_character].getPosition().y > 590) {
		loswav.play();
		selecteditemorder = twoplayers_bothloseindex;
	}
	else if (twoplayers_icy[player1_character].getPosition().y > 601) {
		winner.setString(player2_name);
		player1_name += " is a Looooser!";
		loser.setString(player1_name);
		loswav.play();
		selecteditemorder = twoplayers_gameoverindex;
	}
	else if (twoplayers_icy[player2_character].getPosition().y > 601) {
		winner.setString(player1_name);
		player2_name += " is a Looooser!";
		loser.setString(player2_name);
		loswav.play();
		selecteditemorder = twoplayers_gameoverindex;
	}
	//clock animation
	if (isscrolling) {
		if (stopwatchclock.getElapsedTime().asSeconds() > 3.5f) {
			if (clockanim.left == clocksize.x * 16) {
				clockanim.left = 0;
				scrollspeed += 0.3;
				isHurry = true;
				alarm.play();
			}
			else {
				clockanim.left += clocksize.x;

			}
			stopwatch.setTextureRect(clockanim);
			stopwatchclock.restart();
		}
	}
	if (isHurry == true) {
		if (hurryclock.getElapsedTime().asSeconds() > 0.02f) {
			if (hurryT.getPosition().y > -50) {
				hurryT.move(Vector2f(0, -10));
			}
			else {
				isHurry = false;
				alarm.stop();
				hurryT.setPosition(Vector2f(200, 620));
			}
			hurryclock.restart();
		}
	}
}

