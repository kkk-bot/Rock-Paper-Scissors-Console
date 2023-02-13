#include <iostream>
#include <ctime>
#include <string>
using namespace std;
enum enTurn { Player = 1, Computer = 2, None = 3 };
enum enDropType { Rock = 1, Paper = 2, Scissors = 3};
int PlayerWonTimes = 0;
int ComputerWonTimes = 0;
int DrawTimes = 0;
enTurn FinalWinner;
enTurn TempWinner;
int CurrentRound = 0;
int Rounds = 0;
enTurn CurrentPlayer;
enDropType PlayerChoice;
enDropType ComputerChoice;
enTurn GetCurrentPlayer()
{
	if (::CurrentPlayer == enTurn::Computer)
		return enTurn::Computer;
	else
		return enTurn::Player;
}
int GetCurrentRound()
{
	return (::CurrentRound);
}
int GetTotalRounds()
{
	return (::Rounds);
}
void ChangeTurn()
{
	if (::CurrentPlayer == enTurn::Player)
		CurrentPlayer = enTurn::Computer;
	else
		CurrentPlayer = enTurn::Player;

}
int RandomNumber(int From, int To)
{
	return (rand() % (To - From + 1) + From);
}
void AskForHowManyRounds(int From = 1, int To = 10)
{
	cout << "Please enter how many rounds " << From << " to " << To << "?\n";
	cin >> ::Rounds;

}
string PrintChoice(enDropType choice)
{
	switch (choice)
	{
	case enDropType::Paper:
		return "Paper";
	case enDropType::Rock:
		return "Rock";
	case enDropType::Scissors:
		return "Scissors";
	}
}
void ReadChoiceFromPlayer()
{
	int choice;
	cout << "Your Choice: [1]: Rock, [2]: Paper, [3]: Scissors ?\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
		PlayerChoice = enDropType::Rock;
		break;
	case 2:
		PlayerChoice = enDropType::Paper;
		break;
	case 3:
		PlayerChoice = enDropType::Scissors;
		break;
	}
}
void ReadChoiceFromComputer(int choice)
{
	switch (choice)
	{
	case 1:
		ComputerChoice = enDropType::Rock;
		break;
	case 2:
		ComputerChoice = enDropType::Paper;
		break;
	case 3:
		ComputerChoice = enDropType::Scissors;
		break;
	}
}
enTurn CheckWinner(enDropType player, enDropType computer)
{
	switch (player)
	{
	case enDropType::Paper:
		if (computer == enDropType::Rock)
			return enTurn::Player;
		else if (computer == enDropType::Scissors)
			return enTurn::Computer;
		else
			return enTurn::None;
	case enDropType::Rock:
		if (computer == enDropType::Paper)
			return enTurn::Computer;
		else if (computer == enDropType::Scissors)
			return enTurn::Player;
		else
			return enTurn::None;
	case enDropType::Scissors:
		if (computer == enDropType::Rock)
			return enTurn::Computer;
		else if (computer == enDropType::Paper)
			return enTurn::Player;
		else
			return enTurn::None;
	}
}
string PrintTurn(enTurn player)
{
	switch (player)
	{
	case enTurn::Computer:
		return "Computer";
	case enTurn::Player:
		return "Player";
	case enTurn::None:
		return "No one";
	}
}
void UpdateStats()
{
	if (TempWinner == enTurn::Computer)
	{
		::ComputerWonTimes++;
		system("color 4F");
		cout << '\a';

	}
	else if (TempWinner == enTurn::Player)
	{
		::PlayerWonTimes++;
		system("color 2F");
	}
	else
	{
		::DrawTimes++;
		system("color 6F");
	}

	if (ComputerWonTimes > PlayerWonTimes)
		FinalWinner = enTurn::Computer;
	else if (ComputerWonTimes < PlayerWonTimes)
		FinalWinner = enTurn::Player;
	else
		FinalWinner = enTurn::None;
}
void GameStats()
{
	cout << "\n____________________ Round [" << ::CurrentRound << "]____________________\n\n";
	cout << "Player   choice: ";
	cout << PrintChoice(::PlayerChoice) << endl;
	cout << "Computer choice: ";
	cout << PrintChoice(::ComputerChoice) << endl;
	cout << "Round Winner   : ";
	if (TempWinner == enTurn::Computer)
		cout << "Computer" << endl;
	else if (TempWinner == enTurn::Player)
		cout << "Player" << endl;
	else
		cout << "[No winner]" << endl;
	cout << "\n__________________________________________________\n\n";
}
void ClearGameStats()
{
	::ComputerWonTimes = 0;
	::PlayerWonTimes = 0;
	::DrawTimes = 0;
	::CurrentRound = 0;
	::Rounds = 0;
}
bool IsGameOver()
{
	cout << "\n\n\t\t_____________________________________________________________";
	cout << "\n\n\t\t\t\t\t+++ Game Over +++";
	cout << "\n\t\t_____________________________________________________________";
	cout << "\n\n\t\t_________________________[Game Results]______________________\n\n";
	cout << "\t\tGame Rounds        :  ";
	cout << ::Rounds;
	cout << "\n\t\tPlayer won times   :  ";
	cout << ::PlayerWonTimes;
	cout << "\n\t\tComputer won times :  ";
	cout << ::ComputerWonTimes;
	cout << "\n\t\tDraw times         :  ";
	cout << ::DrawTimes;
	cout << "\n\t\tFinal winner       :  ";
	cout << PrintTurn(::FinalWinner);
	cout << "\n\t\t_____________________________________________________________\n\n";
	
	char Again;
	cout << "\t\tDo you want to play again? Y/N : ";
	cin >> Again;
	if (Again == 'Y' || Again == 'y')
	{
		ClearGameStats();
		return false;
	}
	else
		return true;
}
void GameSetup()
{
	system("color 0F");
	AskForHowManyRounds(1, 100);
	for (int i = 1; i <= ::Rounds; i++)
	{
		::CurrentRound = i;
		cout << "\nRound [" << ::CurrentRound << "] begins: \n\n";
		ReadChoiceFromPlayer();
		system("cls");
		ReadChoiceFromComputer(RandomNumber(1, 3));

		TempWinner = CheckWinner(::PlayerChoice, ::ComputerChoice);
		GameStats();

		UpdateStats();

	}
}

int main()
{
	srand(unsigned(time(NULL)));
	GameSetup();
	while (!IsGameOver())
	{
		GameSetup();
	}
	return 0;
}