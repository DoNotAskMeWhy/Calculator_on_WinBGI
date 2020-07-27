#include "graphics.h"
#include "winbgi.h"
#include "Functions.h"

const unsigned short c_MaxWidth(getmaxwidth());
const unsigned short c_HalfWidth(getmaxwidth() / 2);
const unsigned short c_MaxHeight(getmaxheight());
const unsigned short c_HalfHeight(getmaxheight() / 2);

const unsigned short c_DefaultButtonDimensionX(200);
const unsigned short c_DefaultButtonDimensionY(50); // For 50 the text position is +38
const unsigned short c_DefaultButtonsDistance(25);
const unsigned short c_CalculateButtonPositionY(150);
const unsigned short c_SettingsButtonPositionY(c_CalculateButtonPositionY + c_DefaultButtonDimensionY + c_DefaultButtonsDistance);
const unsigned short c_QuitButtonPositionY(c_SettingsButtonPositionY + c_DefaultButtonDimensionY + c_DefaultButtonsDistance);
const unsigned short c_TextBoxDimensionX(700);
const unsigned short c_TextBoxDimensionY(60);
const unsigned short c_TextBoxPositionY(300);
const unsigned short c_ResetButtonDistance(5);
const unsigned short c_ResetButtonPosittionX(c_HalfWidth + c_TextBoxDimensionX + c_ResetButtonDistance);
const unsigned short c_HistoryButtonPosittionX(c_HalfWidth - c_TextBoxDimensionX - c_TextBoxDimensionY - c_ResetButtonDistance);
const unsigned short c_MathExpressionTextBoxDimensionX(600);
const unsigned short c_MathExpressionTextBoxPositionY(c_TextBoxPositionY + c_TextBoxDimensionY + c_DefaultButtonsDistance);
const unsigned short c_ResultTextBoxDimensionX(500);
const unsigned short c_ResultTextBoxPositionY(c_MathExpressionTextBoxPositionY + c_TextBoxDimensionY + c_DefaultButtonsDistance);
const unsigned short c_SubmitButtonPositionY(c_ResultTextBoxPositionY + c_TextBoxDimensionY + c_DefaultButtonsDistance);

const unsigned short c_ButtonColourRED(174);
const unsigned short c_ButtonColourGREEN(195);
const unsigned short c_ButtonColourBLUE(224);
const unsigned short c_SecondaryButtonColourRED(132);
const unsigned short c_SecondaryButtonColourGREEN(167);
const unsigned short c_SecondaryButtonColourBLUE(209);
const unsigned short c_ButtonGrayColour(198);

unsigned short g_Language{ 1 };
bool g_isMusicOn{ FALSE };



//          SCREEN LAYOUTS          //

void HomeScreen(char* calculateButton, char* settingsButton, char* quitButton);
void CalculationScreen(char* textBoxButtonName);
void SettingsScreen();

//          PROCESSES          //

void CreatingScreenLayouts();
void ModifyingScreenLayouts();
unsigned short CreatingAndShowingHistory(std::string history_1_VisibleList, std::string history_2_VisibleList, std::string history_3_VisibleList, unsigned short historyNumber);
void ClearingHistory();
void CheckingHomeScreenEvents();
void CheckingCalculationScreenEvents();
void CheckingSettingsScreenEvents();
void ShowingTheResult(char* currentListOfCharacters);
void TextBoxesReset();
bool CheckingHomeHover(bool onHomeHover);
bool CheckingSoundHover(bool onSoundHover);
bool CheckingResetHover(bool onResetHover);
bool CheckingHistoryHover(bool onHistoryHover);
bool CheckingButtonHover(bool onButtonHover, unsigned short buttonNamePositionY, char* buttonName);
bool CheckingMouseClickPositionValidation(int positionX, int positionY, unsigned short buttonNamePositionY);
bool CheckingMouseClickPositionValidationForResetButton(int positionX, int positionY);
bool CheckingMouseClickPositionValidationForHistoryButton(int positionX, int positionY);
void ChangingButtonsLanguageDefault(char*& calculateButtonName, char*& settingsButtonName, char*& quitButtonName, char*& submitButtonName);
void ChangingButtonsLanguageOnCalculationScreen(char*& submitButtonName);

//          SETTINGS          //

void DefaultColourSettings(unsigned short redColour, unsigned short greenColour, unsigned short blueColour);
void SecondaryColourSettings(unsigned short redColour, unsigned short greenColour, unsigned short blueColour);
void SoundSettings();

//          BUTTONS          //

void CreatingDefaultButtons(unsigned short buttonNamePositionY, char* buttonName);
void CreatingTextBoxes(unsigned short textBoxDimensionX, unsigned short textBoxPositionY);
void CreatingImageButtons();
void CreatingResetButton();
void CreatingHistoryButton();

int main()
{
	CreatingScreenLayouts();
}

//          SCREEN LAYOUTS          //

void HomeScreen(char* calculateButtonName, char* settingsButtonName, char* quitButtonName)
{
	readimagefile("Background (2) (Resized).jpg", 0, 0, c_MaxWidth, c_MaxHeight);
	DefaultColourSettings(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE);

	CreatingImageButtons();
	CreatingDefaultButtons(c_CalculateButtonPositionY, calculateButtonName);
	CreatingDefaultButtons(c_SettingsButtonPositionY, settingsButtonName);
	CreatingDefaultButtons(c_QuitButtonPositionY, quitButtonName);
}

void CalculationScreen(char* submitButtonName)
{
	readimagefile("Background (2) (Resized).jpg", 0, 0, c_MaxWidth, c_MaxHeight);

	CreatingImageButtons();
	CreatingTextBoxes(c_TextBoxDimensionX, c_TextBoxPositionY);
	CreatingTextBoxes(c_MathExpressionTextBoxDimensionX, c_MathExpressionTextBoxPositionY);
	CreatingTextBoxes(c_ResultTextBoxDimensionX, c_ResultTextBoxPositionY);
	CreatingResetButton();
	CreatingHistoryButton();
	CreatingDefaultButtons(c_SubmitButtonPositionY, submitButtonName);
}

void SettingsScreen()
{
	readimagefile("Background (2) (Resized).jpg", 0, 0, c_MaxWidth, c_MaxHeight);
	DefaultColourSettings(c_SecondaryButtonColourRED, c_SecondaryButtonColourGREEN, c_SecondaryButtonColourBLUE);

	CreatingImageButtons();
	CreatingDefaultButtons(c_CalculateButtonPositionY, "ENGLISH");

	DefaultColourSettings(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE);
	CreatingDefaultButtons(c_SettingsButtonPositionY, "ROMANIAN");
	//CreatingDefaultButtons(c_QuitButtonPositionY, "FRENCH");
}

//          PROCESSES          //

void CreatingScreenLayouts()
{
	//initwindow(c_MaxWidth + 200, c_MaxHeight + 200, "Calculator", -5, -36);
	initwindow(c_MaxWidth, c_MaxHeight, "Calculator");
	g_isMusicOn = PlaySound("Patience - Jiao Ch'ien.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	HomeScreen("CALCULATE", "SETTINGS", "QUIT");

	setactivepage(1);
	CalculationScreen("SUBMIT");

	setactivepage(2);
	SettingsScreen();

	setactivepage(0);
	CheckingHomeScreenEvents();
}

void ModifyingScreenLayouts()
{
	switch (g_Language)
	{
	case 1:
		CreatingDefaultButtons(c_CalculateButtonPositionY, "ENGLISH");
		DefaultColourSettings(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE);
		CreatingDefaultButtons(c_SettingsButtonPositionY, "ROMANIAN");
		//CreatingDefaultButtons(c_QuitButtonPositionY, "FRENCH");

		setactivepage(0);
		HomeScreen("CALCULATE", "SETTINGS", "QUIT");

		setactivepage(1);
		CalculationScreen("SUBMIT");

		setactivepage(2);
		break;
	case 2:
		CreatingDefaultButtons(c_SettingsButtonPositionY, "ROMANA");
		DefaultColourSettings(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE);
		CreatingDefaultButtons(c_CalculateButtonPositionY, "ENGLEZA");
		//CreatingDefaultButtons(c_QuitButtonPositionY, "FRANCEZA");

		setactivepage(0);
		HomeScreen("CALCULEAZA", "SETARI", "IESIRE");

		setactivepage(1);
		CalculationScreen("CALCULEAZA");

		setactivepage(2);
		break;
	}
}

unsigned short CreatingAndShowingHistory(std::string history_1_VisibleList, std::string history_2_VisibleList, std::string history_3_VisibleList, unsigned short historyNumber)
{
	int positionX{};
	int positionY{};
	unsigned short historyPositionY{ c_TextBoxDimensionY + 10 };

	SecondaryColourSettings(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE);
	setlinestyle(SOLID_LINE, 1, 2);

	switch (historyNumber)
	{
	case 0:
		break;
	case 1:
		CreatingTextBoxes(c_TextBoxDimensionX, c_TextBoxPositionY - historyPositionY);
		bgiout << (history_1_VisibleList);
		outstreamxy(c_HalfWidth, c_TextBoxPositionY - historyPositionY + 42);
		break;
	case 2:
		CreatingTextBoxes(c_TextBoxDimensionX, c_TextBoxPositionY - historyPositionY);
		bgiout << (history_1_VisibleList);
		outstreamxy(c_HalfWidth, c_TextBoxPositionY - historyPositionY + 42);
		CreatingTextBoxes(c_TextBoxDimensionX, c_TextBoxPositionY - historyPositionY * 2);
		bgiout << (history_2_VisibleList);
		outstreamxy(c_HalfWidth, c_TextBoxPositionY - historyPositionY * 2 + 42);
		break;
	default:
		CreatingTextBoxes(c_TextBoxDimensionX, c_TextBoxPositionY - historyPositionY);
		bgiout << (history_1_VisibleList);
		outstreamxy(c_HalfWidth, c_TextBoxPositionY - historyPositionY + 42);
		CreatingTextBoxes(c_TextBoxDimensionX, c_TextBoxPositionY - historyPositionY * 2);
		bgiout << (history_2_VisibleList);
		outstreamxy(c_HalfWidth, c_TextBoxPositionY - historyPositionY * 2 + 42);
		CreatingTextBoxes(c_TextBoxDimensionX, c_TextBoxPositionY - historyPositionY * 3);
		bgiout << (history_3_VisibleList);
		outstreamxy(c_HalfWidth, c_TextBoxPositionY - historyPositionY * 3 + 42);
		break;
	}

	while (1)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
			getmouseclick(WM_LBUTTONDOWN, positionX, positionY);
		if (kbhit() || CheckingMouseClickPositionValidationForHistoryButton(positionX, positionY))
		{
			ClearingHistory();
			return 0;
		}
		if ((positionX > c_HalfWidth - c_TextBoxDimensionX) && (positionY > c_TextBoxPositionY - historyPositionY)
			&& (positionX < c_HalfWidth + c_TextBoxDimensionX) && (positionY < c_TextBoxPositionY - historyPositionY + c_TextBoxDimensionY))
		{
			ClearingHistory();
			return 1;
		}
		if ((positionX > c_HalfWidth - c_TextBoxDimensionX) && (positionY > c_TextBoxPositionY - historyPositionY * 2)
			&& (positionX < c_HalfWidth + c_TextBoxDimensionX) && (positionY < c_TextBoxPositionY - historyPositionY * 2 + c_TextBoxDimensionY))
		{
			ClearingHistory();
			return 2;
		}
		if ((positionX > c_HalfWidth - c_TextBoxDimensionX) && (positionY > c_TextBoxPositionY - historyPositionY * 3)
			&& (positionX < c_HalfWidth + c_TextBoxDimensionX) && (positionY < c_TextBoxPositionY - historyPositionY * 3 + c_TextBoxDimensionY))
		{
			ClearingHistory();
			return 3;
		}
	}
}

void ClearingHistory()
{
	setcolor(COLOR(218, 230, 242));
	setbkcolor(COLOR(218, 230, 242));
	setfillstyle(SOLID_FILL, COLOR(218, 230, 242));
	bar(c_HalfWidth - c_TextBoxDimensionX - 5, c_TextBoxPositionY - (c_TextBoxDimensionY + 10) * 3 - 5, c_HalfWidth + c_TextBoxDimensionX + 5, c_TextBoxPositionY - 5);
	DefaultColourSettings(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE);
}

void CheckingHomeScreenEvents()
{
	int positionX{};
	int positionY{};
	bool onHomeHover{ FALSE };
	bool onSoundHover{ FALSE };
	bool onCalculateHover{ FALSE };
	bool onSettingsHover{ FALSE };
	bool onQuitHover{ FALSE };

	char* calculateButtonName{ "CALCULATE" };
	char* settingsButtonName{ "SETTINGS" };
	char* quitButtonName{ "QUIT" };
	char* submitButtonName{ "SUBMIT" };

	while (1)
	{
		onHomeHover = CheckingHomeHover(onHomeHover);
		onSoundHover = CheckingSoundHover(onSoundHover);
		onCalculateHover = CheckingButtonHover(onCalculateHover, c_CalculateButtonPositionY, calculateButtonName);
		onSettingsHover = CheckingButtonHover(onSettingsHover, c_SettingsButtonPositionY, settingsButtonName);
		onQuitHover = CheckingButtonHover(onQuitHover, c_QuitButtonPositionY, quitButtonName);

		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, positionX, positionY);

			if (CheckingMouseClickPositionValidation(positionX, positionY, c_CalculateButtonPositionY))
			{
				setvisualpage(1);
				DefaultColourSettings(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE);
				CreatingDefaultButtons(c_CalculateButtonPositionY, calculateButtonName);
				setactivepage(1);
				CheckingCalculationScreenEvents();
				setvisualpage(0);
				readimagefile("HomeButton (Edited).jpg", 5, 5, 55, 55);
				TextBoxesReset();
				setactivepage(0);
			}
			if (CheckingMouseClickPositionValidation(positionX, positionY, c_SettingsButtonPositionY))
			{
				setvisualpage(2);
				DefaultColourSettings(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE);
				CreatingDefaultButtons(c_SettingsButtonPositionY, settingsButtonName);
				setactivepage(2);
				CheckingSettingsScreenEvents();
				ChangingButtonsLanguageDefault(calculateButtonName, settingsButtonName, quitButtonName, submitButtonName);
				setactivepage(0);
				setvisualpage(0);
			}
			if (CheckingMouseClickPositionValidation(positionX, positionY, c_QuitButtonPositionY))
			{
				closegraph();
				break;
			}
			if ((mousex() > 65) && (mousey() > 5) && (mousex() < 115) && (mousey() < 55))
				SoundSettings();
		}
	}
}

void CheckingCalculationScreenEvents()
{
	int positionX{};
	int positionY{};
	int startingPosition{ c_HalfWidth - c_TextBoxDimensionX + 25 };
	int history_1_StartingPosition{};
	int history_2_StartingPosition{};
	int history_3_StartingPosition{};
	bool onHomeHover{ FALSE };
	bool onSoundHover{ FALSE };
	bool onResetHover{ FALSE };
	bool onHistoryHover{ FALSE };
	bool onSubmitHover{ FALSE };
	bool hadTextBefore{ FALSE };
	bool notInHistory{ TRUE };
	char* submitButtonName{ "SUBMIT" };
	char character{};
	char currentListOfCharacters[1000]{};
	char history_1_CurrentList[1000]{};
	char history_2_CurrentList[1000]{};
	char history_3_CurrentList[1000]{};
	std::string visibleListOfCharacters{};
	std::string history_1_VisibleList{};
	std::string history_2_VisibleList{};
	std::string history_3_VisibleList{};
	std::string curentListOfCharactersString{};
	std::string history_1_CurentListString{};
	std::string history_2_CurentListString{};
	std::string history_3_CurentListString{};
	unsigned short currentPossitionOfCharacter{ 0 };
	unsigned short history_1_CurrentPossitionOfCharacter{ 0 };
	unsigned short history_2_CurrentPossitionOfCharacter{ 0 };
	unsigned short history_3_CurrentPossitionOfCharacter{ 0 };
	unsigned short historyNumber{ 0 };
	
	ChangingButtonsLanguageOnCalculationScreen(submitButtonName);

	while (kbhit())
		getch();

	while (1)
	{
		onHomeHover = CheckingHomeHover(onHomeHover);
		onSoundHover = CheckingSoundHover(onSoundHover);
		onResetHover = CheckingResetHover(onResetHover);
		onHistoryHover = CheckingHistoryHover(onHistoryHover);
		onSubmitHover = CheckingButtonHover(onSubmitHover, c_SubmitButtonPositionY, submitButtonName);

		if (kbhit())
		{
			SecondaryColourSettings(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE);

			character = (char)getch();

			if ((character == 27) || (character == 13))
			{
				goto RESULT;
			}

			if (startingPosition <= c_HalfWidth + c_TextBoxDimensionX - 25)
			{
				if (!(character == 8))
				{
					visibleListOfCharacters += character;
					curentListOfCharactersString += character;
					bgiout << curentListOfCharactersString;
					outstreamxy(c_HalfWidth, c_TextBoxPositionY + 42);

					startingPosition += 25;
					currentListOfCharacters[currentPossitionOfCharacter] = character;
					currentPossitionOfCharacter++;
				}
				else
				{
					if (visibleListOfCharacters.size() > 0)
					{
						bar(c_HalfWidth - c_TextBoxDimensionX + 1, c_TextBoxPositionY + 1, c_HalfWidth + c_TextBoxDimensionX - 1, c_TextBoxPositionY + c_TextBoxDimensionY - 1);
						visibleListOfCharacters.erase(visibleListOfCharacters.size() - 1, 1);
						curentListOfCharactersString.erase(curentListOfCharactersString.size() - 1, 1);
						bgiout << curentListOfCharactersString;
						outstreamxy(c_HalfWidth, c_TextBoxPositionY + 42);

						startingPosition -= 25;
						currentPossitionOfCharacter--;
						currentListOfCharacters[currentPossitionOfCharacter] = '\0';
					}
				}
			}
			else
			{
				if (!(character == 8))
				{
					visibleListOfCharacters += character;
					visibleListOfCharacters.erase(0, 1);
					curentListOfCharactersString += character;
					bgiout << visibleListOfCharacters;
					outstreamxy(c_HalfWidth, c_TextBoxPositionY + 42);

					startingPosition += 25;
					currentListOfCharacters[currentPossitionOfCharacter] = character;
					currentPossitionOfCharacter++;
				}
				else
				{
					bar(c_HalfWidth - c_TextBoxDimensionX + 1, c_TextBoxPositionY + 1, c_HalfWidth + c_TextBoxDimensionX - 1, c_TextBoxPositionY + c_TextBoxDimensionY - 1);
					visibleListOfCharacters.erase(visibleListOfCharacters.size() - 1, 1);
					curentListOfCharactersString.erase(curentListOfCharactersString.size() - 1, 1);
					if (curentListOfCharactersString.size() > 54)
						visibleListOfCharacters = curentListOfCharactersString.substr(curentListOfCharactersString.size() - 55, 55);
					bgiout << visibleListOfCharacters;
					outstreamxy(c_HalfWidth, c_TextBoxPositionY + 42);

					startingPosition -= 25;
					currentPossitionOfCharacter--;
					currentListOfCharacters[currentPossitionOfCharacter] = '\0';
				}
			}
		}

		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, positionX, positionY);

			if ((positionX < 55) && (positionY < 55))
				break;
			if ((mousex() > 65) && (mousey() > 5) && (mousex() < 115) && (mousey() < 55))
				SoundSettings();
			if (CheckingMouseClickPositionValidationForResetButton(positionX, positionY))
			{
				TextBoxesReset();
				startingPosition = c_HalfWidth - c_TextBoxDimensionX + 25;
				character = {};
				visibleListOfCharacters = {};
				curentListOfCharactersString = {};
				memset(currentListOfCharacters, 0, sizeof(currentListOfCharacters));
				currentPossitionOfCharacter = 0;
			}
			if (CheckingMouseClickPositionValidationForHistoryButton(positionX, positionY))
			{
				unsigned short pickedHistory{ CreatingAndShowingHistory(history_1_VisibleList, history_2_VisibleList, history_3_VisibleList, historyNumber) };
				SecondaryColourSettings(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE);

				switch (pickedHistory)
				{
				case 0:
					break;
				case 1:
					memset(currentListOfCharacters, 0, sizeof(currentListOfCharacters));
					bar(c_HalfWidth - c_TextBoxDimensionX + 1, c_TextBoxPositionY + 1, c_HalfWidth + c_TextBoxDimensionX - 1, c_TextBoxPositionY + c_TextBoxDimensionY - 1);
					strcpy(currentListOfCharacters, history_1_CurrentList);
					visibleListOfCharacters = history_1_VisibleList;
					bgiout << visibleListOfCharacters;
					outstreamxy(c_HalfWidth, c_TextBoxPositionY + 42);
					startingPosition = history_1_StartingPosition;
					curentListOfCharactersString = history_1_CurentListString;
					currentPossitionOfCharacter = history_1_CurrentPossitionOfCharacter;
					notInHistory = FALSE;
					goto RESULT;
				case 2:
					memset(currentListOfCharacters, 0, sizeof(currentListOfCharacters));
					bar(c_HalfWidth - c_TextBoxDimensionX + 1, c_TextBoxPositionY + 1, c_HalfWidth + c_TextBoxDimensionX - 1, c_TextBoxPositionY + c_TextBoxDimensionY - 1);
					strcpy(currentListOfCharacters, history_2_CurrentList);
					visibleListOfCharacters = history_2_VisibleList;
					bgiout << visibleListOfCharacters;
					outstreamxy(c_HalfWidth, c_TextBoxPositionY + 42);
					startingPosition = history_2_StartingPosition;
					curentListOfCharactersString = history_2_CurentListString;
					currentPossitionOfCharacter = history_2_CurrentPossitionOfCharacter;
					notInHistory = FALSE;
					goto RESULT;
				case 3:
					memset(currentListOfCharacters, 0, sizeof(currentListOfCharacters));
					bar(c_HalfWidth - c_TextBoxDimensionX + 1, c_TextBoxPositionY + 1, c_HalfWidth + c_TextBoxDimensionX - 1, c_TextBoxPositionY + c_TextBoxDimensionY - 1);
					strcpy(currentListOfCharacters, history_3_CurrentList);
					visibleListOfCharacters = history_3_VisibleList;
					bgiout << visibleListOfCharacters;
					outstreamxy(c_HalfWidth, c_TextBoxPositionY + 42);
					startingPosition = history_3_StartingPosition;
					curentListOfCharactersString = history_3_CurentListString;
					currentPossitionOfCharacter = history_3_CurrentPossitionOfCharacter;
					notInHistory = FALSE;
					goto RESULT;
				}
			}
			if (CheckingMouseClickPositionValidation(positionX, positionY, c_SubmitButtonPositionY))
			{
			RESULT:
				if (hadTextBefore)
				{
					DefaultColourSettings(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE);
					bar(c_HalfWidth - c_MathExpressionTextBoxDimensionX + 1, c_MathExpressionTextBoxPositionY + 1,
						c_HalfWidth + c_MathExpressionTextBoxDimensionX - 1, c_MathExpressionTextBoxPositionY + c_TextBoxDimensionY - 1);
					bar(c_HalfWidth - c_ResultTextBoxDimensionX + 1, c_ResultTextBoxPositionY + 1, c_HalfWidth + c_ResultTextBoxDimensionX - 1, c_ResultTextBoxPositionY + c_TextBoxDimensionY - 1);
				}

				ShowingTheResult(currentListOfCharacters);
				hadTextBefore = TRUE;

				if (notInHistory)
				{
					historyNumber++;
					switch (historyNumber)
					{
					case 0:
						break;
					case 1:
						strcpy(history_1_CurrentList, currentListOfCharacters);
						history_1_VisibleList = visibleListOfCharacters;
						history_1_StartingPosition = startingPosition;
						history_1_CurentListString = curentListOfCharactersString;
						history_1_CurrentPossitionOfCharacter = currentPossitionOfCharacter;
						break;
					case 2:
						strcpy(history_2_CurrentList, history_1_CurrentList);
						strcpy(history_1_CurrentList, currentListOfCharacters);
						history_2_VisibleList = history_1_VisibleList;
						history_1_VisibleList = visibleListOfCharacters;
						history_2_StartingPosition = history_1_StartingPosition;
						history_1_StartingPosition = startingPosition;
						history_2_CurentListString = history_1_CurentListString;
						history_1_CurentListString = curentListOfCharactersString;
						history_2_CurrentPossitionOfCharacter = history_1_CurrentPossitionOfCharacter;
						history_1_CurrentPossitionOfCharacter = currentPossitionOfCharacter;
						break;
					default:
						strcpy(history_3_CurrentList, history_2_CurrentList);
						strcpy(history_2_CurrentList, history_1_CurrentList);
						strcpy(history_1_CurrentList, currentListOfCharacters);
						history_3_VisibleList = history_2_VisibleList;
						history_2_VisibleList = history_1_VisibleList;
						history_1_VisibleList = visibleListOfCharacters;
						history_3_StartingPosition = history_2_StartingPosition;
						history_2_StartingPosition = history_1_StartingPosition;
						history_1_StartingPosition = startingPosition;
						history_3_CurentListString = history_2_CurentListString;
						history_2_CurentListString = history_1_CurentListString;
						history_1_CurentListString = curentListOfCharactersString;
						history_3_CurrentPossitionOfCharacter = history_2_CurrentPossitionOfCharacter;
						history_2_CurrentPossitionOfCharacter = history_1_CurrentPossitionOfCharacter;
						history_1_CurrentPossitionOfCharacter = currentPossitionOfCharacter;
						break;
					}
				}
				notInHistory = TRUE;

				std::cout << '\n';
				std::cout << "currentListOfCharacters:" << currentListOfCharacters << '\n';
				std::cout << "history_1_CurrentList:" << history_1_CurrentList << '\n';
				std::cout << "history_2_CurrentList:" << history_2_CurrentList << '\n';
				std::cout << "history_3_CurrentList:" << history_3_CurrentList << '\n';
				std::cout << '\n';

				std::cout << '\n';
				std::cout << "currentPossitionOfCharacter:" << currentPossitionOfCharacter << '\n';
				std::cout << "history_1_CurrentPossitionOfCharacter:" << history_1_CurrentPossitionOfCharacter << '\n';
				std::cout << "history_2_CurrentPossitionOfCharacter:" << history_2_CurrentPossitionOfCharacter << '\n';
				std::cout << "history_3_CurrentPossitionOfCharacter:" << history_3_CurrentPossitionOfCharacter << '\n';
				std::cout << '\n';
			}
		}
	}
}

void CheckingSettingsScreenEvents()
{
	int positionX{};
	int positionY{};
	bool onHomeHover{ FALSE };
	bool onSoundHover{ FALSE };
	bool onEnglishHover{ FALSE };
	bool onRomanianHover{ FALSE };
	bool onFrenchHover{ FALSE };

	while (1)
	{
		onHomeHover = CheckingHomeHover(onHomeHover);
		onSoundHover = CheckingSoundHover(onSoundHover);

		switch (g_Language)
		{
		case 1:
			onRomanianHover = CheckingButtonHover(onRomanianHover, c_SettingsButtonPositionY, "ROMANIAN");
			//onFrenchHover = CheckingButtonHover(onFrenchHover, c_QuitButtonPositionY, "FRENCH");
			break;
		case 2:
			onEnglishHover = CheckingButtonHover(onEnglishHover, c_CalculateButtonPositionY, "ENGLEZA");
			//onFrenchHover = CheckingButtonHover(onFrenchHover, c_QuitButtonPositionY, "FRANCEZA");
			break;
		/*case 3:
			onEnglishHover = CheckingButtonHover(onEnglishHover, c_CalculateButtonPositionY, "ANGLAIS");
			onRomanianHover = CheckingButtonHover(onRomanianHover, c_SettingsButtonPositionY, "ROUMAINE");
			break;*/
		}

		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, positionX, positionY);

			if ((CheckingMouseClickPositionValidation(positionX, positionY, c_CalculateButtonPositionY) && g_Language != 1))
			{
				g_Language = 1;
				ModifyingScreenLayouts();
			}
			if ((CheckingMouseClickPositionValidation(positionX, positionY, c_SettingsButtonPositionY) && g_Language != 2))
			{
				g_Language = 2;
				ModifyingScreenLayouts();
			}
			/*if ((CheckingMouseClickPositionValidation(positionX, positionY, c_QuitButtonPositionY) && g_Language != 3))
			{
				g_Language = 3;
				CreatingDefaultButtons(c_QuitButtonPositionY, "FRANCAISE");
				DefaultColourSettings(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE);
				CreatingDefaultButtons(c_CalculateButtonPositionY, "ANGLAIS");
				CreatingDefaultButtons(c_SettingsButtonPositionY, "ROUMAINE");
			}*/
			if ((positionX < 55) && (positionY < 55))
				break;
			if ((mousex() > 65) && (mousey() > 5) && (mousex() < 115) && (mousey() < 55))
				SoundSettings();
		}
	}
	readimagefile("HomeButton (Edited).jpg", 5, 5, 55, 55);
}

void ShowingTheResult(char* currentListOfCharacters)
{
	std::string resultWithLetters{};
	std::string visibleResultWithLetters{};
	char* MathExpression[1000]{ CalculationProcess(currentListOfCharacters, resultWithLetters, g_Language) };

	resultWithLetters[0] = toupper(resultWithLetters[0]);

	SecondaryColourSettings(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE);
	bgiout << (*MathExpression);
	outstreamxy(c_HalfWidth, c_MathExpressionTextBoxPositionY + 42);
	if (resultWithLetters.size() > 39)
	{
		size_t stringSize{ resultWithLetters.size() };
		for (unsigned short i{ 0 }; i < stringSize - 39; i++)
		{
			visibleResultWithLetters = resultWithLetters.substr(0, 39);
			resultWithLetters.erase(0, 1);	
			bgiout << visibleResultWithLetters;
			outstreamxy(c_HalfWidth, c_ResultTextBoxPositionY + 42);
			delay(300);
			if (kbhit())
				break;
		}
	}
	else
	{
		bgiout << resultWithLetters;
		outstreamxy(c_HalfWidth, c_ResultTextBoxPositionY + 42);
	}
	ResettingValues();
}

void TextBoxesReset()
{
	bar(c_HalfWidth - c_TextBoxDimensionX + 1, c_TextBoxPositionY + 1, c_HalfWidth + c_TextBoxDimensionX - 1, c_TextBoxPositionY + c_TextBoxDimensionY - 1);
	bar(c_HalfWidth - c_MathExpressionTextBoxDimensionX + 1, c_MathExpressionTextBoxPositionY + 1,
		c_HalfWidth + c_MathExpressionTextBoxDimensionX - 1, c_MathExpressionTextBoxPositionY + c_TextBoxDimensionY - 1);
	bar(c_HalfWidth - c_ResultTextBoxDimensionX + 1, c_ResultTextBoxPositionY + 1, c_HalfWidth + c_ResultTextBoxDimensionX - 1, c_ResultTextBoxPositionY + c_TextBoxDimensionY - 1);
}

bool CheckingHomeHover(bool onHomeHover)
{
	if (!((mousex() < 55) && (mousey() < 55)))
	{
		if (onHomeHover)
		{
			readimagefile("HomeButton (Edited).jpg", 5, 5, 55, 55);
			onHomeHover = FALSE;
		}
	}
	else
	{
		if (!onHomeHover)
		{
			readimagefile("HomeButton (Edited) (onHover).jpg", 5, 5, 55, 55);
			onHomeHover = TRUE;
		}
	}
	return onHomeHover;
}

bool CheckingSoundHover(bool onSoundHover)
{
	if (!((mousex() > 65) && (mousey() > 5) && (mousex() < 115) && (mousey() < 55)))
	{
		if (onSoundHover)
		{
			readimagefile("SoundButton (Edited) v2.jpg", 65, 5, 115, 55);
			onSoundHover = FALSE;
		}
	}
	else
	{
		if (!onSoundHover)
		{
			readimagefile("SoundButton (Edited) (onHover) v2.jpg", 65, 5, 115, 55);
			onSoundHover = TRUE;
		}
	}
	return onSoundHover;
}

bool CheckingResetHover(bool onResetHover)
{
	if (!((mousex() > c_ResetButtonPosittionX) && (mousey() > c_TextBoxPositionY) && (mousex() < c_ResetButtonPosittionX + c_TextBoxDimensionY) && (mousey() < c_TextBoxPositionY + c_TextBoxDimensionY)))
	{
		if (onResetHover)
		{
			readimagefile("ResetButton (Edited).jpg", c_ResetButtonPosittionX, c_TextBoxPositionY, c_ResetButtonPosittionX + c_TextBoxDimensionY, c_TextBoxPositionY + c_TextBoxDimensionY);
			onResetHover = FALSE;
		}
	}
	else
	{
		if (!onResetHover)
		{
			readimagefile("ResetButton (Edited) (onHover).jpg", c_ResetButtonPosittionX, c_TextBoxPositionY, c_ResetButtonPosittionX + c_TextBoxDimensionY, c_TextBoxPositionY + c_TextBoxDimensionY);
			onResetHover = TRUE;
		}
	}
	return onResetHover;
}

bool CheckingHistoryHover(bool onHistoryHover)
{
	if (!((mousex() > c_HistoryButtonPosittionX) && (mousey() > c_TextBoxPositionY) && (mousex() < c_HistoryButtonPosittionX + c_TextBoxDimensionY) && (mousey() < c_TextBoxPositionY + c_TextBoxDimensionY)))
	{
		if (onHistoryHover)
		{
			readimagefile("HistoryButton (Edited).jpg", c_HistoryButtonPosittionX, c_TextBoxPositionY, c_HistoryButtonPosittionX + c_TextBoxDimensionY, c_TextBoxPositionY + c_TextBoxDimensionY);
			onHistoryHover = FALSE;
		}
	}
	else
	{
		if (!onHistoryHover)
		{
			readimagefile("HistoryButton (Edited) (OnHover).jpg", c_HistoryButtonPosittionX, c_TextBoxPositionY, c_HistoryButtonPosittionX + c_TextBoxDimensionY, c_TextBoxPositionY + c_TextBoxDimensionY);
			onHistoryHover = TRUE;
		}
	}
	return onHistoryHover;
}

bool CheckingButtonHover(bool onButtonHover, unsigned short buttonNamePositionY, char* buttonName)
{
	if (!((mousex() > c_HalfWidth - c_DefaultButtonDimensionX) && (mousey() > buttonNamePositionY)
		&& (mousex() < c_HalfWidth + c_DefaultButtonDimensionX) && (mousey() < buttonNamePositionY + c_DefaultButtonDimensionY)))
	{
		if (onButtonHover)
		{
			DefaultColourSettings(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE);
			CreatingDefaultButtons(buttonNamePositionY, buttonName);
			onButtonHover = FALSE;
		}
	}
	else
	{
		if (!onButtonHover)
		{
			DefaultColourSettings(c_SecondaryButtonColourRED, c_SecondaryButtonColourGREEN, c_SecondaryButtonColourBLUE);
			CreatingDefaultButtons(buttonNamePositionY, buttonName);
			onButtonHover = TRUE;
		}
	}
	return onButtonHover;
}

bool CheckingMouseClickPositionValidation(int positionX, int positionY, unsigned short buttonNamePositionY)
{
	return (positionX > c_HalfWidth - c_DefaultButtonDimensionX) && (positionY > buttonNamePositionY)
		&& (positionX < c_HalfWidth + c_DefaultButtonDimensionX) && (positionY < buttonNamePositionY + c_DefaultButtonDimensionY);
}

bool CheckingMouseClickPositionValidationForResetButton(int positionX, int positionY)
{
	return (positionX > c_ResetButtonPosittionX) && (positionY > c_TextBoxPositionY)
		&& (positionX < c_ResetButtonPosittionX + c_TextBoxDimensionY) && (positionY < c_TextBoxPositionY + c_TextBoxDimensionY);
}

bool CheckingMouseClickPositionValidationForHistoryButton(int positionX, int positionY)
{
	return (positionX > c_HistoryButtonPosittionX) && (positionY > c_TextBoxPositionY)
		&& (positionX < c_HistoryButtonPosittionX + c_TextBoxDimensionY) && (positionY < c_TextBoxPositionY + c_TextBoxDimensionY);
}

void ChangingButtonsLanguageDefault(char*& calculateButtonName, char*& settingsButtonName, char*& quitButtonName, char*& submitButtonName)
{
	switch (g_Language)
	{
	case 1:
		calculateButtonName = "CALCULATE";
		settingsButtonName = "SETTINGS";
		quitButtonName = "QUIT";
		submitButtonName = "SUBMIT";
		break;
	case 2:
		calculateButtonName = "CALCULEAZA";
		settingsButtonName = "SETARI";
		quitButtonName = "IESIRE";
		submitButtonName = "CALCULEAZA";
		break;
	}
}

void ChangingButtonsLanguageOnCalculationScreen(char*& submitButtonName)
{
	switch (g_Language)
	{
	case 1:
		submitButtonName = "SUBMIT";
		break;
	case 2:
		submitButtonName = "CALCULEAZA";
		break;
	}
}

//          SETTINGS          //

void DefaultColourSettings(unsigned short redColour, unsigned short greenColour, unsigned short blueColour)
{
	setfillstyle(SOLID_FILL, COLOR(redColour, greenColour, blueColour));
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(10, HORIZ_DIR, 6);
	setlinestyle(SOLID_LINE, 1, 4);
	setbkcolor(COLOR(redColour, greenColour, blueColour));
}

void SecondaryColourSettings(unsigned short redColour, unsigned short greenColour, unsigned short blueColour)
{
	setfillstyle(SOLID_FILL, COLOR(redColour, greenColour, blueColour));
	setbkcolor(COLOR(redColour, greenColour, blueColour));
	setcolor(WHITE);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(10, HORIZ_DIR, 5);
}

void SoundSettings()
{
	if (g_isMusicOn)
	{
		PlaySound(NULL, 0, 0);
		g_isMusicOn = { FALSE };
	}
	else
	{
		g_isMusicOn = PlaySound("Patience - Jiao Ch'ien.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	}
}

//          BUTTONS          //

void CreatingDefaultButtons(unsigned short buttonNamePositionY, char* buttonName)
{
	setcolor(COLOR(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE));
	bar(c_HalfWidth - c_DefaultButtonDimensionX, buttonNamePositionY, c_HalfWidth + c_DefaultButtonDimensionX, buttonNamePositionY + c_DefaultButtonDimensionY);

	setcolor(WHITE);
	outtextxy(c_HalfWidth, buttonNamePositionY + 38, buttonName);

	rectangle((c_HalfWidth - c_DefaultButtonDimensionX) - 1, (buttonNamePositionY)-1, (c_HalfWidth + c_DefaultButtonDimensionX) + 1, (buttonNamePositionY + c_DefaultButtonDimensionY) + 1);
}

void CreatingTextBoxes(unsigned short textBoxDimensionX, unsigned short textBoxPositionY)
{
	setcolor(COLOR(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE));
	setbkcolor(COLOR(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE));
	setfillstyle(SOLID_FILL, COLOR(c_ButtonColourRED, c_ButtonColourGREEN, c_ButtonColourBLUE));
	bar(c_HalfWidth - textBoxDimensionX, textBoxPositionY, c_HalfWidth + textBoxDimensionX, textBoxPositionY + c_TextBoxDimensionY);

	setcolor(WHITE);
	//outtextxy(c_HalfWidth, textBoxPositionY + 42, textBoxButtonName);

	rectangle((c_HalfWidth - textBoxDimensionX) - 1, (textBoxPositionY)-1, (c_HalfWidth + textBoxDimensionX) + 1, (textBoxPositionY + c_TextBoxDimensionY) + 1);
}

void CreatingImageButtons()
{
	readimagefile("HomeButton (Edited).jpg", 5, 5, 55, 55);
	readimagefile("SoundButton (Edited) v2.jpg", 65, 5, 115, 55);
}

void CreatingResetButton()
{
	readimagefile("ResetButton (Edited).jpg", c_ResetButtonPosittionX, c_TextBoxPositionY, c_ResetButtonPosittionX + c_TextBoxDimensionY, c_TextBoxPositionY + c_TextBoxDimensionY);
}

void CreatingHistoryButton()
{
	readimagefile("HistoryButton (Edited).jpg", c_HistoryButtonPosittionX, c_TextBoxPositionY, c_HistoryButtonPosittionX + c_TextBoxDimensionY, c_TextBoxPositionY + c_TextBoxDimensionY);
}