#include <iostream>
#include <vector> // for array lists 
#include <fstream>
#include <string>
#include <cstdlib> // required for random intgers for random shift 
#include <ctime> // required for random see generator for ecnryption 
#include <cctype> // isalpha() islower() isalum() all dependant on this tag
using namespace std; 

class PasswordManager { 
private:
    string MP;
    vector<pair<string, string>> credentials; // username and password pair managing several passwords
    string filename = "passwords.txt";
    int SQ = 3; // shift quantity of a character in the password

public:
    // Caesar cipher encryption
    string encrypt(string text) { //encrpt takes each character of the password and runs adds 3 hence SQ's value and then divides it by 26 leaving the leftover to become the balue that shift each character
        string result = text;
        for (char& c : result) {
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                c = ((c - base + SQ) % 26) + base; // 
            }
        }
        return result;
    }

    // Caesar cipher decryption 
    string decrypt(string text) { //decrypt does everything the encrypt function does but in reverse deducting 3 and dividing instead of adding
        string result = text;
        for (char& c : result) {
            if(isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                c = ((c - base - SQ + 26) % 26) + base;
            }
        }
        return result;
    }

    // sets MP (master password) checks the length of password is bigger then 6
    bool setMP(string pass) {
        if (pass.length() < 6) {
            cout << "Master password must be at least 6 characters!" << endl;
            return false;
        }
        MP = encrypt(pass); //assigns mp to password which is true to the condtional for both the if condtion and master password
        cout << "Master password set successfully!" << endl;
        return true;
    }

    // check MP
    bool CheckMP(string pass) { 
        return encrypt(pass) == MP;
    }

    // add credential
    void addCredential(string user, string pass) { 
        // checks if username already exists
        for (auto& cred : credentials) { 
            if (cred.first == user) {
                cred.second = encrypt(pass); // updates password by assigning new credeintal to password
                cout << "Password updated for: " << user << endl;
                return;
            }
        }
        // add new credential
        credentials.push_back({user, encrypt(pass)}); // adds a new credeintal to the list 
        cout << "Credential added for: " << user << endl; 
    }

    // get credential
    string getCredential(string user) { // credenitals string is found via number assocaited with the encrypted infromation which is then reversed via the base - SQ calc then divided by 26 to decrypted the whole string
        for (auto& cred : credentials) {
            if (cred.first == user) {
                return decrypt(cred.second);
            }
        }
        return ""; // Return empty if not found
    }

    // delete credential
    void deleteCredential(string user) {
        for (auto it = credentials.begin(); it != credentials.end(); ++it) {
            if (it->first == user) {
                credentials.erase(it);
                cout << "Deleted credential for: " << user << endl;
                return;
            }
        }
        cout << "User not found: " << user << endl;
    }

    // save to file
    void saveToFile() { //saves to file via save to file via ofstream(output file)
        ofstream file(filename);
        if (!file) {
            cout << "Error saving file!" << endl;
            return;
        }

        for (auto& cred : credentials) { 
            file << cred.first << "|" << cred.second << endl; 
        }
        file.close();
        cout << "Saved " << credentials.size() << " credentials to file" << endl; 
    }
    
    // Load from file
    void loadFromFile() { 
        ifstream file(filename); // loads to file via ifstream (input file stream)
        if (!file) {
            cout << "No save file found (this is normal on first run).\n";
            return;
        }
        
        credentials.clear();
        string line;
        int count = 0;
        
        while (getline(file, line)) {
            size_t pos = line.find('|');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                string encryptedPass = line.substr(pos + 1);
                credentials.push_back({user, encryptedPass});
                count++;
            }
        }
        file.close();
        cout << "Loaded " << count << " credentials from file.\n";
    }

    // Display all credentials
    void displayAll() {
        if (credentials.empty()) {
            cout << "No credentials stored.\n";
            return;
        }
        
        cout << "\n--- Stored Credentials ---\n";
        for (int i = 0; i < credentials.size(); i++) {
            cout << i+1 << ". Username: " << credentials[i].first << endl; // each list item is saved chronlgically in the vector list
            cout << "   Password (encrypted): " << credentials[i].second << endl;
            cout << "   Password (decrypted): " << decrypt(credentials[i].second) << endl << endl;
        }
    }

    // Generate random password
    void generateRandomPassword() {
        string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$"; //uses whole alphabet to mix and match letters and characters for a password
        string password;
        
        for (int i = 0; i < 12; i++) {
            password += chars[rand() % chars.length()];
        }
        
        cout << "Generated password: " << password << endl;
        
        // Ask if user wants to save it
        cout << "Enter username to save with this password (or 'cancel'): ";
        string user;
        cin >> user;
        
        if (user != "cancel") {
            addCredential(user, password);
        }
    }
};

// Main function
int main() {
    PasswordManager passwordManager;
    string input;
    srand(time(0)); // responsible for random intergers 
    
    cout << "=== PASSWORD MANAGER ===\n";
    while (true) { // condtional to make sure MP is six characters
        cout << "Set master password (min 6 chars): ";
        cin >> input;
        if (passwordManager.setMP(input)) break; // sets master password
    }
    
    int attempts = 0;
    bool loggedIn = false;
    
    while (!loggedIn && attempts < 3) {
        cout << "\nEnter master password (attempt " << attempts+1 << "/3): ";
        cin >> input;
        
        if (passwordManager.CheckMP(input)) {
            loggedIn = true;
            cout << "Login successful!\n";
        } else {
            attempts++;
            cout << "Incorrect password.\n";
        }
    }
    
    if (!loggedIn) { // responsible for triggering a lock out affect if int attempts hits 3 attempts 
        cout << "Too many failed attempts. Exiting.\n"; 
        return 1;
    }
    
    int choice;
    do {
        cout << "\n=== PASSWORD MANAGER MENU ===\n";
        cout << "1. Add Credentials\n";
        cout << "2. Get Credentials\n";
        cout << "3. generate random password\n";
        cout << "4. Delete Credentials\n";
        cout << "5. update password\n";
        cout << "6. Save to File\n";
        cout << "7. Load from File\n";
        cout << "8. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        string user, pass; // structure for credenital input going username then password
        
        switch(choice) {
            case 1:
                cout << "Enter username: ";
                cin >> user;
                cout << "Enter password: ";
                cin >> pass;
                passwordManager.addCredential(user, pass);
                break;
                
            case 2:
                cout << "Enter username: ";
                cin >> user;
                pass = passwordManager.getCredential(user); // password manager gets username to output name and password
                if (!pass.empty()) {
                    cout << "Password for " << user << ": " << pass << endl;
                } else {
                    cout << "User not found.\n";
                }
                break;
                
            case 3:
                cout << "enter username: ";
                passwordManager.generateRandomPassword(); // calls the generate random password function
                break;
            case 4:
                cout << "Enter username to delete: ";
                cin >> user;
                passwordManager.deleteCredential(user);
                break;
                
            case 5:
                cout << "Enter username you want to change: " << endl;
                    cin >> user;
                cout << "enter new password: " << endl;
                    cin >> pass; 
                
                passwordManager.addCredential(user,pass); // gets username that password is assoicated with to update 
                break;
            case 6:
                passwordManager.saveToFile();
                break;
                
            case 7:
                passwordManager.loadFromFile();
                break;
                
            case 8:
                cout << "Goodbye!\n";
                break;
                
            default:
                cout << "Invalid choice.\n";
        }
        
    } while (choice != 8);
    
    return 0;
}
