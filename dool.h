#ifndef DOOL_H_
#define DOOL_H_

struct dool
{
	bool x;
	bool y;

	dool();
	dool(bool);
	dool(bool, bool);

	bool _and();
	bool _or();
};

bool operator||(bool b, dool d)
{
	return b || d._or();
}

bool operator||(dool d, bool b)
{
	return b || d;
}

bool operator&&(bool b, dool d)
{
	return b && d._and();
}

bool operator&&(dool d, bool b)
{
	return b && d;
}

#endif // DOOL_H_
