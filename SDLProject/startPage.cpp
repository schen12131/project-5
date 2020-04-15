#include "startPage.h"
#define PAGE_WIDTH 14
#define PAGE_HEIGHT 8

unsigned int startPage_data[] =
{
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
    3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
    3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

void startPage::Initialize() {
    state.nextScene = -1;
    
    GLuint fontTextureID = Util::LoadTexture("font1.png");
    state.map = new Map(PAGE_WIDTH, PAGE_HEIGHT, startPage_data, fontTextureID, 1.0f, 16, 16);


}
void startPage::Update(float deltaTime) {
    //state.words->Update(NULL, NULL, NULL, 0, NULL);

}

void startPage::Render(ShaderProgram *program) {
   state.map->Render(program);
}
