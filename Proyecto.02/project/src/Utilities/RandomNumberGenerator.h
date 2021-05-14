#pragma once

/*
 *
 */
class RandomNumberGenerator {
public:
	RandomNumberGenerator();
	virtual ~RandomNumberGenerator();
	virtual void init() = 0;
	virtual int nextInt() = 0;
	virtual int nextInt(int low, int high) = 0; // low is inclusive, high is exclusive
};

