#include "study_in_pink1.h"

bool readFile(
    const string &filename,
    int &HP1,
    int &HP2,
    int &EXP1,
    int &EXP2,
    int &M1,
    int &M2,
    int &E1,
    int &E2,
    int &E3)
{
    ifstream ifs(filename);
    if (ifs.is_open())
    {
        ifs >> HP1 >> HP2 >> EXP1 >> EXP2 >> M1 >> M2 >> E1 >> E2 >> E3;
        return true;
    }
    else
    {
        cerr << "The file is not found" << endl;
        return false;
    }
}

int nearestPerfectSquare(int number)
{
    if (number < 0)
        return 0;

    int lowerSquare = 0;
    int upperSquare = 0;
    int i = 0;

    while (true)
    {
        lowerSquare = i * i;
        upperSquare = (i + 1) * (i + 1);

        if (lowerSquare <= number && number < upperSquare)
        {
            break;
        }

        i++;
    }

    return (number - lowerSquare < upperSquare - number) ? lowerSquare : upperSquare;
}

void adjustEXP(int &EXP)
{
    if (EXP > 600)
        EXP = 600;
    else if (EXP < 0)
        EXP = 0;
}

void checkEXP(int &EXP1, int &EXP2)
{
    adjustEXP(EXP1);
    adjustEXP(EXP2);
}

void adjustHealth(int &Health)
{
    if (Health > 666)
        Health = 666;
    else if (Health < 0)
        Health = 0;
}

void validateHealth(int &Health1, int &Health2)
{
    adjustHealth(Health1);
    adjustHealth(Health2);
}

void adjustMana(int &Mana)
{
    if (Mana > 3000)
        Mana = 3000;
    else if (Mana < 0)
        Mana = 0;
}

void validateMana(int &Mana1, int &Mana2)
{
    adjustMana(Mana1);
    adjustMana(Mana2);
}

void initialEncounter_Scenario1(int &experience1, int &experience2, int event1)
{
    if (event1 == 0)
        experience2 += 29;
    else if (event1 == 1)
        experience2 += 45;
    else if (event1 == 2)
        experience2 += 75;
    else
        experience2 += 149;

    int Delta = event1 * 3 + experience1 * 7;
    if (Delta % 2 == 0)
        experience1 = int(ceil(experience1 + (Delta / 200.0) - 0.0001)); // Làm tròn lên
    else
        experience1 = int(ceil(experience1 - (Delta / 100.0) - 0.0001)); // Làm tròn lên

    checkEXP(experience1, experience2);
}

void initialEncounter_Scenario2(int &experience1, int &experience2, int event1)
{
    if (event1 >= 4 && event1 <= 19)
        experience2 = int(ceil(experience2 + (event1 / 4.0 + 19) - 0.0001));
    else if (event1 >= 20 && event1 <= 49)
        experience2 = int(ceil(experience2 + (event1 / 9.0 + 21) - 0.0001));
    else if (event1 >= 50 && event1 <= 65)
        experience2 = int(ceil(experience2 + (event1 / 16.0 + 17) - 0.0001));
    else if (event1 >= 66 && event1 <= 79)
    {
        experience2 = int(ceil(experience2 + (event1 / 4.0 + 19) - 0.0001));
        if (experience2 > 200)
            experience2 = int(ceil(experience2 + (event1 / 9.0 + 21) - 0.0001));
    }
    else
    {
        experience2 = int(ceil(experience2 + (event1 / 4.0 + 19) - 0.0001));
        experience2 = int(ceil(experience2 + (event1 / 9.0 + 21) - 0.0001));
        if (experience2 > 400)
        {
            experience2 = int(ceil(experience2 + (event1 / 16.0 + 17) - 0.0001));
            experience2 = int(ceil(experience2 * 1.15 - 0.0001));
        }
    }

    experience1 -= event1;
    checkEXP(experience1, experience2);
}

int firstMeet(int &exp1, int &exp2, int e1)
{
    switch (e1)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        initialEncounter_Scenario1(exp1, exp2, e1);
        break;
    default:
        if (e1 >= 4 && e1 <= 99)
            initialEncounter_Scenario2(exp1, exp2, e1);
        else
            return -99;
    }

    return exp1 + exp2;
}

double trackBaggage_Route1(int experience1)
{
    int Square;
    Square = nearestPerfectSquare(experience1);
    if (experience1 >= Square)
        return 100;
    else
        return ((experience1 / Square + 80) / 123.0) * 100;
}

double trackBaggage_Route3(int event2)
{
    int Probability[10] = {32, 47, 28, 79, 100, 50, 22, 83, 64, 11};
    int index = (event2 < 10) ? event2 : (event2 / 10 + event2 % 10) % 10;
    return Probability[index];
}

double trackBaggage_Route2(int &health1, int &experience1, int &mana1, int event2)
{
    double initialMana = mana1 * 0.5;
    bool isEventOdd = event2 % 2 == 1;
    bool isEventEven = event2 % 2 == 0;

    do
    {
        bool isHealthLow = health1 < 200;
        bool isExperienceLow = experience1 < 400;
        bool isExperienceMedium = experience1 < 300;

        health1 = int(ceil(health1 * (isHealthLow ? 1.3 : 1.1) - 0.001));
        mana1 -= isHealthLow ? 150 : 70;
        validateHealth(health1, health1);
        validateMana(mana1, mana1);

        if ((isEventOdd && mana1 < initialMana) || (isEventEven && mana1 == 0))
        {
            experience1 = int(ceil(experience1 * 1.17 - 0.001));
            health1 = int(ceil(health1 - health1 * 0.17 - 0.001));
            checkEXP(experience1, experience1);
            validateHealth(health1, health1);
            break;
        }

        mana1 -= isExperienceLow ? 200 : 120;
        experience1 = int(ceil(experience1 * 1.13 - 0.001));
        checkEXP(experience1, experience1);
        validateMana(mana1, mana1);

        if ((isEventOdd && mana1 < initialMana) || (isEventEven && mana1 == 0))
        {
            experience1 = int(ceil(experience1 * 1.17 - 0.001));
            health1 = int(ceil(health1 - health1 * 0.17 - 0.001));
            checkEXP(experience1, experience1);
            validateHealth(health1, health1);
            break;
        }

        mana1 -= isExperienceMedium ? 100 : 120;
        experience1 = int(ceil(experience1 * 0.9 - 0.001));
        checkEXP(experience1, experience1);
        validateMana(mana1, mana1);

        if ((isEventOdd && mana1 <= initialMana) || isEventEven)
        {
            experience1 = int(ceil(experience1 * 1.17 - 0.001));
            checkEXP(experience1, experience1);
            health1 = int(ceil(health1 - health1 * 0.17 - 0.001));
            validateHealth(health1, health1);
            break;
        }
    } while (true);

    return trackBaggage_Route1(experience1);
}

int chaseTaxi(int &HP1, int &EXP1, int &HP2, int &EXP2, int E3)
{
    if (E3 < 0 || E3 > 99)
        return -99;

    int taxiScore[10][10] = {0};
    int sherlockScore[10][10] = {0};

    for (int taxiRow = 0; taxiRow < 10; taxiRow++)
    {
        for (int taxiCol = 0; taxiCol < 10; taxiCol++)
        {
            taxiScore[taxiRow][taxiCol] = ((E3 * taxiCol) + (taxiRow * 2)) * (taxiRow - taxiCol);
        }
    }

    for (int sherlockRow = 0; sherlockRow < 10; sherlockRow++)
    {
        for (int sherlockCol = 0; sherlockCol < 10; sherlockCol++)
        {
            int maxLeftDiagonal = taxiScore[sherlockRow][sherlockCol];
            for (int k = 0; k < min(sherlockRow, sherlockCol); k++)
            {
                maxLeftDiagonal = maxLeftDiagonal > taxiScore[sherlockRow - k][sherlockCol - k] ? maxLeftDiagonal : taxiScore[sherlockRow - k][sherlockCol - k];
            }

            int maxRightDiagonal = taxiScore[sherlockRow][sherlockCol];
            for (int k = 0; k < min(10 - sherlockRow, sherlockCol); k++)
            {
                maxRightDiagonal = maxRightDiagonal > taxiScore[sherlockRow + k][sherlockCol - k] ? maxRightDiagonal : taxiScore[sherlockRow + k][sherlockCol - k];
            }

            sherlockScore[sherlockRow][sherlockCol] = maxLeftDiagonal > maxRightDiagonal ? maxLeftDiagonal : maxRightDiagonal;
            sherlockScore[sherlockRow][sherlockCol] = abs(sherlockScore[sherlockRow][sherlockCol]);
        }
    }

    int meetRow = 0, meetCol = 0;
    for (int taxiRow = 0; taxiRow < 10; taxiRow++)
    {
        for (int taxiCol = 0; taxiCol < 10; taxiCol++)
        {
            if (taxiScore[taxiRow][taxiCol] > E3 * 2)
                meetRow++;
            if (taxiScore[taxiRow][taxiCol] < -E3)
                meetCol++;
        }
    }

    while (meetRow >= 10 || meetCol >= 10)
    {
        if (meetRow >= 10)
            meetRow = meetRow / 10 + meetRow % 10;
        if (meetCol >= 10)
            meetCol = meetCol / 10 + meetCol % 10;
    }

    int finalScore;
    if (abs(taxiScore[meetRow][meetCol]) > sherlockScore[meetRow][meetCol])
    {
        EXP1 = int(ceil(EXP1 * 0.88 - 0.001));
        HP1 = int(ceil(HP1 * 0.9 - 0.001));
        EXP2 = int(ceil(EXP2 * 0.88 - 0.001));
        HP2 = int(ceil(HP2 * 0.9 - 0.001));
        finalScore = taxiScore[meetRow][meetCol];
    }
    else
    {
        EXP1 = int(ceil(EXP1 * 1.12 - 0.001));
        HP1 = int(ceil(HP1 * 1.1 - 0.001));
        EXP2 = int(ceil(EXP2 * 1.12 - 0.001));
        HP2 = int(ceil(HP2 * 1.1 - 0.001));
        finalScore = sherlockScore[meetRow][meetCol];
    }
    checkEXP(EXP1, EXP2);
    validateHealth(HP1, HP2);
    return finalScore;
}

int traceLuggage(int &HP1, int &EXP1, int &M1, int e2)
{
    if (e2 < 0 || e2 > 99)
        return -99;
    double prob1 = trackBaggage_Route1(EXP1);
    double prob2 = trackBaggage_Route2(HP1, EXP1, M1, e2);
    double prob3 = trackBaggage_Route3(e2);

    if (prob1 == 100 && prob2 == 100 && prob3 == 100)
        EXP1 = int(ceil(EXP1 * 0.75 - 0.001));
    else
    {
        double averageProb = (prob1 + prob2 + prob3) / 3;
        if (averageProb < 50)
        {
            HP1 = int(ceil(HP1 * 0.85 - 0.001));
            EXP1 = int(ceil(EXP1 * 1.15 - 0.001));
        }
        else
        {
            HP1 = int(ceil(HP1 * 0.9 - 0.001));
            EXP1 = int(ceil(EXP1 * 1.2 - 0.001));
        }
    }
    checkEXP(EXP1, EXP1);
    validateHealth(HP1, HP1);
    return HP1 + EXP1 + M1;
}

int findCorrectPassword(const char *arr_pwds[], int num_pwds)
{
    int maxFrequency = 0, maxLen = 0, firstIndex = 0;
    int frequency[num_pwds] = {0};

    for (int idx = 0; idx < num_pwds; ++idx)
    {
        int len = strlen(arr_pwds[idx]);
        frequency[idx]++;

        for (int jdx = idx + 1; jdx < num_pwds; ++jdx)
        {
            if (strcmp(arr_pwds[idx], arr_pwds[jdx]) == 0)
            {
                frequency[idx]++;
            }
        }

        if (frequency[idx] > maxFrequency || (frequency[idx] == maxFrequency && len > maxLen))
        {
            maxFrequency = frequency[idx];
            maxLen = len;
            firstIndex = idx;
        }
    }

    return firstIndex;
}

int checkPassword(const char *s, const char *email)
{
    string pwd(s);
    string userMail(email);
    string user = userMail.substr(0, userMail.find('@'));

    bool isLengthValid = pwd.length() >= 8 && pwd.length() <= 20;
    bool doesNotContainUser = pwd.find(user) == string::npos;
    bool hasSpecialSymbol = pwd.find_first_of("@#%$!") != string::npos;
    bool hasOnlyValidChars = pwd.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@#%$!") == string::npos;

    if (!isLengthValid)
        return pwd.length() < 8 ? -1 : -2;
    if (!doesNotContainUser)
        return -(300 + pwd.find(user));

    int idx = 0;
    while (idx < pwd.length() - 2)
    {
        if (pwd[idx] == pwd[idx + 1] && pwd[idx + 1] == pwd[idx + 2])
            return -(400 + idx);
        idx++;
    }

    if (!hasSpecialSymbol)
        return -5;

    if (!hasOnlyValidChars)
        return pwd.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@#%$!");

    return -10;
}