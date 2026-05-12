//---------------------------------------------------------------------------
//
//   MQ3DLib.cpp      Copyright(C) 1999-2023, tetraface Inc.
//
//		A collection of convenient functions.
//
//    　ちょっと便利な関数集。
//
//---------------------------------------------------------------------------

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <float.h>
#include <vector>
#include <cmath>
#include "MQPlugin.h"
#include "MQ3DLib.h"


//---------------------------------------------------------------------------
//  GetNormal()
//     Get a normal vector for a face constituted by three points.
//     3点からなる面の法線を得る
//---------------------------------------------------------------------------
MQPoint GetNormal(const MQPoint& p0, const MQPoint& p1, const MQPoint& p2)
{
	MQPoint ep = GetCrossProduct(p1-p2, p0-p1);

	if(ep == MQPoint(0,0,0))
		return MQPoint(0,0,0);

	return ep / GetSize(ep);
}

//---------------------------------------------------------------------------
//  GetQuadNormal()
//     Get a normal vector for a face constituted by four points.
//     4点からなる面の法線を得る
//---------------------------------------------------------------------------
MQPoint GetQuadNormal(const MQPoint& p0, const MQPoint& p1, const MQPoint& p2, const MQPoint& p3)
{
	MQPoint n,n1a,n1b,n2a,n2b;

	n1a = GetNormal(p0, p1, p2);
	n1b = GetNormal(p0, p2, p3);
	n2a = GetNormal(p1, p2, p3);
	n2b = GetNormal(p1, p3, p0);

	// 凹型や歪んだ四角形の場合は片方の内積が小さくなるので、
	// ２法線の内積の値を比較して、大きい方を選ぶ
	if(GetInnerProduct(n1a,n1b) > GetInnerProduct(n2a,n2b)) {
		n = Normalize(n1a + n1b);
	} else {
		n = Normalize(n2a + n2b);
	}

	return n;
}

//---------------------------------------------------------------------------
//  GetPolyNormal
//     Get a normal vector for a polygonal face.
//     多角形面の法線を得る
//---------------------------------------------------------------------------
MQPoint GetPolyNormal(const MQPoint *pts, int num)
{
	if(num < 3){
		return MQPoint(0,0,0);
	}

	// 多角形をなすバウンディングボックスから最も長い軸を得る
	MQPoint boxmin(FLT_MAX, FLT_MAX, FLT_MAX);
	MQPoint boxmax(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	for(int i=0; i<num; i++){
		if(boxmin.x > pts[i].x) boxmin.x = pts[i].x;
		if(boxmin.y > pts[i].y) boxmin.y = pts[i].y;
		if(boxmin.z > pts[i].z) boxmin.z = pts[i].z;
		if(boxmax.x < pts[i].x) boxmax.x = pts[i].x;
		if(boxmax.y < pts[i].y) boxmax.y = pts[i].y;
		if(boxmax.z < pts[i].z) boxmax.z = pts[i].z;
	}
	int ax1, ax2;
	MQPoint size(boxmax.x-boxmin.x, boxmax.y-boxmin.y, boxmax.z-boxmin.z);
	if(size.x >= size.y){
		if(size.x >= size.z){
			ax1 = 0;
			ax2 = (size.y >= size.z) ? 1 : 2;
		}else{
			ax1 = 2;
			ax2 = 0;
		}
	}else{
		if(size.y >= size.z){
			ax1 = 1;
			ax2 = (size.x >= size.z) ? 0 : 2;
		}else{
			ax1 = 2;
			ax2 = 1;
		}
	}

	// 最も端にある頂点を探す（その頂点は必ず凸となる）
	int minid = -1;
	for(int i=0; i<num; i++){
		float p1 = pts[i].index(ax1);
		if(p1 == boxmin.index(ax1)){
			if(minid == -1){
				minid = i;
			}else if(pts[i].index(ax2) < pts[minid].index(ax2)){
				minid = i;
			}
		}
	}

	// 本当に凸となるか、重心からのベクトルに対する内積をチェック
	MQPoint g(0,0,0);
	for(int i=0; i<num; i++){
		g += pts[i];
	}
	g /= (float)num;
	MQPoint gv = Normalize(pts[minid] - g);
	float maxip = GetInnerProduct(pts[minid] - g, gv);
	for(int i=0; i<num; i++){
		if(i != minid){
			float ip = GetInnerProduct(pts[i] - g, gv);
			if(maxip < ip){
				minid = i; // より遠いものが見つかったので、こちらを採用
				maxip = ip;
			}
		}
	}

	// 凸頂点の法線方向を基準に、各頂点とその近傍頂点との三角形の法線の平均を最終法線とする
	MQPoint base_n = GetNormal(
		pts[(minid-1+num)%num], 
		pts[minid], 
		pts[(minid+1)%num]);
	MQPoint nv(0,0,0);
	for(int i=0; i<num; i++){
		const MQPoint& v1 = pts[(minid+i)%num];
		const MQPoint& v2 = pts[(minid+i+1)%num];
		MQPoint p = GetNormal(g, v1, v2);
		if(GetInnerProduct(base_n, p) >= 0){
			nv += p * GetTriangleArea(g, v1, v2);
		}else{
			nv -= p * GetTriangleArea(g, v1, v2);
		}
	}
	return Normalize(nv);
}

//---------------------------------------------------------------------------
//  GetTriangleArea()
//     Get an area of a triangle constituted by three points
//     3点からなる三角形の面積を得る
//---------------------------------------------------------------------------
float GetTriangleArea(const MQPoint& p1, const MQPoint& p2, const MQPoint& p3)
{	
	MQPoint v1,v2,v3;
	v1 = p2 - p1;
	v2 = p3 - p1;
	v3 = GetCrossProduct(v1, v2);
	return 0.5f * v3.abs();
}

float GetTriangleArea(const MQCoordinate& p1, const MQCoordinate& p2, const MQCoordinate& p3)
{
	MQCoordinate v1,v2;
	float d1,d2,u,t,eps = 0.00001f;

	v1=p2-p1; d1=GetSize(v1);
	v2=p3-p1; d2=GetSize(v2);
	if(d1*d2 == 0) return 0;
	u = GetInnerProduct(v1,v2);
	t = fabs(u/(d1*d2));
	if(1-eps < t && t < 1+eps) return 0;
	return 0.5f * sqrtf(d1*d1 * d2*d2 - u*u);
}

//---------------------------------------------------------------------------
//  GetCrossingAngle()
//     Get an angle which the two vectors intersect in radian (from 0 and PI).
//     2ベクトルの交差する角度をラジアン単位の0からπまでの値で得る
//---------------------------------------------------------------------------
float GetCrossingAngle(const MQPoint& v1, const MQPoint& v2)
{
	float d,c;

	d = GetSize(v1) * GetSize(v2);
	if(d == 0.0f)
		return 0.0f;

	c = GetInnerProduct(v1, v2) / d;
	if(c >= 1.0f) return 0.0f;
	if(c <=-1.0f) return PI;

	return acosf(c);
}

float GetCrossingAngle(const MQCoordinate& v1, const MQCoordinate& v2)
{
	float d,c;

	d = GetSize(v1) * GetSize(v2);
	if(d == 0.0f)
		return 0.0f;

	c = GetInnerProduct(v1, v2) / d;
	if(c >= 1.0f) return 0.0f;
	if(c <=-1.0f) return PI;

	return acosf(c);
}

//---------------------------------------------------------------------------
//  Get2DLineDistance()
//     Get a distance and a nearest point between a point and a 3D line.
//     点と2D(x/y)ライン(線分)との距離・最近点を得る。
//---------------------------------------------------------------------------
float Get2DLineDistance(const MQPoint& p, const MQPoint& l1, const MQPoint& l2, MQPoint *outp, float *outt)
{
	float t, d1,d2;
	MQPoint d,h;

	d.x = l2.x - l1.x;
	d.y = l2.y - l1.y;
	d2 = d.x*d.x + d.y*d.y;
	if(d2 > 0)
	{
		d1 = (p.x-l1.x)*d.x + (p.y-l1.y)*d.y;
		t = d1/d2;
		if( 0<t && t<1 ) {
			h.x = d.x * t + l1.x;
			h.y = d.y * t + l1.y;
			h.z = 0;
			if(outt != nullptr) *outt = t;
		} else if( t<=0 ) {
			h=l1;
			if(outt != nullptr) *outt = 0;
		} else {
			h=l2;
			if(outt != nullptr) *outt = 1;
		}
	} else {
		h = l1;
		if(outt != nullptr) *outt = 0;
	}
	if(outp != nullptr) *outp = h;
	d = h - p;
	return sqrt(d.x*d.x + d.y*d.y);
}

//---------------------------------------------------------------------------
//  Get3DLineDistance()
//     Get a distance and a nearest point between a point and a 3D line.
//     点と3Dライン(線分)との距離・最近点を得る。
//---------------------------------------------------------------------------
float Get3DLineDistance(const MQPoint& p, const MQPoint& l1, const MQPoint& l2, MQPoint *outp, float *outt)
{
	float t, d1,d2;
	MQPoint d,h;

	d.x = l2.x - l1.x;
	d.y = l2.y - l1.y;
	d.z = l2.z - l1.z;
	d2 = d.x*d.x + d.y*d.y + d.z*d.z;
	if(d2 > 0)
	{
		d1 = (p.x-l1.x)*d.x + (p.y-l1.y)*d.y + (p.z-l1.z)*d.z;
		t = d1/d2;
		if( 0<t && t<1 ) {
			h.x = d.x * t + l1.x;
			h.y = d.y * t + l1.y;
			h.z = d.z * t + l1.z;
			if(outt != nullptr) *outt = t;
		} else if( t<=0 ) {
			h=l1;
			if(outt != nullptr) *outt = 0;
		} else {
			h=l2;
			if(outt != nullptr) *outt = 1;
		}
	} else {
		h = l1;
		if(outt != nullptr) *outt = 0;
	}
	if(outp != nullptr) *outp = h;
	d = h - p;
	return d.abs();
}


//---------------------------------------------------------------------------
//  GetRotationMatrixWithAxis()
//     Get a rotation matrix around an arbitrary axis.
//     任意方向の回転軸を用いた回転行列を得る。
//---------------------------------------------------------------------------
MQMatrix GetRotationMatrixWithAxis(const MQPoint& axis, float rad)
{
	MQMatrix mat;

	// Normalize vector of axis
	float a = axis.abs();
	if(a == 0.0f){
		mat.Identify();
		return mat;
	}

	float inv_mod = 1.0f / a;
	float nx = axis.x * inv_mod;
	float ny = axis.y * inv_mod;
	float nz = axis.z * inv_mod;

	float ct = cos(rad);
	float st = sin(rad);

	mat._11 = nx*nx + (1-nx*nx)*ct;
	mat._12 = nx*ny*(1-ct) + nz*st;
	mat._13 = nx*nz*(1-ct) - ny*st;
	mat._21 = nx*ny*(1-ct) - nz*st;
	mat._22 = ny*ny + (1-ny*ny)*ct;
	mat._23 = ny*nz*(1-ct) + nx*st;
	mat._31 = nx*nz*(1-ct) + ny*st;
	mat._32 = ny*nz*(1-ct) - nx*st;
	mat._33 = nz*nz + (1-nz*nz)*ct;
	mat._14 = mat._24 = mat._34 = 0.0f;
	mat._41 = mat._42 = mat._43 = 0.0f;
	mat._44 = 1.0f;

	return mat;
}

//---------------------------------------------------------------------------
//  SearchInvertedFace()
//     Check whether a face exists in the opposite direction of the specified one.
//     It returns an index of the face if it exists, or returns -1 if not exist.
//     反対向きの面が存在するかどうかを調べる
//     存在していればその面のインデックスを、なければ-1を返す
//---------------------------------------------------------------------------
int SearchInvertedFace(MQObject obj, int faceindex, int start, int end)
{
	int i,j,k;
	std::vector<int> cvidx, dvidx;

	int face_count = obj->GetFaceCount();
	if(faceindex >= face_count)
		return -1;

	int pt_count = obj->GetFacePointCount(faceindex);
	if(pt_count == 0)
		return -1;

	cvidx.resize(pt_count);
	dvidx.resize(pt_count);

	obj->GetFacePointArray(faceindex, &(*dvidx.begin()));

	if(start < 0) start = 0;
	if(end   < 0) end   = face_count-1;

	for(i=start; i<=end; i++)
	{
		if(pt_count != obj->GetFacePointCount(i))
			continue;
		
		obj->GetFacePointArray(i, &(*cvidx.begin()));

		for(j=0; j<pt_count; j++) {
			if(cvidx[j] != dvidx[0]) continue;
			for(k=1; k<pt_count; k++) {
				if(cvidx[(j+k)%pt_count] != dvidx[pt_count-k])
					break;
			}
			if(k == pt_count)
				return i;
		}
	}

	return -1;
}


//---------------------------------------------------------------------------
//  IsFrontFace()
//     Check whether a direction of the face is front side in the scene.
//     面の向きが表かどうか調べる
//---------------------------------------------------------------------------
bool IsFrontFace(MQScene scene, MQObject obj, int face_index)
{
	int num = obj->GetFacePointCount(face_index);
	std::vector<int> vert_index(num);
	obj->GetFacePointArray(face_index, &(*vert_index.begin()));

	std::vector<MQPoint> sp(num);
	for (int i=0; i<num; i++){
		sp[i] = scene->Convert3DToScreen(obj->GetVertex(vert_index[i]));

		// 視野より手前にあれば表とみなさない
		if (sp[i].z <= 0) return false;
	}

	// 法線の向きで調べる
	if(num >= 3){
		if((sp[1].x-sp[0].x) * (sp[2].y-sp[1].y) - (sp[1].y-sp[0].y) * (sp[2].x-sp[1].x) >= 0) {
			return true;
		}else if(num >= 4){
			if((sp[2].x-sp[0].x) * (sp[3].y-sp[2].y) - (sp[2].y-sp[0].y) * (sp[3].x-sp[2].x) >= 0) {
				return true;
			}
		}
	}
	else if (num > 0){
		return true;
	}

	return false;
}



//---------------------------------------------------------------------------
//  CalculateTangent()
//     Calculate a tangent vector from positions, normals and coordinates.
//     位置・法線・UV座標から接線ベクトルを計算する
//---------------------------------------------------------------------------
void CalculateTangent(const MQPoint& v0, const MQPoint& v1, const MQPoint& v2,
		const MQPoint& n0, const MQPoint& n1, const MQPoint& n2,
		const MQCoordinate& t0, const MQCoordinate& t1, const MQCoordinate& t2,
		MQPoint& tan0, MQPoint& tan1, MQPoint& tan2)
{
	MQPoint edge1, edge2, crossP;

	edge1.x = v1.x - v0.x;
	edge1.y = t1.u - t0.u; // s-vector - don't need to compute this multiple times
	edge1.z = t1.v - t0.v; // t-vector
	edge2.x = v2.x - v0.x;
	edge2.y = t2.u - t0.u; // another s-vector
	edge2.z = t2.v - t0.v; // another t-vector
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	float tanX = -crossP.y / crossP.x;
	tan0.x = tanX;
	tan1.x = tanX;
	tan2.x = tanX;

	// y, s, t
	edge1.x = v1.y - v0.y;
	edge2.x = v2.y - v0.y;
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	float tanY = -crossP.y / crossP.x;
	tan0.y = tanY;
	tan1.y = tanY;
	tan2.y = tanY;

	// z, s, t
	edge1.x = v1.z - v0.z;
	edge2.x = v2.z - v0.z;
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	float tanZ = -crossP.y / crossP.x;
	tan0.z = tanZ;
	tan1.z = tanZ;
	tan2.z = tanZ;

	// Orthonormalize to normal
	tan0 -= n0 * GetInnerProduct(tan0, n0);
	tan1 -= n1 * GetInnerProduct(tan1, n1);
	tan2 -= n2 * GetInnerProduct(tan2, n2);

	// Normalize tangents
	tan0 = Normalize(tan0);
	tan1 = Normalize(tan1);
	tan2 = Normalize(tan2);
}

void CalculateTangent(const MQPoint& v0, const MQPoint& v1, const MQPoint& v2,
		const MQPoint& normal,
		const MQCoordinate& t0, const MQCoordinate& t1, const MQCoordinate& t2,
		MQPoint& tangent)
{
	MQPoint edge1, edge2, crossP;

	edge1.x = v1.x - v0.x;
	edge1.y = t1.u - t0.u; // s-vector - don't need to compute this multiple times
	edge1.z = t1.v - t0.v; // t-vector
	edge2.x = v2.x - v0.x;
	edge2.y = t2.u - t0.u; // another s-vector
	edge2.z = t2.v - t0.v; // another t-vector
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	float tanX = -crossP.y / crossP.x;
	tangent.x = tanX;

	// y, s, t
	edge1.x = v1.y - v0.y;
	edge2.x = v2.y - v0.y;
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	float tanY = -crossP.y / crossP.x;
	tangent.y = tanY;

	// z, s, t
	edge1.x = v1.z - v0.z;
	edge2.x = v2.z - v0.z;
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	float tanZ = -crossP.y / crossP.x;
	tangent.z = tanZ;

	// Orthonormalize to normal
	tangent -= normal * GetInnerProduct(tangent, normal);

	// Normalize tangents
	tangent = Normalize(tangent);
}


void CalculateTangentAndBinormal(const MQPoint& v0, const MQPoint& v1, const MQPoint& v2,
		const MQPoint& n0, const MQPoint& n1, const MQPoint& n2,
		const MQCoordinate& t0, const MQCoordinate& t1, const MQCoordinate& t2,
		MQPoint& tan0, MQPoint& tan1, MQPoint& tan2, 
		MQPoint& bin0, MQPoint& bin1, MQPoint& bin2)
{
	MQPoint edge1, edge2, crossP;

	edge1.x = v1.x - v0.x;
	edge1.y = t1.u - t0.u; // s-vector - don't need to compute this multiple times
	edge1.z = t1.v - t0.v; // t-vector
	edge2.x = v2.x - v0.x;
	edge2.y = t2.u - t0.u; // another s-vector
	edge2.z = t2.v - t0.v; // another t-vector
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	tan0.x = tan1.x = tan2.x = -crossP.y / crossP.x;
	bin0.x = bin1.x = bin2.x = -crossP.z / crossP.x;

	// y, s, t
	edge1.x = v1.y - v0.y;
	edge2.x = v2.y - v0.y;
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	tan0.y = tan1.y = tan2.y = -crossP.y / crossP.x;
	bin0.y = bin1.y = bin2.y = -crossP.z / crossP.x;

	// z, s, t
	edge1.x = v1.z - v0.z;
	edge2.x = v2.z - v0.z;
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	tan0.z = tan1.z = tan2.z = -crossP.y / crossP.x;
	bin0.z = bin1.z = bin2.z = -crossP.z / crossP.x;

	// Orthonormalize to normal
	tan0 -= n0 * GetInnerProduct(tan0, n0);
	tan1 -= n1 * GetInnerProduct(tan1, n1);
	tan2 -= n2 * GetInnerProduct(tan2, n2);
	bin0 -= n0 * GetInnerProduct(bin0, n0);
	bin1 -= n1 * GetInnerProduct(bin1, n1);
	bin2 -= n2 * GetInnerProduct(bin2, n2);

	// Normalize tangents and binormals
	tan0 = Normalize(tan0);
	tan1 = Normalize(tan1);
	tan2 = Normalize(tan2);
	bin0 = Normalize(bin0);
	bin1 = Normalize(bin1);
	bin2 = Normalize(bin2);
}


//---------------------------------------------------------------------------
//  class MQGouraudHash
//     MQObjNormalクラスで内部的に使われるハッシュ
//---------------------------------------------------------------------------
class MQGouraudHash
{
public:
	MQPoint nv;
	int count;
	MQGouraudHash *next;

	MQGouraudHash() { nv.zero(); count=0; next=NULL; }
};


//---------------------------------------------------------------------------
//  class MQObjNormal
//     オブジェクト中の法線を計算するクラス。
//     スムージング角度に対する処理も行われる。
//     使用例は以下のような感じ。
//     A class for calculating normal vectors for an object.
//     Please refer the following example:
//
//       MQObjNormal *normal = new MQObjNormal(obj);
//       int face_count = obj->GetFaceCount();
//       for(int face=0; face<face_count; face++) {
//           int count = obj->GetFacePointCount(face);
//           for(int vert=0; vert<count; vert++) {
//				MQPoint nv = normal->Get(face, vert);
//              // ここに法線に対する処理を入れる Insert a procedure for normal vectors
//           }
//       }
//       delete normal;
//---------------------------------------------------------------------------
MQObjNormal::~MQObjNormal()
{
}

MQObjNormal::MQObjNormal(MQObject obj)
{
	int i,j;
	int face_count, vert_count;

	face_count = obj->GetFaceCount();
	vert_count = obj->GetVertexCount();

	normal.resize(face_count);
#if 0
	MQPoint *face_n = new MQPoint[face_count];

	// 面ごとに法線を計算
	// Calculate a normal vector for each face.
	for(i=0; i<face_count; i++)
	{
		int count = obj->GetFacePointCount(i);
		if(count < 3){
			face_n[i].zero();
			continue;
		}

		normal.resizeItem(i, count);

		// 三角形・四角形・多角形それぞれに対する法線の計算
		// Calculate a normal vector for a triangle, a quadrangle or a polygon.
		switch(count) {
		case 3:
			{
				int vi[3];
				obj->GetFacePointArray(i, vi);
				face_n[i] = GetNormal(
					obj->GetVertex(vi[0]), obj->GetVertex(vi[1]), obj->GetVertex(vi[2]));
			}
			break;
		case 4:
			{
				int vi[4];
				obj->GetFacePointArray(i, vi);
				face_n[i] = GetQuadNormal(
					obj->GetVertex(vi[0]), obj->GetVertex(vi[1]), 
					obj->GetVertex(vi[2]), obj->GetVertex(vi[3]));
			}
			break;
		default:
			{
				std::vector<int> vi(count);
				obj->GetFacePointArray(i, &(*vi.begin()));

				std::vector<MQPoint> pts(count);
				for(j=0; j<count; j++){
					pts[j] = obj->GetVertex(vi[j]);
				}
				face_n[i] = GetPolyNormal(&(*pts.begin()), count);
			}
			break;
		}
	}

	switch(obj->GetShading()) {
	case MQOBJECT_SHADE_FLAT:
		for(i=0; i<face_count; i++)
		{
			int count = obj->GetFacePointCount(i);
			for(j=0; j<count; j++)
				normal[i][j] = face_n[i];
			for(; j<4; j++)
				normal[i][j].zero();
		}
		break;

	case MQOBJECT_SHADE_GOURAUD:
		{
			MQGouraudHash *hash, *chs;

			// スムージング角度の取得
			// Get a smooth angle.
			float facet = cosf( RAD(obj->GetSmoothAngle()) );

			// ハッシュの初期化
			// Initialize a hash.
			int hash_size = vert_count;
			MQApexValueBase<MQGouraudHash*> vtbl;
			vtbl.resize(face_count);
			for(i=0; i<face_count; i++){
				int count = obj->GetFacePointCount(i);
				if(count >= 3){
					vtbl.resizeItem(i, count);
					hash_size += count;
				}
			}
			hash = new MQGouraudHash[hash_size];
			int hash_count = vert_count;

			// 面ごとにハッシュに法線ベクトルをセット
			// Set a normal vector for each face to the hash.
			for(i=0; i<face_count; i++)
			{
				int count = obj->GetFacePointCount(i);
				if(count < 3) continue;

				std::vector<int> vi(count);
				obj->GetFacePointArray(i, &(*vi.begin()));

				// 面中の各頂点ごとに法線ベクトルをハッシュへ格納
				// Set a normal vector for each vertex in a face to the hash.
				for(j=0; j<count; j++)
				{
					// 注目する頂点に対してのハッシュを得る
					// Get the hash for the target vertex.
					chs = &hash[vi[j]];

					// ハッシュがまだ空ならそこに情報を格納
					// Store the normal if the hash is empty.
					if(chs->count == 0) {
						chs->nv = face_n[i];
						chs->count++;
						vtbl[i][j] = chs;
						continue;
					}

					// ハッシュが空でないなら、既に格納されている法線とのスムージング
					// 角度をチェックする必要がある。
					// It is necessary that checks an angle between the normal vector and the stored vector.

					const MQPoint& pa = face_n[i];
					float da = pa.norm();
					for(; ; chs=chs->next)
					{
						// ２面の角度をチェック
						// Check the angle between the two faces
						float c = 0.0f;
						if(da > 0.0f) {
							MQPoint& pb = chs->nv;
							float db = pb.norm();
							if(db > 0.0f)
								c = GetInnerProduct(pa, pb) / sqrtf(da*db);
						}
							
						// スムージング角度以内か？
						// Is the angle lesser than the smooth angle?
						if(c >= facet)
						{
							// 注目する頂点に対して面の法線ベクトルをそのまま加算する。
							// （注目する頂点に属する面内の２辺の角度によるベクトルの加算量の調整はしていない）
							// Add the normal vector for the vertex.
							chs->nv += pa;
							chs->count++;
							vtbl[i][j] = chs;
							break;
						}

						// スムージングは行われないので、次のハッシュをチェック。
						// 次のハッシュデータがない場合は新規作成。
						// Check the next hash because a smoothing is not applied to the face.
						// Create a new hash if necessary.
						if(chs->next == NULL) {
							vtbl[i][j] = chs->next = &hash[hash_count++];
							chs = chs->next;
							chs->nv = pa;
							chs->count = 1;
							chs->next = NULL;
							break;
						}
					}
				}
			}

			// ハッシュ中の法線ベクトルの正規化
			// Normalize the stored vector in the hash.
			for(i=0,chs=hash; i<hash_count; i++,chs++) {
				if(chs->count > 1)
					chs->nv.normalize();
			}

			// 法線をバッファにセット
			// Set the normal vector.
			for(i=0; i<face_count; i++)
			{
				int count = obj->GetFacePointCount(i);
				if(count < 3) continue;
				for(j=0; j<count; j++)
					normal[i][j] = vtbl[i][j]->nv;
				for(; j<4; j++)
					normal[i][j].zero();
			}

			// ハッシュを解放
			// Free the hash.
			delete[] hash;
		}
		break;
	}

	delete[] face_n;
#else
	switch(obj->GetShading()) {
	case MQOBJECT_SHADE_FLAT:
		for(i=0; i<face_count; i++)
		{
			// 三角形・四角形・多角形それぞれに対する法線の計算
			// Calculate a normal vector for a triangle, a quadrangle or a polygon.
			int count = obj->GetFacePointCount(i);
			if(count < 3)continue;
			normal.resizeItem(i, count);
			MQPoint n;
			switch(count) {
			case 3:
			{
				int vi[3];
				obj->GetFacePointArray(i, vi);
				n = GetNormal(
					obj->GetVertex(vi[0]), obj->GetVertex(vi[1]), obj->GetVertex(vi[2]));
			}
			break;
			case 4:
			{
				int vi[4];
				obj->GetFacePointArray(i, vi);
				n = GetQuadNormal(
					obj->GetVertex(vi[0]), obj->GetVertex(vi[1]), 
					obj->GetVertex(vi[2]), obj->GetVertex(vi[3]));
			}
			break;
			default:
			{
				if(count < 3){
					n.zero();
				}
				std::vector<int> vi(count);
				obj->GetFacePointArray(i, &(*vi.begin()));

				std::vector<MQPoint> pts(count);
				for(j=0; j<count; j++){
					pts[j] = obj->GetVertex(vi[j]);
				}
				n = GetPolyNormal(&(*pts.begin()), count);
			}
			break;
			}
			normal.resizeItem(i, count);
			for(j=0; j<count; j++)
				normal[i][j] = n;
			for(; j<4; j++)
				normal[i][j].zero();
		}
		break;

	case MQOBJECT_SHADE_GOURAUD:
		for(i=0; i<face_count; i++)
		{
			int count = obj->GetFacePointCount(i);
			if(count < 3)continue;
			normal.resizeItem(i, count);
			BYTE flag;
			for(j=0; j<count; j++)
				obj->GetFaceVertexNormal(i,j,flag,normal[i][j]);
			for(; j<4; j++)
				normal[i][j].zero();
		}
	}
#endif
}


MQObjIndexedNormal::~MQObjIndexedNormal()
{
}

MQObjIndexedNormal::MQObjIndexedNormal(MQObject obj)
{
	int i,j;
	int face_count, vert_count;

	face_count = obj->GetFaceCount();
	vert_count = obj->GetVertexCount();

	index.resize(face_count);
#if 0
	MQPoint *face_n = new MQPoint[face_count];

	// 面ごとに法線を計算
	// Calculate a normal vector for each face.
	for(i=0; i<face_count; i++)
	{
		int count = obj->GetFacePointCount(i);
		if(count < 3){
			face_n[i].zero();
			continue;
		}

		index.resizeItem(i, count);

		// 三角形・四角形・多角形それぞれに対する法線の計算
		// Calculate a normal vector for a triangle, a quadrangle or a polygon.
		switch(count) {
		case 3:
			{
				int vi[3];
				obj->GetFacePointArray(i, vi);
				face_n[i] = ::GetNormal(
					obj->GetVertex(vi[0]), obj->GetVertex(vi[1]), obj->GetVertex(vi[2]));
			}
			break;
		case 4:
			{
				int vi[4];
				obj->GetFacePointArray(i, vi);
				face_n[i] = GetQuadNormal(
					obj->GetVertex(vi[0]), obj->GetVertex(vi[1]), 
					obj->GetVertex(vi[2]), obj->GetVertex(vi[3]));
			}
			break;
		default:
			{
				std::vector<int> vi(count);
				obj->GetFacePointArray(i, &(*vi.begin()));

				std::vector<MQPoint> pts(count);
				for(j=0; j<count; j++){
					pts[j] = obj->GetVertex(vi[j]);
				}
				face_n[i] = GetPolyNormal(&(*pts.begin()), count);
			}
			break;
		}
	}
	switch(obj->GetShading()) {
	case MQOBJECT_SHADE_FLAT:
		normal.resize(face_count);
		for(i=0; i<face_count; i++)
		{
			int count = obj->GetFacePointCount(i);
			normal[i] = face_n[i];
			for(j=0; j<count; j++)
				index[i][j] = i;
			for(; j<4; j++)
				index[i][j] = 0;
		}
		break;

	case MQOBJECT_SHADE_GOURAUD:
		{
			MQGouraudHash *hash, *chs;

			// スムージング角度の取得
			// Get a smooth angle.
			float facet = cosf( RAD(obj->GetSmoothAngle()) );

			// ハッシュの初期化
			// Initialize a hash.
			int hash_size = vert_count;
			MQApexValueBase<MQGouraudHash*> vtbl;
			vtbl.resize(face_count);
			for(i=0; i<face_count; i++){
				int count = obj->GetFacePointCount(i);
				if(count >= 3){
					vtbl.resizeItem(i, count);
					hash_size += count;
				}
			}
			hash = new MQGouraudHash[hash_size];
			int hash_count = vert_count;

			// 面ごとにハッシュに法線ベクトルをセット
			// Set a normal vector for each face to the hash.
			for(i=0; i<face_count; i++)
			{
				int count = obj->GetFacePointCount(i);
				if(count < 3) continue;

				std::vector<int> vi(count);
				obj->GetFacePointArray(i, &(*vi.begin()));

				// 面中の各頂点ごとに法線ベクトルをハッシュへ格納
				// Set a normal vector for each vertex in a face to the hash.
				for(j=0; j<count; j++)
				{
					// 注目する頂点に対してのハッシュを得る
					// Get the hash for the target vertex.
					chs = &hash[vi[j]];

					// ハッシュがまだ空ならそこに情報を格納
					// Store the normal if the hash is empty.
					if(chs->count == 0) {
						chs->nv = face_n[i];
						chs->count++;
						vtbl[i][j] = chs;
						continue;
					}

					// ハッシュが空でないなら、既に格納されている法線とのスムージング
					// 角度をチェックする必要がある。
					// It is necessary that checks an angle between the normal vector and the stored vector.

					const MQPoint& pa = face_n[i];
					float da = pa.norm();
					for(; ; chs=chs->next)
					{
						// ２面の角度をチェック
						// Check the angle between the two faces
						float c = 0.0f;
						if(da > 0.0f) {
							MQPoint& pb = chs->nv;
							float db = pb.norm();
							if(db > 0.0f)
								c = GetInnerProduct(pa, pb) / sqrtf(da*db);
						}
							
						// スムージング角度以内か？
						// Is the angle lesser than the smooth angle?
						if(c >= facet)
						{
							// 注目する頂点に対して面の法線ベクトルをそのまま加算する。
							// （注目する頂点に属する面内の２辺の角度によるベクトルの加算量の調整はしていない）
							// Add the normal vector for the vertex.
							chs->nv += pa;
							chs->count++;
							vtbl[i][j] = chs;
							break;
						}

						// スムージングは行われないので、次のハッシュをチェック。
						// 次のハッシュデータがない場合は新規作成。
						// Check the next hash because a smoothing is not applied to the face.
						// Create a new hash if necessary.
						if(chs->next == NULL) {
							vtbl[i][j] = chs->next = &hash[hash_count++];
							chs = chs->next;
							chs->nv = pa;
							chs->count = 1;
							chs->next = NULL;
							break;
						}
					}
				}
			}

			// ハッシュ中の法線ベクトルの正規化
			// Normalize the stored vector in the hash.
			normal.resize(hash_count);
			for(i=0,chs=hash; i<hash_count; i++,chs++) {
				if(chs->count > 1){
					chs->nv.normalize();
				}
				normal[i] = chs->nv;
			}

			// 法線のインデックスをバッファにセット
			// Set the normal index.
			for(i=0; i<face_count; i++)
			{
				int count = obj->GetFacePointCount(i);
				if(count < 3) continue;
				for(j=0; j<count; j++)
					index[i][j] = (int)(vtbl[i][j] - hash);
				for(; j<4; j++)
					index[i][j] = 0;
			}

			// ハッシュを解放
			// Free the hash.
			delete[] hash;
		}
		break;
	}
	delete[] face_n;
#else
	switch(obj->GetShading()) {
	case MQOBJECT_SHADE_FLAT:
		normal.resize(face_count);
		for(i=0; i<face_count; i++)
		{
			int count = obj->GetFacePointCount(i);
			if(count < 3)continue;
			index.resizeItem(i, count);
			switch(count) {
			case 3:
			{
				int vi[3];
				obj->GetFacePointArray(i, vi);
				normal[i] = ::GetNormal(
					obj->GetVertex(vi[0]), obj->GetVertex(vi[1]), obj->GetVertex(vi[2]));
			}
			break;
			case 4:
			{
				int vi[4];
				obj->GetFacePointArray(i, vi);
				normal[i] = GetQuadNormal(
					obj->GetVertex(vi[0]), obj->GetVertex(vi[1]), 
					obj->GetVertex(vi[2]), obj->GetVertex(vi[3]));
			}
			break;
			default:
			{
				if(count < 3){
					normal[i].zero();
					break;
				}
				std::vector<int> vi(count);
				obj->GetFacePointArray(i, &(*vi.begin()));

				std::vector<MQPoint> pts(count);
				for(j=0; j<count; j++){
					pts[j] = obj->GetVertex(vi[j]);
				}
				normal[i] = GetPolyNormal(&(*pts.begin()), count);
			}
			break;
			}
			for(j=0; j<count; j++)
				index[i][j] = i;
			for(; j<4; j++)
				index[i][j] = 0;
		}
		break;

	case MQOBJECT_SHADE_GOURAUD:
		int apex_count = 0;
		int k = 0;
		BYTE flag;
		for(i=0; i<face_count; i++)apex_count += obj->GetFacePointCount(i);
		normal.resize(apex_count);
		for(i=0; i<face_count; i++)
		{
			int count = obj->GetFacePointCount(i);
			if(count < 3)continue;
			index.resizeItem(i, count);
			for(j = 0; j < count; j++){
				obj->GetFaceVertexNormal(i,j,flag,normal[k]);
				index[i][j] = k;
				k++;
			}
			for(; j<4; j++)
				index[i][j] = 0;
		}
		break;
	}
#endif
}


//---------------------------------------------------------------------------
//  class MQObjEdge
//     オブジェクト中のエッジ対を管理する
//     以下のようにしてface_indexで示される面中のline_indexの辺を共有して
//     いる面のインデックスがpfに、辺のインデックスがplに得られる。
//     使用例は以下。
//
//       int pf,pl;
//       MQObjEdge *edge = new MQObjEdge(obj);
//       edge->getPair(face_index, line_index, pf, pl);
//       delete edge;
//
//---------------------------------------------------------------------------
MQObjEdge::MQObjEdge(MQObject obj)
{
	int vert_count = obj->GetVertexCount();
	int face_count = obj->GetFaceCount();

	m_obj = obj;
	m_face = face_count;
	if(!m_pair.resize(face_count)){
		m_face = 0;
		return;
	}

	int tree_size = vert_count;
	for(int cf=0; cf<face_count; cf++)
	{
		int cfc = obj->GetFacePointCount(cf);

		if(cfc >= 3){
			m_pair.resizeItem(cf, cfc);
			tree_size += cfc;
		}
	}

class MRelTree
{
public:
	MQObjEdgePair pair;
	int next;

	inline MRelTree() { next = -1; }
	inline MRelTree& operator = (const MRelTree& r)
		{pair=r.pair; next=r.next; return *this;}
};

	MRelTree *tree = new MRelTree[tree_size];

	int regvc = vert_count;
	std::vector<int> cvi, dvi;
	for(int cf=0; cf<face_count; cf++)
	{
		int cfc = obj->GetFacePointCount(cf);

		if(cfc < 3)
			continue;

		m_pair.resizeItem(cf, cfc);

		cvi.resize(cfc);
		obj->GetFacePointArray(cf, &(*cvi.begin()));

		cfc--; // decrement to be faster
		for(int j=0; j<=cfc; j++)
		{
			// check tree
			int v1 = cvi[j];
			int v2 = cvi[j<cfc? j+1 : 0];
			for(MRelTree drel=tree[v2]; drel.pair.face>=0; drel=tree[drel.next])
			{
				int df = drel.pair.face;
				int dfc = obj->GetFacePointCount(df);
				dvi.resize(dfc);
				obj->GetFacePointArray(df, &(*dvi.begin()));
				if(m_pair[df][drel.pair.line].face < 0)
				{
					if(/*v2 == dvi[drel.pair.line]
					&&*/ v1 == dvi[drel.pair.line<dfc-1 ? drel.pair.line+1 : 0])
					{
						// set relation
						m_pair[df][drel.pair.line] = MQObjEdgePair(cf,j);
						m_pair[cf][j] = drel.pair;
						goto CR_REG_END;
					}
				}
				if(drel.next < 0) break;
			}
			// not find in tree, so regist vertex1
			MRelTree *ctr;
			for(ctr=&tree[v1]; ctr->pair.face>=0; ctr=&tree[ctr->next]){
				if(ctr->next < 0){
					ctr->next = regvc;
					ctr = &tree[regvc++];
					break;
				}
			}
			ctr->pair = MQObjEdgePair(cf,j);
CR_REG_END:;
		}
	}

	delete[] tree;
}

MQObjEdge::~MQObjEdge()
{
}

bool MQObjEdge::getPair(int face_index, int line_index, int& pair_face, int& pair_line)
{
	if(face_index >= m_face)
		return false;

	if(m_pair[face_index][line_index].face < 0)
		return false;

	pair_face = m_pair[face_index][line_index].face;
	pair_line = m_pair[face_index][line_index].line;

	return true;
}

void MQObjEdge::setPair(int face_index, int line_index, int pair_face, int pair_line)
{
	if(face_index >= m_face)
		return;

	m_pair[face_index][line_index].face = pair_face;
	m_pair[face_index][line_index].line = pair_line;
}

void MQObjEdge::addFace(int vert_num)
{
	int index = m_face;
	m_face++;
	m_pair.resize(m_pair.size()+1);
	m_pair.resizeItem(index, vert_num);

	for(int i=0; i<vert_num; i++){
		m_pair[index][i].face = -1;
		m_pair[index][i].line = -1;
	}
}

