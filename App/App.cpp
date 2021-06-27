// Including necessary header files
#include <wx/wx.h>
#include <wx/wxprec.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>

// Using the standard namespace
using namespace std;

// Creating the App Class from wxApp class
class App : public wxApp {
// Public section
public:
	// OnInit Function
	virtual bool OnInit();
};

// Creating the Window class from wxFrame class
class Window : public wxFrame {
// Private Section
private:
	// Variable Declarations
	wxGridSizer* gridLayout;
	wxGridSizer* gridLayout2;
	wxGridSizer* gridLayout3;
	wxGridSizer* gridLayout4;
	wxStaticText* headingLabel;
	wxStaticText* headingLabel2;
	wxStaticText* helpLabel;
	wxStaticText* guessesLabel;
	wxStaticText* clueLabel;
	wxStaticText* resultLabel;
	wxPanel* panel1;
	wxPanel* panel2;
	wxPanel* panel3;
	wxTextCtrl* numberTextCtrl;
	wxButton* submitButton;
	wxButton* replayButton;

	int originalNumber;
	int guesses = 0;
// Public Section
public:
	// Member functions declaration
	Window(const wxString& title);
	void initWindowWidgets(void);
	int generateRandomNumber(void);
	void checkNumber(wxCommandEvent &event);
	void replay(wxCommandEvent &event);

	// Event Table Declaration
	wxDECLARE_EVENT_TABLE();
};

// Start the event table
wxBEGIN_EVENT_TABLE(Window, wxFrame)
	// Binding event with the submit button
	EVT_BUTTON(10000, checkNumber)
	EVT_BUTTON(10001, replay)
wxEND_EVENT_TABLE ()

// Implementing the App
wxIMPLEMENT_APP(App);

// Window Constructor
Window::Window(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxPoint(200, 10), wxSize(1300, 700)) {
	// Window properties
	this->Center();
	this->SetBackgroundColour(wxColor(65, 195, 190));

	this->originalNumber = generateRandomNumber();

	this->initWindowWidgets();
}

// Function to init Window Widgets
void Window::initWindowWidgets() {
	/*
	This is a function which creates all the widgets 
	and sets them.

	Arguments :
		void

	Returns :
		void
	*/

	// Creating all the widgets
	this->gridLayout = new wxGridSizer(3,0,20,20);

	this->headingLabel = new wxStaticText(this, wxID_ANY, "\n\tNumber Guessing Game", wxPoint(100,50));
	this->headingLabel->SetFont(wxFont(19, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));
	this->headingLabel2 = new wxStaticText(this, wxID_ANY, "Rules Of The Game :- \n\n1. You have to guess a number between 0 to 100\n2. Clues will be given according to your guessed number. (If it is less than the original number\nthe it will say Less than the Original Number\nif it is greater then it will say it is Greater than The Original Number\n", wxPoint(100, 90));
	this->headingLabel2->SetFont(wxFont(12, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));
	this->gridLayout->Add(this->headingLabel, -1, wxEXPAND);

	this->panel1 = new wxPanel(this, wxID_ANY, wxPoint(0, 100));
	this->panel1->SetSize(wxSize(200, 200));

	this->gridLayout2 = new wxGridSizer(3, 0, 20, 20);
	this->panel1->SetSizer(this->gridLayout2);
	this->gridLayout2->Layout();

	this->gridLayout->Add(this->panel1, 1, wxEXPAND);

	this->helpLabel = new wxStaticText(this->panel1, wxID_ANY, "\n\nEnter the Number :", wxPoint(100,30));
	this->helpLabel->SetFont(wxFont(12, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));

	this->numberTextCtrl = new wxTextCtrl(this->panel1, wxID_ANY, "", wxPoint(100, 100), wxSize(1100, 40), wxNO_BORDER);
	this->numberTextCtrl->SetBackgroundColour(wxColor(24, 154, 149));
	this->numberTextCtrl->SetForegroundColour(wxColor(255, 255, 255));
	this->numberTextCtrl->SetFont(wxFont(12, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));

	this->panel2 = new wxPanel(this->panel1, wxID_ANY, wxPoint(0, 150), wxSize(1300, 150));

	this->gridLayout3 = new wxGridSizer(0, 3, 20, 20);
	this->panel2->SetSizer(this->gridLayout3);
	this->gridLayout3->Layout();

	this->submitButton = new wxButton(this->panel2, 10000, "Submit", wxPoint(100, 0), wxSize(200, 40), wxNO_BORDER);
	this->submitButton->SetBackgroundColour(wxColor(24, 154, 149));
	this->submitButton->SetForegroundColour(wxColor(0, 0, 0));
	this->submitButton->SetFont(wxFont(12, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));

	this->replayButton = new wxButton(this->panel2, 10001, "Replay", wxPoint(320, 0), wxSize(200, 40), wxNO_BORDER);
	this->replayButton->SetBackgroundColour(wxColor(42, 230, 223));
	this->replayButton->SetForegroundColour(wxColor(0, 0, 0));
	this->replayButton->SetFont(wxFont(12, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));

	this->guessesLabel = new wxStaticText(this->panel2, wxID_ANY, "Guesses Done: 0", wxPoint(1060, 10));
	this->guessesLabel->SetFont(wxFont(12, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));

	this->panel3 = new wxPanel(this, wxID_ANY, wxPoint(0, 490), wxSize(2000, 200));

	this->gridLayout4 = new wxGridSizer(2, 0, 20, 20);
	this->panel3->SetSizer(this->gridLayout4);
	this->gridLayout4->Layout();

	this->clueLabel = new wxStaticText(this->panel3, wxID_ANY, "", wxPoint(), wxSize(1300, 100), wxALIGN_CENTER);
	this->clueLabel->SetFont(wxFont(12, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));

	this->resultLabel = new wxStaticText(this->panel3, wxID_ANY, "", wxPoint(100, 70), wxSize(1100, 100), wxALIGN_CENTER);
	this->resultLabel->SetFont(wxFont(12, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));

	this->SetSizer(gridLayout);
	this->gridLayout->Layout();
}

// Function to generate random number
int Window::generateRandomNumber(void) {
	/*
	This is a member function of the Window 
	Class. This function generates random numbers
	between 0 to 100 whenever it is called

	Arguments:
		void

	Returns:
		int: a random number
	*/

	// Create and assign the random number and returns the number
	srand(time(NULL));
	int randomNumber = rand() % 101;
	return randomNumber;
}

// Function to check the number
void Window::checkNumber(wxCommandEvent &event) {
	/*
	This is a member function of the Window class
	It is called when the submit button is clicked
	This function chcks the number and shows the result according
	to it.

	Arguments :
		wxCommandEvent: event

	Returns :
		void
	*/

	// Getting the text from textbox
	wxString text = this->numberTextCtrl->GetValue();

	// Character Array
	string characterArray = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// Checking the text if it is blank
	if (text == "")
	{
		this->clueLabel->SetLabelText("Enter a number to check");
	}
	// Else
	else 
	{
		// Exception Handling
		// Trying to convert the string to integer
		wxInt64 num = wxAtoi(text);
		
		// Looping through the character array (string)
		for (int i = 0; i < characterArray.length(); i++)
		{
			// Checking if the user enters any text
			if (num == 0 && text.Contains(characterArray[i]))
			{
				// Sets the clue Label and return the function
				this->clueLabel->SetLabelText("Enter a number instead of text");
				return ;
			}
		}

		// Increase the guesses number
		this->guesses++;
		this->guessesLabel->SetLabelText("Guesses Done: " + to_string(this->guesses));

		// Check if the number is equals to the original number
		if (num == this->originalNumber)
		{
			// Setting the result label text, color and clue Label Text
			this->clueLabel->SetLabelText("You won the game at " + to_string(this->guesses) + " guesses");
			this->resultLabel->SetForegroundColour(wxColor(0, 255, 34));
			this->resultLabel->SetLabelText("That's Correct");
			this->resultLabel->Refresh();
			this->submitButton->Disable();
		}
		// Check if the number is greater than the original number
		else if (num > this->originalNumber)
		{
			// Setting the result label text, color and clue Label Text
			this->clueLabel->SetLabelText("The number is greater than the Original number");
			this->resultLabel->SetForegroundColour(wxColor(226, 49, 73));
			this->resultLabel->SetLabelText("That's Incorrect");
			this->resultLabel->Refresh();
		}
		// Else Condition (Check if the number is less than the original number)
		// This condition will be executed only when other two condition returns FALSE
		else
		{
			// Setting the result label text, color and clue Label Text
			this->clueLabel->SetLabelText("The number is less than the Original number");
			this->resultLabel->SetForegroundColour(wxColor(226, 49, 73));
			this->resultLabel->SetLabelText("That's Incorrect");
			this->resultLabel->Refresh();
		}
	}
	event.Skip();
}

// Function to replay
void Window::replay(wxCommandEvent& event) {
	/*
	This is a member function of the window class
	This function set the original number to new 
	randomly generated number from 0 to 100.
	This function also sets the clueLabel and resultLabel
	to an empty string
	It also sets the guessesLabel to 0

	Arguments :
		wxCommandEvent: event

	Returns :
		void
	*/

	// Sets all the things to default
	this->originalNumber = this->generateRandomNumber();
	this->clueLabel->SetLabelText("");
	this->clueLabel->Refresh();
	this->resultLabel->SetLabelText("");
	this->resultLabel->Refresh();
	this->guesses = 0;
	this->guessesLabel->SetLabelText("Guesses Done: " + to_string(this->guesses));
	this->numberTextCtrl->SetValue("");
	this->submitButton->Enable();
	event.Skip();
}

bool App::OnInit() {
	/*
	OnInit function
	Makes an object of Window class and show it
	Arguments :
		void

	Returns :
		bool: true
	*/
	Window* window = new Window("Number Guessing Game");
	window->Show();

	return true;
}
