/*
 * Part1.cpp
 *
 *  Created on: 2016-06-05
 *      Author: alfonso
 */

// Tokenizer
//by Alfonso Diaz || ENSC251
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>

using std::string;
using namespace std;

bool isSpecialChar(char c);

vector<string> tokenizeCodeStrip(istream& code)
{

    string str;
    code.ignore(256, '\n');
    getline(code,str);
    int strIndex = 0;
	int strLength = str.length();

	vector<string> tokens;
	string placeholder;

	//find spaces
	int qCounter=0;

	while (strIndex < strLength){
	    char temp = str.at(strIndex);
	    if(temp == '\"'){
            qCounter++;
        }
        if (qCounter%2==0){
            if(temp == ' '){
                tokens.push_back(placeholder);
                placeholder.clear();
            }
            else{

                placeholder += str.at(strIndex);
            }
	        strIndex++;
        }
        else{
            placeholder += str.at(strIndex);
            strIndex++;
        }
	}
	//Add whatever is left in the placeholder to tokens
	if(placeholder.length() > 0){
	    tokens.push_back(placeholder);
	}
	placeholder.clear();

	//find special characters
	vector<string> tempVector;

	for(int i = 0; i < tokens.size(); i++){ //going through each token
    	for(int k = 0; k < tokens[i].length(); k++){//each letter into a token

    		char currentChar = tokens[i].at(k);// converting the tokens's letters into a character

	        if(isSpecialChar(currentChar)){
                stringstream stringIO;

                //check for ++ or -- or !=
                if(currentChar == '!'){
                    char next = tokens [i].at(k+1);
                    if( next == '=' ){
                        stringIO << tokens[i].at(k);
                        k++;
                    }
                }

                if(currentChar == '+'){
                    char next = tokens [i].at(k+1);
                    if( next == '+' ){
                        stringIO << tokens[i].at(k);
                        k++;
                    }
                }

                if(currentChar == '-'){
                    char next = tokens [i].at(k+1);
                    if( next == '-' ){
                        stringIO << tokens[i].at(k);
                        k++;
                    }
                }

                if(!placeholder.empty()){
                	tempVector.push_back(placeholder);//add previous
                }
                placeholder.clear();

                stringIO << tokens[i].at(k);
                stringIO >> placeholder;
                tempVector.push_back(placeholder);//add special Character

                placeholder.clear();

	        }
	        else{
	            placeholder += tokens[i].at(k);
	        }


    	}
    	//Finished from reading a token, so put what it has
    	//in a new instance of a vector before reading the next
    	if(!placeholder.empty()){
    	   	tempVector.push_back(placeholder);//add previous
    	}
    	placeholder.clear();

	}

	tokens.swap(tempVector); //tempVector used for testing
    return tokens;
}

bool isSpecialChar(char c){
    bool isSpecialChar = false;
    char specialChar[] = {'!','\r','#','$','%','&','(',')','*','+',',','-','/',':',';','<','=','>','\?','@','[',']','-','{','|','}','~'};//convert to char


    for (int i = 0 ; i < 26; i++){

        if (c == specialChar[i]){
            isSpecialChar = true;
            break;
        }
    }
    return isSpecialChar;
}

int main()
{
    istringstream code("#define MYDEFINE \r\n str=\"\\\"\"+\"'\";");
    vector<string> v_string = tokenizeCodeStrip(code);
    int i = 0;
    while(!v_string.empty()){
        cout << v_string[i] << endl;

        i++;
    }
	return 0;
}


