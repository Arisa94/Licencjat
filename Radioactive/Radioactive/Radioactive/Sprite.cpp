#include "Sprite.h"


CSprite::CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, float* passedCameraX, float* passedCameraY, CCollisionRect passedCollision){ //CONSTRUCTOR

	/*And that's the moment when all fun begins*/
	collision = passedCollision;

	cameraX = passedCameraX;
	cameraY = passedCameraY;
	renderer = passed_renderer; //That's that SDL crap to render pictures

	if (x % 25 >= 12){

		x = x - (x % 25) + 25;

	}

	else{

		x = x - (x % 25);

	}

	if (y % 25 >= 12){

		y = y - (y % 25) + 25;

	}

	else{

		y = y - (y % 25);

	}

	/*if (addToColliding){
		
		pair.first = x;
		pair.second = y;
		collisions.push_back(pair);

	}*/

	image = NULL; 
	image = IMG_LoadTexture(renderer, FilePath.c_str()); //loading Texture as U see

	if (image == NULL){

		std::cout << "Couldn't load image " << FilePath.c_str() << std::endl; //If there's no such image for ex'

	}

	collisionImage = NULL;
	collisionImage = IMG_LoadTexture(renderer, "data_images/DebugImages/collision.png"); //loading Texture as U see

	if (collisionImage == NULL){

		std::cout << "Couldn't load collision image " << "CollisionImage" << std::endl; //If there's no such image for ex'

	}

	rect.x = x; //Setting coordinates
	rect.y = y;
	rect.w = w; //Setting size
	rect.h = h;

	SDL_QueryTexture(image, NULL, NULL, &img_width, &img_height); //Taking all pic' with it's default size

	crop.x = 0; //That was to croping image for animation, at starts its anyway placed at 0,0 coordinates
	crop.y = 0;
	crop.w = img_width; //And size is size of whole pic'
	crop.h = img_height;

	xPos = x; //Holding start coordinates
	yPos = y;

	originX = 0; //Setting origin, that's focus (place to move)
	originY = 0;
	
	currentFrame = 0;
	amountFrameX = 0;
	amountFrameY = 0;


	camera.x = rect.x + *cameraX; //Now setting camera to look at the character with it in the middle of the screen
	camera.y = rect.y + *cameraY;
	camera.w = rect.w;
	camera.h = rect.h;

}

void CSprite::draw(){ //That's to rendering all image, drawing it with correct crop

	camera.x = rect.x + *cameraX;
	camera.y = rect.y + *cameraY;
	collision.setX(rect.x + *cameraX);
	collision.setY(rect.y + *cameraY);

	SDL_RenderCopy(renderer, image, &crop, &camera);
//	SDL_RenderCopy(renderer, collisionImage, NULL, &collision.getRect());

}

void CSprite::drawSteady(){ //That was to draw character. Just simply draw

	collision.setX(rect.x + *cameraX);
	collision.setY(rect.y + *cameraY);

	SDL_RenderCopy(renderer, image, &crop, &rect);
//	SDL_RenderCopy(renderer, collisionImage, NULL, &collision.getRect());

}

void CSprite::playAnimation(int beginFrame, int endFrame, int row, float speed){ //Thats all cropping thing with animation

	if (animationDelay + speed < SDL_GetTicks()){ //Speed of movements (only visual movements of animation, not character movements) ~*~*ALSO SPEED POTION!*~*~

		/*That's to crop pic from left to right, all 4 pic parts*/
		if (endFrame <= currentFrame){

			currentFrame = beginFrame;

		}

		else{

			currentFrame++;

		}
		/*It's checking when to "come back" to start part of pic in that loop*/

		crop.x = currentFrame * (img_width / amountFrameX); //All crop formule, hard to understand but working!
		crop.y = row*(img_height / amountFrameY);
		crop.w = img_width / amountFrameX;
		crop.h = img_height / amountFrameY;

		animationDelay = SDL_GetTicks(); //All thing abt ticks and Ya know already

	}

}

void CSprite::setUpAnimation(int passedAmountX, int passedAmountY){ //Setting start values of animated pic size (how much crops upright and horizontally)

	amountFrameX = passedAmountX;
	amountFrameY = passedAmountY;


}

void CSprite::setOrigin(float x, float y){ //Setting origin of pic. That was that focus

	originX = x;
	originY = y;

	setPosition(getX(), getY());

}

void CSprite::setX(float X){ //Setter
	
	xPos = X;

	rect.x = int(xPos - originX);

}

void CSprite::setY(float Y){ //Setter

	yPos = Y;

	rect.y = int(yPos - originY);

}

void CSprite::setPosition(float X, float Y){ //Setter

	xPos = X;
	yPos = Y;

	rect.x = int(xPos - originX);
	rect.y = int(yPos - originY);

}

void CSprite::setWidth(int w){ //Setter

	rect.w = w;
	//camera.w = rect.w;

}

void CSprite::setHeight(int h){ //Setter

	rect.h = h;
	//camera.h = rect.h;

}

int CSprite::getX(){ //Getter

	return xPos;

}

int CSprite::getY(){ //Getter

	return yPos;

}

int CSprite::getWidth(){ //Getter

	return rect.w;

}

int CSprite::getHeight(){ //Getter

	return rect.h;

}

CCollisionRect CSprite::getCollision(){

	return collision;

}

bool CSprite::isColliding(CCollisionRect theCollider){

	return !(collision.getRect().x + collision.getRect().w < theCollider.getRect().x || collision.getRect().y + collision.getRect().h < theCollider.getRect().y || collision.getRect().x > theCollider.getRect().x + theCollider.getRect().w || collision.getRect().y > theCollider.getRect().y + theCollider.getRect().h);

}

bool CSprite::leftCollision(CCollisionRect theCollider){

	return (collision.getRect().x  < theCollider.getRect().x);

}

bool CSprite::rightCollision(CCollisionRect theCollider){

	return (collision.getRect().x  > theCollider.getRect().x);

}

bool CSprite::upCollision(CCollisionRect theCollider){

	return (collision.getRect().y  < theCollider.getRect().y);

}

bool CSprite::downCollision(CCollisionRect theCollider){
	
	return (collision.getRect().y  > theCollider.getRect().y);

}

CSprite::~CSprite(void){ //DESTRUCTOR

	SDL_DestroyTexture(image);
	SDL_DestroyRenderer(renderer);

}