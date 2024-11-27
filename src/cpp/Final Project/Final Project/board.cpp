//
//  board.cpp
//  Final Project
//
//  Created by Michael DeLeo on 4/8/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//

#include "board.h"

object::object()
{
    
    bunny_win = false;
    martian_win = false;
    taz_win = false;
    tweety_win = false;
    
    std::random_device rd;
    /*
    int pieces [7];
    
    for (int i = 0; i < 7; i++)
    {
        pieces [i] = rd() % 25;
    }
    
    for (int i = 0; i < 7; i ++)
    {
        for (int j = i-1; j >=0 ; j--)
        {
            if (pieces[i] == pieces[j])
            {
                j = i;
                pieces[i] = rd() % 25;
            }
        }
    }*/
    
    tweety = "T";
    martian = "M";
    bunny = "B";
    taz = "D";
    //Makes sure the starting values are not the same
    // int* temp;
    //temp = pieces;
    //setBoardSpace(temp);
    
    
    
}

void object::setBoardSpace(int* list)
{
    std::string temp[25];
    for (int i = 0; i < 25; i++)
    {
        temp[i] = " ";
    }
    
    temp[list[0]] = "M";//martian
    temp[list[1]] = "B";//bugs
    temp[list[2]] = "D"; //Taz
    temp[list[3]] = "T";//tweety
    temp[list[4]] = "C";//carrot
    temp[list[5]] = "C";//carrot
    temp[list[6]] = "F";//mountain
         
         
    int counter = 0;
    vector<string> t;
    board.push_back(t);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            board[i].push_back( temp[counter]);
            counter++;
            
        }
        board.push_back(t);
    }
    board.pop_back();
    return;
}

void object::runSimulation()
{
    std::random_device rd;
    /////////////////////////////////
    //here the comment below the statement, describes the statement above.
    /////////////////////////////////
    vector<string> s = {"UP", "UR", "RIGHT", "BR", "DOWN", "BL", "LEFT", "UL"};
    
    if (stillAround(bunny) && !gameOverYet())
    {
        if (bunny == "B" && stillAround("C"))
        {
            setProtagonist(bunny, next_move("C", bunny), "C");
        }
        //Finding a carrot
        else if (bunny == "B(C)")
        {
            setProtagonist(bunny, next_move("F", bunny), "F");
        }
        //Finding the mountain
        else
        {
        setProtagonist(bunny, s.at(rd()%8), " ");
        }
        //No carrots left, random movement
        printBoard();
    }

    if (stillAround(taz)&& !gameOverYet())
    {
        if (taz == "D" && stillAround("C"))
        {
            setProtagonist(taz, next_move("C", taz), "T");
        }
        //Finding a carrot
        else if (taz == "D(C)")
        {
            setProtagonist(taz, next_move("F", taz), "F");
        }
        //Finding the mountain
        else
        {
            setProtagonist(taz, s.at(rd()%8), " ");
        }
        //No carrots left
        printBoard();
    }
    if (stillAround(tweety)&& !gameOverYet())
    {
        if (tweety == "T" && stillAround("C"))
        {
            setProtagonist(tweety, next_move("C", tweety),"C");
        }
        //Finding a carrot
        else if (tweety == "T(C)")
        {
            setProtagonist(tweety, next_move("F", tweety),"F");
        }
        //Finding the mountain
        else
        {
            setProtagonist(tweety, s.at(rd()%8), " ");
        }
        //No carrots left
        printBoard();
    }
    
    if (gameOverYet()){}
    else if (martian == "M" && stillAround("C"))
    {
        setMartian(next_move("C", martian), "C");
        //also will hunt a player
    }
    //Finding a carrot
    
    else if (martian == "M(C)")
    {
        setMartian(next_move("F", martian), "F");
    }
    //Finding the mountain
    
    else
    {
        // no carrots left, hunt players only with carrots. will not necessarily target other players (without carrots), but will not be concerned about running over them
        if (bunny == "B(C)")
        {

        setMartian(next_move("C",martian),bunny);
        }
        else if (taz == "D(C)")
        {
            setMartian(next_move("C",martian),taz);
        }
        else if (tweety == "T(C)")
        {
            setMartian(next_move("C", martian),tweety);
        }
        //for all above moves against a player with a carrot
        //the condition is used to check if a carrot is possessed, then the carrot symbol is passed to say find the nearest player with a carrot
        else{
            setMartian(s.at(rd() % 8), " ");
            //random move, no carrots left. technically game is over after this turn
        }
    }
    //No carrots left
    if (stillAround(martian)){
            printBoard();
    }


    
    //Analyzes board
    
    //TODO MIKE
    
    return;
}

bool object::gameOverYet()
{
    bool carrot_checker = true;
    bool character_checker = true;
    
    std::string character_array [3] = {bunny, taz, tweety};
    
    for (int i = 0; i <5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (board[i][j] == "C" || character_array[k] == "B(C)" || character_array[k] == "T(C)" || character_array[k] == "D(C)")
                {
                    carrot_checker = false;
                }

            }
            for (int k = 0; k < 3; k++)
            {
                if (board[i][j] == character_array[k])
                {
                    character_checker = false;
                }
            }
            
        }
    }
    
    if (carrot_checker || character_checker)
    {
        //Game is Over
        return true;
    }
    else{
        //Game is not over
        return false;
    }
    
}

bool object::getResult()
{
    
    bool carrot_checker = true;
    bool character_checker = true;
    
    std::string character_array [3] = {bunny, taz, tweety};
    
    for (int i = 0; i <5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 3; k++ )
            {
                if (board[i][j] == character_array[k])
                {
                    character_checker = false;
                }
            }
        }
    }
    if (bunny_win)
    {
        std::cout << "Bunny wins!" << std::endl;
    }
    if (taz_win)
    {
        std::cout << "Tax wins!" << std::endl;
    }
    if (tweety_win)
    {
        std::cout << "Tweety wins!" << std::endl;
    }
    if(martian_win)
    {
        std::cout << "Martian wins!" << std::endl;
    }
    
    
    
    if (character_checker)
    {
        return false;
    }
    
    else{
        //getResult has been called too early
        std::cout << "ERROR IN getResult()" << std::endl;
        return false;
    }
    //Placeholder for return value
}

void object::printBoard()
{
    /*Example:
     
     _ _ _ _
     |B X X X |
     |X R X X |
     |X X G X |
     |G X X X |
     - - - -
     For the user, the Bomb and the two golds should be hidden until stepped on
     Spaces stepped on by the robot turn into "O"
     
     */
    
    std::cout << " _    _    _    _    _" << std::endl;
    for (int i = 0; i < 5; i++)
    {
        std::cout << "|";
        for (int j = 0; j < 5; j++)
        {
            /*
             if (board[i][j] == "B" || board[i][j] == "G" || board[i][j] == "X")
             {
             std::cout << "X ";
             }
             
             
             else
             */
            //For Testing
            std::cout << board[i][j] << "    ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << " -    -    -    -    -" << std::endl;
    
}



void object::setProtagonist(std::string & character, string move, std::string searching)
{
    if (stillAround(character))
    {}
    else{
        return;
    }
    //Mike you are not a programming wizard. da fuq you mixed up the coordinates of the martian and the character, no wonder it didnt work smh
    //its fixed now, you're welcome - future mike
    int x_direc = 0;
    //-1 left | 1 right | 0 y is constant
    int y_direc = 0;
    //-1 up | 1 down | 0 x is constant

   /* if (move == 0)
    {
        x_direc = 0;
        y_direc = 0;
    }*/
    if (move == "UP")
    {
        y_direc = -1;
    }
    else if (move == "UR")
    {
        y_direc = -1;
        x_direc = 1;
    }
    else if (move == "RIGHT")
    {
        x_direc = 1;
    }
    else if (move == "BR")
    {
        x_direc = 1;
        y_direc = 1;
    }
    else if (move == "DOWN")
    {
        y_direc = 1;
    }
    
    else if (move == "BL")
    {
        x_direc = -1;
        y_direc = 1;
    }
    else if (move == "LEFT")
    {
        x_direc = -1;
    }
    else if (move == "UL")
    {
        x_direc = -1;
        y_direc = -1;
    }
    //set the x and y offsets
    
    //get coordinates
    std::pair<int,int> current_loc = getPiece(character);
    
    bool check_for_carrot = false;
    for (int i = 0; i < character.size(); i++)
    {
        if (character[i] == 'C')
        {
            check_for_carrot = true;
        }
    }
    //Checks if the character has a carrot

    
    board[current_loc.first][current_loc.second] = " ";
    //empty the character's location
    
    //if character is out of bounds, this means there are no carrots left. penalized, stay still
    if (current_loc.first + y_direc < 0 || current_loc.first + y_direc > 4
        || current_loc.second +x_direc < 0 || current_loc.second + x_direc > 4)
    {
        std::cout << "OUT OF BOUNDS : PENALTY - " << character << std::endl;
        board[current_loc.first][current_loc.second] = character;
        
    }
    
    //if space is good, use it
    else if(board[current_loc.first + y_direc][current_loc.second + x_direc] == " ")
    {
        board[current_loc.first + y_direc][current_loc.second + x_direc] = character;
        //offset of the move with regards to the board. now set to the character
    }
    
    //if space contains carrot, and character has carrot, redirect to the mountain
    else if (board[current_loc.first + y_direc][current_loc.second + x_direc] == "C" && check_for_carrot)
    {
        std::random_device rd;
        board[current_loc.first] [current_loc.second] = character;  //reset character's location back to where it was
        string temp = next_move("F", character);
        std::cout << "REDIRECTING";
        setProtagonist(character, temp, "F");
        
    }
    
    //if space contains carrot, collect it
    else if (board[current_loc.first + y_direc][current_loc.second + x_direc] == "C")
    {
        board[current_loc.first + y_direc][current_loc.second + x_direc] = character + "(C)";
        character = character + "(C)";
    }
    
    //if space contains the martian, character dies and drops the carrot at its position unless the martian needs the carrot
    else if (board[current_loc.first + y_direc][current_loc.second + x_direc] == martian)
    {
        if (martian == "M(C)" && check_for_carrot)  //drop carrot. die
        {
            board[current_loc.first][current_loc.second] = "C";
            board[current_loc.first + y_direc][current_loc.second + x_direc] = martian;
        }
        if (martian == "M" && check_for_carrot) //give carrot. die
        {
            martian = martian + "(C)";
            board[current_loc.first + y_direc][current_loc.second + x_direc] = martian;
        }
        else{
            board[current_loc.first + y_direc][current_loc.second + x_direc] = martian;
        }
    }
    
    //win condition
    else if (board[current_loc.first + y_direc][current_loc.second + x_direc] == "F" && check_for_carrot)
    {
        if (character == "B(C)")
        {
            bunny_win = true;
        }
        
        else if (character == "D(C)")
        {
            taz_win = true;
        }
        
        else if (character == "T(C)")
        {
            tweety_win = true;
        }
    }
    
    //this is a "should never happen case"
    else
    {
        setProtagonist(character, next_move(searching, character), searching);
    }

    
    
    //board[current_loc.first - y_direc * speed][current_loc.second - x_direc] = "R";
    
    return;
    //TODO
    
}


void object::setMartian(string move, std::string searching)
{
    if (stillAround(martian))
    {}
    else{
        return;
    }
    int x_direc = 0;
    //-1 LEFT | 1 RIGHT | 0 x is constant
    int y_direc = 0;
    //-1 UP | 1 DOWN | 0 y is constant
    
    if (move == "UP")
    {
        y_direc = -1;
    }
    else if (move == "UR")
    {
        y_direc = -1;
        x_direc = 1;
    }
    else if (move == "RIGHT")
    {
        x_direc = 1;
    }
    else if (move == "BR")
    {
        x_direc = 1;
        y_direc = 1;
    }
    else if (move == "DOWN")
    {
        y_direc = 1;
    }
    
    else if (move == "BL")
    {
        x_direc = -1;
        y_direc = 1;
    }
    else if (move == "LEFT")
    {
        x_direc = -1;
    }
    else if (move == "UL")
    {
        x_direc = -1;
        y_direc = -1;
    }
    //set the x and y offsets
    
    
    //get coordinate
    std::string character = martian;
    std::pair<int,int> current_loc = getPiece(character);
    
    //check for possesion of carrot
    bool check_for_carrot = false;
    for (int i = 0; i < character.size(); i++)
    {
        if (character[i] == 'C')
        {
            check_for_carrot = true;
        }
    }
    
    //empty the character's space
    board[current_loc.first][current_loc.second] = " ";
    
    regex e(".+([C])+.");   //REGEX
    string newspot = board[current_loc.first + y_direc][current_loc.second + x_direc];
    bool match = regex_match(newspot,e);
    
    //out of bounds
    if (current_loc.first + y_direc < 0 || current_loc.first + y_direc > 4
        || current_loc.second + x_direc < 0 || current_loc.second + x_direc > 4)
    {
        std::cout << "ERROR IN setMartian() : OUT OF BOUNDS" << std::endl;
    }
    //Out of bounds
    
    //empty space, move to empty space
    else if(board[current_loc.first + y_direc][current_loc.second + x_direc] == " ")
    {
        board[current_loc.first + y_direc][current_loc.second + x_direc] = character;
    }
    
    //character has a carrot already, redirect to mountain...really wont happen though with A*
    else if (board[current_loc.first + y_direc][current_loc.second + x_direc] == "C" && check_for_carrot)
    {
        board[current_loc.first] [current_loc.second] = character;
        string temp = next_move("F", character);
        
        setMartian(temp, "F");
        
    }
    
    //if space contains the carrot, take carrot
    else if (board[current_loc.first + y_direc][current_loc.second + x_direc] == "C")
    {
        board[current_loc.first + y_direc][current_loc.second + x_direc] = character + "(C)";
        martian = martian + "(C)";
    }
    
    else if (match)
    {
        if (regex_match(martian,e)){
            //martian has a carrot already
            //martian has killed something with a carrot. drop carrot
            board[current_loc.first][current_loc.second] = "C";
            board[current_loc.first + y_direc][current_loc.second + x_direc] = martian;
        }
        else{
            //matches if there is a character there
            //martian has no carrot
            board[current_loc.first + y_direc][current_loc.second + x_direc] = character + "(C)";
            martian = martian + "(C)";
        }
    }
    
    //win condition
    else if (board[current_loc.first + y_direc][current_loc.second + x_direc] == "F")
    {
        martian_win = true;
    }
        return;
    
}

void object::setMountain()
{
    std::random_device rd;
    
    int first = rd() % 5;
    int second = rd() % 5;
    
    while(board[first][second] != " ")
    {
        first = rd() % 5;
        second = rd() % 5;
    }
    
    std::pair<int,int> mount = getPiece(("F"));
    board[mount.first][mount.second] = " ";
    board[first][second] = "F";

    return;

}

std::pair<int,int> object::getPiece(std::string character)
{
    std::pair<int,int> temp;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[i][j] == character)
            {
                temp.first = i;
                temp.second = j;
                
                return temp;
            }
        }
    }
    std::cout <<"ERROR in getPiece() : " << character << std::endl;
    if (character == "C" || character == "F")
    {}
    else{
        
    }
    return std::pair<int,int> (-1,-1);
    
    
}

bool object::stillAround(std::string character)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[i][j] == character)
            {
                return true;
            }
        }
    }
    
    return false;
}




//Precondition: posr is y coordinate, posc is x coordinate
string object::next_move(std::string end, std::string begin) {
    int posr, posc;
    posr = -1;
    posc = -1;
    std::cout << begin << std::endl;

    //i have to use the string board (vector vector string, because that is the format)
    for (int i = 0; i < board[0].size(); i++){
        for (int j = 0; j < board[0].size(); j++){
            if (this->board[i][j] == begin){
                posr = i;
                posc = j;
            }
        }
    }
    int linearPosition = posr * board.size() + posc+1;
    
    //First, determine the closest goal
    //make a distance matrix
    vector<vector<int>> distances;
    vector<int> t;
    distances.push_back(t);
    for(int i  = 0; i < board[0].size(); i++){
        for(int j = 0; j < board[0].size(); j++){
            if (this->board[i][j] == begin){
                distances.at(i).push_back(0);
            }//starting position
            else{
                distances.at(i).push_back(1);
            }//empty space or dirt
        }//end of line
        distances.push_back(t);
    }
    distances.pop_back();
    //now make a list of the goals
    vector<int> goals;
    int count = 0;
    
    //a note about the following.. to find C is a carrot or a player with a carrot
    //the following uses regex to find if there is a carrot in any space
    //that is.. if the martian is moving now
    if (begin == martian && end == "C"){
        for (int i = 0; i < board[0].size(); i++){
            for(int j = 0; j < board[0].size(); j++){
                regex e(".+([C])+.");   //REGEX
                bool match = regex_match(board[i][j],e);
                if (match){
                    goals.push_back(i*(board.size())+(j+1));
                }
                else{
                    regex b("([C])");
                    if (regex_match(board[i][j],b)){
                        goals.push_back(i*(board.size())+(j+1));
                    }
                }
                //use regex to identify if a character has a carrot
            }
            
        }   //not sure if \n counts as one or two characters
        //i now have the list of goal ID's
    }
    else{
        //this is either not the martian, or the martian looking for the mountain
        //note there is no consideration for avoiding the martian
        for (int i = 0; i < board[0].size(); i++){
            for(int j = 0; j < board[0].size(); j++){
                if (board[i][j] == end){
                    goals.push_back(i*(board.size())+(j+1));
                }

            }
            
        }   //not sure if \n counts as one or two characters
        //i now have the list of goal ID's
    }
    
    //find the goal with lowest F distance from the bot
    int minID = goals[0];
    int min = heuristic(linearPosition, goals[0], distances);
    for(int i = 0; i < goals.size();i++){
        if (heuristic(linearPosition, goals[i], distances) < min){
            minID = goals[i];
            min = heuristic(linearPosition, goals[i], distances);
        }
    }//finds closest goal, and saves the ID
    
    //that is the selected goal
    int goal = minID;
    
    vector<string> nboard;
    string n;
    nboard.push_back(n);
    count = 1;
    for(int i = 0; i < board.size(); i++){
        for (int j = 0; j < board.size(); j++){
            if (count == linearPosition){
                nboard[i].push_back('s');   //start
            }
            else if (count == goal){
                nboard[i].push_back('g');   //goal
            }
            else if (board[i].at(j) == " "){
                nboard[i].push_back('-');   //empty
            }
            else if (begin == martian){ //the martian doesnt treat other players as obstacles
                
            }
            else{   //other player treats other players and things as obstacles
                nboard[i].push_back('d');
            }
            count++;
        }
        nboard.push_back(n);
    }
    nboard.pop_back();
    //Go through the Astar algorithm, find shortest path and choose only the first step
    vector<string> path = finalPath(distances.size(),nboard);
    cout << path[0] << endl;
    return path[0];
}




std::string ** object::shrink(std::string searching, std::pair<int,int> size, std::pair<std::pair<int,int>, std::pair<int,int>> bc, std::string ** set)
{
    std::pair<int,int> finalf = bc.first;
    std::pair<int,int> charc = bc.second;
    
    int carrotx = finalf.first;
    int carroty = finalf.second;
    
    int charcx = charc.first;
    int charcy = charc.second;
    
    int diffx = carrotx - charcx;
    int diffy = carroty - charcy;
    
    int newx = 0;
    int newy = 0;
    for (int i = 0; i < size.first; i++)
    {
        for (int j = 0; j < size.second; j++)
        {
            if (set[i][j] == searching)
            {
                newx = i;
                newy = j;
                i = size.first;
                j = size.second;
            }
        }
    }
    
    
    
    std::string ** newset = new std::string * [size.first - 1];
    for (int i = 0; i < (size.first - 1); i++)
    {
        newset[i] = new std::string [size.second - 1];
    }

    
    if (diffx > 0 && diffy > 0)
    {
        newx--;
        newy--;
        
        set[newx][newy] = searching;
        for (int i = 0; i < (size.first - 1); i++)
        {
            for (int j = 0; j < (size.second -1 ); j++)
            {
                newset[i][j] = set[i][j];
            }
        }
      
    }
    
    else if (diffx < 0 && diffy > 0)
    {
        newx++;
        newy--;
        
        set[newx][newy] = searching;
        for (int i = 1; i < (size.first); i++)
        {
            for (int j = 0; j < (size.second -1 ); j++)
            {
                newset[i-1][j] = set[i][j];
            }
        }
      
    
    }
    
    else if (diffx < 0 && diffy < 0)
    {
        newx++;
        newy++;
        
        set[newx][newy] = searching;
        for (int i = 0; i < (size.first - 1); i++)
        {
            for (int j = 0; j < (size.second -1 ); j++)
            {
                newset[i][j] = set[i+1][j+1];
            }
        }
       

    }
    
    else if (diffx > 0 && diffy < 0)
    {
        newx--;
        newy++;
        
        set[newx][newy] = searching;
        for (int i = 0; i < (size.first - 1); i++)
        {
            for (int j = 1; j < (size.second); j++)
            {
                newset[i][j-1] = set[i][j];
            }
        }

    }
    
    
    for (int i = 0 ; i < size.first -1; i++)
    {
        for (int j = 0; j < size.second -1; j++)
        {
            std::cout << newset[i][j];
        }
        std::cout << std::endl;
    }
    
    return newset;
    
}

bool object::isVecEq(std::vector<int> V1, std::vector<int> V2)
{
    if (V1.size() != V2.size())
    {
        return false;
    }
    int it_start = 0;
    for (int i = 0; i < V1.size();i++)
    {
        if (V1[i] == V2[i])
        {
            it_start++;
        }
        else{
            i = V1.size();
        }
    }
    //Starts the iterator position to save time
    
    if (it_start == V1.size())
    {
        return true;
    }
    //Checks if the entire vector is the same
   
    if (it_start != 0)
    {

        it_start = it_start -1;
    }
    bool trip = true;
    while(std::next_permutation(V2.begin() + it_start, V2.end()))
    {
        
        trip = true;
        for (int i = 0 + it_start; i < V1.size(); i++)
        {
            if (V1.at(i) != V2.at(i))
            {
                trip = false;
            }

        }
        if (trip)
        {
            return true;
        }
    }
    trip = true;
    for (int i = 0 + it_start; i < V1.size(); i++)
    {
        if (V1.at(i) != V2.at(i))
        {
            trip = false;
        }
        
    }
    if (trip)
    {
        return true;
    }
    
    return false;
}

bool object::isNextTo(std::pair<int,int> piece, std::pair<int,int> next)
{
	if (abs(next.first - piece.first) == 1 || abs(next.second - piece.second) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename Iterator>
inline bool object::next_combination(const Iterator first, Iterator k, const Iterator last)
{
    /* Credits: Thomas Draper */
    if ((first == last) || (first == k) || (last == k))
        return false;
    Iterator itr1 = first;
    Iterator itr2 = last;
    ++itr1;
    if (last == itr1)
        return false;
    itr1 = last;
    --itr1;
    itr1 = k;
    --itr2;
    while (first != itr1)
    {
        if (*--itr1 < *itr2)
        {
            Iterator j = k;
            while (!(*itr1 < *j)) ++j;
            std::iter_swap(itr1,j);
            ++itr1;
            ++j;
            itr2 = k;
            std::rotate(itr1,j,last);
            while (last != j)
            {
                ++j;
                ++itr2;
            }
            std::rotate(k,itr2,last);
            return true;
        }
    }
    std::rotate(first,k,last);
    return false;
}

































