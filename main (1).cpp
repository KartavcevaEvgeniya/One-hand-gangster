#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class QueueRing 
{
    int* Wait;
    int MaxQueueLength;
    int QueueLength;

public:
    QueueRing(int m);
    ~QueueRing();

    void Add(int c);
    void Extract();
    void Show();
    int GetFirst();
};

QueueRing::QueueRing(int m) 
{
    MaxQueueLength = m;
    Wait = new int[m];
    QueueLength = 0;
}

QueueRing::~QueueRing() 
{
    delete[] Wait;
}

void QueueRing::Add(int c) 
{
    if (QueueLength < MaxQueueLength) 
    {
        Wait[QueueLength++] = c;
    }
}

void QueueRing::Extract() {
    if (QueueLength > 0) 
    {
        int temp = Wait[0];
        for (int i = 1; i < QueueLength; i++) 
        {
            Wait[i - 1] = Wait[i];
        }
        Wait[QueueLength - 1] = temp;
    }
}

int QueueRing::GetFirst() 
{
    return Wait[0];
}

void QueueRing::Show() 
{
    cout << GetFirst() << " ";
}

int main() 
{
    srand(time(0));

    QueueRing Q1(5);
    QueueRing Q2(5);
    QueueRing Q3(5);

    for (int i = 1; i <= 5; i++) 
    {
        Q1.Add(i);
        Q2.Add(i);
        Q3.Add(i);
    }

    int money = 100;
    char choice;

    do 
    {
        cout << "\nYour money: " << money << endl;
        cout << "Press Enter to spin!";
        cin.get();

        // Кожен барабан обертається випадково
        int n1 = rand() % 20 + 1;
        int n2 = rand() % 20 + 1;
        int n3 = rand() % 20 + 1;

        for (int i = 0; i < n1; i++)
        {    Q1.Extract();}

        for (int i = 0; i < n2; i++)
        {    Q2.Extract();}

        for (int i = 0; i < n3; i++)
        {    Q3.Extract();}

        cout << "\n-----------------\n";
        cout << "| ";
        Q1.Show();
        cout << "| ";
        Q2.Show();
        cout << "| ";
        Q3.Show();
        cout << "|\n";
        cout << "-----------------\n";

        money -= 10;

        if (Q1.GetFirst() == Q2.GetFirst() && Q2.GetFirst() == Q3.GetFirst()) 
        {
            cout << "JACKPOT! +50\n";
            money += 50;
        }
        else if (Q1.GetFirst() == Q2.GetFirst() || Q1.GetFirst() == Q3.GetFirst() || Q2.GetFirst() == Q3.GetFirst()) 
        {
            cout << "Two symbols match! +20\n";
            money += 20;
        }
        else 
        {
            cout << "No win!\n";
        }
        if (money <= 0) 
        {
            cout << "Game over!\n";
            break;
        }

        cout << "Play again?: ";
        cin >> choice;
        cin.ignore();

    } while (choice == 'y');

    return 0;
}
