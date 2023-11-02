#include <iostream>
#include <stdlib.h>
#include <windows.h>

using namespace std;

enum Frame : char
{
	leftTopCorner = char(201),
	leftBottomCorner = char(200),
	rightTopCorner = char(187),
	rightBottomCorner = char(188),
	horizontal = char(205),
	vertical = char(186),
	boldTopHorizontal = char(223),
	boldBottomHorizontal = char(220),
	boldVertical = char(219)
};

void printInfoMenu(const int arr[], const int step);

void printGameBox(const int array[], const int);

void arrayMix(int arr[], const int);

void move(int arr[], const int, const int, const int show = 1);

int findIndex(const int arr[], const int, const int number);

bool isNear(const int firstNumber, const int secondNumber);

bool isSolved(const int arr[]);

void mainInstruction(int arr[], const int);

int timeDeff(const int, const int divider = 1);

void timerInstruction(int arr[], int number);

void showTime(int number);

int main()
{
	srand(time(NULL));
	const int length{ 16 };
	int box[length]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	mainInstruction(box, length);
	
}

void printInfoMenu(const int arr[], const int step) {
	cout << "\n\t      FOR EXIT ENTER 0\n\n\n\t" << Frame::boldVertical;
	for (int i = 0; i < 25; i++) {
		if (i != 13) cout << Frame::boldTopHorizontal;
		else cout << Frame::boldVertical;
	}
	cout << Frame::boldVertical << "\n\t" << Frame::boldVertical
		<< " TIME: " << arr[0] << arr[1] << ':' << arr[2] << arr[3]
		<< " " << boldVertical << " STEP: " << step;
	if (step < 10) cout << "   ";
	else if (step > 9 && step < 100) cout << "  ";
	else if (step > 99 && step < 1000) cout << " ";
	cout << Frame::boldVertical << endl;

}

void printGameBox(const int array[], const int length) {
	int j{ 0 }, h{ 0 }, b{ 0 };
	cout << '\t' << Frame::boldVertical << Frame::boldTopHorizontal;
	for (int i = 0, j = 0; i < 23; i++) {
		cout << Frame::boldTopHorizontal;
	}
	cout << Frame::boldTopHorizontal << Frame::boldVertical << endl;

	for (int i = 0; i < length / 4; i++)
	{

		cout << '\t' << Frame::boldVertical;
		for (int i = 0; i < length / 4; i++) {
			if (array[h] != 0) {
				cout << ' ' << Frame::leftTopCorner;
				for (int i = 0; i < length / 4 - 1; i++)
					cout << Frame::horizontal;
				cout << Frame::rightTopCorner;
			}
			else cout << "      ";
			h++;
		}
		cout << ' ' << Frame::boldVertical << "\n\t" << Frame::boldVertical;
		for (int i = 0; i < length / 4; i++)
		{
			if (array[j] == 0)
				cout << "      ";
			else if (array[j] < 10)
				cout << ' ' << Frame::vertical << ' ' << array[j] << ' ' << vertical;
			else
				cout << ' ' << Frame::vertical << array[j] << ' ' << vertical;
			j++;
		}
		cout << ' ' << Frame::boldVertical << "\n\t" << Frame::boldVertical;
		for (int i = 0; i < length / 4; i++) {
			if (array[b] != 0) {
				cout << ' ' << Frame::leftBottomCorner;
				for (int i = 0; i < length / 4 - 1; i++)
					cout << Frame::horizontal;
				cout << Frame::rightBottomCorner;
			}
			else cout << "      ";
			b++;
		}
		cout << ' ' << Frame::boldVertical << endl;
	}
	cout << '\t' << Frame::boldVertical << Frame::boldBottomHorizontal;
	for (int i = 0, j = 0; i < 23; i++) {
		cout << Frame::boldBottomHorizontal;
	}
	cout << Frame::boldBottomHorizontal << Frame::boldVertical << endl;
}

void arrayMix(int arr[], const int length) {
	for (int i = 0; i < 500; i++) {
		int randNumber = rand() % 16;
		move(arr, length, randNumber, 0);
		
	}
}

int findIndex(const int arr[], const int length, const int number) {
	for (int i = 0; i < length; i++) {
		if (arr[i] == number)
			return i;
	}
	return -1;

}

bool isNear(const int firstNumber, const int secondNumber) {
	int deff = firstNumber - secondNumber;
	if (deff == 1 || deff == -1 || deff == 4 || deff == -4) 
		return true;		
	else return false;
}

bool isSolved(const int arr[]) {
	const int len{ 16 };
	int array[len]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	for (int i = 0; i < len; i++)
		if (arr[i] != array[i])
			return false;
	return true;
}

void mainInstruction(int arr[], const int length) {
	arrayMix(arr, length);
	int steps{},
		timer[4]{},
		timeStart = time(NULL);
	while (true) {
		timerInstruction(timer, timeStart);
		system("cls");
		printInfoMenu(timer, steps);
		printGameBox(arr, length);

		if (isSolved(arr)) {
			timerInstruction(timer, timeStart);
			system("cls");
			printInfoMenu(timer, steps);
			printGameBox(arr, length);
			showTime(timeStart);
			return;
		}
		
		int userNumber;
		cout << "\nSelect number: ";
		cin >> userNumber;
		if (userNumber == 0) {
			timerInstruction(timer, timeStart);
			system("cls");
			printInfoMenu(timer, steps);
			printGameBox(arr, length);
			showTime(timeStart);
			return;
		}

		move(arr, length, userNumber);
		steps++;

	}
}

void move(int arr[], const int length, const int number, const int show) {
	int zeroIndex = findIndex(arr, length, 0);
	int fIndex = findIndex(arr, length, number);
	if (isNear(zeroIndex, fIndex)) {
		int temp = arr[zeroIndex];
		arr[zeroIndex] = arr[fIndex];
		arr[fIndex] = temp;
	}
	else if (show != 0) {
		cout << "\nInvalid move! Try again.\n\n";
		system("pause");
	}
}

int timeDeff(const int number, const int divider) {
	return ((time(NULL) - number) / divider) % 10;
}

void timerInstruction(int arr[], int number) {
	int temp = number;
	arr[2] = timeDeff(temp, 10);
	arr[3] = timeDeff(temp);
	if (arr[2] == 5 && arr[3] == 9) {
		temp += 59;
		arr[2] = 0;
		arr[3] = 0;
		arr[1]++;
		if (arr[1] == 9) {
			arr[1] = 0;
			arr[0]++;
		}
	}
}

void showTime(int number) {
	int seconds = (time(NULL) - number) % 100;
	if (seconds > 59) {
		seconds = seconds % 10 + seconds - 60;
	}
	cout << "\n\t\t Exit..\n"
		<< "\t\t Time: " << (time(NULL) - number) / 60 << " m " << seconds << " s\n";
}



