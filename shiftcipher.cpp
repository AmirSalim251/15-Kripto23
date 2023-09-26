/*
Nama : Amir Salim
NPM : 140810210015
Kelas :  A
Deskripsi program : Program Shift cipher
*/
#include <iostream>
using namespace std;
 

string encrypt(string text, int s)
{
    string result = "";
 
    
    for (int i = 0; i < text.length(); i++) {
       
        if (isupper(text[i]))
            result += char(int(text[i] + s - 65) % 26 + 65);
 
        
        else
            result += char(int(text[i] + s - 97) % 26 + 97);
    }
 
    
    return result;
}

string decrypt(string text, int s)
{
    string result = "";
 
    
    for (int i = 0; i < text.length(); i++) {
       
        if (isupper(text[i]))
            result += char(int(text[i] - s - 65) % 26 + 65);
 
        
        else
            result += char(int(text[i] - s - 97) % 26 + 97);
    }
 
   
    return result;
}
 

int main()
{
    string msg;
    int s;

    cout<<"=== PLAIN TEXT ===\n";
    cout<<"Text : ";
    cin>>msg;
    cout<<"\n";

    cout<<"=== KEY SHIFT ===\n";
    cout<<"Key : ";
    cin>>s;
    cout<<"\n";




    string enctext = encrypt(msg,s);
    string dectext = decrypt(enctext,s);

    cout<<"=== HASIL ===\n";
    cout << "Text : " << msg;
    cout << "\nShift: " << s;
    cout << "\nCipher: " << enctext;
    cout<<"\nDecrypt: "<< dectext;

    return 0;
}