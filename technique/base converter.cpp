std::string convertToBase(ll number, int base) {
	if (base < 2 || base > 36) {
		throw std::invalid_argument("Base must be in the range 2-36.");
	}

	if (number == 0) {
		return "0";
	}

	std::string result;
	bool isNegative = (number < 0);
	if (isNegative) {
		number = -number;
	}

	while (number > 0) {
		int remainder = number % base;
		if (remainder < 10) {
			result += '0' + remainder;
		} else {
			result += 'A' + (remainder - 10);
		}
		number /= base;
	}

	if (isNegative) {
		result += '-';
	}

    // Reverse the string since the remainders produce the number in reverse order
	std::reverse(result.begin(), result.end());

	return result;
}