#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;
const string ClientsFileName = "Clients.txt";

enum enMainMenueOptions { enQuickWithdraw = 1, enNormalWithdraw = 2, enDeposit = 3, enCheckBalance = 4,enLogout=5 };
void Login();
void ShowMainMenue();
void GoBackToMainMenue();
struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

stClient CurrentClient;

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   

        vString.push_back(sWord);


        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}
string ConvertRecordToLine(stClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

vector <stClient> SaveCleintsDataToFile(string FileName, vector <stClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (stClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}


stClient ConvertClientLinetoRecord(string Line, string Seperator = "#//#")
{

    stClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);
    if (vClientData.size() <= 5) {

        Client.AccountNumber = vClientData[0];
        Client.PinCode = vClientData[1];
        Client.Name = vClientData[2];
        Client.Phone = vClientData[3];
        Client.AccountBalance =stod( vClientData[4]);


       
    }
    return Client;

}

vector <stClient> LoadClientsDataFromFile(string FileName)
{

    vector <stClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            if (Line == "") continue;

            Client = ConvertClientLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}
bool FindClientByUserAccountNumberAndPinCode(string AccountNumber, string PinCode, stClient& User)
{

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    for (stClient U : vClients)
    {

        if (U.AccountNumber == AccountNumber && U.PinCode == PinCode)
        {
            User = U;
            return true;
        }

    }
    return false;

}



bool  LoadClientInfo(string AccountNumber, string PinCode)
{

    if (FindClientByUserAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient))
        return true;
    else
        return false;

}
short ReadQuickWithdrawOption() {




    cout << "Choose what do you want to do? [1 to 9]? ";
    short Choice;
    cin >> Choice;

    while (Choice <= 0) {

        cout << "Enter a valid Choice Number";
        cin >> Choice;

    }

    return Choice;


}
int ReadNumberToDeposit() {

    cout << "Enter a positive Deposit Amount? ";
    int Choice;
    cin >> Choice;

    while (Choice <= 0) {

        cout << "Enter a valid  Number";
        cin >> Choice;

    }

    return Choice;
}
short ReadNormalWithdrawOption() {




    cout << "Enter an amount multiple of 5's ? ";
    short Choice;
    cin >> Choice;

    while (Choice <= 0) {

        cout << "Enter a valid Choice Number";
        cin >> Choice;

    }

    return Choice;


}
short ReadMainMenueOption() {



    
        cout << "Choose what do you want to do? [1 to 5]? ";
        short Choice;
        cin >> Choice;

        while (Choice<= 0) {

            cout << "Enter a valid Choice Number";
            cin >> Choice;

       }

        return Choice;
    

}
enum enQuickWithdrawNumbers { Twenty=1,Fifty=2,Onehundred=3, Twohundred=4,Fourhundred=5,
 Sixhundred=6,Eighthundred=7, Onethousand=8,Exit=9};
short PerformQuickWithdrawChoice(enQuickWithdrawNumbers QuickWithdrawNumber) {

    switch (QuickWithdrawNumber) {
    case enQuickWithdrawNumbers::Twenty:
        return 20;
    case enQuickWithdrawNumbers::Fifty:
        return 50;

    case enQuickWithdrawNumbers::Onehundred:
        return 100;

    case enQuickWithdrawNumbers::Twohundred:
        return 200;

    case enQuickWithdrawNumbers::Fourhundred:
        return 400;

    case enQuickWithdrawNumbers::Sixhundred:
        return 600;

    case enQuickWithdrawNumbers::Eighthundred:
        return 800;

    case enQuickWithdrawNumbers::Onethousand:
        return 1000;

    case enQuickWithdrawNumbers::Exit:

        ShowMainMenue();

    }
}

void ShowQuickWithdrawScreen() {
    cout << "===========================================\n";
    cout << "\t\tQuick Withdraw\n";
    cout << "===========================================\n";

    cout << "\t[1] 20\t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "===========================================\n";
    cout << "Your Balance is: " << CurrentClient.AccountBalance;
    cout << endl;
    short NumberToWithdraw=PerformQuickWithdrawChoice(enQuickWithdrawNumbers(ReadQuickWithdrawOption()));
    if (NumberToWithdraw >CurrentClient.AccountBalance) {

        cout << "Your account balance is not enough";
        GoBackToMainMenue();


    }
    vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        CurrentClient.AccountBalance -= NumberToWithdraw;

        for (stClient& C : vClients) {
            if (C.AccountNumber == CurrentClient.AccountNumber) {
                C.AccountBalance = CurrentClient.AccountBalance;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                break;
            }

        }

        cout << "Done Successfully. New balance is: " << CurrentClient.AccountBalance;
        GoBackToMainMenue();
    }

   
}

void ShowNormalWithdrawScreen() {
    cout << "===========================================\n";
    cout << "\t\tNormal Withdraw\n";
    cout << "===========================================\n\n";

    short NumberToWithdraw = ReadNormalWithdrawOption();
    
  
   

    if (NumberToWithdraw>CurrentClient.AccountBalance) {
        cout << "The amount exceeds your balance, make another choice.";
        cout << "\n\nPress Anykey to continue...";
        system("pause>0");
        system("cls");
        ShowNormalWithdrawScreen();
        
    }
    while (!(NumberToWithdraw % 5 == 0)) {

        NumberToWithdraw = ReadNormalWithdrawOption();
    }


    vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        CurrentClient.AccountBalance -= NumberToWithdraw;
        for (stClient& C : vClients) {

            if (C.AccountNumber == CurrentClient.AccountNumber) {
                C.AccountBalance = CurrentClient.AccountBalance;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                break;
            }


        }
        SaveCleintsDataToFile(ClientsFileName, vClients);
        cout << "Done Successfully. New balance is: " << CurrentClient.AccountBalance;
        GoBackToMainMenue();
    }


}

void ShowDepositScreen() {
    cout << "===========================================\n";
    cout << "\t\Deposit Screen\n";
    cout << "===========================================\n\n";
    int NumberToDeposit = ReadNumberToDeposit();

    char Answer;
    cout << "Are you sure you want perfrom this transaction? y/n? ";
    cin >> Answer;
    vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
    if (Answer == 'y' || Answer == 'Y') {
        CurrentClient.AccountBalance += NumberToDeposit;
        for (stClient& C : vClients) {
            if (C.AccountNumber == CurrentClient.AccountNumber) {
               
                C.AccountBalance =CurrentClient.AccountBalance;
          
              SaveCleintsDataToFile(ClientsFileName,vClients);
                break;
            }


        }
     

        
        cout << "Done Successfully. New balance is: " << CurrentClient.AccountBalance;
        GoBackToMainMenue();


    }




}
void ShowCheckBalanceScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\t Check Balance Screen";
    cout << "\n-----------------------------------\n";
 
    cout << "Your Balance is " << CurrentClient.AccountBalance;




}
void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}
void PerfromManageClientsMenueOption(enMainMenueOptions MainMenueOption) {

    switch (MainMenueOption) {


    case enMainMenueOptions::enQuickWithdraw:
        system("cls");

        ShowQuickWithdrawScreen();
        GoBackToMainMenue();
        return;

    case enMainMenueOptions::enNormalWithdraw:
        system("cls");

        ShowNormalWithdrawScreen();
        GoBackToMainMenue();
        return;


    case enMainMenueOptions::enDeposit:
        system("cls");


        ShowDepositScreen();
        GoBackToMainMenue();
        return;

    case enMainMenueOptions::enCheckBalance:
        system("cls");

        ShowCheckBalanceScreen();
        GoBackToMainMenue();
        return;

    case enMainMenueOptions::enLogout:
        system("cls");

        Login();



    }

}

void ShowMainMenue() {


    system("cls");
    cout << "===========================================\n";
    cout << "\t\ATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    
    cout << "===========================================\n";



    PerfromManageClientsMenueOption((enMainMenueOptions)ReadMainMenueOption());


}
    void Login()
{
    bool LoginFaild = false;

    string AccountNumber, PinCode;
    do
    {
        system("cls");

        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";

        if (LoginFaild)
        {
            cout << "Invlaid AccountNumber/PinCode!\n";
        }

        cout << "Enter Username? ";
        cin >> AccountNumber;

        cout << "Enter Password? ";
        cin >> PinCode;

        LoginFaild = !LoadClientInfo(AccountNumber, PinCode);

    } while (LoginFaild);

    ShowMainMenue();

}


int main() {



	Login();

	system("pause>0");

}