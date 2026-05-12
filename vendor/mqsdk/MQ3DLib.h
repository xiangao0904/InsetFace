//---------------------------------------------------------------------------
//
//   MQ3DLib.h      Copyright(C) 1999-2023, tetraface Inc.
//
//		A collection of convenient functions.
//
//    　ちょっと便利な関数集。
//
//---------------------------------------------------------------------------

#ifndef MQ3DLIB_H
#define MQ3DLIB_H

#include <math.h>
#include <assert.h>
#include <vector>
#include <new>


// Ratio of the circumference of a circle to its diameter
// 円周率π
#ifndef PI
	#define PI 3.1415926536f
#endif

// Convert degree (from 0 to 360) to radian (from 0 and 2*PI)
// 弧度(0から360)からラジアン(0から2π)へ変換
#ifndef RAD
	#define RAD(_x) ((_x)/180.0f*PI)
#endif

// Convert radian (from 0 and 2*pi) to degree (from 0 to 360)
// ラジアン(0から2π)から弧度(0から360)へ変換
#ifndef DEG
	#define DEG(_x) ((_x)/PI*180.0f)
#endif

// The square of the magnitude of a vector 
// ベクトルのサイズの２乗
inline float GetNorm(const MQPoint& p)
{
	return p.x*p.x + p.y*p.y + p.z*p.z;
}

inline float GetNorm(const MQCoordinate& p)
{
	return p.u*p.u + p.v*p.v;
}

// The magnitude of a vector 
// ベクトルのサイズ
inline float GetSize(const MQPoint& p)
{
	return sqrtf(p.x*p.x + p.y*p.y + p.z*p.z);
}

inline float GetSize(const MQCoordinate& p)
{
	return sqrtf(p.u*p.u + p.v*p.v);
}

// Normalize a vector
// ベクトルの正規化
inline MQPoint Normalize(const MQPoint& p) 
{
	float s = GetSize(p);
	if(s == 0.0f)
		return MQPoint(0,0,0);
	return p / s;
}

// Get an inner product
// 内積の値を得る
inline float GetInnerProduct(const MQPoint& pa, const MQPoint& pb)
{
	return pa.x * pb.x + pa.y * pb.y + pa.z * pb.z; 
}

inline float GetInnerProduct(const MQCoordinate& pa, const MQCoordinate& pb)
{
	return pa.u * pb.u + pa.v * pb.v;
}

// Get a cross product
// 外積ベクトルを得る
inline MQPoint GetCrossProduct(const MQPoint& v1, const MQPoint& v2)
{
	return MQPoint(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

inline MQPoint GetExteriorProduct(const MQPoint& v1, const MQPoint& v2)
{
	return GetCrossProduct(v1, v2); 
}

// Get a normal vector for a face constituted by three points
// 3点からなる面の法線を得る
MQPoint GetNormal(const MQPoint& p0, const MQPoint& p1, const MQPoint& p2);

// Get a normal vector for a face constituted by four points
// 4点からなる面の法線を得る
MQPoint GetQuadNormal(const MQPoint& p0, const MQPoint& p1, const MQPoint& p2, const MQPoint& p3);

// Get a normal vector for a polygonal face
// 多角形面の法線を得る
MQPoint GetPolyNormal(const MQPoint *pts, int num);

// Get an area of a triangle constituted by three points
// 3点からなる三角形の面積を得る
float GetTriangleArea(const MQPoint& p1, const MQPoint& p2, const MQPoint& p3);
float GetTriangleArea(const MQCoordinate& p1, const MQCoordinate& p2, const MQCoordinate& p3);

// Get an angle which the two vectors intersect in radian (from 0 and PI)
// 2ベクトルの交差する角度をラジアン単位の0からπまでの値で得る
float GetCrossingAngle(const MQPoint& v1, const MQPoint& v2);
float GetCrossingAngle(const MQCoordinate& v1, const MQCoordinate& v2);

// Get a distance and a nearest point between a point and a 2D line segment.
// 点と2D(x/y)ライン(線分)との距離・最近点を得る。
float Get2DLineDistance(const MQPoint& p, const MQPoint& l1, const MQPoint& l2, MQPoint *outp, float *outt);

// Get a distance and a nearest point between a point and a 3D line segment.
// 点と3Dライン(線分)との距離・最近点を得る。
float Get3DLineDistance(const MQPoint& p, const MQPoint& l1, const MQPoint& l2, MQPoint *outp, float *outt);

// Get a rotation matrix around an arbitrary axis
// 任意方向の回転軸を用いた回転行列を得る
MQMatrix GetRotationMatrixWithAxis(const MQPoint& axis, float rad);

// Check whether a face exists in the opposite direction of the specified one.
// It returns an index of the face if it exists, or returns -1 if not exist.
// 反対向きの面が存在するかどうかを調べる
// 存在していればその面のインデックスを、なければ-1を返す
int SearchInvertedFace(MQObject obj, int faceindex, int start=-1, int end=-1);

// Check whether a direction of the face is front side in the scene
// 面の向きが表かどうか調べる
bool IsFrontFace(MQScene scene, MQObject obj, int face_index);

// Calculate a tangent vector from positions, normals and coordinates
// 位置・法線・UV座標から接線ベクトルを計算する
void CalculateTangent(const MQPoint& v0, const MQPoint& v1, const MQPoint& v2,
		const MQPoint& n0, const MQPoint& n1, const MQPoint& n2,
		const MQCoordinate& t0, const MQCoordinate& t1, const MQCoordinate& t2,
		MQPoint& tan0, MQPoint& tan1, MQPoint& tan2);

void CalculateTangent(const MQPoint& v0, const MQPoint& v1, const MQPoint& v2,
		const MQPoint& normal, 
		const MQCoordinate& t0, const MQCoordinate& t1, const MQCoordinate& t2,
		MQPoint& tangent);

// Calculate a tangent vector and a binormal vector from positions, normals and coordinates
// 位置・法線・UV座標から接線ベクトル・従法線ベクトルを計算する
void CalculateTangentAndBinormal(const MQPoint& v0, const MQPoint& v1, const MQPoint& v2,
		const MQPoint& n0, const MQPoint& n1, const MQPoint& n2,
		const MQCoordinate& t0, const MQCoordinate& t1, const MQCoordinate& t2,
		MQPoint& tan0, MQPoint& tan1, MQPoint& tan2, 
		MQPoint& bin0, MQPoint& bin1, MQPoint& bin2);


//---------------------------------------------------------------------------
//  MQApexValueBaseSetter class
//---------------------------------------------------------------------------
template<typename T> class MQApexValueBaseSetter {
public:
	MQApexValueBaseSetter();

	void resize(size_t size);
	void clear();
	size_t size() const { return pointers.size(); }

	T*& operator[](size_t index) { return pointers[index]; }
	const T* const& operator[](size_t index) const { return pointers[index]; }

private:
	std::vector<T*> pointers;
};

template<typename T> MQApexValueBaseSetter<T>::MQApexValueBaseSetter()
{
}

template<typename T> void MQApexValueBaseSetter<T>::resize(size_t size)
{
	pointers.resize(size);
}

template<typename T> void MQApexValueBaseSetter<T>::clear()
{
	pointers.clear();
}


//---------------------------------------------------------------------------
//  MQApexValueBase class
//---------------------------------------------------------------------------

template<typename T, typename S = MQApexValueBaseSetter<T>, int N = 4> class MQApexValueBase
{
public:
	MQApexValueBase();
	~MQApexValueBase();

	void setItemArrayNum(int num);
	int getItemArrayNum() const { return itemarray_num; }

	template<typename F> bool alloc(F *faces, size_t num);
	template<typename F> bool alloc(F *faces, size_t num, size_t capacity_size, T init_value = T());
	bool resize(size_t capacity_size, T init_value = T());
	size_t size() const { return pointers.size(); }
	void clear();

	bool isValid() const { return pointers.size() != 0; }
	bool resizeItem(int index, int vert_num);

	const T* operator[](int face) const { return pointers[face]; }
	T* operator[](int face) { return pointers[face]; }
	const T* at(int face) const { return pointers[face]; }
	T* at(int face) { return pointers[face]; }

protected:
	S pointers;
	std::vector<T> buffer;
	int itemarray_num;
};


template<typename T, typename S, int N> MQApexValueBase<T,S,N>::MQApexValueBase()
{
	itemarray_num = 1;
}

template<typename T, typename S, int N> MQApexValueBase<T,S,N>::~MQApexValueBase()
{
	clear();
}

template<typename T, typename S, int N> void MQApexValueBase<T,S,N>::setItemArrayNum(int num)
{
	assert(num > 0);
	assert(!isValid());

	itemarray_num = num;
}

template<typename T, typename S, int N> template<typename F> bool MQApexValueBase<T,S,N>::alloc(F *faces, size_t num)
{
	return alloc(faces, num, num);
}

template<typename T, typename S, int N> template<typename F> bool MQApexValueBase<T,S,N>::alloc(F *faces, size_t num, size_t capacity_size, T init_value)
{
	assert(num <= capacity_size);

	clear();

	try{
		buffer.resize(capacity_size*itemarray_num*N, init_value);
		pointers.resize(capacity_size);
	}catch(std::bad_alloc&){
		pointers.clear();
		buffer.clear();
		return false;
	}

	T *buf = !buffer.empty() ? &(*buffer.begin()) : NULL;
	
	for(int i=0; i<num; i++){
		if(faces[i].count > N){
#ifdef _WIN32
			T *p = new(std::nothrow) T[faces[i].count * itemarray_num];
#else
			T *p;
			try {
				p = new T[faces[i].count * itemarray_num];
			}catch(...){
				p = NULL;
			}
#endif
			if(p == NULL){
				for(int j=0; j<i; j++){
					if(pointers[j] != buf + j*itemarray_num*N){
						delete[] pointers[j];
					}
				}
				pointers.clear();
				buffer.clear();
				return false;
			}
			pointers[i] = p;
		}else{
			pointers[i] = buf + i*itemarray_num*N;
		}
	}
	for(size_t i=num; i<capacity_size; i++){
		pointers[i] = buf + i*itemarray_num*N;
	}
	return true;
}

template<typename T, typename S, int N> bool MQApexValueBase<T,S,N>::resize(size_t capacity_size, T init_value)
{
	size_t oldptcap = pointers.size();
	T *oldbuf = !buffer.empty() ? &(*buffer.begin()) : NULL;

	if(oldptcap > capacity_size){
		for(size_t i=capacity_size; i<oldptcap; i++){
			if(pointers[i] != oldbuf + i*itemarray_num*N){
				delete[] pointers[i];
				pointers[i] = oldbuf + i*itemarray_num*N;
			}
		}
	}

	try{
		buffer.resize(capacity_size*itemarray_num*N, init_value);
		pointers.resize(capacity_size);
	}catch(std::bad_alloc&){
		return false;
	}

	T *newbuf = !buffer.empty() ? &(*buffer.begin()) : NULL;

	if(oldbuf != newbuf){
		size_t num = (capacity_size < oldptcap) ? capacity_size : oldptcap;
		for(size_t i=0; i<num; i++){
			if(pointers[i] == oldbuf + i*itemarray_num*N){
				pointers[i] = newbuf + i*itemarray_num*N;
			}
		}
	}
	for(size_t i=oldptcap; i<capacity_size; i++){
		pointers[i] = newbuf + i*itemarray_num*N;
	}

	return true;
}

template<typename T, typename S, int N> void MQApexValueBase<T,S,N>::clear()
{
	T *buf = !buffer.empty() ? &(*buffer.begin()) : NULL;

	size_t faceNum = pointers.size();
	for(size_t i=0; i<faceNum; i++){
		if(pointers[i] != buf + i*itemarray_num*N){
			delete[] pointers[i];
		}
	}

	buffer.clear();
	pointers.clear();
}

template<typename T, typename S, int N> bool MQApexValueBase<T,S,N>::resizeItem(int index, int vert_num)
{
	assert(index < (int)pointers.size());

	T *buf = !buffer.empty() ? &(*buffer.begin()) : NULL;
	
	if(pointers[index] == buf + index*itemarray_num*N){
		if(vert_num > N){
			T *p = new(std::nothrow) T[vert_num * itemarray_num];
			if(p == NULL){
				return false;
			}
			pointers[index] = p;
		}
	}else{
		delete[] pointers[index];
		if(vert_num > N){
			T *p = new(std::nothrow) T[vert_num * itemarray_num];
			if(p == NULL){
				return false;
			}
			pointers[index] = p;
		}else{
			pointers[index] = buf + index*itemarray_num*N;
		}
	}
	return true;
}


// Class for calculating normal vectors in an object
// オブジェクト中の法線を計算するクラス
class MQObjNormal
{
protected:
	MQApexValueBase<MQPoint> normal;
public:
	MQObjNormal(MQObject obj);
	~MQObjNormal();

	MQPoint& Get(int face_index, int pt_index) {
		return normal[face_index][pt_index];
	}
};

// Class for calculating normal vectors with indices in an object
// オブジェクト中の法線を計算するクラス
class MQObjIndexedNormal
{
protected:
	std::vector<MQPoint> normal;
	MQApexValueBase<int> index;
public:
	MQObjIndexedNormal(MQObject obj);
	~MQObjIndexedNormal();

	int GetSize() const { return (int)normal.size(); }
	MQPoint GetNormal(int index) const { return normal[index]; }
	int& GetIndex(int face_index, int pt_index) {
		return index[face_index][pt_index];
	}
};



// A pair of an edge using in the MQObjEdge class
// MQObjEdgeクラス内で使用されるエッジ対情報
class MQObjEdgePair
{
public:
	int face;
	int line;

	MQObjEdgePair() { face = line = -1; }
	MQObjEdgePair(int f, int l) { face = f; line = l; }
	MQObjEdgePair& operator = (const MQObjEdgePair& r) 
		{ face=r.face; line=r.line; return *this; }
};


// Class for managing pairs of edges
// オブジェクトのエッジ対管理クラス
class MQObjEdge
{
private:
	int m_face;
	MQObject m_obj;
	MQApexValueBase<MQObjEdgePair> m_pair;
public:
	MQObjEdge(MQObject obj);
	~MQObjEdge();

	int getFaceCount() const { return m_face; }
	bool getPair(int face_index, int line_index, int& pair_face, int& pair_line);
	void setPair(int face_index, int line_index, int pair_face, int pair_line);
	void addFace(int vert_num);
};


#endif //MQ3DLIB_H
