#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
// We know concept of Array, Function, Storage Classes 
// Enumeration For representing a Suit 
enum Suit
{
	HEART, DIAMOND, CLUB, SPADE 
};

// For preparing a Deck of 52 Cards 
// A Card have two value 1) Face Value 2) Suit value 
// So we use the concept of Parallel Array 
int DeckCardFace[52];
Suit DeckCardSuit[52];
// 0th index of DeckCardFace contain Face Value of Card 1
// 0th index of DeckCardSuit contain Suit Value of Card 1
// 1st index of DeckCardFace contain Face Value of Card 2
// 1st index of DeckCardSuit contain Suit Value of Card 2
// and so on

// We also construct an index for deck which must be picked 
int top_index;

// Prepare The Deck of Card and Shuffle it 
void PrepareDeck()
{
	int deck_index = 0;
	for( int face = 1; face <= 13; face++ )
	{
		DeckCardFace[deck_index] = face;
		DeckCardSuit[deck_index] = HEART;
		deck_index++; 
		
		DeckCardFace[deck_index] = face;
		DeckCardSuit[deck_index] = CLUB;
		deck_index++; 
		
		DeckCardFace[deck_index] = face;
		DeckCardSuit[deck_index] = DIAMOND;
		deck_index++; 
		
		DeckCardFace[deck_index] = face;
		DeckCardSuit[deck_index] = SPADE;
		deck_index++; 
	}
	srand(time(NULL));
	int temp_face, swap_index;
	Suit temp_suit;
	for( int count = 1; count <= 1000; count++ )
	{
		swap_index = rand() % 52;
		// Swapping of Face Value 
		temp_face = DeckCardFace[0] ;
		DeckCardFace[0]  = DeckCardFace[swap_index]; 
		DeckCardFace[swap_index] = temp_face;
		// Swapping of Suit Value 
		temp_suit = DeckCardSuit[0] ;
		DeckCardSuit[0]  = DeckCardSuit[swap_index]; 
		DeckCardSuit[swap_index] = temp_suit;
	}
	top_index = 0;
}

// Arrangement of Picking Player Cards as well as Dealer Cards 
// We have to given maximum number of card hold by a Player 
// 1 + 1 + 1 + 1 + 2 + 2 + 2 + 2 + 3 + 3 + 3 + 3
int PlayerCardFace[12];
Suit PlayerCardSuit[12];
int DealerCardFace[12];
Suit DealerCardSuit[12];

// We construct two index variable which convey current last position 
// of card stored in above array
int player_index = -1; // -1 represent invalid index 
int dealer_index = -1;

// Function used to pick a card from Deck and stored its value into Player Card
void PickCardForPlayer()
{
	player_index++;
	PlayerCardFace[player_index] = DeckCardFace[top_index];
	PlayerCardSuit[player_index] = DeckCardSuit[top_index];
	top_index++;
}

// Function used to pick a card from Deck and stored its value into Dealer Card
void PickCardForDealer()
{
	dealer_index++;
	DealerCardFace[dealer_index] = DeckCardFace[top_index];
	DealerCardSuit[dealer_index] = DeckCardSuit[top_index];
	top_index++;
}

// Function to Check Card Rank According to its Face 
int GetRank( int face )
{
	if( face >= 11 )
	{
		return 10;
	}
	return face;
}

// Function to Display Face String according to Card Face 
void DisplayFace( int face )
{
	if( face == 1 )
	{
		cout<<"Ace";
	}
	else if( face == 11 )
	{
		cout<<"Jack";
	}
	else if( face == 12 )
	{
		cout<<"Queen";
	}
	else if( face == 13 )
	{
		cout<<"King";
	}
	else
	{
		cout<<face;
	}
}

// Function to display Suit String using Card suit 
void DisplaySuit( Suit suit )
{
	if( suit == HEART )
	{
		cout<<"HEART";
	}
	else if( suit == SPADE )
	{
		cout<<"SPADE";
	}
	else if( suit == DIAMOND )
	{
		cout<<"DIAMOND";
	}
	else if( suit == CLUB )
	{
		cout<<"CLUB";
	}
}

// Function to calculate Total Rank of Player Cards 
int CalculateTotalRankOfPlayerCard()
{
	int total = 0;
	bool ace_found = false;
	for( int index = 0; index <= player_index; index++ )
	{
		total += GetRank( PlayerCardFace[index] );
		if( PlayerCardFace[index] == 1 )
		{
			ace_found = true;
		}
	}
	if( ace_found && total + 10 <= 21 )
	{
		total += 10;
	}
	return total;
}

// Function to calculate Total Rank of Dealer Unfolded Cards 
int CalculateTotalRankOfDealerCard()
{
	int total = 0;
	bool ace_found = false;
	for( int index = 0; index <= dealer_index; index++ )
	{
		total += GetRank( DealerCardFace[index] );
		if( DealerCardFace[index] == 1 )
		{
			ace_found = true;
		}
	}
	if( ace_found && total + 10 <= 21 )
	{
		total += 10;
	}
	return total;
}

// Function to calculate Total Rank of Dealer Folded Cards 
int CalculateTotalRankOfDealerFoldedCard()
{
	int total = 0;
	bool ace_found = false;
	for( int index = 0; index <= dealer_index; index++ )
	{
		if( index != 0 )
		{
			total += GetRank( DealerCardFace[index] );
			if( DealerCardFace[index] == 1 )
			{
				ace_found = true;
			}
		}
	}
	if( ace_found && total + 10 <= 21 )
	{
		total += 10;
	}
	return total;
}

// Function to display Player Cards 
void DisplayPlayerCards()
{
	cout<<"\n Player Cards: ";
	for( int index = 0; index <= player_index; index++ )
	{
		cout<<" [ ";
		DisplayFace( PlayerCardFace[index] );
		cout<<" of ";
		DisplaySuit( PlayerCardSuit[index] );
		cout<<" ]";
	}
	cout<<" { Total Rank: "<<CalculateTotalRankOfPlayerCard()<<" }";	
	cout<<endl;
}

// Function to display Dealer Unfolded Cards 
void DisplayDealerCards()
{
	cout<<"\n Dealer Cards: ";
	for( int index = 0; index <= dealer_index; index++ )
	{
		cout<<" [ ";
		DisplayFace( DealerCardFace[index] );
		cout<<" of ";
		DisplaySuit( DealerCardSuit[index] );
		cout<<" ]";
	}
	cout<<" { Total Rank: "<<CalculateTotalRankOfDealerCard()<<" }";	
	cout<<endl;
}

// Function to display Dealer Folded Cards 
void DisplayDealerFoldedCards()
{
	cout<<"\n Dealer Cards: ";
	for( int index = 0; index <= dealer_index; index++ )
	{
		cout<<" [ ";
		if( index == 0 )
		{
			cout<<"FOLDED";
		}
		else
		{
			DisplayFace( DealerCardFace[index] );		
			cout<<" of ";
			DisplaySuit( DealerCardSuit[index] );
		}
		cout<<" ]";
	}
	cout<<" { Total Rank: "<<CalculateTotalRankOfDealerFoldedCard()<<" }";	
	cout<<endl;
}

// Function to Start Game 
void StartGame( double bet, double & amount )
{
	player_index = dealer_index = -1;
	top_index = 0;
	
	// Prepare the Deck 
	PrepareDeck();
	
	// Pick Two Card For Player as well as Dealer 
	PickCardForPlayer();
	PickCardForDealer();
	PickCardForPlayer();
	PickCardForDealer();
	
	DisplayPlayerCards();
	DisplayDealerFoldedCards();
	
	if( CalculateTotalRankOfPlayerCard() == 21 )
	{
		cout<<"\n BLACK JACK !!! \n";
		DisplayDealerCards();
		int dealer_total = CalculateTotalRankOfDealerCard();
		while( dealer_total <= 16 )
		{
			PickCardForDealer();
			DisplayDealerCards();
			dealer_total = CalculateTotalRankOfDealerCard();
		}
		if( dealer_total == 21 )
		{
			cout<<"\n Its TIE So No Win No Lose \n";
		}
		else
		{
			cout<<"\n Player Won the Bet amount Rs. "<< bet * 1.5 <<endl;
			amount += bet * 1.5;
		}
	}
	else
	{
		bool running = true;
		int choice;
		while( running )
		{
			cout<<"\n Press 1 For Hit a Card ";
			cout<<"\n Press 2 For Stand \n";
			cout<<"\n Enter Your Choice: ";
			cin>>choice;
			if( choice == 1 )
			{
				PickCardForPlayer();
				DisplayPlayerCards();
				int player_total = CalculateTotalRankOfPlayerCard();
				if( player_total > 21 )
				{
					DisplayDealerCards();
					cout<<"\n Player Busted and Lose the Amount Rs. "<<bet<<endl;
					amount -= bet;
					running = false;
				}
				else
				{
					DisplayDealerFoldedCards();
				}
			}
			else if( choice == 2 )
			{
				int player_total = CalculateTotalRankOfPlayerCard();
				DisplayDealerCards();
				int dealer_total = CalculateTotalRankOfDealerCard();
				while( dealer_total <= 16 && dealer_total < player_total )
				{
					PickCardForDealer();
					DisplayDealerCards();
					dealer_total = CalculateTotalRankOfDealerCard();
				}
				if( dealer_total == player_total )
				{
					cout<<"\n Its TIE So No Win No Lose \n";
				}
				else if( dealer_total <= 21 && dealer_total > player_total )
				{
					cout<<"\n Player Lose the Amount Rs. "<<bet<<endl;
					amount -= bet;
				}
				else
				{
					cout<<"\n Player Won the Amount Rs. "<<bet<<endl;
					amount += bet;
				}
				running = false;
			}
			else
			{
				cout<<"\n Invalid Choice. Try Again \n";
			}
		}
	}
}

int main()
{	
	double bet, amount = 2500;
	int choice;
	bool running = true;
	while( running )
	{
		cout<<"\n Press 1 For Start A Game ";
		cout<<"\n Press 2 For Account History ";
		cout<<"\n Press 3 For Exit \n";
		cout<<"\n Enter Your Choice: ";
		cin>>choice;
		switch( choice )
		{
			case 1:
				cout<<"\n Enter Bet Amount: ";
				cin>>bet;
				if( bet > 0 && bet <= amount )
				{
					StartGame( bet, amount );
				}
				else
				{
					cout<<"\n Invalid Bet Amount Given \n";
				}
				break;
			case 2:
				cout<<"\n Your Amount Rs. "<<amount<<endl;
				break;
			case 3:
				running = false;
				cout<<"\n Exit From Game Panel \n";
				break;
			default:
				cout<<"\n Invalid Choice Try Again \n";
				break;
		}
	}
	return 0;
}
