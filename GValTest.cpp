#include <GVal.h>
#include <SmallVector.h>
#include <GValUtils.h>
#include <GValParser.h>
#include <MultiArrayIterator.h>
#include <MultiArraySlice.h>
#include <Usutf.h>
#include <GValFormatter.h>
#include <FileStream.h>
#include <BinaryStream.h>
#include <MemoryStream.h>
#include <GValSerializer.h>
#include <iostream>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <cstdio>

USUTF_TEST(testSmallVector)
{
	SmallVector<int, 2> v;
	Usutf::test(v.size() == 0);
	v.push_back(12);
	Usutf::test(v.size() == 1);
	Usutf::test(v[0] == 12);
	v.push_back(25);
	Usutf::test(v.size() == 2);
	Usutf::test(v[0] == 12);
	Usutf::test(v[1] == 25);
	v.push_back(77);
	Usutf::test(v.size() == 3);
	Usutf::test(v[0] == 12);
	Usutf::test(v[1] == 25);
	Usutf::test(v[2] == 77);
	v.push_back(373);
	Usutf::test(v.size() == 4);
	Usutf::test(v[0] == 12);
	Usutf::test(v[1] == 25);
	Usutf::test(v[2] == 77);
	Usutf::test(v[3] == 373);
}

USUTF_TEST(testGValUtils)
{
	Usutf::test(toString(GVal("abc")) == "abc");
	Usutf::test(toString(GVal(10)) == "10");
	Usutf::test(toString(GVal(2.5)) == "2.5");
	double ref = 1.234567890123456789;
	std::string s = toString(GVal(ref));
	double test = atof(s.c_str());
	double tol = 1.0e-14;
	Usutf::test(fabs(ref - test) < tol);
}

USUTF_TEST(testGVal)
{
	GVal v;
	v.setBool(true);
	Usutf::test(v.asBool(), "Test set/get true.");
	v.setBool(false);
	Usutf::test(!v.asBool(), "Test set/get false.");
	v.setInt(10);
	Usutf::test(v.asInt() == 10, "Test set/get int.");
	v.setMultiArray(3, GVal::GVT_INT);
	v.set(0, GVal(10));
	v.set(1, GVal(20));
	v.set(2, GVal(30));
	Usutf::test(v[0].asInt() == 10);
	Usutf::test(v[1].asInt() == 20);
	Usutf::test(v[2].asInt() == 30);
	v.setMap();
	v.set(std::string("pera"), GVal(23));
	Usutf::test(v[GVal("pera")].asInt() == 23);
}

USUTF_TEST(testGValCheck)
{
	GVal v;
	v.setMap();
	v.set("Pera", GVal(10));
	Usutf::test(v.check("Pera"));
	Usutf::test(!v.check("Mika"));
	Usutf::test(!v.check(GVal(4)));
}

USUTF_TEST(testGValParseString)
{
	std::string s = "'foo'";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v.asString() == "foo");
}

USUTF_TEST(testGValParseInt)
{
	std::string s = "1";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v.asInt() == 1);
	std::cout << v.asInt() << "\n";
}

USUTF_TEST(testGValParseNegativeInt)
{
	std::string s = "-7";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v.asInt() == -7);
	std::cout << v.asInt() << "\n";
}

USUTF_TEST(testGValParseDouble01)
{
	std::string s = "2.0";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v.asDouble() == 2.0);
	std::cout << v.asDouble() << "\n";
}

USUTF_TEST(testGValParseDouble02)
{
	std::string s = "2.0e10";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v.asDouble() == 2.0e10);
}

USUTF_TEST(testGValParserDouble03)
{
	std::string s = "132.67e-10";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v.asDouble() == 132.67e-10);
}

USUTF_TEST(testGValParserNegativeDouble)
{
	std::string s = "-0.5e-3";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v.asDouble() == -0.5e-3);
}

USUTF_TEST(testGValParserNegativeFloat)
{
	std::string s = "-2.25e-7f";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v.asFloat() == -2.25e-7f);
}

USUTF_TEST(testGValParseTrue)
{
	std::string s = "true";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v.asBool() == true);
}

USUTF_TEST(testGValParseFalse)
{
	std::string s = "false";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v.asBool() == false);
}

USUTF_TEST(testGValParseMap)
{
	std::string s =
		"{"
		"	'a' = 'foo';"
		"	'b' = 123;"
		"}";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v["a"].asString() == "foo");
	Usutf::test(v["b"].asInt() == 123);
}

USUTF_TEST(testGValParseList)
{
	std::string s = "[1.5, 'foo', 123]";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v[0].asDouble() == 1.5);
	Usutf::test(v[1].asString() == "foo");
	Usutf::test(v[2].asInt() == 123);
}

USUTF_TEST(testMultiArrayIterator01)
{
	MultiArrayIterator it;
	it.shape.push_back(2);
	it.shape.push_back(3);
	it.indices.push_back(0);
	it.indices.push_back(0);
	Usutf::test(it.atEnd() == false);
	Usutf::test(it.indices[0] == 0);
	Usutf::test(it.indices[1] == 0);
	it.next();
	Usutf::test(it.atEnd() == false);
	Usutf::test(it.indices[0] == 0);
	Usutf::test(it.indices[1] == 1);
	it.next();
	Usutf::test(it.atEnd() == false);
	Usutf::test(it.indices[0] == 0);
	Usutf::test(it.indices[1] == 2);
	it.next();
	Usutf::test(it.atEnd() == false);
	Usutf::test(it.indices[0] == 1);
	Usutf::test(it.indices[1] == 0);
	it.next();
	Usutf::test(it.atEnd() == false);
	Usutf::test(it.indices[0] == 1);
	Usutf::test(it.indices[1] == 1);
	it.next();
	Usutf::test(it.atEnd() == false);
	Usutf::test(it.indices[0] == 1);
	Usutf::test(it.indices[1] == 2);
	it.next();
	Usutf::test(it.atEnd() == true);
}

USUTF_TEST(testMultiArrayIterator02)
{
	SmallVector<size_t, 4> shape;
	shape.push_back(3);
	MultiArrayIterator it(shape);

	Usutf::test(it.atEnd() == false);
	Usutf::test(it.indices[0] == 0);
	it.next();
	Usutf::test(it.atEnd() == false);
	Usutf::test(it.indices[0] == 1);
	it.next();
	Usutf::test(it.atEnd() == false);
	Usutf::test(it.indices[0] == 2);
	it.next();
	Usutf::test(it.atEnd() == true);
}

USUTF_TEST(testGValParser03)
{
	std::string s = "MAI(3)[1, 4, 5]";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v.size() == 3);
	Usutf::test(v[0].asInt() == 1);
	Usutf::test(v[1].asInt() == 4);
	Usutf::test(v[2].asInt() == 5);
}

USUTF_TEST(testGValParser031)
{
	std::string s = "MAI(2,3)[[1, 4, 5],[14, 48, 51]]";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v.numberOfDimensions() == 2);
	Usutf::test(v.size(0) == 2);
	Usutf::test(v.size(1) == 3);
	Usutf::test(v(0, 0).asInt() == 1);
	Usutf::test(v(0, 1).asInt() == 4);
	Usutf::test(v(0, 2).asInt() == 5);
	Usutf::test(v(1, 0).asInt() == 14);
	Usutf::test(v(1, 1).asInt() == 48);
	Usutf::test(v(1, 2).asInt() == 51);
}

USUTF_TEST(testGValParser04)
{
	std::string s = "MAD(2, 2)[[1.0, 2.5], [5.25, -2.125]]";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v(0, 0).asDouble() == 1.0);
	Usutf::test(v(0, 1).asDouble() == 2.5);
	Usutf::test(v(1, 0).asDouble() == 5.25);
	Usutf::test(v(1, 1).asDouble() == -2.125);
}

USUTF_TEST(testGValParser05)
{
	std::string s = "MAF(2, 1)[[1.0f], [15.5f]]";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v(0, 0).asFloat() == 1.0f);
	Usutf::test(v(1, 0).asFloat() == 15.5f);
}

USUTF_TEST(testGValParser06)
{
	std::string s = "MAG(3)[1.5f, 2, 'pera']";
	GValParser parser;
	GVal v = parser.parseString(s);
	Usutf::test(v[0].asFloat() == 1.5f);
	Usutf::test(v[1].asInt() == 2);
	Usutf::test(v[2].asString() == "pera");
}

USUTF_TEST(testMultiArraySlice01)
{
	//int data[2 * 2 * 3] = {
	//1, 2, 9,
	//3, 4, 5,

	//2, 7, 6,
	//0, 8, 3 };

	MultiArraySlice mas;
	SmallVector<size_t, 4> shape;
	shape.push_back(2);
	shape.push_back(2);
	shape.push_back(3);

	mas.setWholeArray(shape);

	SmallVector<size_t, 4> indices;
	indices.resize(2);

	MultiArraySlice slice = mas.slice(0, 0);

	indices[0] = 0;
	indices[1] = 0;
	Usutf::test(slice.calculateOffset(indices) == 0);
	indices[1] = 1;
	Usutf::test(slice.calculateOffset(indices) == 1);
	indices[1] = 2;
	Usutf::test(slice.calculateOffset(indices) == 2);
	indices[0] = 1;
	indices[1] = 0;
	Usutf::test(slice.calculateOffset(indices) == 3);
	indices[1] = 1;
	Usutf::test(slice.calculateOffset(indices) == 4);
	indices[1] = 2;
	Usutf::test(slice.calculateOffset(indices) == 5);

	slice = mas.slice(0, 1);

	indices[0] = 0;
	indices[1] = 0;
	Usutf::test(slice.calculateOffset(indices) == 6);
	indices[1] = 1;
	Usutf::test(slice.calculateOffset(indices) == 7);
	indices[1] = 2;
	Usutf::test(slice.calculateOffset(indices) == 8);
	indices[0] = 1;
	indices[1] = 0;
	Usutf::test(slice.calculateOffset(indices) == 9);
	indices[1] = 1;
	Usutf::test(slice.calculateOffset(indices) == 10);
	indices[1] = 2;
	Usutf::test(slice.calculateOffset(indices) == 11);

	slice = mas.slice(1, 0);

	indices[0] = 0;
	indices[1] = 0;
	Usutf::test(slice.calculateOffset(indices) == 0);
	indices[1] = 1;
	Usutf::test(slice.calculateOffset(indices) == 1);
	indices[1] = 2;
	Usutf::test(slice.calculateOffset(indices) == 2);
	indices[0] = 1;
	indices[1] = 0;
	Usutf::test(slice.calculateOffset(indices) == 6);
	indices[1] = 1;
	Usutf::test(slice.calculateOffset(indices) == 7);
	indices[1] = 2;
	Usutf::test(slice.calculateOffset(indices) == 8);

	slice = mas.slice(1, 1);

	indices[0] = 0;
	indices[1] = 0;
	Usutf::test(slice.calculateOffset(indices) == 3);
	indices[1] = 1;
	Usutf::test(slice.calculateOffset(indices) == 4);
	indices[1] = 2;
	Usutf::test(slice.calculateOffset(indices) == 5);
	indices[0] = 1;
	indices[1] = 0;
	Usutf::test(slice.calculateOffset(indices) == 9);
	indices[1] = 1;
	Usutf::test(slice.calculateOffset(indices) == 10);
	indices[1] = 2;
	Usutf::test(slice.calculateOffset(indices) == 11);

	slice = mas.slice(2, 0);

	indices[0] = 0;
	indices[1] = 0;
	Usutf::test(slice.calculateOffset(indices) == 0);
	indices[1] = 1;
	Usutf::test(slice.calculateOffset(indices) == 3);
	indices[0] = 1;
	indices[1] = 0;
	Usutf::test(slice.calculateOffset(indices) == 6);
	indices[1] = 1;
	Usutf::test(slice.calculateOffset(indices) == 9);

	slice = mas.slice(2, 1);

	indices[0] = 0;
	indices[1] = 0;
	Usutf::test(slice.calculateOffset(indices) == 1);
	indices[1] = 1;
	Usutf::test(slice.calculateOffset(indices) == 4);
	indices[0] = 1;
	indices[1] = 0;
	Usutf::test(slice.calculateOffset(indices) == 7);
	indices[1] = 1;
	Usutf::test(slice.calculateOffset(indices) == 10);

	slice = mas.slice(2, 2);

	indices[0] = 0;
	indices[1] = 0;
	Usutf::test(slice.calculateOffset(indices) == 2);
	indices[1] = 1;
	Usutf::test(slice.calculateOffset(indices) == 5);
	indices[0] = 1;
	indices[1] = 0;
	Usutf::test(slice.calculateOffset(indices) == 8);
	indices[1] = 1;
	Usutf::test(slice.calculateOffset(indices) == 11);
}

USUTF_TEST(testGValFormatter01)
{
	GValFormatter gvf;
	Usutf::test(gvf.toStringSimple(GVal()) == "null");
	//std::cout << gvf.toStringSimple(GVal()) << "\n";
	Usutf::test(gvf.toStringSimple(GVal("pera")) == "'pera'");
	//std::cout << gvf.toStringSimple(GVal("pera")) << "\n";
	GVal ma;
	ma.setMultiArray(2, 2, GVal::GVT_INT);
	ma.set(0, 0, GVal(4));
	ma.set(0, 1, GVal(7));
	ma.set(1, 0, GVal(2));
	ma.set(1, 1, GVal(9));
	//std::cout << gvf.toStringSimple(ma) << "\n";
	std::string ref = "MAI(2, 2)[[4, 7], [2, 9]]";
	Usutf::test(gvf.toStringSimple(ma) == ref);
}

USUTF_TEST(testGValFormatter02)
{
	GValFormatter gvf;
	GVal ma;
	ma.setMultiArray(2, GVal::GVT_GENERIC);
	ma.set(0, 0, GVal(4));
	ma.set(0, 1, GVal("mika"));
	std::cout << gvf.toStringSimple(ma) << "\n";
	std::string ref = "[4, 'mika']";
	Usutf::test(gvf.toStringSimple(ma) == ref);
}

USUTF_TEST(testGValFormatter03)
{
	GValFormatter gvf;
	GVal m;
	m.setMap();
	m.set(GVal("pera"), GVal(34));
	m.set(GVal(4), GVal(0.5));
	std::cout << gvf.toStringSimple(m) << "\n";
	std::string ref = "{4 = 0.5; 'pera' = 34;}";
	Usutf::test(gvf.toStringSimple(m) == ref);
}

USUTF_TEST(testIntegrationOfGValFormatterAndGValParser)
{
	GValParser gvp;
	std::string ref = "{1 = 3; 'aca' = 123; 'laza' = [1, 3, 'open', 3.0f, 45.0];}";
	GVal v = gvp.parseString(ref);
	GValFormatter gvf;
	std::string test = gvf.toStringSimple(v);
	std::cout << test << "\n";
	Usutf::test(test == ref);
}

USUTF_TEST(testFileStream)
{
	std::string fileName = "test_xyz235355az";
	const int fileSize = 5;
	FileStream fs(fileName, FileStream::WRITE_MODE);
	char buffer1[fileSize] = { 45, 127, -128, 0, -1 };
	char buffer2[fileSize] = { 0, 0, 0, 0, 0 };
	fs.writeBytes(fileSize, buffer1);
	fs.close();
	fs.open(fileName, FileStream::READ_MODE);
	Usutf::test(fs.atEnd() == false);
	fs.readBytes(fileSize, buffer2);
	Usutf::test(fs.atEnd() == true);
	Usutf::test(fs.check() == true);
	fs.close();
	remove(fileName.c_str());
	for (int i = 0; i < fileSize; i++)
		Usutf::test(buffer1[i] == buffer2[i]);
}

USUTF_TEST(testBinaryStream)
{
	std::string fileName = "test_brfjrtyrt53546gfg";
	FileStream fs(fileName, FileStream::WRITE_MODE);
	BinaryStream bs(&fs);
	
	char cr = 17;
	int ir = 123456;
	long long lr = 1234567890LL;
	float fr = 4.5f;
	double dr = 17.25;
	std::string sr = "bar";
	bs.writeByte(cr);
	bs.writeInt(ir);
	bs.writeLong(lr);
	bs.writeFloat(fr);
	bs.writeDouble(dr);
	bs.writeString(sr);
	fs.close();
	fs.open(fileName, FileStream::READ_MODE);
	Usutf::test(fs.atEnd() == false);
	char ct = bs.readByte();
	int it = bs.readInt();
	long long lt = bs.readLong();
	float ft = bs.readFloat();
	double dt = bs.readDouble();
	std::string st = bs.readString();
	Usutf::test(fs.atEnd() == true);
	Usutf::test(fs.check() == true);
	fs.close();
	remove(fileName.c_str());
	Usutf::test(ct == cr);
	Usutf::test(it == ir);
	Usutf::test(lt == lr);
	Usutf::test(ft == fr);
	Usutf::test(dt == dr);
	Usutf::test(st == sr);
}

USUTF_TEST(testMemoryStream)
{
	MemoryStream ms;
	BinaryStream bs(&ms);

	char cr = -1;
	int ir = 123456;
	double dr = -44.75;
	bs.writeByte(cr);
	bs.writeInt(ir);
	bs.writeDouble(dr);

	Usutf::test(ms.atEnd() == false);
	char ct = bs.readByte();
	int it = bs.readInt();
	double dt = bs.readDouble();
	Usutf::test(ms.atEnd() == true);
	Usutf::test(ms.check() == true);
	Usutf::test(ct == cr);
	Usutf::test(it == ir);
	Usutf::test(dt == dr);
}

USUTF_TEST(testGValSerializer01)
{
	GValSerializer gvs;
	MemoryStream ms;
	BinaryStream bs(&ms);
	gvs.binaryStream = &bs;
	GVal r = GVal(4);
	gvs.write(r);
	GVal t = gvs.read();
	Usutf::test(r == t);
}

USUTF_TEST(testGValSerializer02)
{
	GValSerializer gvs;
	MemoryStream ms;
	BinaryStream bs(&ms);
	gvs.binaryStream = &bs;
	GVal r = GVal("Pera");
	gvs.write(r);
	GVal t = gvs.read();
	Usutf::test(r == t);
}

USUTF_TEST(testGValSerializer03)
{
	GValSerializer gvs;
	MemoryStream ms;
	BinaryStream bs(&ms);
	gvs.binaryStream = &bs;
	GVal r = gvParseString("MAI(2, 2)[[1, 4], [5, 75]]");
	gvs.write(r);
	GVal t = gvs.read();
	Usutf::test(r == t);
	Usutf::test(r(1, 1) == t(1, 1));
	Usutf::test(r(1, 1) == GVal(75));
	Usutf::test(r(1, 1) != GVal(74));
}

USUTF_TEST(testGValSerializer04)
{
	GValSerializer gvs;
	MemoryStream ms;
	BinaryStream bs(&ms);
	gvs.binaryStream = &bs;
	GVal r = gvParseString("{ 1 = 4; 'a' = 'pera'; 'c' = 45.0; }");
	gvs.write(r);
	GVal t = gvs.read();
	Usutf::test(r == t);
}

USUTF_TEST(testGValSerializer05)
{
	GValSerializer gvs;
	MemoryStream ms;
	BinaryStream bs(&ms);
	gvs.binaryStream = &bs;
	GVal r = gvParseString("{ 1 = 4; 'a' = 'pera'; 'c' = []; }");
	gvs.write(r);
	GVal t = gvs.read();
	Usutf::test(r == t);
}

USUTF_TEST(testGValCompareMultiArray)
{
	GVal a = gvParseString("MAI(2, 3)[[1, 4, 5], [5, 75, 9]]");
	GVal b = gvParseString("MAI(2, 3)[[1, 4, 5], [5, 75, 9]]");
	GVal c = gvParseString("MAI(2, 3)[[1, 4, 5], [5, 76, 9]]");
	Usutf::test(a == b);
	Usutf::test(!(a == c));
	Usutf::test(a != c);
	Usutf::test(a < c);
	Usutf::test(c > a);
	Usutf::test(!(b > a));
}

USUTF_TEST(testGValCompareMap01)
{
	GVal a = gvParseString("{ 1 = 4; 'a' = 'pera'; 'c' = 45.0; }");
	GVal b = gvParseString("{ 1 = 4; 'a' = 'pera'; 'c' = 45.0; }");
	GVal c = gvParseString("{ 1 = 4; 'a' = 'pera'; 'c' = 45.5; }");
	Usutf::test(!(a == c));
	Usutf::test(a == b);
	Usutf::test(a != c);
	Usutf::test(a < c);
	Usutf::test(c > a);
	Usutf::test(!(b > a));
}

USUTF_TEST(testGValCompareMap02)
{
	GVal a = gvParseString("{ [1, 4] = 4; 'a' = 'pera'; 'c' = 45.0; }");
	GVal b = gvParseString("{ [1, 4] = 4; 'a' = 'pera'; 'c' = 45.0; }");
	GVal c = gvParseString("{ [1, 5] = 4; 'a' = 'pera'; 'c' = 45.0; }");
	Usutf::test(!(a == c));
	Usutf::test(a == b);
	Usutf::test(a != c);
	Usutf::test(a < c);
	Usutf::test(c > a);
	Usutf::test(!(b > a));
}

USUTF_TEST(testGvArray)
{
	GVal x0(2);
	GVal x1("pera");

	GVal a = gvArray(x0, x1);

	Usutf::test(a.size() == 2);
	Usutf::test(a[0] == x0);
	Usutf::test(a[1] == x1);
}

USUTF_TEST(testGvReadFromBinaryFile)
{
	std::string fileName = "test.gval";
	GVal x("pera");
	gvWriteToBinaryFile(x, fileName);
	GVal t = gvReadFromBinaryFile(fileName);
	Usutf::test(t.getType() == GVal::GVT_STRING);
	Usutf::test(t.asString() == "pera");
}

int main(int argc, char *argv[])
{
	Usutf::runTests(argc, argv);
	//testBinaryStream();
	return 0;
}
