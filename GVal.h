#ifndef GVAL_H
#define GVAL_H

#include <cstdint>
#include <memory>
#include <map>
#include <SmallVector.h>
#include <ProgressReporter.h>
#include <toString.h>

class GVal
{
public:
	enum GValType {
		GVT_NULL, GVT_BOOL, GVT_UCHAR, GVT_INT, GVT_LONG, GVT_FLOAT, GVT_DOUBLE,
		GVT_STRING, GVT_MULTI_ARRAY, GVT_MAP, GVT_GENERIC
	};

	GVal() : type(GVT_NULL) { }
	explicit GVal(bool x) : type(GVT_BOOL) { boolValue = x; }
	explicit GVal(unsigned char x) : type(GVT_UCHAR) { ucharValue = x; }
	explicit GVal(int x) : type(GVT_INT) { intValue = x; }
	explicit GVal(long long x) : type(GVT_LONG) { longValue = x; }
	explicit GVal(float x) : type(GVT_FLOAT) { floatValue = x; }
	explicit GVal(double x) : type(GVT_DOUBLE) { doubleValue = x; }
	explicit GVal(const std::string &x) : type(GVT_STRING) { stringValue = x; }
	explicit GVal(const char *x) : type(GVT_STRING) { stringValue = std::string(x); }
	GVal(const GVal &x) {
		copyContentFrom(x);
	}
	~GVal() {
		reset();
	}

	GVal &operator = (const GVal &x);
	bool operator < (const GVal &x) const;
	bool operator > (const GVal &x) const;
	bool operator == (const GVal &x) const;
	bool operator != (const GVal &x) const;

	int compareMultiArray(const GVal &x) const;
	int compareMap(const GVal &x) const;

	int getType() const { return type; }
	void setType(int x) { type = x; }

	GVal operator[] (size_t i) const { return get(i); }
	//GVal operator[] (const std::string &key) const { return get(key); }
	GVal operator[] (const GVal &key) const { return get(key); }
	GVal operator[] (const std::string &key) const { return get(GVal(key)); }
	GVal operator() (size_t i0, size_t i1) const { return get(i0, i1); }
	GVal operator() (size_t i0, size_t i1, size_t i2) const { return get(i0, i1, i2); }
	GVal operator() (size_t i0, size_t i1, size_t i2, size_t i3) const { return get(i0, i1, i2, i3); }

	GVal get(size_t i0) const;
	GVal get(size_t i0, size_t i1) const;
	GVal get(size_t i0, size_t i1, size_t i2) const;
	GVal get(size_t i0, size_t i1, size_t i2, size_t i3) const;
	void set(size_t i0, const GVal &x);
	void set(size_t i0, size_t i1, const GVal &x);
	void set(size_t i0, size_t i1, size_t i2, const GVal &x);
	void set(size_t i0, size_t i1, size_t i2, size_t i3, const GVal &x);
	GVal get(const SmallVector<size_t, 4> &i) const;
	//GVal get(size_t *i, int dim) const;
	GVal get(const std::string &key) const;
	GVal get(const char *key) const;
	GVal get(const GVal &key) const;
	void set(const SmallVector<size_t, 4> &i, const GVal &x);
	//void set(size_t *i, int dim, const GVal &x);
	void set(const std::string &key, const GVal &x);
	void set(const GVal &key, const GVal &x);
	GVal getLinear(size_t i) const;
	void setLinear(size_t i, const GVal &x);

	void copyContentFrom(const GVal &x);
	void reset();
	size_t size() const;
	size_t size(unsigned dim) const { return shape()[dim]; }
	const SmallVector<size_t, 4> &shape() const;
	size_t numberOfDimensions() const { return shape().size(); }
	void resize(size_t i0);
	void resize(size_t i0, size_t i1);
	void resize(size_t i0, size_t i1, size_t i2);
	void resize(size_t i0, size_t i1, size_t i2, size_t i3);
	void resize(const SmallVector<size_t, 4> &x);
	void resize(size_t *i, int dim);

	void reshape(size_t i0);
	void reshape(size_t i0, size_t i1);
	void reshape(size_t i0, size_t i1, size_t i2);
	void reshape(size_t i0, size_t i1, size_t i2, size_t i3);
	void reshape(const SmallVector<size_t, 4> &x);
	void reshape(size_t *i, int dim);

	GVal front() const;
	GVal back() const;

	void pushBack(const GVal &x);
	GVal popBack();

	GVal keys() const;
	bool check(const std::string &key) const;
	bool check(const GVal &key) const;

	void setNull() {
		reset();
		type = GVT_NULL;
	}
	void setBool(bool x) {
		reset();
		type = GVT_BOOL;
		boolValue = x;
	}
	void setUChar(unsigned char x) {
		reset();
		type = GVT_UCHAR;
		ucharValue = x;
	}
	void setInt(int x) {
		reset();
		type = GVT_INT;
		intValue = x;
	}
	void setLong(long long x) {
		reset();
		type = GVT_LONG;
		longValue = x;
	}
	void setFloat(float x) {
		reset();
		type = GVT_FLOAT;
		floatValue = x;
	}
	void setDouble(double x) {
		reset();
		type = GVT_DOUBLE;
		doubleValue = x;
	}
	void setString(const std::string &x) {
		reset();
		type = GVT_STRING;
		stringValue = x;
	}
	void setMultiArray();
	void setMultiArray(size_t i, int entryType);
	void setMultiArray(size_t i0, size_t i1, int entryType);
	void setMultiArray(size_t i0, size_t i1, size_t i2, int entryType);
	void setMultiArray(size_t i0, size_t i1, size_t i2, size_t i3, int entryType);
	void setMultiArray(const SmallVector<size_t, 4> &x, int entryType);
	void setMultiArray(size_t *i, size_t dim, int entryType);
	void setMultiArrayFromData(const SmallVector<size_t, 4> &shape, int entryType,
		void *data, bool borrowData = false);
	void setMap();
	void setMap(int keyType_, int valueType_);

	bool isNull() const {
		return type == GVT_NULL;
	}
	bool asBool() const {
		if (type != GVT_BOOL)
			error("Bool type expected.");
		return boolValue;
	}
	unsigned char asUChar() const {
		if (type != GVT_UCHAR)
			error("UChar type expected but found type " + typeToString(type) + ".");
		return static_cast<unsigned char>(intValue);
	}
	int asInt() const {
		if (type != GVT_INT)
			error("Int type expected but found type " + typeToString(type) + ".");
		return intValue;
	}
	long long asLong() const {
		if (type != GVT_LONG)
			error("Long type expected.");
		return longValue;
	}
	float asFloat() const {
		if (type != GVT_FLOAT)
			error("Float type expected.");
		return floatValue;
	}
	double asDouble() const {
		if (type != GVT_DOUBLE)
			error("Double type expected.");
		return doubleValue;
	}
	const std::string &asString() const {
		if (type != GVT_STRING)
			error("String type expected.");
		return stringValue;
	}

	void error(const std::string &msg) const;
	static std::string typeToString(int type_);

	std::shared_ptr<void> &getGenericValue() { return genericValue; }
	const std::shared_ptr<void> &getGenericValue() const { return genericValue; }

	GVal keys();
	void *getData() const;
protected:
	int type;
	union
	{
		bool boolValue;
		unsigned char ucharValue;
		int intValue;
		long long longValue;
		float floatValue;
		double doubleValue;
	};
	std::shared_ptr<void> genericValue;
	std::string stringValue;
	ProgressReporter progressReporter;
};

class GValMultiArray
{
public:
	GValMultiArray();
	~GValMultiArray();

	void reset();

	size_t size() const;
	GVal get(size_t *i, int dim) const;
	void set(size_t *i, int dim, const GVal &x);
	GVal getLinear(size_t i) const;
	void setLinear(size_t i, const GVal &x);

	GVal front() const;
	GVal back() const;

	void pushBack(const GVal &x);
	GVal popBack();

	int getEntryType() const { return entryType; }
	void resizeAndSetEntryType(size_t *i, size_t dim, int entryType_);
	void fromBorrowedData(const SmallVector<size_t, 4> &shape_, int entryType_, void *data_);
	const SmallVector<size_t, 4> &getShape() { return shape; }
	void *getData() const { return data; }
	size_t getEntrySize(int type) const;
protected:
	int entryType;
	SmallVector<size_t, 4> shape;
	size_t capacity;
	void *data;
	bool borrowedData;

	size_t calculateOffset(size_t *i, int dim) const;
	void createObjects(GVal *objs, size_t count);
	void destroyObjects(GVal *objs, size_t count);
	void copyObjects(GVal *dst, GVal *src, size_t count);
};

class GValMap
{
public:
	size_t size() { return data.size(); }

	GVal get(const GVal &key) const;
	void set(const GVal &key, const GVal &value);
	GVal keys() const;
	bool check(const GVal &key);
protected:
	int keyType;
	int valueType;
	std::map<GVal, GVal> data;
};

#endif
