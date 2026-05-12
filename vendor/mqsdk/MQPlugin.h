//---------------------------------------------------------------------------
//
//   MQPlugin.h      Copyright(C) 1999-2023, tetraface Inc.
//
//     This is an include file based on specification of Metasequoia SDK. 
//    You do not need to modify this file.
//
//    　Metasequoia SDKの仕様に基づくインクルードファイル。
//    プラグイン開発者がこのファイルの内容を変更する必要はない。
//
//---------------------------------------------------------------------------

#ifndef MQPluginH
#define MQPluginH

#include <math.h>
#include <stdlib.h>
#include <string>

// It treats as the latest revision if MQPLUGIN_VERSION is not defined in preprocessor.
// プリプロセッサでMQPLUGIN_VERSIONが定義されていなければ最新として扱う
#ifndef MQPLUGIN_VERSION
#define MQPLUGIN_VERSION  0x0485    // Rev4.85
#endif
#ifndef MQPLUGIN_REQUIRED_EXE_VERSION
#define MQPLUGIN_REQUIRED_EXE_VERSION 0x4805
#endif


#ifndef MQPLUGIN_EXPORTS
#define MQPLUGIN_API extern "C"

#ifdef _WIN32
#ifdef GetObject
#undef GetObject
inline int GetObject(HGDIOBJ hgdiobj, int cbBuffer, LPVOID lpvObject)
{
#ifdef UNICODE
	return GetObjectW(hgdiobj, cbBuffer, lpvObject);
#else
	return GetObjectA(hgdiobj, cbBuffer, lpvObject);
#endif
}
#endif

#ifdef min
#undef min
template<typename T> inline T min(T a, T b) { return (a < b) ? a : b; }
#endif
#ifdef max
#undef max
template<typename T> inline T max(T a, T b) { return (a > b) ? a : b; }
#endif
#endif
#if __APPLE__
typedef char BOOL;
typedef int INT;
typedef unsigned int UINT;
typedef short SHORT;
typedef unsigned short USHORT;
typedef float FLOAT;
typedef char CHAR;
typedef void VOID, *LPVOID;
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int64_t __int64;
typedef int64_t INT64;
typedef uint64_t UINT64;
#define CONST const
#define FALSE 0
#define TRUE 1
struct POINT { int x, y; };
#ifndef RGBQUAD_defined
#define RGBQUAD_defined
struct RGBQUAD { BYTE rgbBlue, rgbGreen, rgbRed, rgbReserved; };
#endif
#define _countof(_x) (sizeof(_x) / sizeof(_x[0]))
inline int _wtoi(const wchar_t *s) {
	try { return std::stoi(std::wstring(s)); }
	catch(...){ return 0; }
}
inline double _wtof(const wchar_t *s) {
	try { return std::stod(std::wstring(s)); }
	catch(...){ return 0.0; }
}
class MQCursor;
typedef MQCursor *HCURSOR;
#define CALLBACK
#endif

inline POINT operator + (const POINT& a, const POINT& b) { POINT p = {a.x+b.x, a.y+b.y}; return p; }
inline POINT operator - (const POINT& a, const POINT& b) { POINT p = {a.x-b.x, a.y-b.y}; return p; }
#endif

#ifdef _WIN32
#define MQPLUGIN_EXPORT extern "C" __declspec(dllexport)
#ifdef _WIN64
#define MQAPICALL
#else
#define MQAPICALL __stdcall
#endif
#endif
#if __APPLE__
#define MQPLUGIN_EXPORT extern "C" __attribute__((visibility("default")))
#define MQAPICALL
#endif

#if __APPLE__
#include <sys/syslimits.h>
#define MQ_MAX_PATH PATH_MAX
#else
#define MQ_MAX_PATH MAX_PATH
#endif

#if __APPLE__
#define MK_LBUTTON 0x01
#define MK_RBUTTON 0x02
#define MK_SHIFT   0x04
#define MK_CONTROL 0x08
#define MK_MBUTTON 0x10
#define MK_ALT     0x20
#define MK_COMMAND 0x40 // Mac only
#endif

#define MQPLUGIN_TYPE_IMPORT   1
#define MQPLUGIN_TYPE_EXPORT   2
#define MQPLUGIN_TYPE_CREATE   3
#define MQPLUGIN_TYPE_OBJECT   4
#define MQPLUGIN_TYPE_SELECT   5
#define MQPLUGIN_TYPE_STATION  6
#define MQPLUGIN_TYPE_COMMAND  7

// MQOnEvent
#define MQEVENT_INITIALIZE			1
#define MQEVENT_EXIT				2
#define MQEVENT_ENUM_SUBCOMMAND     3		// new in Rev4.23
#define MQEVENT_SUBCOMMAND_STRING   4		// new in Rev4.23
#define MQEVENT_BASE_INSTANCE       5		// new in Rev4.59
#define MQEVENT_NEW_INSTANCE        6		// new in Rev4.59
#define MQEVENT_CONFIG_CHANGED      7		// new in Rev4.64
#define MQEVENT_ACTIVATE			100
#define MQEVENT_IS_ACTIVATED		101
#define MQEVENT_MINIMIZE			102
#define MQEVENT_USER_MESSAGE		103
#define MQEVENT_SUBCOMMAND			104		// new in Rev4.23
#define MQEVENT_SWITCH_SUBCOMMAND	105		// new in Rev4.64
#define MQEVENT_DRAW				110
#define MQEVENT_LBUTTON_DOWN		120
#define MQEVENT_LBUTTON_MOVE		121
#define MQEVENT_LBUTTON_UP			122
#define MQEVENT_MBUTTON_DOWN		123
#define MQEVENT_MBUTTON_MOVE		124
#define MQEVENT_MBUTTON_UP			125
#define MQEVENT_RBUTTON_DOWN		126
#define MQEVENT_RBUTTON_MOVE		127
#define MQEVENT_RBUTTON_UP			128
#define MQEVENT_MOUSE_MOVE			129
#define MQEVENT_MOUSE_WHEEL			130
#define MQEVENT_KEY_DOWN			140
#define MQEVENT_KEY_UP				141
#define MQEVENT_NEW_DOCUMENT		200
#define MQEVENT_END_DOCUMENT		201
#define MQEVENT_SAVE_DOCUMENT		202
#define MQEVENT_SAVE_PAST_DOCUMENT	203		// new in Rev4.60
#define MQEVENT_INSERT_DOCUMENT		204		// new in Rev4.70
#define MQEVENT_UNDO				210
#define MQEVENT_REDO				211
#define MQEVENT_UNDO_UPDATED		212
#define MQEVENT_OBJECT_LIST			220
#define MQEVENT_OBJECT_MODIFIED		221
#define MQEVENT_OBJECT_SELECTED		222
#define MQEVENT_MATERIAL_LIST		230
#define MQEVENT_MATERIAL_MODIFIED	231
#define MQEVENT_SCENE				240
#define MQEVENT_EDIT_OPTION			250		// new in Rev4.40
#define MQEVENT_QUERY_INTERPOLATE	260		// new in Rev4.72
#define MQEVENT_INTERPOLATE			261		// new in Rev4.72
#define MQEVENT_COPY_PASTE			262		// new in Rev4.72
#define MQEVENT_IMPORT_SUPPORT_BACKGROUND	300
#define MQEVENT_IMPORT_SET_OPTIONS			301

// MQ_SendMessage
#define MQMESSAGE_ACTIVATE 				100
#define MQMESSAGE_USER_MESSAGE			101
#define MQMESSAGE_NEW_DRAW_OBJECT		200
#define MQMESSAGE_NEW_DRAW_MATERIAL		201
#define MQMESSAGE_NEW_DRAW_TEXT			202		// new in Rev4.50
#define MQMESSAGE_DELETE_DRAW_OBJECT	210
#define MQMESSAGE_DELETE_DRAW_MATERIAL	211
#define MQMESSAGE_DELETE_DRAW_TEXT		212		// new in Rev4.50
#define MQMESSAGE_SET_DRAW_PROXY_OBJECT	220
#define MQMESSAGE_GET_UVCNANNEL_ID		230		// new in Rev4.85
#define MQMESSAGE_GET_UVCNANNEL_NAME	231		// new in Rev4.85
#define MQMESSAGE_GET_MAX_UVCNANNEL_NUM	232		// new in Rev4.85
#define MQMESSAGE_GET_UNDO_STATE		300
#define MQMESSAGE_UPDATE_UNDO			301
#define MQMESSAGE_UNDO					302		// new in Rev4.59
#define MQMESSAGE_REDO					303		// new in Rev4.59
#define MQMESSAGE_CLEAR_UNDO			304		// new in Rev4.59
#define MQMESSAGE_SAVE_DOCUMENT			305		// new in Rev4.59
#define MQMESSAGE_SET_UNDO_USED_MEMORY	306		// new in Rev4.60
#define MQMESSAGE_OPEN_DOCUMENT			307		// new in Rev4.71
#define MQMESSAGE_INSERT_DOCUMENT		308		// new in Rev4.71
#define MQMESSAGE_REDRAW_SCENE			400
#define MQMESSAGE_REDRAW_ALL_SCENE		401
#define MQMESSAGE_GET_SCENE_OPTION		410
#define MQMESSAGE_HIT_TEST				411		// new in Rev2.49
#define MQMESSAGE_GET_ENVMAP			420		// new in Rev4.80
#define MQMESSAGE_SET_ENVMAP			421		// new in Rev4.80
#define MQMESSAGE_GET_EDIT_OPTION		500
#define MQMESSAGE_GET_SNAPPED_POS		501
#define MQMESSAGE_GET_RESOURCE_CURSOR	502
#define MQMESSAGE_GET_SETTING_ELEMENT	505		// new in Rev4.00
#define MQMESSAGE_GET_RESOURCE_TEXT		506		// new in Rev4.00
#define MQMESSAGE_GET_SYSTEM_COLOR		507		// new in Rev4.02
#define MQMESSAGE_GET_TEXT_VALUE		508		// new in Rev4.02
#define MQMESSAGE_GET_SCREEN_MOUSE_CURSOR 509   // new in Rev4.30
#define MQMESSAGE_GET_LUT               510     // new in Rev4.40
#define MQMESSAGE_GET_DISPLAY_UNIT      511     // new in Rev4.59
#define MQMESSAGE_GET_LOADABLE_IMAGES   512     // new in Rev4.60
#define MQMESSAGE_SET_MOUSE_CURSOR		603
#define MQMESSAGE_SET_STATUS_STRING		604		// new in Rev2.49
#define MQMESSAGE_SET_TEXT_VALUE		608		// new in Rev4.11
#define MQMESSAGE_SET_SCREEN_MOUSE_CURSOR 609   // new in Rev4.30
#define MQMESSAGE_IMPORT_QUERY_CANCEL	700
#define MQMESSAGE_IMPORT_PROGRESS		701
#define MQMESSAGE_REGISTER_KEYBUTTON	800		// new in Rev4.30

// MQ_ShowFileDialog
#define MQFILE_TYPE_LEFT       0
#define MQFILE_TYPE_RIGHT      1
#define MQFILE_TYPE_UP         2
#define MQFILE_TYPE_DOWN       3
#define MQFILE_TYPE_FRONT      4
#define MQFILE_TYPE_BACK       5

// MQ_GetSystemPath
#define MQFOLDER_ROOT          1
#define MQFOLDER_METASEQ_EXE   2
//#define MQFOLDER_METASEQ_INI   3 // obsolete in Rev4.00
#define MQFOLDER_DATA          4
#define MQFOLDER_PLUGINS       5
#define MQFOLDER_APPDATA       6   // new in Rev4.66

// MQDoc_ClearSelect
#define MQDOC_CLEARSELECT_VERTEX  1
#define MQDOC_CLEARSELECT_LINE    2
#define MQDOC_CLEARSELECT_FACE    4
#define MQDOC_CLEARSELECT_ALL     7

// MQDoc_FindMappingFile
#define MQMAPPING_TEXTURE   1
#define MQMAPPING_ALPHA     2
#define MQMAPPING_BUMP      3
#define MQMAPPING_HLSL      4
#define MQMAPPING_ENVMAP    5   // new inv Rev4.80

// MQDoc_CreateUserData
#define MQUSERDATA_OBJECT	1
#define MQUSERDATA_MATERIAL 2
#define MQUSERDATA_VERTEX   3
#define MQUSERDATA_FACE     4

// MQScene_IntValue/MQScene_FloatValue
#define MQSCENE_GET_CAMERA_POS   		0x101
#define MQSCENE_GET_CAMERA_ANGLE 		0x102
#define MQSCENE_GET_LOOK_AT_POS   		0x103
#define MQSCENE_GET_ROTATION_CENTER		0x104
#define MQSCENE_GET_FOV					0x105
#define MQSCENE_GET_DIRECTIONAL_LIGHT	0x106
#define MQSCENE_GET_AMBIENT_COLOR		0x107
#define MQSCENE_GET_FRONT_Z				0x108
#define MQSCENE_GET_ORTHO				0x109
#define MQSCENE_GET_ZOOM				0x10A // new in Rev4.30
#define MQSCENE_GET_FRONT_CLIP			0x10B // new in Rev4.50
#define MQSCENE_GET_BACK_CLIP			0x10C // new in Rev4.50
#define MQSCENE_SET_CAMERA_POS   		0x201
#define MQSCENE_SET_CAMERA_ANGLE 		0x202
#define MQSCENE_SET_LOOK_AT_POS   		0x203
#define MQSCENE_SET_ROTATION_CENTER		0x204
#define MQSCENE_SET_FOV					0x205
#define MQSCENE_SET_DIRECTIONAL_LIGHT	0x206
#define MQSCENE_SET_AMBIENT_COLOR		0x207
#define MQSCENE_SET_ORTHO				0x209
#define MQSCENE_SET_ZOOM				0x20A // new in Rev4.30
#define MQSCENE_CONVERT_3D_TO_SCREEN	0x300
#define MQSCENE_CONVERT_SCREEN_TO_3D	0x301
#define MQSCENE_ADD_MULTILIGHT			0x400 // new in Rev3.11
#define MQSCENE_DELETE_MULTILIGHT		0x401 // new in Rev3.11
#define MQSCENE_GET_MULTILIGHT_NUMBER	0x402 // new in Rev3.11
#define MQSCENE_SET_MULTILIGHT_INDEX	0x403 // new in Rev3.11
#define MQSCENE_GET_MULTILIGHT_DIR		0x404 // new in Rev3.11
#define MQSCENE_SET_MULTILIGHT_DIR		0x405 // new in Rev3.11
#define MQSCENE_GET_MULTILIGHT_COLOR	0x406 // new in Rev3.11
#define MQSCENE_SET_MULTILIGHT_COLOR	0x407 // new in Rev3.11
#define MQSCENE_GET_BKIMAGE				0x408 // new in Rev4.71
#define MQSCENE_SET_BKIMAGE				0x409 // new in Rev4.71

// MQObj_GetType
#define MQOBJECT_TYPE_NORMAL              0
#define MQOBJECT_TYPE_POINT_LIGHT         1
#define MQOBJECT_TYPE_DIRECTIONAL_LIGHT   2

// MQObj_Freeze
#define MQOBJECT_FREEZE_PATCH    0x00000001
#define MQOBJECT_FREEZE_MIRROR   0x00000002
#define MQOBJECT_FREEZE_LATHE    0x00000004
#define MQOBJECT_FREEZE_ALL      0x7FFFFFFF

// MQObj_GetPatchType, MQObj_SetPatchType
#define MQOBJECT_PATCH_MAX       4
#define MQOBJECT_PATCH_NONE      0
#define MQOBJECT_PATCH_SPLINE1   1
#define MQOBJECT_PATCH_SPLINE2   2
#define MQOBJECT_PATCH_CATMULL   3
#define MQOBJECT_PATCH_OPENSUBDIV   4

// MQObj_GetPatchMeshInterp, MQObj_SetPatchMeshInterp
//#define MQOBJECT_INTERP_NONE            0 // deprecated
#define MQOBJECT_INTERP_EDGE_ONLY       1
#define MQOBJECT_INTERP_EDGE_AND_CORNER 2
//#define MQOBJECT_INTERP_ALWAY_SHARP     3 // deprecated

// MQObj_GetPatchUVInterp, MQObj_SetPatchUVInterp
#define MQOBJECT_UVINTERP_NONE          1
#define MQOBJECT_UVINTERP_CORNERS_ONLY  4
#define MQOBJECT_UVINTERP_CORNERS_PLUS1 2
#define MQOBJECT_UVINTERP_CORNERS_PLUS2 5
#define MQOBJECT_UVINTERP_BOUNDARIES    3
#define MQOBJECT_UVINTERP_ALL           0

// MQObj_GetShading, MQObj_SetShading
#define MQOBJECT_SHADE_MAX       1
#define MQOBJECT_SHADE_FLAT      0
#define MQOBJECT_SHADE_GOURAUD   1

// MQObj_GetMirrorType, MQObj_SetMirrorType
#define MQOBJECT_MIRROR_MAX      2
#define MQOBJECT_MIRROR_NONE     0
#define MQOBJECT_MIRROR_NORMAL   1
#define MQOBJECT_MIRROR_JOIN     2

// MQObj_GetMirrorAxis, MQObj_SetMirrorAxis
#define MQOBJECT_MIRROR_AXIS_X   1
#define MQOBJECT_MIRROR_AXIS_Y   2
#define MQOBJECT_MIRROR_AXIS_Z   4

// MQObj_GetLatheType, MQObj_SetLatheType
#define MQOBJECT_LATHE_MAX       3
#define MQOBJECT_LATHE_NONE      0
#define MQOBJECT_LATHE_FRONT     1
#define MQOBJECT_LATHE_BACK      2
#define MQOBJECT_LATHE_BOTH      3

// MQObj_GetLatheAxis, MQObj_SetLatheAxis
#define MQOBJECT_LATHE_X         0
#define MQOBJECT_LATHE_Y         1
#define MQOBJECT_LATHE_Z         2

// MQObj_GetFaceVertexNormal, MQObj_SetFaceVertexNormal
#define MQOBJECT_NORMAL_NONE         0
#define MQOBJECT_NORMAL_HARD_EDGE    1
#define MQOBJECT_NORMAL_FIX          2

// MQObject::AddRenderFlag/RemoveRenderFlag/AddRenderEraseFlag/RemoveRenderEraseFlag
enum MQOBJECT_RENDER_FLAG {
	MQOBJECT_RENDER_POINT,
	MQOBJECT_RENDER_LINE,
	MQOBJECT_RENDER_FACE,
	MQOBJECT_RENDER_OVERWRITELINE,
	MQOBJECT_RENDER_OVERWRITEFACE,
	MQOBJECT_RENDER_ALPHABLEND,
	MQOBJECT_RENDER_MULTILIGHT,
	MQOBJECT_RENDER_SHADOW,
	MQOBJECT_RENDER_TEXTURE,			// new in Rev4.59
	MQOBJECT_RENDER_VERTEXCOLOR,		// new in Rev4.59
	MQOBJECT_RENDER_VERTEXCOLORPOINT,
	MQOBJECT_RENDER_EDGECOLOR,          // new in Rev4.70
	MQOBJECT_RENDER_SCREEN,
};

// MQMat_GetShader, MQMat_SetShader
#define MQMATERIAL_SHADER_CLASSIC      0
#define MQMATERIAL_SHADER_CONSTANT     1
#define MQMATERIAL_SHADER_LAMBERT      2
#define MQMATERIAL_SHADER_PHONG        3
#define MQMATERIAL_SHADER_BLINN        4
#define MQMATERIAL_SHADER_HLSL         5  // new in Rev4.33

// MQMat_GetVertexColor, MQMat_SetVertexColor
#define MQMATERIAL_VERTEXCOLOR_DISABLE		0
#define MQMATERIAL_VERTEXCOLOR_DIFFUSE		1

// MQMat_GetMappingType, MQMat_SetMappingType
#define MQMATERIAL_PROJECTION_UV			0
#define MQMATERIAL_PROJECTION_FLAT			1
#define MQMATERIAL_PROJECTION_CYLINDER		2
#define MQMATERIAL_PROJECTION_SPHERE		3

// MQMat_GetMappingFilter, MQMat_SetMappingFilter
#define MQMATERIAL_FILTER_NEAREST			0
#define MQMATERIAL_FILTER_LINEAR			1

// MQMat_GetWrapModeU/V, MQMat_SetWrapModeU/V
#define MQMATERIAL_WRAP_REPEAT			0
#define MQMATERIAL_WRAP_MIRROR			1
#define MQMATERIAL_WRAP_CLAMP			2

// MQMaterial::GetShaderParameterValueType
#define MQMATERIAL_SHADER_PARAM_TYPE_NONE  0  // new in Rev4.33
#define MQMATERIAL_SHADER_PARAM_TYPE_BOOL  1  // new in Rev4.33
#define MQMATERIAL_SHADER_PARAM_TYPE_INT   2  // new in Rev4.33
#define MQMATERIAL_SHADER_PARAM_TYPE_FLOAT 3  // new in Rev4.33
#define MQMATERIAL_SHADER_PARAM_TYPE_COLOR 4  // new in Rev4.33
#define MQMATERIAL_SHADER_PARAM_TYPE_STRING 5  // new in Rev4.50

// MQObj_GetIntValue, MQObj_SetIntValue
// MQObj_GetFloatArray, MQObj_SetFloatArray
#define MQOBJ_ID_DEPTH	 				0x101  // Int Value
#define MQOBJ_ID_FOLDING 				0x102  // Int Value
#define MQOBJ_ID_LOCKING				0x103  // Int Value
#define MQOBJ_ID_UNIQUE_ID 				0x104  // Int Value
#define MQOBJ_ID_TYPE	 				0x105  // Int Value : new in Rev3.00
#define MQOBJ_ID_SELECTED				0x106  // Int Value : new in Rev3.10
#define MQOBJ_ID_PATCH_TRIANGLE			0x107  // Int Value : new in Rev3.10
#define MQOBJ_ID_PATCH_SMOOTH_TRIANGLE	0x108  // Int Value : new in Rev4.20
#define MQOBJ_ID_PATCH_MESH_INTERP		0x109  // Int Value : new in Rev4.30
#define MQOBJ_ID_PATCH_UV_INTERP		0x10A  // Int Value : new in Rev4.30
#define MQOBJ_ID_PATCH_LIMIT_SURFACE    0x10B  // Int Value : new in Rev4.51
#define MQOBJ_ID_COLOR	 				0x201  // Float Array
#define MQOBJ_ID_COLOR_VALID			0x201  // Int Value
#define MQOBJ_ID_SCALING 				0x301  // Float Array
#define MQOBJ_ID_ROTATION				0x302  // Float Array
#define MQOBJ_ID_TRANSLATION 			0x303  // Float Array
#define MQOBJ_ID_LOCAL_MATRIX 			0x304  // Float Array
#define MQOBJ_ID_LOCAL_INVERSE_MATRIX 	0x305  // Float Array (get only)
#define MQOBJ_ID_LIGHT_VALUE			0x401  // Float Value : new in Rev3.00
#define MQOBJ_ID_LIGHT_ATTENUATION		0x402  // Int Value   : new in Rev3.00
#define MQOBJ_ID_LIGHT_FALLOFF_END		0x403  // Float Value : new in Rev3.00
#define MQOBJ_ID_LIGHT_FALLOFF_HALF		0x404  // Float Value : new in Rev3.00
#define MQOBJ_ID_LIGHT_FALLOFF_HALF		0x404  // Float Value : new in Rev3.00
#define MQOBJ_ID_ADD_RENDER_FLAG		0x501  // Pointer Array
#define MQOBJ_ID_REMOVE_RENDER_FLAG		0x502  // Pointer Array
#define MQOBJ_ID_ADD_ERASE_FLAG			0x503  // Pointer Array
#define MQOBJ_ID_REMOVE_ERASE_FLAG		0x504  // Pointer Array
#define MQOBJ_ID_MERGE					0x510  // Pointer Array : new in Rev4.64
#define MQOBJ_ID_FREEZE					0x511  // Pointer Array : new in Rev4.64
#define MQOBJ_ID_OPTIMIZE				0x512  // Pointer Array : new in Rev4.64
#define MQOBJ_ID_RESERVE_VERTEX			0x513  // Pointer Array : new in Rev4.64
#define MQOBJ_ID_RESERVE_FACE			0x514  // Pointer Array : new in Rev4.64
#define MQOBJ_ID_NAME					0x515  // Pointer Array : new in Rev4.70
#define MQOBJ_ID_NAME_W					0x516  // Pointer Array : new in Rev4.70
#define MQOBJ_ID_SET_NAME_W				0x517  // Pointer Array : new in Rev4.70
#define MQOBJ_ID_UPDATE_NORMAL			0x518  // Pointer Array : new in Rev4.71
#define MQOBJ_ID_GET_UV_CHANNEL			0x600  // Pointer Array : new in Rev4.85
#define MQOBJ_ID_ACTIVATE_UV_CHANNEL	0x601  // Pointer Array : new in Rev4.85
#define MQOBJ_ID_GET_ACTIVE_UV_CHANNEL	0x602  // Pointer Array : new in Rev4.85
#define MQOBJ_ID_ADD_UV_CHANNEL			0x603  // Pointer Array : new in Rev4.85
#define MQOBJ_ID_DELETE_UV_CHANNEL		0x604  // Pointer Array : new in Rev4.85

// MQMat_GetIntValue, MQMat_SetIntValue, MQMat_SetValueArray
// MQMat_GetFloatArray, MQMat_SetFloatArray, MQMat_GetValueArray
#define MQMAT_ID_SHADER 				0x101  // Int Value
#define MQMAT_ID_VERTEXCOLOR    		0x102  // Int Value
#define MQMAT_ID_UNIQUE_ID 				0x103  // Int Value
#define MQMAT_ID_DOUBLESIDED			0x104  // Int Value : new in Rev3.10
#define MQMAT_ID_SELECTED				0x106  // Int Value : new in Rev3.10
#define MQMAT_ID_NAME					0x107  // Int Value : new in Rev4.70
#define MQMAT_ID_NAME_W					0x108  // Int Value : new in Rev4.70
#define MQMAT_ID_CLONE					0x109  // Int Value : new in Rev4.84b
#define MQMAT_ID_REFLECTION				0x208  // Float Array : new in Rev4.00
#define MQMAT_ID_REFRACTION				0x209  // Float Array : new in Rev4.00
#define MQMAT_ID_AMBIENT_COLOR			0x210  // Float Array : new in Rev4.20
#define MQMAT_ID_SPECULAR_COLOR			0x211  // Float Array : new in Rev4.20
#define MQMAT_ID_EMISSION_COLOR			0x212  // Float Array : new in Rev4.20
#define MQMAT_ID_MAPPROJ 				0x301  // Int Value
#define MQMAT_ID_MAPPROJ_POSITION 		0x302  // Float Array
#define MQMAT_ID_MAPPROJ_SCALING		0x303  // Float Array
#define MQMAT_ID_MAPPROJ_ANGLE 			0x304  // Float Array
#define MQMAT_ID_MAPWRAPU 				0x305  // Int Value : new in Rev4.70
#define MQMAT_ID_MAPWRAPV 				0x306  // Int Value : new in Rev4.70
#define MQMAT_ID_MAPFILTER				0x307  // Int Value : new in Rev4.70
#define MQMAT_ID_TEXTURE_NAME_W			0x308  // Int Value : new in Rev4.70
#define MQMAT_ID_ALPHA_NAME_W			0x309  // Int Value : new in Rev4.70
#define MQMAT_ID_BUMP_NAME_W			0x310  // Int Value : new in Rev4.70
#define MQMAT_ID_TEXTURE_UVCHANNEL		0x311  // Int Value : new in Rev4.85
#define MQMAT_ID_ALPHA_UVCHANNEL		0x312  // Int Value : new in Rev4.85
#define MQMAT_ID_BUMP_UVCHANNEL			0x313  // Int Value : new in Rev4.85
#define MQMAT_ID_SHADER_NAME			0x401  // Value Array : new in Rev4.33
#define MQMAT_ID_SHADER_PARAM_NUM		0x402  // Value Array : new in Rev4.33
#define MQMAT_ID_SHADER_PARAM_NAME		0x403  // Value Array : new in Rev4.33
#define MQMAT_ID_SHADER_PARAM_VALUE_TYPE  0x404  // Value Array : new in Rev4.33
#define MQMAT_ID_SHADER_PARAM_ARRAY_SIZE  0x405  // Value Array : new in Rev4.33
#define MQMAT_ID_SHADER_PARAM_INT_VALUE   0x406  // Value Array : new in Rev4.33
#define MQMAT_ID_SHADER_PARAM_FLOAT_VALUE 0x407  // Value Array : new in Rev4.33
#define MQMAT_ID_SHADER_PARAM_COLOR_VALUE 0x408  // Value Array : new in Rev4.33
#define MQMAT_ID_SHADER_MAP_NUM			0x409  // Value Array : new in Rev4.33
#define MQMAT_ID_SHADER_MAP_NAME		0x40A  // Value Array : new in Rev4.33
#define MQMAT_ID_SHADER_MAP_FILENAME	0x40B  // Value Array : new in Rev4.33
#define MQMAT_ID_SHADER_MAP_FILENAME_W	0x40C  // Value Array : new in Rev4.33
#define MQMAT_ID_SHADER_OPTION			0x40D  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_PARAM_OPTION	0x40E  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_MAP_OPTION		0x40F  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_MAP_PARAM_NUM		0x410  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_MAP_PARAM_NAME		0x411  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_MAP_PARAM_VALUE_TYPE  0x412  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_MAP_PARAM_ARRAY_SIZE  0x413  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_MAP_PARAM_INT_VALUE   0x414  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_MAP_PARAM_FLOAT_VALUE 0x415  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_MAP_PARAM_COLOR_VALUE 0x416  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_MAP_PARAM_OPTION      0x417  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_MAP_CONNECT_NODE_ID   0x418  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_MAP_CONNECT_NODE      0x419  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_OUTPUT_NUM		0x420  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_OUTPUT_NAME		0x421  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_OUTPUT_OPTION	0x422  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_OUTPUT_VALUE_TYPE  0x423  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_PARAM_STRING_VALUE 0x424  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_MAP_PARAM_STRING_VALUE 0x425  // Value Array : new in Rev4.50
#define MQMAT_ID_SHADER_MAP_UV_CHANNEL  0x426  // Int Value : new in Rev4.85
#define MQMAT_ID_SUBSHADER_CREATE		0x500  // Value Array : new in Rev4.50
#define MQMAT_ID_SUBSHADER_DELETE		0x501  // Value Array : new in Rev4.50
#define MQMAT_ID_SUBSHADER				0x502  // Value Array : new in Rev4.50
#define MQMAT_ID_SUBSHADER_NUM			0x503  // Value Array : new in Rev4.50
#define MQMAT_ID_SUBSHADER_ID			0x504  // Value Array : new in Rev4.50

// MQMatrix_FloatValue
#define MQMATRIX_GET_SCALING			0x101
#define MQMATRIX_GET_ROTATION			0x102
#define MQMATRIX_GET_TRANSLATION		0x103
#define MQMATRIX_GET_INVERSE_TRANSFORM	0x105
#define MQMATRIX_SET_TRANSFORM			0x204
#define MQMATRIX_SET_INVERSE_TRANSFORM	0x205

// MQXmlElem_Value
#define MQXMLELEM_ADD_CHILD_ELEMENT		0x101
#define MQXMLELEM_REMOVE_CHILD_ELEMENT	0x102
#define MQXMLELEM_FIRST_CHILD_ELEMENT	0x201
#define MQXMLELEM_NEXT_CHILD_ELEMENT 	0x202
#define MQXMLELEM_GET_PARENT_ELEMENT 	0x203
#define MQXMLELEM_GET_NAME				0x301
#define MQXMLELEM_GET_TEXT		 		0x302
#define MQXMLELEM_GET_ATTRIBUTE			0x303
#define MQXMLELEM_SET_TEXT				0x402
#define MQXMLELEM_SET_ATTRIBUTE			0x403

// MQXmlDoc_Value
#define MQXMLDOC_CREATE					0x001
#define MQXMLDOC_DELETE					0x002
#define MQXMLDOC_LOAD					0x003
#define MQXMLDOC_SAVE					0x004
#define MQXMLDOC_CREATE_ROOT_ELEMENT	0x101
#define MQXMLDOC_GET_ROOT_ELEMENT		0x102

// MQWidget_Value
#define MQWIDGET_EXECUTE				0x001
#define MQWIDGET_FIND					0x100
#define MQWIDGET_CREATE					0x101
#define MQWIDGET_DELETE					0x102
#define MQWIDGET_ADD_CHILD				0x201
#define MQWIDGET_REMOVE_CHILD			0x202
#define MQWIDGET_ADD_CHILD_WINDOW		0x203
#define MQWIDGET_REMOVE_CHILD_WINDOW	0x204
#define MQWIDGET_GET					0x301
#define MQWIDGET_SET					0x302
#define MQWIDGET_EDIT					0x303
#define MQWIDGET_ADD_EVENT				0x304
#define MQWIDGET_REMOVE_EVENT			0x305

enum MQDISPLAYUNIT {
	MQDISPLAYUNIT_DISABLED = -1,
	MQDISPLAYUNIT_NONE = 0,
	MQDISPLAYUNIT_MM,
	MQDISPLAYUNIT_CM,
	MQDISPLAYUNIT_M,
	MQDISPLAYUNIT_INCH,
	MQDISPLAYUNIT_FEET,
};



typedef BYTE MQBool;

//
// struct MQPoint
//
struct MQPoint
{
public:
	float x,y,z;

	// constructor
	MQPoint() { }
	MQPoint(float nx, float ny, float nz) {x=nx; y=ny; z=nz;}

	// operator
	MQPoint& operator = (const MQPoint& p)
		{x=p.x; y=p.y; z=p.z; return *this;}
	MQPoint& operator = (const float& s)
		{x=y=z=s; return *this;}
	MQPoint& operator += (const MQPoint& p)
		{x+=p.x; y+=p.y; z+=p.z; return *this;}
	MQPoint& operator += (const float& s)
		{x+=s; y+=s; z+=s; return *this;}
	MQPoint& operator -= (const MQPoint& p)
		{x-=p.x; y-=p.y; z-=p.z; return *this;}
	MQPoint& operator -= (const float& s)
		{x-=s; y-=s; z-=s; return *this;}
	MQPoint& operator *= (const MQPoint& p)
		{x*=p.x; y*=p.y; z*=p.z; return *this;}
	MQPoint& operator *= (float s)
		{x*=s; y*=s; z*=s; return *this;}
	MQPoint& operator /= (float s)
		{x/=s; y/=s; z/=s; return *this;}
	MQPoint operator + () const {return *this;}
	MQPoint operator - () const {return MQPoint(-x,-y,-z);}
	friend MQPoint operator + (const MQPoint& p1, const MQPoint& p2)
		{return MQPoint(p1.x+p2.x, p1.y+p2.y, p1.z+p2.z);}
	friend MQPoint operator + (const MQPoint& p, const float& s)
		{return MQPoint(p.x+s, p.y+s, p.z+s);}
	friend MQPoint operator + (const float& s, const MQPoint& p)
		{return MQPoint(p.x+s, p.y+s, p.z+s);}
	friend MQPoint operator - (const MQPoint& p1, const MQPoint& p2)
		{return MQPoint(p1.x-p2.x, p1.y-p2.y, p1.z-p2.z);}
	friend MQPoint operator - (const MQPoint& p, const float& s)
		{return MQPoint(p.x-s, p.y-s, p.z-s);}
	friend MQPoint operator - (const float& s, const MQPoint& p)
		{return MQPoint(s-p.x, s-p.y, s-p.z);}
	friend MQPoint operator * (const MQPoint& p1, const MQPoint& p2)
		{return MQPoint(p1.x*p2.x, p1.y*p2.y, p1.z*p2.z);}
	friend MQPoint operator * (const MQPoint& p, const float& s)
		{return MQPoint(p.x*s, p.y*s, p.z*s);}
	friend MQPoint operator * (const float& s, const MQPoint& p)
		{return MQPoint(p.x*s, p.y*s, p.z*s);}
	friend MQPoint operator / (const MQPoint& p, const float& s)
		{return MQPoint(p.x/s, p.y/s, p.z/s);}
	friend MQPoint operator / (const MQPoint& p, const MQPoint& s)
		{return MQPoint(p.x/s.x, p.y/s.y, p.z/s.z);}
	friend bool operator == (const MQPoint& p1, const MQPoint& p2)
		{return (p1.x==p2.x && p1.y==p2.y && p1.z==p2.z);}
	friend bool operator != (const MQPoint& p1, const MQPoint& p2)
		{return (p1.x!=p2.x || p1.y!=p2.y || p1.z!=p2.z);}

	float& index(int i)				{ return *(&x + i); }
	const float& index(int i) const	{ return *(&x + i); }

	void zero() { x=y=z=0.0f; }
	void one() { x=y=z=1.0f; }
	float norm() const { return x*x + y*y + z*z; }
	float abs() const { return (float)sqrt(norm()); }
	void normalize() {
		float a = abs();
		if(a > 0.0f) *this /= a;
		else zero();
	}
	float min() const { return (x < y) ? (x < z ? x : z) : (y < z ? y : z); }
	float max() const { return (x > y) ? (x > z ? x : z) : (y > z ? y : z); }
};


//
// struct MQPoint2
//
struct MQPoint2
{
public:
	float x,y;

	// constructor
	MQPoint2() { }
	MQPoint2(float nx, float ny) {x=nx; y=ny;}

	// operator
	MQPoint2& operator = (const MQPoint2& p)	{x=p.x; y=p.y; return *this;}
	MQPoint2& operator = (const float& s)		{x=y=s; return *this;}
	MQPoint2& operator += (const MQPoint2& p)	{x+=p.x; y+=p.y; return *this;}
	MQPoint2& operator += (const float& s)		{x+=s; y+=s; return *this;}
	MQPoint2& operator -= (const MQPoint2& p)	{x-=p.x; y-=p.y; return *this;}
	MQPoint2& operator -= (const float& s)		{x-=s; y-=s; return *this;}
	MQPoint2& operator *= (const MQPoint2& p)	{x*=p.x; y*=p.y; return *this;}
	MQPoint2& operator *= (float s)				{x*=s; y*=s; return *this;}
	MQPoint2& operator /= (float s)				{x/=s; y/=s; return *this;}
	MQPoint2 operator + () const {return *this;}
	MQPoint2 operator - () const {return MQPoint2(-x,-y);}
	friend MQPoint2 operator + (const MQPoint2& p1, const MQPoint2& p2)	
		{return MQPoint2(p1.x+p2.x, p1.y+p2.y);}
	friend MQPoint2 operator + (const MQPoint2& p, const float& s)
		{return MQPoint2(p.x+s, p.y+s);}
	friend MQPoint2 operator + (const float& s, const MQPoint2& p)
		{return MQPoint2(p.x+s, p.y+s);}
	friend MQPoint2 operator - (const MQPoint2& p1, const MQPoint2& p2)
		{return MQPoint2(p1.x-p2.x, p1.y-p2.y);}
	friend MQPoint2 operator - (const MQPoint2& p, const float& s)
		{return MQPoint2(p.x-s, p.y-s);}
	friend MQPoint2 operator - (const float& s, const MQPoint2& p)
		{return MQPoint2(s-p.x, s-p.y);}
	friend MQPoint2 operator * (const MQPoint2& p1, const MQPoint2& p2)
		{return MQPoint2(p1.x*p2.x, p1.y*p2.y);}
	friend MQPoint2 operator * (const MQPoint2& p, const float& s)
		{return MQPoint2(p.x*s, p.y*s);}
	friend MQPoint2 operator * (const float& s, const MQPoint2& p)
		{return MQPoint2(p.x*s, p.y*s);}
	friend MQPoint2 operator / (const MQPoint2& p, const float& s)
		{return MQPoint2(p.x/s, p.y/s);}
	friend bool operator == (const MQPoint2& p1, const MQPoint2& p2)
		{return (p1.x==p2.x && p1.y==p2.y);}
	friend bool operator != (const MQPoint2& p1, const MQPoint2& p2)
		{return (p1.x!=p2.x || p1.y!=p2.y);}

	float& index(int i)				{ return *(&x + i); }
	const float& index(int i) const	{ return *(&x + i); }

	void zero() { x=y=0.0f; }
	void one() { x=y=1.0f; }
	float norm() const { return x*x + y*y; }
	float abs() const { return (float)sqrt(norm()); }
	void normalize() {
		float a = abs();
		if(a > 0.0f) *this /= a;
		else zero();
	}
	float min() const { return (x < y) ? x : y; }
	float max() const { return (x > y) ? x : y; }
};


//
// struct MQColor
//
struct MQColor
{
	float r,g,b;
public:
	MQColor() {}
	MQColor(float value) { r=g=b=value; }
	MQColor(float nr, float ng, float nb) { r=nr; g=ng; b=nb; }

	MQColor& operator += (const MQColor& c) {r+=c.r; g+=c.g; b+=c.b; return *this;}
	MQColor& operator -= (const MQColor& c) {r-=c.r; g-=c.g; b-=c.b; return *this;}
	MQColor& operator *= (const MQColor& c) {r*=c.r; g*=c.g; b*=c.b; return *this;}
	MQColor& operator *= (float s) {r*=s; g*=s; b*=s; return *this;}
	MQColor& operator /= (float s) {r/=s; g/=s; b/=s; return *this;}
	friend MQColor operator + (const MQColor& c1, const MQColor& c2)
		{return MQColor(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b);}
	friend MQColor operator + (const MQColor& c, const float& s)
		{return MQColor(c.r+s, c.g+s, c.b+s);}
	friend MQColor operator + (const float& s, const MQColor& c)
		{return MQColor(c.r+s, c.g+s, c.b+s);}
	friend MQColor operator - (const MQColor& c1, const MQColor& c2)
		{return MQColor(c1.r-c2.r, c1.g-c2.g, c1.b-c2.b);}
	friend MQColor operator - (const MQColor& c, const float& s)
		{return MQColor(c.r-s, c.g-s, c.b-s);}
	friend MQColor operator - (const float& s, const MQColor& c)
		{return MQColor(s-c.r, s-c.g, s-c.b);}
	friend MQColor operator * (const MQColor& c1, const MQColor& c2)
		{return MQColor(c1.r*c2.r, c1.g*c2.g, c1.b*c2.b);}
	friend MQColor operator * (const MQColor& c, const float& s)
		{return MQColor(c.r*s, c.g*s, c.b*s);}
	friend MQColor operator * (const float& s, const MQColor& c)
		{return MQColor(c.r*s, c.g*s, c.b*s);}
	friend bool operator == (const MQColor& c1, const MQColor& c2)
		{return (c1.r==c2.r && c1.g==c2.g && c1.b==c2.b);}
	friend bool operator != (const MQColor& c1, const MQColor& c2)
		{return (c1.r!=c2.r || c1.g!=c2.g || c1.b!=c2.b);}

	float min() const { return (r < g) ? (r < b ? r : b) : (g < b ? g : b); }
	float max() const { return (r > g) ? (r > b ? r : b) : (g > b ? g : b); }
};


//
// struct MQColorRGBA
//
struct MQColorRGBA
{
	float r,g,b,a;
public:
	MQColorRGBA() {}
	MQColorRGBA(float value) { r=g=b=a=value; }
	MQColorRGBA(float nr, float ng, float nb, float na) { r=nr; g=ng; b=nb; a=na; }

	friend MQColorRGBA operator + (const MQColorRGBA& c1, const MQColorRGBA& c2)
		{return MQColorRGBA(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b, c1.a+c2.a);}
	friend MQColorRGBA operator + (const MQColorRGBA& c, const float& s)
		{return MQColorRGBA(c.r+s, c.g+s, c.b+s, c.a+s);}
	friend MQColorRGBA operator + (const float& s, const MQColorRGBA& c)
		{return MQColorRGBA(c.r+s, c.g+s, c.b+s, c.a+s);}
	friend MQColorRGBA operator - (const MQColorRGBA& c1, const MQColorRGBA& c2)
		{return MQColorRGBA(c1.r-c2.r, c1.g-c2.g, c1.b-c2.b, c1.a-c2.a);}
	friend MQColorRGBA operator - (const MQColorRGBA& c, const float& s)
		{return MQColorRGBA(c.r-s, c.g-s, c.b-s, c.a-s);}
	friend MQColorRGBA operator - (const float& s, const MQColorRGBA& c)
		{return MQColorRGBA(s-c.r, s-c.g, s-c.b, s-c.a);}
	friend MQColorRGBA operator * (const MQColorRGBA& c1, const MQColorRGBA& c2)
		{return MQColorRGBA(c1.r*c2.r, c1.g*c2.g, c1.b*c2.b, c1.a*c2.a);}
	friend MQColorRGBA operator * (const MQColorRGBA& c, const float& s)
		{return MQColorRGBA(c.r*s, c.g*s, c.b*s, c.a*s);}
	friend MQColorRGBA operator * (const float& s, const MQColorRGBA& c)
		{return MQColorRGBA(c.r*s, c.g*s, c.b*s, c.a*s);}
	friend bool operator == (const MQColorRGBA& c1, const MQColorRGBA& c2)
		{return (c1.r==c2.r && c1.g==c2.g && c1.b==c2.b && c1.a==c2.a);}
	friend bool operator != (const MQColorRGBA& c1, const MQColorRGBA& c2)
		{return (c1.r!=c2.r || c1.g!=c2.g || c1.b!=c2.b || c1.a!=c2.a);}
};


//
// struct MQCoordinate
//
struct MQCoordinate
{
	float u,v;
public:
	MQCoordinate() {}
	MQCoordinate(float nu, float nv) { u=nu; v=nv; }

	MQCoordinate& operator += (const MQCoordinate& p)
		{u+=p.u; v+=p.v; return *this;}
	MQCoordinate& operator += (const float& s)
		{u+=s; v+=s; return *this;}
	MQCoordinate& operator -= (const MQCoordinate& p)
		{u-=p.u; v-=p.v; return *this;}
	MQCoordinate& operator -= (const float& s)
		{u-=s; v-=s; return *this;}
	MQCoordinate& operator *= (const MQCoordinate& p)
		{u*=p.u; v*=p.v; return *this;}
	MQCoordinate& operator *= (float s)
		{u*=s; v*=s; return *this;}
	MQCoordinate& operator /= (float s)
		{u/=s; v/=s; return *this;}
	MQCoordinate operator + () const {return *this;}
	MQCoordinate operator - () const {return MQCoordinate(-u,-v);}
	friend MQCoordinate operator + (const MQCoordinate& p1, const MQCoordinate& p2)
		{return MQCoordinate(p1.u+p2.u, p1.v+p2.v);}
	friend MQCoordinate operator + (const MQCoordinate& p, const float& s)
		{return MQCoordinate(p.u+s, p.v+s);}
	friend MQCoordinate operator + (const float& s, const MQCoordinate& p)
		{return MQCoordinate(p.u+s, p.v+s);}
	friend MQCoordinate operator - (const MQCoordinate& p1, const MQCoordinate& p2)
		{return MQCoordinate(p1.u-p2.u, p1.v-p2.v);}
	friend MQCoordinate operator - (const MQCoordinate& p, const float& s)
		{return MQCoordinate(p.u-s, p.v-s);}
	friend MQCoordinate operator - (const float& s, const MQCoordinate& p)
		{return MQCoordinate(s-p.u, s-p.v);}
	friend MQCoordinate operator * (const MQCoordinate& p1, const MQCoordinate& p2)
		{return MQCoordinate(p1.u*p2.u, p1.v*p2.v);}
	friend MQCoordinate operator * (const MQCoordinate& p, const float& s)
		{return MQCoordinate(p.u*s, p.v*s);}
	friend MQCoordinate operator * (const float& s, const MQCoordinate& p)
		{return MQCoordinate(p.u*s, p.v*s);}
	friend MQCoordinate operator / (const MQCoordinate& p, const float& s)
		{return MQCoordinate(p.u/s, p.v/s);}
	friend MQCoordinate operator / (const MQCoordinate& p1, const MQCoordinate& p2)
		{return MQCoordinate(p1.u/p2.u, p1.v/p2.v);}
	friend bool operator == (const MQCoordinate& p1, const MQCoordinate& p2)
		{return (p1.u==p2.u && p1.v==p2.v);}
	friend bool operator != (const MQCoordinate& p1, const MQCoordinate& p2)
		{return (p1.u!=p2.u || p1.v!=p2.v);}

	void zero() { u=v=0.0f; }
	void one() { u=v=1.0f; }
};


//
// struct MQAngle
//
class MQMatrix;
struct MQAngle
{
	float head;
	union {
		float pich;
		float pitch;
	};
	float bank;

	MQAngle() {}
	MQAngle(float h, float p, float b) { head=h; pich=p; bank=b; }

	MQMatrix GetRotationMatrix() const;

	friend bool operator == (const MQAngle& p1, const MQAngle& p2)
		{return (p1.head==p2.head && p1.pich==p2.pich && p1.bank==p2.bank);}
	friend bool operator != (const MQAngle& p1, const MQAngle& p2)
		{return (p1.head!=p2.head || p1.pich!=p2.pich || p1.bank!=p2.bank);}
};


//
// class MQMatrix
//
class MQMatrix
{
public:
	union {
		float t[16];
		float d[4][4];
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
	};

	// operator
	friend MQMatrix operator + (const MQMatrix& m1, const MQMatrix& m2)
	{
		MQMatrix m0;
		for(int i=0; i<16; i++) m0.t[i] = m1.t[i] + m2.t[i];
		return m0;
	}
	friend MQMatrix operator - (const MQMatrix& m1, const MQMatrix& m2)
	{
		MQMatrix m0;
		for(int i=0; i<16; i++) m0.t[i] = m1.t[i] - m2.t[i];
		return m0;
	}
	friend MQMatrix operator * (const MQMatrix& m1, const MQMatrix& m2)
	{
		MQMatrix m0;
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
				m0.d[i][j] =
					m1.d[i][0]*m2.d[0][j] + m1.d[i][1]*m2.d[1][j] +
					m1.d[i][2]*m2.d[2][j] + m1.d[i][3]*m2.d[3][j];
		return m0;
	}
	friend MQPoint operator * (const MQPoint& qp, const MQMatrix& m)
	{
		return MQPoint(
			qp.x*m._11 + qp.y*m._21 + qp.z*m._31 + m._41,
			qp.x*m._12 + qp.y*m._22 + qp.z*m._32 + m._42,
			qp.x*m._13 + qp.y*m._23 + qp.z*m._33 + m._43 );
	}
	MQMatrix& operator *= (const MQMatrix mat) { *this = (*this * mat); return *this; }
	float& operator() (int i, int j) { return d[i][j]; }
	const float& operator() (int i, int j) const { return d[i][j]; }

	MQMatrix() {}
	MQMatrix(const float *value){
		for (int i=0; i<16; i++)
			t[i] = value[i];
	}

	void Identify(void)
	{
		for (int i=0; i<4; i++){
			for (int j=0; j<4; j++){
				d[i][j] = (i == j) ? 1.0f : 0.0f;
			}
		}
	}
	bool IsIdentity(void) const
	{
		return (
			_11 == 1.0f && _12 == 0.0f && _13 == 0.0f && _14 == 0.0f &&
			_21 == 0.0f && _22 == 1.0f && _23 == 0.0f && _24 == 0.0f &&
			_31 == 0.0f && _32 == 0.0f && _33 == 1.0f && _34 == 0.0f &&
			_41 == 0.0f && _42 == 0.0f && _43 == 0.0f && _44 == 1.0f);
	}
	bool IsIdentity3(void) const
	{
		return (
			_11 == 1.0f && _12 == 0.0f && _13 == 0.0f &&
			_21 == 0.0f && _22 == 1.0f && _23 == 0.0f &&
			_31 == 0.0f && _32 == 0.0f && _33 == 1.0f);
	}
	MQPoint Mult3(const MQPoint& p) const
	{
		return MQPoint(
			p.x*_11 + p.y*_21 + p.z*_31,
			p.x*_12 + p.y*_22 + p.z*_32,
			p.x*_13 + p.y*_23 + p.z*_33 );
	}
	void Transpose3(void)
	{
		float v12 = _12;
		float v13 = _13;
		float v21 = _21;
		float v23 = _23;
		float v31 = _31;
		float v32 = _32;
		_12 = v21;
		_13 = v31;
		_21 = v12;
		_23 = v32;
		_31 = v13;
		_32 = v23;
	}
	MQMatrix GetTranspose3() const
	{
		MQMatrix mtx;
		mtx._11 = _11; mtx._12 = _21; mtx._13 = _31; mtx._14 = _14;
		mtx._21 = _12; mtx._22 = _22; mtx._23 = _32; mtx._24 = _24;
		mtx._31 = _13; mtx._32 = _23; mtx._33 = _33; mtx._34 = _34;
		mtx._41 = _41; mtx._42 = _42; mtx._43 = _43; mtx._44 = _44;
		return mtx;
	}
	bool Inverse(MQMatrix& inv_mtx) const;
	MQPoint GetRow3(int r) const
	{
		return MQPoint(d[r][0], d[r][1], d[r][2]);
	}
	MQPoint GetColumn3(int c) const
	{
		return MQPoint(d[0][c], d[1][c], d[2][c]);
	}
	void SetRow3(int r, const MQPoint& p)
	{
		d[r][0] = p.x;
		d[r][1] = p.y;
		d[r][2] = p.z;
	}
	void SetColumn3(int c, const MQPoint& p)
	{
		d[0][c] = p.x;
		d[1][c] = p.y;
		d[2][c] = p.z;
	}

	MQPoint GetScaling() const;
	MQAngle GetRotation() const;
	MQPoint GetTranslation() const;
	void SetTransform(const MQPoint *scaling, const MQAngle *rotation, const MQPoint *trans);
	void SetTransform(const MQPoint& scaling, const MQAngle& rotation, const MQPoint& trans);
	void SetInverseTransform(const MQPoint *scaling, const MQAngle *rotation, const MQPoint *trans);
	void SetInverseTransform(const MQPoint& scaling, const MQAngle& rotation, const MQPoint& trans);
};


struct MQFileDialogCallbackParam {
	int dialog_id;
	int parent_frame_id;
};

//
// struct MQFileDialogInfo
//
struct MQFileDialogInfo {
	enum HAND_TYPE {
		HAND_LEFT = 0,
		HAND_RIGHT = 1,
	};
	enum HIDDEN_FLAG_MASK {
		HIDDEN_SCALE		= 0x0001,
		HIDDEN_AXIS			= 0x0002,
		HIDDEN_INVERT_FACE	= 0x0004,
	};

	DWORD dwSize;
	DWORD hidden_flag;
	float scale;
	const char *softname;
	int axis_x;
	int axis_y;
	int axis_z;
	BOOL invert_face;	// Added in Rev4.00
	HAND_TYPE hand_type;		// Added in Rev4.00 ([out] 0:left, 1:right)
	void (*dialog_callback)(bool init, MQFileDialogCallbackParam *param, void *ptr);
	void *dialog_callback_ptr;
	BOOL background;	// Added in Rev4.20
	void *option_args;	// Added in Rev4.20

};


//
// struct MQUserDataInfo
//
struct MQUserDataInfo {
	DWORD dwSize;
	DWORD productID;
	DWORD pluginID;
	char identifier[16];
	int userdata_type;
	int bytes_per_element;
	bool create;

	MQUserDataInfo(){
		memset(this, 0, sizeof(MQUserDataInfo));
		dwSize = sizeof(MQUserDataInfo);
	}
};

//
// struct MQSendMessageInfo
//
struct MQSendMessageInfo {
	DWORD Product;
	DWORD ID;
	int index;
	void *option;
#if __APPLE__
	void *plugin;
#endif

	MQSendMessageInfo(){
		Product = 0;
		ID = 0;
		index = 0;
		option = NULL;
#if __APPLE__
		plugin = NULL;
#endif
	}
};


//
// struct MQSelectVertex
//
struct MQSelectVertex
{
	int object; // index of object
	int vertex; // index of vertex

	MQSelectVertex() {}
	MQSelectVertex(int i, int j) { object=i; vertex=j; }
	friend bool operator == (const MQSelectVertex& l1, const MQSelectVertex& l2)
		{return (l1.object==l2.object && l1.vertex==l2.vertex);}
	friend bool operator != (const MQSelectVertex& l1, const MQSelectVertex& l2)
		{return (l1.object!=l2.object || l1.vertex!=l2.vertex);}
};


//
// struct MQSelectLine
//
struct MQSelectLine
{
	int object; // index of object
	int face;   // index of face
	int line;   // index of line

	MQSelectLine() {}
	MQSelectLine(int i, int j, int k) { object=i; face=j; line=k; }
	friend bool operator == (const MQSelectLine& l1, const MQSelectLine& l2)
		{return (l1.object==l2.object && l1.face==l2.face && l1.line==l2.line);}
	friend bool operator != (const MQSelectLine& l1, const MQSelectLine& l2)
		{return (l1.object!=l2.object || l1.face!=l2.face || l1.line!=l2.line);}
};


//
// struct MQSelectFace
//
struct MQSelectFace
{
	int object; // index of object
	int face;   // index of face

	MQSelectFace() {}
	MQSelectFace(int i, int j) { object=i; face=j; }
	friend bool operator == (const MQSelectFace& l1, const MQSelectFace& l2)
		{return (l1.object==l2.object && l1.face==l2.face);}
	friend bool operator != (const MQSelectFace& l1, const MQSelectFace& l2)
		{return (l1.object!=l2.object || l1.face!=l2.face);}
};



class MQCDocument;
class MQCScene;
class MQCObject;
class MQCMaterial;
class MQCShaderNode;
class MQCXmlElement;
class MQCXmlDocument;

typedef MQCDocument *MQDocument;
typedef MQCScene *MQScene;
typedef MQCObject *MQObject;
typedef MQCMaterial *MQMaterial;
typedef MQCShaderNode *MQShaderNode;
typedef MQCXmlElement *MQXmlElement;
typedef MQCXmlDocument *MQXmlDocument;


typedef BOOL (MQAPICALL *MQStationCallbackProc)(MQDocument doc, void *option);


#ifndef MQPLUGIN_EXPORTS

//
// plugin interface
//
MQPLUGIN_EXPORT DWORD MQCheckVersion(DWORD exe_version);
MQPLUGIN_EXPORT BOOL MQInit(const char *exe_name);
MQPLUGIN_EXPORT const char *MQGetPlugInName(void);
MQPLUGIN_EXPORT void MQGetPlugInID(DWORD *Product, DWORD *ID);
MQPLUGIN_EXPORT int MQGetPlugInType(void);
MQPLUGIN_EXPORT const char *MQEnumString(int index);
MQPLUGIN_EXPORT const wchar_t *MQEnumStringW(int index);
MQPLUGIN_EXPORT const char *MQEnumFileType(int index);
MQPLUGIN_EXPORT const char *MQEnumFileExt(int index);
MQPLUGIN_EXPORT BOOL MQExportFile(int index, const char *filename, MQDocument doc);
MQPLUGIN_EXPORT BOOL MQImportFile(int index, const char *filename, MQDocument doc);
MQPLUGIN_EXPORT BOOL MQCreate(int index, MQDocument doc);
MQPLUGIN_EXPORT BOOL MQModifyObject(int index, MQDocument doc);
MQPLUGIN_EXPORT BOOL MQModifySelect(int index, MQDocument doc);
MQPLUGIN_EXPORT BOOL MQOnEvent(MQDocument doc, int event_type, void *option);

//
// global function
//
#ifdef _WIN32
__declspec(deprecated) extern HWND (MQAPICALL *MQ_GetWindowHandle)(void);
#endif
extern MQObject (MQAPICALL *MQ_CreateObject)(void);
extern MQMaterial (MQAPICALL *MQ_CreateMaterial)(void);
extern void (MQAPICALL *MQ_ShowFileDialog)(const char *title, MQFileDialogInfo *info);
extern void (MQAPICALL *MQ_ImportAxis)(MQFileDialogInfo *info, MQPoint *pts, int pts_count);
extern void (MQAPICALL *MQ_ExportAxis)(MQFileDialogInfo *info, MQPoint *pts, int pts_count);
extern BOOL (MQAPICALL *MQ_LoadImage)(const char *filename, LPVOID *header, LPVOID *buffer, DWORD reserved);
extern BOOL (MQAPICALL *MQ_LoadImageW)(const wchar_t *filename, LPVOID *header, LPVOID *buffer, DWORD reserved);
extern BOOL (MQAPICALL *MQ_GetSystemPath)(char *buffer, int type);
extern BOOL (MQAPICALL *MQ_GetSystemPathW)(wchar_t *buffer, int type);
extern void (MQAPICALL *MQ_RefreshView)(void *reserved);
#if __APPLE__
extern void (MQAPICALL *MQ_StationCallback)(MQStationCallbackProc proc, void *plugin, void *option);
#else
extern void (MQAPICALL *MQ_StationCallback)(MQStationCallbackProc proc, void *option);
#endif
extern BOOL (MQAPICALL *MQ_SendMessage)(int message_type, MQSendMessageInfo *info);


//
// class MQDocument
//
extern int  (MQAPICALL *MQDoc_GetObjectCount)(MQDocument doc);
extern MQObject (MQAPICALL *MQDoc_GetObject)(MQDocument doc, int index);
extern MQObject (MQAPICALL *MQDoc_GetObjectFromUniqueID)(MQDocument doc, int id);
extern int  (MQAPICALL *MQDoc_GetCurrentObjectIndex)(MQDocument doc);
extern void (MQAPICALL *MQDoc_SetCurrentObjectIndex)(MQDocument doc, int index);
extern int  (MQAPICALL *MQDoc_AddObject)(MQDocument doc, MQObject obj);
extern void (MQAPICALL *MQDoc_DeleteObject)(MQDocument doc, int index);
extern int  (MQAPICALL *MQDoc_GetObjectIndex)(MQDocument doc, MQObject obj);
extern void (MQAPICALL *MQDoc_GetUnusedObjectName)(MQDocument doc, char *buffer, int buffer_size, const char *base_name);
extern void (MQAPICALL *MQDoc_GetUnusedObjectNameW)(MQDocument doc, wchar_t *buffer, int buffer_size, const wchar_t *base_name);
extern int  (MQAPICALL *MQDoc_GetMaterialCount)(MQDocument doc);
extern MQMaterial (MQAPICALL *MQDoc_GetMaterial)(MQDocument doc, int index);
extern MQMaterial (MQAPICALL *MQDoc_GetMaterialFromUniqueID)(MQDocument doc, int id);
extern int  (MQAPICALL *MQDoc_GetCurrentMaterialIndex)(MQDocument doc);
extern void (MQAPICALL *MQDoc_SetCurrentMaterialIndex)(MQDocument doc, int index);
extern int  (MQAPICALL *MQDoc_AddMaterial)(MQDocument doc, MQMaterial mat);
extern void (MQAPICALL *MQDoc_DeleteMaterial)(MQDocument doc, int index);
extern void (MQAPICALL *MQDoc_GetUnusedMaterialName)(MQDocument doc, char *buffer, int buffer_size, const char *base_name);
extern void (MQAPICALL *MQDoc_GetUnusedMaterialNameW)(MQDocument doc, wchar_t *buffer, int buffer_size, const wchar_t *base_name);
extern void (MQAPICALL *MQDoc_Compact)(MQDocument doc);
extern void (MQAPICALL *MQDoc_ClearSelect)(MQDocument doc, DWORD flag);
extern BOOL (MQAPICALL *MQDoc_AddSelectVertex)(MQDocument doc, int objindex, int vertindex);
extern BOOL (MQAPICALL *MQDoc_DeleteSelectVertex)(MQDocument doc, int objindex, int vertindex);
extern BOOL (MQAPICALL *MQDoc_IsSelectVertex)(MQDocument doc, int objindex, int vertindex);
extern BOOL (MQAPICALL *MQDoc_AddSelectLine)(MQDocument doc, int objindex, int faceindex, int lineindex);
extern BOOL (MQAPICALL *MQDoc_DeleteSelectLine)(MQDocument doc, int objindex, int faceindex, int lineindex);
extern BOOL (MQAPICALL *MQDoc_IsSelectLine)(MQDocument doc, int objindex, int faceindex, int lineindex);
extern BOOL (MQAPICALL *MQDoc_AddSelectFace)(MQDocument doc, int objindex, int faceindex);
extern BOOL (MQAPICALL *MQDoc_DeleteSelectFace)(MQDocument doc, int objindex, int faceindex);
extern BOOL (MQAPICALL *MQDoc_IsSelectFace)(MQDocument doc, int objindex, int faceindex);
extern BOOL (MQAPICALL *MQDoc_AddSelectUVVertex)(MQDocument doc, int objindex, int faceindex, int vertindex);
extern BOOL (MQAPICALL *MQDoc_DeleteSelectUVVertex)(MQDocument doc, int objindex, int faceindex, int vertindex);
extern BOOL (MQAPICALL *MQDoc_IsSelectUVVertex)(MQDocument doc, int objindex, int faceindex, int vertindex);
extern BOOL (MQAPICALL *MQDoc_FindMappingFile)(MQDocument doc, char *out_path, const char *filename, DWORD map_type);
extern BOOL (MQAPICALL *MQDoc_FindMappingFileW)(MQDocument doc, wchar_t *out_path, const wchar_t *filename, DWORD map_type);
extern MQScene (MQAPICALL *MQDoc_GetScene)(MQDocument doc, int index);
extern BOOL (MQAPICALL *MQDoc_GetMappingImage)(MQDocument doc, const char *filename, DWORD map_type, void **array);
extern BOOL (MQAPICALL *MQDoc_GetMappingImageW)(MQDocument doc, const wchar_t *filename, DWORD map_type, void **array);
extern MQObject (MQAPICALL *MQDoc_GetParentObject)(MQDocument doc, MQObject obj);
extern int (MQAPICALL *MQDoc_GetChildObjectCount)(MQDocument doc, MQObject obj);
extern MQObject (MQAPICALL *MQDoc_GetChildObject)(MQDocument doc, MQObject obj, int index);
extern void (MQAPICALL *MQDoc_GetGlobalMatrix)(MQDocument doc, MQObject obj, float *matrix);
extern void (MQAPICALL *MQDoc_GetGlobalInverseMatrix)(MQDocument doc, MQObject obj, float *matrix);
extern int  (MQAPICALL *MQDoc_InsertObject)(MQDocument doc, MQObject obj, MQObject before);
extern BOOL (MQAPICALL *MQDoc_RemoveObject)(MQDocument doc, MQObject obj);
extern int  (MQAPICALL *MQDoc_CreateUserData)(MQDocument doc, MQUserDataInfo *info);
extern void (MQAPICALL *MQDoc_DeleteUserData)(MQDocument doc, int userdata_type, int userdata_id);
extern BOOL (MQAPICALL *MQDoc_Triangulate)(MQDocument doc, const MQPoint *points, int points_num, int *index_array, int index_num);

//
// class MQScene
//
extern void (MQAPICALL *MQScene_InitSize)(MQScene scene, int width, int height);
extern void (MQAPICALL *MQScene_GetProjMatrix)(MQScene scene, float *matrix);
extern void (MQAPICALL *MQScene_GetViewMatrix)(MQScene scene, float *matrix);
extern void (MQAPICALL *MQScene_IntValue)(MQScene scene, int type_id, int *values);
extern void (MQAPICALL *MQScene_FloatValue)(MQScene scene, int type_id, float *values);
extern void (MQAPICALL *MQScene_ValueArray)(MQScene scene, int type_id, void **array);
extern BOOL (MQAPICALL *MQScene_GetVisibleFace)(MQScene scene, MQObject obj, BOOL *visible);

//
// class MQObject
//
extern void (MQAPICALL *MQObj_Delete)(MQObject obj);
extern MQObject (MQAPICALL *MQObj_Clone)(MQObject obj);
extern void (MQAPICALL *MQObj_Merge)(MQObject dest, MQObject source);
extern void (MQAPICALL *MQObj_Clear)(MQObject obj, DWORD flag);
extern void (MQAPICALL *MQObj_Freeze)(MQObject obj, DWORD flag);
//extern void (MQAPICALL *MQObj_GetName)(MQObject obj, char *buffer, int size);
extern int  (MQAPICALL *MQObj_GetVertexCount)(MQObject obj);
extern void (MQAPICALL *MQObj_GetVertex)(MQObject obj, int index, MQPoint *pts);
extern void (MQAPICALL *MQObj_SetVertex)(MQObject obj, int index, MQPoint *pts);
extern void (MQAPICALL *MQObj_GetVertexArray)(MQObject obj, MQPoint *ptsarray);
extern int  (MQAPICALL *MQObj_GetFaceCount)(MQObject obj);
extern int  (MQAPICALL *MQObj_GetFacePointCount)(MQObject obj, int face);
extern void (MQAPICALL *MQObj_GetFacePointArray)(MQObject obj, int face, int *vertex);
extern void (MQAPICALL *MQObj_GetFaceCoordinateArray)(MQObject obj, int face, MQCoordinate *uvarray);
extern void (MQAPICALL *MQObj_GetFaceCoordinate)(MQObject obj, int face, int apex, MQCoordinate& uv);
extern BOOL (MQAPICALL *MQObj_GetFaceChannelCoordinate)(MQObject obj, int face, int apex, UINT channelID, MQCoordinate& uvarray);
extern int  (MQAPICALL *MQObj_GetFaceMaterial)(MQObject obj, int face);
extern UINT (MQAPICALL *MQObj_GetFaceUniqueID)(MQObject obj, int face);
extern int (MQAPICALL *MQObj_GetFaceIndexFromUniqueID)(MQObject obj, UINT unique_id);
extern void (MQAPICALL *MQObj_SetName)(MQObject obj, const char *buffer);
extern int  (MQAPICALL *MQObj_AddVertex)(MQObject obj, MQPoint *p);
extern BOOL (MQAPICALL *MQObj_DeleteVertex)(MQObject obj, int index, BOOL del_face);
extern int  (MQAPICALL *MQObj_GetVertexRefCount)(MQObject obj, int index);
extern UINT (MQAPICALL *MQObj_GetVertexUniqueID)(MQObject obj, int index);
extern int (MQAPICALL *MQObj_GetVertexIndexFromUniqueID)(MQObject obj, UINT unique_id);
extern int  (MQAPICALL *MQObj_GetVertexRelatedFaces)(MQObject obj, int vertex, int *faces);
//extern DWORD (MQAPICALL *MQObj_GetVertexColor)(MQObject obj, int index); // OBSOLETE
//extern void (MQAPICALL *MQObj_SetVertexColor)(MQObject obj, int index, DWORD color); // OBSOLETE
extern float (MQAPICALL *MQObj_GetVertexWeight)(MQObject obj, int index);
extern void (MQAPICALL *MQObj_SetVertexWeight)(MQObject obj, int index, float value);
extern void (MQAPICALL *MQObj_CopyVertexAttribute)(MQObject obj, int vert1, MQObject obj2, int vert2);
extern int  (MQAPICALL *MQObj_AddFace)(MQObject obj, int count, int *index);
extern int  (MQAPICALL *MQObj_InsertFace)(MQObject obj, int face_index, int count, int *vert_index);
extern BOOL (MQAPICALL *MQObj_DeleteFace)(MQObject obj, int index, BOOL del_vert);
extern BOOL (MQAPICALL *MQObj_InvertFace)(MQObject obj, int index);
extern void (MQAPICALL *MQObj_SetFaceMaterial)(MQObject obj, int face, int material);
extern void (MQAPICALL *MQObj_SetFaceCoordinateArray)(MQObject obj, int face, MQCoordinate *uvarray);
extern void (MQAPICALL *MQObj_SetFaceCoordinate)(MQObject obj, int face, int apex, const MQCoordinate& uv);
extern BOOL (MQAPICALL *MQObj_SetFaceChannelCoordinate)(MQObject obj, int face, int apex, UINT channelID, const MQCoordinate& uv);
extern DWORD (MQAPICALL *MQObj_GetFaceVertexColor)(MQObject obj, int face, int vertex);
extern void (MQAPICALL *MQObj_SetFaceVertexColor)(MQObject obj, int face, int vertex, DWORD color);
extern float (MQAPICALL *MQObj_GetFaceEdgeCrease)(MQObject obj, int face, int line);
extern void (MQAPICALL *MQObj_SetFaceEdgeCrease)(MQObject obj, int face, int line, float crease);
extern void (MQAPICALL *MQObj_GetFaceVertexNormal)(MQObject obj, int face, int vertex, BYTE &flag, MQPoint &normal);
extern void (MQAPICALL *MQObj_SetFaceVertexNormal)(MQObject obj, int face, int vertex, BYTE type, MQPoint normal);
extern BOOL (MQAPICALL *MQObj_GetFaceVisible)(MQObject obj, int face);
extern void (MQAPICALL *MQObj_SetFaceVisible)(MQObject obj, int face, BOOL flag);
extern void (MQAPICALL *MQObj_OptimizeVertex)(MQObject obj, float distance, MQBool *apply);
extern void (MQAPICALL *MQObj_Compact)(MQObject obj);
extern DWORD (MQAPICALL *MQObj_GetVisible)(MQObject obj);
extern void (MQAPICALL *MQObj_SetVisible)(MQObject obj, DWORD visible);
extern DWORD (MQAPICALL *MQObj_GetPatchType)(MQObject obj);
extern void (MQAPICALL *MQObj_SetPatchType)(MQObject obj, DWORD type);
extern int  (MQAPICALL *MQObj_GetPatchSegment)(MQObject obj);
extern void (MQAPICALL *MQObj_SetPatchSegment)(MQObject obj, int segment);
extern int  (MQAPICALL *MQObj_GetShading)(MQObject obj);
extern void (MQAPICALL *MQObj_SetShading)(MQObject obj, int type);
extern float (MQAPICALL *MQObj_GetSmoothAngle)(MQObject obj);
extern void (MQAPICALL *MQObj_SetSmoothAngle)(MQObject obj, float degree);
extern int  (MQAPICALL *MQObj_GetMirrorType)(MQObject obj);
extern void (MQAPICALL *MQObj_SetMirrorType)(MQObject obj, int type);
extern DWORD (MQAPICALL *MQObj_GetMirrorAxis)(MQObject obj);
extern void (MQAPICALL *MQObj_SetMirrorAxis)(MQObject obj, DWORD axis);
extern float (MQAPICALL *MQObj_GetMirrorDistance)(MQObject obj);
extern void (MQAPICALL *MQObj_SetMirrorDistance)(MQObject obj, float dis);
extern int  (MQAPICALL *MQObj_GetLatheType)(MQObject obj);
extern void (MQAPICALL *MQObj_SetLatheType)(MQObject obj, int type);
extern DWORD (MQAPICALL *MQObj_GetLatheAxis)(MQObject obj);
extern void (MQAPICALL *MQObj_SetLatheAxis)(MQObject obj, DWORD axis);
extern int  (MQAPICALL *MQObj_GetLatheSegment)(MQObject obj);
extern void (MQAPICALL *MQObj_SetLatheSegment)(MQObject obj, int segment);
extern int (MQAPICALL *MQObj_GetIntValue)(MQObject obj, int type_id);
extern void (MQAPICALL *MQObj_GetFloatArray)(MQObject obj, int type_id, float *array);
extern void (MQAPICALL *MQObj_SetIntValue)(MQObject obj, int type_id, int value);
extern void (MQAPICALL *MQObj_SetFloatArray)(MQObject obj, int type_id, const float *array);
extern void (MQAPICALL *MQObj_PointerArray)(MQObject obj, int type_id, void **array);
extern BOOL (MQAPICALL *MQObj_AllocUserData)(MQObject obj, int userdata_id);
extern void (MQAPICALL *MQObj_FreeUserData)(MQObject obj, int userdata_id);
extern BOOL (MQAPICALL *MQObj_GetUserData)(MQObject obj, int userdata_id, int offset, int copy_bytes, void *buffer);
extern BOOL (MQAPICALL *MQObj_SetUserData)(MQObject obj, int userdata_id, int offset, int copy_bytes, const void *buffer);
extern BOOL (MQAPICALL *MQObj_AllocVertexUserData)(MQObject obj, int userdata_id);
extern void (MQAPICALL *MQObj_FreeVertexUserData)(MQObject obj, int userdata_id);
extern BOOL (MQAPICALL *MQObj_GetVertexUserData)(MQObject obj, int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, void *buffer);
extern BOOL (MQAPICALL *MQObj_SetVertexUserData)(MQObject obj, int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, const void *buffer);
extern BOOL (MQAPICALL *MQObj_AllocFaceUserData)(MQObject obj, int userdata_id);
extern void (MQAPICALL *MQObj_FreeFaceUserData)(MQObject obj, int userdata_id);
extern BOOL (MQAPICALL *MQObj_GetFaceUserData)(MQObject obj, int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, void *buffer);
extern BOOL (MQAPICALL *MQObj_SetFaceUserData)(MQObject obj, int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, const void *buffer);

//
// class MQMaterial
//
extern void (MQAPICALL *MQMat_Delete)(MQMaterial mat);
extern int (MQAPICALL *MQMat_GetIntValue)(MQMaterial mat, int type_id);
extern void (MQAPICALL *MQMat_GetFloatArray)(MQMaterial mat, int type_id, float *array);
//extern void (MQAPICALL *MQMat_GetName)(MQMaterial mat, char *buffer, int size);
extern void (MQAPICALL *MQMat_GetColor)(MQMaterial mat, MQColor *color);
extern float (MQAPICALL *MQMat_GetAlpha)(MQMaterial mat);
extern float (MQAPICALL *MQMat_GetDiffuse)(MQMaterial mat);
extern float (MQAPICALL *MQMat_GetAmbient)(MQMaterial mat);
extern float (MQAPICALL *MQMat_GetEmission)(MQMaterial mat);
extern float (MQAPICALL *MQMat_GetSpecular)(MQMaterial mat);
extern float (MQAPICALL *MQMat_GetPower)(MQMaterial mat);
extern void (MQAPICALL *MQMat_GetTextureName)(MQMaterial mat, char *buffer, int size);
extern void (MQAPICALL *MQMat_GetAlphaName)(MQMaterial mat, char *buffer, int size);
extern void (MQAPICALL *MQMat_GetBumpName)(MQMaterial mat, char *buffer, int size);
extern void (MQAPICALL *MQMat_SetIntValue)(MQMaterial mat, int type_id, int value);
extern void (MQAPICALL *MQMat_SetFloatArray)(MQMaterial mat, int type_id, const float *array);
extern void (MQAPICALL *MQMat_SetName)(MQMaterial mat, const char *name);
extern void (MQAPICALL *MQMat_SetColor)(MQMaterial mat, MQColor *color);
extern void (MQAPICALL *MQMat_SetAlpha)(MQMaterial mat, float value);
extern void (MQAPICALL *MQMat_SetDiffuse)(MQMaterial mat, float value);
extern void (MQAPICALL *MQMat_SetAmbient)(MQMaterial mat, float value);
extern void (MQAPICALL *MQMat_SetEmission)(MQMaterial mat, float value);
extern void (MQAPICALL *MQMat_SetSpecular)(MQMaterial mat, float value);
extern void (MQAPICALL *MQMat_SetPower)(MQMaterial mat, float value);
extern void (MQAPICALL *MQMat_SetTextureName)(MQMaterial mat, const char *name);
extern void (MQAPICALL *MQMat_SetAlphaName)(MQMaterial mat, const char *name);
extern void (MQAPICALL *MQMat_SetBumpName)(MQMaterial mat, const char *name);
extern BOOL (MQAPICALL *MQMat_AllocUserData)(MQMaterial mat, int userdata_id);
extern void (MQAPICALL *MQMat_FreeUserData)(MQMaterial mat, int userdata_id);
extern BOOL (MQAPICALL *MQMat_GetUserData)(MQMaterial mat, int userdata_id, int offset, int copy_bytes, void *buffer);
extern BOOL (MQAPICALL *MQMat_SetUserData)(MQMaterial mat, int userdata_id, int offset, int copy_bytes, const void *buffer);
extern void (MQAPICALL *MQMat_GetValueArray)(MQMaterial mat, int type_id, void **array);
extern void (MQAPICALL *MQMat_SetValueArray)(MQMaterial mat, int type_id, void **array);

// class MQShaderNode
extern void (MQAPICALL *MQShaderNode_GetValueArray)(MQShaderNode shader, int type_id, void **array);
extern void (MQAPICALL *MQShaderNode_SetValueArray)(MQShaderNode shader, int type_id, void **array);

//
// class MQMatrix
//
extern void (MQAPICALL *MQMatrix_FloatValue)(float *mtx, int type_id, float *values);

//
// class MQXmlElement
//
extern void (MQAPICALL *MQXmlElem_Value)(MQXmlElement elem, int type_id, void *values);

//
// class MQXmlDocument
//
extern void (MQAPICALL *MQXmlDoc_Value)(MQXmlDocument doc, int type_id, void *values);

//
// class MQWidget
//
extern BOOL (MQAPICALL *MQWidget_Value)(int widget_id, int type_id, void *values);

//
// class MQCanvas
//
extern void (MQAPICALL *MQCanvas_Value)(void *canvas, int type_id, void *values);

//
// class MQSVGDraw
//
extern void (MQAPICALL *MQSVGDraw_Value)(void *canvas, int type_id, void *values);



//
// class MQCDocument
//
class MQCDocument
{
public:
	int 		GetObjectCount(void);
	MQObject 	GetObject(int index);
	MQObject 	GetObjectFromUniqueID(int id);
	int 		GetCurrentObjectIndex(void);
	void 		SetCurrentObjectIndex(int index);
	int 		AddObject(MQObject obj);
	int			InsertObject(MQObject obj, MQObject before);
	BOOL		RemoveObject(MQObject obj);
	void 		DeleteObject(int index);
	int 		GetObjectIndex(MQObject obj);
	void		GetUnusedObjectName(char *buffer, int buffer_size);
	void		GetUnusedObjectName(char *buffer, int buffer_size, const char *base_name);
	void		GetUnusedObjectName(wchar_t *buffer, int buffer_size);
	void		GetUnusedObjectName(wchar_t *buffer, int buffer_size, const wchar_t *base_name);
	int 		GetMaterialCount(void);
	MQMaterial 	GetMaterial(int index);
	MQMaterial 	GetMaterialFromUniqueID(int id);
	int 		GetCurrentMaterialIndex(void);
	void 		SetCurrentMaterialIndex(int index);
	int 		AddMaterial(MQMaterial mat);
	void 		DeleteMaterial(int index);
	void		GetUnusedMaterialName(char *buffer, int buffer_size);
	void		GetUnusedMaterialName(char *buffer, int buffer_size, const char *base_name);
	void		GetUnusedMaterialName(wchar_t *buffer, int buffer_size);
	void		GetUnusedMaterialName(wchar_t *buffer, int buffer_size, const wchar_t *base_name);
	void 		Compact(void);
	void 		ClearSelect(DWORD flag);
	BOOL 		AddSelectVertex(int objindex, int vertindex);
	BOOL 		DeleteSelectVertex(int objindex, int vertindex);
	BOOL 		IsSelectVertex(int objindex, int vertindex);
	BOOL 		AddSelectVertex(MQSelectVertex sel);
	BOOL 		DeleteSelectVertex(MQSelectVertex sel);
	BOOL 		IsSelectVertex(MQSelectVertex sel);
	BOOL 		AddSelectLine(int objindex, int faceindex, int lineindex);
	BOOL 		DeleteSelectLine(int objindex, int faceindex, int lineindex);
	BOOL 		IsSelectLine(int objindex, int faceindex, int lineindex);
	BOOL 		AddSelectLine(MQSelectLine sel);
	BOOL 		DeleteSelectLine(MQSelectLine sel);
	BOOL 		IsSelectLine(MQSelectLine sel);
	BOOL 		AddSelectFace(int objindex, int faceindex);
	BOOL 		DeleteSelectFace(int objindex, int faceindex);
	BOOL 		IsSelectFace(int objindex, int faceindex);
	BOOL 		AddSelectFace(MQSelectFace sel);
	BOOL 		DeleteSelectFace(MQSelectFace sel);
	BOOL 		IsSelectFace(MQSelectFace sel);
	BOOL 		AddSelectUVVertex(int objindex, int faceindex, int vertindex);
	BOOL 		DeleteSelectUVVertex(int objindex, int faceindex, int vertindex);
	BOOL 		IsSelectUVVertex(int objindex, int faceindex, int vertindex);
	BOOL 		FindMappingFile(char *out_path, const char *filename, DWORD map_type);
	BOOL 		FindMappingFile(wchar_t *out_path, const wchar_t *filename, DWORD map_type);
	UINT		GetUVChannelID(const wchar_t *name);
	std::wstring GetUVChannelName(UINT channelID);
	int			GetMaxUVChannelNum();
	MQScene 	GetScene(int index);
	std::wstring GetEnvironmentMapName();
	BOOL		SetEnvironmentMapName(const std::wstring& name, BOOL show_progress = FALSE);
	float		GetEnvironmentMapIntensity();
	void		SetEnvironmentMapIntensity(float intensity);
	float		GetEnvironmentMapRotation();
	void		SetEnvironmentMapRotation(float rotation);
	BOOL		GetMappingImageSize(const char *filename, DWORD map_type, int& width, int& height);
	BOOL		GetMappingImageSize(const wchar_t *filename, DWORD map_type, int& width, int& height);
	BOOL		GetMappingImage(const char *filename, DWORD map_type, int& width, int& height, int& bpp, const RGBQUAD*& colors, const BYTE*& buffer);
	BOOL		GetMappingImage(const wchar_t *filename, DWORD map_type, int& width, int& height, int& bpp, const RGBQUAD*& colors, const BYTE*& buffer);
	MQObject	GetParentObject(MQObject obj);
	int			GetChildObjectCount(MQObject obj);
	MQObject	GetChildObject(MQObject obj, int index);
	void		GetGlobalMatrix(MQObject obj, MQMatrix& matrix);
	void		GetGlobalInverseMatrix(MQObject obj, MQMatrix& matrix);
private:
	int  		CreateUserData(DWORD productID, DWORD pluginID, const char *identifier, int userdata_type, int bytes_per_object);
	int  		FindUserData(DWORD productID, DWORD pluginID, const char *identifier, int userdata_type);
public:
	int  		CreateObjectUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_object);
	void		DeleteObjectUserData(int userdata_id);
	int  		FindObjectUserData(DWORD productID, DWORD pluginID, const char *identifier);
	int  		CreateVertexUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_vertex);
	void		DeleteVertexUserData(int userdata_id);
	int  		FindVertexUserData(DWORD productID, DWORD pluginID, const char *identifier);
	int  		CreateFaceUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_face);
	void		DeleteFaceUserData(int userdata_id);
	int  		FindFaceUserData(DWORD productID, DWORD pluginID, const char *identifier);
	int  		CreateMaterialUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_material);
	void		DeleteMaterialUserData(int userdata_id);
	int  		FindMaterialUserData(DWORD productID, DWORD pluginID, const char *identifier);
	BOOL		Triangulate(const MQPoint *points, int points_num, int *index_array, int index_num);
};



//
// class MQCScene
//
class MQCScene
{
public:
	void InitSize(int width, int height);
	void GetProjMatrix(float *matrix);
	void GetViewMatrix(float *matrix);
	MQPoint GetCameraPosition();
	MQAngle GetCameraAngle();
	MQPoint GetLookAtPosition();
	MQPoint GetRotationCenter();
	float GetFOV();
	//MQPoint GetGlobalDirectionalLight(); // OBSOLETE in Rev3.11: Replaced with GetGlobalDirectionalLightDirection()
	MQColor GetGlobalAmbientColor();
	void SetCameraPosition(const MQPoint& p);
	void SetCameraAngle(const MQAngle& angle);
	void SetLookAtPosition(const MQPoint& p);
	void SetRotationCenter(const MQPoint& p);
	void SetFOV(float fov);
	//void SetGlobalDirectionalLight(const MQPoint& dir); // OBSOLETE in Rev3.11: Replaced with SetGlobalDirectionalLightDirection()
	void SetGlobalAmbientColor(const MQColor& amb);

	MQPoint Convert3DToScreen(const MQPoint& p, float *out_w = NULL);
	MQPoint ConvertScreenTo3D(const MQPoint& p);
	BOOL GetVisibleFace(MQObject obj, BOOL *visible);
	int AddGlobalDirectionalLight();
	BOOL DeleteGlobalDirectionalLight(int index);
	int GetGlobalDirectionalLightNum();
	MQPoint GetGlobalDirectionalLightDirection(int index);
	MQColor GetGlobalDirectionalLightColor(int index);
	void SetGlobalDirectionalLightDirection(int index, const MQPoint& dir);
	void SetGlobalDirectionalLightColor(int index, const MQColor& col);
	float GetFrontZ();
	bool GetOrtho();
	void SetOrtho(bool ortho);
	float GetZoom();
	void SetZoom(float zoom);
	float GetFrontClip();
	float GetBackClip();

	std::wstring GetBackgroundImage();
	BOOL SetBackgroundImage(const std::wstring& name);
	BOOL GetBackgroundImagePosition(float& x1, float& y1, float& x2, float& y2, float& rotation);
	BOOL SetBackgroundImagePosition(float x1, float y1, float x2, float y2, float rotation);
};


//
// class MQCObject
//
class MQCObject
{
public:
	void 	DeleteThis(void);
	MQObject Clone(void);
	//void 	Merge(MQObject source); // OBSOLETE
	BOOL 	Merge(MQObject source);
	void	Clear(void);
	//void 	Freeze(DWORD flag); // OBSOLETE
	BOOL 	Freeze(DWORD flag);
	int 	GetName(char *buffer, int size);
	int 	GetNameW(wchar_t *buffer, int size);
	std::string GetName();
	std::wstring GetNameW();

	int  	GetVertexCount(void);
	MQPoint GetVertex(int index);
	void 	SetVertex(int index, MQPoint pts);
	void 	GetVertexArray(MQPoint *ptsarray);
	BOOL  	ReserveVertex(int size);
	int  	AddVertex(MQPoint p);
	BOOL 	DeleteVertex(int index);
	int  	GetVertexRefCount(int index);
	UINT  	GetVertexUniqueID(int index);
	int  	GetVertexIndexFromUniqueID(UINT unique_id);
	int		GetVertexRelatedFaces(int vertex, int *faces);
	//DWORD 	GetVertexColor(int index); // OBSOLETE
	//void 	SetVertexColor(int index, DWORD color); // OBSOLETE
	float 	GetVertexWeight(int index);
	void 	SetVertexWeight(int index, float value);
	void 	CopyVertexAttribute(int vert1, MQObject obj2, int vert2);

	int  	GetFaceCount(void);
	int  	GetFacePointCount(int face);
	void 	GetFacePointArray(int face, int *vertex);
	void 	GetFaceCoordinateArray(int face, MQCoordinate *uvarray);
	void 	GetFaceCoordinate(int face, int vertex, MQCoordinate& uv);
	int  	GetFaceMaterial(int face);
	UINT  	GetFaceUniqueID(int face);
	int  	GetFaceIndexFromUniqueID(UINT unique_id);
	void 	SetName(const char *buffer);
	void 	SetName(const wchar_t *buffer);
	BOOL  	ReserveFace(int size);
	int  	AddFace(int count, int *index);
	int		InsertFace(int face_index, int count, int *vert_index);
	BOOL 	DeleteFace(int index, bool delete_vertex=true);
	BOOL 	InvertFace(int index);
	void 	SetFaceMaterial(int face, int material);
	void 	SetFaceCoordinateArray(int face, MQCoordinate *uvarray);
	void 	SetFaceCoordinate(int face, int vertex, const MQCoordinate& uv);
	DWORD  	GetFaceVertexColor(int face, int vertex);
	void  	SetFaceVertexColor(int face, int vertex, DWORD color);
	float	GetFaceEdgeCrease(int face, int line);
	void	SetFaceEdgeCrease(int face, int line, float crease);
	void	UpdateNormal();
	void	GetFaceVertexNormal(int face, int vertex, BYTE &flag, MQPoint &normal);
	void	SetFaceVertexNormal(int face, int vertex, BYTE flag, MQPoint normal);
	BOOL	GetFaceVisible(int face);
	void	SetFaceVisible(int face, BOOL visible);

	int		GetUVChannelNum();
	bool	GetUVChannel(int index, UINT& channelID);
	bool	ActivateUVChannel(UINT channelID);
	UINT	GetActiveUVChannel();
	bool	AddUVChannel(UINT channelID);
	bool	DeleteUVChannel(UINT channelID);
	bool	GetFaceChannelCoordinate(int face, int vertex, UINT channelID, MQCoordinate& uv);
	bool	SetFaceChannelCoordinate(int face, int vertex, UINT channelID, const MQCoordinate& uv);

	void 	OptimizeVertex(float distance, MQBool *apply);
	BOOL 	OptimizeVertex(float distance, MQBool *apply, bool callback(float,void*), void *callback_data);
	void 	Compact(void);

	DWORD 	GetVisible(void);
	void 	SetVisible(DWORD visible);
	DWORD 	GetPatchType(void);
	void 	SetPatchType(DWORD type);
	int  	GetPatchSegment(void);
	void 	SetPatchSegment(int segment);
	BOOL	GetPatchTriangle(void);
	void	SetPatchTriangle(BOOL flag);
	BOOL	GetPatchSmoothTriangle(void);
	void	SetPatchSmoothTriangle(BOOL flag);
	BOOL	GetPatchLimitSurface(void);
	void	SetPatchLimitSurface(BOOL flag);
	int		GetPatchMeshInterp(void);
	void	SetPatchMeshInterp(int interp);
	int		GetPatchUVInterp(void);
	void	SetPatchUVInterp(int interp);
	int  	GetShading(void);
	void 	SetShading(int type);
	float 	GetSmoothAngle(void);
	void 	SetSmoothAngle(float degree);
	int  	GetMirrorType(void);
	void 	SetMirrorType(int type);
	DWORD 	GetMirrorAxis(void);
	void 	SetMirrorAxis(DWORD axis);
	float 	GetMirrorDistance(void);
	void 	SetMirrorDistance(float dis);
	int  	GetLatheType(void);
	void 	SetLatheType(int type);
	DWORD 	GetLatheAxis(void);
	void 	SetLatheAxis(DWORD axis);
	int  	GetLatheSegment(void);
	void 	SetLatheSegment(int segment);
	UINT	GetUniqueID(void);
	int		GetDepth(void);
	void	SetDepth(int depth);
	BOOL	GetFolding(void);
	void	SetFolding(BOOL flag);
	BOOL	GetLocking(void);
	void	SetLocking(BOOL flag);
	MQColor	GetColor(void);
	void	SetColor(MQColor color);
	BOOL	GetColorValid(void);
	void	SetColorValid(BOOL flag);

	MQPoint	GetScaling(void);
	void	SetScaling(MQPoint scale);
	MQAngle	GetRotation(void);
	void	SetRotation(MQAngle angle);
	MQPoint	GetTranslation(void);
	void	SetTranslation(MQPoint trans);
	MQMatrix	GetLocalMatrix(void);
	void		SetLocalMatrix(const MQMatrix& mtx);
	MQMatrix	GetLocalInverseMatrix(void);

	int		GetType(void);
	void	SetType(int type);
	float	GetLightValue(void);
	void	SetLightValue(float value);
	int		GetLightAttenuation(void);
	void	SetLightAttenuation(int value);
	float	GetLightFallOffEnd(void);
	void	SetLightFallOffEnd(float distance);
	float	GetLightFallOffHalf(void);
	void	SetLightFallOffHalf(float distance);
	BOOL	GetSelected();
	void	SetSelected(BOOL flag);

	BOOL	AllocUserData(int userdata_id);
	void 	FreeUserData(int userdata_id);
	BOOL 	GetUserData(int userdata_id, void *buffer);
	BOOL 	GetUserDataPart(int userdata_id, int offset, int copy_bytes, void *buffer);
	BOOL 	SetUserData(int userdata_id, const void *buffer);
	BOOL 	SetUserDataPart(int userdata_id, int offset, int copy_bytes, const void *buffer);
	BOOL	AllocVertexUserData(int userdata_id);
	void 	FreeVertexUserData(int userdata_id);
	BOOL 	GetVertexUserData(int userdata_id, int vertex_index, void *buffer);
	BOOL 	GetVertexUserDataPart(int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, void *buffer);
	BOOL 	SetVertexUserData(int userdata_id, int vertex_index, const void *buffer);
	BOOL 	SetVertexUserDataPart(int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, const void *buffer);
	BOOL	AllocFaceUserData(int userdata_id);
	void 	FreeFaceUserData(int userdata_id);
	BOOL 	GetFaceUserData(int userdata_id, int face_index, void *buffer);
	BOOL 	GetFaceUserDataPart(int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, void *buffer);
	BOOL 	SetFaceUserData(int userdata_id, int face_index, const void *buffer);
	BOOL 	SetFaceUserDataPart(int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, const void *buffer);
	
	void	AddRenderFlag(MQOBJECT_RENDER_FLAG flag);
	void	RemoveRenderFlag(MQOBJECT_RENDER_FLAG flag);
	void	AddRenderEraseFlag(MQOBJECT_RENDER_FLAG flag);
	void	RemoveRenderEraseFlag(MQOBJECT_RENDER_FLAG flag);
};


//
// class MQCMaterial
//
class MQCMaterial
{
public:
	void 	DeleteThis(void);
	MQMaterial Clone(void);
	int 	GetName(char *buffer, int size);
	int 	GetNameW(wchar_t *buffer, int size);
	std::string GetName();
	std::wstring GetNameW();

	UINT 	GetUniqueID(void);
	MQColor GetColor(void);
	float 	GetAlpha(void);
	float 	GetDiffuse(void);
	float 	GetAmbient(void);
	float 	GetEmission(void);
	float 	GetSpecular(void);
	float 	GetPower(void);
	MQColor GetAmbientColor(void);
	MQColor GetEmissionColor(void);
	MQColor GetSpecularColor(void);
	float 	GetReflection(void);
	float 	GetRefraction(void);
	void 	GetTextureName(char *buffer, int size);
	std::string GetTextureName();
	int		GetTextureNameW(wchar_t *buffer, int size);
	std::wstring GetTextureNameW();
	void 	GetAlphaName(char *buffer, int size);
	std::string GetAlphaName();
	int		GetAlphaNameW(wchar_t *buffer, int size);
	std::wstring GetAlphaNameW();
	void 	GetBumpName(char *buffer, int size);
	std::string GetBumpName();
	int		GetBumpNameW(wchar_t *buffer, int size);
	std::wstring GetBumpNameW();
	UINT	GetTextureUVChannel();
	UINT	GetAlphaUVChannel();
	UINT	GetBumpUVChannel();

	void 	SetName(const char *name);
	void 	SetName(const wchar_t *name);
	void 	SetColor(MQColor color);
	void 	SetAlpha(float value);
	void 	SetDiffuse(float value);
	void 	SetAmbient(float value);
	void 	SetEmission(float value);
	void 	SetSpecular(float value);
	void 	SetPower(float value);
	void 	SetAmbientColor(MQColor color);
	void 	SetEmissionColor(MQColor color);
	void 	SetSpecularColor(MQColor color);
	void 	SetReflection(float value);
	void 	SetRefraction(float value);
	void 	SetTextureName(const char *name);
	void 	SetTextureName(const wchar_t *name);
	void 	SetAlphaName(const char *name);
	void 	SetAlphaName(const wchar_t *name);
	void 	SetBumpName(const char *name);
	void 	SetBumpName(const wchar_t *name);
	void	SetTextureUVChannel(UINT channel);
	void	SetAlphaUVChannel(UINT channel);
	void	SetBumpUVChannel(UINT channel);

	int 	GetShader(void);
	int 	GetVertexColor(void);
	int 	GetMappingType(void);
	MQPoint GetMappingPosition(void);
	MQPoint GetMappingScaling(void);
	MQAngle GetMappingAngle(void);
	int		GetMappingFilter(void);
	int		GetWrapModeU(void);
	int		GetWrapModeV(void);
	void 	SetShader(int shader);
	void 	SetVertexColor(int value);
	void 	SetMappingType(int type);
	void 	SetMappingPosition(MQPoint pos);
	void 	SetMappingScaling(MQPoint scale);
	void 	SetMappingAngle(MQAngle angle);
	void	SetMappingFilter(int type);
	void	SetWrapModeU(int type);
	void	SetWrapModeV(int type);

	BOOL	GetSelected(void);
	void	SetSelected(BOOL flag);
	BOOL	GetDoubleSided(void);
	void	SetDoubleSided(BOOL value);

	BOOL	AllocUserData(int userdata_id);
	void 	FreeUserData(int userdata_id);
	BOOL 	GetUserData(int userdata_id, void *buffer);
	BOOL 	GetUserDataPart(int userdata_id, int offset, int copy_bytes, void *buffer);
	BOOL 	SetUserData(int userdata_id, const void *buffer);
	BOOL 	SetUserDataPart(int userdata_id, int offset, int copy_bytes, const void *buffer);

	// Shader
	int		GetShaderName(char *buffer, int buffer_size);
	std::string GetShaderName(void);
	bool	SetShaderName(const char *name);
	
	// Shader parameter
	int		GetShaderParameterNum(void);
	int		GetShaderParameterName(int index, char *buffer, int buffer_size);
	std::string GetShaderParameterName(int index);
	int		GetShaderParameterValueType(int index);
	int		GetShaderParameterValueType(const char *name);
	int		GetShaderParameterArraySize(int index);
	int		GetShaderParameterArraySize(const char *name);
	bool	GetShaderParameterBoolValue(int index, int array_index);
	bool	GetShaderParameterBoolValue(const char *name, int array_index);
	int		GetShaderParameterIntValue(int index, int array_index);
	int		GetShaderParameterIntValue(const char *name, int array_index);
	float	GetShaderParameterFloatValue(int index, int array_index);
	float	GetShaderParameterFloatValue(const char *name, int array_index);
	MQColorRGBA	GetShaderParameterColorValue(int index, int array_index);
	MQColorRGBA	GetShaderParameterColorValue(const char *name, int array_index);
	void	SetShaderParameterBoolValue(int index, int array_index, bool value);
	void	SetShaderParameterBoolValue(const char *name, int array_index, bool value);
	void	SetShaderParameterIntValue(int index, int array_index, int value);
	void	SetShaderParameterIntValue(const char *name, int array_index, int value);
	void	SetShaderParameterFloatValue(int index, int array_index, float value);
	void	SetShaderParameterFloatValue(const char *name, int array_index, float value);
	void	SetShaderParameterColorValue(int index, int array_index, MQColorRGBA color);
	void	SetShaderParameterColorValue(const char *name, int array_index, MQColorRGBA color);

	// Shader mapping
	int		GetShaderMappingNum(void);
	int		GetShaderMappingName(int index, char *buffer, int buffer_size);
	std::string GetShaderMappingName(int index);
	int		GetShaderMappingFilename(int index, char *buffer, int buffer_size);
	int		GetShaderMappingFilename(const char *name, char *buffer, int buffer_size);
	int		GetShaderMappingFilename(int index, wchar_t *buffer, int buffer_size);
	int		GetShaderMappingFilename(const char *name, wchar_t *buffer, int buffer_size);
	std::string GetShaderMappingFilenameA(int index);
	std::string GetShaderMappingFilenameA(const char *name);
	std::wstring GetShaderMappingFilenameW(int index);
	std::wstring GetShaderMappingFilenameW(const char *name);	
	void	SetShaderMappingFilename(int index, const char *buffer);
	void	SetShaderMappingFilename(const char *name, const char *buffer);
	void	SetShaderMappingFilename(int index, const wchar_t *buffer);
	void	SetShaderMappingFilename(const char *name, const wchar_t *buffer);
	UINT	GetShaderMappingUVChannel(int index);
	UINT	GetShaderMappingUVChannel(const char *name);
	void	SetShaderMappingUVChannel(int index, UINT channel);
	void	SetShaderMappingUVChannel(const char *name, UINT channel);

	// Shader node
	MQShaderNode GetMainShaderNode();
	//MQShaderNode CreateSubShaderNode(const char *shader_name, const char *id);
	//void	DeleteSubShaderNode(const char *id);
	int		GetSubShaderNodeNum();
	std::string	GetSubShaderNodeID(int index);
	MQShaderNode GetSubShaderNode(int index);
	MQShaderNode GetSubShaderNode(const char *id);

};


//
// class MQCShaderNode
//
class MQCShaderNode
{
public:
	int		GetShaderName(char *buffer, int buffer_size);
	std::string GetShaderName(void);
	int		GetOptionValue(const char *option_name, char *buffer, int buffer_size);
	std::string GetOptionValue(const char *option_name);

	// Parameter
	int		GetParameterNum(void);
	int		GetParameterName(int index, char *buffer, int buffer_size);
	std::string GetParameterName(int index);
	int		GetParameterOptionValue(int index, const char *option_name, char *buffer, int buffer_size);
	std::string GetParameterOptionValue(int index, const char *option_name);
	int		GetParameterOptionValue(const char *name, const char *option_name, char *buffer, int buffer_size);
	std::string GetParameterOptionValue(const char *name, const char *option_name);
	int		GetParameterValueType(int index);
	int		GetParameterValueType(const char *name);
	int		GetParameterArraySize(int index);
	int		GetParameterArraySize(const char *name);
	bool	GetParameterBoolValue(int index, int array_index);
	bool	GetParameterBoolValue(const char *name, int array_index);
	int		GetParameterIntValue(int index, int array_index);
	int		GetParameterIntValue(const char *name, int array_index);
	float	GetParameterFloatValue(int index, int array_index);
	float	GetParameterFloatValue(const char *name, int array_index);
	MQColorRGBA	GetParameterColorValue(int index, int array_index);
	MQColorRGBA	GetParameterColorValue(const char *name, int array_index);
	std::string	GetParameterStringValue(int index, int array_index);
	std::string	GetParameterStringValue(const char *name, int array_index);
	void	SetParameterBoolValue(int index, int array_index, bool value);
	void	SetParameterBoolValue(const char *name, int array_index, bool value);
	void	SetParameterIntValue(int index, int array_index, int value);
	void	SetParameterIntValue(const char *name, int array_index, int value);
	void	SetParameterFloatValue(int index, int array_index, float value);
	void	SetParameterFloatValue(const char *name, int array_index, float value);
	void	SetParameterColorValue(int index, int array_index, MQColorRGBA color);
	void	SetParameterColorValue(const char *name, int array_index, MQColorRGBA color);
	void	SetParameterStringValue(int index, int array_index, const char *str);
	void	SetParameterStringValue(const char *name, int array_index, const char *str);

	// Mapping
	int		GetMappingNum(void);
	int		GetMappingName(int index, char *buffer, int buffer_size);
	std::string GetMappingName(int index);
	int		GetMappingOptionValue(int index, const char *option_name, char *buffer, int buffer_size);
	std::string GetMappingOptionValue(int index, const char *option_name);
	int		GetMappingOptionValue(const char *name, const char *option_name, char *buffer, int buffer_size);
	std::string GetMappingOptionValue(const char *name, const char *option_name);
	int		GetMappingFilename(int index, char *buffer, int buffer_size);
	int		GetMappingFilename(const char *name, char *buffer, int buffer_size);
	int		GetMappingFilename(int index, wchar_t *buffer, int buffer_size);
	int		GetMappingFilename(const char *name, wchar_t *buffer, int buffer_size);
	std::string GetMappingFilename(int index);
	std::string GetMappingFilename(const char *name);
	std::wstring GetMappingFilenameW(int index);
	std::wstring GetMappingFilenameW(const char *name);	
	void	SetMappingFilename(int index, const char *buffer);
	void	SetMappingFilename(const char *name, const char *buffer);
	void	SetMappingFilename(int index, const wchar_t *buffer);
	void	SetMappingFilename(const char *name, const wchar_t *buffer);
	bool	GetMappingConnectedNodeID(int index, std::string& node_id, std::string& output);
	bool	GetMappingConnectedNodeID(const char *name, std::string& node_id, std::string& output);
	void	SetMappingConnectedNodeID(int index, const char *node_id, const char *output);
	void	SetMappingConnectedNodeID(const char *name, const char *node_id, const char *output);
	MQShaderNode GetMappingConnectedNode(int index);
	MQShaderNode GetMappingConnectedNode(const char *name);
	UINT	GetMappingUVChannel(int index);
	UINT	GetMappingUVChannel(const char *name);
	void	SetMappingUVChannel(int index, UINT channel);
	void	SetMappingUVChannel(const char *name, UINT channel);

	// Mapping parameter
	int		GetMappingParameterNum(int map_index);
	int		GetMappingParameterNum(const char *map_name);
	int		GetMappingParameterName(int map_index, int param_index, char *buffer, int buffer_size);
	std::string GetMappingParameterName(int map_index, int param_index);
	int		GetMappingParameterName(const char *map_name, int param_index, char *buffer, int buffer_size);
	std::string GetMappingParameterName(const char *map_name, int param_index);
	int		GetMappingParameterOptionValue(int map_index, int param_index, const char *option_name, char *buffer, int buffer_size);
	std::string GetMappingParameterOptionValue(int map_index, int param_index, const char *option_name);
	int		GetMappingParameterOptionValue(const char *map_name, int param_index, const char *option_name, char *buffer, int buffer_size);
	std::string GetMappingParameterOptionValue(const char *map_name, int param_index, const char *option_name);
	int		GetMappingParameterOptionValue(const char *map_name, const char *param_name, const char *option_name, char *buffer, int buffer_size);
	std::string GetMappingParameterOptionValue(const char *map_name, const char *param_name, const char *option_name);
	int		GetMappingParameterValueType(int map_index, int param_index);
	int		GetMappingParameterValueType(const char *map_name, int param_index);
	int		GetMappingParameterValueType(const char *map_name, const char *param_name);
	int		GetMappingParameterArraySize(int map_index, int param_index);
	int		GetMappingParameterArraySize(const char *map_name, int param_index);
	int		GetMappingParameterArraySize(const char *map_name, const char *param_name);
	bool	GetMappingParameterBoolValue(int map_index, int param_index, int array_index);
	bool	GetMappingParameterBoolValue(const char *map_name, int param_index, int array_index);
	bool	GetMappingParameterBoolValue(const char *map_name, const char *param_name, int array_index);
	int		GetMappingParameterIntValue(int map_index, int param_index, int array_index);
	int		GetMappingParameterIntValue(const char *map_name, int param_index, int array_index);
	int		GetMappingParameterIntValue(const char *map_name, const char *param_name, int array_index);
	float	GetMappingParameterFloatValue(int map_index, int param_index, int array_index);
	float	GetMappingParameterFloatValue(const char *map_name, int param_index, int array_index);
	float	GetMappingParameterFloatValue(const char *map_name, const char *param_name, int array_index);
	MQColorRGBA	GetMappingParameterColorValue(int map_index, int param_index, int array_index);
	MQColorRGBA	GetMappingParameterColorValue(const char *map_name, int param_index, int array_index);
	MQColorRGBA	GetMappingParameterColorValue(const char *map_name, const char *param_name, int array_index);
	std::string GetMappingParameterStringValue(int map_index, int param_index, int array_index);
	std::string GetMappingParameterStringValue(const char *map_name, int param_index, int array_index);
	std::string GetMappingParameterStringValue(const char *map_name, const char *param_name, int array_index);
	void	SetMappingParameterBoolValue(int map_index, int param_index, int array_index, bool value);
	void	SetMappingParameterBoolValue(const char *map_name, int param_index, int array_index, bool value);
	void	SetMappingParameterBoolValue(const char *map_name, const char *param_name, int array_index, bool value);
	void	SetMappingParameterIntValue(int map_index, int param_index, int array_index, int value);
	void	SetMappingParameterIntValue(const char *map_name, int param_index, int array_index, int value);
	void	SetMappingParameterIntValue(const char *map_name, const char *param_name, int array_index, int value);
	void	SetMappingParameterFloatValue(int map_index, int param_index, int array_index, float value);
	void	SetMappingParameterFloatValue(const char *map_name, int param_index, int array_index, float value);
	void	SetMappingParameterFloatValue(const char *map_name, const char *param_name, int array_index, float value);
	void	SetMappingParameterColorValue(int map_index, int param_index, int array_index, MQColorRGBA color);
	void	SetMappingParameterColorValue(const char *map_name, int param_index, int array_index, MQColorRGBA color);
	void	SetMappingParameterColorValue(const char *map_name, const char *param_name, int array_index, MQColorRGBA color);
	void	SetMappingParameterStringValue(int map_index, int param_index, int array_index, const char *str);
	void	SetMappingParameterStringValue(const char *map_name, int param_index, int array_index, const char *str);
	void	SetMappingParameterStringValue(const char *map_name, const char *param_name, int array_index, const char *str);

	// Output parameter
	int		GetOutputParameterNum();
	int		GetOutputParameterName(int index, char *buffer, int buffer_size);
	std::string GetOutputParameterName(int index);
	int		GetOutputParameterOptionValue(int index, const char *option_name, char *buffer, int buffer_size);
	std::string GetOutputParameterOptionValue(int index, const char *option_name);
	int		GetOutputParameterOptionValue(const char *name, const char *option_name, char *buffer, int buffer_size);
	std::string GetOutputParameterOptionValue(const char *name, const char *option_name);
	int		GetOutputParameterValueType(int index);
	int		GetOutputParameterValueType(const char *name);
};


//
// class MQCXmlElement
//
class MQCXmlElement
{
	friend class MQCXmlDocument;

public:
	MQXmlElement AddChildElement(const char *name);
	MQXmlElement AddChildElement(const wchar_t *name);
	BOOL RemoveChildElement(MQXmlElement child);

	MQXmlElement FirstChildElement(void);
	MQXmlElement FirstChildElement(const char *name);
	MQXmlElement FirstChildElement(const wchar_t *name);
	MQXmlElement NextChildElement(MQXmlElement child);
	MQXmlElement NextChildElement(const char *name, MQXmlElement child);
	MQXmlElement NextChildElement(const wchar_t *name, MQXmlElement child);
	MQXmlElement GetParentElement();

	std::string GetName(void);
	std::wstring GetNameW(void);
	std::string GetText(void);
	std::wstring GetTextW(void);
	BOOL GetText(std::string& result_value);
	BOOL GetText(std::wstring& result_value);
	std::string GetAttribute(const char *name);
	std::wstring GetAttribute(const wchar_t *name);
	BOOL GetAttribute(const char *name, std::string& result_value);
	BOOL GetAttribute(const wchar_t *name, std::wstring& result_value);

	void SetText(const char *text);
	void SetText(const wchar_t *text);
	void SetAttribute(const char *name, const char *value);
	void SetAttribute(const wchar_t *name, const wchar_t *value);

private:
	MQCXmlElement();
};


//
// class MQCXmlDocument
//
class MQCXmlDocument
{
public:
	static MQXmlDocument Create();
	void DeleteThis();
	MQXmlElement GetRootElement();
	MQXmlElement CreateRootElement(const char *name);
	MQXmlElement CreateRootElement(const wchar_t *name);
	BOOL LoadFile(const char *filename);
	BOOL LoadFile(const wchar_t *filename);
	BOOL SaveFile(const char *filename);
	BOOL SaveFile(const wchar_t *filename);

private:
	MQCXmlDocument();
};

//
// class MQEncoding
//
class MQEncoding {
public:
	static std::string Utf8ToAnsi(const char *ptr);
	static std::wstring Utf8ToWide(const char *ptr);
	static std::string AnsiToUtf8(const char *ptr);
	static std::wstring AnsiToWide(const char *ptr);
	static std::wstring AnsiToWideWithCodePage(const char *ptr, int codepage);
	static std::string WideToAnsi(const wchar_t *ptr);
	static std::string WideToAnsiWithCodePage(const wchar_t *ptr, int codepage);
	static std::string WideToUtf8(const wchar_t *ptr);
};



// class MQCDocument
inline int 		MQCDocument::GetObjectCount(void) 			{ return MQDoc_GetObjectCount(this); }
inline MQObject MQCDocument::GetObject(int index) 			{ return MQDoc_GetObject(this, index); }
inline MQObject MQCDocument::GetObjectFromUniqueID(int id) 	{ return MQDoc_GetObjectFromUniqueID(this, id); }
inline int 		MQCDocument::GetCurrentObjectIndex(void) 	{ return MQDoc_GetCurrentObjectIndex(this); }
inline void 	MQCDocument::SetCurrentObjectIndex(int index) 	{ MQDoc_SetCurrentObjectIndex(this, index); }
inline int 		MQCDocument::AddObject(MQObject obj) 		{ return MQDoc_AddObject(this, obj); }
inline void 	MQCDocument::DeleteObject(int index) 		{ MQDoc_DeleteObject(this, index); }
inline int 		MQCDocument::GetObjectIndex(MQObject obj) 	{ return MQDoc_GetObjectIndex(this, obj); }
inline void		MQCDocument::GetUnusedObjectName(char *buffer, int buffer_size) { return MQDoc_GetUnusedObjectName(this, buffer, buffer_size, NULL); }
inline void		MQCDocument::GetUnusedObjectName(char *buffer, int buffer_size, const char *base_name) { return MQDoc_GetUnusedObjectName(this, buffer, buffer_size, base_name); }
inline void		MQCDocument::GetUnusedObjectName(wchar_t *buffer, int buffer_size) { return MQDoc_GetUnusedObjectNameW(this, buffer, buffer_size, NULL); }
inline void		MQCDocument::GetUnusedObjectName(wchar_t *buffer, int buffer_size, const wchar_t *base_name) { return MQDoc_GetUnusedObjectNameW(this, buffer, buffer_size, base_name); }
inline int 		MQCDocument::GetMaterialCount(void) 		{ return MQDoc_GetMaterialCount(this); }
inline MQMaterial MQCDocument::GetMaterial(int material) 	{ return MQDoc_GetMaterial(this, material); }
inline MQMaterial MQCDocument::GetMaterialFromUniqueID(int id) 	{ return MQDoc_GetMaterialFromUniqueID(this, id); }
inline int 		MQCDocument::GetCurrentMaterialIndex(void) 		{ return MQDoc_GetCurrentMaterialIndex(this); }
inline void 	MQCDocument::SetCurrentMaterialIndex(int index) { MQDoc_SetCurrentMaterialIndex(this, index); }
inline int 		MQCDocument::AddMaterial(MQMaterial mat) 	{ return MQDoc_AddMaterial(this, mat); }
inline void 	MQCDocument::DeleteMaterial(int index) 		{ MQDoc_DeleteMaterial(this, index); }
inline void		MQCDocument::GetUnusedMaterialName(char *buffer, int buffer_size) { return MQDoc_GetUnusedMaterialName(this, buffer, buffer_size, NULL); }
inline void		MQCDocument::GetUnusedMaterialName(char *buffer, int buffer_size, const char *base_name) { return MQDoc_GetUnusedMaterialName(this, buffer, buffer_size, base_name); }
inline void		MQCDocument::GetUnusedMaterialName(wchar_t *buffer, int buffer_size) { return MQDoc_GetUnusedMaterialNameW(this, buffer, buffer_size, NULL); }
inline void		MQCDocument::GetUnusedMaterialName(wchar_t *buffer, int buffer_size, const wchar_t *base_name) { return MQDoc_GetUnusedMaterialNameW(this, buffer, buffer_size, base_name); }
inline void 	MQCDocument::Compact(void) 					{ MQDoc_Compact(this); }
inline void 	MQCDocument::ClearSelect(DWORD flag) 		{ MQDoc_ClearSelect(this, flag); }
inline BOOL 	MQCDocument::AddSelectVertex(int objindex, int vertindex) 		{ return MQDoc_AddSelectVertex(this, objindex, vertindex); }
inline BOOL 	MQCDocument::DeleteSelectVertex(int objindex, int vertindex) 	{ return MQDoc_DeleteSelectVertex(this, objindex, vertindex); }
inline BOOL 	MQCDocument::IsSelectVertex(int objindex, int vertindex) 		{ return MQDoc_IsSelectVertex(this, objindex, vertindex); }
inline BOOL 	MQCDocument::AddSelectVertex(MQSelectVertex sel) 				{ return MQDoc_AddSelectVertex(this, sel.object, sel.vertex); }
inline BOOL 	MQCDocument::DeleteSelectVertex(MQSelectVertex sel) 			{ return MQDoc_DeleteSelectVertex(this, sel.object, sel.vertex); }
inline BOOL 	MQCDocument::IsSelectVertex(MQSelectVertex sel) 				{ return MQDoc_IsSelectVertex(this, sel.object, sel.vertex); }
inline BOOL 	MQCDocument::AddSelectLine(int objindex, int faceindex, int lineindex) 		{ return MQDoc_AddSelectLine(this, objindex, faceindex, lineindex); }
inline BOOL 	MQCDocument::DeleteSelectLine(int objindex, int faceindex, int lineindex) 	{ return MQDoc_DeleteSelectLine(this, objindex, faceindex, lineindex); }
inline BOOL 	MQCDocument::IsSelectLine(int objindex, int faceindex, int lineindex) 		{ return MQDoc_IsSelectLine(this, objindex, faceindex, lineindex); }
inline BOOL 	MQCDocument::AddSelectLine(MQSelectLine sel) 								{ return MQDoc_AddSelectLine(this, sel.object, sel.face, sel.line); }
inline BOOL 	MQCDocument::DeleteSelectLine(MQSelectLine sel) 							{ return MQDoc_DeleteSelectLine(this, sel.object, sel.face, sel.line); }
inline BOOL 	MQCDocument::IsSelectLine(MQSelectLine sel) 								{ return MQDoc_IsSelectLine(this, sel.object, sel.face, sel.line); }
inline BOOL 	MQCDocument::AddSelectFace(int objindex, int faceindex) 					{ return MQDoc_AddSelectFace(this, objindex, faceindex); }
inline BOOL 	MQCDocument::DeleteSelectFace(int objindex, int faceindex) 					{ return MQDoc_DeleteSelectFace(this, objindex, faceindex); }
inline BOOL 	MQCDocument::IsSelectFace(int objindex, int faceindex) 						{ return MQDoc_IsSelectFace(this, objindex, faceindex); }
inline BOOL 	MQCDocument::AddSelectFace(MQSelectFace sel) 								{ return MQDoc_AddSelectFace(this, sel.object, sel.face); }
inline BOOL 	MQCDocument::DeleteSelectFace(MQSelectFace sel) 							{ return MQDoc_DeleteSelectFace(this, sel.object, sel.face); }
inline BOOL 	MQCDocument::IsSelectFace(MQSelectFace sel) 								{ return MQDoc_IsSelectFace(this, sel.object, sel.face); }
inline BOOL 	MQCDocument::AddSelectUVVertex(int objindex, int faceindex, int vertindex)		{ return MQDoc_AddSelectUVVertex(this, objindex, faceindex, vertindex); }
inline BOOL 	MQCDocument::DeleteSelectUVVertex(int objindex, int faceindex, int vertindex)	{ return MQDoc_DeleteSelectUVVertex(this, objindex, faceindex, vertindex); }
inline BOOL 	MQCDocument::IsSelectUVVertex(int objindex, int faceindex, int vertindex)		{ return MQDoc_IsSelectUVVertex(this, objindex, faceindex, vertindex); }
inline BOOL 	MQCDocument::FindMappingFile(char *out_path, const char *filename, DWORD map_type) { return MQDoc_FindMappingFile(this, out_path, filename, map_type); }
inline BOOL 	MQCDocument::FindMappingFile(wchar_t *out_path, const wchar_t *filename, DWORD map_type) { return MQDoc_FindMappingFileW(this, out_path, filename, map_type); }
inline UINT		MQCDocument::GetUVChannelID(const wchar_t *name){
	MQSendMessageInfo info;
	UINT channel = 0;
	void *array[7] = { (void*)"doc", this, (void*)"name", (void*)name, (void*)"channel", &channel, NULL };
	info.option = array;
	MQ_SendMessage(MQMESSAGE_GET_UVCNANNEL_ID, &info);
	return channel;
}
inline std::wstring MQCDocument::GetUVChannelName(UINT channelID){
	MQSendMessageInfo info;
	int name_size = 0;
	void *array[9] = { (void*)"doc", this, (void*)"channel", &channelID, (void*)"name_size", &name_size, NULL };
	info.option = array;
	MQ_SendMessage(MQMESSAGE_GET_UVCNANNEL_NAME, &info);
	int buffer_size = name_size + 1;
	wchar_t *buffer = (wchar_t*)malloc(buffer_size * sizeof(wchar_t));
	buffer[0] = L'\0';
	array[0] = (void*)"doc"; array[1] = this; array[2] = (void*)"channel"; array[3] = &channelID; array[4] = (void*)"name"; array[5] = buffer; array[6] = (void*)"name_size"; array[7] = &buffer_size; array[8] = NULL;
	MQ_SendMessage(MQMESSAGE_GET_UVCNANNEL_NAME, &info);
	std::wstring ret(buffer);
	free(buffer);
	return ret;
}
inline int MQCDocument::GetMaxUVChannelNum(){
	MQSendMessageInfo info;
	int num = 0;
	void *array[5] = { (void*)"doc", this, (void*)"num", &num, NULL };
	info.option = array;
	MQ_SendMessage(MQMESSAGE_GET_MAX_UVCNANNEL_NUM, &info);
	return num;
}

inline MQScene 	MQCDocument::GetScene(int index) 	{ return MQDoc_GetScene(this, index); }
inline std::wstring MQCDocument::GetEnvironmentMapName()
{
	MQSendMessageInfo info;
	int name_size = 0;
	void *array[7] = { (void*)"doc", this, (void*)"name_size", &name_size, NULL };
	info.option = array;
	MQ_SendMessage(MQMESSAGE_GET_ENVMAP, &info);
	int buffer_size = name_size + 1;
	wchar_t *buffer = (wchar_t*)malloc(buffer_size * sizeof(wchar_t));
	buffer[0] = L'\0';
	array[0] = (void*)"doc"; array[1] = this; array[2] = (void*)"name"; array[3] = buffer; array[4] = (void*)"name_size"; array[5] = &buffer_size; array[6] = NULL;
	MQ_SendMessage(MQMESSAGE_GET_ENVMAP, &info);
	std::wstring ret(buffer);
	free(buffer);
	return ret;

}
inline BOOL MQCDocument::SetEnvironmentMapName(const std::wstring& name, BOOL show_progress)
{
	MQSendMessageInfo info;
	void *array[7] = { (void*)"doc", this, (void*)"name", (void*)name.c_str(), (void*)"progress", &show_progress, NULL };
	info.option = array;
	return MQ_SendMessage(MQMESSAGE_SET_ENVMAP, &info);
}
inline float MQCDocument::GetEnvironmentMapIntensity()
{
	MQSendMessageInfo info;
	float value = 0;
	void *array[5] = { (void*)"doc", this, (void*)"intensity", (void*)&value, NULL };
	info.option = array;
	MQ_SendMessage(MQMESSAGE_GET_ENVMAP, &info);
	return value;
}
inline void MQCDocument::SetEnvironmentMapIntensity(float intensity)
{
	MQSendMessageInfo info;
	void *array[5] = { (void*)"doc", this, (void*)"intensity", (void*)&intensity, NULL };
	info.option = array;
	MQ_SendMessage(MQMESSAGE_SET_ENVMAP, &info);
}
inline float MQCDocument::GetEnvironmentMapRotation()
{
	MQSendMessageInfo info;
	float value = 0;
	void *array[5] = { (void*)"doc", this, (void*)"rotation", (void*)&value, NULL };
	info.option = array;
	MQ_SendMessage(MQMESSAGE_GET_ENVMAP, &info);
	return value;
}
inline void MQCDocument::SetEnvironmentMapRotation(float rotation)
{
	MQSendMessageInfo info;
	void *array[5] = { (void*)"doc", this, (void*)"rotation", (void*)&rotation, NULL };
	info.option = array;
	MQ_SendMessage(MQMESSAGE_SET_ENVMAP, &info);
}
inline BOOL		MQCDocument::GetMappingImageSize(const char *filename, DWORD map_type, int& width, int& height)
{
	int bpp;
	const RGBQUAD *colors;
	const BYTE *buffer;
	return GetMappingImage(filename, map_type, width, height, bpp, colors, buffer);
}
inline BOOL		MQCDocument::GetMappingImageSize(const wchar_t *filename, DWORD map_type, int& width, int& height)
{
	int bpp;
	const RGBQUAD *colors;
	const BYTE *buffer;
	return GetMappingImage(filename, map_type, width, height, bpp, colors, buffer);
}
inline BOOL		MQCDocument::GetMappingImage(const char *filename, DWORD map_type, int& width, int& height, int& bpp, const RGBQUAD*& colors, const BYTE*& buffer)
{
	void *array[5];
	array[0] = &width;
	array[1] = &height;
	array[2] = &bpp;
	array[3] = &colors;
	array[4] = &buffer;

	if(!MQDoc_GetMappingImage(this, filename, map_type, array)){
		width = height = bpp = 0;
		colors = NULL;
		buffer = NULL;
		return FALSE;
	}
	return TRUE;
}
inline BOOL		MQCDocument::GetMappingImage(const wchar_t *filename, DWORD map_type, int& width, int& height, int& bpp, const RGBQUAD*& colors, const BYTE*& buffer)
{
	void *array[5];
	array[0] = &width;
	array[1] = &height;
	array[2] = &bpp;
	array[3] = &colors;
	array[4] = &buffer;

	if(!MQDoc_GetMappingImageW(this, filename, map_type, array)){
		width = height = bpp = 0;
		colors = NULL;
		buffer = NULL;
		return FALSE;
	}
	return TRUE;
}
inline MQObject	MQCDocument::GetParentObject(MQObject obj) 					{ return MQDoc_GetParentObject(this, obj); }
inline int		MQCDocument::GetChildObjectCount(MQObject obj) 				{ return MQDoc_GetChildObjectCount(this, obj); }
inline MQObject	MQCDocument::GetChildObject(MQObject obj, int index) 		{ return MQDoc_GetChildObject(this, obj, index); }
inline void		MQCDocument::GetGlobalMatrix(MQObject obj, MQMatrix& mtx)	{ MQDoc_GetGlobalMatrix(this, obj, mtx.t); }
inline void		MQCDocument::GetGlobalInverseMatrix(MQObject obj, MQMatrix& mtx){ MQDoc_GetGlobalInverseMatrix(this, obj, mtx.t); }
inline int		MQCDocument::InsertObject(MQObject obj, MQObject before)	{ return MQDoc_InsertObject(this, obj, before); }
inline BOOL		MQCDocument::RemoveObject(MQObject obj)	{ return MQDoc_RemoveObject(this, obj); }
inline int MQCDocument::CreateUserData(DWORD productID, DWORD pluginID, const char *identifier, int userdata_type, int bytes_per_object)
{
	MQUserDataInfo info;
	info.dwSize = sizeof(info);
	info.productID = productID;
	info.pluginID = pluginID;
#if _MSC_VER >=1400
	strncpy_s(info.identifier, _countof(info.identifier), identifier, _countof(info.identifier)-1);
#else
	strncpy(info.identifier, identifier, sizeof(info.identifier)-1);
#endif
	info.userdata_type = userdata_type;
	info.bytes_per_element = bytes_per_object;
	info.create = true;
	return MQDoc_CreateUserData(this, &info);
}

inline int MQCDocument::FindUserData(DWORD productID, DWORD pluginID, const char *identifier, int userdata_type)
{
	MQUserDataInfo info;
	info.dwSize = sizeof(info);
	info.productID = productID;
	info.pluginID = pluginID;
#if _MSC_VER >=1400 
	strncpy_s(info.identifier, _countof(info.identifier), identifier, _countof(info.identifier)-1);
#else
	strncpy(info.identifier, identifier, sizeof(info.identifier)-1);
#endif
	info.userdata_type = userdata_type;
	info.bytes_per_element = 0;
	return MQDoc_CreateUserData(this, &info);
}

inline int  	MQCDocument::CreateObjectUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_object) { return CreateUserData(productID, pluginID, identifier, MQUSERDATA_OBJECT, bytes_per_object); }
inline void		MQCDocument::DeleteObjectUserData(int userdata_id) { MQDoc_DeleteUserData(this, MQUSERDATA_OBJECT, userdata_id); }
inline int  	MQCDocument::FindObjectUserData(DWORD productID, DWORD pluginID, const char *identifier) { return FindUserData(productID, pluginID, identifier, MQUSERDATA_OBJECT); }
inline int  	MQCDocument::CreateVertexUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_vertex) { return CreateUserData(productID, pluginID, identifier, MQUSERDATA_VERTEX, bytes_per_vertex); }
inline void		MQCDocument::DeleteVertexUserData(int userdata_id) { MQDoc_DeleteUserData(this, MQUSERDATA_VERTEX, userdata_id); }
inline int  	MQCDocument::FindVertexUserData(DWORD productID, DWORD pluginID, const char *identifier) { return FindUserData(productID, pluginID, identifier, MQUSERDATA_VERTEX); }
inline int  	MQCDocument::CreateFaceUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_face) { return CreateUserData(productID, pluginID, identifier, MQUSERDATA_FACE, bytes_per_face); }
inline void		MQCDocument::DeleteFaceUserData(int userdata_id) { MQDoc_DeleteUserData(this, MQUSERDATA_FACE, userdata_id); }
inline int  	MQCDocument::FindFaceUserData(DWORD productID, DWORD pluginID, const char *identifier) { return FindUserData(productID, pluginID, identifier, MQUSERDATA_FACE); }
inline int  	MQCDocument::CreateMaterialUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_material) { return CreateUserData(productID, pluginID, identifier, MQUSERDATA_MATERIAL, bytes_per_material); }
inline void		MQCDocument::DeleteMaterialUserData(int userdata_id) { MQDoc_DeleteUserData(this, MQUSERDATA_MATERIAL, userdata_id); }
inline int  	MQCDocument::FindMaterialUserData(DWORD productID, DWORD pluginID, const char *identifier) { return FindUserData(productID, pluginID, identifier, MQUSERDATA_MATERIAL); }
inline BOOL  	MQCDocument::Triangulate(const MQPoint *points, int points_num, int *index_array, int index_num) { return MQDoc_Triangulate(this, points, points_num, index_array, index_num); }


// class MQCScene
inline void 	MQCScene::InitSize(int width, int height) 		{ MQScene_InitSize(this, width, height); }
inline void 	MQCScene::GetProjMatrix(float *matrix) 			{ MQScene_GetProjMatrix(this, matrix); }
inline void 	MQCScene::GetViewMatrix(float *matrix) 			{ MQScene_GetViewMatrix(this, matrix); }
inline MQPoint 	MQCScene::GetCameraPosition()					{ float val[3]; MQScene_FloatValue(this,MQSCENE_GET_CAMERA_POS,val); return MQPoint(val[0],val[1],val[2]); }
inline MQAngle 	MQCScene::GetCameraAngle()						{ float val[3]; MQScene_FloatValue(this,MQSCENE_GET_CAMERA_ANGLE,val); return MQAngle(val[0],val[1],val[2]); }
inline MQPoint 	MQCScene::GetLookAtPosition()					{ float val[3]; MQScene_FloatValue(this,MQSCENE_GET_LOOK_AT_POS,val); return MQPoint(val[0],val[1],val[2]); }
inline MQPoint 	MQCScene::GetRotationCenter()					{ float val[3]; MQScene_FloatValue(this,MQSCENE_GET_ROTATION_CENTER,val); return MQPoint(val[0],val[1],val[2]); }
inline float 	MQCScene::GetFOV()								{ float val; MQScene_FloatValue(this,MQSCENE_GET_FOV,&val); return val; }
// OBSOLETE in Rev3.11: Replaced with GetGlobalDirectionalLightDirection()
//inline MQPoint 	MQCScene::GetGlobalDirectionalLight()			{ float val[3]; MQScene_FloatValue(this,MQSCENE_GET_DIRECTIONAL_LIGHT,val); return MQPoint(val[0],val[1],val[2]); }
inline MQColor 	MQCScene::GetGlobalAmbientColor()				{ float val[3]; MQScene_FloatValue(this,MQSCENE_GET_AMBIENT_COLOR,val); return MQColor(val[0],val[1],val[2]); }
inline void 	MQCScene::SetCameraPosition(const MQPoint& p)	{ float val[3]; val[0]=p.x; val[1]=p.y; val[2]=p.z; MQScene_FloatValue(this,MQSCENE_SET_CAMERA_POS,val); }
inline void 	MQCScene::SetCameraAngle(const MQAngle& angle)	{ float val[3]; val[0]=angle.head; val[1]=angle.pich; val[2]=angle.bank; MQScene_FloatValue(this,MQSCENE_SET_CAMERA_ANGLE,val); }
inline void 	MQCScene::SetLookAtPosition(const MQPoint& p)	{ float val[6]; val[0]=p.x; val[1]=p.y; val[2]=p.z; val[3]=0; val[4]=1; val[5]=0; MQScene_FloatValue(this,MQSCENE_SET_LOOK_AT_POS,val); }
inline void 	MQCScene::SetRotationCenter(const MQPoint& p)	{ float val[3]; val[0]=p.x; val[1]=p.y; val[2]=p.z; MQScene_FloatValue(this,MQSCENE_SET_ROTATION_CENTER,val); }
inline void 	MQCScene::SetFOV(float fov)						{ MQScene_FloatValue(this,MQSCENE_SET_FOV,&fov); }
// OBSOLETE in Rev3.11: Replaced with SetGlobalDirectionalLightDirection()
//inline void 	MQCScene::SetGlobalDirectionalLight(const MQPoint& vec)	{ float val[3]; val[0]=vec.x; val[1]=vec.y; val[2]=vec.z; MQScene_FloatValue(this,MQSCENE_SET_DIRECTIONAL_LIGHT,val); }
inline void 	MQCScene::SetGlobalAmbientColor(const MQColor& amb){ float val[3]; val[0]=amb.r; val[1]=amb.g; val[2]=amb.b; MQScene_FloatValue(this,MQSCENE_SET_AMBIENT_COLOR,val); }
inline MQPoint	MQCScene::Convert3DToScreen(const MQPoint& p, float *out_w){
	float val[7];
	val[0]=p.x; val[1]=p.y; val[2]=p.z;
	MQScene_FloatValue(this,MQSCENE_CONVERT_3D_TO_SCREEN,val);
	if (out_w != NULL) *out_w = val[6];
	return MQPoint(val[3],val[4],val[5]);
}
inline MQPoint	MQCScene::ConvertScreenTo3D(const MQPoint& p){
	float val[6];
	val[0]=p.x; val[1]=p.y; val[2]=p.z;
	MQScene_FloatValue(this,MQSCENE_CONVERT_SCREEN_TO_3D,val);
	return MQPoint(val[3],val[4],val[5]);
}
inline BOOL 	MQCScene::GetVisibleFace(MQObject obj, BOOL *visible)	{ return MQScene_GetVisibleFace(this,obj,visible); }
inline int		MQCScene::AddGlobalDirectionalLight()					{ int val[1]; MQScene_IntValue(this,MQSCENE_ADD_MULTILIGHT,val); return val[0]; }
inline BOOL		MQCScene::DeleteGlobalDirectionalLight(int index)		{ int val[2]; val[0]=index; MQScene_IntValue(this,MQSCENE_DELETE_MULTILIGHT,val); return val[1] ? TRUE : FALSE; }
inline int	 	MQCScene::GetGlobalDirectionalLightNum()				{ int val[1]; MQScene_IntValue(this,MQSCENE_GET_MULTILIGHT_NUMBER,val); return val[0]; }
inline MQPoint 	MQCScene::GetGlobalDirectionalLightDirection(int index)	{ float val[3]; MQScene_IntValue(this,MQSCENE_SET_MULTILIGHT_INDEX,&index); MQScene_FloatValue(this,MQSCENE_GET_MULTILIGHT_DIR,val); return MQPoint(val[0],val[1],val[2]); }
inline MQColor	MQCScene::GetGlobalDirectionalLightColor(int index)		{ float val[3]; MQScene_IntValue(this,MQSCENE_SET_MULTILIGHT_INDEX,&index); MQScene_FloatValue(this,MQSCENE_GET_MULTILIGHT_COLOR,val); return MQColor(val[0],val[1],val[2]); }
inline void		MQCScene::SetGlobalDirectionalLightDirection(int index, const MQPoint& dir)			{ float val[3]; MQScene_IntValue(this,MQSCENE_SET_MULTILIGHT_INDEX,&index); val[0]=dir.x; val[1]=dir.y; val[2]=dir.z; MQScene_FloatValue(this,MQSCENE_SET_MULTILIGHT_DIR,val); }
inline void 	MQCScene::SetGlobalDirectionalLightColor(int index, const MQColor& col)	{ float val[3]; MQScene_IntValue(this,MQSCENE_SET_MULTILIGHT_INDEX,&index); val[0]=col.r; val[1]=col.g; val[2]=col.b; MQScene_FloatValue(this,MQSCENE_SET_MULTILIGHT_COLOR,val); }
inline float 	MQCScene::GetFrontZ()							{ float val; MQScene_FloatValue(this,MQSCENE_GET_FRONT_Z,&val); return val; }
inline bool 	MQCScene::GetOrtho()							{ int val=0; MQScene_IntValue(this,MQSCENE_GET_ORTHO,&val); return val!=0; }
inline void 	MQCScene::SetOrtho(bool ortho)					{ int val=ortho?1:0; MQScene_IntValue(this,MQSCENE_SET_ORTHO,&val); }
inline float 	MQCScene::GetZoom()								{ float val=1.0f; MQScene_FloatValue(this,MQSCENE_GET_ZOOM,&val); return val; }
inline void 	MQCScene::SetZoom(float fov)					{ MQScene_FloatValue(this,MQSCENE_SET_ZOOM,&fov); }
inline float 	MQCScene::GetFrontClip()						{ float val=1.0f; MQScene_FloatValue(this,MQSCENE_GET_FRONT_CLIP,&val); return val; }
inline float 	MQCScene::GetBackClip()							{ float val=1.0f; MQScene_FloatValue(this,MQSCENE_GET_BACK_CLIP,&val); return val; }
inline std::wstring MQCScene::GetBackgroundImage()				{wchar_t *nameptr=nullptr; void *args[3]={(void*)"name",&nameptr,NULL}; MQScene_ValueArray(this,MQSCENE_GET_BKIMAGE,args); return nameptr ? std::wstring(nameptr) : std::wstring();}
inline BOOL		MQCScene::SetBackgroundImage(const std::wstring& name) {BOOL result=FALSE; void *args[5]={(void*)"name",name.empty()?nullptr:(void*)name.c_str(),(void*)"result",&result,NULL}; MQScene_ValueArray(this,MQSCENE_SET_BKIMAGE,args); return result; }
inline BOOL		MQCScene::GetBackgroundImagePosition(float& x1, float& y1, float& x2, float& y2, float& rotation) {BOOL result=FALSE; void *args[13]={(void*)"x1",&x1,(void*)"y1",&y1,(void*)"x2",&x2,(void*)"y2",&y2,(void*)"rotation",&rotation,(void*)"result",&result,NULL}; MQScene_ValueArray(this,MQSCENE_GET_BKIMAGE,args); return result; }
inline BOOL		MQCScene::SetBackgroundImagePosition(float x1, float y1, float x2, float y2, float rotation) {BOOL result=FALSE; void *args[13]={(void*)"x1",&x1,(void*)"y1",&y1,(void*)"x2",&x2,(void*)"y2",&y2,(void*)"rotation",&rotation,(void*)"result",&result,NULL}; MQScene_ValueArray(this,MQSCENE_SET_BKIMAGE,args); return result; }

// class MQCObject
inline void 	MQCObject::DeleteThis(void) 					{ MQObj_Delete(this); }
inline MQObject MQCObject::Clone(void) 							{ return MQObj_Clone(this); }
//inline void 	MQCObject::Merge(MQObject source) 				{ MQObj_Merge(this, source); } // OBSOLETE
inline BOOL 	MQCObject::Merge(MQObject source) 				{ BOOL result=FALSE; void *args[5]={(void*)"source",source,(void*)"result",&result,NULL}; MQObj_PointerArray(this,MQOBJ_ID_MERGE,args); return result; }
inline void		MQCObject::Clear(void) 							{ MQObj_Clear(this, 0); }
//inline void 	MQCObject::Freeze(DWORD flag) 					{ MQObj_Freeze(this, flag); } // OBSOLETE
inline BOOL 	MQCObject::Freeze(DWORD flag) 					{ BOOL result=FALSE; void *args[5]={(void*)"flag",&flag,(void*)"result",&result,NULL}; MQObj_PointerArray(this,MQOBJ_ID_FREEZE,args); return result; }
inline int	 	MQCObject::GetName(char *buffer, int size) 		{ int length=0; void *args[3]={buffer,&size,&length}; MQObj_PointerArray(this,MQOBJ_ID_NAME,args); return length; }
inline int	 	MQCObject::GetNameW(wchar_t *buffer, int size) 	{ int length=0; void *args[3]={buffer,&size,&length}; MQObj_PointerArray(this,MQOBJ_ID_NAME_W,args); return length; }
inline std::string MQCObject::GetName() 						{ int length=GetName(NULL,0); if(length == 0) return std::string(); char *buffer = new char[length+1]; GetName(buffer, length+1); std::string ret(buffer); delete[] buffer; return ret; }
inline std::wstring MQCObject::GetNameW() 						{ int length=GetNameW(NULL,0); if(length == 0) return std::wstring(); wchar_t *buffer = new wchar_t[length+1]; GetNameW(buffer, length+1); std::wstring ret(buffer); delete[] buffer; return ret; }
inline int  	MQCObject::GetVertexCount(void) 				{ return MQObj_GetVertexCount(this); }
inline MQPoint 	MQCObject::GetVertex(int index) 				{ MQPoint pts; MQObj_GetVertex(this, index, &pts); return pts; }
inline void 	MQCObject::SetVertex(int index, MQPoint pts) 	{ MQObj_SetVertex(this, index, &pts); }
inline void 	MQCObject::GetVertexArray(MQPoint *ptsarray) 	{ MQObj_GetVertexArray(this, ptsarray); }
inline BOOL  	MQCObject::ReserveVertex(int size)				{ BOOL result=FALSE; void *args[5]={(void*)"size",&size,(void*)"result",&result,NULL}; MQObj_PointerArray(this,MQOBJ_ID_RESERVE_VERTEX,args); return result; }
inline int  	MQCObject::AddVertex(MQPoint p) 					{ return MQObj_AddVertex(this, &p); }
inline BOOL 	MQCObject::DeleteVertex(int index) 					{ return MQObj_DeleteVertex(this, index, TRUE); }
inline int  	MQCObject::GetVertexRefCount(int index) 			{ return MQObj_GetVertexRefCount(this, index); }
inline UINT  	MQCObject::GetVertexUniqueID(int index) 			{ return MQObj_GetVertexUniqueID(this, index); }
inline int  	MQCObject::GetVertexIndexFromUniqueID(UINT unique_id){ return MQObj_GetVertexIndexFromUniqueID(this, unique_id); }
inline int		MQCObject::GetVertexRelatedFaces(int vertex, int *faces){ return MQObj_GetVertexRelatedFaces(this, vertex, faces); }
//inline DWORD 	MQCObject::GetVertexColor(int index) 				{ return MQObj_GetVertexColor(this, index); } // OBSOLETE
//inline void 	MQCObject::SetVertexColor(int index, DWORD color) 	{ MQObj_SetVertexColor(this, index, color); } // OBSOLETE
inline float 	MQCObject::GetVertexWeight(int index) 				{ return MQObj_GetVertexWeight(this, index); }
inline void 	MQCObject::SetVertexWeight(int index, float value) 	{ MQObj_SetVertexWeight(this, index, value); }
inline void 	MQCObject::CopyVertexAttribute(int vert1, MQObject obj2, int vert2) { MQObj_CopyVertexAttribute(this, vert1, obj2, vert2); }
inline int  	MQCObject::GetFaceCount(void) 					{ return MQObj_GetFaceCount(this); }
inline int  	MQCObject::GetFacePointCount(int face) 			{ return MQObj_GetFacePointCount(this, face); }
inline void 	MQCObject::GetFacePointArray(int face, int *vertex) { MQObj_GetFacePointArray(this, face, vertex); }
inline void 	MQCObject::GetFaceCoordinateArray(int face, MQCoordinate *uvarray) { MQObj_GetFaceCoordinateArray(this, face, uvarray); }
inline void 	MQCObject::GetFaceCoordinate(int face, int vertex, MQCoordinate& uv) { MQObj_GetFaceCoordinate(this, face, vertex, uv); }
inline int  	MQCObject::GetFaceMaterial(int face) 				{ return MQObj_GetFaceMaterial(this, face); }
inline UINT  	MQCObject::GetFaceUniqueID(int face) 				{ return MQObj_GetFaceUniqueID(this, face); }
inline int  	MQCObject::GetFaceIndexFromUniqueID(UINT unique_id) { return MQObj_GetFaceIndexFromUniqueID(this, unique_id); }
inline void 	MQCObject::SetName(const char *buffer)		 		{ MQObj_SetName(this, buffer); }
inline void 	MQCObject::SetName(const wchar_t *buffer)		 	{ void *args[1]={(void*)buffer}; MQObj_PointerArray(this,MQOBJ_ID_SET_NAME_W,args); }
inline BOOL  	MQCObject::ReserveFace(int size)				{ BOOL result=FALSE; void *args[5]={(void*)"size",&size,(void*)"result",&result,NULL}; MQObj_PointerArray(this,MQOBJ_ID_RESERVE_FACE,args); return result; }
inline int  	MQCObject::AddFace(int count, int *index) 			{ return MQObj_AddFace(this, count, index); }
inline int  	MQCObject::InsertFace(int face_index, int count, int *vert_index) 	{ return MQObj_InsertFace(this, face_index, count, vert_index); }
inline BOOL 	MQCObject::DeleteFace(int index, bool delete_vertex){ return MQObj_DeleteFace(this, index, delete_vertex); }
inline BOOL 	MQCObject::InvertFace(int index) 					{ return MQObj_InvertFace(this, index); }
inline void 	MQCObject::SetFaceMaterial(int face, int material) 	{ MQObj_SetFaceMaterial(this, face, material); }
inline void 	MQCObject::SetFaceCoordinateArray(int face, MQCoordinate *uvarray) { MQObj_SetFaceCoordinateArray(this, face, uvarray); }
inline void 	MQCObject::SetFaceCoordinate(int face, int vertex, const MQCoordinate& uv) { MQObj_SetFaceCoordinate(this, face, vertex, uv); }
inline DWORD  	MQCObject::GetFaceVertexColor(int face, int vertex) 				{ return MQObj_GetFaceVertexColor(this, face, vertex); }
inline void  	MQCObject::SetFaceVertexColor(int face, int vertex, DWORD color) 	{ MQObj_SetFaceVertexColor(this, face, vertex, color); }
inline float 	MQCObject::GetFaceEdgeCrease(int face, int line)               { return MQObj_GetFaceEdgeCrease(this, face, line ); }
inline void		MQCObject::SetFaceEdgeCrease(int face, int line, float crease) { MQObj_SetFaceEdgeCrease(this, face, line, crease); }
inline void 	MQCObject::UpdateNormal()		 			{ MQObj_PointerArray(this,MQOBJ_ID_UPDATE_NORMAL,nullptr); }
inline void 	MQCObject::GetFaceVertexNormal(int face, int vertex, BYTE &flag, MQPoint &normal){ MQObj_GetFaceVertexNormal(this, face, vertex, flag, normal); }
inline void		MQCObject::SetFaceVertexNormal(int face, int vertex, BYTE flag, MQPoint normal)	{ MQObj_SetFaceVertexNormal(this, face, vertex, flag, normal); }
inline BOOL  	MQCObject::GetFaceVisible(int face) 				{ return MQObj_GetFaceVisible(this, face); }
inline void  	MQCObject::SetFaceVisible(int face, BOOL flag) 		{ MQObj_SetFaceVisible(this, face, flag); }
inline int		MQCObject::GetUVChannelNum()						{ int num=0; void *args[3]={(void*)"number",&num,NULL}; MQObj_PointerArray(this,MQOBJ_ID_GET_UV_CHANNEL,args); return num; }
inline bool		MQCObject::GetUVChannel(int index, UINT& channelID) { channelID=0; void *args[5]={(void*)"index",&index,(void*)"channel",&channelID,NULL}; MQObj_PointerArray(this,MQOBJ_ID_GET_UV_CHANNEL,args); return channelID>=0; }
inline bool		MQCObject::ActivateUVChannel(UINT channelID)		{ BOOL result=FALSE; void *args[5]={(void*)"channel",&channelID,(void*)"result",&result,NULL}; MQObj_PointerArray(this,MQOBJ_ID_ACTIVATE_UV_CHANNEL,args); return result != FALSE; }
inline UINT		MQCObject::GetActiveUVChannel()						{ UINT channelID=0; void *args[3]={(void*)"channel",&channelID,NULL}; MQObj_PointerArray(this,MQOBJ_ID_GET_ACTIVE_UV_CHANNEL,args); return channelID; }
inline bool		MQCObject::AddUVChannel(UINT channelID)				{ BOOL result=FALSE; void *args[5]={(void*)"channel",&channelID,(void*)"result",&result,NULL}; MQObj_PointerArray(this,MQOBJ_ID_ADD_UV_CHANNEL,args); return result != FALSE; }
inline bool		MQCObject::DeleteUVChannel(UINT channelID)			{ BOOL result=FALSE; void *args[5]={(void*)"channel",&channelID,(void*)"result",&result,NULL}; MQObj_PointerArray(this,MQOBJ_ID_DELETE_UV_CHANNEL,args); return result != FALSE; }
inline bool		MQCObject::GetFaceChannelCoordinate(int face, int vertex, UINT channelID, MQCoordinate& uv) { BOOL result = MQObj_GetFaceChannelCoordinate(this, face, vertex, channelID, uv); return result != FALSE; }
inline bool		MQCObject::SetFaceChannelCoordinate(int face, int vertex, UINT channelID, const MQCoordinate& uv){ BOOL result = MQObj_SetFaceChannelCoordinate(this, face, vertex, channelID, uv); return result != FALSE; }
inline void 	MQCObject::OptimizeVertex(float distance, MQBool *apply) { MQObj_OptimizeVertex(this, distance, apply); }
inline BOOL 	MQCObject::OptimizeVertex(float distance, MQBool *apply, bool callback(float,void*), void *callback_data) {
	BOOL result=FALSE; void *args[11]={(void*)"distance",&distance,(void*)"apply",apply,(void*)"callback",(void*)callback,(void*)"callback_data",callback_data,(void*)"result",&result,NULL}; MQObj_PointerArray(this,MQOBJ_ID_OPTIMIZE,args); return result; }
inline void 	MQCObject::Compact(void) 					{ MQObj_Compact(this); }
inline DWORD 	MQCObject::GetVisible(void) 				{ return MQObj_GetVisible(this); }
inline void 	MQCObject::SetVisible(DWORD visible)	 	{ MQObj_SetVisible(this, visible); }
inline DWORD 	MQCObject::GetPatchType(void) 				{ return MQObj_GetPatchType(this); }
inline void 	MQCObject::SetPatchType(DWORD type) 		{ MQObj_SetPatchType(this, type); }
inline int  	MQCObject::GetPatchSegment(void) 			{ return MQObj_GetPatchSegment(this); }
inline void 	MQCObject::SetPatchSegment(int segment) 	{ MQObj_SetPatchSegment(this, segment); }
inline BOOL		MQCObject::GetPatchTriangle(void)			{ return MQObj_GetIntValue(this, MQOBJ_ID_PATCH_TRIANGLE) != 0 ? TRUE : FALSE; }
inline void		MQCObject::SetPatchTriangle(BOOL flag)      { MQObj_SetIntValue(this, MQOBJ_ID_PATCH_TRIANGLE, flag ? 1 : 0); }
inline BOOL		MQCObject::GetPatchSmoothTriangle(void)		{ return MQObj_GetIntValue(this, MQOBJ_ID_PATCH_SMOOTH_TRIANGLE) != 0 ? TRUE : FALSE; }
inline void		MQCObject::SetPatchSmoothTriangle(BOOL flag){ MQObj_SetIntValue(this, MQOBJ_ID_PATCH_SMOOTH_TRIANGLE, flag ? 1 : 0); }
inline BOOL		MQCObject::GetPatchLimitSurface(void)		{ return MQObj_GetIntValue(this, MQOBJ_ID_PATCH_LIMIT_SURFACE) != 0 ? TRUE : FALSE; }
inline void		MQCObject::SetPatchLimitSurface(BOOL flag)	{ MQObj_SetIntValue(this, MQOBJ_ID_PATCH_LIMIT_SURFACE, flag ? 1 : 0); }
inline int		MQCObject::GetPatchMeshInterp(void)			{ return MQObj_GetIntValue(this, MQOBJ_ID_PATCH_MESH_INTERP); }
inline void		MQCObject::SetPatchMeshInterp(int interp)	{ MQObj_SetIntValue(this, MQOBJ_ID_PATCH_MESH_INTERP, interp); }
inline int		MQCObject::GetPatchUVInterp(void)			{ return MQObj_GetIntValue(this, MQOBJ_ID_PATCH_UV_INTERP); }
inline void		MQCObject::SetPatchUVInterp(int interp)		{ MQObj_SetIntValue(this, MQOBJ_ID_PATCH_UV_INTERP, interp); }
inline int  	MQCObject::GetShading(void) 			{ return MQObj_GetShading(this); }
inline void 	MQCObject::SetShading(int type) 		{ MQObj_SetShading(this, type); }
inline float 	MQCObject::GetSmoothAngle(void) 		{ return MQObj_GetSmoothAngle(this); }
inline void 	MQCObject::SetSmoothAngle(float degree) { MQObj_SetSmoothAngle(this, degree); }
inline int  	MQCObject::GetMirrorType(void) 			{ return MQObj_GetMirrorType(this); }
inline void 	MQCObject::SetMirrorType(int type) 		{ MQObj_SetMirrorType(this, type); }
inline DWORD 	MQCObject::GetMirrorAxis(void) 			{ return MQObj_GetMirrorAxis(this); }
inline void 	MQCObject::SetMirrorAxis(DWORD axis) 	{ MQObj_SetMirrorAxis(this, axis); }
inline float 	MQCObject::GetMirrorDistance(void) 		{ return MQObj_GetMirrorDistance(this); }
inline void 	MQCObject::SetMirrorDistance(float dis) { MQObj_SetMirrorDistance(this, dis); }
inline int  	MQCObject::GetLatheType(void) 			{ return MQObj_GetLatheType(this); }
inline void 	MQCObject::SetLatheType(int type) 		{ MQObj_SetLatheType(this, type); }
inline DWORD 	MQCObject::GetLatheAxis(void) 			{ return MQObj_GetLatheAxis(this); }
inline void 	MQCObject::SetLatheAxis(DWORD axis) 	{ MQObj_SetLatheAxis(this, axis); }
inline int  	MQCObject::GetLatheSegment(void) 		{ return MQObj_GetLatheSegment(this); }
inline void 	MQCObject::SetLatheSegment(int segment) { MQObj_SetLatheSegment(this, segment); }
inline UINT		MQCObject::GetUniqueID(void) 			{ return (UINT)MQObj_GetIntValue(this, MQOBJ_ID_UNIQUE_ID); }
inline int		MQCObject::GetDepth(void) 				{ return MQObj_GetIntValue(this, MQOBJ_ID_DEPTH); }
inline void		MQCObject::SetDepth(int depth) 			{ MQObj_SetIntValue(this, MQOBJ_ID_DEPTH, depth); }
inline BOOL		MQCObject::GetFolding(void) 			{ return MQObj_GetIntValue(this, MQOBJ_ID_FOLDING) ? TRUE : FALSE; }
inline void		MQCObject::SetFolding(BOOL flag) 		{ MQObj_SetIntValue(this, MQOBJ_ID_FOLDING, flag ? 1 : 0); }
inline BOOL		MQCObject::GetLocking(void) 			{ return MQObj_GetIntValue(this, MQOBJ_ID_LOCKING) ? TRUE : FALSE; }
inline void		MQCObject::SetLocking(BOOL flag) 		{ MQObj_SetIntValue(this, MQOBJ_ID_LOCKING, flag ? 1 : 0); }
inline MQColor	MQCObject::GetColor(void) 				{ float val[3]; MQObj_GetFloatArray(this, MQOBJ_ID_COLOR, val); return MQColor(val[0],val[1],val[2]); }
inline void		MQCObject::SetColor(MQColor color) 		{ float val[3]; val[0]=color.r; val[1]=color.g; val[2]=color.b; MQObj_SetFloatArray(this, MQOBJ_ID_COLOR, val); }
inline BOOL		MQCObject::GetColorValid(void) 			{ return MQObj_GetIntValue(this, MQOBJ_ID_COLOR_VALID) ? TRUE : FALSE; }
inline void		MQCObject::SetColorValid(BOOL flag) 	{ MQObj_SetIntValue(this, MQOBJ_ID_COLOR_VALID, flag); }
inline MQPoint	MQCObject::GetScaling(void) 			{ float val[3]; MQObj_GetFloatArray(this, MQOBJ_ID_SCALING, val); return MQPoint(val[0],val[1],val[2]); }
inline void		MQCObject::SetScaling(MQPoint scale) 	{ float val[3]; val[0]=scale.x; val[1]=scale.y; val[2]=scale.z; MQObj_SetFloatArray(this, MQOBJ_ID_SCALING, val); }
inline MQAngle	MQCObject::GetRotation(void) 			{ float val[3]; MQObj_GetFloatArray(this, MQOBJ_ID_ROTATION, val); return MQAngle(val[0],val[1],val[2]); }
inline void		MQCObject::SetRotation(MQAngle angle) 	{ float val[3]; val[0]=angle.head; val[1]=angle.pich; val[2]=angle.bank; MQObj_SetFloatArray(this, MQOBJ_ID_ROTATION, val); }
inline MQPoint	MQCObject::GetTranslation(void) 		{ float val[3]; MQObj_GetFloatArray(this, MQOBJ_ID_TRANSLATION, val); return MQPoint(val[0],val[1],val[2]); }
inline void		MQCObject::SetTranslation(MQPoint trans){ float val[3]; val[0]=trans.x; val[1]=trans.y; val[2]=trans.z; MQObj_SetFloatArray(this, MQOBJ_ID_TRANSLATION, val); }
inline MQMatrix	MQCObject::GetLocalMatrix(void) 		{ MQMatrix mtx; MQObj_GetFloatArray(this, MQOBJ_ID_LOCAL_MATRIX, mtx.t); return mtx; }
inline void		MQCObject::SetLocalMatrix(const MQMatrix& mtx)	{ MQObj_SetFloatArray(this, MQOBJ_ID_LOCAL_MATRIX, mtx.t); }
inline MQMatrix	MQCObject::GetLocalInverseMatrix(void)	{ MQMatrix mtx; MQObj_GetFloatArray(this, MQOBJ_ID_LOCAL_INVERSE_MATRIX, mtx.t); return mtx; }
inline int		MQCObject::GetType(void)				{ return MQObj_GetIntValue(this, MQOBJ_ID_TYPE); }
inline void		MQCObject::SetType(int type)            { MQObj_SetIntValue(this, MQOBJ_ID_TYPE, type); }
inline float	MQCObject::GetLightValue(void)          { float val[1]; MQObj_GetFloatArray(this, MQOBJ_ID_LIGHT_VALUE, val); return val[0]; }
inline void		MQCObject::SetLightValue(float value)   { float val[1]; val[0]=value; MQObj_SetFloatArray(this, MQOBJ_ID_LIGHT_VALUE, val); }
inline int		MQCObject::GetLightAttenuation(void) 	{ return MQObj_GetIntValue(this, MQOBJ_ID_LIGHT_ATTENUATION); }
inline void		MQCObject::SetLightAttenuation(int value)		{ MQObj_SetIntValue(this, MQOBJ_ID_LIGHT_ATTENUATION, value); }
inline float	MQCObject::GetLightFallOffEnd(void)		{ float val[1]; MQObj_GetFloatArray(this, MQOBJ_ID_LIGHT_FALLOFF_END, val); return val[0]; }
inline void		MQCObject::SetLightFallOffEnd(float distance)	{ float val[1]; val[0]=distance; MQObj_SetFloatArray(this, MQOBJ_ID_LIGHT_FALLOFF_END, val); }
inline float	MQCObject::GetLightFallOffHalf(void)	{ float val[1]; MQObj_GetFloatArray(this, MQOBJ_ID_LIGHT_FALLOFF_HALF, val); return val[0]; }
inline void		MQCObject::SetLightFallOffHalf(float distance)	{ float val[1]; val[0]=distance; MQObj_SetFloatArray(this, MQOBJ_ID_LIGHT_FALLOFF_HALF, val); }
inline BOOL		MQCObject::GetSelected()					{ return MQObj_GetIntValue(this, MQOBJ_ID_SELECTED); }
inline void		MQCObject::SetSelected(BOOL flag)			{ MQObj_SetIntValue(this, MQOBJ_ID_SELECTED, flag); }
inline BOOL		MQCObject::AllocUserData(int userdata_id) { return MQObj_AllocUserData(this, userdata_id); }
inline void 	MQCObject::FreeUserData(int userdata_id)	{ MQObj_FreeUserData(this, userdata_id); }
inline BOOL 	MQCObject::GetUserData(int userdata_id, void *buffer)       { return MQObj_GetUserData(this, userdata_id, 0, 0, buffer); }
inline BOOL 	MQCObject::GetUserDataPart(int userdata_id, int offset, int copy_bytes, void *buffer)       { return MQObj_GetUserData(this, userdata_id, offset, copy_bytes, buffer); }
inline BOOL 	MQCObject::SetUserData(int userdata_id, const void *buffer) { return MQObj_SetUserData(this, userdata_id, 0, 0, buffer); }
inline BOOL 	MQCObject::SetUserDataPart(int userdata_id, int offset, int copy_bytes, const void *buffer) { return MQObj_SetUserData(this, userdata_id, offset, copy_bytes, buffer); }
inline BOOL		MQCObject::AllocVertexUserData(int userdata_id) { return MQObj_AllocVertexUserData(this, userdata_id); }
inline void 	MQCObject::FreeVertexUserData(int userdata_id)	{ MQObj_FreeVertexUserData(this, userdata_id); }
inline BOOL 	MQCObject::GetVertexUserData(int userdata_id, int vertex_index, void *buffer)       { return MQObj_GetVertexUserData(this, userdata_id, vertex_index, 1, 0, 0, buffer); }
inline BOOL 	MQCObject::GetVertexUserDataPart(int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, void *buffer)       { return MQObj_GetVertexUserData(this, userdata_id, vertex_start_index, copy_vertex_num, offset, copy_bytes, buffer); }
inline BOOL 	MQCObject::SetVertexUserData(int userdata_id, int vertex_index, const void *buffer) { return MQObj_SetVertexUserData(this, userdata_id, vertex_index, 1, 0, 0, buffer); }
inline BOOL 	MQCObject::SetVertexUserDataPart(int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, const void *buffer) { return MQObj_SetVertexUserData(this, userdata_id, vertex_start_index, copy_vertex_num, offset, copy_bytes, buffer); }
inline BOOL		MQCObject::AllocFaceUserData(int userdata_id) { return MQObj_AllocFaceUserData(this, userdata_id); }
inline void 	MQCObject::FreeFaceUserData(int userdata_id)  { MQObj_FreeFaceUserData(this, userdata_id); }
inline BOOL 	MQCObject::GetFaceUserData(int userdata_id, int face_index, void *buffer)       { return MQObj_GetFaceUserData(this, userdata_id, face_index, 1, 0, 0, buffer); }
inline BOOL 	MQCObject::GetFaceUserDataPart(int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, void *buffer) { return MQObj_GetFaceUserData(this, userdata_id, face_start_index, copy_face_num, offset, copy_bytes, buffer); }
inline BOOL 	MQCObject::SetFaceUserData(int userdata_id, int face_index, const void *buffer) { return MQObj_SetFaceUserData(this, userdata_id, face_index, 1, 0, 0, buffer); }
inline BOOL 	MQCObject::SetFaceUserDataPart(int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, const void *buffer) { return MQObj_SetFaceUserData(this, userdata_id, face_start_index, copy_face_num, offset, copy_bytes, buffer); }
inline void 	MQCObject::AddRenderFlag(MQOBJECT_RENDER_FLAG flag){
	void *ptr[2];
	switch(flag){
	case MQOBJECT_RENDER_POINT: ptr[0] = (void*)"point"; break;
	case MQOBJECT_RENDER_LINE: ptr[0] = (void*)"line"; break;
	case MQOBJECT_RENDER_FACE: ptr[0] = (void*)"face"; break;
	case MQOBJECT_RENDER_OVERWRITELINE: ptr[0] = (void*)"overwriteline"; break;
	case MQOBJECT_RENDER_OVERWRITEFACE: ptr[0] = (void*)"overwriteface"; break;
	case MQOBJECT_RENDER_ALPHABLEND: ptr[0] = (void*)"alphablend"; break;
	case MQOBJECT_RENDER_MULTILIGHT: ptr[0] = (void*)"multilight"; break;
	case MQOBJECT_RENDER_SHADOW: ptr[0] = (void*)"shadow"; break;
	case MQOBJECT_RENDER_TEXTURE: ptr[0] = (void*)"texture"; break;
	case MQOBJECT_RENDER_VERTEXCOLOR: ptr[0] = (void*)"vcol"; break;
	case MQOBJECT_RENDER_VERTEXCOLORPOINT: ptr[0] = (void*)"vcolpoint"; break;
	case MQOBJECT_RENDER_EDGECOLOR: ptr[0] = (void*)"edgecolor"; break;
	case MQOBJECT_RENDER_SCREEN: ptr[0] = (void*)"screen"; break;
	}
	ptr[1] = NULL;
	MQObj_PointerArray(this, MQOBJ_ID_ADD_RENDER_FLAG, ptr);
}
inline void 	MQCObject::RemoveRenderFlag(MQOBJECT_RENDER_FLAG flag){
	void *ptr[2];
	switch(flag){
	case MQOBJECT_RENDER_POINT: ptr[0] = (void*)"point"; break;
	case MQOBJECT_RENDER_LINE: ptr[0] = (void*)"line"; break;
	case MQOBJECT_RENDER_FACE: ptr[0] = (void*)"face"; break;
	case MQOBJECT_RENDER_OVERWRITELINE: ptr[0] = (void*)"overwriteline"; break;
	case MQOBJECT_RENDER_OVERWRITEFACE: ptr[0] = (void*)"overwriteface"; break;
	case MQOBJECT_RENDER_ALPHABLEND: ptr[0] = (void*)"alphablend"; break;
	case MQOBJECT_RENDER_MULTILIGHT: ptr[0] = (void*)"multilight"; break;
	case MQOBJECT_RENDER_SHADOW: ptr[0] = (void*)"shadow"; break;
	case MQOBJECT_RENDER_TEXTURE: ptr[0] = (void*)"texture"; break;
	case MQOBJECT_RENDER_VERTEXCOLOR: ptr[0] = (void*)"vcol"; break;
	case MQOBJECT_RENDER_VERTEXCOLORPOINT: ptr[0] = (void*)"vcolpoint"; break;
	case MQOBJECT_RENDER_EDGECOLOR: ptr[0] = (void*)"edgecolor"; break;
	case MQOBJECT_RENDER_SCREEN: ptr[0] = (void*)"screen"; break;
	}
	ptr[1] = NULL;
	MQObj_PointerArray(this, MQOBJ_ID_REMOVE_RENDER_FLAG, ptr);
}
inline void MQCObject::AddRenderEraseFlag(MQOBJECT_RENDER_FLAG flag){
	void *ptr[2];
	switch(flag){
	case MQOBJECT_RENDER_POINT: ptr[0] = (void*)"point"; break;
	case MQOBJECT_RENDER_LINE: ptr[0] = (void*)"line"; break;
	case MQOBJECT_RENDER_FACE: ptr[0] = (void*)"face"; break;
	case MQOBJECT_RENDER_OVERWRITELINE: ptr[0] = (void*)"overwriteline"; break;
	case MQOBJECT_RENDER_OVERWRITEFACE: ptr[0] = (void*)"overwriteface"; break;
	case MQOBJECT_RENDER_ALPHABLEND: ptr[0] = (void*)"alphablend"; break;
	case MQOBJECT_RENDER_MULTILIGHT: ptr[0] = (void*)"multilight"; break;
	case MQOBJECT_RENDER_SHADOW: ptr[0] = (void*)"shadow"; break;
	case MQOBJECT_RENDER_TEXTURE: ptr[0] = (void*)"texture"; break;
	case MQOBJECT_RENDER_VERTEXCOLOR: ptr[0] = (void*)"vcol"; break;
	case MQOBJECT_RENDER_VERTEXCOLORPOINT: ptr[0] = (void*)"vcolpoint"; break;
	case MQOBJECT_RENDER_EDGECOLOR: ptr[0] = (void*)"edgecolor"; break;
	case MQOBJECT_RENDER_SCREEN: ptr[0] = (void*)"screen"; break;
	}
	ptr[1] = NULL;
	MQObj_PointerArray(this, MQOBJ_ID_ADD_ERASE_FLAG, ptr);
}
inline void MQCObject::RemoveRenderEraseFlag(MQOBJECT_RENDER_FLAG flag){
	void *ptr[2];
	switch(flag){
	case MQOBJECT_RENDER_POINT: ptr[0] = (void*)"point"; break;
	case MQOBJECT_RENDER_LINE: ptr[0] = (void*)"line"; break;
	case MQOBJECT_RENDER_FACE: ptr[0] = (void*)"face"; break;
	case MQOBJECT_RENDER_OVERWRITELINE: ptr[0] = (void*)"overwriteline"; break;
	case MQOBJECT_RENDER_OVERWRITEFACE: ptr[0] = (void*)"overwriteface"; break;
	case MQOBJECT_RENDER_ALPHABLEND: ptr[0] = (void*)"alphablend"; break;
	case MQOBJECT_RENDER_MULTILIGHT: ptr[0] = (void*)"multilight"; break;
	case MQOBJECT_RENDER_SHADOW: ptr[0] = (void*)"shadow"; break;
	case MQOBJECT_RENDER_TEXTURE: ptr[0] = (void*)"texture"; break;
	case MQOBJECT_RENDER_VERTEXCOLOR: ptr[0] = (void*)"vcol"; break;
	case MQOBJECT_RENDER_VERTEXCOLORPOINT: ptr[0] = (void*)"vcolpoint"; break;
	case MQOBJECT_RENDER_EDGECOLOR: ptr[0] = (void*)"edgecolor"; break;
	case MQOBJECT_RENDER_SCREEN: ptr[0] = (void*)"screen"; break;
	}
	ptr[1] = NULL;
	MQObj_PointerArray(this, MQOBJ_ID_REMOVE_ERASE_FLAG, ptr);
}

// class MQCMaterial
inline void 	MQCMaterial::DeleteThis(void) 					{ MQMat_Delete(this); }
inline MQMaterial MQCMaterial::Clone(void) 						{ void *array[1]={nullptr}; MQMat_GetValueArray(this, MQMAT_ID_CLONE, array); return (MQMaterial)array[0]; }
inline int		MQCMaterial::GetName(char *buffer, int size) 	{ int length=0; void *array[3] = {buffer,&size,&length}; MQMat_GetValueArray(this, MQMAT_ID_NAME, array); return length; }
inline int		MQCMaterial::GetNameW(wchar_t *buffer, int size){ int length=0; void *array[3] = {buffer,&size,&length}; MQMat_GetValueArray(this, MQMAT_ID_NAME_W, array); return length; }
inline std::string MQCMaterial::GetName() 						{ int length=GetName(NULL,0); if(length == 0) return std::string(); char *buffer = new char[length+1]; GetName(buffer, length+1); std::string ret(buffer); delete[] buffer; return ret; }
inline std::wstring MQCMaterial::GetNameW() 					{ int length=GetNameW(NULL,0); if(length == 0) return std::wstring(); wchar_t *buffer = new wchar_t[length+1]; GetNameW(buffer, length+1); std::wstring ret(buffer); delete[] buffer; return ret; }
inline UINT 	MQCMaterial::GetUniqueID(void) 					{ return (UINT)MQMat_GetIntValue(this, MQMAT_ID_UNIQUE_ID); }
inline int 		MQCMaterial::GetShader(void) 					{ return MQMat_GetIntValue(this, MQMAT_ID_SHADER); }
inline int 		MQCMaterial::GetVertexColor(void) 				{ return MQMat_GetIntValue(this, MQMAT_ID_VERTEXCOLOR); }
inline BOOL		MQCMaterial::GetSelected()						{ return MQMat_GetIntValue(this, MQMAT_ID_SELECTED); }
inline BOOL		MQCMaterial::GetDoubleSided(void) 				{ return MQMat_GetIntValue(this, MQMAT_ID_DOUBLESIDED) != 0 ? TRUE : FALSE; }
inline MQColor 	MQCMaterial::GetColor(void) 			{ MQColor color; MQMat_GetColor(this, &color); return color; }
inline float 	MQCMaterial::GetAlpha(void) 			{ return MQMat_GetAlpha(this); }
inline float 	MQCMaterial::GetDiffuse(void) 			{ return MQMat_GetDiffuse(this); }
inline MQColor 	MQCMaterial::GetAmbientColor(void) 		{ float val[3]; MQMat_GetFloatArray(this, MQMAT_ID_AMBIENT_COLOR, val); return MQColor(val[0], val[1], val[2]); }
inline MQColor 	MQCMaterial::GetEmissionColor(void) 	{ float val[3]; MQMat_GetFloatArray(this, MQMAT_ID_EMISSION_COLOR, val); return MQColor(val[0], val[1], val[2]); }
inline MQColor 	MQCMaterial::GetSpecularColor(void) 	{ float val[3]; MQMat_GetFloatArray(this, MQMAT_ID_SPECULAR_COLOR, val); return MQColor(val[0], val[1], val[2]); }
inline float 	MQCMaterial::GetAmbient(void) 			{ return MQMat_GetAmbient(this); }
inline float 	MQCMaterial::GetEmission(void) 			{ return MQMat_GetEmission(this); }
inline float 	MQCMaterial::GetSpecular(void) 			{ return MQMat_GetSpecular(this); }
inline float 	MQCMaterial::GetPower(void) 			{ return MQMat_GetPower(this); }
inline float 	MQCMaterial::GetReflection(void) 		{ float val[1]; MQMat_GetFloatArray(this, MQMAT_ID_REFLECTION, val); return val[0]; }
inline float 	MQCMaterial::GetRefraction(void) 		{ float val[1]; MQMat_GetFloatArray(this, MQMAT_ID_REFRACTION, val); return val[0]; }
inline int 		MQCMaterial::GetMappingType(void) 		{ return MQMat_GetIntValue(this, MQMAT_ID_MAPPROJ); }
inline MQPoint 	MQCMaterial::GetMappingPosition(void) 	{ float val[3]; MQMat_GetFloatArray(this, MQMAT_ID_MAPPROJ_POSITION, val); return MQPoint(val[0], val[1], val[2]); }
inline MQPoint 	MQCMaterial::GetMappingScaling(void) 	{ float val[3]; MQMat_GetFloatArray(this, MQMAT_ID_MAPPROJ_SCALING,  val); return MQPoint(val[0], val[1], val[2]); }
inline MQAngle 	MQCMaterial::GetMappingAngle(void) 		{ float val[3]; MQMat_GetFloatArray(this, MQMAT_ID_MAPPROJ_ANGLE,    val); return MQAngle(val[0], val[1], val[2]); }
inline int	 	MQCMaterial::GetWrapModeU(void) 		{ return MQMat_GetIntValue(this, MQMAT_ID_MAPWRAPU); }
inline int	 	MQCMaterial::GetWrapModeV(void) 		{ return MQMat_GetIntValue(this, MQMAT_ID_MAPWRAPV); }
inline int	 	MQCMaterial::GetMappingFilter(void) 		{ return MQMat_GetIntValue(this, MQMAT_ID_MAPFILTER); }
inline void 	MQCMaterial::GetTextureName(char *buffer, int size) { MQMat_GetTextureName(this, buffer, size); }
inline std::string MQCMaterial::GetTextureName() { char path[MQ_MAX_PATH]={'\0'}; GetTextureName(path, MQ_MAX_PATH); return std::string(path); }
inline int		MQCMaterial::GetTextureNameW(wchar_t *buffer, int size) { int length=0; void *array[3] = {buffer,&size,&length}; MQMat_GetValueArray(this, MQMAT_ID_TEXTURE_NAME_W, array); return length; }
inline std::wstring MQCMaterial::GetTextureNameW() { wchar_t path[MQ_MAX_PATH]={L'\0'}; GetTextureNameW(path, MQ_MAX_PATH); return std::wstring(path); }
inline void 	MQCMaterial::GetAlphaName(char *buffer, int size) 	{ MQMat_GetAlphaName(this, buffer, size); }
inline std::string MQCMaterial::GetAlphaName() { char path[MQ_MAX_PATH]={'\0'}; GetAlphaName(path, MQ_MAX_PATH); return std::string(path); }
inline int		MQCMaterial::GetAlphaNameW(wchar_t *buffer, int size) 	{ int length=0; void *array[3] = {buffer,&size,&length}; MQMat_GetValueArray(this, MQMAT_ID_ALPHA_NAME_W, array); return length; }
inline std::wstring MQCMaterial::GetAlphaNameW() { wchar_t path[MQ_MAX_PATH]={L'\0'}; GetAlphaNameW(path, MQ_MAX_PATH); return std::wstring(path); }
inline void 	MQCMaterial::GetBumpName(char *buffer, int size) 	{ MQMat_GetBumpName(this, buffer, size); }
inline std::string MQCMaterial::GetBumpName() { char path[MQ_MAX_PATH]={'\0'}; GetBumpName(path, MQ_MAX_PATH); return std::string(path); }
inline int		MQCMaterial::GetBumpNameW(wchar_t *buffer, int size) 	{ int length=0; void *array[3] = {buffer,&size,&length}; MQMat_GetValueArray(this, MQMAT_ID_BUMP_NAME_W, array); return length; }
inline std::wstring MQCMaterial::GetBumpNameW() { wchar_t path[MQ_MAX_PATH]={L'\0'}; GetBumpNameW(path, MQ_MAX_PATH); return std::wstring(path); }
inline UINT		MQCMaterial::GetTextureUVChannel()		{ return (UINT)MQMat_GetIntValue(this, MQMAT_ID_TEXTURE_UVCHANNEL); }
inline UINT		MQCMaterial::GetAlphaUVChannel()		{ return (UINT)MQMat_GetIntValue(this, MQMAT_ID_ALPHA_UVCHANNEL); }
inline UINT		MQCMaterial::GetBumpUVChannel()		{ return (UINT)MQMat_GetIntValue(this, MQMAT_ID_BUMP_UVCHANNEL); }
inline void 	MQCMaterial::SetName(const char *name) 				{ MQMat_SetName(this, name); }
inline void 	MQCMaterial::SetName(const wchar_t *name) 			{ void *array[1] = {(void*)name}; MQMat_SetValueArray(this, MQMAT_ID_NAME_W, array); }
inline void 	MQCMaterial::SetShader(int shader) 		{ MQMat_SetIntValue(this, MQMAT_ID_SHADER, shader); }
inline void 	MQCMaterial::SetVertexColor(int value) 	{ MQMat_SetIntValue(this, MQMAT_ID_VERTEXCOLOR, value); }
inline void		MQCMaterial::SetSelected(BOOL flag)		{ MQMat_SetIntValue(this, MQMAT_ID_SELECTED, flag); }
inline void 	MQCMaterial::SetDoubleSided(BOOL value) { MQMat_SetIntValue(this, MQMAT_ID_DOUBLESIDED, value ? 1: 0); }
inline void 	MQCMaterial::SetColor(MQColor color) 	{ MQMat_SetColor(this, &color); }
inline void 	MQCMaterial::SetAlpha(float value) 		{ MQMat_SetAlpha(this, value); }
inline void 	MQCMaterial::SetDiffuse(float value) 	{ MQMat_SetDiffuse(this, value); }
inline void 	MQCMaterial::SetAmbient(float value) 	{ MQMat_SetAmbient(this, value); }
inline void 	MQCMaterial::SetEmission(float value) 	{ MQMat_SetEmission(this, value); }
inline void 	MQCMaterial::SetSpecular(float value) 	{ MQMat_SetSpecular(this, value); }
inline void 	MQCMaterial::SetPower(float value) 		{ MQMat_SetPower(this, value); }
inline void 	MQCMaterial::SetAmbientColor(MQColor color) 	{ float val[3] = {color.r, color.g, color.b}; MQMat_SetFloatArray(this, MQMAT_ID_AMBIENT_COLOR, val); }
inline void 	MQCMaterial::SetEmissionColor(MQColor color) 	{ float val[3] = {color.r, color.g, color.b}; MQMat_SetFloatArray(this, MQMAT_ID_EMISSION_COLOR, val); }
inline void 	MQCMaterial::SetSpecularColor(MQColor color) 	{ float val[3] = {color.r, color.g, color.b}; MQMat_SetFloatArray(this, MQMAT_ID_SPECULAR_COLOR, val); }
inline void 	MQCMaterial::SetReflection(float value) 		{ float val[1]; val[0]=value; MQMat_SetFloatArray(this, MQMAT_ID_REFLECTION, val); }
inline void 	MQCMaterial::SetRefraction(float value) 		{ float val[1]; val[0]=value; MQMat_SetFloatArray(this, MQMAT_ID_REFRACTION, val); }
inline void 	MQCMaterial::SetMappingType(int type) 	{ MQMat_SetIntValue(this, MQMAT_ID_MAPPROJ, type); }
inline void 	MQCMaterial::SetMappingPosition(MQPoint pos) 	{ float val[3]; val[0]=pos.x; val[1]=pos.y; val[2]=pos.z; MQMat_SetFloatArray(this, MQMAT_ID_MAPPROJ_POSITION, val); }
inline void 	MQCMaterial::SetMappingScaling(MQPoint scale) 	{ float val[3]; val[0]=scale.x; val[1]=scale.y; val[2]=scale.z; MQMat_SetFloatArray(this, MQMAT_ID_MAPPROJ_SCALING, val); }
inline void 	MQCMaterial::SetMappingAngle(MQAngle angle) 	{ float val[3]; val[0]=angle.head; val[1]=angle.pich; val[2]=angle.bank; MQMat_SetFloatArray(this, MQMAT_ID_MAPPROJ_ANGLE, val); }
inline void 	MQCMaterial::SetWrapModeU(int type)			{ MQMat_SetIntValue(this, MQMAT_ID_MAPWRAPU, type); }
inline void 	MQCMaterial::SetWrapModeV(int type)			{ MQMat_SetIntValue(this, MQMAT_ID_MAPWRAPV, type); }
inline void 	MQCMaterial::SetMappingFilter(int type)			{ MQMat_SetIntValue(this, MQMAT_ID_MAPFILTER, type); }
inline void 	MQCMaterial::SetTextureName(const char *name) 	{ MQMat_SetTextureName(this, name); }
inline void 	MQCMaterial::SetTextureName(const wchar_t *name) { void *array[1] = {(void*)name}; MQMat_SetValueArray(this, MQMAT_ID_TEXTURE_NAME_W, array); }
inline void 	MQCMaterial::SetAlphaName(const char *name) 	{ MQMat_SetAlphaName(this, name); }
inline void 	MQCMaterial::SetAlphaName(const wchar_t *name) { void *array[1] = {(void*)name}; MQMat_SetValueArray(this, MQMAT_ID_ALPHA_NAME_W, array); }
inline void 	MQCMaterial::SetBumpName(const char *name) 		{ MQMat_SetBumpName(this, name); }
inline void 	MQCMaterial::SetBumpName(const wchar_t *name) { void *array[1] = {(void*)name}; MQMat_SetValueArray(this, MQMAT_ID_BUMP_NAME_W, array); }
inline void		MQCMaterial::SetTextureUVChannel(UINT channel)		{ return MQMat_SetIntValue(this, MQMAT_ID_TEXTURE_UVCHANNEL, (int)channel); }
inline void		MQCMaterial::SetAlphaUVChannel(UINT channel)		{ return MQMat_SetIntValue(this, MQMAT_ID_ALPHA_UVCHANNEL, (int)channel); }
inline void		MQCMaterial::SetBumpUVChannel(UINT channel)		{ return MQMat_SetIntValue(this, MQMAT_ID_BUMP_UVCHANNEL, (int)channel); }
inline BOOL		MQCMaterial::AllocUserData(int userdata_id) { return MQMat_AllocUserData(this, userdata_id); }
inline void 	MQCMaterial::FreeUserData(int userdata_id)	{ MQMat_FreeUserData(this, userdata_id); }
inline BOOL 	MQCMaterial::GetUserData(int userdata_id, void *buffer)       { return MQMat_GetUserData(this, userdata_id, 0, 0, buffer); }
inline BOOL 	MQCMaterial::GetUserDataPart(int userdata_id, int offset, int copy_bytes, void *buffer)       { return MQMat_GetUserData(this, userdata_id, offset, copy_bytes, buffer); }
inline BOOL 	MQCMaterial::SetUserData(int userdata_id, const void *buffer) { return MQMat_SetUserData(this, userdata_id, 0, 0, buffer); }
inline BOOL 	MQCMaterial::SetUserDataPart(int userdata_id, int offset, int copy_bytes, const void *buffer) { return MQMat_SetUserData(this, userdata_id, offset, copy_bytes, buffer); }
inline int		MQCMaterial::GetShaderName(char *buffer, int buffer_size) { int length=0; void *array[3]; array[0]=buffer; array[1]=&buffer_size; array[2]=&length; MQMat_GetValueArray(this, MQMAT_ID_SHADER_NAME, array); return length; }
inline std::string MQCMaterial::GetShaderName(void) { char buffer[64]; GetShaderName(buffer, sizeof(buffer)); return std::string(buffer); }
inline bool		MQCMaterial::SetShaderName(const char *name) { bool result=false; void *array[2]; array[0]=(void*)name; array[1]=&result; MQMat_SetValueArray(this, MQMAT_ID_SHADER_NAME, array); return result; }
inline int		MQCMaterial::GetShaderParameterNum(void)	{ int num=0; void *array[1]; array[0]=&num; MQMat_GetValueArray(this, MQMAT_ID_SHADER_PARAM_NUM, array); return num; }
inline int		MQCMaterial::GetShaderParameterName(int index, char *buffer, int buffer_size) { int length=0; void *array[4]; array[0]=&index; array[1]=buffer; array[2]=&buffer_size; array[3]=&length; MQMat_GetValueArray(this, MQMAT_ID_SHADER_PARAM_NAME, array); return length; }
inline std::string MQCMaterial::GetShaderParameterName(int index)	{ char buffer[64]; GetShaderParameterName(index, buffer, sizeof(buffer)); return std::string(buffer); }
inline int		MQCMaterial::GetShaderParameterValueType(int index)  { int type=0; void *array[3]; array[0]=&index; array[1]=NULL; array[2]=&type; MQMat_GetValueArray(this, MQMAT_ID_SHADER_PARAM_VALUE_TYPE, array); return type; }
inline int		MQCMaterial::GetShaderParameterValueType(const char *name)  { int type=0; void *array[3]; array[0]=NULL; array[1]=(void*)name; array[2]=&type; MQMat_GetValueArray(this, MQMAT_ID_SHADER_PARAM_VALUE_TYPE, array); return type; }
inline int		MQCMaterial::GetShaderParameterArraySize(int index)  { int num=0; void *array[3]; array[0]=&index; array[1]=NULL; array[2]=&num; MQMat_GetValueArray(this, MQMAT_ID_SHADER_PARAM_ARRAY_SIZE, array); return num; }
inline int		MQCMaterial::GetShaderParameterArraySize(const char *name)  { int num=0; void *array[3]; array[0]=NULL; array[1]=(void*)name; array[2]=&num; MQMat_GetValueArray(this, MQMAT_ID_SHADER_PARAM_ARRAY_SIZE, array); return num; }
inline bool		MQCMaterial::GetShaderParameterBoolValue(int index, int array_index)  { int value=0; void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&value; MQMat_GetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); return value != 0; }
inline bool		MQCMaterial::GetShaderParameterBoolValue(const char *name, int array_index)  { int value=0; void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&value; MQMat_GetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); return value != 0; }
inline int		MQCMaterial::GetShaderParameterIntValue(int index, int array_index)  { int value=0; void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&value; MQMat_GetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); return value; }
inline int		MQCMaterial::GetShaderParameterIntValue(const char *name, int array_index)  { int value=0; void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&value; MQMat_GetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); return value; }
inline float	MQCMaterial::GetShaderParameterFloatValue(int index, int array_index)  { float value=0; void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&value; MQMat_GetValueArray(this, MQMAT_ID_SHADER_PARAM_FLOAT_VALUE, array); return value; }
inline float	MQCMaterial::GetShaderParameterFloatValue(const char *name, int array_index)  { float value=0; void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&value; MQMat_GetValueArray(this, MQMAT_ID_SHADER_PARAM_FLOAT_VALUE, array); return value; }
inline MQColorRGBA	MQCMaterial::GetShaderParameterColorValue(int index, int array_index)  { MQColorRGBA value(0,0,0,0); void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&value; MQMat_GetValueArray(this, MQMAT_ID_SHADER_PARAM_COLOR_VALUE, array); return value; }
inline MQColorRGBA	MQCMaterial::GetShaderParameterColorValue(const char *name, int array_index)  { MQColorRGBA value(0,0,0,0); void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&value; MQMat_GetValueArray(this, MQMAT_ID_SHADER_PARAM_COLOR_VALUE, array); return value; }
inline int		MQCMaterial::GetShaderMappingNum(void) { int num=0; void *array[1]; array[0]=&num; MQMat_GetValueArray(this, MQMAT_ID_SHADER_MAP_NUM, array); return num; }
inline int		MQCMaterial::GetShaderMappingName(int index, char *buffer, int buffer_size) { int length=0; void *array[4]; array[0]=&index; array[1]=buffer; array[2]=&buffer_size; array[3]=&length; MQMat_GetValueArray(this, MQMAT_ID_SHADER_MAP_NAME, array); return length; }
inline std::string MQCMaterial::GetShaderMappingName(int index)	{ char buffer[64]; GetShaderMappingName(index, buffer, sizeof(buffer)); return std::string(buffer); }
inline int		MQCMaterial::GetShaderMappingFilename(int index, char *buffer, int buffer_size) { int length=0; void *array[5]; array[0]=&index; array[1]=NULL; array[2]=buffer; array[3]=&buffer_size; array[4]=&length; MQMat_GetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME, array); return length; }
inline int		MQCMaterial::GetShaderMappingFilename(const char *name, char *buffer, int buffer_size) { int length=0; void *array[5]; array[0]=NULL; array[1]=(void*)name; array[2]=buffer; array[3]=&buffer_size; array[4]=&length; MQMat_GetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME, array); return length; }
inline int		MQCMaterial::GetShaderMappingFilename(int index, wchar_t *buffer, int buffer_size) { int length=0; void *array[5]; array[0]=&index; array[1]=NULL; array[2]=buffer; array[3]=&buffer_size; array[4]=&length; MQMat_GetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME_W, array); return length; }
inline int		MQCMaterial::GetShaderMappingFilename(const char *name, wchar_t *buffer, int buffer_size) { int length=0; void *array[5]; array[0]=NULL; array[1]=(void*)name; array[2]=buffer; array[3]=&buffer_size; array[4]=&length; MQMat_GetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME_W, array); return length; }
inline std::string MQCMaterial::GetShaderMappingFilenameA(int index)	{ int len=GetShaderMappingFilename(index,(char*)NULL,0); if(len==0) return std::string(); char *buffer = new char[len+1]; GetShaderMappingFilename(index, buffer, len+1); std::string str(buffer); delete[] buffer; return str; }
inline std::string MQCMaterial::GetShaderMappingFilenameA(const char *name)	{ int len=GetShaderMappingFilename(name,(wchar_t*)NULL,0); if(len==0) return std::string(); char *buffer = new char[len+1]; GetShaderMappingFilename(name, buffer, len+1); std::string str(buffer); delete[] buffer; return str; }
inline std::wstring MQCMaterial::GetShaderMappingFilenameW(int index)	{ int len=GetShaderMappingFilename(index,(wchar_t*)NULL,0); if(len==0) return std::wstring(); wchar_t *buffer = new wchar_t[len+1]; GetShaderMappingFilename(index, buffer, len+1); std::wstring str(buffer); delete[] buffer; return str; }
inline std::wstring MQCMaterial::GetShaderMappingFilenameW(const char *name)	{ int len=GetShaderMappingFilename(name,(wchar_t*)NULL,0); if(len==0) return std::wstring(); wchar_t *buffer = new wchar_t[len+1]; GetShaderMappingFilename(name, buffer, len+1); std::wstring str(buffer); delete[] buffer; return str; }
inline void		MQCMaterial::SetShaderParameterBoolValue(int index, int array_index, bool value)  { int ival=value?1:0; void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&ival; MQMat_SetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); }
inline void		MQCMaterial::SetShaderParameterBoolValue(const char *name, int array_index, bool value)  { int ival=value?1:0; void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&ival; MQMat_SetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); }
inline void		MQCMaterial::SetShaderParameterIntValue(int index, int array_index, int value)  { void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&value; MQMat_SetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); }
inline void		MQCMaterial::SetShaderParameterIntValue(const char *name, int array_index, int value)  { void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&value; MQMat_SetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); }
inline void		MQCMaterial::SetShaderParameterFloatValue(int index, int array_index, float value)  { void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&value; MQMat_SetValueArray(this, MQMAT_ID_SHADER_PARAM_FLOAT_VALUE, array); }
inline void		MQCMaterial::SetShaderParameterFloatValue(const char *name, int array_index, float value)  { void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&value; MQMat_SetValueArray(this, MQMAT_ID_SHADER_PARAM_FLOAT_VALUE, array); }
inline void		MQCMaterial::SetShaderParameterColorValue(int index, int array_index, MQColorRGBA color)  { void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&color; MQMat_SetValueArray(this, MQMAT_ID_SHADER_PARAM_COLOR_VALUE, array); }
inline void		MQCMaterial::SetShaderParameterColorValue(const char *name, int array_index, MQColorRGBA color)  { void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&color; MQMat_SetValueArray(this, MQMAT_ID_SHADER_PARAM_COLOR_VALUE, array); }
inline void		MQCMaterial::SetShaderMappingFilename(int index, const char *buffer) { void *array[3]; array[0]=&index; array[1]=NULL; array[2]=(void*)buffer; MQMat_SetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME, array); }
inline void		MQCMaterial::SetShaderMappingFilename(const char *name, const char *buffer) { void *array[3]; array[0]=NULL; array[1]=(void*)name; array[2]=(void*)buffer; MQMat_SetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME, array); }
inline void		MQCMaterial::SetShaderMappingFilename(int index, const wchar_t *buffer) { void *array[3]; array[0]=&index; array[1]=NULL; array[2]=(void*)buffer; MQMat_SetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME_W, array); }
inline void		MQCMaterial::SetShaderMappingFilename(const char *name, const wchar_t *buffer) { void *array[3]; array[0]=NULL; array[1]=(void*)name; array[2]=(void*)buffer; MQMat_SetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME_W, array); }
inline UINT		MQCMaterial::GetShaderMappingUVChannel(int index) { UINT channel=0; void *array[3] = {&index, NULL, &channel}; MQMat_GetValueArray(this, MQMAT_ID_SHADER_MAP_UV_CHANNEL, array); return channel; }
inline UINT		MQCMaterial::GetShaderMappingUVChannel(const char *name) { UINT channel=0; void *array[3] = {NULL, (void*)name, &channel}; MQMat_GetValueArray(this, MQMAT_ID_SHADER_MAP_UV_CHANNEL, array); return channel; }
inline void		MQCMaterial::SetShaderMappingUVChannel(int index, UINT channel) { void *array[3] = {&index, NULL, &channel}; MQMat_SetValueArray(this, MQMAT_ID_SHADER_MAP_UV_CHANNEL, array); }
inline void		MQCMaterial::SetShaderMappingUVChannel(const char *name, UINT channel) { void *array[3] = {NULL, (void*)name, &channel}; MQMat_SetValueArray(this, MQMAT_ID_SHADER_MAP_UV_CHANNEL, array); }
inline MQShaderNode MQCMaterial::GetMainShaderNode() { return GetSubShaderNode(nullptr); }
//inline MQShaderNode MQCMaterial::CreateSubShaderNode(const char *shader_name, const char *id) { MQShaderNode result=nullptr; void *array[3]; array[0]=(void*)shader_name; array[1]=(void*)id; array[2]=&result; MQMat_SetValueArray(this, MQMAT_ID_SUBSHADER_CREATE, array); return result; }
//inline void		MQCMaterial::DeleteSubShaderNode(const char *id) { void *array[1]; array[0]=(void*)id; MQMat_SetValueArray(this, MQMAT_ID_SUBSHADER_DELETE, array); }
inline int		MQCMaterial::GetSubShaderNodeNum() { int num=0; void *array[1]; array[0]=&num; MQMat_GetValueArray(this, MQMAT_ID_SUBSHADER_NUM, array); return num; }
inline std::string	MQCMaterial::GetSubShaderNodeID(int index) { const char *result=nullptr; void *array[2]; array[0]=&index; array[1]=&result; MQMat_GetValueArray(this, MQMAT_ID_SUBSHADER_ID, array); if(result == nullptr) return std::string(); else return std::string(result); }
inline MQShaderNode MQCMaterial::GetSubShaderNode(int index) { MQShaderNode shader=NULL; void *array[3]; array[0]=&index; array[1]=NULL; array[2]=&shader; MQMat_GetValueArray(this, MQMAT_ID_SUBSHADER, array); return shader; }
inline MQShaderNode MQCMaterial::GetSubShaderNode(const char *id) { MQShaderNode shader=NULL; void *array[3]; array[0]=NULL; array[1]=(void*)id; array[2]=&shader; MQMat_GetValueArray(this, MQMAT_ID_SUBSHADER, array); return shader; }

// class MQShaderNode
inline int		MQCShaderNode::GetShaderName(char *buffer, int buffer_size) { int length=0; void *array[3]; array[0]=buffer; array[1]=&buffer_size; array[2]=&length; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_NAME, array); return length; }
inline std::string MQCShaderNode::GetShaderName(void) { char buffer[64]; GetShaderName(buffer, sizeof(buffer)); return std::string(buffer); }
inline int MQCShaderNode::GetOptionValue(const char *option_name, char *buffer, int buffer_size) {
	int length=0;
	void *array[4];
	array[0]=(void*)option_name;
	array[1]=buffer;
	array[2]=&buffer_size;
	array[3]=&length;
	MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_OPTION, array);
	return length;
}
inline std::string MQCShaderNode::GetOptionValue(const char *option_name) {
	int length=GetOptionValue(option_name,NULL,0);
	if(length==0) return std::string();
	char *buffer=(char*)malloc(length+1);
	length=GetOptionValue(option_name,buffer,length+1);
	std::string ret(buffer);
	free(buffer);
	return ret;
}
inline int		MQCShaderNode::GetParameterNum(void)	{ int num=0; void *array[1]; array[0]=&num; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_NUM, array); return num; }
inline int		MQCShaderNode::GetParameterName(int index, char *buffer, int buffer_size) { int length=0; void *array[4]; array[0]=&index; array[1]=buffer; array[2]=&buffer_size; array[3]=&length; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_NAME, array); return length; }
inline std::string MQCShaderNode::GetParameterName(int index)	{ char buffer[64]; GetParameterName(index, buffer, sizeof(buffer)); return std::string(buffer); }
inline int MQCShaderNode::GetParameterOptionValue(int index, const char *option_name, char *buffer, int buffer_size) {
	int length=0;
	void *array[6];
	array[0]=&index;
	array[1]=NULL;
	array[2]=(void*)option_name;
	array[3]=buffer;
	array[4]=&buffer_size;
	array[5]=&length;
	MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_OPTION, array);
	return length;
}
inline std::string MQCShaderNode::GetParameterOptionValue(int index, const char *option_name)	{
	int length=GetParameterOptionValue(index,option_name,NULL,0);
	if(length==0) return std::string();
	char *buffer=(char*)malloc(length+1);
	length=GetParameterOptionValue(index,option_name,buffer,length+1);
	std::string ret(buffer);
	free(buffer);
	return ret;
}
inline int MQCShaderNode::GetParameterOptionValue(const char *name, const char *option_name, char *buffer, int buffer_size) {
	int length=0;
	void *array[6];
	array[0]=NULL;
	array[1]=(void*)name;
	array[2]=(void*)option_name;
	array[3]=buffer;
	array[4]=&buffer_size;
	array[5]=&length;
	MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_OPTION, array);
	return length;
}
inline std::string MQCShaderNode::GetParameterOptionValue(const char *name, const char *option_name)	{
	int length=GetParameterOptionValue(name,option_name,NULL,0);
	if(length==0) return std::string();
	char *buffer=(char*)malloc(length+1);
	length=GetParameterOptionValue(name,option_name,buffer,length+1);
	std::string ret(buffer);
	free(buffer);
	return ret;
}
inline int		MQCShaderNode::GetParameterValueType(int index)  { int type=0; void *array[3]; array[0]=&index; array[1]=NULL; array[2]=&type; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_VALUE_TYPE, array); return type; }
inline int		MQCShaderNode::GetParameterValueType(const char *name)  { int type=0; void *array[3]; array[0]=NULL; array[1]=(void*)name; array[2]=&type; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_VALUE_TYPE, array); return type; }
inline int		MQCShaderNode::GetParameterArraySize(int index)  { int num=0; void *array[3]; array[0]=&index; array[1]=NULL; array[2]=&num; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_ARRAY_SIZE, array); return num; }
inline int		MQCShaderNode::GetParameterArraySize(const char *name)  { int num=0; void *array[3]; array[0]=NULL; array[1]=(void*)name; array[2]=&num; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_ARRAY_SIZE, array); return num; }
inline bool		MQCShaderNode::GetParameterBoolValue(int index, int array_index)  { int value=0; void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); return value != 0; }
inline bool		MQCShaderNode::GetParameterBoolValue(const char *name, int array_index)  { int value=0; void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); return value != 0; }
inline int		MQCShaderNode::GetParameterIntValue(int index, int array_index)  { int value=0; void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); return value; }
inline int		MQCShaderNode::GetParameterIntValue(const char *name, int array_index)  { int value=0; void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); return value; }
inline float	MQCShaderNode::GetParameterFloatValue(int index, int array_index)  { float value=0; void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_FLOAT_VALUE, array); return value; }
inline float	MQCShaderNode::GetParameterFloatValue(const char *name, int array_index)  { float value=0; void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_FLOAT_VALUE, array); return value; }
inline MQColorRGBA	MQCShaderNode::GetParameterColorValue(int index, int array_index)  { MQColorRGBA value(0,0,0,0); void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_COLOR_VALUE, array); return value; }
inline MQColorRGBA	MQCShaderNode::GetParameterColorValue(const char *name, int array_index)  { MQColorRGBA value(0,0,0,0); void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_COLOR_VALUE, array); return value; }
inline std::string	MQCShaderNode::GetParameterStringValue(int index, int array_index)  { const char *value=nullptr; void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_STRING_VALUE, array); if(value == nullptr) return std::string(); else return std::string(value); }
inline std::string	MQCShaderNode::GetParameterStringValue(const char *name, int array_index)  { const char *value=nullptr; void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_PARAM_STRING_VALUE, array); if(value == nullptr) return std::string(); else return std::string(value); }
inline void		MQCShaderNode::SetParameterBoolValue(int index, int array_index, bool value)  { void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); }
inline void		MQCShaderNode::SetParameterBoolValue(const char *name, int array_index, bool value)  { void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); }
inline void		MQCShaderNode::SetParameterIntValue(int index, int array_index, int value)  { void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); }
inline void		MQCShaderNode::SetParameterIntValue(const char *name, int array_index, int value)  { void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_PARAM_INT_VALUE, array); }
inline void		MQCShaderNode::SetParameterFloatValue(int index, int array_index, float value)  { void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_PARAM_FLOAT_VALUE, array); }
inline void		MQCShaderNode::SetParameterFloatValue(const char *name, int array_index, float value)  { void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_PARAM_FLOAT_VALUE, array); }
inline void		MQCShaderNode::SetParameterColorValue(int index, int array_index, MQColorRGBA color)  { void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=&color; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_PARAM_COLOR_VALUE, array); }
inline void		MQCShaderNode::SetParameterColorValue(const char *name, int array_index, MQColorRGBA color)  { void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=&color; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_PARAM_COLOR_VALUE, array); }
inline void		MQCShaderNode::SetParameterStringValue(int index, int array_index, const char *str)  { void *array[4]; array[0]=&index; array[1]=NULL; array[2]=&array_index; array[3]=(void*)str; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_PARAM_STRING_VALUE, array); }
inline void		MQCShaderNode::SetParameterStringValue(const char *name, int array_index, const char *str)  { void *array[4]; array[0]=NULL; array[1]=(void*)name; array[2]=&array_index; array[3]=(void*)str; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_PARAM_STRING_VALUE, array); }
inline int		MQCShaderNode::GetMappingNum(void) { int num=0; void *array[1]; array[0]=&num; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_NUM, array); return num; }
inline int		MQCShaderNode::GetMappingName(int index, char *buffer, int buffer_size) { int length=0; void *array[4]; array[0]=&index; array[1]=buffer; array[2]=&buffer_size; array[3]=&length; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_NAME, array); return length; }
inline std::string MQCShaderNode::GetMappingName(int index)	{ char buffer[64]; GetMappingName(index, buffer, sizeof(buffer)); return std::string(buffer); }
inline int		MQCShaderNode::GetMappingFilename(int index, char *buffer, int buffer_size) { int length=0; void *array[5]; array[0]=&index; array[1]=NULL; array[2]=buffer; array[3]=&buffer_size; array[4]=&length; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME, array); return length; }
inline int		MQCShaderNode::GetMappingFilename(const char *name, char *buffer, int buffer_size) { int length=0; void *array[5]; array[0]=NULL; array[1]=(void*)name; array[2]=buffer; array[3]=&buffer_size; array[4]=&length; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME, array); return length; }
inline int		MQCShaderNode::GetMappingFilename(int index, wchar_t *buffer, int buffer_size) { int length=0; void *array[5]; array[0]=&index; array[1]=NULL; array[2]=buffer; array[3]=&buffer_size; array[4]=&length; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME_W, array); return length; }
inline int		MQCShaderNode::GetMappingFilename(const char *name, wchar_t *buffer, int buffer_size) { int length=0; void *array[5]; array[0]=NULL; array[1]=(void*)name; array[2]=buffer; array[3]=&buffer_size; array[4]=&length; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME_W, array); return length; }
inline std::string MQCShaderNode::GetMappingFilename(int index)	{ int len=GetMappingFilename(index,(char*)NULL,0); if(len==0) return std::string(); char *buffer = new char[len+1]; GetMappingFilename(index, buffer, len+1); std::string str(buffer); delete[] buffer; return str; }
inline std::string MQCShaderNode::GetMappingFilename(const char *name)	{ int len=GetMappingFilename(name,(wchar_t*)NULL,0); if(len==0) return std::string(); char *buffer = new char[len+1]; GetMappingFilename(name, buffer, len+1); std::string str(buffer); delete[] buffer; return str; }
inline std::wstring MQCShaderNode::GetMappingFilenameW(int index)	{ int len=GetMappingFilename(index,(wchar_t*)NULL,0); if(len==0) return std::wstring(); wchar_t *buffer = new wchar_t[len+1]; GetMappingFilename(index, buffer, len+1); std::wstring str(buffer); delete[] buffer; return str; }
inline std::wstring MQCShaderNode::GetMappingFilenameW(const char *name)	{ int len=GetMappingFilename(name,(wchar_t*)NULL,0); if(len==0) return std::wstring(); wchar_t *buffer = new wchar_t[len+1]; GetMappingFilename(name, buffer, len+1); std::wstring str(buffer); delete[] buffer; return str; }
inline void		MQCShaderNode::SetMappingFilename(int index, const char *buffer) { void *array[3]; array[0]=&index; array[1]=NULL; array[2]=(void*)buffer; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME, array); }
inline void		MQCShaderNode::SetMappingFilename(const char *name, const char *buffer) { void *array[3]; array[0]=NULL; array[1]=(void*)name; array[2]=(void*)buffer; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME, array); }
inline void		MQCShaderNode::SetMappingFilename(int index, const wchar_t *buffer) { void *array[3]; array[0]=&index; array[1]=NULL; array[2]=(void*)buffer; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME_W, array); }
inline void		MQCShaderNode::SetMappingFilename(const char *name, const wchar_t *buffer) { void *array[3]; array[0]=NULL; array[1]=(void*)name; array[2]=(void*)buffer; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_FILENAME_W, array); }
inline int MQCShaderNode::GetMappingOptionValue(int index, const char *option_name, char *buffer, int buffer_size) {
	int length=0;
	void *array[6];
	array[0]=&index;
	array[1]=NULL;
	array[2]=(void*)option_name;
	array[3]=buffer;
	array[4]=&buffer_size;
	array[5]=&length;
	MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_OPTION, array);
	return length;
}
inline std::string MQCShaderNode::GetMappingOptionValue(int index, const char *option_name) {
	int length=GetMappingOptionValue(index,option_name,NULL,0);
	if(length==0) return std::string();
	char *buffer=(char*)malloc(length+1);
	length=GetMappingOptionValue(index,option_name,buffer,length+1);
	std::string ret(buffer);
	free(buffer);
	return ret;
}
inline int MQCShaderNode::GetMappingOptionValue(const char *name, const char *option_name, char *buffer, int buffer_size) {
	int length=0;
	void *array[6];
	array[0]=NULL;
	array[1]=(void*)name;
	array[2]=(void*)option_name;
	array[3]=buffer;
	array[4]=&buffer_size;
	array[5]=&length;
	MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_OPTION, array);
	return length;
}
inline std::string MQCShaderNode::GetMappingOptionValue(const char *name, const char *option_name) {
	int length=GetMappingOptionValue(name,option_name,NULL,0);
	if(length==0) return std::string();
	char *buffer=(char*)malloc(length+1);
	length=GetMappingOptionValue(name,option_name,buffer,length+1);
	std::string ret(buffer);
	free(buffer);
	return ret;
}
inline bool MQCShaderNode::GetMappingConnectedNodeID(int index, std::string& node_id, std::string& output) {
	int name_len=0, output_len=0; void *array[8] = {&index, NULL, NULL, NULL, &name_len, NULL, NULL, &output_len}; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_CONNECT_NODE_ID, array); 
	if(name_len==0 && output_len==0) { node_id.clear(); output.clear(); return false; }
	int name_bufsize=name_len+1, output_bufsize=output_len+1;
	char *name_buf = new char[name_bufsize];
	char *output_buf = new char[output_bufsize];
	array[2]=name_buf; array[3]=&name_bufsize; array[5]=output_buf; array[6]=&output_bufsize; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_CONNECT_NODE_ID, array);
	node_id = std::string(name_buf); output = std::string(output_buf); delete[] name_buf; delete[] output_buf; return true; }
inline bool MQCShaderNode::GetMappingConnectedNodeID(const char *name, std::string& node_id, std::string& output) {
	int name_len=0, output_len=0; void *array[8] = {NULL, (void*)name, NULL, NULL, &name_len, NULL, NULL, &output_len}; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_CONNECT_NODE_ID, array); 
	if(name_len==0 && output_len==0) { node_id.clear(); output.clear(); return false; }
	int name_bufsize=name_len+1, output_bufsize=output_len+1;
	char *name_buf = new char[name_bufsize];
	char *output_buf = new char[output_bufsize];
	array[2]=name_buf; array[3]=&name_bufsize; array[5]=output_buf; array[6]=&output_bufsize; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_CONNECT_NODE_ID, array);
	node_id = std::string(name_buf); output = std::string(output_buf); delete[] name_buf; delete[] output_buf; return true; }
inline void MQCShaderNode::SetMappingConnectedNodeID(int index, const char *node_id, const char *output) { void *array[4] = {&index, NULL, (void*)node_id, (void*)output}; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_CONNECT_NODE_ID, array);  }
inline void MQCShaderNode::SetMappingConnectedNodeID(const char *name, const char *node_id, const char *output) { void *array[4] = {NULL, (void*)name, (void*)node_id, (void*)output}; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_CONNECT_NODE_ID, array);  }
inline MQShaderNode MQCShaderNode::GetMappingConnectedNode(int index) { MQShaderNode result=NULL; void *array[3] = {&index, NULL, &result}; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_CONNECT_NODE, array); return result; }
inline MQShaderNode MQCShaderNode::GetMappingConnectedNode(const char *name) { MQShaderNode result=NULL; void *array[3] = {NULL, (void*)name, &result}; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_CONNECT_NODE, array); return result; }
inline UINT	MQCShaderNode::GetMappingUVChannel(int index) { UINT channel=0; void *array[3] = {&index, NULL, &channel}; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_UV_CHANNEL, array); return channel; }
inline UINT	MQCShaderNode::GetMappingUVChannel(const char *name) { UINT channel=0; void *array[3] = {NULL, (void*)name, &channel}; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_UV_CHANNEL, array); return channel; }
inline void MQCShaderNode::SetMappingUVChannel(int index, UINT channel) { void *array[3] = {&index, NULL, &channel}; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_UV_CHANNEL, array); }
inline void MQCShaderNode::SetMappingUVChannel(const char *name, UINT channel) { void *array[3] = {NULL, (void*)name, &channel}; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_UV_CHANNEL, array); }
inline int		MQCShaderNode::GetMappingParameterNum(int map_index)	{ int num=0; void *array[3]; array[0]=&map_index; array[1]=NULL; array[2]=&num; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_NUM, array); return num; }
inline int		MQCShaderNode::GetMappingParameterNum(const char *map_name)	{ int num=0; void *array[3]; array[0]=NULL; array[1]=(void*)map_name; array[2]=&num; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_NUM, array); return num; }
inline int		MQCShaderNode::GetMappingParameterName(int map_index, int param_index, char *buffer, int buffer_size) { int length=0; void *array[6]; array[0]=&map_index; array[1]=NULL; array[2]=&param_index; array[3]=buffer; array[4]=&buffer_size; array[5]=&length; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_NAME, array); return length; }
inline std::string MQCShaderNode::GetMappingParameterName(int map_index, int param_index)	{ char buffer[64]; GetMappingParameterName(map_index, param_index, buffer, sizeof(buffer)); return std::string(buffer); }
inline int		MQCShaderNode::GetMappingParameterName(const char *map_name, int param_index, char *buffer, int buffer_size) { int length=0; void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=&param_index; array[3]=buffer; array[4]=&buffer_size; array[5]=&length; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_NAME, array); return length; }
inline std::string MQCShaderNode::GetMappingParameterName(const char *map_name, int param_index)	{ char buffer[64]; GetMappingParameterName(map_name, param_index, buffer, sizeof(buffer)); return std::string(buffer); }
inline int MQCShaderNode::GetMappingParameterOptionValue(int map_index, int param_index, const char *option_name, char *buffer, int buffer_size) {
	int length=0;
	void *array[8];
	array[0]=&map_index;
	array[1]=NULL;
	array[2]=&param_index;
	array[3]=NULL;
	array[4]=(void*)option_name;
	array[5]=buffer;
	array[6]=&buffer_size;
	array[7]=&length;
	MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_OPTION, array);
	return length;
}
inline std::string MQCShaderNode::GetMappingParameterOptionValue(int map_index, int param_index, const char *option_name) {
	int length=GetMappingParameterOptionValue(map_index,param_index,option_name,NULL,0);
	if(length==0) return std::string();
	char *buffer=(char*)malloc(length+1);
	length=GetMappingParameterOptionValue(map_index,param_index,option_name,buffer,length+1);
	std::string ret(buffer);
	free(buffer);
	return ret;
}
inline int MQCShaderNode::GetMappingParameterOptionValue(const char *map_name, int param_index, const char *option_name, char *buffer, int buffer_size) {
	int length=0;
	void *array[8];
	array[0]=NULL;
	array[1]=(void*)map_name;
	array[2]=&param_index;
	array[3]=NULL;
	array[4]=(void*)option_name;
	array[5]=buffer;
	array[6]=&buffer_size;
	array[7]=&length;
	MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_OPTION, array);
	return length;
}
inline std::string MQCShaderNode::GetMappingParameterOptionValue(const char *map_name, int param_index, const char *option_name) {
	int length=GetMappingParameterOptionValue(map_name,param_index,option_name,NULL,0);
	if(length==0) return std::string();
	char *buffer=(char*)malloc(length+1);
	length=GetMappingParameterOptionValue(map_name,param_index,option_name,buffer,length+1);
	std::string ret(buffer);
	free(buffer);
	return ret;
}
inline int MQCShaderNode::GetMappingParameterOptionValue(const char *map_name, const char *param_name, const char *option_name, char *buffer, int buffer_size) {
	int length=0;
	void *array[8];
	array[0]=NULL;
	array[1]=(void*)map_name;
	array[2]=NULL;
	array[3]=(void*)param_name;
	array[4]=(void*)option_name;
	array[5]=buffer;
	array[6]=&buffer_size;
	array[7]=&length;
	MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_OPTION, array);
	return length;
}
inline std::string MQCShaderNode::GetMappingParameterOptionValue(const char *map_name, const char *param_name, const char *option_name) {
	int length=GetMappingParameterOptionValue(map_name,param_name,option_name,NULL,0);
	if(length==0) return std::string();
	char *buffer=(char*)malloc(length+1);
	length=GetMappingParameterOptionValue(map_name,param_name,option_name,buffer,length+1);
	std::string ret(buffer);
	free(buffer);
	return ret;
}
inline int		MQCShaderNode::GetMappingParameterValueType(int map_index, int param_index)  { int type=0; void *array[5]; array[0]=&map_index; array[1]=NULL; array[2]=&param_index; array[3]=NULL; array[4]=&type; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_VALUE_TYPE, array); return type; }
inline int		MQCShaderNode::GetMappingParameterValueType(const char *map_name, int param_index)  { int type=0; void *array[5]; array[0]=NULL; array[1]=(void*)map_name; array[2]=&param_index; array[3]=NULL; array[4]=&type; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_VALUE_TYPE, array); return type; }
inline int		MQCShaderNode::GetMappingParameterValueType(const char *map_name, const char *param_name)  { int type=0; void *array[5]; array[0]=NULL; array[1]=(void*)map_name; array[2]=NULL; array[3]=(void*)param_name; array[4]=&type; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_VALUE_TYPE, array); return type; }
inline int		MQCShaderNode::GetMappingParameterArraySize(int map_index, int param_index)  { int num=0; void *array[5]; array[0]=&map_index; array[1]=NULL; array[2]=&param_index; array[3]=NULL; array[4]=&num; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_ARRAY_SIZE, array); return num; }
inline int		MQCShaderNode::GetMappingParameterArraySize(const char *map_name, int param_index)  { int num=0; void *array[5]; array[0]=NULL; array[1]=(void*)map_name; array[2]=&param_index; array[3]=NULL; array[4]=&num; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_ARRAY_SIZE, array); return num; }
inline int		MQCShaderNode::GetMappingParameterArraySize(const char *map_name, const char *param_name)  { int num=0; void *array[5]; array[0]=NULL; array[1]=(void*)map_name; array[2]=NULL; array[3]=(void*)param_name; array[4]=&num; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_ARRAY_SIZE, array); return num; }
inline bool		MQCShaderNode::GetMappingParameterBoolValue(int map_index, int param_index, int array_index)  { int value=0; void *array[6]; array[0]=&map_index; array[1]=NULL; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_INT_VALUE, array); return value != 0; }
inline bool		MQCShaderNode::GetMappingParameterBoolValue(const char *map_name, int param_index, int array_index)  { int value=0; void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_INT_VALUE, array); return value != 0; }
inline bool		MQCShaderNode::GetMappingParameterBoolValue(const char *map_name, const char *param_name, int array_index)  { int value=0; void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=NULL; array[3]=(void*)param_name; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_INT_VALUE, array); return value != 0; }
inline int		MQCShaderNode::GetMappingParameterIntValue(int map_index, int param_index, int array_index)  { int value=0; void *array[6]; array[0]=&map_index; array[1]=NULL; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_INT_VALUE, array); return value; }
inline int		MQCShaderNode::GetMappingParameterIntValue(const char *map_name, int param_index, int array_index)  { int value=0; void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_INT_VALUE, array); return value; }
inline int		MQCShaderNode::GetMappingParameterIntValue(const char *map_name, const char *param_name, int array_index)  { int value=0; void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=NULL; array[3]=(void*)param_name; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_INT_VALUE, array); return value; }
inline float	MQCShaderNode::GetMappingParameterFloatValue(int map_index, int param_index, int array_index)  { float value=0; void *array[6]; array[0]=&map_index; array[1]=NULL; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_FLOAT_VALUE, array); return value; }
inline float	MQCShaderNode::GetMappingParameterFloatValue(const char *map_name, int param_index, int array_index)  { float value=0; void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_FLOAT_VALUE, array); return value; }
inline float	MQCShaderNode::GetMappingParameterFloatValue(const char *map_name, const char *param_name, int array_index)  { float value=0; void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=NULL; array[3]=(void*)param_name; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_FLOAT_VALUE, array); return value; }
inline MQColorRGBA	MQCShaderNode::GetMappingParameterColorValue(int map_index, int param_index, int array_index)  { MQColorRGBA value(0,0,0,0); void *array[6]; array[0]=&map_index; array[1]=NULL; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_COLOR_VALUE, array); return value; }
inline MQColorRGBA	MQCShaderNode::GetMappingParameterColorValue(const char *map_name, int param_index, int array_index)  { MQColorRGBA value(0,0,0,0); void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_COLOR_VALUE, array); return value; }
inline MQColorRGBA	MQCShaderNode::GetMappingParameterColorValue(const char *map_name, const char *param_name, int array_index)  { MQColorRGBA value(0,0,0,0); void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=NULL; array[3]=(void*)param_name; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_COLOR_VALUE, array); return value; }
inline std::string	MQCShaderNode::GetMappingParameterStringValue(int map_index, int param_index, int array_index)  { const char *value=nullptr; void *array[6]; array[0]=&map_index; array[1]=NULL; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_STRING_VALUE, array); if(value == nullptr) return std::string(); else return std::string(value); }
inline std::string	MQCShaderNode::GetMappingParameterStringValue(const char *map_name, int param_index, int array_index)  { const char *value=nullptr; void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_STRING_VALUE, array); if(value == nullptr) return std::string(); else return std::string(value); }
inline std::string	MQCShaderNode::GetMappingParameterStringValue(const char *map_name, const char *param_name, int array_index)  { const char *value=nullptr; void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=NULL; array[3]=(void*)param_name; array[4]=&array_index; array[5]=&value; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_STRING_VALUE, array); if(value == nullptr) return std::string(); else return std::string(value); }
inline void		MQCShaderNode::SetMappingParameterBoolValue(int map_index, int param_index, int array_index, bool value)  { void *array[6]; array[0]=&map_index; array[1]=NULL; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_INT_VALUE, array); }
inline void		MQCShaderNode::SetMappingParameterBoolValue(const char *map_name, int param_index, int array_index, bool value)  { void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_INT_VALUE, array); }
inline void		MQCShaderNode::SetMappingParameterBoolValue(const char *map_name, const char *param_name, int array_index, bool value)  { void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=NULL; array[3]=(void*)param_name; array[4]=&array_index; array[5]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_INT_VALUE, array); }
inline void		MQCShaderNode::SetMappingParameterIntValue(int map_index, int param_index, int array_index, int value)  { void *array[6]; array[0]=&map_index; array[1]=NULL; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_INT_VALUE, array); }
inline void		MQCShaderNode::SetMappingParameterIntValue(const char *map_name, int param_index, int array_index, int value)  { void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_INT_VALUE, array); }
inline void		MQCShaderNode::SetMappingParameterIntValue(const char *map_name, const char *param_name, int array_index, int value)  { void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=NULL; array[3]=(void*)param_name; array[4]=&array_index; array[5]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_INT_VALUE, array); }
inline void		MQCShaderNode::SetMappingParameterFloatValue(int map_index, int param_index, int array_index, float value)  { void *array[6]; array[0]=&map_index; array[1]=NULL; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_FLOAT_VALUE, array); }
inline void		MQCShaderNode::SetMappingParameterFloatValue(const char *map_name, int param_index, int array_index, float value)  { void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_FLOAT_VALUE, array); }
inline void		MQCShaderNode::SetMappingParameterFloatValue(const char *map_name, const char *param_name, int array_index, float value)  { void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=NULL; array[3]=(void*)param_name; array[4]=&array_index; array[5]=&value; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_FLOAT_VALUE, array); }
inline void		MQCShaderNode::SetMappingParameterColorValue(int map_index, int param_index, int array_index, MQColorRGBA color)  { void *array[6]; array[0]=&map_index; array[1]=NULL; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&color; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_COLOR_VALUE, array); }
inline void		MQCShaderNode::SetMappingParameterColorValue(const char *map_name, int param_index, int array_index, MQColorRGBA color)  { void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=&color; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_COLOR_VALUE, array); }
inline void		MQCShaderNode::SetMappingParameterColorValue(const char *map_name, const char *param_name, int array_index, MQColorRGBA color)  { void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=NULL; array[3]=(void*)param_name; array[4]=&array_index; array[5]=&color; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_COLOR_VALUE, array); }
inline void		MQCShaderNode::SetMappingParameterStringValue(int map_index, int param_index, int array_index, const char *str)  { void *array[6]; array[0]=&map_index; array[1]=NULL; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=(void*)str; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_STRING_VALUE, array); }
inline void		MQCShaderNode::SetMappingParameterStringValue(const char *map_name, int param_index, int array_index, const char *str)  { void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=&param_index; array[3]=NULL; array[4]=&array_index; array[5]=(void*)str; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_STRING_VALUE, array); }
inline void		MQCShaderNode::SetMappingParameterStringValue(const char *map_name, const char *param_name, int array_index, const char *str)  { void *array[6]; array[0]=NULL; array[1]=(void*)map_name; array[2]=NULL; array[3]=(void*)param_name; array[4]=&array_index; array[5]=(void*)str; MQShaderNode_SetValueArray(this, MQMAT_ID_SHADER_MAP_PARAM_STRING_VALUE, array); }
inline int		MQCShaderNode::GetOutputParameterNum(void)	{ int num=0; void *array[1]; array[0]=&num; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_OUTPUT_NUM, array); return num; }
inline int		MQCShaderNode::GetOutputParameterName(int index, char *buffer, int buffer_size) { int length=0; void *array[4]; array[0]=&index; array[1]=buffer; array[2]=&buffer_size; array[3]=&length; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_OUTPUT_NAME, array); return length; }
inline std::string MQCShaderNode::GetOutputParameterName(int index)	{ char buffer[64]; GetOutputParameterName(index, buffer, sizeof(buffer)); return std::string(buffer); }
inline int MQCShaderNode::GetOutputParameterOptionValue(int index, const char *option_name, char *buffer, int buffer_size) {
	int length=0;
	void *array[6];
	array[0]=&index;
	array[1]=NULL;
	array[2]=(void*)option_name;
	array[3]=buffer;
	array[4]=&buffer_size;
	array[5]=&length;
	MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_OUTPUT_OPTION, array);
	return length;
}
inline std::string MQCShaderNode::GetOutputParameterOptionValue(int index, const char *option_name)	{
	int length=GetOutputParameterOptionValue(index,option_name,NULL,0);
	if(length==0) return std::string();
	char *buffer=(char*)malloc(length+1);
	length=GetOutputParameterOptionValue(index,option_name,buffer,length+1);
	std::string ret(buffer);
	free(buffer);
	return ret;
}
inline int MQCShaderNode::GetOutputParameterOptionValue(const char *name, const char *option_name, char *buffer, int buffer_size) {
	int length=0;
	void *array[6];
	array[0]=NULL;
	array[1]=(void*)name;
	array[2]=(void*)option_name;
	array[3]=buffer;
	array[4]=&buffer_size;
	array[5]=&length;
	MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_OUTPUT_OPTION, array);
	return length;
}
inline std::string MQCShaderNode::GetOutputParameterOptionValue(const char *name, const char *option_name)	{
	int length=GetOutputParameterOptionValue(name,option_name,NULL,0);
	if(length==0) return std::string();
	char *buffer=(char*)malloc(length+1);
	length=GetOutputParameterOptionValue(name,option_name,buffer,length+1);
	std::string ret(buffer);
	free(buffer);
	return ret;
}
inline int		MQCShaderNode::GetOutputParameterValueType(int index)  { int type=0; void *array[3]; array[0]=&index; array[1]=NULL; array[2]=&type; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_OUTPUT_VALUE_TYPE, array); return type; }
inline int		MQCShaderNode::GetOutputParameterValueType(const char *name)  { int type=0; void *array[3]; array[0]=NULL; array[1]=(void*)name; array[2]=&type; MQShaderNode_GetValueArray(this, MQMAT_ID_SHADER_OUTPUT_VALUE_TYPE, array); return type; }

// class MQAngle
inline MQMatrix	MQAngle::GetRotationMatrix() const {
	float val[9] = {1,1,1,head,pich,bank,0,0,0};
	MQMatrix mtx;
	MQMatrix_FloatValue(mtx.t, MQMATRIX_SET_TRANSFORM, val);
	return mtx;
}

// class MQMatrix
inline MQPoint	MQMatrix::GetScaling() const			{ float val[3]; MQMatrix_FloatValue((float*)this->t, MQMATRIX_GET_SCALING, val); return MQPoint(val[0],val[1],val[2]); }
inline MQAngle	MQMatrix::GetRotation() const			{ float val[3]; MQMatrix_FloatValue((float*)this->t, MQMATRIX_GET_ROTATION, val); return MQAngle(val[0],val[1],val[2]); }
inline MQPoint	MQMatrix::GetTranslation() const		{ float val[3]; MQMatrix_FloatValue((float*)this->t, MQMATRIX_GET_TRANSLATION, val); return MQPoint(val[0],val[1],val[2]); }
inline void		MQMatrix::SetTransform(const MQPoint *scaling, const MQAngle *rotation, const MQPoint *trans){
	 float val[9];
	 val[0] = scaling->x; val[1] = scaling->y; val[2] = scaling->z;
	 val[3] = rotation->head; val[4] = rotation->pich; val[5] = rotation->bank;
	 val[6] = trans->x; val[7] = trans->y; val[8] = trans->z;
	 MQMatrix_FloatValue(this->t, MQMATRIX_SET_TRANSFORM, val);
}
inline void		MQMatrix::SetTransform(const MQPoint& scaling, const MQAngle& rotation, const MQPoint& trans){
	float val[9];
	val[0] = scaling.x; val[1] = scaling.y; val[2] = scaling.z;
	val[3] = rotation.head; val[4] = rotation.pich; val[5] = rotation.bank;
	val[6] = trans.x; val[7] = trans.y; val[8] = trans.z;
	MQMatrix_FloatValue(this->t, MQMATRIX_SET_TRANSFORM, val);
}
inline void		MQMatrix::SetInverseTransform(const MQPoint *scaling, const MQAngle *rotation, const MQPoint *trans){
	 float val[9];
	 val[0] = scaling->x; val[1] = scaling->y; val[2] = scaling->z;
	 val[3] = rotation->head; val[4] = rotation->pich; val[5] = rotation->bank;
	 val[6] = trans->x; val[7] = trans->y; val[8] = trans->z;
	 MQMatrix_FloatValue(this->t, MQMATRIX_SET_INVERSE_TRANSFORM, val);
}
inline void		MQMatrix::SetInverseTransform(const MQPoint& scaling, const MQAngle& rotation, const MQPoint& trans){
	float val[9];
	val[0] = scaling.x; val[1] = scaling.y; val[2] = scaling.z;
	val[3] = rotation.head; val[4] = rotation.pich; val[5] = rotation.bank;
	val[6] = trans.x; val[7] = trans.y; val[8] = trans.z;
	MQMatrix_FloatValue(this->t, MQMATRIX_SET_INVERSE_TRANSFORM, val);
}


#endif //MQPLUGIN_EXPORTS

#endif //MQPluginH


