#include "BarlekampClass.h"

/*
BarlekampMasseyClass::BarlekampMasseyClass(std::vector<int> cypheredSeq, unsigned base, unsigned degree = 1)
{

	this->base = base;
	this->degree = degree;
	if (cypheredSeq.size() > sequence.size())
		EasyOperational.extendPoly(sequence, cypheredSeq.size());
	for (unsigned i{}; i < cypheredSeq.size(); i++) {

		int temp = cypheredSeq[i];
		EasyOperational.numToField(temp, base);
		sequence[i] = static_cast<unsigned>(temp);

	}

}
*/ 

void BarlekampMasseyClass::easyFieldBM() {

	std::vector<unsigned> returnalPoly{ 1 };
	std::vector<unsigned> previousState{ 1 };
	std::vector<unsigned> tempForReturnal{ 1 };
	std::stack<std::vector<unsigned>> tempForStates{};
	unsigned length = 0; // ReturnalPoly size
	unsigned b = 1;
	unsigned x = 1;
	unsigned n = 0; // Steps quantity
	int d = 0; // Error
	int prevErr = 0; // Temporary for comparing errors
	// ANOTHER TEMPS
	int multiplierNegative{}; 
	unsigned multiplierPositive{}; 
	int sizeDifference{};
	int tempForBring{};

	while (n < sequence.size()) {

		prevErr = 0;
		for (unsigned i{ 1 }; i < length + 1; i++) {
		
			int tempNum = returnalPoly[returnalPoly.size() - i - 1] * sequence[n - i];
			prevErr += tempNum;
		
		}
		d = sequence[n] + (prevErr); // Checking an error
		EasyOperational->numToField(d, base);
		if (d == 0) {
			x++;
			n++;
			continue;
		}
		
		else if (d != 0) {

			// CALCULATING NEW RETURNAL 

			tempForStates.push(std::vector<unsigned>{previousState.begin(), previousState.end()});

			multiplierNegative = 0 - d;
			EasyOperational->polyToDegree(previousState, x); // Bringing poly to field
			multiplierNegative *= EasyOperational->reversedToField(b, base); // Finding reversed and inserting it
			EasyOperational->numToField(multiplierNegative, base);
			multiplierPositive = static_cast<unsigned>(multiplierNegative); 
			//Calculating needed operations for all situations

			if ((2 * length) <= n) {

				EasyOperational->extendPoly(tempForReturnal, returnalPoly.size() - tempForReturnal.size()); // Extending if needed
				std::copy(returnalPoly.begin(), returnalPoly.end(), tempForReturnal.begin()); // Copying to temp array

			}
			

			EasyOperational->multiplyPolyOnConst(previousState, base, multiplierPositive); // Renewing a returnals
			sizeDifference = previousState.size() - returnalPoly.size();
			if (sizeDifference > 0)
				EasyOperational->extendPoly(returnalPoly, sizeDifference);
			else
				EasyOperational->extendPoly(previousState, abs(sizeDifference));

			for (unsigned j{}; j < previousState.size(); j++) {
				
				tempForBring = previousState[j] + returnalPoly[j];
				EasyOperational->numToField(tempForBring, base);
				returnalPoly[j] = static_cast<unsigned>(tempForBring); // Rewriting returnalPolynom

			}
			previousState = tempForStates.top();
			//tempForStates.pop();

			if ((2 * length) <= n) {

				sizeDifference = previousState.size() - tempForReturnal.size();
				if (sizeDifference >= 0)
					EasyOperational->decreasePoly(previousState, previousState.size() - tempForReturnal.size());
				else
					EasyOperational->extendPoly(previousState, abs(sizeDifference));
				std::copy(tempForReturnal.begin(), tempForReturnal.end(), previousState.begin());
				length = n + 1 - length;
				b = d;
				x = 1;

			}
			else
				x++; // Increasing a gradecounter

			n++; // Increasing steps, coming to next iteration

		}
	

	}

	//returnalPoly.pop_back(); // Deleting unused num
	std::reverse(returnalPoly.begin(), returnalPoly.end()); // Reversing to display in LFSR (x^0 + x^1 + x^2....+ x^n)
	for (auto n : returnalPoly)
		std::cout << n << "\t";
	std::cout << std::endl;
	std::cout << length << std::endl;

}


