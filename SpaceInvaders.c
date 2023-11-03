/*|-----------------------------|
  |                             |
  |     Space Invaders Proje    |
  |                             |
  |     ENSAR YİĞİT SARITAŞ     |
  |          220229027          |
  |                             |
  |-----------------------------|*/

/**************************************************************************
 Projenin içeriği ve detaylar için klasördeki README.rtf dosyasını okuyun!
*************************************************************************/

//--------------------Include---------------------

//Include alanı SDL kütüphanemiz ve diğer header dosyaları burada tanımlanır.

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

//--------------------Define---------------------

//Define alanı projemizin kullanılacak ekran boyutlarını,
//Uzay gemisinin, düşman uzaylılıların ve atılan merminin özellikleri burada tanımlanır.

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define SHIP_WIDTH 64
#define SHIP_HEIGHT 64
#define SHIP_SPEED 9

#define ENEMY_WIDTH 30
#define ENEMY_HEIGHT 30
#define ENEMY_ROWS 3
#define ENEMY_COLS 12

#define ENEMY_INITIAL_X 25
#define ENEMY_INITIAL_Y 25
#define ENEMY_PADDING 15

#define BULLET_WIDTH 8
#define BULLET_HEIGHT 16
#define BULLET_SPEED 15

//--------------------Structlar---------------------

//Uzay gemisi, düşman uzaylı, mermi structları burada oluşturulur.
//Uzay gemisi için boyutlar, sağa sola hareket ve x,y düzlem yapısı burada tutulur.
//Düşman uzaylı için boyutlar, düşman uzaylının canlı olma durumu ve x,y düzlem yapısı burada tutulur.
//Atılan mermiler için boyutlar, merminin aktif olma durumu ve x,y düzlem yapısı burada tutulur.

typedef struct {
    int x, y;
    int width, height;
    bool isMovingLeft, isMovingRight;
} Ship;

typedef struct {
    int x, y;
    int width, height;
    bool isAlive;
} Enemy;

typedef struct {
    int x, y;
    int width, height;
    bool isActive;
} Bullet;

//--------------------Tanımlanan Değişkenler---------------------

//SDL kütüphanesiyle birlikte tanımlanan değişkenlerdir.
//isRunning değişkeni oyunun devamlılığını sağlar.

bool isRunning = true;
int enemySpeed = 1;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* backgroundTexture = NULL;

Ship ship;
Enemy enemies[ENEMY_ROWS][ENEMY_COLS];
Bullet bullet;


//********************Fonksiyonlar**********************

//--------------------init---------------------

//-Initialization-
//Oyunun başlatılması için gerekli olan SDL kütüphanesinin başlatılmasını ve gerekli bileşenlerin oluşturulmasını sağlar.
//Eğer fonksiyon true değeri döndürürse, oyun başarıyla başlatılmış demektir.

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL baslatilamadi. SDL Hatasi: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Space Invaders",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("Pencere olusturulamadi. SDL Hatasi: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        printf("Renderer olusturulamadi. SDL Hatasi: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

//--------------------initShip---------------------

//-Initialize ship-
// Uzay gemisinin; x,y özelliklerini, boyutlarını, oyunun ilk durumundaki hareket durumu için kullanılır.
// initShip() fonksiyonu, oyunun başlangıcında uzay gemisi objesini başlatmak için kullanılır.
// initShip() fonksiyonu oyun başladığında uzay gemisi objesinin başlangıç durumunu belirler.

void initShip()
{
    ship.x = (SCREEN_WIDTH - SHIP_WIDTH) / 2;
    ship.y = SCREEN_HEIGHT - SHIP_HEIGHT - 10;
    ship.width = SHIP_WIDTH;
    ship.height = SHIP_HEIGHT;
    ship.isMovingLeft = false;
    ship.isMovingRight = false;
}

//--------------------initEnemies---------------------

//-Initialize enemies-
// Düşman uzaylıların, oyunun başlangıcında matrisini başlatmak için kullanılır.
// initEnemies() fonksiyonu oyun başladığında düşman uzay gemilerinin başlangıç durumunu, boyutlarını, hayatta kalma durumunu true olarak belirler.

void initEnemies()
{
    int startX = ENEMY_INITIAL_X;
    int startY = ENEMY_INITIAL_Y;
    int padding = ENEMY_PADDING;

    for (int i = 0; i < ENEMY_ROWS; i++)
    {
        for (int j = 0; j < ENEMY_COLS; j++)
        {
            enemies[i][j].x = startX + (ENEMY_WIDTH + padding) * j;
            enemies[i][j].y = startY + (ENEMY_HEIGHT + padding) * i;
            enemies[i][j].width = ENEMY_WIDTH;
            enemies[i][j].height = ENEMY_HEIGHT;
            enemies[i][j].isAlive = true;
        }
    }
}

//--------------------initBullet---------------------

//-Initialize bullet-
// Uzay gemisinden çıkan merilerin; boyutlarını, ilk durumdaki aktifliği için kullanılır.
// initBullet() fonksiyonu, oyunun başlangıcında mermi objesini başlatmak için kullanılır. Bu fonksiyon, mermi objesinin başlangıç özelliklerini ayarlar.

void initBullet()
{
    bullet.width = BULLET_WIDTH;
    bullet.height = BULLET_HEIGHT;
    bullet.isActive = false;
}

//--------------------loadBackground---------------------

//Oyunun arka plan görüntüsünü yükler ve kullanıma hazır hale getirir.

bool loadBackground()
{
    SDL_Surface* surface = SDL_LoadBMP("background.bmp");

    if (surface == NULL)
    {
        printf("Arka plan yuklenemedi. SDL Hatasi: %s\n", SDL_GetError());
        return false;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);

    if (backgroundTexture == NULL)
    {
        printf("Arka plan yuklenemedi. SDL Hatasi: %s\n", SDL_GetError());

        SDL_FreeSurface(surface);
        return false;
    }

    SDL_FreeSurface(surface);
    return true;
}

//--------------------renderBackground---------------------

//Arka planın render edilmesini sağlar.

void renderBackground()
{
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
}

//--------------------moveShip---------------------

//Uzay gemisinin yatay yönde hareketini sağlar.

void moveShip()
{
    if (ship.isMovingLeft && ship.x > 0)
    {
        ship.x -= SHIP_SPEED;
    }

    if (ship.isMovingRight && ship.x < SCREEN_WIDTH - ship.width)
    {
        ship.x += SHIP_SPEED;
    }
}

//--------------------moveEnemies---------------------

//Düşmanların yatay hareketini yönetir ve düşmanların sınırlar içinde kalmasını, yönlerini değiştirmesini sağlar.
//Oyuncunun oyunu kaybetmesini kontrol eder.

void moveEnemies()
{
    int minX = ENEMY_INITIAL_X;
    int maxX = 0;

    for (int i = 0; i < ENEMY_ROWS; i++)
    {
        for (int j = 0; j < ENEMY_COLS; j++)
        {
            if (enemies[i][j].isAlive)
            {
                enemies[i][j].x += enemySpeed;

                if (enemies[i][j].x > maxX)
                {
                    maxX = enemies[i][j].x;
                }

                if (enemies[i][j].x < minX)
                {
                    minX = enemies[i][j].x;
                }
            }
        }
    }

    if (maxX > SCREEN_WIDTH - ENEMY_WIDTH || minX < ENEMY_PADDING)
    {
        enemySpeed = -enemySpeed;

        for (int i = 0; i < ENEMY_ROWS; i++)
        {
            for (int j = 0; j < ENEMY_COLS; j++)
            {
                enemies[i][j].y += ENEMY_HEIGHT;

                // Uzay gemisine düşman çarpması kontrolü
                if (enemies[i][j].y + enemies[i][j].height >= ship.y)
                {
                    printf("Uzay gemisine dusman uzaylilar carpti! Oyunu Kaybettiniz!\n");

                    isRunning = false;
                }
            }
        }
    }
}

//--------------------moveBullet---------------------

//Uzay gemisinden atılan mermilerin dikey yönde hareketini ve aktiflik kontrolünü sağlar.
//Mermiyi ekranın üst sınırına ulaştığında devre dışı bırakır.

void moveBullet()
{
    if (bullet.isActive)
    {
        bullet.y -= BULLET_SPEED;

        if (bullet.y < 0)
        {
            bullet.isActive = false;
        }
    }
}

//--------------------fireBullet---------------------

//Mermiyi ateşler ve başlangıç konumunu ayarlar.

void fireBullet()
{
    if (!bullet.isActive)
    {
        bullet.x = ship.x + (ship.width - bullet.width) / 2;
        bullet.y = ship.y;
        bullet.isActive = true;
    }
}

//--------------------checkCollisions---------------------

// Uzay gemisinden çıkan mermiler ve düşman uzaylılar arasındaki çarpışmaları kontrol eder. Çarpışma durumunda gerekli işlemleri gerçekleştirir.

void checkCollisions()
{
    for (int i = 0; i < ENEMY_ROWS; i++)
    {
        for (int j = 0; j < ENEMY_COLS; j++)
        {
            if (enemies[i][j].isAlive &&
                bullet.isActive &&
                bullet.x < enemies[i][j].x + enemies[i][j].width &&
                bullet.x + bullet.width > enemies[i][j].x &&
                bullet.y < enemies[i][j].y + enemies[i][j].height &&
                bullet.y + bullet.height > enemies[i][j].y)
            {
                enemies[i][j].isAlive = false;
                bullet.isActive = false;
            }
        }
    }
}

//--------------------checkGameStatus---------------------

//Düşmanların durumunu kontrol ederek oyunun kazanılıp kazanılmadığını belirler.

void checkGameStatus()
{
    bool allEnemiesDead = true;

    for (int i = 0; i < ENEMY_ROWS; i++)
    {
        for (int j = 0; j < ENEMY_COLS; j++)
        {
            if (enemies[i][j].isAlive)
            {
                allEnemiesDead = false;
                break;
            }
        }

        if (!allEnemiesDead)
        {
            break;
        }
    }

    if (allEnemiesDead)
    {
        printf("Butun dusman uzaylilar olduruldu.Oyun kazanildi!\n");

        isRunning = false;
    }
}



//--------------------gameLoop---------------------

//Oyunun ana döngüsünü oluşturarak, oyunun sürekli olarak güncellenmesini, kullanıcı etkileşimlerini takip edilmesini, nesnelerin hareketini ve çarpışmaların kontrol edilmesini sağlar.
//Oyunun akıcı bir şekilde çalışmasını sağlayarak oyun deneyimini sunar.

void gameLoop()
{

    Uint32 lastTime = SDL_GetTicks();

    while (isRunning)
    {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        SDL_Event event;

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }

            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_LEFT:

                        ship.isMovingLeft = true;
                        break;

                    case SDLK_RIGHT:
                        ship.isMovingRight = true;
                        break;

                    case SDLK_SPACE:
                        fireBullet();
                        break;
                }
            }

            else if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        ship.isMovingLeft = false;
                        break;

                    case SDLK_RIGHT:
                        ship.isMovingRight = false;
                        break;
                }
            }
        }

        moveShip();
        moveBullet();
        moveEnemies();
        checkCollisions();
        checkGameStatus();
        renderBackground();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &ship);
        SDL_RenderFillRect(renderer, &ship);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &bullet);
        SDL_RenderFillRect(renderer, &bullet);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (int i = 0; i < ENEMY_ROWS; i++)
        {
            for (int j = 0; j < ENEMY_COLS; j++)
            {
                if (enemies[i][j].isAlive)
                {
                    SDL_Rect enemyRect = {enemies[i][j].x, enemies[i][j].y, enemies[i][j].width, enemies[i][j].height};
                    SDL_RenderDrawRect(renderer, &enemyRect);
                    SDL_RenderFillRect(renderer, &enemyRect);
                }
            }
        }

        SDL_Delay(5);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
}

//--------------------close---------------------

//Oyunun sonlandırılması ve kullanılan kaynakların temizlenmesidir.

void close()
{
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//********************Main**********************

int main(int argc, char* args[])
{
    if ( !init() )
    {
        printf("Oyun baslatilamadi.\n");
        return -1;
    }

    if ( !loadBackground() )
    {
        printf("Arka plan yüklenemedi.\n");
        close();
        return -1;
    }

    initShip();
    initEnemies();
    initBullet();
    gameLoop();
    close();

return 0;
}

