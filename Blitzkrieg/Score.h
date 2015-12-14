#pragma once

#include "Position.h"

struct Score
{
	int mg;
	int eg;

	Score();
	Score(int x);
	Score(int m, int e);

	Score operator+(Score const& s) const;
	Score operator-(Score const& s) const;
	Score operator*(Score const& s) const;
	Score operator/(Score const& s) const;

	Score operator+=(Score const& s);
	Score operator-=(Score const& s);
	Score operator*=(Score const& s);
	Score operator/=(Score const& s);

	Score operator+(int s) const;
	Score operator-(int s) const;
	Score operator*(int s) const;
	Score operator/(int s) const;

	Score operator+=(int s);
	Score operator-=(int s);
	Score operator*=(int s);
	Score operator/=(int s);

	Score operator+(float s) const;
	Score operator-(float s) const;
	Score operator*(float s) const;
	Score operator/(float s) const;

	Score operator+=(float s);
	Score operator-=(float s);
	Score operator*=(float s);
	Score operator/=(float s);

	/*Score operator+(uint64_t s) const;
	Score operator-(uint64_t s) const;
	Score operator*(uint64_t s) const;
	Score operator/(uint64_t s) const;

	Score operator+=(uint64_t s);
	Score operator-=(uint64_t s);
	Score operator*=(uint64_t s);
	Score operator/=(uint64_t s);*/

	operator int() const;
};
