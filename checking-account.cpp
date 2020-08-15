/*File Name: jgl397_hw12.cpp
  Author: Jin Gyu Lee
  Email Address: jgl397@nyu.edu, ccjglingm07@gmail.com
  Assignment Number: 12
  Description: The program will read in, from the console, the following for all checks
			   that were not cashed as of the last time you balanced your checkbook:
			   the number of each check (int),
			   the amount of the check (double),
			   and whether or not it has been cashed (1 or 0, ture or false, boolean in the array).

			   The program outputs the total of the checks cashed, the total of the deposits,
			   what the new balance should be, and how much this figure differs from
			   what the bank says the new balance is.

			   It also outputs two lists of checks:
			   the checks cashed since the last time you balanced your checkbook
			   and the checks still not cashed, in sorted order from lowest to highest check number.
  Last Changed: July 06, 2019
*/

#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

class Money {
	long allCents;
public:
	friend Money operator +(const Money& amount1, const Money& amount2);
	//Retruns the sum of the values of amount 1 and amount2.

	friend Money operator -(const Money& amount, const Money& amount2);
	//Returns amount1 minus amount2.

	friend Money operator -(const Money& amount);
	//Returns the negative of the value of amount.

	friend bool operator ==(const Money& amount1, const Money& amount2);
	//Returns true if amount1 and amount2 have the same value; false otherwise.

	friend bool operator <(const Money& amount1, const Money& amount2);
	//Returns true if amount1 is less than amount2; false otherwise.

	Money(long dollars, int cents);
	/*Initializes the object so its value represents an amount with the dollars and cents given
	  by the arguments. If the amount is negative, then both dollars and cents should be negative.
	*/

	Money(double amount);
	//Initializes the object so its value represents $amount.

	Money(long dollars);
	//Initializes the object so its value represents $dollars.00.

	Money();
	//Initializes the object so its value represents $0.00.

	double getValue() const;
	//Returns the amount of money recorded in the data portion of the calling object.

	void setValue(double newAmount);
	//Sets the value of amount to be newAmount.

	friend istream& operator >> (istream& ins, Money& amount);
	/*Overloads the >> operator so it can be used to input values of type Money.
	  Notation for inputting negative amounts is as in -$100.00.
	  Precondition: If ins is a file input stream, then ins has already been connected to a file.
	*/

	friend ostream& operator << (ostream& outs, const Money& amount);
	/*Overloads the << operator so it can be used to output values of type Money.
	  Precedes each output value of type Money with a dollar sign.
	  Precondition: If outs is a file output stream, then outs has already been connected to a file.
	*/

	void operator =(const Money& moneyRHS);
	//assigns moneyRHS to this object.
};

class Check {
	int checkNum;
	bool cashed;
	Money amount;
public:
	Check(int newCheckNum, double newAmount, bool newCashed);
	/*Initializes the object so its value represents a check with its check number, its amount
	  and information on whether it has been cashed or not.
	*/
	Check();
	/*Initializes the object so its value represents an uncashed check with
	  check number of -1, and amount $0.00.
	*/

	int getCheckNum() const;
	//Returns the number of check recorded in the data portion of the calling object.

	Money getAmount() const;
	//Returns the amount of check recorded in the data portion of the calling object.

	bool getCashed() const;
	//Returns information on whether check of the calling object has bee cashed or not.

	void setCheckNum(int newCheckNum);
	//Sets the value of check number to be newCheckNum.

	void setAmount(double newAmount);
	//Sets the value of amount to be newAmount.

	void setCashed(char YorN);
	//Sets the information on whether the check has been cashed or not.

	void input(istream& ins, ostream& outs);
	/*inputs information of the number of check, the amount of check,
	  and on whether the check has been cashed or not.
	*/

	void output(ostream& outs);
	/*outputs information of the number of check, the amount of check,
	  and on whether the check has been cashed or not.
	*/

	friend bool operator >(const Check& checkNum1, const Check& checkNum2);
	//Returns true if check number of checkNum1 is greater than that of checkNum2; false otherwise.

	void operator =(const Check& checkRHS);
	//assigns checkRHS to this object.
};

int digitToInt(char c);
/*Used in the definition fo the overloaded input operator >>.
  Precondition: c is one of the digits '0' through '9'.
  Returns the integer for the digit; for example, digit_to_int('3') returns 3.
*/

vector<Check> makeChecksVec();
// It returns vector of Checks that have been inputted.

vector<double> makeDepositVec();
// It returns vector of deposits that have nee inputted.

void sortAscending(vector<Check>& checks);
//It sorts the checks in sorted order from lowest to highest check number.

Money sumChecks(vector<Check> checks);
//It returns a total sum of amount of checks.

void outputChecks(vector<Check> checks);
//It outputs each Checks in checks.

void outputResult(Money& oldBalance, Money& newBalance, Money& pendingBalance, Money& totalCashedAmount,
	Money& totalUncashedAmount, Money& depositSum, vector<Check> checks, vector<double> deposits);
/*It outputs the reult of oldBalance, newBalance, pendingBalance,
  the diffrerence of newBalance and pendingBalance,
  the totalCasheAmount, the depositSum,
  and all of the checks.
*/

int main() {
	Money oldBalance, newBalance, pendingBalance, totalCashedAmount, totalUncashedAmount, depositSum;
	vector<Check> checks;
	vector<double> deposits;

	cout << "Please input your old account balance (using standard decimal notation, e. g. '123.65'): ";
	cin >> oldBalance;

	checks = makeChecksVec();

	cout << "Please add your bank deposits. Enter each deposit on a separate line,\n"
		<< "followed by a deposit of '0.00' to stop:" << endl;
	deposits = makeDepositVec();

	cout << "========================================================" << endl << endl;

	outputResult(oldBalance, newBalance, pendingBalance, totalCashedAmount, totalUncashedAmount,
		depositSum, checks, deposits);

	return 0;
}


Money operator +(const Money& amount1, const Money& amount2) {
	Money temp;
	temp.allCents = amount1.allCents + amount2.allCents;
	return temp;
}

Money operator -(const Money& amount1, const Money& amount2) {
	Money temp;
	temp.allCents = amount1.allCents - amount2.allCents;
	return temp;
}

Money operator -(const Money& amount) {
	return -amount.allCents;
}

bool operator ==(const Money& amount1, const Money& amount2) {
	return (amount1.allCents == amount2.allCents);
}

bool operator <(const Money& amount1, const Money& amount2) {
	return amount1.allCents < amount2.allCents;
}

Money::Money(long dollars, int cents) {
	if (dollars * cents < 0) {
		cout << "Illegal values for dollars and cents.\n";
		exit(1);
	}
	allCents = dollars * 100 + cents;
}

Money::Money(long dollars) : allCents(dollars * 100) {}

Money::Money(double amount) : allCents(floor(amount * 100)) {}

Money::Money() : allCents(0) {}

double Money::getValue() const {
	return (allCents * 0.01);
}

void Money::setValue(double amount) {
	allCents = floor(amount * 100);
}

int digitToInt(char c) {
	return (static_cast<int>(c) - static_cast<int>('0'));
}

istream& operator >> (istream& ins, Money& amount) {
	char oneChar, decimalPoint,
		digit1, digit2; //digits for the amount of cents
	long dollars;
	int cents;
	bool negative; //set to true if amount is negative

	//read '$'
	ins >> oneChar;
	if (oneChar == '-') {
		negative = true;
		ins >> oneChar;
	}
	else {
		negative = false;
	}

	ins >> dollars >> decimalPoint >> digit1 >> digit2;

	if (oneChar != '$' || decimalPoint != '.' || !isdigit(digit1) || !isdigit(digit2)) {
		cout << "Error illegal form for money input\n";
		exit(1);
	}

	cents = digitToInt(digit1) * 10 + digitToInt(digit2);

	amount.allCents = dollars * 100 + cents;
	if (negative) {
		amount.allCents = -amount.allCents;
	}

	return ins;
}

ostream& operator << (ostream& outs, const Money& amount) {
	long positiveCents, dollars, cents;
	positiveCents = labs(amount.allCents);
	dollars = positiveCents / 100;
	cents = positiveCents % 100;

	if (amount.allCents < 0) {
		outs << "-$" << dollars << '.';
	}
	else {
		outs << "$" << dollars << '.';
	}

	if (cents < 10) {
		outs << '0' << cents;
	}
	else {
		outs << cents;
	}

	return outs;
}

void Money::operator =(const Money& moneyRHS) {
	allCents = moneyRHS.getValue() * 100;
}


Check::Check(int newCheckNum, double newAmount, bool newCashed) {
	checkNum = newCheckNum;
	amount.setValue(newAmount);
	cashed = newCashed;
}

Check::Check() : checkNum(-1), amount(), cashed(false) {}

int Check::getCheckNum() const {
	return checkNum;
}

Money Check::getAmount() const {
	return amount;
}

bool Check::getCashed() const {
	return cashed;
}

void Check::setCheckNum(int newCheckNum) {
	checkNum = newCheckNum;
}

void Check::setAmount(double newAmount) {
	amount.setValue(newAmount);
}

void Check::setCashed(char YorN) {
	char newYorN;
	if ((YorN == 'y') || (YorN == 'Y')) {
		cashed = true;
	}
	else if ((YorN == 'n') || (YorN == 'N')) {
		cashed = false;
	}
	else {
		cout << "Illegal input. Please type in 'y' or 'Y' for yes, 'n' or 'N' for no." << endl;
		cin >> newYorN;
		setCashed(newYorN);
	}
}

void Check::input(istream& ins, ostream& outs) {
	outs << "Enter the check number: ";
	ins >> checkNum;

	double amountInDouble;
	outs << "Enter check amount as a decmial: ";
	ins >> amountInDouble;
	amount.setValue(amountInDouble);

	char cashedInChar;
	outs << "Was this check cashed (y/n)? ";
	ins >> cashedInChar;
	this->setCashed(cashedInChar);
}

void Check::output(ostream& outs) {
	outs << "Check #" << checkNum << ":\t\t" << amount;
	if (cashed) {
		outs << " (cashed)." << endl;
	}
	else {
		outs << " (not cashed)." << endl;
	}
}

bool operator >(const Check& checkNum1, const Check& checkNum2) {
	return (checkNum1.getCheckNum() > checkNum2.getCheckNum());
}

void Check::operator =(const Check& checkRHS) {
	checkNum = checkRHS.getCheckNum();
	cashed = checkRHS.getCashed();
	amount = checkRHS.getAmount();
}

vector<Check> makeChecksVec() {
	vector<Check> checksVec;
	Check check;
	int checkCounter, checkNum;
	double checkAmount;
	char checkedYN, finishYN;
	bool dontEnd, wrong;

	checkCounter = 1;
	dontEnd = true;
	while (dontEnd) {
		cout << "Check #" << checkCounter << endl;
		check.input(cin, cout);
		checksVec.push_back(check);
		cout << endl;

		wrong = true;
		while (wrong) {
			cout << "Would you like to add another check (y/n)? ";
			cin >> finishYN;

			if ((finishYN == 'y') || (finishYN == 'Y')) {
				dontEnd = true;
				checkCounter++;
				wrong = false;
			}
			else if ((finishYN == 'n') || (finishYN == 'N')) {
				dontEnd = false;
				wrong = false;
			}
			else {
				cout << "Illegal input. Please type in 'y' or 'Y' for yes, 'n' or 'N' for no." << endl;
			}
		}
		cout << endl;
	}
	return checksVec;
}

vector<double> makeDepositVec() {
	vector<double> depositVec;
	double deposit;
	bool dontEnd = true;

	while (dontEnd) {
		cin >> deposit;
		if (deposit != 0.00) {
			depositVec.push_back(deposit);
		}
		else {
			dontEnd = false;
		}
	}
	cout << endl;

	return depositVec;
}

void sortAscending(vector<Check>& checks) {
	for (int i = 0; i < checks.size(); i++) {
		for (int j = i; j < checks.size(); j++) {
			if (checks[i] > checks[j]) {
				Check temp = checks[i];
				checks[i] = checks[j];
				checks[j] = temp;
			}
		}
	}
}

Money sumChecks(vector<Check> checks) {
	Money sum;
	for (int i = 0; i < checks.size(); i++) {
		sum = sum + checks[i].getAmount();
	}
	return sum;
}

void outputChecks(vector<Check> checks) {
	if (checks.size() == 0) {
		cout << "NONE" << endl;
	}
	for (int i = 0; i < checks.size(); i++) {
		checks[i].output(cout);
	}
}

void outputResult(Money& oldBalance, Money& newBalance, Money& pendingBalance, Money& totalCashedAmount,
	Money& totalUncashedAmount, Money& depositSum, vector<Check> checks, vector<double> deposits) {
	vector<Check> cashedChecks;
	vector<Check> uncashedChecks;

	//sum the deposits
	double tempSum = 0;
	for (int i = 0; i < deposits.size(); i++) {
		tempSum += deposits[i];
	}
	depositSum.setValue(tempSum);

	//divide checks from cashed to uncashed
	for (int i = 0; i < checks.size(); i++) {
		if (checks[i].getCashed()) {
			cashedChecks.push_back(checks[i]);
		}
		else {
			uncashedChecks.push_back(checks[i]);
		}
	}
	sortAscending(cashedChecks);
	sortAscending(uncashedChecks);

	totalCashedAmount = sumChecks(cashedChecks);
	totalUncashedAmount = sumChecks(uncashedChecks);

	newBalance = oldBalance + depositSum - totalCashedAmount;

	pendingBalance = oldBalance - totalCashedAmount - totalUncashedAmount + depositSum;

	cout << "Old Balance:\t\t" << oldBalance << endl;
	cout << "New Balance:\t\t" << newBalance << endl;
	cout << "Pending Balance:\t" << pendingBalance << endl;
	cout << "Balance Difference:\t" << newBalance - pendingBalance << endl;
	cout << "Total Amount Cashed:\t" << totalCashedAmount << endl;
	cout << "Total Amount Deposited:\t" << depositSum << endl << endl;

	cout << "Cashed Checks:" << endl;
	outputChecks(cashedChecks);
	cout << endl;
	cout << "Uncashed Checks:" << endl;
	outputChecks(uncashedChecks);
}
