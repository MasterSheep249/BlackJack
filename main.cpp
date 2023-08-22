#include <iostream>
#include <string>
#include <string_view>
#include <iterator>
#include <algorithm>
#include <vector>
#include <array>
#include <ctime>
#include <random>
//#include <boost/algorithm/string.hpp>


//What's the difference between returing std::array and type alias;

enum class Suit
{
	clubs,
	diamonds,
	hearts,
	spades,
	Max
};

enum class Rank
{
	rank_2,
	rank_3,
	rank_4,
	rank_5,
	rank_6,
	rank_7,
	rank_8,
	rank_9,
	rank_10,
	Jack,
	Queen,
	King,
	Ace,
	Max
};

struct Card
{
	Suit suit{};
	Rank rank{};
};

using Deck = std::array<Card, 52>;


Deck createDeck()
{
	Deck myDeck;
	int tracker{ 0 };
	
	for (int index{ 0 }; index < static_cast<int>(Suit::Max); ++index)
	{
		for (int index_2{ 0 }; index_2 < static_cast<int>(Rank::Max); ++index_2)
		{
			myDeck[tracker].suit = static_cast<Suit>(index);
			myDeck[tracker].rank = static_cast<Rank>(index_2);
			++tracker;
		}
	}
	
	return myDeck;
}


void printSuit(Suit aSuit)
{
	switch (static_cast<int>(aSuit))
	{
	case 0:
		std::cout << "C";
		return;
	case 1:
		std::cout << "D";
		return;
	case 2:
		std::cout << "H";
		return;
	case 3:
		std::cout << "S";
		return;
	}
}
void printRank(Rank aRank)
{
	switch (static_cast<int>(aRank))
	{
	case 0:
		std::cout << "2";
		return;
	case 1:
		std::cout << "3";
		return;
	case 2:
		std::cout << "4";
		return;
	case 3:
		std::cout << "5";
		return;
	case 4:
		std::cout << "6";
		return;
	case 5:
		std::cout << "7";
		return;
	case 6:
		std::cout << "8";
		return;
	case 7:
		std::cout << "9";
		return;
	case 8:
		std::cout << "10";
		return;
	case 9:
		std::cout << "J";
		return;
	case 10:
		std::cout << "Q";
		return;
	case 11:
		std::cout << "K";
		return;
	case 12:
		std::cout << "A";
		return;
	}
}

void printDeck(const Deck& aDeck)
{
	for (std::size_t index{0}; index < aDeck.size(); ++index){
		Card aCard = aDeck[index];
		printRank(aCard.rank);
		printSuit(aCard.suit);
		std::cout << " ";
	}
}

void shuffleDeck(Deck& deck)
{
	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	std::shuffle(deck.begin(), deck.end(), mt);
}

int getRank(Rank aRank)
{
	switch (static_cast<int>(aRank))
	{
	case 0:
		return 2;
	case 1:
		return 3;
	case 2:
		return 4;
	case 3:
		return 5;
	case 4:
		return 6;
	case 5:
		return 7;
	case 6:
		return 8;
	case 7:
		return 9;
	case 8:
		return 10;
	case 9:
		return 10;
	case 10:
		return 10;
	case 11:
		return 10;
	case 12:
		return 11;
	}
}
bool equalsIgnoreCase(std::string str1, std::string str2)
{
	if (str1.length() != str2.length())
	{
		return false;
	}

	for (int index{ 0 }; index < str1.length(); ++index)
	{
		char a = str1.at(index);
		char b = str2.at(index);
		int int1 = static_cast<int>(a);
		int int2 = static_cast<int>(b);
		if ((int1 != int2) && (int1 != (int2 + 32)) && (int1 != (int2 - 32)))
		{
			return false;
		}
	}

	return true;
}
bool bust(int aInt)
{
	return ((aInt > 21) ? true : false);
}
bool playBlackJack(Deck& aDeck)
{
	//Card dealerCard = aDeck[0];
	//Card playerCardOne = aDeck[1];
	//Card playerCardTwo = aDeck[2];
	Rank randomPlayerRank{};
	Rank randomDealerRank{};

	int playerScore{ getRank(aDeck[0].rank) + getRank(aDeck[1].rank)};
	int dealerScore{ getRank(aDeck[2].rank)};

	int playerCardIndex{ 1 };
	int dealerCardIndex{ 0 };

	std::cout << "Player starting with score of " << playerScore << '\n';
	std::cout << "Dealer starting with score of " << dealerScore << '\n';
	std::cout << '\n';


	while (true)
	{
		while (true)
		{
			std::cout << "Hit or Stand? ";
			std::string choice{};
			std::cin >> choice;
			if (equalsIgnoreCase(choice, "hit"))
			{
				randomPlayerRank = aDeck[playerCardIndex + 1].rank;
				std::cout << "HIT..." << '\n';
				std::cout << '\n';
				std::cout << "You drew a card with rank " << getRank(randomPlayerRank) << '\n';
				std::cout << '\n';
				++playerCardIndex;
				playerScore += getRank(randomPlayerRank);
				if (bust(playerScore))
				{
					std::cout << "You went over the score of 21 with a score of " << playerScore << '\n';
					return false;
				}
			}
			else if (equalsIgnoreCase(choice, "stand"))
			{
				std::cout << "Turn over. Your score is " << playerScore << '\n';
				std::cout << '\n';
				std::cout << "Starting dealer turn..." << '\n';
				std::cout << '\n';
				break;
			}
		}
		

		std::cout << "Dealer begins drawing cards... " << '\n';
		std::cout << '\n';
		while (true)
		{
			if (dealerCardIndex <= playerCardIndex)
			{
				dealerCardIndex = playerCardIndex + 2;
			}

			randomDealerRank = aDeck[dealerCardIndex].rank;
			dealerScore += getRank(randomDealerRank);
			std::cout << "Dealer drew card with rank " << getRank(randomDealerRank) << '\n';
			std::cout << '\n';
			std::cout << "Dealer's score is " << dealerScore << "\n\n";

			if (dealerScore > 17 && dealerScore <= 21)
			{
				std::cout << "The dealer's final score was " << dealerScore << '\n';
				std::cout << '\n';
				break;
			}

			if (dealerScore > 21)
			{
				std::cout << "The dealer busts with a score of " << dealerScore << "! You win";
				return true;
			}
			++dealerCardIndex;
		}

		if (playerScore > dealerScore)
		{
			std::cout << "The player won with a score of " << playerScore << " and the dealer's score was " << dealerScore;
			return true;
		}
		if (playerScore < dealerScore)
		{
			std::cout << "The dealer won with a score of " << dealerScore << " and the player's score was " << playerScore;
			return false;
		}
		else
		{
			std::cout << "TIE SCORE: The dealer won with a score of " << dealerScore << " and the player's score was " << playerScore;
			return false;
		}
		
	}
	return true;
}
int main()
{
	
	Deck aDeck = createDeck();
	shuffleDeck(aDeck);
	playBlackJack(aDeck);

}
