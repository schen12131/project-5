#include "Level3.h"
#define LEVEL3_WIDTH 14
#define LEVEL3_HEIGHT 8

#define LEVEL3_ENEMY_COUNT 1
unsigned int level3_data[] =
{
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1,
    3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 3, 2,
    3, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 3, 2
};

void Level3::Initialize() {
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 4, 1);
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(5, 0, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 2.0f;
    state.player->textureID = Util::LoadTexture("george_0.png");
    
    state.player->animRight = new int[4] {3, 7, 11, 15};
    state.player->animLeft = new int[4] {1, 5, 9, 13};
    state.player->animUp = new int[4] {2, 6, 10, 14};
    state.player->animDown = new int[4] {0, 4, 8, 12};
    
    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 4;
    state.player->animRows = 4;
    state.player->height = 0.8f;
    state.player->width = 0.8f;
    
    state.player->jumpPower = 7.0f;
    
    state.enemies = new Entity[LEVEL3_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("enemy2.png");
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].aiType = WALKER;
    state.enemies[0].aiState = WALKING;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(1, -5, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].movement = glm::vec3(1, 0, 0);
    state.enemies[0].isActive = true;
    
    state.gameOver = new Entity[9];
    state.youWin = new Entity[7];
    float counter = 3.0f;
    
    GLuint fontTextureID = Util::LoadTexture("font1.png");
    
    for (int i = 0; i < 9; i++){
        state.gameOver[i].textureID = fontTextureID;
        state.gameOver[i].position = glm::vec3(counter, -2, 0);
        state.gameOver[i].animCols = 16;
        state.gameOver[i].animRows = 16;
        state.gameOver[i].height = 0.3f;
        state.gameOver[i].width = 0.3f;
        state.gameOver[i].fail = new int[9] {71, 65, 77, 69, 9, 79, 86, 69, 82};
        state.gameOver[i].index = i;
        state.gameOver[i].isActive = false;
        if (i < 7){
            state.youWin[i].textureID = fontTextureID;
            state.youWin[i].position = glm::vec3(counter + 6, -2, 0);
            state.youWin[i].animCols = 16;
            state.youWin[i].animRows = 16;
            state.youWin[i].height = 0.3f;
            state.youWin[i].width = 0.3f;
            state.youWin[i].success = new int[7] {89, 79, 85, 9, 87, 73, 78};
            state.youWin[i].index = i;
            state.youWin[i].isActive = false;
        }
        counter += 0.5f;
    }
    
    for (int j = 0; j < 9; j++){
        state.gameOver[j].Update(NULL, NULL, NULL, 0, state.map);
    }
    for (int j = 0; j < 7; j++){
        state.youWin[j].Update(NULL, NULL, NULL, 0, state.map);
    }
}
void Level3::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
    state.enemies[0].Update(deltaTime, state.player, NULL, 0, state.map);
    
    if (state.player->lives == 0){
        state.player->isActive = false;
        for ( int i = 0; i < 9; i++){
            state.gameOver[i].isActive = true;
            state.gameOver[i].Update(NULL, NULL, NULL, 0, state.map);
        }
    }
    if (state.player->position.x >= 12){
        state.player->isActive = false;
        for ( int i = 0; i < 7; i++){
            state.youWin[i].isActive = true;
            state.youWin[i].Update(NULL, NULL, NULL, 0, state.map);
        }
    }
}

void Level3::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.enemies[0].Render(program);
    state.player->Render(program);
    for ( int i = 0; i < 9; i++){
        state.gameOver[i].Render(program);
    }
    for ( int i = 0; i < 7; i++){
        state.youWin[i].Render(program);
    }
}
