//---------------------------------------------------------------------------
//
//   MQInit.cpp      Copyright(C) 1999-2023, tetraface Inc.
//
//     The initialization functions based on Metasequoia SDK are 
//    defined in this file.
//     You do not need to modify this file.
//
//    　Metasequoia SDKの仕様に基づく初期化関数を定義している。
//    プラグイン開発者がこのファイルの内容を変更する必要はない。
//
//---------------------------------------------------------------------------

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#if __APPLE__
#include <CoreFoundation/CFBundle.h>
#endif
#include "MQPlugin.h"


//
// global functions
//
#ifdef _WIN32
HWND (MQAPICALL *MQ_GetWindowHandle)(void);
#endif
MQObject (MQAPICALL *MQ_CreateObject)(void);
MQMaterial (MQAPICALL *MQ_CreateMaterial)(void);
void (MQAPICALL *MQ_ShowFileDialog)(const char *title, MQFileDialogInfo *info);
void (MQAPICALL *MQ_ImportAxis)(MQFileDialogInfo *info, MQPoint *pts, int pts_count);
void (MQAPICALL *MQ_ExportAxis)(MQFileDialogInfo *info, MQPoint *pts, int pts_count);
BOOL (MQAPICALL *MQ_LoadImage)(const char *filename, LPVOID *header, LPVOID *buffer, DWORD reserved);
BOOL (MQAPICALL *MQ_LoadImageW)(const wchar_t *filename, LPVOID *header, LPVOID *buffer, DWORD reserved);
BOOL (MQAPICALL *MQ_GetSystemPath)(char *buffer, int type);
BOOL (MQAPICALL *MQ_GetSystemPathW)(wchar_t *buffer, int type);
void (MQAPICALL *MQ_RefreshView)(void *reserved);
#if __APPLE__
void (MQAPICALL *MQ_StationCallback)(MQStationCallbackProc proc, void *plugin, void *option);
#else
void (MQAPICALL *MQ_StationCallback)(MQStationCallbackProc proc, void *option);
#endif
BOOL (MQAPICALL *MQ_SendMessage)(int message_type, MQSendMessageInfo *info);

//
// class MQDodument
//
int  (MQAPICALL *MQDoc_GetObjectCount)(MQDocument doc);
MQObject (MQAPICALL *MQDoc_GetObject)(MQDocument doc, int index);
MQObject (MQAPICALL *MQDoc_GetObjectFromUniqueID)(MQDocument doc, int id);
int  (MQAPICALL *MQDoc_GetCurrentObjectIndex)(MQDocument doc);
void (MQAPICALL *MQDoc_SetCurrentObjectIndex)(MQDocument doc, int index);
int  (MQAPICALL *MQDoc_AddObject)(MQDocument doc, MQObject obj);
void (MQAPICALL *MQDoc_DeleteObject)(MQDocument doc, int index);
int  (MQAPICALL *MQDoc_GetObjectIndex)(MQDocument doc, MQObject obj);
void (MQAPICALL *MQDoc_GetUnusedObjectName)(MQDocument doc, char *buffer, int buffer_size, const char *base_name);
void (MQAPICALL *MQDoc_GetUnusedObjectNameW)(MQDocument doc, wchar_t *buffer, int buffer_size, const wchar_t *base_name);
int  (MQAPICALL *MQDoc_GetMaterialCount)(MQDocument doc);
MQMaterial (MQAPICALL *MQDoc_GetMaterial)(MQDocument doc, int index);
MQMaterial (MQAPICALL *MQDoc_GetMaterialFromUniqueID)(MQDocument doc, int id);
int  (MQAPICALL *MQDoc_GetCurrentMaterialIndex)(MQDocument doc);
void (MQAPICALL *MQDoc_SetCurrentMaterialIndex)(MQDocument doc, int index);
int  (MQAPICALL *MQDoc_AddMaterial)(MQDocument doc, MQMaterial mat);
void (MQAPICALL *MQDoc_DeleteMaterial)(MQDocument doc, int index);
void (MQAPICALL *MQDoc_GetUnusedMaterialName)(MQDocument doc, char *buffer, int buffer_size, const char *base_name);
void (MQAPICALL *MQDoc_GetUnusedMaterialNameW)(MQDocument doc, wchar_t *buffer, int buffer_size, const wchar_t *base_name);
BOOL (MQAPICALL *MQDoc_FindMappingFile)(MQDocument doc, char *out_path, const char *filename, DWORD map_type);
BOOL (MQAPICALL *MQDoc_FindMappingFileW)(MQDocument doc, wchar_t *out_path, const wchar_t *filename, DWORD map_type);
BOOL (MQAPICALL *MQDoc_GetMappingImage)(MQDocument doc, const char *filename, DWORD map_type, void **array);
BOOL (MQAPICALL *MQDoc_GetMappingImageW)(MQDocument doc, const wchar_t *filename, DWORD map_type, void **array);
void (MQAPICALL *MQDoc_Compact)(MQDocument doc);
void (MQAPICALL *MQDoc_ClearSelect)(MQDocument doc, DWORD flag);
BOOL (MQAPICALL *MQDoc_AddSelectVertex)(MQDocument doc, int objindex, int vertindex);
BOOL (MQAPICALL *MQDoc_DeleteSelectVertex)(MQDocument doc, int objindex, int vertindex);
BOOL (MQAPICALL *MQDoc_IsSelectVertex)(MQDocument doc, int objindex, int vertindex);
BOOL (MQAPICALL *MQDoc_AddSelectLine)(MQDocument doc, int objindex, int faceindex, int lineindex);
BOOL (MQAPICALL *MQDoc_DeleteSelectLine)(MQDocument doc, int objindex, int faceindex, int lineindex);
BOOL (MQAPICALL *MQDoc_IsSelectLine)(MQDocument doc, int objindex, int faceindex, int lineindex);
BOOL (MQAPICALL *MQDoc_AddSelectFace)(MQDocument doc, int objindex, int faceindex);
BOOL (MQAPICALL *MQDoc_DeleteSelectFace)(MQDocument doc, int objindex, int faceindex);
BOOL (MQAPICALL *MQDoc_IsSelectFace)(MQDocument doc, int objindex, int faceindex);
BOOL (MQAPICALL *MQDoc_AddSelectUVVertex)(MQDocument doc, int objindex, int faceindex, int vertindex);
BOOL (MQAPICALL *MQDoc_DeleteSelectUVVertex)(MQDocument doc, int objindex, int faceindex, int vertindex);
BOOL (MQAPICALL *MQDoc_IsSelectUVVertex)(MQDocument doc, int objindex, int faceindex, int vertindex);
MQScene (MQAPICALL *MQDoc_GetScene)(MQDocument doc, int index);
MQObject (MQAPICALL *MQDoc_GetParentObject)(MQDocument doc, MQObject obj);
int (MQAPICALL *MQDoc_GetChildObjectCount)(MQDocument doc, MQObject obj);
MQObject (MQAPICALL *MQDoc_GetChildObject)(MQDocument doc, MQObject obj, int index);
void (MQAPICALL *MQDoc_GetGlobalMatrix)(MQDocument doc, MQObject obj, float *matrix);
void (MQAPICALL *MQDoc_GetGlobalInverseMatrix)(MQDocument doc, MQObject obj, float *matrix);
int  (MQAPICALL *MQDoc_InsertObject)(MQDocument doc, MQObject obj, MQObject before);
BOOL (MQAPICALL *MQDoc_RemoveObject)(MQDocument doc, MQObject obj);
int  (MQAPICALL *MQDoc_CreateUserData)(MQDocument doc, MQUserDataInfo *info);
void (MQAPICALL *MQDoc_DeleteUserData)(MQDocument doc, int userdata_type, int userdata_id);
BOOL (MQAPICALL *MQDoc_Triangulate)(MQDocument doc, const MQPoint *points, int points_num, int *index_array, int index_num);

//
// class MQScene
//
void (MQAPICALL *MQScene_InitSize)(MQScene scene, int width, int height);
void (MQAPICALL *MQScene_GetProjMatrix)(MQScene scene, float *matrix);
void (MQAPICALL *MQScene_GetViewMatrix)(MQScene scene, float *matrix);
void (MQAPICALL *MQScene_IntValue)(MQScene scene, int type_id, int *values);
void (MQAPICALL *MQScene_FloatValue)(MQScene scene, int type_id, float *values);
void (MQAPICALL *MQScene_ValueArray)(MQScene scene, int type_id, void **array);
BOOL (MQAPICALL *MQScene_GetVisibleFace)(MQScene scene, MQObject obj, BOOL *visible);

//
// class MQObject
//
void (MQAPICALL *MQObj_Delete)(MQObject obj);
MQObject (MQAPICALL *MQObj_Clone)(MQObject obj);
void (MQAPICALL *MQObj_Merge)(MQObject dest, MQObject source);
void (MQAPICALL *MQObj_Clear)(MQObject obj, DWORD flag);
void (MQAPICALL *MQObj_Freeze)(MQObject obj, DWORD flag);
//void (MQAPICALL *MQObj_GetName)(MQObject obj, char *buffer, int size);
int  (MQAPICALL *MQObj_GetVertexCount)(MQObject obj);
void (MQAPICALL *MQObj_GetVertex)(MQObject obj, int index, MQPoint *pts);
void (MQAPICALL *MQObj_SetVertex)(MQObject obj, int index, MQPoint *pts);
void (MQAPICALL *MQObj_GetVertexArray)(MQObject obj, MQPoint *ptsarray);
int  (MQAPICALL *MQObj_GetFaceCount)(MQObject obj);
int  (MQAPICALL *MQObj_GetFacePointCount)(MQObject obj, int face);
void (MQAPICALL *MQObj_GetFacePointArray)(MQObject obj, int face, int *vertex);
void (MQAPICALL *MQObj_GetFaceCoordinateArray)(MQObject obj, int face, MQCoordinate *uvarray);
void (MQAPICALL *MQObj_GetFaceCoordinate)(MQObject obj, int face, int apex, MQCoordinate& uv);
BOOL (MQAPICALL *MQObj_GetFaceChannelCoordinate)(MQObject obj, int face, int apex, UINT channelID, MQCoordinate& uv);
int  (MQAPICALL *MQObj_GetFaceMaterial)(MQObject obj, int face);
UINT (MQAPICALL *MQObj_GetFaceUniqueID)(MQObject obj, int face);
int (MQAPICALL *MQObj_GetFaceIndexFromUniqueID)(MQObject obj, UINT unique_id);
void (MQAPICALL *MQObj_SetName)(MQObject obj, const char *buffer);
int  (MQAPICALL *MQObj_AddVertex)(MQObject obj, MQPoint *p);
BOOL (MQAPICALL *MQObj_DeleteVertex)(MQObject obj, int index, BOOL del_vert);
int  (MQAPICALL *MQObj_GetVertexRefCount)(MQObject obj, int index);
UINT (MQAPICALL *MQObj_GetVertexUniqueID)(MQObject obj, int index);
int (MQAPICALL *MQObj_GetVertexIndexFromUniqueID)(MQObject obj, UINT unique_id);
int  (MQAPICALL *MQObj_GetVertexRelatedFaces)(MQObject obj, int vertex, int *faces);
//DWORD (MQAPICALL *MQObj_GetVertexColor)(MQObject obj, int index); // OBSOLUTE
//void (MQAPICALL *MQObj_SetVertexColor)(MQObject obj, int index, DWORD color); // OBSOLUTE
float (MQAPICALL *MQObj_GetVertexWeight)(MQObject obj, int index);
void (MQAPICALL *MQObj_SetVertexWeight)(MQObject obj, int index, float value);
void (MQAPICALL *MQObj_CopyVertexAttribute)(MQObject obj, int vert1, MQObject obj2, int vert2);
int  (MQAPICALL *MQObj_AddFace)(MQObject obj, int count, int *index);
int  (MQAPICALL *MQObj_InsertFace)(MQObject obj, int face_index, int count, int *vert_index);
BOOL (MQAPICALL *MQObj_DeleteFace)(MQObject obj, int index, BOOL del_vert);
BOOL (MQAPICALL *MQObj_InvertFace)(MQObject obj, int index);
void (MQAPICALL *MQObj_SetFaceMaterial)(MQObject obj, int face, int material);
void (MQAPICALL *MQObj_SetFaceCoordinateArray)(MQObject obj, int face, MQCoordinate *uvarray);
void (MQAPICALL *MQObj_SetFaceCoordinate)(MQObject obj, int face, int vertex, const MQCoordinate& uv);
BOOL (MQAPICALL *MQObj_SetFaceChannelCoordinate)(MQObject obj, int face, int apex, UINT channelID, const MQCoordinate& uv);
DWORD (MQAPICALL *MQObj_GetFaceVertexColor)(MQObject obj, int face, int vertex);
void (MQAPICALL *MQObj_SetFaceVertexColor)(MQObject obj, int face, int vertex, DWORD color);
float (MQAPICALL *MQObj_GetFaceEdgeCrease)(MQObject obj, int face, int line);
void (MQAPICALL *MQObj_SetFaceEdgeCrease)(MQObject obj, int face, int line, float crease);
void (MQAPICALL *MQObj_GetFaceVertexNormal)(MQObject obj, int face, int vertex, BYTE &flag, MQPoint &normal);
void (MQAPICALL *MQObj_SetFaceVertexNormal)(MQObject obj, int face, int vertex, BYTE flag, MQPoint normal);
BOOL (MQAPICALL *MQObj_GetFaceVisible)(MQObject obj, int face);
void (MQAPICALL *MQObj_SetFaceVisible)(MQObject obj, int face, BOOL flag);
void (MQAPICALL *MQObj_OptimizeVertex)(MQObject obj, float distance, MQBool *apply);
void (MQAPICALL *MQObj_Compact)(MQObject obj);
DWORD (MQAPICALL *MQObj_GetVisible)(MQObject obj);
void (MQAPICALL *MQObj_SetVisible)(MQObject obj, DWORD visible);
DWORD (MQAPICALL *MQObj_GetPatchType)(MQObject obj);
void (MQAPICALL *MQObj_SetPatchType)(MQObject obj, DWORD type);
int  (MQAPICALL *MQObj_GetPatchSegment)(MQObject obj);
void (MQAPICALL *MQObj_SetPatchSegment)(MQObject obj, int segment);
int  (MQAPICALL *MQObj_GetShading)(MQObject obj);
void (MQAPICALL *MQObj_SetShading)(MQObject obj, int type);
float (MQAPICALL *MQObj_GetSmoothAngle)(MQObject obj);
void (MQAPICALL *MQObj_SetSmoothAngle)(MQObject obj, float degree);
int  (MQAPICALL *MQObj_GetMirrorType)(MQObject obj);
void (MQAPICALL *MQObj_SetMirrorType)(MQObject obj, int type);
DWORD (MQAPICALL *MQObj_GetMirrorAxis)(MQObject obj);
void (MQAPICALL *MQObj_SetMirrorAxis)(MQObject obj, DWORD axis);
float (MQAPICALL *MQObj_GetMirrorDistance)(MQObject obj);
void (MQAPICALL *MQObj_SetMirrorDistance)(MQObject obj, float dis);
int  (MQAPICALL *MQObj_GetLatheType)(MQObject obj);
void (MQAPICALL *MQObj_SetLatheType)(MQObject obj, int type);
DWORD (MQAPICALL *MQObj_GetLatheAxis)(MQObject obj);
void (MQAPICALL *MQObj_SetLatheAxis)(MQObject obj, DWORD axis);
int  (MQAPICALL *MQObj_GetLatheSegment)(MQObject obj);
void (MQAPICALL *MQObj_SetLatheSegment)(MQObject obj, int segment);
int (MQAPICALL *MQObj_GetIntValue)(MQObject obj, int type_id);
void (MQAPICALL *MQObj_GetFloatArray)(MQObject obj, int type_id, float *array);
void (MQAPICALL *MQObj_SetIntValue)(MQObject obj, int type_id, int value);
void (MQAPICALL *MQObj_SetFloatArray)(MQObject obj, int type_id, const float *array);
void (MQAPICALL *MQObj_PointerArray)(MQObject obj, int type_id, void **array);
BOOL (MQAPICALL *MQObj_AllocUserData)(MQObject obj, int userdata_id);
void (MQAPICALL *MQObj_FreeUserData)(MQObject obj, int userdata_id);
BOOL (MQAPICALL *MQObj_GetUserData)(MQObject obj, int userdata_id, int offset, int copy_bytes, void *buffer);
BOOL (MQAPICALL *MQObj_SetUserData)(MQObject obj, int userdata_id, int offset, int copy_bytes, const void *buffer);
BOOL (MQAPICALL *MQObj_AllocVertexUserData)(MQObject obj, int userdata_id);
void (MQAPICALL *MQObj_FreeVertexUserData)(MQObject obj, int userdata_id);
BOOL (MQAPICALL *MQObj_GetVertexUserData)(MQObject obj, int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, void *buffer);
BOOL (MQAPICALL *MQObj_SetVertexUserData)(MQObject obj, int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, const void *buffer);
BOOL (MQAPICALL *MQObj_AllocFaceUserData)(MQObject obj, int userdata_id);
void (MQAPICALL *MQObj_FreeFaceUserData)(MQObject obj, int userdata_id);
BOOL (MQAPICALL *MQObj_GetFaceUserData)(MQObject obj, int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, void *buffer);
BOOL (MQAPICALL *MQObj_SetFaceUserData)(MQObject obj, int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, const void *buffer);

//
// class MQMaterial
//
void (MQAPICALL *MQMat_Delete)(MQMaterial mat);
int (MQAPICALL *MQMat_GetIntValue)(MQMaterial mat, int type_id);
void (MQAPICALL *MQMat_GetFloatArray)(MQMaterial mat, int type_id, float *array);
//void (MQAPICALL *MQMat_GetName)(MQMaterial mat, char *buffer, int size);
void (MQAPICALL *MQMat_GetColor)(MQMaterial mat, MQColor *color);
float (MQAPICALL *MQMat_GetAlpha)(MQMaterial mat);
float (MQAPICALL *MQMat_GetDiffuse)(MQMaterial mat);
float (MQAPICALL *MQMat_GetAmbient)(MQMaterial mat);
float (MQAPICALL *MQMat_GetEmission)(MQMaterial mat);
float (MQAPICALL *MQMat_GetSpecular)(MQMaterial mat);
float (MQAPICALL *MQMat_GetPower)(MQMaterial mat);
void (MQAPICALL *MQMat_GetTextureName)(MQMaterial mat, char *buffer, int size);
void (MQAPICALL *MQMat_GetAlphaName)(MQMaterial mat, char *buffer, int size);
void (MQAPICALL *MQMat_GetBumpName)(MQMaterial mat, char *buffer, int size);
void (MQAPICALL *MQMat_SetIntValue)(MQMaterial mat, int type_id, int value);
void (MQAPICALL *MQMat_SetFloatArray)(MQMaterial mat, int type_id, const float *array);
void (MQAPICALL *MQMat_SetName)(MQMaterial mat, const char *name);
void (MQAPICALL *MQMat_SetColor)(MQMaterial mat, MQColor *color);
void (MQAPICALL *MQMat_SetAlpha)(MQMaterial mat, float value);
void (MQAPICALL *MQMat_SetDiffuse)(MQMaterial mat, float value);
void (MQAPICALL *MQMat_SetAmbient)(MQMaterial mat, float value);
void (MQAPICALL *MQMat_SetEmission)(MQMaterial mat, float value);
void (MQAPICALL *MQMat_SetSpecular)(MQMaterial mat, float value);
void (MQAPICALL *MQMat_SetPower)(MQMaterial mat, float value);
void (MQAPICALL *MQMat_SetTextureName)(MQMaterial mat, const char *name);
void (MQAPICALL *MQMat_SetAlphaName)(MQMaterial mat, const char *name);
void (MQAPICALL *MQMat_SetBumpName)(MQMaterial mat, const char *name);
BOOL (MQAPICALL *MQMat_AllocUserData)(MQMaterial mat, int userdata_id);
void (MQAPICALL *MQMat_FreeUserData)(MQMaterial mat, int userdata_id);
BOOL (MQAPICALL *MQMat_GetUserData)(MQMaterial mat, int userdata_id, int offset, int copy_bytes, void *buffer);
BOOL (MQAPICALL *MQMat_SetUserData)(MQMaterial mat, int userdata_id, int offset, int copy_bytes, const void *buffer);
void (MQAPICALL *MQMat_GetValueArray)(MQMaterial mat, int type_id, void **array);
void (MQAPICALL *MQMat_SetValueArray)(MQMaterial mat, int type_id, void **array);

// class MQShaderNode
void (MQAPICALL *MQShaderNode_GetValueArray)(MQShaderNode shader, int type_id, void **array);
void (MQAPICALL *MQShaderNode_SetValueArray)(MQShaderNode shader, int type_id, void **array);

//
// class MQMatrix
//
void (MQAPICALL *MQMatrix_FloatValue)(float *mtx, int type_id, float *values);

//
// class MQXmlElement
//
void (MQAPICALL *MQXmlElem_Value)(MQXmlElement elem, int type_id, void *values);

//
// class MQXmlDocument
//
void (MQAPICALL *MQXmlDoc_Value)(MQXmlDocument doc, int type_id, void *values);

//
// class MQWidget
//
BOOL (MQAPICALL *MQWidget_Value)(int widget_id, int type_id, void *values);

//
// class MQCanvas
//
void (MQAPICALL *MQCanvas_Value)(void *canvas, int type_id, void *values);

//
// class MQSVGDraw
//
void (MQAPICALL *MQSVGDraw_Value)(void *canvas, int type_id, void *values);


//---------------------------------------------------------------------------
//  MQCheckVersion
//---------------------------------------------------------------------------
MQPLUGIN_EXPORT DWORD MQCheckVersion(DWORD exe_version)
{
	// Version check
	if(exe_version < MQPLUGIN_REQUIRED_EXE_VERSION)
		return 0;

	// This plug-in is based on the latest version of the specification
	// このプラグインは最新版に基づく仕様
	return MQPLUGIN_VERSION;
}


#ifdef _WIN32
#define GPA(proc) \
	*(FARPROC *)&proc = GetProcAddress(hModule, #proc); \
	if(proc == NULL) goto MQINIT_EXIT;
#endif
#if __APPLE__
#define GPA(proc) \
	*(void**)&proc = CFBundleGetFunctionPointerForName(bundleRef, CFSTR(#proc)); \
	if(proc == NULL) goto MQINIT_EXIT;
#endif

//---------------------------------------------------------------------------
//  MQInit
//---------------------------------------------------------------------------
MQPLUGIN_EXPORT BOOL MQInit(const char *exe_name)
{
#ifdef _WIN32
	HMODULE hModule = LoadLibraryA(exe_name);
	if(hModule == NULL)
		return FALSE;
#endif
#if __APPLE__
	//CFURLRef bundleURL = CFURLCreateFromFileSystemRepresentation(kCFAllocatorDefault, (const UInt8*)exe_name, strlen(exe_name), FALSE);
	
	CFBundleRef bundleRef = CFBundleGetMainBundle();//CFBundleCreate(kCFAllocatorDefault, bundleURL);
	//CFRelease(bundleURL);
	if(!bundleRef) return FALSE;
	
	if(!CFBundleLoadExecutable(bundleRef)){
		//CFRelease(bundleRef);
		return FALSE;
	}
#endif

	BOOL result = FALSE;

	// ***** Global *****
#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4996)
	GPA(MQ_GetWindowHandle);
#pragma warning(pop)
#endif
	GPA(MQ_CreateObject);
	GPA(MQ_CreateMaterial);
	GPA(MQ_ShowFileDialog);
	GPA(MQ_ImportAxis);
	GPA(MQ_ExportAxis);
	GPA(MQ_LoadImage);
	GPA(MQ_LoadImageW);
	GPA(MQ_GetSystemPath);
	GPA(MQ_GetSystemPathW);
	GPA(MQ_RefreshView);
	GPA(MQ_StationCallback);
	GPA(MQ_SendMessage);

	// ***** MQDocument *****
	GPA(MQDoc_GetObjectCount);
	GPA(MQDoc_GetObject);
	GPA(MQDoc_GetObjectFromUniqueID);
	GPA(MQDoc_GetCurrentObjectIndex);
	GPA(MQDoc_SetCurrentObjectIndex);
	GPA(MQDoc_AddObject);
	GPA(MQDoc_DeleteObject);
	GPA(MQDoc_GetObjectIndex);
	GPA(MQDoc_GetUnusedObjectName);
	GPA(MQDoc_GetUnusedObjectNameW);
	GPA(MQDoc_GetMaterialCount);
	GPA(MQDoc_GetMaterial);
	GPA(MQDoc_GetMaterialFromUniqueID);
	GPA(MQDoc_GetCurrentMaterialIndex);
	GPA(MQDoc_SetCurrentMaterialIndex);
	GPA(MQDoc_AddMaterial);
	GPA(MQDoc_DeleteMaterial);
	GPA(MQDoc_GetUnusedMaterialName);
	GPA(MQDoc_GetUnusedMaterialNameW);
	GPA(MQDoc_Compact);
	GPA(MQDoc_ClearSelect);
	GPA(MQDoc_AddSelectVertex);
	GPA(MQDoc_DeleteSelectVertex);
	GPA(MQDoc_IsSelectVertex);
	GPA(MQDoc_AddSelectLine);
	GPA(MQDoc_DeleteSelectLine);
	GPA(MQDoc_IsSelectLine);
	GPA(MQDoc_AddSelectFace);
	GPA(MQDoc_DeleteSelectFace);
	GPA(MQDoc_IsSelectFace);
	GPA(MQDoc_AddSelectUVVertex);
	GPA(MQDoc_DeleteSelectUVVertex);
	GPA(MQDoc_IsSelectUVVertex);
	GPA(MQDoc_FindMappingFile);
	GPA(MQDoc_FindMappingFileW);
	GPA(MQDoc_GetScene);
	GPA(MQDoc_GetMappingImage);
	GPA(MQDoc_GetMappingImageW);
	GPA(MQDoc_GetParentObject);
	GPA(MQDoc_GetChildObjectCount);
	GPA(MQDoc_GetChildObject);
	GPA(MQDoc_GetGlobalMatrix);
	GPA(MQDoc_GetGlobalInverseMatrix);
	GPA(MQDoc_InsertObject);
	GPA(MQDoc_RemoveObject);
	GPA(MQDoc_CreateUserData);
	GPA(MQDoc_DeleteUserData);
	GPA(MQDoc_Triangulate);

	// ***** MQScene *****
	GPA(MQScene_InitSize);
	GPA(MQScene_GetProjMatrix);
	GPA(MQScene_GetViewMatrix);
	GPA(MQScene_IntValue);
	GPA(MQScene_FloatValue);
	GPA(MQScene_ValueArray);
	GPA(MQScene_GetVisibleFace);

	// ***** MQObject *****
	GPA(MQObj_Delete);
	GPA(MQObj_Clone);
	GPA(MQObj_Merge);
	GPA(MQObj_Clear);
	GPA(MQObj_Freeze);
	//GPA(MQObj_GetName);
	GPA(MQObj_GetVertexCount);
	GPA(MQObj_GetVertex);
	GPA(MQObj_SetVertex);
	GPA(MQObj_GetVertexArray);
	GPA(MQObj_GetFaceCount);
	GPA(MQObj_GetFacePointCount);
	GPA(MQObj_GetFacePointArray);
	GPA(MQObj_GetFaceCoordinateArray);
	GPA(MQObj_GetFaceCoordinate);
	GPA(MQObj_GetFaceChannelCoordinate);
	GPA(MQObj_GetFaceMaterial);
	GPA(MQObj_GetFaceUniqueID);
	GPA(MQObj_GetFaceIndexFromUniqueID);
	GPA(MQObj_SetName);
	GPA(MQObj_AddVertex);
	GPA(MQObj_DeleteVertex);
	GPA(MQObj_GetVertexRefCount);
	GPA(MQObj_GetVertexUniqueID);
	GPA(MQObj_GetVertexIndexFromUniqueID);
	GPA(MQObj_GetVertexRelatedFaces);
	//GPA(MQObj_GetVertexColor); // OBSOLETE
	//GPA(MQObj_SetVertexColor); // OBSOLETE
	GPA(MQObj_GetVertexWeight);
	GPA(MQObj_SetVertexWeight);
	GPA(MQObj_CopyVertexAttribute);
	GPA(MQObj_AddFace);
	GPA(MQObj_InsertFace);
	GPA(MQObj_DeleteFace);
	GPA(MQObj_InvertFace);
	GPA(MQObj_SetFaceMaterial);
	GPA(MQObj_SetFaceCoordinateArray);
	GPA(MQObj_SetFaceCoordinate);
	GPA(MQObj_SetFaceChannelCoordinate);
	GPA(MQObj_GetFaceVertexColor);
	GPA(MQObj_SetFaceVertexColor);
	GPA(MQObj_GetFaceEdgeCrease);
	GPA(MQObj_SetFaceEdgeCrease);
	GPA(MQObj_GetFaceVertexNormal);
	GPA(MQObj_SetFaceVertexNormal);
	GPA(MQObj_GetFaceVisible);
	GPA(MQObj_SetFaceVisible);
	GPA(MQObj_OptimizeVertex);
	GPA(MQObj_Compact);
	GPA(MQObj_GetVisible);
	GPA(MQObj_SetVisible);
	GPA(MQObj_GetPatchType);
	GPA(MQObj_SetPatchType);
	GPA(MQObj_GetPatchSegment);
	GPA(MQObj_SetPatchSegment);
	GPA(MQObj_GetShading);
	GPA(MQObj_SetShading);
	GPA(MQObj_GetSmoothAngle);
	GPA(MQObj_SetSmoothAngle);
	GPA(MQObj_GetMirrorType);
	GPA(MQObj_SetMirrorType);
	GPA(MQObj_GetMirrorAxis);
	GPA(MQObj_SetMirrorAxis);
	GPA(MQObj_GetMirrorDistance);
	GPA(MQObj_SetMirrorDistance);
	GPA(MQObj_GetLatheType);
	GPA(MQObj_SetLatheType);
	GPA(MQObj_GetLatheAxis);
	GPA(MQObj_SetLatheAxis);
	GPA(MQObj_GetLatheSegment);
	GPA(MQObj_SetLatheSegment);
	GPA(MQObj_GetIntValue);
	GPA(MQObj_GetFloatArray);
	GPA(MQObj_SetIntValue);
	GPA(MQObj_SetFloatArray);
	GPA(MQObj_PointerArray);
	GPA(MQObj_AllocUserData);
	GPA(MQObj_FreeUserData);
	GPA(MQObj_GetUserData);
	GPA(MQObj_SetUserData);
	GPA(MQObj_AllocVertexUserData);
	GPA(MQObj_FreeVertexUserData);
	GPA(MQObj_GetVertexUserData);
	GPA(MQObj_SetVertexUserData);
	GPA(MQObj_AllocFaceUserData);
	GPA(MQObj_FreeFaceUserData);
	GPA(MQObj_GetFaceUserData);
	GPA(MQObj_SetFaceUserData);

	// ***** MQMaterial ***** 
	GPA(MQMat_Delete);
	GPA(MQMat_GetIntValue);
	GPA(MQMat_GetFloatArray);
	//GPA(MQMat_GetName);
	GPA(MQMat_GetColor);
	GPA(MQMat_GetAlpha);
	GPA(MQMat_GetDiffuse);
	GPA(MQMat_GetAmbient);
	GPA(MQMat_GetEmission);
	GPA(MQMat_GetSpecular);
	GPA(MQMat_GetPower);
	GPA(MQMat_GetTextureName);
	GPA(MQMat_GetAlphaName);
	GPA(MQMat_GetBumpName);
	GPA(MQMat_SetIntValue);
	GPA(MQMat_SetFloatArray);
	GPA(MQMat_SetName);
	GPA(MQMat_SetColor);
	GPA(MQMat_SetAlpha);
	GPA(MQMat_SetDiffuse);
	GPA(MQMat_SetAmbient);
	GPA(MQMat_SetEmission);
	GPA(MQMat_SetSpecular);
	GPA(MQMat_SetPower);
	GPA(MQMat_SetTextureName);
	GPA(MQMat_SetAlphaName);
	GPA(MQMat_SetBumpName);
	GPA(MQMat_AllocUserData);
	GPA(MQMat_FreeUserData);
	GPA(MQMat_GetUserData);
	GPA(MQMat_SetUserData);
	GPA(MQMat_GetValueArray);
	GPA(MQMat_SetValueArray);
	GPA(MQShaderNode_GetValueArray);
	GPA(MQShaderNode_SetValueArray);

	GPA(MQMatrix_FloatValue);

	GPA(MQXmlElem_Value);

	GPA(MQXmlDoc_Value);

	GPA(MQWidget_Value);

	GPA(MQCanvas_Value);
	GPA(MQSVGDraw_Value);

	result = TRUE;

MQINIT_EXIT:
#ifdef _WIN32
	FreeLibrary(hModule);
#endif
#if __APPLE__
	//CFBundleUnloadExecutable(bundleRef);
	//CFRelease(bundleRef);
#endif
	return result;
}


