

#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


// The initilize our lexer, we need to get the contents of a file
lexer_T* init_lexer(char* contents)
{
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT)); // Create a lexer variable
    lexer->contents = contents; // Set the contents of the lexer to what we got
    lexer->i = 0; // Set the current index to 0
    lexer->c = contents[lexer->i]; // Set the current charecter to be the index
    
    return lexer; // return the lexer we created
}

// Move the current char to the next one, if it is the last char, it will not be called
void lexer_advance(lexer_T* lexer)
{
    // Declare an 'if' statment so that it is not the end of the file, also to check if it is not an empty space
    if (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
    {
        // Increase the index by 1
        lexer->i++;
        // Set the current char to the current char in the file contents
        lexer->c = lexer->contents[lexer->i];
    }
}

// A function to skip whitespace
void lexer_skip_whitespace(lexer_T* lexer)
{
    // If there is an empty space, or a '\n', we will call the advance function to skip the line
    while (lexer->c == ' ' || lexer->c == 10) // Create a while loop to search the current character
    {
        lexer_advance(lexer); // Call the advance function
    }
}

// Get the next token in the contents of the file
token_T* lexer_get_next_token(lexer_T* lexer)
{
    // Create a while loop to search for the next token in the file contents
    while (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
    {
        // If there is any whitespace, we will call the whitespace function
        if (lexer->c == ' ' || lexer->c == 10)
            lexer_skip_whitespace(lexer);
        
        // If it is an alphbet or a number, collect the name or the identifier
        if (isalnum(lexer->c))
            return lexer_collect_id(lexer);
        
        // If there is a string, we will collect the contents of a string
        if (lexer->c == '"')
            return lexer_collect_string(lexer);
        
        // If there is a accent sign, we will collect the contents of that accent sign
        if (lexer->c == '`')
            return lexer_collect_include_string(lexer);
        
        // If none of this alply, we will do a switch statment
        switch (lexer->c)
        {
                // We will just skip all of these signs
                
            case '=': return lexer_advance_with_token(lexer, init_token(token_equals, lexer_get_current_char_as_string(lexer))); break;
            case '(': return lexer_advance_with_token(lexer, init_token(token_left_parenthesis, lexer_get_current_char_as_string(lexer))); break;
            case ')': return lexer_advance_with_token(lexer, init_token(token_right_parenthesis, lexer_get_current_char_as_string(lexer))); break;
        }
    }
    
    return (void*)0;
}

// Get the insides of a string
token_T* lexer_collect_string(lexer_T* lexer)
{
    // Skip the '"' sign in the string
    lexer_advance(lexer);
    
    // Get a varible that is the contents of the string
    char* value = calloc(1, sizeof(char));
    // set the value to 0
    value[0] = '\0';
    
    // Create a while loop as long as it doesn't reach the last '"' sign
    while (lexer->c != '"')
    {
        // Convert the char to a string
        char* s = lexer_get_current_char_as_string(lexer);
        
        // Set the value to be equal to the things inside the string
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        // Merge value and s toghter
        strcat(value, s);
        
        // Go to the next char
        lexer_advance(lexer);
    }
    //if (value == "")
    // go to the next char
    lexer_advance(lexer);
    
    // Return an init token
    return init_token(token_char, value);
}

// Same thing as the 'lexer_collect_string' functoin but it's for the '`' type of strings
token_T* lexer_collect_include_string(lexer_T* lexer)
{
    lexer_advance(lexer);
    
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';
    
    while (lexer->c != '`')
    {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);
        
        lexer_advance(lexer);
    }
    lexer_advance(lexer);
    printf("FOUND INCLUDE STRING FILE \n");
    return init_token(token_grave_accent, value);
}

// Collect the ID of the token
// Works the same way as the 'lexer_collect_string' function
token_T* lexer_collect_id(lexer_T* lexer)
{
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';
    
    while (isalnum(lexer->c))
    {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);
        
        lexer_advance(lexer);
    }
    
    // Check if there is an include statment
    if (value[0] == 'i' && value[1] == 'n' && value[2] == 'c' && value[3] == 'l' && value[4] == 'u' && value[5] == 'd') {
        printf("FOUND INCLUDE STATEMENT");
        printf("\n");
    }
    
    return init_token(token_char, value);
}

// This is advance with a token
token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token)
{
    lexer_advance(lexer);
    
    return token;
}

// Convert the current char as a string
char* lexer_get_current_char_as_string(lexer_T* lexer)
{
    char* str = calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';
    
    return str;
}