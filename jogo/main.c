


/***************************************
**PARA RODAR O JOGO PRESSIONE CTRL+F11**
***************************************/



#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "objetos.h"
#include <math.h>

//GLOBALS==============================
//Variaveis auxiliares
bool ACERTOU, ERROU, validar_and, validar_or, validar_nand, validar_nor, validar_andna, validar_andnb, validar_orna, validar_ornb, validar_not;
bool Binarios = true;
bool Resposta = false;
int rndA, rndB, rndS;

#define WIDTH 1200
#define HEIGHT 600
#define NUM_BULLETS 5
#define NUM_SCORES 10
#define NUM_EXPLOSIONS 5
#define NUM_SCORES1 10
#define NUM_and 2
#define NUM_nand 2
#define NUM_andna 2
#define NUM_andnb 2
#define NUM_or 2
#define NUM_nor 2
#define NUM_orna 2
#define NUM_ornb 2
#define NUM_not 2



enum STATE{TITLE, INTRO, PLAYING, LOST};
enum KEYS{UP, DOWN, SPACE};
bool keys[5] = {false, false, false};

SpaceShip ship;
SpaceBadShip Bship;
Bullet bullets[NUM_BULLETS];
Scores zero[NUM_SCORES];
Scores1 um[NUM_SCORES1];
varand and[NUM_and];
varnand nand[NUM_nand];
varandna andna[NUM_andna];
varandnb andnb[NUM_andnb];
varor or[NUM_or];
varnor nor[NUM_nor];
varorna orna[NUM_orna];
varornb ornb[NUM_ornb];
varnot not[NUM_not];
Explosion explosions[NUM_EXPLOSIONS];

ALLEGRO_SAMPLE *shot = NULL;
ALLEGRO_SAMPLE *boom = NULL;
ALLEGRO_SAMPLE *boom2 = NULL;
ALLEGRO_SAMPLE *song1= NULL;
ALLEGRO_SAMPLE *song2= NULL;
ALLEGRO_SAMPLE *song3= NULL;
ALLEGRO_SAMPLE *gameover = NULL;
ALLEGRO_SAMPLE *allright = NULL;
ALLEGRO_SAMPLE *allwrong = NULL;
ALLEGRO_SAMPLE_INSTANCE *songInstance = NULL;
ALLEGRO_TIMER *tempo = NULL;
ALLEGRO_TIMER *temp_res = NULL;
ALLEGRO_TIMER *movimenta = NULL;

//prototypes
void InitShip(SpaceShip *ship, ALLEGRO_BITMAP *image);
void ResetShipAnimation(SpaceShip *ship, int position);
void DrawShip(SpaceShip *ship);
void MoveShipUp(SpaceShip *ship);
void MoveShipDown(SpaceShip *ship);
void MoveShipLeft(SpaceShip *ship);
void MoveShipRight(SpaceShip *ship);

void InitBadShip(SpaceBadShip *Bship, ALLEGRO_BITMAP *image);
void ResetBadShipAnimation(SpaceBadShip *Bship, int position);
void DrawBadShip(SpaceBadShip *Bship);
void MoveBadShipUp(SpaceBadShip *Bship);
void MoveBadShipDown(SpaceBadShip *Bship);
void MoveBadShipLeft(SpaceBadShip *Bship);
void MoveBadShipRight(SpaceBadShip *Bship);
void MoveBadShipRight2(SpaceBadShip *Bship);

bool CollidShips(SpaceBadShip *Bship, SpaceShip *ship);

void InitBullet(Bullet bullet[], int size);
void DrawBullet(Bullet bullet[], int size);
void FireBullet(Bullet bullet[], int size, SpaceShip *ship);
void UpdateBullet(Bullet bullet[], int size);
void CollideBullet(Bullet bullet[], int bSize, varand and[], int cSize, varnand nand[], int dSize, varandna andna[], int eSize, varandnb andnb[], int fSize, varor or[], int gSize, varnor nor[], int hSize, varorna orna[], int iSize, varornb ornb[], int jSize, varnot not[], int kSize,SpaceShip *ship, Explosion explosions[], int zSize);

void InitAnd(varand and[], int size, ALLEGRO_BITMAP *image);
void DrawAnd(varand and[], int size);
void StartAnd(varand and[], int size);
void UpdateAnd(varand and[], int size);
void CollideAnd(varand and[], int cSize, SpaceShip *ship);

void InitNand(varnand nand[], int size, ALLEGRO_BITMAP *image);
void DrawNand(varnand nand[], int size);
void StartNand(varnand nand[], int size);
void UpdateNand(varnand nand[], int size);
void CollideNand(varnand nand[], int cSize, SpaceShip *ship);

void InitAndna(varandna andna[], int size, ALLEGRO_BITMAP *image);
void DrawAndna(varandna andna[], int size);
void StartAndna(varandna andna[], int size);
void UpdateAndna(varandna andna[], int size);
void CollideAndna(varandna andna[], int cSize, SpaceShip *ship);

void InitAndnb(varandnb andnb[], int size, ALLEGRO_BITMAP *image);
void DrawAndnb(varandnb andnb[], int size);
void StartAndnb(varandnb andnb[], int size);
void UpdateAndnb(varandnb andnb[], int size);
void CollideAndnb(varandnb andnb[], int cSize, SpaceShip *ship);

void InitOr(varor or[], int size, ALLEGRO_BITMAP *image);
void DrawOr(varor or[], int size);
void StartOr(varor or[], int size);
void UpdateOr(varor or[], int size);
void CollideOr(varor or[], int cSize, SpaceShip *ship);

void InitNor(varnor nor[], int size, ALLEGRO_BITMAP *image);
void DrawNor(varnor nor[], int size);
void StartNor(varnor nor[], int size);
void UpdateNor(varnor nor[], int size);
void CollideNor(varnor nor[], int cSize, SpaceShip *ship);

void InitOrna(varorna orna[], int size, ALLEGRO_BITMAP *image);
void DrawOrna(varorna orna[], int size);
void StartOrna(varorna orna[], int size);
void UpdateOrna(varorna orna[], int size);
void CollideOrna(varorna orna[], int cSize, SpaceShip *ship);

void InitOrnb(varornb ornb[], int size, ALLEGRO_BITMAP *image);
void DrawOrnb(varornb ornb[], int size);
void StartOrnb(varornb ornb[], int size);
void UpdateOrnb(varornb ornb[], int size);
void CollideOrnb(varornb ornb[], int cSize, SpaceShip *ship);

void InitNot(varnot not[], int size, ALLEGRO_BITMAP *image);
void DrawNot(varnot not[], int size);
void StartNot(varnot not[], int size);
void UpdateNot(varnot not[], int size);
void CollideNot(varnot not[], int cSize, SpaceShip *ship);

void InitExplosions(Explosion explosions[], int size, ALLEGRO_BITMAP *image);
void DrawExplosions(Explosion explosions[], int size);
void StartExplosions(Explosion explosions[], int size, int x, int y);
void UpdateExplosions(Explosion explosions[], int size);

void InitBackground(Background *brack, float x, float y, float velX, float velY, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image);
void UpdateBackground(Background *back);
void DrawBackground(Background *back);

void ChangeState(int *state, int newState);


int main(void)
{
	//primitive variable
	bool done = false;
	bool redraw = true;
	ACERTOU = false;
	ERROU = false;
	const int FPS = 60;
	int state = -1;

	//object variables
	Background BG;
	Background MG;
	Background FG;

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_FONT *font30 = NULL;
	ALLEGRO_FONT *FontScore30 = NULL;
	ALLEGRO_BITMAP *shipImage;
	ALLEGRO_BITMAP *BshipImage;
	ALLEGRO_BITMAP *expImage;
	ALLEGRO_BITMAP *andImage;
	ALLEGRO_BITMAP *orImage;
	ALLEGRO_BITMAP *notImage;
	ALLEGRO_BITMAP *nandImage;
	ALLEGRO_BITMAP *andnaImage;
	ALLEGRO_BITMAP *andnbImage;
	ALLEGRO_BITMAP *norImage;
	ALLEGRO_BITMAP *ornaImage;
	ALLEGRO_BITMAP *ornbImage;
	ALLEGRO_BITMAP *andErradoImage;
	ALLEGRO_BITMAP *orErradoImage;
	ALLEGRO_BITMAP *notErradoImage;
	ALLEGRO_BITMAP *nandErradoImage;
	ALLEGRO_BITMAP *andnaErradoImage;
	ALLEGRO_BITMAP *andnbErradoImage;
	ALLEGRO_BITMAP *norErradoImage;
	ALLEGRO_BITMAP *ornaErradoImage;
	ALLEGRO_BITMAP *ornbErradoImage;
	ALLEGRO_BITMAP *andCertoImage;
	ALLEGRO_BITMAP *orCertoImage;
	ALLEGRO_BITMAP *nandCertoImage;
	ALLEGRO_BITMAP *andnaCertoImage;
	ALLEGRO_BITMAP *andnbCertoImage;
	ALLEGRO_BITMAP *norCertoImage;
	ALLEGRO_BITMAP *ornaCertoImage;
	ALLEGRO_BITMAP *ornbCertoImage;
	ALLEGRO_BITMAP *title = NULL;
	ALLEGRO_BITMAP *introImage = NULL;
	ALLEGRO_BITMAP *lost = NULL;
	ALLEGRO_BITMAP *CertoErrado = NULL;
	ALLEGRO_BITMAP *scoreImage;
	ALLEGRO_BITMAP *bgImage = NULL;
	ALLEGRO_BITMAP *mgImage = NULL;
	ALLEGRO_BITMAP *fgImage = NULL;


	//Initialization Functions
	if(!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);

	if(!display)
		return -1;


	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();


	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	tempo = al_create_timer(0.30);
	temp_res = al_create_timer(1);
	movimenta = al_create_timer(1);

	shipImage  = al_load_bitmap("SRC/robo.png");
	al_convert_mask_to_alpha(shipImage, al_map_rgb(255, 0, 255));
	BshipImage  = al_load_bitmap("SRC/Brobo.png");
	al_convert_mask_to_alpha(BshipImage, al_map_rgb(255, 0, 255));

	orImage  = al_load_bitmap("SRC/or.png");
	al_convert_mask_to_alpha(orImage, al_map_rgb(0,0,0));
	norImage  = al_load_bitmap("SRC/nor.png");
	al_convert_mask_to_alpha(norImage, al_map_rgb(0,0,0));
	ornaImage  = al_load_bitmap("SRC/orna.png");
	al_convert_mask_to_alpha(ornaImage, al_map_rgb(0,0,0));
	ornbImage  = al_load_bitmap("SRC/ornb.png");
	al_convert_mask_to_alpha(ornbImage, al_map_rgb(0,0,0));
	andImage  = al_load_bitmap("SRC/and.png");
	al_convert_mask_to_alpha(andImage, al_map_rgb(0,0,0));
	nandImage  = al_load_bitmap("SRC/nand.png");
	al_convert_mask_to_alpha(nandImage, al_map_rgb(0,0,0));
	andnaImage  = al_load_bitmap("SRC/andna.png");
	al_convert_mask_to_alpha(andnaImage, al_map_rgb(0,0,0));
	andnbImage  = al_load_bitmap("SRC/andnb.png");
	al_convert_mask_to_alpha(andnbImage, al_map_rgb(0,0,0));
	notImage = al_load_bitmap("SRC/not.png");
	al_convert_mask_to_alpha(notImage, al_map_rgb(0,0,0));

	orErradoImage  = al_load_bitmap("SRC/orErrado.png");
	al_convert_mask_to_alpha(orErradoImage, al_map_rgb(255,255,255));
	norErradoImage  = al_load_bitmap("SRC/norErrado.png");
	al_convert_mask_to_alpha(norErradoImage, al_map_rgb(255,255,255));
	ornaErradoImage  = al_load_bitmap("SRC/ornaErrado.png");
	al_convert_mask_to_alpha(ornaErradoImage, al_map_rgb(255,255,255));
	ornbErradoImage  = al_load_bitmap("SRC/ornbErrado.png");
	al_convert_mask_to_alpha(ornbErradoImage, al_map_rgb(255,255,255));
	andErradoImage  = al_load_bitmap("SRC/andErrado.png");
	al_convert_mask_to_alpha(andErradoImage, al_map_rgb(255,255,255));
	nandErradoImage  = al_load_bitmap("SRC/nandErrado.png");
	al_convert_mask_to_alpha(nandErradoImage, al_map_rgb(255,255,255));
	andnaErradoImage  = al_load_bitmap("SRC/andnaErrado.png");
	al_convert_mask_to_alpha(andnaErradoImage, al_map_rgb(255,255,255));
	andnbErradoImage  = al_load_bitmap("SRC/andnbErrado.png");
	al_convert_mask_to_alpha(andnbErradoImage, al_map_rgb(255,255,255));
	notErradoImage = al_load_bitmap("SRC/notErrado.png");
	al_convert_mask_to_alpha(notErradoImage, al_map_rgb(255,255,255));
	orCertoImage  = al_load_bitmap("SRC/orCerto.png");
	al_convert_mask_to_alpha(orCertoImage, al_map_rgb(255,255,255));
	norCertoImage  = al_load_bitmap("SRC/norCerto.png");
	al_convert_mask_to_alpha(norCertoImage, al_map_rgb(255,255,255));
	ornaCertoImage  = al_load_bitmap("SRC/ornaCerto.png");
	al_convert_mask_to_alpha(ornaCertoImage, al_map_rgb(255,255,255));
	ornbCertoImage  = al_load_bitmap("SRC/ornbCerto.png");
	al_convert_mask_to_alpha(ornbCertoImage, al_map_rgb(255,255,255));
	andCertoImage  = al_load_bitmap("SRC/andCerto.png");
	al_convert_mask_to_alpha(andCertoImage, al_map_rgb(255,255,255));
	nandCertoImage  = al_load_bitmap("SRC/nandCerto.png");
	al_convert_mask_to_alpha(nandCertoImage, al_map_rgb(255,255,255));
	andnaCertoImage  = al_load_bitmap("SRC/andnaCerto.png");
	al_convert_mask_to_alpha(andnaCertoImage, al_map_rgb(255,255,255));
	andnbCertoImage  = al_load_bitmap("SRC/andnbCerto.png");
	al_convert_mask_to_alpha(andnbCertoImage, al_map_rgb(255,255,255));

	expImage = al_load_bitmap("SRC/explosion_3_40_128.png");

	title = al_load_bitmap("SRC/Inicial.png");
	introImage = al_load_bitmap("SRC/HowTo.png");
	lost = al_load_bitmap("SRC/GameOver_2.png");
	scoreImage = al_load_bitmap("SRC/score.png");
	al_convert_mask_to_alpha(scoreImage, al_map_rgb(255, 0, 255));

	bgImage = al_load_bitmap("SRC/BG.png");
	mgImage = al_load_bitmap("SRC/starFG.png");
	al_convert_mask_to_alpha(mgImage, al_map_rgb(255,255,255));
	fgImage = al_load_bitmap("SRC/starFG.png");
	al_convert_mask_to_alpha(fgImage, al_map_rgb(255,255,255));

	al_reserve_samples(3);

	shot = al_load_sample("SRC/hit.wav");
	boom = al_load_sample("SRC/explosion.wav");
	song1 = al_load_sample("SRC/starwars.wav");
	song2 = al_load_sample("SRC/welcomem.wav");
	boom2 = al_load_sample("SRC/explosion.wav");
	gameover = al_load_sample("SRC/losesound.WAV");
	allright = al_load_sample("SRC/coin.wav");
	allwrong = al_load_sample("SRC/error.wav");

	al_set_window_title(display, "Pinguelogic");


	songInstance = al_create_sample_instance(song1);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());


	srand(time(NULL));

	ChangeState(&state, TITLE);

	InitShip(&ship, shipImage);
	InitBadShip(&Bship, BshipImage);
	InitBullet(bullets, NUM_BULLETS);
	InitExplosions(explosions, NUM_EXPLOSIONS, expImage);
	InitAnd(and, NUM_and, andImage);
	InitNand(nand, NUM_nand, nandImage);
	InitAndna(andna, NUM_andna, andnaImage);
	InitAndnb(andnb, NUM_andnb, andnbImage);
	InitOr(or, NUM_or, orImage);
	InitNor(nor, NUM_nor, norImage);
	InitOrna(orna, NUM_orna, ornaImage);
	InitOrnb(ornb, NUM_ornb, ornbImage);
	InitNot(not, NUM_not, notImage);

	InitBackground(&BG, 0, 0, 1, 0, 1197, 600, -1, 1, bgImage);
	InitBackground(&MG, 0, 0, 3, 0, 1600, 600, -1, 1, mgImage);
	InitBackground(&FG, 0, 0, 5, 0, 800, 600, -1, 1, fgImage);

	font18 = al_load_font("SRC/pdark.ttf", 18, 0);
	font30 = al_load_font("SRC/pdark.ttf", 30, 0);
	FontScore30 = al_load_font("SRC/pdark.ttf", 65, 0);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(movimenta));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(tempo));
	al_register_event_source(event_queue, al_get_timer_event_source(temp_res));

	al_start_timer(timer);
	al_start_timer(tempo);
	al_start_timer(movimenta);


	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			if(keys[UP])
				MoveShipUp(&ship);
			else if(keys[DOWN])
				MoveShipDown(&ship);
			else
				ResetShipAnimation(&ship, 1);

			if(keys[UP])
				MoveBadShipUp(&Bship);
			else if(keys[DOWN])
			    MoveBadShipDown(&Bship);
			else
				ResetBadShipAnimation(&Bship,1);

			if(state == TITLE)
			{}
			else if (state == INTRO)
			{}
			else if(state == PLAYING)
			{
				UpdateBackground(&BG);
				UpdateBackground(&MG);
				UpdateBackground(&FG);

// Inicialização dos Binarios e Portas
				if (Binarios)
								{
									rndA = rand()%2;
									rndB = rand()%2;
									rndS = rand()%2;

									Binarios = false;
								}

// Validação de Acertos e Erros

				if (validar_and || validar_andna || validar_andnb || validar_orna || validar_ornb || validar_or || validar_nand || validar_nor || validar_not)
				{
					Resposta = true;
					if (rndA == 0 && rndB == 0 && rndS == 0 )
					{
						if (validar_and || validar_andna || validar_andnb || validar_or )
						{
							al_start_timer(temp_res);
							ACERTOU = true;
							ship.score += 50;
							al_play_sample(allright, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

						}
						else if (validar_nand || validar_nor || validar_not || validar_orna || validar_ornb)
						{
							al_start_timer(temp_res);
							ERROU = true;
							al_play_sample(allwrong, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						}
					}
					if (rndA == 1 && rndB == 1 && rndS == 0 )
					{
						if (validar_nand || validar_andna || validar_andnb || validar_nor )
						{
							al_start_timer(temp_res);
							ACERTOU = true;
							ship.score += 50;
							al_play_sample(allright, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						}
						else if (validar_and || validar_not || validar_or || validar_orna || validar_ornb)
						{
							al_start_timer(temp_res);
							ERROU = true;
							al_play_sample(allwrong, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

						}
					}

					if (rndA == 0 && rndB == 0 && rndS == 1 )
					{
						if ( validar_nand || validar_nor || validar_orna || validar_ornb )
						{
							al_start_timer(temp_res);
							ACERTOU = true;
							ship.score += 50;
							al_play_sample(allright, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						}
						else if (validar_and || validar_not || validar_andna || validar_andnb || validar_or )
						{
							al_start_timer(temp_res);
							ERROU = true;
							al_play_sample(allwrong, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

						}
					}

					if (rndA == 1 && rndB == 1 && rndS == 1 )
					{
						if (validar_and || validar_orna || validar_ornb || validar_or)
						{
							al_start_timer(temp_res);
							ACERTOU = true;
							ship.score += 50;
							al_play_sample(allright, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						}
						else if (validar_nand || validar_nor || validar_not || validar_andna || validar_andnb)
						{
							al_start_timer(temp_res);
							ERROU = true;
							al_play_sample(allwrong, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

						}
					}

					if (rndA == 0 && rndB == 1 && rndS == 0 )
					{
						if (validar_and || validar_andnb || validar_ornb || validar_nor)
						{
							al_start_timer(temp_res);
							ACERTOU = true;
							ship.score += 50;
							al_play_sample(allright, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						}
						else if (validar_nand || validar_or || validar_orna  || validar_not || validar_andna)
						{
							al_start_timer(temp_res);
							ERROU = true;
							al_play_sample(allwrong, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

						}
					}

					if (rndA == 1 && rndB == 0 && rndS == 0 )
					{
						if (validar_and || validar_andna || validar_orna || validar_nor)
						{
							al_start_timer(temp_res);
							ACERTOU = true;
							ship.score += 50;
							al_play_sample(allright, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						}
						else if (validar_nand || validar_or || validar_ornb || validar_not || validar_andnb)
						{
							al_start_timer(temp_res);
							ERROU = true;
							al_play_sample(allwrong, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

						}
					}

					if (rndA == 0 && rndB == 1 && rndS == 1 )
					{
						if (validar_nand || validar_andna || validar_or || validar_orna)
						{
							al_start_timer(temp_res);
							ACERTOU = true;
							ship.score += 50;
							al_play_sample(allright, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						}
						else if (validar_and || validar_ornb || validar_not || validar_andnb || validar_nor)
						{
							al_start_timer(temp_res);
							ERROU = true;
							al_play_sample(allwrong, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

						}
					}

					if (rndA == 1 && rndB == 0 && rndS == 1 )
					{
						if (validar_nand || validar_andnb || validar_or || validar_ornb)
						{
							al_start_timer(temp_res);
							ACERTOU = true;
							ship.score += 50;
							al_play_sample(allright, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						}
						else if (validar_and || validar_orna || validar_not || validar_andna || validar_nor)
						{
							al_start_timer(temp_res);
							ERROU = true;
							al_play_sample(allwrong, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

						}
					}
					if(ACERTOU && validar_and)
						CertoErrado = andCertoImage;
					if(ACERTOU && validar_nand)
						CertoErrado = nandCertoImage;
					if(ACERTOU && validar_andna)
						CertoErrado = andnaCertoImage;
					if(ACERTOU && validar_andnb)
						CertoErrado = andnbCertoImage;
					if(ACERTOU && validar_or)
						CertoErrado = orCertoImage;
					if(ACERTOU && validar_nor)
						CertoErrado = norCertoImage;
					if(ACERTOU && validar_orna)
						CertoErrado = ornaCertoImage;
					if(ACERTOU && validar_ornb)
						CertoErrado = ornbCertoImage;
					if(ERROU && validar_and)
						CertoErrado = andErradoImage;
					if(ERROU && validar_nand)
						CertoErrado = nandErradoImage;
					if(ERROU && validar_andna)
						CertoErrado = andnaErradoImage;
					if(ERROU && validar_andnb)
						CertoErrado = andnbErradoImage;
					if(ERROU && validar_or)
						CertoErrado = orErradoImage;
					if(ERROU && validar_nor)
						CertoErrado = norErradoImage;
					if(ERROU && validar_orna)
						CertoErrado = ornaErradoImage;
					if(ERROU && validar_ornb)
						CertoErrado = ornbErradoImage;
					if(ERROU && validar_not)
						CertoErrado = notErradoImage;
					Binarios = true;
					validar_nand = false;
					validar_nor = false;
					validar_not = false;
					validar_and = false;
					validar_andna = false;
					validar_andnb = false;
					validar_or = false;
					validar_orna = false;
					validar_ornb = false;
				}

				UpdateExplosions(explosions, NUM_EXPLOSIONS);
				UpdateBullet(bullets, NUM_BULLETS);
				StartAnd(and, NUM_and);
				StartNand(nand, NUM_nand);
				StartAndna(andna, NUM_andna);
				StartAndnb(andnb, NUM_andnb);
				StartOr(or, NUM_or);
				StartNor(nor, NUM_nor);
				StartOrna(orna, NUM_orna);
				StartOrnb(ornb, NUM_ornb);
				StartNot(not, NUM_not);
				UpdateAnd(and, NUM_and);
				UpdateNand(nand, NUM_nand);
				UpdateAndna(andna, NUM_andna);
				UpdateAndnb(andnb, NUM_andnb);
				UpdateOr(or, NUM_or);
				UpdateNor(nor, NUM_nor);
				UpdateOrna(orna, NUM_orna);
				UpdateOrnb(ornb, NUM_ornb);
				UpdateNot(not, NUM_not);
				CollideBullet(bullets, NUM_BULLETS, and, NUM_and, nand, NUM_nand, andna, NUM_andna, andnb, NUM_andnb, or, NUM_or, nor, NUM_nor, orna, NUM_orna, ornb, NUM_ornb, not, NUM_not, &ship, explosions, NUM_EXPLOSIONS);
				CollidShips(&Bship, &ship);
				CollideAnd(and,NUM_and, &ship);
				CollideNand(nand,NUM_nand, &ship);
				CollideAndna(andna, NUM_andna, &ship);
				CollideAndnb(andnb, NUM_andnb, &ship);
				CollideOr(or, NUM_or, &ship);
				CollideNor(nor, NUM_nor, &ship);
				CollideOrna(orna, NUM_orna, &ship);
				CollideOrnb(ornb, NUM_ornb, &ship);
				CollideNot(not, NUM_not, &ship);

				if (CollidShips(&Bship, &ship))
					ChangeState(&state, LOST);
			}
			else if(state == LOST)
			{}
			// Movimentação dos robos em caso de acerto e erro
			if (ev.timer.source == tempo)
			{
				if (ACERTOU)
				{
					if ((ship).x < 399)
						MoveShipRight(&ship);
					else
						MoveBadShipLeft(&Bship);
					ACERTOU = false;
				}

				if (ERROU)
				{
					MoveBadShipRight(&Bship);
					ERROU = false;

				}
			}
		}
		if (ev.timer.source == movimenta)
		{
			MoveBadShipRight2(&Bship);
		}
		if (ev.timer.source == temp_res)
		{
			if (Resposta)
			{
			Resposta = false;
			al_stop_timer(temp_res);
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				if(state == TITLE)
					ChangeState(&state, INTRO);
				else if(state == INTRO)
					ChangeState(&state, PLAYING);
				else if(state ==PLAYING)
					FireBullet(bullets, NUM_BULLETS, &ship);
				else if(state == LOST)
					ChangeState(&state, PLAYING);
				break;
			}

		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}

		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			if(state == TITLE)
			{
				al_draw_bitmap(title, 0, 0, 0);
			}
			else if (state == INTRO)
			{
				al_draw_bitmap(introImage, 0, 0, 0);
			}
			else if(state == PLAYING)
			{

				DrawBackground(&BG);
				DrawBackground(&MG);
				DrawBackground(&FG);
				DrawShip(&ship);
				DrawBullet(bullets, NUM_BULLETS);
				DrawAnd(and, NUM_and);
				DrawNand(nand, NUM_nand);
				DrawAndna(andna, NUM_andna);
				DrawAndnb(andnb, NUM_andnb);
				DrawOr(or, NUM_or);
				DrawNor(nor, NUM_nor);
				DrawOrna(orna, NUM_orna);
				DrawOrnb(ornb, NUM_ornb);
				DrawNot(not, NUM_not);
				DrawExplosions(explosions, NUM_EXPLOSIONS);
				DrawBadShip(&Bship);
				al_draw_textf(font30, al_map_rgb(255,255,255), 80, 23, 0, "Score %i", ship.score);
				//Desenho do retangulo no canto inferior direito e dados dentro dele
				al_draw_filled_rectangle((WIDTH - 225),(HEIGHT - 110), (WIDTH-75), (HEIGHT - 10), al_map_rgb(255,255,255));
				al_draw_line((WIDTH - 260),(HEIGHT - 40), (WIDTH-225), (HEIGHT - 40), al_map_rgb(255,255,255),2);
				al_draw_line((WIDTH - 260),(HEIGHT - 80), (WIDTH-225), (HEIGHT - 80), al_map_rgb(255,255,255),2);
				al_draw_line((WIDTH - 40),(HEIGHT - 60), (WIDTH-75), (HEIGHT - 60), al_map_rgb(255,255,255),2);
				al_draw_circle((WIDTH - 280),(HEIGHT - 40), 20, al_map_rgb(255,255,255),2);
				al_draw_circle((WIDTH - 280),(HEIGHT - 80), 20, al_map_rgb(255,255,255),2);
				al_draw_circle((WIDTH - 20),(HEIGHT - 60), 20, al_map_rgb(255,255,255),2);
				al_draw_textf(font30, al_map_rgb(255,255,255), (WIDTH - 280), (HEIGHT - 95) , 1, "%i", rndA);
				al_draw_textf(font30, al_map_rgb(255,255,255), (WIDTH - 280), (HEIGHT - 55) , 1, "%i", rndB);
				al_draw_textf(font30, al_map_rgb(255,255,255), (WIDTH - 20), (HEIGHT - 75), 1, "%i", rndS);
				al_draw_bitmap(scoreImage,0,0,0);


				if (Resposta)
				{
				al_draw_bitmap(CertoErrado,(WIDTH - 220),(HEIGHT - 105),0);
				}

			}


			else if(state == LOST)
			{
				al_draw_bitmap(lost, 0, 0, 0);

				al_draw_textf(FontScore30, al_map_rgb(255,255,255), 900, 400 , ALLEGRO_ALIGN_RIGHT, "Score Final %i", ship.score);

			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	al_destroy_sample(shot);
	al_destroy_sample(boom);
	al_destroy_sample(song1);
	al_destroy_sample(song2);
	al_destroy_sample(boom2);
	al_destroy_sample(allright);
	al_destroy_sample(allwrong);
	al_destroy_sample_instance(songInstance);
	al_destroy_bitmap(bgImage);
	al_destroy_bitmap(mgImage);
	al_destroy_bitmap(fgImage);
	al_destroy_bitmap(scoreImage);
	al_destroy_bitmap(title);
	al_destroy_bitmap(introImage);
	al_destroy_bitmap(lost);
	al_destroy_bitmap(expImage);
	al_destroy_bitmap(shipImage);
	al_destroy_bitmap(BshipImage);
	al_destroy_bitmap(andImage);
	al_destroy_bitmap(andnaImage);
	al_destroy_bitmap(andnbImage);
	al_destroy_bitmap(nandImage);
	al_destroy_bitmap(orImage);
	al_destroy_bitmap(ornaImage);
	al_destroy_bitmap(ornbImage);
	al_destroy_bitmap(norImage);
	al_destroy_bitmap(notImage);
	al_destroy_bitmap(andErradoImage);
	al_destroy_bitmap(andnaErradoImage);
	al_destroy_bitmap(andnbErradoImage);
	al_destroy_bitmap(nandErradoImage);
	al_destroy_bitmap(orErradoImage);
	al_destroy_bitmap(ornaErradoImage);
	al_destroy_bitmap(ornbErradoImage);
	al_destroy_bitmap(norErradoImage);
	al_destroy_bitmap(notErradoImage);
	al_destroy_bitmap(andCertoImage);
	al_destroy_bitmap(andnaCertoImage);
	al_destroy_bitmap(andnbCertoImage);
	al_destroy_bitmap(nandCertoImage);
	al_destroy_bitmap(orCertoImage);
	al_destroy_bitmap(ornaCertoImage);
	al_destroy_bitmap(ornbCertoImage);
	al_destroy_bitmap(norCertoImage);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_timer(temp_res);
	al_destroy_timer(tempo);
	al_destroy_timer(movimenta);
	al_destroy_font(font18);
	al_destroy_display(display);

	return 0;
}

void InitShip(SpaceShip *ship, ALLEGRO_BITMAP *image)
{
	(*ship).x = 200;
	(*ship).y = HEIGHT / 2;
	(*ship).ID = PLAYER;
	(*ship).lives = 300;
	(*ship).speed = 6;
	(*ship).boundx = 30;
	(*ship).boundy = 30;
	(*ship).score = 0;

	(*ship).maxFrame = 3;
	(*ship).curFrame = 0;
	(*ship).frameCount = 0;
	(*ship).frameDelay = 50;
	(*ship).frameWidth = 52;
	(*ship).frameHeight = 95;
	(*ship).animationColumns = 3;
	(*ship).animationDirection = 1;

	(*ship).animationRow = 1;

	if(image != NULL)
		(*ship).image = image;
}

void ResetShipAnimation(SpaceShip *ship, int position)
{
	if(position == 1)
		(*ship).animationRow = 1;
	else
		(*ship).curFrame = 0;
}

void DrawShip(SpaceShip *ship)
{
	int fx =((*ship).curFrame % (*ship).animationColumns) * (*ship).frameWidth;
	int fy = (*ship).animationRow * (*ship).frameHeight;

	al_draw_bitmap_region((*ship).image, fx, fy, (*ship).frameWidth,
		(*ship).frameHeight, (*ship).x - (*ship).frameWidth / 2, (*ship).y - (*ship).frameHeight / 2, 0);

}

void MoveShipUp(SpaceShip *ship)
{
	(*ship).animationRow = 0;
	(*ship).y -= (*ship).speed;
	if((*ship).y < 0)
		(*ship).y = 0;
}

void MoveShipDown(SpaceShip *ship)
{
	(*ship).animationRow = 2;
	(*ship).y += (*ship).speed;
	if((*ship).y > HEIGHT)
		(*ship).y = HEIGHT;
}

void MoveShipLeft(SpaceShip *ship)
{
	(*ship).curFrame = 2;
	(*ship).x -= 100;
	if((*ship).x < 100)
		(*ship).x = 100;
	(*ship).animationRow = 1;
	(*ship).curFrame = 0;

}

void MoveShipRight(SpaceShip *ship)
{
	int aux;
	(*ship).curFrame = 1;
	aux = (*ship).x + 100;
	(*ship).x += 50;
	if((*ship).x > aux)
		(*ship).x = aux;
	 ACERTOU = false;
 	(*ship).animationRow = 1;
	(*ship).curFrame = 0;

}


void InitBadShip(SpaceBadShip *Bship, ALLEGRO_BITMAP *image)
{
	(*Bship).x = 40;
	(*Bship).y = HEIGHT / 2;
	(*Bship).live = false;
	(*Bship).ID = BAD;
	(*Bship).speed = 6;
	(*Bship).boundx = 10;
	(*Bship).boundy = 12;

	(*Bship).maxFrame = 3;
	(*Bship).curFrame = 0;
	(*Bship).frameCount = 0;
	(*Bship).frameDelay = 50;
	(*Bship).frameWidth = 93;
	(*Bship).frameHeight = 100;
	(*Bship).animationColumns = 3;
	(*Bship).animationDirection = 1;

	(*Bship).animationRow = 1;

	if(image != NULL)
		(*Bship).image = image;
}

void ResetBadShipAnimation(SpaceBadShip *Bship, int position)
{
	if(position == 1)
		(*Bship).animationRow = 1;
	else
		(*Bship).curFrame = 0;
}

void DrawBadShip(SpaceBadShip *Bship)
{
	int fx =((*Bship).curFrame % (*Bship).animationColumns) * (*Bship).frameWidth;
	int fy = (*Bship).animationRow * (*Bship).frameHeight;

	al_draw_bitmap_region((*Bship).image, fx, fy, (*Bship).frameWidth,
		(*Bship).frameHeight, (*Bship).x - (*Bship).frameWidth / 2, (*Bship).y - (*Bship).frameHeight / 2, 0);

}

void MoveBadShipUp(SpaceBadShip *Bship)
{
	(*Bship).animationRow = 0;
	(*Bship).y -= (*Bship).speed;
	if((*Bship).y < 0)
		(*Bship).y = 0;
}

void MoveBadShipDown(SpaceBadShip *Bship)
{
	(*Bship).animationRow = 2;
	(*Bship).y += (*Bship).speed;
	if((*Bship).y > HEIGHT)
		(*Bship).y = HEIGHT;
}
void MoveBadShipLeft(SpaceBadShip *Bship)
{
	(*Bship).curFrame = 2;
	(*Bship).x -= 50;
	(*Bship).animationRow = 1;
	(*Bship).curFrame = 0;

}

void MoveBadShipRight(SpaceBadShip *Bship)
{
	(*Bship).curFrame = 1;
	(*Bship).x += 25;
	(*Bship).animationRow = 1;
	(*Bship).curFrame = 0;

}
void MoveBadShipRight2(SpaceBadShip *Bship)
{
	(*Bship).curFrame = 1;
	(*Bship).x += 4;
	(*Bship).animationRow = 1;
	(*Bship).curFrame = 0;
}




void InitBullet(Bullet bullet[], int size)
{
	for(int i = 0; i < size; i++)
	{
		bullet[i].ID = BULLET;
		bullet[i].speed = 10;
		bullet[i].live = false;
	}
}

void DrawBullet(Bullet bullet[], int size)
{
	for( int i = 0; i < size; i++)
	{
		if(bullet[i].live)
			al_draw_filled_circle(bullet[i].x, bullet[i].y, 2, al_map_rgb(255, 255, 255));
	}
}

void FireBullet(Bullet bullet[], int size, SpaceShip *ship)
{
	for( int i = 0; i < size; i++)
	{
		if(!bullet[i].live)
		{
			bullet[i].x = (*ship).x + 17;
			bullet[i].y = (*ship).y;
			bullet[i].live = true;

			al_play_sample(shot, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

			break;
		}
	}
}

void UpdateBullet(Bullet bullet[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(bullet[i].live)
		{
			bullet[i].x += bullet[i].speed;
			if(bullet[i].x > WIDTH)
				bullet[i].live = false;
		}
	}
}

void CollideBullet(Bullet bullet[], int bSize, varand and[], int cSize, varnand nand[], int dSize, varandna andna[], int eSize, varandnb andnb[], int fSize, varor or[], int gSize, varnor nor[], int hSize, varorna orna[], int iSize, varornb ornb[], int jSize, varnot not[], int kSize, SpaceShip *ship, Explosion explosions[], int zSize)
{
	for(int i = 0; i < bSize; i++)
	{
		if(bullet[i].live)
		{
			for(int j =0; j < cSize; j++)
			{
				if(and[j].live)
				{
					if(bullet[i].x > (and[j].x - and[j].boundx) &&
						bullet[i].x < (and[j].x + and[j].boundx) &&
						bullet[i].y > (and[j].y - and[j].boundy) &&
						bullet[i].y < (and[j].y + and[j].boundy))
					{
						bullet[i].live = false;
						and[j].live = false;

						StartExplosions(explosions, zSize, bullet[i].x, bullet[i].y);

						al_play_sample(boom, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					}
				}
			}

			for(int j =0; j < dSize; j++)
						{
							if(nand[j].live)
							{
								if(bullet[i].x > (nand[j].x - nand[j].boundx) &&
									bullet[i].x < (nand[j].x + nand[j].boundx) &&
									bullet[i].y > (nand[j].y - nand[j].boundy) &&
									bullet[i].y < (nand[j].y + nand[j].boundy))
								{
									bullet[i].live = false;
									nand[j].live = false;

									StartExplosions(explosions, zSize, bullet[i].x, bullet[i].y);

									al_play_sample(boom, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
								}
							}
						}
			for(int j =0; j < eSize; j++)
						{
							if(andna[j].live)
							{
								if(bullet[i].x > (andna[j].x - andna[j].boundx) &&
									bullet[i].x < (andna[j].x + andna[j].boundx) &&
									bullet[i].y > (andna[j].y - andna[j].boundy) &&
									bullet[i].y < (andna[j].y + andna[j].boundy))
								{
									bullet[i].live = false;
									andna[j].live = false;

									StartExplosions(explosions, zSize, bullet[i].x, bullet[i].y);

									al_play_sample(boom, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
								}
							}
						}
			for(int j =0; j < fSize; j++)
						{
							if(andnb[j].live)
							{
								if(bullet[i].x > (andnb[j].x - andnb[j].boundx) &&
									bullet[i].x < (andnb[j].x + andnb[j].boundx) &&
									bullet[i].y > (andnb[j].y - andnb[j].boundy) &&
									bullet[i].y < (andnb[j].y + andnb[j].boundy))
								{
									bullet[i].live = false;
									andnb[j].live = false;

									StartExplosions(explosions, zSize, bullet[i].x, bullet[i].y);

									al_play_sample(boom, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
								}
							}
						}
			for(int j =0; j < gSize; j++)
						{
							if(or[j].live)
							{
								if(bullet[i].x > (or[j].x - or[j].boundx) &&
									bullet[i].x < (or[j].x + or[j].boundx) &&
									bullet[i].y > (or[j].y - or[j].boundy) &&
									bullet[i].y < (or[j].y + or[j].boundy))
								{
									bullet[i].live = false;
									or[j].live = false;

									StartExplosions(explosions, zSize, bullet[i].x, bullet[i].y);

									al_play_sample(boom, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
								}
							}
						}
			for(int j =0; j < hSize; j++)
						{
							if(nor[j].live)
							{
								if(bullet[i].x > (nor[j].x - nor[j].boundx) &&
									bullet[i].x < (nor[j].x + nor[j].boundx) &&
									bullet[i].y > (nor[j].y - nor[j].boundy) &&
									bullet[i].y < (nor[j].y + nor[j].boundy))
								{
									bullet[i].live = false;
									nor[j].live = false;

									StartExplosions(explosions, zSize, bullet[i].x, bullet[i].y);

									al_play_sample(boom, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
								}
							}
						}
			for(int j =0; j < iSize; j++)
						{
							if(orna[j].live)
							{
								if(bullet[i].x > (orna[j].x - orna[j].boundx) &&
									bullet[i].x < (orna[j].x + orna[j].boundx) &&
									bullet[i].y > (orna[j].y - orna[j].boundy) &&
									bullet[i].y < (orna[j].y + orna[j].boundy))
								{
									bullet[i].live = false;
									orna[j].live = false;

									StartExplosions(explosions, zSize, bullet[i].x, bullet[i].y);

									al_play_sample(boom, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
								}
							}
						}
			for(int j =0; j < jSize; j++)
						{
							if(ornb[j].live)
							{
								if(bullet[i].x > (ornb[j].x - ornb[j].boundx) &&
									bullet[i].x < (ornb[j].x + ornb[j].boundx) &&
									bullet[i].y > (ornb[j].y - ornb[j].boundy) &&
									bullet[i].y < (ornb[j].y + ornb[j].boundy))
								{
									bullet[i].live = false;
									ornb[j].live = false;

									StartExplosions(explosions, zSize, bullet[i].x, bullet[i].y);

									al_play_sample(boom, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
								}
							}
						}
			for(int j =0; j < kSize; j++)
						{
							if(not[j].live)
							{
								if(bullet[i].x > (not[j].x - not[j].boundx) &&
									bullet[i].x < (not[j].x + not[j].boundx) &&
									bullet[i].y > (not[j].y - not[j].boundy) &&
									bullet[i].y < (not[j].y + not[j].boundy))
								{
									bullet[i].live = false;
									not[j].live = false;

									StartExplosions(explosions, zSize, bullet[i].x, bullet[i].y);

									al_play_sample(boom, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
								}
							}
						}
		}
	}
}

void InitAnd(varand and[], int size, ALLEGRO_BITMAP *image)
{
	for(int i = 0; i < size; i++)
	{
		and[i].ID = AND;
		and[i].live = false;
		and[i].speed = 3;
		and[i].boundx = 35;
		and[i].boundy = 35;

		and[i].maxFrame = 2;
		and[i].curFrame = 0;
		and[i].frameCount = 0;
		and[i].frameDelay = 30;
		and[i].frameWidth = 54;
		and[i].frameHeight = 30;
		and[i].animationColumns = 2;
		and[i].animationDirection = 1;

		if(image != NULL)
		{
			and[i].image = image;
		}
	}
}

void DrawAnd(varand and[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(and[i].live)
		{
			int fx = (and[i].curFrame % and[i].animationColumns) * and[i].frameWidth;
			int fy = (and[i].curFrame / and[i].animationColumns) * and[i].frameHeight;

			al_draw_bitmap_region(and[i].image, fx, fy, and[i].frameWidth,
				and[i].frameHeight, and[i].x - and[i].frameWidth / 2, and[i].y - and[i].frameHeight / 2, 0);

		}
	}
}

void StartAnd(varand and[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(!and[i].live)
		{
			if(rand() % 500 == 0)
			{
				and[i].live = true;
				and[i].y = rand() % HEIGHT;
				and[i].x = WIDTH;

				break;
			}
		}
	}
}

void UpdateAnd(varand and[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(and[i].live)
		{
			and[i].curFrame = 0;
			and[i].x -= and[i].speed;
		}
	}
}


void CollideAnd(varand and[], int cSize, SpaceShip *ship)
{
	for(int i = 0; i < cSize; i++)
	{
		if(and[i].live)
		{
			if(and[i].x - and[i].boundx < (*ship).x + (*ship).boundx &&
				and[i].x + and[i].boundx > (*ship).x - (*ship).boundx &&
				and[i].y - and[i].boundy < (*ship).y + (*ship).boundy &&
				and[i].y + and[i].boundy > (*ship).y - (*ship).boundy)
			{
				and[i].live = false;
				validar_and = true;
			}
			else if(and[i].x < 0)
			{
				and[i].live = false;

			}
		}
	}
}

void InitNand(varnand nand[], int size, ALLEGRO_BITMAP *image)
{
	for(int i = 0; i < size; i++)
	{
		nand[i].ID = NAND;
		nand[i].live = false;
		nand[i].speed = 3;
		nand[i].boundx = 35;
		nand[i].boundy = 35;

		nand[i].maxFrame = 2;
		nand[i].curFrame = 0;
		nand[i].frameCount = 0;
		nand[i].frameDelay = 30;
		nand[i].frameWidth = 54;
		nand[i].frameHeight = 30	;
		nand[i].animationColumns = 2;
		nand[i].animationDirection = 1;

		if(image != NULL)
		{
			nand[i].image = image;
		}
	}
}

void DrawNand(varnand nand[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(nand[i].live)
		{
			int fx = (nand[i].curFrame % nand[i].animationColumns) * nand[i].frameWidth;
			int fy = (nand[i].curFrame / nand[i].animationColumns) * nand[i].frameHeight;

			al_draw_bitmap_region(nand[i].image, fx, fy, nand[i].frameWidth,
				nand[i].frameHeight, nand[i].x - nand[i].frameWidth / 2, nand[i].y - nand[i].frameHeight / 2, 0);

		}
	}
}

void StartNand(varnand nand[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(!nand[i].live)
		{
			if(rand() % 500 == 0)
			{
				nand[i].live = true;
				nand[i].y = rand() % HEIGHT;
				nand[i].x = WIDTH ;

				break;
			}
		}
	}
}

void UpdateNand(varnand nand[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(nand[i].live)
		{
			nand[i].curFrame = 0;
			nand[i].x -= nand[i].speed;
		}
	}
}


void CollideNand(varnand nand[], int cSize, SpaceShip *ship)
{
	for(int i = 0; i < cSize; i++)
	{
		if(nand[i].live)
		{
			if(nand[i].x - nand[i].boundx < (*ship).x + (*ship).boundx &&
				nand[i].x + nand[i].boundx > (*ship).x - (*ship).boundx &&
				nand[i].y - nand[i].boundy < (*ship).y + (*ship).boundy &&
				nand[i].y + nand[i].boundy > (*ship).y - (*ship).boundy)
			{
				nand[i].live = false;
				validar_nand = true;
			}
			else if(nand[i].x < 0)
			{
				nand[i].live = false;
			}
		}
	}
}

void InitAndna(varandna andna[], int size, ALLEGRO_BITMAP *image)
{
	for(int i = 0; i < size; i++)
	{
		andna[i].ID = ANDNA;
		andna[i].live = false;
		andna[i].speed = 3;
		andna[i].boundx = 35;
		andna[i].boundy = 35;

		andna[i].maxFrame = 2;
		andna[i].curFrame = 0;
		andna[i].frameCount = 0;
		andna[i].frameDelay = 30;
		andna[i].frameWidth = 54;
		andna[i].frameHeight = 30	;
		andna[i].animationColumns = 2;
		andna[i].animationDirection = 1;

		if(image != NULL)
		{
			andna[i].image = image;
		}
	}
}

void DrawAndna(varandna andna[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(andna[i].live)
		{
			int fx = (andna[i].curFrame % andna[i].animationColumns) * andna[i].frameWidth;
			int fy = (andna[i].curFrame / andna[i].animationColumns) * andna[i].frameHeight;

			al_draw_bitmap_region(andna[i].image, fx, fy, andna[i].frameWidth,
				andna[i].frameHeight, andna[i].x - andna[i].frameWidth / 2, andna[i].y - andna[i].frameHeight / 2, 0);

		}
	}
}

void StartAndna(varandna andna[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(!andna[i].live)
		{
			if(rand() % 500 == 0)
			{
				andna[i].live = true;
				andna[i].y = rand() % HEIGHT;
				andna[i].x = WIDTH ;

				break;
			}
		}
	}
}

void UpdateAndna(varandna andna[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(andna[i].live)
		{
			andna[i].curFrame = 0;
			andna[i].x -= andna[i].speed;
		}
	}
}


void CollideAndna(varandna andna[], int cSize, SpaceShip *ship)
{
	for(int i = 0; i < cSize; i++)
	{
		if(andna[i].live)
		{
			if(andna[i].x - andna[i].boundx < (*ship).x + (*ship).boundx &&
				andna[i].x + andna[i].boundx > (*ship).x - (*ship).boundx &&
				andna[i].y - andna[i].boundy < (*ship).y + (*ship).boundy &&
				andna[i].y + andna[i].boundy > (*ship).y - (*ship).boundy)
			{
				andna[i].live = false;
				validar_andna = true;
			}
			else if(andna[i].x < 0)
			{
				andna[i].live = false;
			}
		}
	}
}



void InitAndnb(varandnb andnb[], int size, ALLEGRO_BITMAP *image)
{
	for(int i = 0; i < size; i++)
	{
		andnb[i].ID = ANDNB;
		andnb[i].live = false;
		andnb[i].speed = 3;
		andnb[i].boundx = 35;
		andnb[i].boundy = 35;

		andnb[i].maxFrame = 2;
		andnb[i].curFrame = 0;
		andnb[i].frameCount = 0;
		andnb[i].frameDelay = 30;
		andnb[i].frameWidth = 54;
		andnb[i].frameHeight = 30	;
		andnb[i].animationColumns = 2;
		andnb[i].animationDirection = 1;

		if(image != NULL)
		{
			andnb[i].image = image;
		}
	}
}

void DrawAndnb(varandnb andnb[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(andnb[i].live)
		{
			int fx = (andnb[i].curFrame % andnb[i].animationColumns) * andnb[i].frameWidth;
			int fy = (andnb[i].curFrame / andnb[i].animationColumns) * andnb[i].frameHeight;

			al_draw_bitmap_region(andnb[i].image, fx, fy, andnb[i].frameWidth,
				andnb[i].frameHeight, andnb[i].x - andnb[i].frameWidth / 2, andnb[i].y - andnb[i].frameHeight / 2, 0);

		}
	}
}

void StartAndnb(varandnb andnb[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(!andnb[i].live)
		{
			if(rand() % 500 == 0)
			{
				andnb[i].live = true;
				andnb[i].y = rand() % HEIGHT;
				andnb[i].x = WIDTH ;

				break;
			}
		}
	}
}

void UpdateAndnb(varandnb andnb[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(andnb[i].live)
		{
			andnb[i].curFrame = 0;
			andnb[i].x -= andnb[i].speed;
		}
	}
}


void CollideAndnb(varandnb andnb[], int cSize, SpaceShip *ship)
{
	for(int i = 0; i < cSize; i++)
	{
		if(andnb[i].live)
		{
			if(andnb[i].x - andnb[i].boundx < (*ship).x + (*ship).boundx &&
				andnb[i].x + andnb[i].boundx > (*ship).x - (*ship).boundx &&
				andnb[i].y - andnb[i].boundy < (*ship).y + (*ship).boundy &&
				andnb[i].y + andnb[i].boundy > (*ship).y - (*ship).boundy)
			{
				andnb[i].live = false;
				validar_andnb = true;
			}
			else if(andnb[i].x < 0)
			{
				andnb[i].live = false;
			}
		}
	}
}




void InitOr(varor or[], int size, ALLEGRO_BITMAP *image)
{
	for(int i = 0; i < size; i++)
	{
		or[i].ID = OR;
		or[i].live = false;
		or[i].speed = 3;
		or[i].boundx = 35;
		or[i].boundy = 35;

		or[i].maxFrame = 2;
		or[i].curFrame = 0;
		or[i].frameCount = 0;
		or[i].frameDelay = 30;
		or[i].frameWidth = 54;
		or[i].frameHeight = 30	;
		or[i].animationColumns = 2;
		or[i].animationDirection = 1;

		if(image != NULL)
		{
			or[i].image = image;
		}
	}
}

void DrawOr(varor or[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(or[i].live)
		{
			int fx = (or[i].curFrame % or[i].animationColumns) * or[i].frameWidth;
			int fy = (or[i].curFrame / or[i].animationColumns) * or[i].frameHeight;

			al_draw_bitmap_region(or[i].image, fx, fy, or[i].frameWidth,
				or[i].frameHeight, or[i].x - or[i].frameWidth / 2, or[i].y - or[i].frameHeight / 2, 0);

		}
	}
}

void StartOr(varor or[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(!or[i].live)
		{
			if(rand() % 500 == 0)
			{
				or[i].live = true;
				or[i].y = rand() % HEIGHT;
				or[i].x = WIDTH ;

				break;
			}
		}
	}
}

void UpdateOr(varor or[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(or[i].live)
		{
			or[i].curFrame = 0;
			or[i].x -= or[i].speed;
		}
	}
}


void CollideOr(varor or[], int cSize, SpaceShip *ship)
{
	for(int i = 0; i < cSize; i++)
	{
		if(or[i].live)
		{
			if(or[i].x - or[i].boundx < (*ship).x + (*ship).boundx &&
				or[i].x + or[i].boundx > (*ship).x - (*ship).boundx &&
				or[i].y - or[i].boundy < (*ship).y + (*ship).boundy &&
				or[i].y + or[i].boundy > (*ship).y - (*ship).boundy)
			{
				or[i].live = false;
				validar_or = true;
			}
			else if(or[i].x < 0)
			{
				or[i].live = false;
			}
		}
	}
}



void InitNor(varnor nor[], int size, ALLEGRO_BITMAP *image)
{
	for(int i = 0; i < size; i++)
	{
		nor[i].ID = NOR;
		nor[i].live = false;
		nor[i].speed = 3;
		nor[i].boundx = 35;
		nor[i].boundy = 35;

		nor[i].maxFrame = 2;
		nor[i].curFrame = 0;
		nor[i].frameCount = 0;
		nor[i].frameDelay = 30;
		nor[i].frameWidth = 54;
		nor[i].frameHeight = 30	;
		nor[i].animationColumns = 2;
		nor[i].animationDirection = 1;

		if(image != NULL)
		{
			nor[i].image = image;
		}
	}
}

void DrawNor(varnor nor[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(nor[i].live)
		{
			int fx = (nor[i].curFrame % nor[i].animationColumns) * nor[i].frameWidth;
			int fy = (nor[i].curFrame / nor[i].animationColumns) * nor[i].frameHeight;

			al_draw_bitmap_region(nor[i].image, fx, fy, nor[i].frameWidth,
				nor[i].frameHeight, nor[i].x - nor[i].frameWidth / 2, nor[i].y - nor[i].frameHeight / 2, 0);

		}
	}
}

void StartNor(varnor nor[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(!nor[i].live)
		{
			if(rand() % 500 == 0)
			{
				nor[i].live = true;
				nor[i].y = rand() % HEIGHT;
				nor[i].x = WIDTH ;

				break;
			}
		}
	}
}

void UpdateNor(varnor nor[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(nor[i].live)
		{
			nor[i].curFrame = 0;
			nor[i].x -= nor[i].speed;
		}
	}
}


void CollideNor(varnor nor[], int cSize, SpaceShip *ship)
{
	for(int i = 0; i < cSize; i++)
	{
		if(nor[i].live)
		{
			if(nor[i].x - nor[i].boundx < (*ship).x + (*ship).boundx &&
				nor[i].x + nor[i].boundx > (*ship).x - (*ship).boundx &&
				nor[i].y - nor[i].boundy < (*ship).y + (*ship).boundy &&
				nor[i].y + nor[i].boundy > (*ship).y - (*ship).boundy)
			{
				nor[i].live = false;
				validar_nor = true;
			}
			else if(nor[i].x < 0)
			{
				nor[i].live = false;
			}
		}
	}
}


void InitOrna(varorna orna[], int size, ALLEGRO_BITMAP *image)
{
	for(int i = 0; i < size; i++)
	{
		orna[i].ID = ORNA;
		orna[i].live = false;
		orna[i].speed = 3;
		orna[i].boundx = 35;
		orna[i].boundy = 35;

		orna[i].maxFrame = 2;
		orna[i].curFrame = 0;
		orna[i].frameCount = 0;
		orna[i].frameDelay = 30;
		orna[i].frameWidth = 54;
		orna[i].frameHeight = 30	;
		orna[i].animationColumns = 2;
		orna[i].animationDirection = 1;

		if(image != NULL)
		{
			orna[i].image = image;
		}
	}
}

void DrawOrna(varorna orna[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(orna[i].live)
		{
			int fx = (orna[i].curFrame % orna[i].animationColumns) * orna[i].frameWidth;
			int fy = (orna[i].curFrame / orna[i].animationColumns) * orna[i].frameHeight;

			al_draw_bitmap_region(orna[i].image, fx, fy, orna[i].frameWidth,
				orna[i].frameHeight, orna[i].x - orna[i].frameWidth / 2, orna[i].y - orna[i].frameHeight / 2, 0);

		}
	}
}

void StartOrna(varorna orna[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(!orna[i].live)
		{
			if(rand() % 500 == 0)
			{
				orna[i].live = true;
				orna[i].y = rand() % HEIGHT;
				orna[i].x = WIDTH ;

				break;
			}
		}
	}
}

void UpdateOrna(varorna orna[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(orna[i].live)
		{
			orna[i].curFrame = 0;
			orna[i].x -= orna[i].speed;
		}
	}
}


void CollideOrna(varorna orna[], int cSize, SpaceShip *ship)
{
	for(int i = 0; i < cSize; i++)
	{
		if(orna[i].live)
		{
			if(orna[i].x - orna[i].boundx < (*ship).x + (*ship).boundx &&
				orna[i].x + orna[i].boundx > (*ship).x - (*ship).boundx &&
				orna[i].y - orna[i].boundy < (*ship).y + (*ship).boundy &&
				orna[i].y + orna[i].boundy > (*ship).y - (*ship).boundy)
			{
				orna[i].live = false;
				validar_orna = true;
			}
			else if(orna[i].x < 0)
			{
				orna[i].live = false;
			}
		}
	}
}


void InitOrnb(varornb ornb[], int size, ALLEGRO_BITMAP *image)
{
	for(int i = 0; i < size; i++)
	{
		ornb[i].ID = ORNB;
		ornb[i].live = false;
		ornb[i].speed = 3;
		ornb[i].boundx = 35;
		ornb[i].boundy = 35;

		ornb[i].maxFrame = 2;
		ornb[i].curFrame = 0;
		ornb[i].frameCount = 0;
		ornb[i].frameDelay = 30;
		ornb[i].frameWidth = 54;
		ornb[i].frameHeight = 30	;
		ornb[i].animationColumns = 2;
		ornb[i].animationDirection = 1;

		if(image != NULL)
		{
			ornb[i].image = image;
		}
	}
}

void DrawOrnb(varornb ornb[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(ornb[i].live)
		{
			int fx = (ornb[i].curFrame % ornb[i].animationColumns) * ornb[i].frameWidth;
			int fy = (ornb[i].curFrame / ornb[i].animationColumns) * ornb[i].frameHeight;

			al_draw_bitmap_region(ornb[i].image, fx, fy, ornb[i].frameWidth,
				ornb[i].frameHeight, ornb[i].x - ornb[i].frameWidth / 2, ornb[i].y - ornb[i].frameHeight / 2, 0);

		}
	}
}

void StartOrnb(varornb ornb[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(!ornb[i].live)
		{
			if(rand() % 500 == 0)
			{
				ornb[i].live = true;
				ornb[i].y = rand() % HEIGHT;
				ornb[i].x = WIDTH ;

				break;
			}
		}
	}
}

void UpdateOrnb(varornb ornb[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(ornb[i].live)
		{
			ornb[i].curFrame = 0;
			ornb[i].x -= ornb[i].speed;
		}
	}
}


void CollideOrnb(varornb ornb[], int cSize, SpaceShip *ship)
{
	for(int i = 0; i < cSize; i++)
	{
		if(ornb[i].live)
		{
			if(ornb[i].x - ornb[i].boundx < (*ship).x + (*ship).boundx &&
				ornb[i].x + ornb[i].boundx > (*ship).x - (*ship).boundx &&
				ornb[i].y - ornb[i].boundy < (*ship).y + (*ship).boundy &&
				ornb[i].y + ornb[i].boundy > (*ship).y - (*ship).boundy)
			{
				ornb[i].live = false;
				validar_ornb = true;
			}
			else if(ornb[i].x < 0)
			{
				ornb[i].live = false;
			}
		}
	}
}


void InitNot(varnot not[], int size, ALLEGRO_BITMAP *image)
{
	for(int i = 0; i < size; i++)
	{
		not[i].ID = NOT;
		not[i].live = false;
		not[i].speed = 3;
		not[i].boundx = 35;
		not[i].boundy = 35;

		not[i].maxFrame = 2;
		not[i].curFrame = 0;
		not[i].frameCount = 0;
		not[i].frameDelay = 30;
		not[i].frameWidth = 54;
		not[i].frameHeight = 30	;
		not[i].animationColumns = 2;
		not[i].animationDirection = 1;

		if(image != NULL)
		{
			not[i].image = image;
		}
	}
}

void DrawNot(varnot not[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(not[i].live)
		{
			int fx = (not[i].curFrame % not[i].animationColumns) * not[i].frameWidth;
			int fy = (not[i].curFrame / not[i].animationColumns) * not[i].frameHeight;

			al_draw_bitmap_region(not[i].image, fx, fy, not[i].frameWidth,
				not[i].frameHeight, not[i].x - not[i].frameWidth / 2, not[i].y - not[i].frameHeight / 2, 0);

		}
	}
}

void StartNot(varnot not[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(!not[i].live)
		{
			if(rand() % 500 == 0)
			{
				not[i].live = true;
				not[i].y = rand() % HEIGHT;
				not[i].x = WIDTH ;

				break;
			}
		}
	}
}

void UpdateNot(varnot not[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(not[i].live)
		{
			not[i].curFrame = 0;
			not[i].x -= not[i].speed;
		}
	}
}


void CollideNot(varnot not[], int cSize, SpaceShip *ship)
{
	for(int i = 0; i < cSize; i++)
	{
		if(not[i].live)
		{
			if(not[i].x - not[i].boundx < (*ship).x + (*ship).boundx &&
				not[i].x + not[i].boundx > (*ship).x - (*ship).boundx &&
				not[i].y - not[i].boundy < (*ship).y + (*ship).boundy &&
				not[i].y + not[i].boundy > (*ship).y - (*ship).boundy)
			{
				not[i].live = false;
				validar_not = true;
			}
			else if(not[i].x < 0)
			{
				not[i].live = false;
			}
		}
	}
}



bool CollidShips(SpaceBadShip *Bship, SpaceShip *ship){
	if (sqrt(pow((*ship).x - (*Bship).x, 2) + pow((*ship).y - (*Bship).y, 2)) <= 60)
		{
			return true;
		}
	else
		return false;
}



	void InitExplosions(Explosion explosions[], int size, ALLEGRO_BITMAP *image)
{
	for(int i = 0; i < size; i++)
	{
		explosions[i].live = false;
		explosions[i].maxFrame = 31;
		explosions[i].curFrame = 0;
		explosions[i].frameCount = 0;
		explosions[i].frameDelay = 1;
		explosions[i].frameWidth = 128;
		explosions[i].frameHeight = 128;
		explosions[i].animationColumns = 8;
		explosions[i].animationDirection = 1;

		if(image != NULL)
			explosions[i].image = image;
	}
}

void DrawExplosions(Explosion explosions[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(explosions[i].live)
		{
			int fx = (explosions[i].curFrame % explosions[i].animationColumns) * explosions[i].frameWidth;
			int fy = (explosions[i].curFrame / explosions[i].animationColumns) * explosions[i].frameHeight;

			al_draw_bitmap_region(explosions[i].image, fx, fy, explosions[i].frameWidth,
				explosions[i].frameHeight, explosions[i].x - explosions[i].frameWidth / 2, explosions[i].y - explosions[i].frameHeight / 2, 0);
		}
	}
}

void StartExplosions(Explosion explosions[], int size, int x, int y)
{
	for(int i = 0; i < size; i++)
	{
		if(!explosions[i].live)
		{
			explosions[i].live = true;
			explosions[i].x = x;
			explosions[i].y = y;
			break;
		}
	}
}

void UpdateExplosions(Explosion explosions[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(explosions[i].live)
		{
			if(++explosions[i].frameCount >= explosions[i].frameDelay)
			{
				explosions[i].curFrame += explosions[i].animationDirection;
				if(explosions[i].curFrame >= explosions[i].maxFrame)
				{
					explosions[i].curFrame = 0;
					explosions[i].live = false;
				}

				explosions[i].frameCount = 0;
			}
		}
	}
}

void InitBackground(Background *back, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image)
{
	(*back).x = x;
	(*back).y = y;
	(*back).velX = velx;
	(*back).velY = vely;
	(*back).width = width;
	(*back).height = height;
	(*back).dirX = dirX;
	(*back).dirY = dirY;
	(*back).image = image;
}

void UpdateBackground(Background *back)
{
	(*back).x += (*back).velX * (*back).dirX;
	if((*back).x + (*back).width <= 0)
		(*back).x = 0;
}

void DrawBackground(Background *back)
{
	al_draw_bitmap((*back).image, (*back).x, (*back).y, 0);

	if((*back).x + (*back).width < WIDTH)
		al_draw_bitmap((*back).image, (*back).x + (*back).width, (*back).y, 0);
}

void ChangeState(int *state, int newState)
{
	if(*state == TITLE)
	{}
	else if (*state == INTRO)
	{
	}
	else if(*state == PLAYING)
	{
		al_stop_sample_instance(songInstance);
	}
	else if(*state == LOST)
	{}

	*state = newState;

	if(*state == TITLE)
	{
		al_play_sample(song2, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
	}

	else if (*state == INTRO)
	{
	}
	else if(*state == PLAYING)
	{
		InitShip(&ship, NULL);
		InitBadShip(&Bship, NULL);
		InitBullet(bullets, NUM_BULLETS);
		InitExplosions(explosions, NUM_EXPLOSIONS, NULL);

		al_play_sample_instance(songInstance);
	}
	else if(*state == LOST)
	{
		al_play_sample(gameover, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
	}
}
