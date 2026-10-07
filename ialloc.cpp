#include <iostream>
using namespace std;

#define TOTAL 10
#define MAX 5

struct SuperBlock
{
    int list[MAX];
    int count;
    int remembered;
};

int inode[TOTAL] = {0};
SuperBlock sb;

// Fill superblock
void refill()
{
    sb.count = 0;

    for (int i = sb.remembered; i < TOTAL && sb.count < MAX; i++)
    {
        if (inode[i] == 0)
        {
            sb.list[sb.count++] = i + 1;
            sb.remembered = i + 1;
        }
    }

    cout << "\nSuperBlock refilled!!";
}

void ialloc()
{
    if (sb.count == 0)
        refill();

    if (sb.count == 0)
    {
        cout << "\nNo Free Inode available..";
        return;
    }

    int n = sb.list[0];

    for (int i = 0; i < sb.count - 1; i++)
        sb.list[i] = sb.list[i + 1];

    sb.count--;
    inode[n - 1] = 1;

    cout << "\nInode " << n << " allocated.";
}

void ifree(int n)
{
    if (n < 1 || n > TOTAL || inode[n - 1] == 0)
    {
        cout << "\nInvalid or Already free inode";
        return;
    }

    inode[n - 1] = 0;

    if (sb.count < MAX)
    {
        sb.list[sb.count++] = n;
        cout << "\nInode " << n << " inserted in superblock.";
    }
    else
    {
        cout << "\nSuperblock full; inode " << n << " is free on disk.";
    }
}

void display()
{
    cout << "\n\nFree count = " << sb.count;
    cout << "\nFree list = ";

    for (int i = 0; i < sb.count; i++)
        cout << sb.list[i] << " ";

    cout << "\nRemembered index = " << sb.remembered + 1;
}

int main()
{
    int ch, n;

    // Initially fill superblock
    sb.remembered = 0;
    refill();

    while (1)
    {
        cout << "\n\n1. Display";
        cout << "\n2. ialloc()";
        cout << "\n3. ifree()";
        cout << "\n4. Exit";
        cout << "\nChoice: ";
        cin >> ch;

        if (ch == 1)
            display();

        else if (ch == 2)
            ialloc();

        else if (ch == 3)
        {
            cout << "Enter inode number: ";
            cin >> n;
            ifree(n);
        }

        else if (ch == 4)
            break;

        else
            cout << "\nInvalid choice!";
    }

    return 0;
}


