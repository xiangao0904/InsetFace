//---------------------------------------------------------------------------
//
//   MQBasePlugin
//
//          Copyright(C) 1999-2023, tetraface Inc.
//
//     This is a wrapper for using C++ classes without taking care of 
//    Metasequoia plug-in interface API.
//     The API functions for each type of a plug-in are defined as the 
//    pure virtual functions, and it is necessary to implement them 
//    in an inherited class.
//
//    　Metasequoia用プラグインインターフェースをAPIレベルから隠蔽して
//    C++のクラスとして扱うためのラッパーです。
//      各プラグインの種類ごとに必須のAPIは純粋仮想関数として定義され
//    ているため、これらの関数は継承クラス側で実装を行う必要があります。
//
//---------------------------------------------------------------------------

#ifndef _MQBASEPLUGIN_H_
#define _MQBASEPLUGIN_H_

#include "MQPlugin.h"
#include <vector>
#include <string>
#include <map>

class MQSetting;


enum MQSYSTEMCOLOR_TYPE {
	MQSYSTEMCOLOR_OBJECT,
	MQSYSTEMCOLOR_SELECT,
	MQSYSTEMCOLOR_TEMP,
	MQSYSTEMCOLOR_HIGHLIGHT,
	MQSYSTEMCOLOR_UNACTIVE,
	MQSYSTEMCOLOR_MESH_YZ,
	MQSYSTEMCOLOR_MESH_ZX,
	MQSYSTEMCOLOR_MESH_XY,
	MQSYSTEMCOLOR_BLOB_PLUS,
	MQSYSTEMCOLOR_BLOB_MINUS,
	MQSYSTEMCOLOR_UV,
	MQSYSTEMCOLOR_AXIS_X,
	MQSYSTEMCOLOR_AXIS_Y,
	MQSYSTEMCOLOR_AXIS_Z,
	MQSYSTEMCOLOR_AXIS_W,
	MQSYSTEMCOLOR_AXIS_ACTIVE,
	MQSYSTEMCOLOR_PREVIEW_BACK,
};


enum MQSETTINGVALUE_TYPE {
	MQSETTINGVALUE_LANGUAGE,         // string
	MQSETTINGVALUE_ROTATION_HANDLE,  // string ("arrow" or "ring")
	MQSETTINGVALUE_HANDLE_SIZE,      // float
	MQSETTINGVALUE_HANDLE_SCALE,     // float
	MQSETTINGVALUE_NORMALMAP_FLIP,   // float array [x,y,z]
	MQSETTINGVALUE_FONT,             // string
	MQSETTINGVALUE_FIXED_FONT,       // string
	MQSETTINGVALUE_APPLICATION_NAME, // string
};

typedef void *MQDrawingText;


// Base class for all plug-ins
// すべてのプラグインの基底クラス
class MQBasePlugin
{
public:
	// Options for GetResourceCursor()
	// GetResourceCursor()の引数
	enum MQCURSOR_TYPE {
		MQCURSOR_SIZEALL	= -22,		// ４方向矢印
		MQCURSOR_HANDPOINT	= -21,		// 指先
		MQCURSOR_HELP		= -20,		// 疑問符付き
		MQCURSOR_NO			= -18,		// 禁止
		MQCURSOR_WAIT		= -11,		// 砂時計
		MQCURSOR_UPARROW	= -10,		// 上向き矢印
		MQCURSOR_SIZEWE		= -9,		// 左右を指す両方向矢印
		MQCURSOR_SIZENWSE	= -8,		// 左上と右下を指す両方向矢印
		MQCURSOR_SIZENS		= -7,		// 上下を指す両方向矢印
		MQCURSOR_SIZENESW	= -6,		// 右上と左下を指す両方向矢印
		MQCURSOR_CROSS		= -3,		// 十字
		MQCURSOR_NONE		= -1,		// 非表示
		MQCURSOR_DEFAULT	= 0,		// 標準
		MQCURSOR_RECT		= 1,		// 範囲
		MQCURSOR_ROPE		= 2,		// 投げ縄
		MQCURSOR_MOVE		= 3,		// 移動
		MQCURSOR_SCALE		= 4, 		// 拡大
		MQCURSOR_ROTATE		= 5,		// 回転
	};

	// Parameters for GetSceneOption()
	// GetSceneOption()のパラメータ
	struct SCENE_OPTION {
		BOOL ShowVertex;	// Show vertices         | 頂点を表示
		BOOL ShowLine;		// Show lines            | 辺を表示
		BOOL ShowFace;		// Show faces            | 面を表示
		BOOL FrontOnly;		// Show front faces only | 前面のみ表示
		BOOL ShowBkimg;		// Show backgound images | 下絵を表示
	};

	// Coordinate type
	// 座標タイプ
	enum COORDINATE_TYPE {
		COORDINATE_SCREEN	= 0,	// Screen coordinate | スクリーン座標
		COORDINATE_WORLD	= 1,	// World coordinate  | ワールド座標
		COORDINATE_LOCAL	= 2,	// Local coordinate  | ローカル座標
	};

	// Edit option type
	// 編集オプションタイプ
	enum EDITOPTION_TYPE {
		EDITOPTION_UNKNOWN,
		EDITOPTION_SCREEN,
		EDITOPTION_WORLD,
		EDITOPTION_LOCAL,
	};

	// EDIT_OPTION::SnapGrid, GetSnappedPos()への指定（複数可）
	enum SNAP_GRID_TYPE {
		SNAP_GRID_X = 1,	// Snap to X axis | X軸に吸着
		SNAP_GRID_Y = 2,	// Snap to Y axis | Y軸に吸着
		SNAP_GRID_Z = 4,	// Snap to Z axis | Z軸に吸着
	};

	// EDIT_OPTION::SnapPlane
	enum SNAP_PLANE_TYPE {
		SNAP_PLANE_NONE = 0,	// Not snap any plane       | 平面に吸着しない
		SNAP_PLANE_X = 1,		// Fix X position           | X座標を固定
		SNAP_PLANE_Y = 2,		// Fix Y position           | Y座標を固定
		SNAP_PLANE_Z = 3,		// Fix Z position           | Z座標を固定
		SNAP_PLANE_ARB = 4,		// Snap to arbitrary plane  | 任意の平面に吸着
	};

	// Parameters for GetEditOption()
	// GetEditOption()のパラメータ
	struct EDIT_OPTION {
		BOOL EditVertex;	// Enable vertex editing    | 頂点を編集可
		BOOL EditLine;		// Enable line editing      | 辺を編集可
		BOOL EditFace;		// Enable face editing      | 面を編集可
		BOOL SelectRect;	// Rectangle selection      | 矩形選択
		BOOL SelectRope;	// Rope selection           | 投げ縄選択
		BOOL SnapX;			// Edit along X axis        | X軸に沿った編集
		BOOL SnapY;			// Edit along Y axis        | Y軸に沿った編集
		BOOL SnapZ;			// Edit along Z axis        | Z軸に沿った編集
		COORDINATE_TYPE CoordinateType;	// Coordinate axis          | 座標軸の種類
		SNAP_GRID_TYPE SnapGrid;		// Snap to grid             | グリッドへの吸着
		BOOL Symmetry;		       // Symmetry editing              | 対称編集
		float SymmetryDistance;	   // Distance for symmetry editing | 対称とみなす距離
		BOOL CurrentObjectOnly;	   // Edit current object only      | カレントオブジェクトのみを編集
		SNAP_PLANE_TYPE SnapPlane; // Snap to a plane               | 平面への吸着
		MQPoint SnapPlanePos;      // Position of snapping plane    | 吸着する平面の位置
		MQPoint SnapPlaneDir;      // Direction of snapping plane   | 吸着する平面の向き
		BOOL SnapVertex;           // Snap to vertices              | 頂点への吸着
		BOOL SnapLine;             // Snap to lines                 | 辺への吸着
		BOOL SnapFace;             // Snap to faces                 | 面への吸着
	};

public:
	// Constructor
	// コンストラクタ
	MQBasePlugin();

	// Destructor
	// デストラクタ
	virtual ~MQBasePlugin();

	// Get a plug-in ID
	// プラグインIDを返す。
	virtual void GetPlugInID(DWORD *Product, DWORD *ID) = 0;

	// Get a plug-in name
	// プラグイン名を返す。
	virtual const char *GetPlugInName(void) = 0;

	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) = 0;

	// Open a setting file
	// 設定ファイルを開く
	MQSetting *OpenSetting(void);

	// Close a setting file
	// 設定ファイルを閉じる
	void CloseSetting(MQSetting *setting);

	// Get a resource string in command.xml
	// command.xmlファイル内に定義されるリソース文字列を取得する
	std::wstring GetResourceString(const char *id);
	static std::wstring GetResourceString(const char *id, DWORD productID, DWORD pluginID, MQBasePlugin *plugin);

	// Get a setting value
	// 設定値をを取得する
	int GetSettingIntValue(MQSETTINGVALUE_TYPE type);
	float GetSettingFloatValue(MQSETTINGVALUE_TYPE type);
	std::vector<float> GetSettingFloatArray(MQSETTINGVALUE_TYPE type);
	std::wstring GetSettingValue(MQSETTINGVALUE_TYPE type);
	static std::wstring GetSettingValue(MQSETTINGVALUE_TYPE type, DWORD productID, DWORD pluginID, MQBasePlugin *plugin);

	// Get a system-defined color
	// システム定義色を取得する
	MQColor GetSystemColor(MQSYSTEMCOLOR_TYPE color_type);

	// Get a default mouse cursor
	// 標準マウスカーソルを取得
	HCURSOR GetResourceCursor(MQCURSOR_TYPE cursor_type);

	// Get a current mouse cursor for a screen
	// 現在のスクリーン用マウスカーソルを取得
	HCURSOR GetScreenMouseCursor();

	// Set a mouse cursor for a screen
	// スクリーン用マウスカーソルを設定
	void SetScreenMouseCursor(HCURSOR cursor);

	int GetLUTCount();
	std::wstring GetLUTName(int index);
	const unsigned char *GetLUTData(int index);
	const unsigned char *GetDefaultLUTData();

	// Get display options of the scene
	// シーンの表示オプションを取得
	void GetSceneOption(MQScene scene, SCENE_OPTION& option);

	// Get edit options
	// 編集オプションを取得
	void GetEditOption(EDIT_OPTION& option);

	// Get a display unit.
	// 表示単位の取得
	MQDISPLAYUNIT GetDisplayUnit();
	
	static const wchar_t *GetDisplayUnitString(MQDISPLAYUNIT unit, double *scale);

	// Get a filename.
	// ファイル名の取得
	std::wstring GetFilename(MQDocument doc);

	struct SAVE_DOCUMENT_OPTION {
		DWORD ExportProductID;
		DWORD ExportPluginID;
		int ExportIndex;
		SAVE_DOCUMENT_OPTION() : ExportPluginID(0), ExportProductID(0), ExportIndex(0) { }
	};
	// Save a document to a file.
	// ドキュメントのファイル保存
	bool SaveDocument(MQDocument doc, const wchar_t *filename, const SAVE_DOCUMENT_OPTION& option = SAVE_DOCUMENT_OPTION());

	struct OPEN_DOCUMENT_OPTION {
		DWORD ImportProductID;
		DWORD ImportPluginID;
		int ImportIndex;
		enum MERGE_MODE {
			ASK,
			FORCE_MERGE,
			FORCE_ADD,
		} MergeMode;
		OPEN_DOCUMENT_OPTION() : ImportPluginID(0), ImportProductID(0), ImportIndex(0), MergeMode(ASK) { }
	};
	//MQDocument OpenDocument(const wchar_t *filename, const OPEN_DOCUMENT_OPTION& option = OPEN_DOCUMENT_OPTION()); // Not implemented yet
	bool InsertDocument(MQDocument doc, const wchar_t *filename, const OPEN_DOCUMENT_OPTION& option = OPEN_DOCUMENT_OPTION());

	std::vector<std::wstring> EnumLoadableImages();

	// Send a plug-in own mesage to other plug-ins
	// 他のプラグインにプラグイン独自のメッセージを送る
	int SendUserMessage(MQDocument doc, DWORD target_product, DWORD target_id, const char *description, void *param);

	// Set a draw proxy object
	// 描画代替オブジェクトを設定
	void SetDrawProxyObject(MQObject obj, MQObject proxy, bool sync_select = false);

	// Update an undo buffer
	// アンドゥバッファを更新する
	void UpdateUndo();
	void UpdateUndo(const wchar_t *str);
};


// Import plug-in class
// インポートプラグインクラス
class MQImportPlugin : public MQBasePlugin
{
	friend class MQBasePluginMediator;

public:
	// Constructor
	// コンストラクタ
	MQImportPlugin();

	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) { return MQPLUGIN_TYPE_IMPORT; }

	// Get a file type for importing
	// 入力出力可能なファイルタイプを返す。
	virtual const char *EnumFileType(int index) = 0;

	// Get a file extension for importing
	// 入力可能な拡張子を返す。
	virtual const char *EnumFileExt(int index) = 0;

	// Import a file
	// ファイルの読み込み
	virtual BOOL ImportFile(int index, const wchar_t *filename, MQDocument doc) = 0;

	// Get whether a background loading can be processed or not.
	// バックグラウンド読み込みが可能かどうかを返す。
	virtual BOOL SupportBackground(void) { return FALSE; }

	// Get whether the current loading is foreground(FALSE) or background(TRUE).
	// 現在の読み込みがフォアグラウンド(FALSE)かバックグラウンド(TRUE)読み込みかを返す。
	BOOL IsBackground(void);

	// Get import options for MQ_ShowFileDialog()
	// MQ_ShowFileDialog()用の読み込みオプションの取得
	void *GetImportOptions(void);

	// Get whether the current loading has been canceled or not.
	// 現在の読み込みがキャンセルされたかどうかを返す。
	BOOL IsCanceled(void);

	// Set a current progress from 0 to 1.
	// 0～1の範囲で現在の進捗状況を設定します。
	void SetProgress(float progress);

private:
	BOOL m_ImportBackground;
	void *m_ImportOptions;
};

// Export plug-in class
// エクスポートプラグインクラス
class MQExportPlugin : public MQBasePlugin
{
public:
	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) { return MQPLUGIN_TYPE_EXPORT; }

	// Get a file type for exporting
	// 出力可能なファイルタイプを返す。
	virtual const char *EnumFileType(int index) = 0;

	// Get a file extension for exporting
	// 出力可能な拡張子を返す。
	virtual const char *EnumFileExt(int index) = 0;

	// Export a file
	// ファイルの出力
	virtual BOOL ExportFile(int index, const wchar_t *filename, MQDocument doc) = 0;

};

// Plug-in class using a menu 
// メニュー型プラグインの基底クラス
class MQMenuBasePlugin : public MQBasePlugin
{
public:
	// Get a string displayed in a menu
	// ポップアップメニューに表示される文字列を返す。
	virtual const wchar_t *EnumString(int index) = 0;

	virtual BOOL Execute(int index, MQDocument doc) = 0;
};

// Create plug-in class
// 作成プラグインクラス
class MQCreatePlugin : public MQMenuBasePlugin
{
public:
	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) { return MQPLUGIN_TYPE_CREATE; }
};

// Select plug-in class
// 選択プラグインクラス
class MQSelectPlugin : public MQMenuBasePlugin
{
public:
	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) { return MQPLUGIN_TYPE_SELECT; }
};

// Object plug-in class
// オブジェクトプラグインクラス
class MQObjectPlugin : public MQMenuBasePlugin
{
public:
	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) { return MQPLUGIN_TYPE_OBJECT; }
};

// Station plug-in class
// 常駐型プラグインクラス
/*
	常駐型プラグインのベースとなるクラスです。
	常駐型プラグインはメニュー[パネル]に項目を追加し、内部状態の変化を
	メッセージとして受け取り、プラグイン独自の処理を行います。
*/
class MQStationPlugin : public MQBasePlugin
{
public:
	// Parameters for OnNewDocument()
	// OnNewDocument()のパラメータ
	struct NEW_DOCUMENT_PARAM {
		MQXmlElement elem;	// XML element for saved plugin's information | プラグインによって保存されたXML要素
	};

	// Parameters for OnInsertDocument()
	// OnInsertDocument()のパラメータ
	struct INSERT_DOCUMENT_PARAM : public NEW_DOCUMENT_PARAM {
		MQDocument srcdoc;
		UINT *object_table;
		UINT *material_table;

		UINT GetDestObjectID(UINT src_objid) const;
		std::map<UINT,UINT> GetObjectIDConversionMap() const;
		UINT GetDestMaterialID(UINT src_matid) const;
		std::map<UINT,UINT> GetMaterialIDConversionMap() const;
	};

	// Parameters for OnSaveDocument(),OnSavePastDocument()
	// OnSaveDocument(),OnSavePastDocument()のパラメータ
	struct SAVE_DOCUMENT_PARAM {
		MQXmlElement elem;	// XML element for saving plugin's information | プラグインに割り当てられた保存用XML要素
		BOOL bSaveUniqueID;	// Whether to save unique IDs | ユニークIDを保存するかどうか
		int PastState;      // Past state (from undo buffer) | 過去の状態（アンドゥバッファから）
	};

	enum DRAWING_TEXT_ALIGNMENT {
		TEXT_ALIGN_LEFT   = 0,
		TEXT_ALIGN_TOP    = 0,
		TEXT_ALIGN_CENTER = 1,
		TEXT_ALIGN_RIGHT  = 2,
		TEXT_ALIGN_BOTTOM = 2,
	};

	// Parameters for CreateDrawingText()
	// CreateDrawingText()のパラメータ
	struct DRAWING_TEXT_PARAM {
		MQPoint ScreenPos;  // Position on a screen coordinate | スクリーン座標での位置
		MQColor Color;      // Text color   | 文字色
		float FontScale;	// Text scaling | 文字の拡大率
		DRAWING_TEXT_ALIGNMENT HorzAlign; // Text horizontal alignment | 横方向の配置
		DRAWING_TEXT_ALIGNMENT VertAlign; // Text vertical alignment   | 縦方向の配置

		DRAWING_TEXT_PARAM() : ScreenPos(0,0,0), Color(0,0,0), FontScale(1.0f), HorzAlign(TEXT_ALIGN_LEFT), VertAlign(TEXT_ALIGN_TOP) { }
	};

public:
	// Constructor
	// コンストラクタ
	MQStationPlugin();

	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) { return MQPLUGIN_TYPE_STATION; }

#if __APPLE__
	// Create a new plugin class for another document.
	// 別のドキュメントのための新しいプラグインクラスを作成する。
	virtual MQBasePlugin *CreateNewPlugin() = 0;
#endif

	// Get a string displayed in a menu or on a button
	// ポップアップメニューまたはボタンに表示される文字列を返す。
	virtual const wchar_t *EnumString(void) = 0;
	// Enumerate a sub command.
	// サブコマンドの名前を列挙
	virtual const char *EnumSubCommand(int index);
	// Get a sub command string for GUI.
	// サブコマンドの表示名の取得
	virtual const wchar_t *GetSubCommandString(int index);

	// Initialize an application
	// アプリケーションの初期化
	virtual BOOL Initialize() = 0;
	// Exit an application
	// アプリケーションの終了
	virtual void Exit() = 0;

	// A message for activating or deactivation a window
	// 表示・非表示切り替え要求
	virtual BOOL Activate(MQDocument doc, BOOL flag) = 0;
	// A message for checking an activated state of a plug-in
	// 表示・非表示状態の返答
	virtual BOOL IsActivated(MQDocument doc) = 0;
	// A message for calling a sub command
	// サブコマンドの呼び出し
	virtual BOOL OnSubCommand(MQDocument doc, int index);
	// A message for switching a sub command
	// サブコマンドの切り替え
	virtual BOOL OnSwitchSubCommand(MQDocument doc);
	// A message for minimizing a window
	// ウインドウの最小化への返答
	virtual void OnMinimize(MQDocument doc, BOOL flag);
	// A message for receiving a plug-in own message
	// プラグイン独自のメッセージの受け取り
	virtual int OnReceiveUserMessage(MQDocument doc, DWORD src_product, DWORD src_id, const char *description, void *message);
	// A message for drawing
	// 描画時の処理
	virtual void OnDraw(MQDocument doc, MQScene scene, int width, int height);

	// A message for initializing a document
	// ドキュメント初期化時
	virtual void OnNewDocument(MQDocument doc, const char *filename, NEW_DOCUMENT_PARAM& param);
	// A message for inserting a document
	// ドキュメント挿入時
	virtual void OnInsertDocument(MQDocument doc, const char *filename, INSERT_DOCUMENT_PARAM& param);
	// A message for exiting a document
	// ドキュメント終了時
	virtual void OnEndDocument(MQDocument doc);
	// A message for saving a document
	// ドキュメント保存時
	virtual void OnSaveDocument(MQDocument doc, const char *filename, SAVE_DOCUMENT_PARAM& param);
	// A message for saving a document
	// 過去のドキュメント保存時
	virtual void OnSavePastDocument(MQDocument doc, const char *filename, SAVE_DOCUMENT_PARAM& param);
	// A message for an undo
	// アンドゥ実行時
	virtual BOOL OnUndo(MQDocument doc, int undo_state);
	// A message for an redo
	// リドゥ実行時
	virtual BOOL OnRedo(MQDocument doc, int redo_state);
	// A message for updating an undo state
	// アンドゥ状態更新時
	virtual void OnUpdateUndo(MQDocument doc, int undo_state, int undo_size);
	// A message for editing objects
	// オブジェクトの編集時
	virtual void OnObjectModified(MQDocument doc);
	// A message for selecting objects
	// オブジェクトの選択状態の変更時
	virtual void OnObjectSelected(MQDocument doc);
	// A message for changing a current object
	// カレントオブジェクトの変更時
	virtual void OnUpdateObjectList(MQDocument doc);
	// A message for modifying parameters of materials
	// マテリアルのパラメータ変更時
	virtual void OnMaterialModified(MQDocument doc);
	// A message for changing a current material
	// カレントマテリアルの変更時
	virtual void OnUpdateMaterialList(MQDocument doc);
	// A message for updating a scene
	// シーン情報の変更時
	virtual void OnUpdateScene(MQDocument doc, MQScene scene);
	// A message for changing an edit option
	// 編集オプションの変更時
	virtual void OnChangeEditOption(MQDocument doc, EDITOPTION_TYPE trigger);
	// A message for changing the configuration settings
	// 環境設定の変更時
	virtual void OnConfigurationChanged(MQDocument doc);

	enum INTERPOLATE_TYPE {
		INTERPOLATE_VERTEX,
		INTERPOLATE_APEX,
	};
	enum INTERPOLATE_REASON {
		INTERPOLATE_BY_OTHER,
		INTERPOLATE_BY_CLONE_OBJECT,
		INTERPOLATE_BY_MERGE_OBJECT,
		INTERPOLATE_BY_PATCH,
		INTERPOLATE_BY_MIRROR,
	};
	struct INTERPOLATE_VERTEX_PARAM {
		MQObject obj;
		int vert;
		float weight;
	};
#pragma pack(push, 4)
	struct INTERPOLATE_APEX_PARAM {
		MQObject obj;
		int face;
		int apex;
		float weight;
	};
#pragma pack(pop)
	virtual bool OnQueryInterpolate(MQDocument doc, MQObject dstobj, MQObject srcobj, INTERPOLATE_TYPE type, INTERPOLATE_REASON reason);
	virtual void OnInterpolateVertexData(MQDocument doc, MQObject obj, int vert, INTERPOLATE_VERTEX_PARAM *valarray, int valnum);
	virtual void OnInterpolateApexData(MQDocument doc, MQObject obj, int face, int apex, INTERPOLATE_APEX_PARAM *valarray, int valnum);

	enum CLIPBOARD_METHOD {
		CLIPBOARD_QUERY_COPY,
		CLIPBOARD_COPY,
		CLIPBOARD_PASTE,
	};
	struct CLIPBOARD_PARAM {
		// for QUERY_COPY
		int SelectedVertexCount;
		int SelectedLineCount;
		int SelectedFaceCount;
		// for COPY, PASTE
		void *Buffer;		// COPY: call AllocBuffer(); PASTE (read only)
		size_t BufferSize;	// COPY: call AllocBuffer(); PASTE (read only)
		// for COPY
		std::pair<UINT,UINT> *OrgVertexID;	// <object_id, vertex_id>
		std::pair<UINT,UINT> *OrgFaceID;	// <object_id, face_id>

		CLIPBOARD_PARAM() : SelectedVertexCount(0), SelectedLineCount(0), SelectedFaceCount(0), 
			Buffer(nullptr), BufferSize(0), OrgVertexID(nullptr), OrgFaceID(nullptr) { }
		void *AllocBuffer(size_t size);
		std::vector<std::pair<UINT,UINT>> MakeOrgVertexIDTable(); // <object_id, vertex_id>
		std::vector<std::pair<UINT,UINT>> MakeOrgFaceIDTable(); // <object_id, face_id>
		std::map<std::pair<UINT,UINT>,int> MakeOrgVertexIDToNewIndexMap(); // <<object_id, vertex_id>, index>
		std::map<std::pair<UINT,UINT>,int> MakeOrgFaceIDToNewIndexMap(); // <<object_id, face_id>, index>
	};
	virtual bool OnUseClipboard(MQDocument doc, MQObject obj, CLIPBOARD_METHOD method, CLIPBOARD_PARAM& param);


	// Begin the callback procedure
	// コールバック処理の開始
	void BeginCallback(void *option);

	// Close a window
	// ウインドウを閉じる
	void WindowClose();


private:
	struct StationCallbackInnerOption {
		MQStationPlugin *this_ptr;
		void *option;
	};

	// Callback for a procedure by the plug-in
	// プラグイン内からの処理に対するコールバック
	static BOOL CALLBACK StationCallback(MQDocument doc, void *option);

protected:
	// Implementation for the callback
	// コールバックに対する実装部
	virtual bool ExecuteCallback(MQDocument doc, void *option) = 0;

public:
	// Options for visibility in CreateDrawObject() (Multiple values are enabled.)
	// CreateDrawObject()のvisibilityに渡す引数（複数指定可）
	enum DRAW_OBJECT_VISIBILITY {
		DRAW_OBJECT_POINT = 1,		// Show vertices | 頂点を表示
		DRAW_OBJECT_LINE = 2,		// Show lines    | ラインを表示
		DRAW_OBJECT_FACE = 4,		// Show faces    | 面を表示
		DRAW_FORCE_DWORD = 0xFFFFFFFF,
	};
#ifdef _WIN32
	__declspec(deprecated) typedef DRAW_OBJECT_VISIBILITY DRAW_OBJECT_VIISIBILITY;
#endif

	// Parameters for GetSnappedPos()
	// GetSnappedPos()のパラメータ
	struct GET_SNAP_PARAM {
		BOOL SnapEyeDir;		// Snap on the eye direction| 視線方向へのスナップ
		BOOL IgnoreSelected;	// Ignore selected elements | 選択部を無視
		BOOL IgnoreCurObj;		// Ignore current object    | カレントオブジェクトを無視

		GET_SNAP_PARAM(){
			SnapEyeDir = FALSE;
			IgnoreSelected = FALSE;
			IgnoreCurObj = FALSE;
		}
	};

	// Add a drawing object in OnDraw()
	// OnDraw()時に描画オブジェクトを追加
	MQObject CreateDrawingObject(MQDocument doc, DRAW_OBJECT_VISIBILITY visibility, BOOL instant=TRUE);
	MQObject CreateDrawingObjectByClone(MQDocument doc, MQObject clone_source, DRAW_OBJECT_VISIBILITY visibility, BOOL instant=TRUE);

	// Add a material for a drawing object in OnDraw()
	// OnDraw()時に描画オブジェクト用マテリアルを追加
	MQMaterial CreateDrawingMaterial(MQDocument doc, int& index, BOOL instant=TRUE);

	// Add a drawing text in OnDraw()
	// OnDraw()時に描画テキストを追加
	MQDrawingText CreateDrawingText(MQDocument doc, const wchar_t *text, DRAWING_TEXT_PARAM& param, BOOL instant=TRUE);

	// Delete a drawing object
	// 描画オブジェクトを削除する
	void DeleteDrawingObject(MQDocument doc, MQObject obj);

	// Delete a material for drawing objects
	// 描画オブジェクト用マテリアルを削除する
	void DeleteDrawingMaterial(MQDocument doc, MQMaterial mat);

	// Delete a drawing text
	// 描画テキストを削除する
	void DeleteDrawingText(MQDocument doc, MQDrawingText text);

	// Get a current undo state
	// 現在のアンドゥの状態カウンタを取得
	int GetCurrentUndoState(MQDocument doc);
	struct UNDO_STATE {
		int state;
		bool can_undo;
		bool can_redo;
	};
	bool GetCurrentUndoState(MQDocument doc, UNDO_STATE& undo_state);

	// Execute an undo.
	bool ExecuteUndo(MQDocument doc);
	// Execute an redo.
	bool ExecuteRedo(MQDocument doc);
	// Clear an undo-buffer.
	bool ClearUndoBuffer(MQDocument doc);
	// Declare how much memory is used for undo in this plugin
	// プラグインのアンドゥバッファの使用メモリーサイズを設定
	void SetUndoUsedMemory(MQDocument doc, int target_undo_state, size_t data_size);

	// Get a snapped position
	// スナップ位置を取得
#ifdef _WIN32
	__declspec(deprecated) MQPoint GetSnappedPos(MQScene scene, const MQPoint& p, SNAP_GRID_TYPE type);
#endif
	MQPoint GetSnappedPos(MQScene scene, const MQPoint& p, const EDIT_OPTION& option, const GET_SNAP_PARAM& snap_param);
};


// Command plug-in class
// コマンド型プラグインクラス
/*
	コマンドプラグインのベースとなるクラスです。
	コマンドプラグインはコマンドパネル上にボタンを追加し、マウスなどの
	操作に応じた独自の処理を行うことができます。
*/
class MQCommandPlugin : public MQStationPlugin
{
public:
	// Parameters for mouse events
	// マウスイベント時のパラメータ
	struct MOUSE_BUTTON_STATE {
		POINT MousePos;	// Mouse cursor position | マウスカーソルの位置
		int Wheel;		// Wheel rotation        | マウスホイールの回転量（WHEEL_DELTAの倍数または約数）
		BOOL LButton;	// Left button           | 左ボタンが押されているか
		BOOL MButton;	// Middle button         | 中ボタンが押されているか
		BOOL RButton;	// Right button          | 右ボタンが押されているか
		BOOL Shift;		// Shift key             | Shiftキーが押されているか
		BOOL Ctrl;		// Ctrl key              | Ctrlキーが押されているか
		BOOL Alt;		// Alt key               | Altキーが押されているか
		float Pressure;	// For tablet or touch   | タブレットやタッチ操作時の圧力 (0-1)
	};

	// A type using for HitTest()
	// HitTest()で使用される型
	enum HIT_TYPE {
		HIT_TYPE_NONE	= 0,//なし
		HIT_TYPE_VERTEX	= 1,//頂点
		HIT_TYPE_LINE	= 2,//ライン
		HIT_TYPE_FACE	= 4,//面
	};

	// Parameters for HitTest()
	// HitTest()のパラメータ
	struct HIT_TEST_PARAM {
		// input
		BOOL TestVertex;	// 頂点の検知を行う
		BOOL TestLine;		// ラインを検知
		BOOL TestFace;		// 面を検知
		BOOL DisableFrontOnly; // 前面のみの検知を無効化
		BOOL DisableCoverByFace;   // 手前の面による頂点・ラインの遮蔽を無効化

		// output
		HIT_TYPE HitType;	// 検知されたタイプ
		MQPoint HitPos;		// 検知された位置
		int ObjectIndex;	// 検知されたオブジェクト
		int VertexIndex;	// 頂点のインデックス（頂点が検知されたときのみ）
		int LineIndex;		// ラインのインデックス（ラインが検知されたときのみ）
		int FaceIndex;		// 面のインデックス（ラインまたは面が検知されたときのみ）

		HIT_TEST_PARAM(){
			TestVertex = TestLine = TestFace = TRUE;
			DisableFrontOnly = FALSE;
			DisableCoverByFace = FALSE;
		}
	};

public:
	// Constructor
	// コンストラクタ
	MQCommandPlugin();

	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) { return MQPLUGIN_TYPE_COMMAND; }
	// 表示・非表示状態の返答
	virtual BOOL IsActivated(MQDocument doc);
	// コールバックに対する実装部
	virtual bool ExecuteCallback(MQDocument doc, void *option);

	// When a left button is pressed
	// 左ボタンが押されたとき
	virtual BOOL OnLeftButtonDown(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a mouse is moved with pressing a left button
	// 左ボタンが押されながらマウスが移動したとき
	virtual BOOL OnLeftButtonMove(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a left button is released
	// 左ボタンが離されたとき
	virtual BOOL OnLeftButtonUp(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a middle button is pressed
	// 中ボタンが押されたとき
	virtual BOOL OnMiddleButtonDown(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a mouse is moved with pressing a middle button
	// 中ボタンが押されながらマウスが移動したとき
	virtual BOOL OnMiddleButtonMove(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a middle button is released
	// 中ボタンが離されたとき
	virtual BOOL OnMiddleButtonUp(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a right button is pressed
	// 右ボタンが押されたとき
	virtual BOOL OnRightButtonDown(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a mouse is moved with pressing a right button
	// 右ボタンが押されながらマウスが移動したとき
	virtual BOOL OnRightButtonMove(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a right button is released
	// 右ボタンが離されたとき
	virtual BOOL OnRightButtonUp(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a mouse is moved
	// マウスが移動したとき
	virtual BOOL OnMouseMove(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a mouse wheel is rotated
	// マウスのホイールが回転したとき
	virtual BOOL OnMouseWheel(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a key is pressed
	// キーが押されたとき
	virtual BOOL OnKeyDown(MQDocument doc, MQScene scene, int key, MOUSE_BUTTON_STATE& state);
	// When a key is released
	// キーが離されたとき
	virtual BOOL OnKeyUp(MQDocument doc, MQScene scene, int key, MOUSE_BUTTON_STATE& state);

	// Reserve updating a scene
	// シーンの再描画を予約する
	void RedrawScene(MQScene scene);
	// Reserve updating all scenes
	// すべてのシーンの再描画を予約する
	void RedrawAllScene();
	// Detect a target at the specified position at the scene
	// シーン内の指定された位置にあるものを検知
	bool HitTest(MQScene scene, POINT p, HIT_TEST_PARAM& param);
	// Detect a target at the specified position in objects at the scene
	// 指定された位置にあるものを指定したオブジェクト内から検知
	bool HitTestObjects(MQScene scene, POINT p, const std::vector<MQObject>& objects, HIT_TEST_PARAM& param);
	// Set a mouse cursor for views
	// ビュー用マウスカーソルを設定
	void SetMouseCursor(HCURSOR cursor);
	// Set a string displayed on a status bar
	// ステータスバーの文字列を設定
	void SetStatusString(const char *str);
	void SetStatusString(const wchar_t *str);
	// Set a help page
	// ヘルプページの設定
	void SetHelpPage(const wchar_t *url);
	// Apply a layout to OptionPanel
	// オプションパネルにレイアウトを設定
	void ApplyLayoutToOptionPanel();
	// Specify whether menu or command has priority over key
	// キーをメニュー・コマンドどちらを優先するか設定
	void SetKeyPriortizeMenu(bool flag);
};


class MQWaitCursorChanger
{
public:
	MQWaitCursorChanger(MQBasePlugin *plugin, bool active = true)
	{
		m_Plugin = plugin;
		if(active){
			m_Active = true;
#ifdef _WIN32
			m_OrgCursor = m_Plugin->GetScreenMouseCursor();
			m_Plugin->SetScreenMouseCursor(m_Plugin->GetResourceCursor(MQBasePlugin::MQCURSOR_WAIT));
#endif
		}else{
			m_Active = false;
#ifdef _WIN32
			m_OrgCursor = NULL;
#endif
		}
	}
	~MQWaitCursorChanger()
	{
		End();
	}
	void Begin(){
		if(!m_Active){
			m_Active = true;
#ifdef _WIN32
			m_OrgCursor = m_Plugin->GetScreenMouseCursor();
			m_Plugin->SetScreenMouseCursor(m_Plugin->GetResourceCursor(MQBasePlugin::MQCURSOR_WAIT));
#endif
		}
	}
	void End(){
		if(m_Active){
			m_Active = false;
#ifdef _WIN32
			m_Plugin->SetScreenMouseCursor(m_OrgCursor);
#endif
		}
	}

private:
	MQBasePlugin *m_Plugin;
	bool m_Active;
#ifdef _WIN32
	HCURSOR m_OrgCursor;
#endif
};


// Get a plug-in class
// プラグインのベースクラスを返す
extern MQBasePlugin *GetPluginClass();


#endif //_MQBASEPLUGIN_H_
