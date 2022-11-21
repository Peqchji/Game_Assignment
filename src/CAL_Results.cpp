#include "CAL_Results.h"
RESULTS::RESULTS(sf::Font &fontV1, sf::Font &fontV2)
{
	this->FontLarge =fontV2;
	this->FontSmall = fontV1;

	this->CAL_SCOREbuffer.create(::ScreenWidth, ::ScreenHeight);

	this->InputSelTexture.loadFromFile("../content/GUI/InputSelected.png");
    this->InputSelected.setTexture(this->InputSelTexture);
    this->InputSelected.setOrigin(sf::Vector2f(this->InputSelTexture.getSize().x/2.f, this->InputSelTexture.getSize().y/2.f));
    this->InputSelected.setScale(192.f/46, 59.f/13);
    this->InputSelected.setPosition(::ScreenWidth/2.f, ::ScreenHeight - 50.f);

	this->InputBlockTexture.loadFromFile("../content/GUI/InputBlock.png");
    this->InputBlock.setTexture(this->InputBlockTexture);
    this->InputBlock.setOrigin(sf::Vector2f(this->InputBlockTexture.getSize().x/2.f, this->InputBlockTexture.getSize().y/2.f));
    this->InputBlock.setScale(192.f/46, 59.f/13);
    this->InputBlock.setPosition(::ScreenWidth/2.f, ::ScreenHeight - 50.f);

    this->clickPlayBox.setSize((sf::Vector2f(this->InputBlockTexture.getSize().x * 192.f/46, 59.f/13 * this->InputBlockTexture.getSize().y)));
    this->clickPlayBox.setOrigin((sf::Vector2f(this->InputBlockTexture.getSize().x * 192.f/92.f, 59.f * this->InputBlockTexture.getSize().y/26.f)));
    this->clickPlayBox.setFillColor(sf::Color::Transparent);
    this->clickPlayBox.setPosition(::ScreenWidth/2.f, ::ScreenHeight - 50.f);

	this->Inputplay.setFont(FontSmall);
    this->Inputplay.setCharacterSize(36.f);
    this->Inputplay.setFillColor(sf::Color::White);
    this->Inputplay.setString("Go to Leaderboard");
    this->Inputplay.setOrigin(sf::Vector2f(Inputplay.getLocalBounds().left + Inputplay.getLocalBounds().width/2.f, (Inputplay.getLocalBounds().top + Inputplay.getLocalBounds().height)/2.f));
    this->Inputplay.setPosition(::ScreenWidth/2.f, ::ScreenHeight - 60.f);
    this->Inputplay.setOutlineColor(sf::Color::Black);
    this->Inputplay.setOutlineThickness(4.f);

	this->GAMEOVER.setFont(this->FontLarge);
    this->GAMEOVER.setCharacterSize(72.f);
    this->GAMEOVER.setFillColor(sf::Color::White);
    this->GAMEOVER.setString("GAMEOVER");
    this->GAMEOVER.setOrigin(sf::Vector2f(GAMEOVER.getLocalBounds().left + GAMEOVER.getLocalBounds().width/2.f, (GAMEOVER.getLocalBounds().top + GAMEOVER.getLocalBounds().height)/2.f));
    this->GAMEOVER.setPosition(::ScreenWidth/2.f, ::ScreenHeight/2.f - GAMEOVER.getLocalBounds().height/2.f);
    this->GAMEOVER.setOutlineColor(sf::Color::Black);
    this->GAMEOVER.setOutlineThickness(6.f);

	this->yourScore.setFont(this->FontLarge);
    this->yourScore.setCharacterSize(54.f);
    this->yourScore.setFillColor(sf::Color::White);
    this->yourScore.setPosition(::ScreenWidth/2.f, ::ScreenHeight/2.f + GAMEOVER.getLocalBounds().height/2.f);
    this->yourScore.setOutlineColor(sf::Color::Black);
    this->yourScore.setOutlineThickness(4.f);
	
	this->AnimationCLK.restart();
}
void RESULTS::update(float &InitPosi_x, float &InitPosi_y, float &mousePosi_x, float &mousePosi_y, bool &Toggle, bool &Running, int currentScore)
{
	std::stringstream ScoreStream;
	AnimationTimer = AnimationCLK.getElapsedTime();
	if(AnimationTimer.asMilliseconds() > 16 && currentAnimation != 127)
	{
		currentAnimation += 1;
		AnimationCLK.restart();
	}
	if(isSELECT(mousePosi_x, mousePosi_y, clickPlayBox) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Running = false;
		Toggle = true;
	}
	ScoreStream << "Your Score: " << currentScore;
	this->yourScore.setString(ScoreStream.str());
	this->yourScore.setOrigin(sf::Vector2f(yourScore.getLocalBounds().left + yourScore.getLocalBounds().width/2.f, (yourScore.getLocalBounds().top + yourScore.getLocalBounds().height)/2.f));
	setup_newProgessScene(InitPosi_x, InitPosi_y, mousePosi_x, mousePosi_y);
}

void RESULTS::setup_newProgessScene(float posi_x, float posi_y, float mouse_x, float mouse_y)
{
	this->CAL_SCOREbuffer.clear(sf::Color{0, 0, 0, static_cast<sf::Uint8>(2 * currentAnimation)});

	if(isSELECT(mouse_x, mouse_y, clickPlayBox))
	{
		this->CAL_SCOREbuffer.draw(this->InputSelected);
	}
	else
	{
		this->CAL_SCOREbuffer.draw(this->InputBlock);
	}
	this->CAL_SCOREbuffer.draw(this->GAMEOVER);
	this->CAL_SCOREbuffer.draw(this->yourScore);
	this->CAL_SCOREbuffer.draw(this->Inputplay);
	
	this->CAL_SCOREbuffer.display();

	this->currentCAL_SCORE.setTexture(this->CAL_SCOREbuffer.getTexture());
	this->currentCAL_SCORE.setOrigin(sf::Vector2f(::ScreenWidth/2.f, ::ScreenHeight/2.f));
	this->currentCAL_SCORE.setScale(1.f/ScaleUp, 1.f/ScaleUp);
	this->currentCAL_SCORE.setPosition(posi_x, posi_y);
}

void RESULTS::sorting(std::string &Name, unsigned int &playerScore)
{
	int count = 0;
	PlayerInfo.clear();
	file_LeaderBoardReader();
	// copy key-value pairs from the map to the vector
    std::vector<std::pair<std::string, unsigned int>>:: iterator It_Info;
    if(playerScore > PlayerInfo[0].second)
	{
		PlayerInfo[0].first = Name;
		PlayerInfo[0].second = playerScore;
	}
    std::sort(PlayerInfo.begin(), PlayerInfo.end(), [](auto p1, auto p2){return p1.second > p2.second;}); 
	// print the vector
	FILE *F_ptr;
	F_ptr = fopen("LeaderBoard.txt", "w+");
	for (int i = 0; i < PlayerInfo.size(); i++)
	{
		char *cstr = PlayerInfo[i].first.data();
		fprintf(F_ptr,"%d~%s\n", PlayerInfo[i].second, cstr);
	}
	fclose(F_ptr);
}

void RESULTS::file_LeaderBoardReader()
{
	PlayerInfo.clear();
    FILE *fptr;
    int i;
    if (!(fptr = fopen("LeaderBoard.txt", "r"))){
        fptr = fopen("LeaderBoard.txt", "w+");
        fprintf(fptr,"0~Unknow1\n0~Unknow2\n0~Unknow3\n0~Unknow4\n0~Unknow5");
        fclose(fptr);
    }
    fptr = fopen("LeaderBoard.txt","r");
    for(i = 0; i < 5; i++){
        fscanf(fptr,"%d~%[^\n]s", &scoreInfo[i], &playerNameInfo[i]);
		PlayerInfo.insert(PlayerInfo.begin(), std::make_pair(playerNameInfo[i], scoreInfo[i]));
    }
    fclose(fptr);
}

bool RESULTS::isSELECT(float Posi_x, float Posi_y, sf::RectangleShape  &Container)
{
    if(Container.getGlobalBounds().contains(sf::Vector2f(Posi_x, Posi_y)))
    {
        return true;
    }
    return false;
}