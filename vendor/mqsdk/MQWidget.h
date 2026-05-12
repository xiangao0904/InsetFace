//---------------------------------------------------------------------------
//
//   MQWidget
//
//          Copyright(C) 1999-2023, tetraface Inc.
//
//	   A class for accessing widgets to construct a graphical user interfaces 
//    such as buttons, check boxes, dialogs and so on.
//
//    　ボタン、チェックボックスやダイアログなどのGUIを構築するためのウィ
//    ジェットにアクセスするクラスです。
//
//---------------------------------------------------------------------------

#ifndef _MQWIDGET_H_
#define _MQWIDGET_H_

#include "MQPlugin.h"
#include <vector>
#include <set>
#include <map>
#include <string>
#include <memory>

#ifdef _WIN32
#ifdef CreateWindow
#undef CreateWindow
inline HWND CreateWindow(LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
#ifdef UNICODE
	return CreateWindowW(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
#else
	return CreateWindowA(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
#endif
}
#endif
#ifdef MessageBox
#undef MessageBox
inline int MessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCation, UINT uType)
{
#ifdef UNICODE
	return MessageBoxW(hWnd, lpText, lpCation, uType);
#else
	return MessageBoxA(hWnd, lpText, lpCation, uType);
#endif
}
#endif
#ifdef DrawText
#undef DrawText
inline int DrawText(HDC hDC, LPCTSTR lpchText, int nCount, LPRECT lpRect, UINT uFormat)
{
#ifdef UNICODE
	return DrawTextW(hDC, lpchText, nCount, lpRect, uFormat);
#else
	return DrawTextA(hDC, lpchText, nCount, lpRect, uFormat);
#endif
}
#endif
#endif

class MQStationPlugin;
class MQWidgetBase;
class MQFrame;
class MQDockFrame;
class MQGroupBox;
class MQTab;
class MQButton;
class MQCheckBox;
class MQRadioButton;
class MQComboBox;
class MQListBox;
class MQCheckListBox;
class MQTreeListBox;
class MQLabel;
class MQEdit;
class MQMemo;
class MQSpinBox;
class MQDoubleSpinBox;
class MQSlider;
class MQProgressBar;
class MQScrollBar;
class MQScrollBox;
class MQColorPanel;
class MQPaintBox;
class MQWindow;
class MQDockWindow;
class MQMenuBar;
class MQMenuItem;
class MQCanvas;

#if defined(_MSC_VER) && (_MSC_VER >= 1600)		// VC2010 or later
#define MQWidgetSharedPtr std::shared_ptr
#elif defined(_MSC_VER) && (_MSC_VER >= 1500)	// VC2008 or later
#define MQWidgetSharedPtr std::tr1::shared_ptr
#else
#define MQWidgetSharedPtr std::shared_ptr
#endif


namespace MQKeyCode {
enum KEY_CODE
{
#ifdef _WINDOWS
	KEY_NONE = 0,
	KEY_BACK = 8,
	KEY_TAB = 9,
	KEY_ENTER = 13,
	KEY_SHIFT = 16,
	KEY_CTRL = 17,
	KEY_ALT = 18,
	KEY_ESC = 27,
	KEY_SPACE = 32,
	KEY_PAGEUP = 33,
	KEY_PAGEDOWN = 34,
	KEY_END = 35,
	KEY_HOME = 36,
	KEY_LEFT = 37,
	KEY_UP = 38,
	KEY_RIGHT = 39,
	KEY_DOWN = 40,
	KEY_INSERT = 45,
	KEY_DELETE = 46,
	KEY_0 = 48,
	KEY_1 = 49,
	KEY_2 = 50,
	KEY_3 = 51,
	KEY_4 = 52,
	KEY_5 = 53,
	KEY_6 = 54,
	KEY_7 = 55,
	KEY_8 = 56,
	KEY_9 = 57,
	KEY_A = 65,
	KEY_B = 66,
	KEY_C = 67,
	KEY_D = 68,
	KEY_E = 69,
	KEY_F = 70,
	KEY_G = 71,
	KEY_H = 72,
	KEY_I = 73,
	KEY_J = 74,
	KEY_K = 75,
	KEY_L = 76,
	KEY_M = 77,
	KEY_N = 78,
	KEY_O = 79,
	KEY_P = 80,
	KEY_Q = 81,
	KEY_R = 82,
	KEY_S = 83,
	KEY_T = 84,
	KEY_U = 85,
	KEY_V = 86,
	KEY_W = 87,
	KEY_X = 88,
	KEY_Y = 89,
	KEY_Z = 90,
	KEY_NUMPAD0 = 96,
	KEY_NUMPAD1 = 97,
	KEY_NUMPAD2 = 98,
	KEY_NUMPAD3 = 99,
	KEY_NUMPAD4 = 100,
	KEY_NUMPAD5 = 101,
	KEY_NUMPAD6 = 102,
	KEY_NUMPAD7 = 103,
	KEY_NUMPAD8 = 104,
	KEY_NUMPAD9 = 105,
	KEY_NUMPADMUL = 106,
	KEY_NUMPADADD = 107,
	KEY_NUMPADSUB = 109,
	KEY_NUMPADDOT = 110,
	KEY_NUMPADDIV = 111,
	KEY_F1 = 112,
	KEY_F2 = 113,
	KEY_F3 = 114,
	KEY_F4 = 115,
	KEY_F5 = 116,
	KEY_F6 = 117,
	KEY_F7 = 118,
	KEY_F8 = 119,
	KEY_F9 = 120,
	KEY_F10 = 121,
	KEY_F11 = 122,
	KEY_F12 = 123,
	KEY_SEMICOLON = 186, // JP=':'
	KEY_EQUAL = 187, // JP=';'
	KEY_COMMA = 188,
	KEY_MINUS = 189,
	KEY_PERIOD = 190,
	KEY_SLASH = 191,
	KEY_BACKQUOTE = 192, // JP='@'
	KEY_LEFTSQUAREBRACKET = 219,
	KEY_BACKSLASH = 220, // JP='¥'
	KEY_RIGHTSQUAREBRACKET = 221,
	KEY_SINGLEQUOTE = 222, // JP='^'
	KEY_PAUSE = 19,
	KEY_JP_HENKAN = 28,
	KEY_JP_MUHENKAN = 29,
	KEY_JP_YEN = 226,
	KEY_LAST = 255,
#endif
#if __APPLE__
	KEY_NONE = -1,
	KEY_BACK = 51, // Delete (back)
	KEY_TAB = 48,
	KEY_ENTER = 36,  // Return
	KEY_SHIFT = 56,  // Left shift
	KEY_RSHIFT = 60, // Right shift
	KEY_CTRL = 59,   // Left control
	KEY_RCTRL = 62,  // Right control
	KEY_ALT = 58,    // Left option
	KEY_RALT = 61,   // Right option
	KEY_COMMAND = 55,// Left command
	KEY_RCOMMAND = 54,//Right command
	KEY_ESC = 53,
	KEY_SPACE = 49,
	KEY_PAGEUP = 116,
	KEY_PAGEDOWN = 121,
	KEY_END = 119,
	KEY_HOME = 115,
	KEY_LEFT = 123,
	KEY_UP = 126,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	//KEY_INSERT = ,
	KEY_DELETE = 117, // Delete x->
	KEY_0 = 29,
	KEY_1 = 18,
	KEY_2 = 19,
	KEY_3 = 20,
	KEY_4 = 21,
	KEY_5 = 23,
	KEY_6 = 22,
	KEY_7 = 26,
	KEY_8 = 28,
	KEY_9 = 25,
	KEY_A = 0,
	KEY_B = 11,
	KEY_C = 8,
	KEY_D = 2,
	KEY_E = 14,
	KEY_F = 3,
	KEY_G = 5,
	KEY_H = 4,
	KEY_I = 34,
	KEY_J = 38,
	KEY_K = 40,
	KEY_L = 37,
	KEY_M = 46,
	KEY_N = 45,
	KEY_O = 31,
	KEY_P = 35,
	KEY_Q = 12,
	KEY_R = 15,
	KEY_S = 1,
	KEY_T = 17,
	KEY_U = 32,
	KEY_V = 9,
	KEY_W = 13,
	KEY_X = 7,
	KEY_Y = 16,
	KEY_Z = 6,
	KEY_NUMPAD0 = 82,
	KEY_NUMPAD1 = 83,
	KEY_NUMPAD2 = 84,
	KEY_NUMPAD3 = 85,
	KEY_NUMPAD4 = 86,
	KEY_NUMPAD5 = 87,
	KEY_NUMPAD6 = 88,
	KEY_NUMPAD7 = 89,
	KEY_NUMPAD8 = 91,
	KEY_NUMPAD9 = 92,
	KEY_NUMPADDOT = 65,
	KEY_NUMPADMUL = 67,
	KEY_NUMPADADD = 69,
	KEY_NUMPADDIV = 75,
	KEY_NUMPADSUB = 78,
	KEY_NUMPADEQUAL = 81,
	KEY_NUMPADENTER = 76,
	KEY_F1 = 122,
	KEY_F2 = 120,
	KEY_F3 = 99,
	KEY_F4 = 118,
	KEY_F5 = 96,
	KEY_F6 = 97,
	KEY_F7 = 98,
	KEY_F8 = 100,
	KEY_F9 = 101,
	KEY_F10 = 109,
	KEY_F11 = 103,
	KEY_F12 = 111,
	KEY_F13 = 105,
	KEY_F14 = 107,
	KEY_F15 = 113,
	KEY_F16 = 106,
	KEY_F17 = 64,
	KEY_F18 = 79,
	KEY_F19 = 80,
	//KEY_F20 = 90,
	KEY_MINUS = 27,
	KEY_EQUAL = 24, // JP='^'
	KEY_BACKSLASH = 42, // JP=']'
	KEY_LEFTBRACKET = 33, // JP='@'
	KEY_RIGHTBRACKET = 30, // JP='['
	KEY_SEMICOLON = 41,
	KEY_QUOTE = 39, //JP=':'
	KEY_BACKQUOTE = 50,
	KEY_COMMA = 43,
	KEY_PERIOD = 47,
	KEY_SLASH = 44,
	KEY_JP_YEN = 93,
	KEY_JP_UNDERSCORE = 94,
	KEY_JP_EISUU = 102,
	KEY_JP_KANA = 104,
	KEY_FN = 63, // Mac only
	KEY_CLEAR = 71, // Mac only
	KEY_LAST = 255,
#endif
};
} //MQKeyCode

namespace MQSystemWidget {
	enum WidgetType {
		MainWindow,
		OptionPanel,
	};
}

struct MQWidgetMouseParam {
	POINT ClientPos; // Mouse cursor position on the client area
	POINT ScreenPos; // Mouse cursor position on the screen
	POINT DownPos;   // Clicked position on the client area
	POINT LastPos;   // Mouse cursor position on the client area at the last time
	int Wheel;       // Rotation of the mouse wheel (WHEEL_DELTA based value)
	bool LButton;
	bool MButton;
	bool RButton;
	bool Shift;
	bool Ctrl;
	bool Alt;
	float Pressure;  // For tablet or touch (0-1)
	bool Finished;

	MQWidgetMouseParam(){
		ClientPos.x = 0;
		ClientPos.y = 0;
		ScreenPos.x = 0;
		ScreenPos.y = 0;
		DownPos.x = 0;
		DownPos.y = 0;
		Wheel = 0;
		LButton = false;
		MButton = false;
		RButton = false;
		Shift = false;
		Ctrl = false;
		Alt = false;
		Pressure = 0.0f;
		Finished = false;
	};
};

struct MQWidgetKeyParam {
	MQKeyCode::KEY_CODE Key;
	bool AutoRepeat;
	bool LButton;
	bool MButton;
	bool RButton;
	bool Shift;
	bool Ctrl;
	bool Alt;
	bool Finished;

	MQWidgetKeyParam(){
		Key = MQKeyCode::KEY_NONE;
		AutoRepeat = false;
		LButton = false;
		MButton = false;
		RButton = false;
		Shift = false;
		Ctrl = false;
		Alt = false;
		Finished = false;
	};
};

struct MQWidgetPaintParam {
	MQCanvas *Canvas;
	bool *Interrupted; // for hardware rendering

	MQWidgetPaintParam(){
		Canvas = NULL;
		Interrupted = NULL;
	};
};

struct MQWidgetCloseQueryParam {
	bool Canceled;

	MQWidgetCloseQueryParam(){
		Canceled = false;
	};
};

struct MQWidgetDragOverParam {
	POINT ClientPos; // Mouse cursor position on the client area
	POINT ScreenPos; // Mouse cursor position on the screen
	bool Result;

	MQWidgetDragOverParam(){
		ClientPos.x = 0;
		ClientPos.y = 0;
		ScreenPos.x = 0;
		ScreenPos.y = 0;
		Result = false;
	};
};

struct MQWidgetDropFilesParam {
	POINT ClientPos; // Mouse cursor position on the client area
	POINT ScreenPos; // Mouse cursor position on the screen
	std::vector<const wchar_t*> Files;

	MQWidgetDropFilesParam(){
		ClientPos.x = 0;
		ClientPos.y = 0;
		ScreenPos.x = 0;
		ScreenPos.y = 0;
	};
};

struct MQListBoxDrawItemParam {
	MQCanvas *Canvas;
	int ItemIndex;
	int X;
	int Y;
	int Width;
	int Height;

	MQListBoxDrawItemParam(){
		Canvas = NULL;
	};
};

struct MQTreeListBoxDrawItemParam {
	MQCanvas *Canvas;
	int ItemIndex;
	int ItemID;
	int X;
	int Y;
	int Width;
	int Height;

	MQTreeListBoxDrawItemParam(){
		Canvas = NULL;
	};
};

struct MQMemoDrawItemParam {
	MQCanvas *Canvas;
	int Line;
	size_t StartPos;
	size_t EndPos;
	int X;
	int Y;
	int Width;
	int Height;

	MQMemoDrawItemParam(){
		Canvas = NULL;
	};
};

class MQWidgetEventClosureBase
{
public:
	MQWidgetEventClosureBase() { }

	virtual BOOL invoke(MQWidgetBase *sender, MQDocument doc, void *ptr) = 0;
	virtual bool isEqual(const MQWidgetEventClosureBase *c) const = 0;
	virtual MQWidgetBase *getReceiver() = 0;
	virtual void *getFunction() = 0;
};

struct MQCanvasColor
{
	int r, g, b, a;

	MQCanvasColor() { }
	MQCanvasColor(int _r, int _g, int _b) : r(_r), g(_g), b(_b), a(255) { }
	MQCanvasColor(int _r, int _g, int _b, int _a) : r(_r), g(_g), b(_b), a(_a) { }

	void SetRGB(const MQCanvasColor& col){
		r = col.r;
		g = col.g;
		b = col.b;
	}

	void SetRGBA(const MQCanvasColor& col){
		r = col.r;
		g = col.g;
		b = col.b;
		a = col.a;
	}

	void Clip(int minval = 0, int maxval = 255){
		if(r < minval) r = minval;
		if(r > maxval) r = maxval;
		if(g < minval) g = minval;
		if(g > maxval) g = maxval;
		if(b < minval) b = minval;
		if(b > maxval) b = maxval;
		if(a < minval) a = minval;
		if(a > maxval) a = maxval;
	}

	void Blend(const MQCanvasColor& col2, double ratio){
		r = (int)ceil(r * (1-ratio) + col2.r * ratio + 0.5);
		g = (int)ceil(g * (1-ratio) + col2.g * ratio + 0.5);
		b = (int)ceil(b * (1-ratio) + col2.b * ratio + 0.5);
		a = (int)ceil(a * (1-ratio) + col2.a * ratio + 0.5);
	}

	static MQCanvasColor Blend(const MQCanvasColor& col1, const MQCanvasColor& col2, double ratio){
		return MQCanvasColor(
			(int)ceil(col1.r * (1-ratio) + col2.r * ratio + 0.5), 
			(int)ceil(col1.g * (1-ratio) + col2.g * ratio + 0.5), 
			(int)ceil(col1.b * (1-ratio) + col2.b * ratio + 0.5), 
			(int)ceil(col1.a * (1-ratio) + col2.a * ratio + 0.5));
	}

	bool operator == (const MQCanvasColor& c){
		return (r == c.r && g == c.g && b == c.b && a == c.a);
	}
	bool operator != (const MQCanvasColor& c){
		return !(r == c.r && g == c.g && b == c.b && a == c.a);
	}
	MQCanvasColor& operator += (const MQCanvasColor& p){
		r += p.r;
		g += p.g;
		b += p.b;
		a += p.a;
		return *this;
	}
	MQCanvasColor& operator -= (const MQCanvasColor& p){
		r -= p.r;
		g -= p.g;
		b -= p.b;
		a -= p.a;
		return *this;
	}
	friend MQCanvasColor operator + (const MQCanvasColor& p1, const MQCanvasColor& p2){
		return MQCanvasColor(p1.r+p2.r, p1.g+p2.g, p1.b+p2.b, p1.a+p2.a);
	}
	friend MQCanvasColor operator - (const MQCanvasColor& p1, const MQCanvasColor& p2){
		return MQCanvasColor(p1.r-p2.r, p1.g-p2.g, p1.b-p2.b, p1.a-p2.a);
	}
};


// Base class for all widgets
// すべてのウィジェットの基底クラス
class MQWidgetBase
{
public:
	enum LAYOUT_TYPE {
		LAYOUT_AUTO,
		LAYOUT_FIXED,
		LAYOUT_HINTSIZE,
		LAYOUT_FILL,
		LAYOUT_FREE,
	};

public:
	// Constructor
	// コンストラクタ
	MQWidgetBase();
	MQWidgetBase(int id);

	// Destructor
	// デストラクタ
	virtual ~MQWidgetBase();

	// Get ID.
	// IDを取得します。
	int GetID() const;

	// Add a child widget.
	// 子ウィジェットを追加します。
	int AddChild(MQWidgetBase *child);

	// Insert a child widget at the specified index.
	// 子ウィジェットを追加します。
	int InsertChild(MQWidgetBase *child, int index);

	// Remove a child widget. (Not delete it.)
	// 子ウィジェットを切り離します。（削除はされません）
	void RemoveChild(MQWidgetBase *child);

	// Get an index of a child widget.
	// 子ウィジェットのインデックスを取得します。
	int GetIndexOfChild(MQWidgetBase *child);

	std::wstring GetName();
	void SetName(const std::wstring& value);

	__int64 GetTag();
	void SetTag(__int64 value);

	bool GetEnabled();
	void SetEnabled(bool value);
	
	bool GetVisible();
	void SetVisible(bool value);
	
	LAYOUT_TYPE GetHorzLayout();
	void SetHorzLayout(LAYOUT_TYPE value);
	
	LAYOUT_TYPE GetVertLayout();
	void SetVertLayout(LAYOUT_TYPE value);

	int GetWidth();
	// Note: SetWidth is not recommended. Please use SetHintSizeRateX as possible.
	//       SetWidthは推奨されません。可能な限りSetHintSizeRateXを使用してください。
	void SetWidth(int value);
	
	int GetHeight();
	// Note: SetHeight is not recommended. Please use SetHintSizeRateY as possible.
	//       SetHeightは推奨されません。可能な限りSetHintSizeRateYを使用してください。
	void SetHeight(int value);

	double GetFillRateX();
	void SetFillRateX(double value);
	
	double GetFillRateY();
	void SetFillRateY(double value);
	
	double GetFillBeforeRate();
	void SetFillBeforeRate(double value);
	
	double GetFillAfterRate();
	void SetFillAfterRate(double value);
	
	double GetInSpace();
	void SetInSpace(double value);
	
	double GetOutSpace();
	void SetOutSpace(double value);

	double GetHintSizeRateX();
	void SetHintSizeRateX(double value);

	double GetHintSizeRateY();
	void SetHintSizeRateY(double value);

	int GetCellColumn();
	void SetCellColumn(int value);

	std::wstring GetHintText();
	void SetHintText(const std::wstring& text);

	void SetCursor(HCURSOR cursor);

	POINT GetJustSize(int max_width = -1, int max_height = -1);

	bool ClientToScreen(int client_x, int client_y, int *screen_x, int *screen_y);
	bool ScreenToClient(int screen_x, int screen_y, int *client_x, int *client_y);
	bool ClientToClient(int client_x, int client_y, MQWidgetBase *target, int *target_x, int *target_y);

	void Repaint(bool immediate = false);
	void RefreshPaint();

	void CaptureMouse(bool value);

	bool CanReceiveMouseEvent();


	// Find a widget by the ID.
	// IDによってウィジェットを検索します。
	static MQWidgetBase *FindWidgetByID(int id);

	// Get the specified system widget ID.
	// 指定したシステムウィジェットのIDを取得します。
	static int GetSystemWidgetID(MQSystemWidget::WidgetType type);

	static int GetBaseRateSize(double rate);

	static void GetDefaultFrameColor(int& r, int& g, int& b, int& a);
	static void GetDefaultBackColor(int& r, int& g, int& b, int& a);
	static void GetDefaultTextColor(int& r, int& g, int& b, int& a);
	static void GetDefaultTitleBackColor(int& r, int& g, int& b, int& a);
	static void GetDefaultTitleTextColor(int& r, int& g, int& b, int& a);
	static void GetDefaultListBackColor(int& r, int& g, int& b, int& a);
	static void GetDefaultListTextColor(int& r, int& g, int& b, int& a);
	static void GetDefaultListActiveColor(int& r, int& g, int& b, int& a);
	static void GetDefaultListActiveTextColor(int& r, int& g, int& b, int& a);
	static void GetDefaultEditBackColor(int& r, int& g, int& b, int& a);
	static void GetDefaultEditTextColor(int& r, int& g, int& b, int& a);
	static void GetDefaultEditSelectionColor(int& r, int& g, int& b, int& a);
	static void GetDefaultEditSelectionTextColor(int& r, int& g, int& b, int& a);
	static MQCanvasColor GetDefaultFrameColor();
	static MQCanvasColor GetDefaultBackColor();
	static MQCanvasColor GetDefaultTextColor();
	static MQCanvasColor GetDefaultTitleBackColor();
	static MQCanvasColor GetDefaultTitleTextColor();
	static MQCanvasColor GetDefaultListBackColor();
	static MQCanvasColor GetDefaultListTextColor();
	static MQCanvasColor GetDefaultListActiveColor();
	static MQCanvasColor GetDefaultListActiveTextColor();
	static MQCanvasColor GetDefaultEditBackColor();
	static MQCanvasColor GetDefaultEditTextColor();
	static MQCanvasColor GetDefaultEditSelectionColor();
	static MQCanvasColor GetDefaultEditSelectionTextColor();

	static void RegisterSubCommandButton(MQStationPlugin *plugin, MQButton *button, const char *command_str);

	static void EnterEventLoop(unsigned int timeout_ms = (unsigned int)-1, bool empty_return = false);
	static void ExitEventLoop();

	static bool CanReceiveTextFromClipboard();

	static bool GetKeyState(MQKeyCode::KEY_CODE key);

	template<typename T> void AddShowEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument), bool prior = false);
	template<typename T> void RemoveShowEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument));
	template<typename T> bool ExistsShowEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) const;

	template<typename T> void AddHideEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument), bool prior = false);
	template<typename T> void RemoveHideEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument));
	template<typename T> bool ExistsHideEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) const;

	template<typename T> void AddMoveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument), bool prior = false);
	template<typename T> void RemoveMoveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument));
	template<typename T> bool ExistsMoveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) const;

	template<typename T> void AddResizeEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument), bool prior = false);
	template<typename T> void RemoveResizeEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument));
	template<typename T> bool ExistsResizeEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) const;

	template<typename T> void AddLeftDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior = false);
	template<typename T> void RemoveLeftDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&));
	template<typename T> bool ExistsLeftDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const;

	template<typename T> void AddLeftUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior = false);
	template<typename T> void RemoveLeftUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&));
	template<typename T> bool ExistsLeftUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const;

	template<typename T> void AddLeftDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior = false);
	template<typename T> void RemoveLeftDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&));
	template<typename T> bool ExistsLeftDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const;

	template<typename T> void AddMiddleDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior = false);
	template<typename T> void RemoveMiddleDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&));
	template<typename T> bool ExistsMiddleDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const;

	template<typename T> void AddMiddleUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior = false);
	template<typename T> void RemoveMiddleUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&));
	template<typename T> bool ExistsMiddleUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const;

	template<typename T> void AddMiddleDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior = false);
	template<typename T> void RemoveMiddleDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&));
	template<typename T> bool ExistsMiddleDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const;

	template<typename T> void AddRightDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior = false);
	template<typename T> void RemoveRightDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&));
	template<typename T> bool ExistsRightDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const;

	template<typename T> void AddRightUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior = false);
	template<typename T> void RemoveRightUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&));
	template<typename T> bool ExistsRightUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const;

	template<typename T> void AddRightDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior = false);
	template<typename T> void RemoveRightDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&));
	template<typename T> bool ExistsRightDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const;

	template<typename T> void AddMouseMoveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior = false);
	template<typename T> void RemoveMouseMoveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&));
	template<typename T> bool ExistsMouseMoveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const;

	template<typename T> void AddMouseWheelEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior = false);
	template<typename T> void RemoveMouseWheelEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&));
	template<typename T> bool ExistsMouseWheelEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const;

	template<typename T> void AddMouseEnterEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument), bool prior = false);
	template<typename T> void RemoveMouseEnterEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument));
	template<typename T> bool ExistsMouseEnterEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) const;

	template<typename T> void AddMouseLeaveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument), bool prior = false);
	template<typename T> void RemoveMouseLeaveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument));
	template<typename T> bool ExistsMouseLeaveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) const;

	template<typename T> void AddKeyDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetKeyParam&), bool prior = false);
	template<typename T> void RemoveKeyDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetKeyParam&));
	template<typename T> bool ExistsKeyDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetKeyParam&)) const;

	template<typename T> void AddKeyUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetKeyParam&), bool prior = false);
	template<typename T> void RemoveKeyUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetKeyParam&));
	template<typename T> bool ExistsKeyUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetKeyParam&)) const;

	template<typename T> void AddTimerEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument), unsigned int timeout_ms, bool overwrite = false);
	template<typename T> void RemoveTimerEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument));
	template<typename T> bool ExistsTimerEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) const;

public:
	enum {
		NullID = 0,
	};

protected:
	int m_ID;
	bool m_IDOwner;

	void RegisterID();

	void AddEventCallback(const char *event_type, MQWidgetSharedPtr<MQWidgetEventClosureBase> closure, bool prior);
	void RemoveEventCallback(const char *event_type, MQWidgetSharedPtr<MQWidgetEventClosureBase> closure);
	bool ExistsEventCallback(const char *event_type, MQWidgetSharedPtr<MQWidgetEventClosureBase> closure) const;
	static BOOL MQAPICALL EventCallback(MQDocument doc, void **params, void *option);

	void AddTimerEventCallback(MQWidgetSharedPtr<MQWidgetEventClosureBase> closure, unsigned int timeout_ms, bool overwrite);

private:
	std::vector<MQWidgetSharedPtr<MQWidgetEventClosureBase>> m_Events;

};

template<typename T> class MQWidgetEventClosure : public MQWidgetEventClosureBase
{
	typedef BOOL (T::*Func)(MQWidgetBase*, MQDocument doc);
	
public:
	MQWidgetEventClosure(T *_p, Func _f) : MQWidgetEventClosureBase(), p(_p), id(_p->GetID()), f(_f) { }
	
	BOOL invoke(MQWidgetBase *sender, MQDocument doc, void *ptr) override {
		if(MQWidgetBase::FindWidgetByID(id) != NULL){
			return (p->*f)(sender, doc);
		}
		return FALSE;
	}
	
	bool isEqual(const MQWidgetEventClosureBase *c) const override {
		if(typeid(*this) != typeid(*c)) return false;
		const MQWidgetEventClosure<T> *cc = static_cast<const MQWidgetEventClosure<T>*>(c);
		return (p == cc->p && f == cc->f);
	}
	
	MQWidgetBase *getReceiver() override { return p; }
	void *getFunction() override { return *(void**)&f; }
	
private:
	T *p;
	int id;
	Func f;
	
	MQWidgetEventClosure();
};

template<typename T> class MQWidgetMouseEventClosure : public MQWidgetEventClosureBase
{
	typedef BOOL (T::*Func)(MQWidgetBase*, MQDocument doc, MQWidgetMouseParam& param);
	
public:
	MQWidgetMouseEventClosure(T *_p, Func _f) : MQWidgetEventClosureBase(), p(_p), id(_p->GetID()), f(_f) { }
	
	BOOL invoke(MQWidgetBase *sender, MQDocument doc, void *ptr) override {
		if(MQWidgetBase::FindWidgetByID(id) != NULL){
			MQWidgetMouseParam *mouse_param = static_cast<MQWidgetMouseParam*>(ptr);
			return (p->*f)(sender, doc, *mouse_param);
		}
		return FALSE;
	}
	
	bool isEqual(const MQWidgetEventClosureBase *c) const override {
		if(typeid(*this) != typeid(*c)) return false;
		const MQWidgetMouseEventClosure<T> *cc = static_cast<const MQWidgetMouseEventClosure<T>*>(c);
		return (p == cc->p && f == cc->f);
	}
	
	MQWidgetBase *getReceiver() override { return p; }
	void *getFunction() override { return *(void**)&f; }

private:
	T *p;
	int id;
	Func f;
	
	MQWidgetMouseEventClosure();
};

template<typename T> class MQWidgetKeyEventClosure : public MQWidgetEventClosureBase
{
	typedef BOOL (T::*Func)(MQWidgetBase*, MQDocument doc, MQWidgetKeyParam& param);
	
public:
	MQWidgetKeyEventClosure(T *_p, Func _f) : MQWidgetEventClosureBase(), p(_p), id(_p->GetID()), f(_f) { }
	
	BOOL invoke(MQWidgetBase *sender, MQDocument doc, void *ptr) override {
		if(MQWidgetBase::FindWidgetByID(id) != NULL){
			MQWidgetKeyParam *key_param = static_cast<MQWidgetKeyParam*>(ptr);
			return (p->*f)(sender, doc, *key_param);
		}
		return FALSE;
	}
	
	bool isEqual(const MQWidgetEventClosureBase *c) const override {
		if(typeid(*this) != typeid(*c)) return false;
		const MQWidgetKeyEventClosure<T> *cc = static_cast<const MQWidgetKeyEventClosure<T>*>(c);
		return (p == cc->p && f == cc->f);
	}
	
	MQWidgetBase *getReceiver() override { return p; }
	void *getFunction() override { return *(void**)&f; }
	
private:
	T *p;
	int id;
	Func f;
	
	MQWidgetKeyEventClosure();
};

template<typename T> class MQWidgetPaintEventClosure : public MQWidgetEventClosureBase
{
	typedef BOOL (T::*Func)(MQWidgetBase*, MQDocument doc, MQWidgetPaintParam& param);
	
public:
	MQWidgetPaintEventClosure(T *_p, Func _f) : MQWidgetEventClosureBase(), p(_p), id(_p->GetID()), f(_f) { }
	
	BOOL invoke(MQWidgetBase *sender, MQDocument doc, void *ptr) override {
		if(MQWidgetBase::FindWidgetByID(id) != NULL){
			MQWidgetPaintParam *paint_param = static_cast<MQWidgetPaintParam*>(ptr);
			return (p->*f)(sender, doc, *paint_param);
		}
		return FALSE;
	}
	
	bool isEqual(const MQWidgetEventClosureBase *c) const override {
		if(typeid(*this) != typeid(*c)) return false;
		const MQWidgetPaintEventClosure<T> *cc = static_cast<const MQWidgetPaintEventClosure<T>*>(c);
		return (p == cc->p && f == cc->f);
	}
	
	MQWidgetBase *getReceiver() override { return p; }
	void *getFunction() override { return *(void**)&f; }
	
private:
	T *p;
	int id;
	Func f;
	
	MQWidgetPaintEventClosure();
};

template<typename T> class MQWidgetCloseQueryEventClosure : public MQWidgetEventClosureBase
{
	typedef BOOL (T::*Func)(MQWidgetBase*, MQDocument doc, MQWidgetCloseQueryParam& param);

public:
	MQWidgetCloseQueryEventClosure(T *_p, Func _f) : MQWidgetEventClosureBase(), p(_p), id(_p->GetID()), f(_f) { }

	BOOL invoke(MQWidgetBase *sender, MQDocument doc, void *ptr) override {
		if(MQWidgetBase::FindWidgetByID(id) != NULL){
			MQWidgetCloseQueryParam *close_param = static_cast<MQWidgetCloseQueryParam*>(ptr);
			return (p->*f)(sender, doc, *close_param);
		}
		return FALSE;
	}

	bool isEqual(const MQWidgetEventClosureBase *c) const override {
		if(typeid(*this) != typeid(*c)) return false;
		const MQWidgetCloseQueryEventClosure<T> *cc = static_cast<const MQWidgetCloseQueryEventClosure<T>*>(c);
		return (p == cc->p && f == cc->f);
	}

	MQWidgetBase *getReceiver() override { return p; }
	void *getFunction() override { return *(void**)&f; }

private:
	T *p;
	int id;
	Func f;

	MQWidgetCloseQueryEventClosure();
};

template<typename T> class MQWidgetDragOverEventClosure : public MQWidgetEventClosureBase
{
	typedef BOOL (T::*Func)(MQWidgetBase*, MQDocument doc, MQWidgetDragOverParam& param);
	
public:
	MQWidgetDragOverEventClosure(T *_p, Func _f) : MQWidgetEventClosureBase(), p(_p), id(_p->GetID()), f(_f) { }
	
	BOOL invoke(MQWidgetBase *sender, MQDocument doc, void *ptr) override {
		if(MQWidgetBase::FindWidgetByID(id) != NULL){
			MQWidgetDragOverParam *paint_param = static_cast<MQWidgetDragOverParam*>(ptr);
			return (p->*f)(sender, doc, *paint_param);
		}
		return FALSE;
	}
	
	bool isEqual(const MQWidgetEventClosureBase *c) const override {
		if(typeid(*this) != typeid(*c)) return false;
		const MQWidgetDragOverEventClosure<T> *cc = static_cast<const MQWidgetDragOverEventClosure<T>*>(c);
		return (p == cc->p && f == cc->f);
	}
	
	MQWidgetBase *getReceiver() override { return p; }
	void *getFunction() override { return *(void**)&f; }
	
private:
	T *p;
	int id;
	Func f;
	
	MQWidgetDragOverEventClosure();
};

template<typename T> class MQWidgetDropFilesEventClosure : public MQWidgetEventClosureBase
{
	typedef BOOL (T::*Func)(MQWidgetBase*, MQDocument doc, MQWidgetDropFilesParam& param);
	
public:
	MQWidgetDropFilesEventClosure(T *_p, Func _f) : MQWidgetEventClosureBase(), p(_p), id(_p->GetID()), f(_f) { }
	
	BOOL invoke(MQWidgetBase *sender, MQDocument doc, void *ptr) override {
		if(MQWidgetBase::FindWidgetByID(id) != NULL){
			MQWidgetDropFilesParam *paint_param = static_cast<MQWidgetDropFilesParam*>(ptr);
			return (p->*f)(sender, doc, *paint_param);
		}
		return FALSE;
	}
	
	bool isEqual(const MQWidgetEventClosureBase *c) const override {
		if(typeid(*this) != typeid(*c)) return false;
		const MQWidgetDropFilesEventClosure<T> *cc = static_cast<const MQWidgetDropFilesEventClosure<T>*>(c);
		return (p == cc->p && f == cc->f);
	}
	
	MQWidgetBase *getReceiver() override { return p; }
	void *getFunction() override { return *(void**)&f; }
	
private:
	T *p;
	int id;
	Func f;
	
	MQWidgetDropFilesEventClosure();
};

template<typename T> class MQListBoxDrawItemEventClosure : public MQWidgetEventClosureBase
{
	typedef BOOL (T::*Func)(MQWidgetBase*, MQDocument doc, MQListBoxDrawItemParam& param);
	
public:
	MQListBoxDrawItemEventClosure(T *_p, Func _f) : MQWidgetEventClosureBase(), p(_p), id(_p->GetID()), f(_f) { }
	
	BOOL invoke(MQWidgetBase *sender, MQDocument doc, void *ptr) override {
		if(MQWidgetBase::FindWidgetByID(id) != NULL){
			MQListBoxDrawItemParam *drawitem_param = static_cast<MQListBoxDrawItemParam*>(ptr);
			return (p->*f)(sender, doc, *drawitem_param);
		}
		return FALSE;
	}
	
	bool isEqual(const MQWidgetEventClosureBase *c) const override {
		if(typeid(*this) != typeid(*c)) return false;
		const MQListBoxDrawItemEventClosure<T> *cc = static_cast<const MQListBoxDrawItemEventClosure<T>*>(c);
		return (p == cc->p && f == cc->f);
	}
	
	MQWidgetBase *getReceiver() override { return p; }
	void *getFunction() override { return *(void**)&f; }
	
private:
	T *p;
	int id;
	Func f;
	
	MQListBoxDrawItemEventClosure();
};

template<typename T> class MQTreeListBoxDrawItemEventClosure : public MQWidgetEventClosureBase
{
	typedef BOOL (T::*Func)(MQWidgetBase*, MQDocument doc, MQTreeListBoxDrawItemParam& param);
	
public:
	MQTreeListBoxDrawItemEventClosure(T *_p, Func _f) : MQWidgetEventClosureBase(), p(_p), id(_p->GetID()), f(_f) { }
	
	BOOL invoke(MQWidgetBase *sender, MQDocument doc, void *ptr) override {
		if(MQWidgetBase::FindWidgetByID(id) != NULL){
			MQTreeListBoxDrawItemParam *drawitem_param = static_cast<MQTreeListBoxDrawItemParam*>(ptr);
			return (p->*f)(sender, doc, *drawitem_param);
		}
		return FALSE;
	}
	
	bool isEqual(const MQWidgetEventClosureBase *c) const override {
		if(typeid(*this) != typeid(*c)) return false;
		const MQTreeListBoxDrawItemEventClosure<T> *cc = static_cast<const MQTreeListBoxDrawItemEventClosure<T>*>(c);
		return (p == cc->p && f == cc->f);
	}
	
	MQWidgetBase *getReceiver() override { return p; }
	void *getFunction() override { return *(void**)&f; }
	
private:
	T *p;
	int id;
	Func f;
	
	MQTreeListBoxDrawItemEventClosure();
};

template<typename T> class MQMemoDrawItemEventClosure : public MQWidgetEventClosureBase
{
	typedef BOOL (T::*Func)(MQWidgetBase*, MQDocument doc, MQMemoDrawItemParam& param);

public:
	MQMemoDrawItemEventClosure(T *_p, Func _f) : MQWidgetEventClosureBase(), p(_p), id(_p->GetID()), f(_f) { }

	BOOL invoke(MQWidgetBase *sender, MQDocument doc, void *ptr) override {
		if(MQWidgetBase::FindWidgetByID(id) != NULL){
			MQMemoDrawItemParam *drawitem_param = static_cast<MQMemoDrawItemParam*>(ptr);
			return (p->*f)(sender, doc, *drawitem_param);
		}
		return FALSE;
	}

	bool isEqual(const MQWidgetEventClosureBase *c) const override {
		if(typeid(*this) != typeid(*c)) return false;
		const MQMemoDrawItemEventClosure<T> *cc = static_cast<const MQMemoDrawItemEventClosure<T>*>(c);
		return (p == cc->p && f == cc->f);
	}

	MQWidgetBase *getReceiver() override { return p; }
	void *getFunction() override { return *(void**)&f; }

private:
	T *p;
	int id;
	Func f;

	MQMemoDrawItemEventClosure();
};

template<typename T> inline void MQWidgetBase::AddShowEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument), bool prior) {
	AddEventCallback("show", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveShowEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) {
	RemoveEventCallback("show", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsShowEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) const {
	return ExistsEventCallback("show", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddHideEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument), bool prior) {
	AddEventCallback("hide", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveHideEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) {
	RemoveEventCallback("hide", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsHideEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) const {
	return ExistsEventCallback("hide", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddMoveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument), bool prior) {
	AddEventCallback("move", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveMoveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) {
	RemoveEventCallback("move", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsMoveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) const {
	return ExistsEventCallback("move", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddResizeEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument), bool prior) {
	AddEventCallback("resize", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveResizeEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) {
	RemoveEventCallback("resize", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsResizeEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) const {
	return ExistsEventCallback("resize", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddLeftDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior) {
	AddEventCallback("leftdown", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveLeftDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) {
	RemoveEventCallback("leftdown", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsLeftDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const {
	return ExistsEventCallback("leftdown", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddLeftUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior) {
	AddEventCallback("leftup", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveLeftUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) {
	RemoveEventCallback("leftup", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsLeftUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const {
	return ExistsEventCallback("leftup", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddLeftDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior) {
	AddEventCallback("leftdoubleclick", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveLeftDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) {
	RemoveEventCallback("leftdoubleclick", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsLeftDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const {
	return ExistsEventCallback("leftdoubleclick", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddMiddleDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior) {
	AddEventCallback("middledown", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveMiddleDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) {
	RemoveEventCallback("middledown", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsMiddleDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const {
	return ExistsEventCallback("middledown", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddMiddleUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior) {
	AddEventCallback("middleup", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveMiddleUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) {
	RemoveEventCallback("middleup", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsMiddleUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const {
	return ExistsEventCallback("middleup", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddMiddleDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior) {
	AddEventCallback("middledoubleclick", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveMiddleDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) {
	RemoveEventCallback("middledoubleclick", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsMiddleDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const {
	return ExistsEventCallback("middledoubleclick", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddRightDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior) {
	AddEventCallback("rightdown", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveRightDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) {
	RemoveEventCallback("rightdown", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsRightDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const {
	return ExistsEventCallback("rightdown", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddRightUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior) {
	AddEventCallback("rightup", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveRightUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) {
	RemoveEventCallback("rightup", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsRightUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const {
	return ExistsEventCallback("rightup", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddRightDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior) {
	AddEventCallback("rightdoubleclick", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveRightDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) {
	RemoveEventCallback("rightdoubleclick", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsRightDoubleClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const {
	return ExistsEventCallback("rightdoubleclick", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddMouseMoveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior) {
	AddEventCallback("mousemove", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveMouseMoveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) {
	RemoveEventCallback("mousemove", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsMouseMoveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const {
	return ExistsEventCallback("mousemove", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddMouseWheelEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&), bool prior) {
	AddEventCallback("mousewheel", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveMouseWheelEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) {
	RemoveEventCallback("mousewheel", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsMouseWheelEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetMouseParam&)) const {
	return ExistsEventCallback("mousewheel", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetMouseEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddMouseEnterEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument), bool prior) {
	AddEventCallback("mouseenter", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveMouseEnterEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) {
	RemoveEventCallback("mouseenter", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsMouseEnterEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) const {
	return ExistsEventCallback("mouseenter", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddMouseLeaveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument), bool prior) {
	AddEventCallback("mouseleave", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveMouseLeaveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) {
	RemoveEventCallback("mouseleave", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsMouseLeaveEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) const {
	return ExistsEventCallback("mouseleave", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddKeyDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetKeyParam&), bool prior) {
	AddEventCallback("keydown", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetKeyEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveKeyDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetKeyParam&)) {
	RemoveEventCallback("keydown", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetKeyEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsKeyDownEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetKeyParam&)) const {
	return ExistsEventCallback("keydown", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetKeyEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddKeyUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetKeyParam&), bool prior) {
	AddEventCallback("keyup", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetKeyEventClosure<T>(p, f)), prior);
}
template<typename T> inline void MQWidgetBase::RemoveKeyUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetKeyParam&)) {
	RemoveEventCallback("keyup", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetKeyEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsKeyUpEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetKeyParam&)) const {
	return ExistsEventCallback("keyup", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetKeyEventClosure<T>(p, f)));
}

template<typename T> inline void MQWidgetBase::AddTimerEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument), unsigned int timeout_ms, bool overwrite) {
	AddTimerEventCallback(MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), timeout_ms, overwrite);
}
template<typename T> inline void MQWidgetBase::RemoveTimerEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) {
	RemoveEventCallback("timer", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
}
template<typename T> inline bool MQWidgetBase::ExistsTimerEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument)) const {
	return ExistsEventCallback("timer", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
}

// Base window
// ベースウィンドウ
class MQWindowBase : public MQWidgetBase
{
public:
	// Destructor
	// デストラクタ
	~MQWindowBase();

	void AddChildWindow(MQWindowBase *child);
	void RemoveChildWindow(MQWindowBase *child);

	// A widget created by Create****() must be deleted by DeleteWidget() or will be automatically deleted together when this window is deleted.
	// Create****()で作成したウィジェットはDeleteWidget()で削除するか、またはこのウィンドウ削除時に自動的に削除されます。
	MQFrame *CreateHorizontalFrame(MQWidgetBase *parent);
	MQFrame *CreateVerticalFrame(MQWidgetBase *parent);
	MQDockFrame *CreateDockFrame(MQWidgetBase *parent);
	MQGroupBox *CreateGroupBox(MQWidgetBase *parent, const std::wstring& str = std::wstring());
	MQTab *CreateTab(MQWidgetBase *parent);
	MQButton *CreateButton(MQWidgetBase *parent, const std::wstring& str = std::wstring());
	MQCheckBox *CreateCheckBox(MQWidgetBase *parent, const std::wstring& str = std::wstring());
	MQRadioButton *CreateRadioButton(MQWidgetBase *parent, const std::wstring& str = std::wstring());
	MQComboBox *CreateComboBox(MQWidgetBase *parent);
	MQListBox *CreateListBox(MQWidgetBase *parent);
	MQCheckListBox *CreateCheckListBox(MQWidgetBase *parent);
	MQTreeListBox *CreateTreeListBox(MQWidgetBase *parent);
	MQLabel *CreateLabel(MQWidgetBase *parent, const std::wstring& str = std::wstring());
	MQEdit *CreateEdit(MQWidgetBase *parent, const std::wstring& str = std::wstring());
	MQMemo *CreateMemo(MQWidgetBase *parent);
	MQSpinBox *CreateSpinBox(MQWidgetBase *parent);
	MQDoubleSpinBox *CreateDoubleSpinBox(MQWidgetBase *parent);
	MQSlider *CreateSlider(MQWidgetBase *parent);
	MQProgressBar *CreateProgressBar(MQWidgetBase *parent);
	MQScrollBar *CreateScrollBar(MQWidgetBase *parent);
	MQScrollBox *CreateScrollBox(MQWidgetBase *parent);
	MQColorPanel *CreateColorPanel(MQWidgetBase *parent);
	MQPaintBox *CreatePaintBox(MQWidgetBase *parent);
	MQMenuBar *CreateMenuBar(MQWidgetBase *parent);

	// Delete a widget created by Create****().
	// Create****()で作成したウィジェットを削除します。
	void DeleteWidget(MQWidgetBase *widget);

	// Set this window as a modal window.
	void SetModal();
	// Release a modal status.
	void ReleaseModal();
	// Check if this window has a modal status.
	bool IsModal();

	// Get a window title.
	// ウィンドウのタイトル文字列を取得します。
	std::wstring GetTitle();

	// Set a window title.
	// ウィンドウのタイトル文字列を設定します。
	void SetTitle(const std::wstring& text);

	int GetPosX() const;
	void SetPosX(int value);

	int GetPosY() const;
	void SetPosY(int value);

	bool GetWindowFrame() const;
	void SetWindowFrame(bool value);

	bool GetTitleBar() const;
	void SetTitleBar(bool value);

	bool GetCanResize() const;
	void SetCanResize(bool value);

	bool GetCloseButton() const;
	void SetCloseButton(bool value);

	bool GetMaximizeButton() const;
	void SetMaximizeButton(bool value);

	bool GetMinimizeButton() const;
	void SetMinimizeButton(bool value);

	bool GetMaximized() const;
	void SetMaximized(bool value);

	bool GetMinimized() const;
	void SetMinimized(bool value);

	void GetBackColor(int& r, int& g, int& b) const;
	MQCanvasColor GetBackColor() const;
	void SetBackColor(int r, int g, int b);
	void SetBackColor(MQCanvasColor col);

	int GetAlphaBlend() const;
	void SetAlphaBlend(int value);

	bool GetAcceptDrops() const;
	void SetAcceptDrops(bool value);

	bool ExecuteMenuShortcut(MQWidgetKeyParam& param);

	template<typename T> void AddCloseQueryEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetCloseQueryParam&), bool prior = false) {
		AddEventCallback("closequery", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetCloseQueryEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveCloseQueryEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetCloseQueryParam&)) {
		RemoveEventCallback("closequery", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetCloseQueryEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsCloseQueryEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetCloseQueryParam&)) const {
		return ExistsEventCallback("closequery", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetCloseQueryEventClosure<T>(p, f)));
	}

	template<typename T> void AddDragOverEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetDragOverParam&), bool prior = false) {
		AddEventCallback("dragover", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetDragOverEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveDragOverEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetDragOverParam&)) {
		RemoveEventCallback("dragover", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetDragOverEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsDragOverEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetDragOverParam&)) const {
		return ExistsEventCallback("dragover", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetDragOverEventClosure<T>(p, f)));
	}

	template<typename T> void AddDropFilesEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetDropFilesParam&), bool prior = false) {
		AddEventCallback("dropfiles", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetDropFilesEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveDropFilesEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetDropFilesParam&)) {
		RemoveEventCallback("dropfiles", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetDropFilesEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsDropFilesEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetDropFilesParam&)) const {
		return ExistsEventCallback("dropfiles", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetDropFilesEventClosure<T>(p, f)));
	}

protected:
	// Constructor
	// コンストラクタ
	MQWindowBase();
	MQWindowBase(int id);

private:
	std::set<MQWidgetBase*> m_CreatedWidgets;
};


// Window
// ウィンドウ
class MQWindow : public MQWindowBase
{
public:
	// Constructor
	// コンストラクタ
	MQWindow();
	MQWindow(int id);
	MQWindow(MQWindowBase& parent);

	// Destructor
	// デストラクタ
	~MQWindow();

	static MQWindow GetMainWindow();
	static MQWindow *CreateWindow(MQWindowBase& parent);

private:
	void CreateWindowID();
};


// Docking window
// ドッキングウィンドウ
class MQDockWindow : public MQWindowBase
{
public:
	enum MQDockDirection {
		DOCK_NONE,
		DOCK_LEFT,
		DOCK_RIGHT,
		DOCK_TOP,
		DOCK_BOTTOM,
	};
	struct MQDockStatus {
		int Order;
		MQDockWindow *Parent;
		MQDockDirection Direction;
		double SizeRate;

		MQDockStatus(){
			Order = -1;
			Parent = nullptr;
			Direction = DOCK_NONE;
			SizeRate = 0.0;
		}
	};

public:
	// Constructor
	// コンストラクタ
	MQDockWindow();
	MQDockWindow(int id);
	MQDockWindow(MQWindowBase& parent);

	// Destructor
	// デストラクタ
	~MQDockWindow();

	void EnableDockableMenu();

	bool GetCanDock();
	void SetCanDock(bool value);

	bool GetShowDockingTitle();
	void SetShowDockingTitle(bool value);

	bool GetVerticalTitle();
	void SetVerticalTitle(bool value);

	bool IsDocking();
	void DockToFrame(MQDockFrame *frame, MQDockWindow *hierarchy_parent, MQDockDirection direction);
	void RedockWithJustSize();

	static MQDockWindow *CreateDockWindow(MQWindowBase& parent);

private:
	void CreateWindowID();
};


// Dialog
// ダイアログ
class MQDialog : public MQWindowBase
{
public:
	enum DIALOG_RESULT {
		DIALOG_NONE = 0,
		DIALOG_OK,
		DIALOG_CANCEL,
		DIALOG_YES,
		DIALOG_NO,
		DIALOG_ALL,
	};

public:
	// Constructor
	// コンストラクタ
	MQDialog();
	MQDialog(int id);
	MQDialog(MQWindowBase& parent);

	// Destructor
	// デストラクタ
	~MQDialog();

	DIALOG_RESULT Execute();
	void Close(DIALOG_RESULT code = DIALOG_NONE);

	static DIALOG_RESULT MessageWarningBox(MQWindowBase& parent, const std::wstring& message, const std::wstring& title);
	static DIALOG_RESULT MessageInformationBox(MQWindowBase& parent, const std::wstring& message, const std::wstring& title);
	static DIALOG_RESULT MessageYesNoBox(MQWindowBase& parent, const std::wstring& message, const std::wstring& title);
	static DIALOG_RESULT MessageYesNoCancelBox(MQWindowBase& parent, const std::wstring& message, const std::wstring& title);
	static DIALOG_RESULT MessageOkCancelBox(MQWindowBase& parent, const std::wstring& message, const std::wstring& title);
	static DIALOG_RESULT MessageBox(MQWindowBase& parent, const std::wstring& message, const std::wstring& title, const std::vector<DIALOG_RESULT>& buttons, int default_index = -1);

protected:
	MQDialog(MQWindowBase& parent, int dummy_for_no_creation);
private:
	void CreateDialogID();
};


// Popup
// ポップアップ
class MQPopup : public MQWindowBase
{
public:
	// Constructor
	// コンストラクタ
	MQPopup();
	MQPopup(int id);
	MQPopup(MQWindowBase& parent);

	// Destructor
	// デストラクタ
	~MQPopup();

	MQMenuItem *CreateMenuItem(const std::wstring& text = std::wstring());
	MQMenuItem *CreateSubMenuItem(MQMenuItem *parent, const std::wstring& text = std::wstring());

	void GetPreferredSidePosition(int& x, int& y, int& w, int& h, MQWidgetBase *widget, bool horz);

	void ShowPopup(int screen_x, int screen_y);

	bool GetShadow();
	void SetShadow(bool value);

	bool GetOverlay();
	void SetOverlay(bool value);

private:
	void CreatePopupID();

	std::set<MQMenuItem*> m_CreatedMenuItems;
};


// Frame
// フレーム
class MQFrameBase : public MQWidgetBase
{
public:
	enum MQFrameAlignment {
		ALIGN_NONE,
		ALIGN_HORIZONTAL,
		ALIGN_VERTICAL,
	};

protected:
	// Constructor
	// コンストラクタ
	MQFrameBase();
	MQFrameBase(int id);

public:
	// Destructor
	// デストラクタ
	~MQFrameBase();

	// Get a direction of an alignment for child widgets.
	// 子ウィジェットを配置する方向を取得します。
	MQFrameAlignment GetAlignment();

	// Set a direction of an alignment for child widgets.
	// 子ウィジェットを配置する方向を指定します。
	void SetAlignment(MQFrameAlignment align);

	// Check if children can be aligned on a single column or multiple columns.
	// 幅に応じて子ウィジェットを自動的に複数行に分割するかを取得します。
	bool GetMultiColumn();

	// Specify that children can be aligned on a single column or multiple columns.
	// 幅に応じて子ウィジェットを自動的に複数行に分割するかを設定します。
	void SetMultiColumn(bool value);

	// Get a number of chilren in a column.
	// １行に配置可能な子ウィジェットの数を取得します。
	int GetMatrixColumn();

	// Set a number of chilren in a column.
	// １行に配置可能な子ウィジェットの数を設定します。
	void SetMatrixColumn(int value);

	// Check if all children has the same width/height.
	// 子ウィジェットの幅を同じにするかどうかを取得します。
	bool GetUniformSize();

	// Specify that all children has the same width/height.
	// 子ウィジェットの幅を同じにするかどうかを設定します。
	void SetUniformSize(bool value);

	// Check if inner widgets can be resized by a dragging.
	// ドラッグにより内部のウィジェットの幅を変更可能にするかどうかを取得します。
	bool GetSplit();

	// Specify that inner widgets can be resized by a dragging.
	// ドラッグにより内部のウィジェットの幅を変更可能にするかどうかを設定します。
	void SetSplit(bool value);

};


// Frame
// フレーム
class MQFrame : public MQFrameBase
{
public:
	// Constructor
	// コンストラクタ
	MQFrame();
	MQFrame(int id);

	// Destructor
	// デストラクタ
	~MQFrame();

	void GetBackColor(int& r, int& g, int& b, int& a);
	MQCanvasColor GetBackColor();
	void SetBackColor(int r, int g, int b, int a);
	void SetBackColor(MQCanvasColor col);

};


// Docking frame
// ドックフレーム
class MQDockFrame : public MQFrameBase
{
public:
	// Constructor
	// コンストラクタ
	MQDockFrame();
	MQDockFrame(int id);

	// Destructor
	// デストラクタ
	~MQDockFrame();

	void RegisterDockableWindow(MQDockWindow *dock_window);
	void GetDockedWindowStatus(std::map<MQDockWindow*, MQDockWindow::MQDockStatus>& status);

	void GetBackColor(int& r, int& g, int& b, int& a);
	MQCanvasColor GetBackColor();
	void SetBackColor(int r, int g, int b, int a);
	void SetBackColor(MQCanvasColor col);
private:
	std::vector<std::pair<int,MQDockWindow*>> m_DockWindows;
};


// GroupBox
// グループボックス
class MQGroupBox : public MQFrameBase
{
public:
	// Constructor
	// コンストラクタ
	MQGroupBox();
	MQGroupBox(int id);

	// Destructor
	// デストラクタ
	~MQGroupBox();

	std::wstring GetText();
	void SetText(const std::wstring& text);

	bool GetCanMinimize();
	void SetCanMinimize(bool value);

	bool GetMinimized();
	void SetMinimized(bool value);

	bool GetShowTitle();
	void SetShowTitle(bool value);

};


// ScrollBox
// スクロールボックス
class MQScrollBox : public MQWidgetBase
{
public:
	enum MQScrollBoxBarStatus {
		SCROLLBAR_AUTO = 0,
		SCROLLBAR_OFF,
		SCROLLBAR_ON,
	};

public:
	// Constructor
	// コンストラクタ
	MQScrollBox();
	MQScrollBox(int id);

	// Destructor
	// デストラクタ
	~MQScrollBox();

	MQScrollBoxBarStatus GetHorzBarStatus();
	void SetHorzBarStatus(MQScrollBoxBarStatus value);

	MQScrollBoxBarStatus GetVertBarStatus();
	void SetVertBarStatus(MQScrollBoxBarStatus value);

	bool GetAutoWidgetScroll();
	void SetAutoWidgetScroll(bool value);


};


// Tab
// タブ
class MQTab : public MQWidgetBase
{
public:
	// Constructor
	// コンストラクタ
	MQTab();
	MQTab(int id);

	// Destructor
	// デストラクタ
	~MQTab();

	std::wstring GetTabTitle(int index);
	void SetTabTitle(int index, const std::wstring& text);

	int GetCurrentPage();
	void SetCurrentPage(int value);

	bool GetShowTab();
	void SetShowTab(bool value);

	bool GetExclusive();
	void SetExclusive(bool value);


	template<typename T> void AddChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

};


// Button
// ボタン
class MQButton : public MQWidgetBase
{
public:
	enum MQButtonTextAlignment {
		ALIGN_LEFT,
		ALIGN_RIGHT,
		ALIGN_CENTER,
		ALIGN_CENTER_EXCEPT_IMAGE,
	};

	enum MQButtonImagePosition {
		IMAGE_LEFT = 0,
		IMAGE_TOP,
		IMAGE_RIGHT,
		IMAGE_BOTTOM,
		IMAGE_ONLY,
	};

public:
	// Constructor
	// コンストラクタ
	MQButton();
	MQButton(int id);

	// Destructor
	// デストラクタ
	~MQButton();

	// Get a text displayed on the button.
	// ボタン上に表示される文字列を取得します。
	std::wstring GetText();

	// Set a text displayed on the button.
	// ボタン上に表示される文字列を設定します。
	void SetText(const std::wstring& text);

	std::wstring GetFontName();
	void SetFontName(const std::wstring& value);

	bool GetFontBold();
	void SetFontBold(bool value);

	void GetFontColor(int& r, int& g, int& b, int& a);
	void SetFontColor(int r, int g, int b, int a);
	MQCanvasColor GetFontColor();
	void SetFontColor(const MQCanvasColor& color);

	double GetFontScale();
	void SetFontScale(double value);

	MQButtonTextAlignment GetAlignment();
	void SetAlignment(MQButtonTextAlignment value);

	// Check if the button can be automatically switched.
	// 自動的にボタンのOn/Offを切り替えるどうかを取得します。
	bool GetToggle();

	// Specify that the button can be automatically switched.
	// 自動的にボタンのOn/Offを切り替えるどうかを設定します。
	void SetToggle(bool value);

	// Check if the button is down or up.
	// ボタンが押されているかどうかを取得します。
	bool GetDown();

	// Specify that the button is down or up.
	// ボタンが押されているかどうかを設定します。
	void SetDown(bool value);

	// Check if events are invoked repeatly while pushing the button.
	// ボタンが押し続けられたときにイベントを連続発生させるかどうかを取得します。
	bool GetRepeat();

	// Specify that events are invoked repeatly while pushing the button.
	// ボタンが押し続けられたときにイベントを連続発生させるかどうかを設定します。
	void SetRepeat(bool value);

	// Check if the button is displayed as connected with the neighbor buttons.
	// ボタンが隣のボタンとつながっているように表示されるかどうかを取得します。
	bool GetChain();

	// Specify that the button is displayed as connected with the neighbor buttons.
	// ボタンが隣のボタンとつながっているように表示されるかどうかを設定します。
	void SetChain(bool value);

	// Check if the button is displayed as a flat button.
	// ボタンの外観が平面スタイルかどうかを取得します。
	bool GetFlat();

	// Specify that the button is displayed as a flat button.
	// ボタンの外観が平面スタイルかどうかを設定します。
	void SetFlat(bool value);

	double GetPaddingX();
	void SetPaddingX(double value);

	double GetPaddingY();
	void SetPaddingY(double value);

	// Set as a default button called when an Enter key is pushed.
	// Enterキーを押したときに動作するデフォルトボタンとして設定します。
	void SetDefault(bool value);

	// Set as a cancel button called when an Esc key is pushed.
	// キャンセルボタンとして設定します。
	void SetCancel(bool value);

	// Set a modal result for a dialog.
	// ダイアログ用の結果を設定します。
	void SetModalResult(MQDialog::DIALOG_RESULT value);

	void SetSystemSVGFile(const wchar_t *filename);

	double GetImageScale();
	void SetImageScale(double value);

	MQButtonImagePosition GetImagePosition();
	void SetImagePosition(MQButtonImagePosition value);

	// Swap OK and Cancel buttons 'if necessary'. (for Mac)
	static void ReorderOKButton(MQWidgetBase *parent, MQButton *btn1, MQButton *btn2);


	template<typename T> void AddClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

	template<typename T> void AddRepeatEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveRepeatEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsRepeatEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

};


// Check box
// チェックボックス
class MQCheckBox : public MQWidgetBase
{
public:
	// Constructor
	// コンストラクタ
	MQCheckBox();
	MQCheckBox(int id);

	// Destructor
	// デストラクタ
	~MQCheckBox();

	// Get a checked status.
	// チェックされているかどうかを取得します。
	bool GetChecked();

	// Set a checked status.
	// チェックされているかどうかを設定します。
	void SetChecked(bool value);

	// Get a text displayed beside the check box.
	// チェックボックスの横に表示される文字列を取得します。
	std::wstring GetText();

	// Set a text displayed beside the check box.
	// チェックボックスの横に表示される文字列を指定します。
	void SetText(const std::wstring& text);

	void GetFontColor(int& r, int& g, int& b, int& a);
	void SetFontColor(int r, int g, int b, int a);
	MQCanvasColor GetFontColor();
	void SetFontColor(const MQCanvasColor& color);

	bool GetShadowText();
	void SetShadowText(bool value);

	template<typename T> void AddChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

};


// Radio button
// チェックボックス
class MQRadioButton : public MQWidgetBase
{
public:
	// Constructor
	// コンストラクタ
	MQRadioButton();
	MQRadioButton(int id);

	// Destructor
	// デストラクタ
	~MQRadioButton();

	// Get a checked status.
	// チェックされているかどうかを取得します。
	bool GetChecked();

	// Set a checked status.
	// チェックされているかどうかを設定します。
	void SetChecked(bool value);

	// Get a text displayed beside the radio button.
	// チェックボックスの横に表示される文字列を取得します。
	std::wstring GetText();

	// Set a text displayed beside the radio button.
	// チェックボックスの横に表示される文字列を指定します。
	void SetText(const std::wstring& text);

	void GetFontColor(int& r, int& g, int& b, int& a);
	void SetFontColor(int r, int g, int b, int a);
	MQCanvasColor GetFontColor();
	void SetFontColor(const MQCanvasColor& color);

	bool GetShadowText();
	void SetShadowText(bool value);

	template<typename T> void AddChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

};


// Combo box
// コンボボックス
class MQComboBox : public MQWidgetBase
{
public:
	// Constructor
	// コンストラクタ
	MQComboBox();
	MQComboBox(int id);

	// Destructor
	// デストラクタ
	~MQComboBox();

	int GetCurrentIndex();
	void SetCurrentIndex(int value);

	int AddItem(const std::wstring& text);
	int AddItem(const std::wstring& text, __int64 tag);
	void DeleteItem(int index);
	void ClearItems();
	int GetItemCount();
	std::wstring GetItem(int index);
	void SetItem(int index, const std::wstring& text);
	__int64 GetItemTag(int index);
	void SetItemTag(int index, __int64 tag);

	int GetNumVisible();
	void SetNumVisible(int value);


	template<typename T> void AddChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

};


// List box
// リストボックス
class MQListBox : public MQWidgetBase
{
public:
	enum MQListBoxStyle {
		STYLE_NORMAL,
		STYLE_ICON,
		STYLE_ICON_ONLY,
	};

public:
	// Constructor
	// コンストラクタ
	MQListBox();
	MQListBox(int id);

	// Destructor
	// デストラクタ
	~MQListBox();

	int GetCurrentIndex();
	void SetCurrentIndex(int value);

	void BeginUpdate();
	void EndUpdate();
	int AddItem(const std::wstring& text);
	int AddItem(const std::wstring& text, __int64 tag);
	void DeleteItem(int index);
	void ClearItems();
	int GetItemCount();
	std::wstring GetItem(int index);
	void SetItem(int index, const std::wstring& text);
	__int64 GetItemTag(int index);
	void SetItemTag(int index, __int64 tag);
	bool GetItemSelected(int index);
	void SetItemSelected(int index, bool selected);
	std::wstring GetItemHint(int index);
	void SetItemHint(int index, const std::wstring& hint);
	void SetItemDIB(int index, void *header, void *buffer);

	int GetVisibleRow();
	void SetVisibleRow(int value);
	double GetLineHeightRate();
	void SetLineHeightRate(double value);
	bool GetVertScrollVisible();
	void SetVertScrollVisible(bool value);
	bool GetMultiSelect();
	void SetMultiSelect(bool value);
	MQListBoxStyle GetListStyle();
	void SetListStyle(MQListBoxStyle style);
	double GetIconSizeRate();
	void SetIconSizeRate(double value);

	void ClearSelection();

	void MakeItemVisible(int index);
	int HitTestItem(int x, int y);
	void GetItemRect(int index, int& x, int& y, int& w, int& h);

	template<typename T> void AddChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> void AddDrawItemEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc, MQListBoxDrawItemParam& param), bool prior = false) {
		AddEventCallback("listdrawitem", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQListBoxDrawItemEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveDrawItemEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc, MQListBoxDrawItemParam& param)) {
		RemoveEventCallback("listdrawitem", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQListBoxDrawItemEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsDrawItemEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc, MQListBoxDrawItemParam& param)) const {
		return ExistsEventCallback("listdrawitem", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQListBoxDrawItemEventClosure<T>(p, f)));
	}

};


// Check List box
// チェックリストボックス
class MQCheckListBox : public MQWidgetBase
{
public:
	// Constructor
	// コンストラクタ
	MQCheckListBox();
	MQCheckListBox(int id);

	// Destructor
	// デストラクタ
	~MQCheckListBox();

	int GetCurrentIndex();
	void SetCurrentIndex(int value);

	void BeginUpdate();
	void EndUpdate();
	int AddItem(const std::wstring& text);
	int AddItem(const std::wstring& text, __int64 tag);
	void DeleteItem(int index);
	void ClearItems();
	int GetItemCount();
	std::wstring GetItem(int index);
	void SetItem(int index, const std::wstring& text);
	__int64 GetItemTag(int index);
	void SetItemTag(int index, __int64 tag);
	bool GetItemSelected(int index);
	void SetItemSelected(int index, bool selected);
	bool GetItemChecked(int index);
	void SetItemChecked(int index, bool checked);
	std::wstring GetItemHint(int index);
	void SetItemHint(int index, const std::wstring& hint);

	int GetVisibleRow();
	void SetVisibleRow(int value);
	double GetLineHeightRate();
	void SetLineHeightRate(double value);
	bool GetVertScrollVisible();
	void SetVertScrollVisible(bool value);
	bool GetMultiSelect();
	void SetMultiSelect(bool value);

	void ClearSelection();

	void MakeItemVisible(int index);
	int HitTestItem(int x, int y);
	void GetItemRect(int index, int& x, int& y, int& w, int& h);

	template<typename T> void AddChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}


};


// Tree List box
// ツリーリストボックス
class MQTreeListBox : public MQWidgetBase
{
public:
	enum {
		NullItemID = -1,
	};
public:
	// Constructor
	// コンストラクタ
	MQTreeListBox();
	MQTreeListBox(int id);

	// Destructor
	// デストラクタ
	~MQTreeListBox();

	int GetCurrentID();
	void SetCurrentID(int value);

	void BeginUpdate();
	void EndUpdate();
	int AddItem(const std::wstring& text);
	int AddItem(const std::wstring& text, __int64 tag);
	int AddItem(int parent_id, const std::wstring& text);
	int AddItem(int parent_id, const std::wstring& text, __int64 tag);
	void DeleteItem(int id);
	void ClearItems();
	void ReparentItem(int id, int new_parent_id);
	int GetItemCount();
	int GetItemIDByIndex(int index);
	int GetItemParent(int id);
	std::vector<int> GetItemChildren(int id);
	std::wstring GetItem(int id);
	void SetItem(int id, const std::wstring& text);
	__int64 GetItemTag(int id);
	void SetItemTag(int id, __int64 tag);
	bool GetItemSelected(int id);
	void SetItemSelected(int id, bool selected);
	std::wstring GetItemHint(int id);
	void SetItemHint(int id, const std::wstring& hint);
	bool GetItemCollapsed(int id);
	void SetItemCollapsed(int id, bool collapsed);

	int GetVisibleRow();
	void SetVisibleRow(int value);
	double GetLineHeightRate();
	void SetLineHeightRate(double value);
	bool GetHorzScrollVisible();
	void SetHorzScrollVisible(bool value);
	bool GetVertScrollVisible();
	void SetVertScrollVisible(bool value);
	bool GetMultiSelect();
	void SetMultiSelect(bool value);

	void ClearSelection();

	void MakeItemVisible(int id);
	int HitTestItem(int x, int y);
	void GetItemRect(int id, int& x, int& y, int& w, int& h);

	template<typename T> void AddChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> void AddDrawItemEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc, MQTreeListBoxDrawItemParam& param), bool prior = false) {
		AddEventCallback("treelistdrawitem", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQTreeListBoxDrawItemEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveDrawItemEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc, MQTreeListBoxDrawItemParam& param)) {
		RemoveEventCallback("treelistdrawitem", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQTreeListBoxDrawItemEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsDrawItemEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc, MQTreeListBoxDrawItemParam& param)) const {
		return ExistsEventCallback("treelistdrawitem", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQTreeListBoxDrawItemEventClosure<T>(p, f)));
	}

};


// Label
// ラベル
class MQLabel : public MQWidgetBase
{
public:
	enum MQLabelTextAlignment {
		ALIGN_LEFT,
		ALIGN_RIGHT,
		ALIGN_CENTER,
	};

public:
	// Constructor
	// コンストラクタ
	MQLabel();
	MQLabel(int id);

	// Destructor
	// デストラクタ
	~MQLabel();

	// Get a displayed text.
	// 表示される文字列を取得します。
	std::wstring GetText();

	// Set a displayed text.
	// 表示される文字列を指定します。
	void SetText(const std::wstring& text);

	std::wstring GetFontName();
	void SetFontName(const std::wstring& value);

	bool GetFontBold();
	void SetFontBold(bool value);

	void GetFontColor(int& r, int& g, int& b, int& a);
	void SetFontColor(int r, int g, int b, int a);
	MQCanvasColor GetFontColor();
	void SetFontColor(const MQCanvasColor& color);

	double GetFontScale();
	void SetFontScale(double value);

	MQLabelTextAlignment GetAlignment();
	void SetAlignment(MQLabelTextAlignment value);

	bool GetVerticalText();
	void SetVerticalText(bool value);

	bool GetWordWrap();
	void SetWordWrap(bool value);

	bool GetFrame();
	void SetFrame(bool value);

	bool GetShadowText();
	void SetShadowText(bool value);

	void SetSystemSVGFile(const wchar_t *filename);

	double GetImageScale();
	void SetImageScale(double value);
};


// Edit
// 文字入力
class MQEdit : public MQWidgetBase
{
public:
	enum MQEditTextAlignment {
		ALIGN_LEFT,
		ALIGN_RIGHT,
	};

	enum MQEditNumericType {
		NUMERIC_TEXT,
		NUMERIC_INT,
		NUMERIC_DOUBLE,
	};

public:
	// Constructor
	// コンストラクタ
	MQEdit();
	MQEdit(int id);

	// Destructor
	// デストラクタ
	~MQEdit();

	// Get a displayed text.
	// 表示される文字列を取得します。
	std::wstring GetText();

	// Set a displayed text.
	// 表示される文字列を指定します。
	void SetText(const std::wstring& text);

	std::wstring GetFontName();
	void SetFontName(const std::wstring& value);

	bool GetFontBold();
	void SetFontBold(bool value);

	double GetFontScale();
	void SetFontScale(double value);

	bool GetReadOnly();
	void SetReadOnly(bool value);

	bool GetPassword();
	void SetPassword(bool value);

	MQEditTextAlignment GetAlignment();
	void SetAlignment(MQEditTextAlignment value);

	MQEditNumericType GetNumeric();
	void SetNumeric(MQEditNumericType value);

	int GetMaxLength();
	void SetMaxLength(int value);

	int GetMaxAnsiLength();
	void SetMaxAnsiLength(int value);

	int GetVisibleColumn();
	void SetVisibleColumn(int value);

	bool GetEnterSelect();
	void SetEnterSelect(bool value);

	bool GetEnterKeyDefault();
	void SetEnterKeyDefault(bool value);

	void SetFocus(bool value);

	void SelectAll();
	void SelectRange(size_t start, size_t end);
	bool GetSelectedRange(size_t& start, size_t& end);
	void CutSelection();
	void CopySelection();
	void PasteFromClipboard();

	template<typename T> void AddChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

	template<typename T> void AddChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

};


// Text input with multiple columns
// 複数行テキスト入力
class MQMemo : public MQWidgetBase
{
public:
	enum {
		INVALID_POS = (size_t)-1,
	};
	enum MQBarStatus {
		SCROLLBAR_AUTO = 0,
		SCROLLBAR_OFF,
		SCROLLBAR_ON,
	};

public:
	// Constructor
	// コンストラクタ
	MQMemo();
	MQMemo(int id);

	// Destructor
	// デストラクタ
	~MQMemo();

	void AddLine(const std::wstring& str);
	std::wstring GetLine(int line_index);

	// Get a displayed text.
	// 表示される文字列を取得します。
	std::wstring GetText();
	
	size_t GetTextLength();

	// Set a displayed text.
	// 表示される文字列を指定します。
	void SetText(const std::wstring& text);

	std::wstring GetFontName();
	void SetFontName(const std::wstring& value);

	bool GetFontBold();
	void SetFontBold(bool value);

	double GetFontScale();
	void SetFontScale(double value);

	bool GetReadOnly();
	void SetReadOnly(bool value);

	bool GetPriorMenuShortcut();
	void SetPriorMenuShortcut(bool value);

	MQBarStatus GetHorzBarStatus();
	void SetHorzBarStatus(MQBarStatus value);

	MQBarStatus GetVertBarStatus();
	void SetVertBarStatus(MQBarStatus value);

	bool GetFocus();
	void SetFocus(bool value);

	size_t GetCaretPos();
	void SetCaretPos(size_t value);

	int GetTabColumn();
	void SetTabColumn(int value);

	bool GetAutoIndent();
	void SetAutoIndent(bool value);

	bool GetShowTabMark();
	void SetShowTabMark(bool value);

	bool GetShowReturnMark();
	void SetShowReturnMark(bool value);

	bool GetShowLineNumber();
	void SetShowLineNumber(bool value);

	bool GetSyntaxHighlight();
	void SetSyntaxHighlight(bool value);

	bool GetChanged();
	void SetChanged(bool value);

	std::wstring GetMarkCharacters();
	void SetMarkCharacters(const std::wstring& text);

	void AddSyntaxKeyword(const std::wstring& text);
	void ClearSyntaxKeyword();

	void AddRadixPrefix(const std::wstring& prefix);
	void ClearRadixPrefix();

	std::wstring GetSyntaxComment() const;
	void SetSyntaxComment(const std::wstring& word);

	void AddSyntaxMultiLineComment(const std::wstring& start, const std::wstring& end);
	void ClearSyntaxMultiLineComment();

	void AddSyntaxString(const std::wstring& start, const std::wstring& end);
	void ClearSyntaxString();

	void SelectAll();
	void SelectRange(size_t start, size_t end);
	bool GetSelectedRange(size_t& start, size_t& end);
	void CutSelection();
	void CopySelection();
	void PasteFromClipboard();
	void ReplaceSelectedText(const std::wstring& text);
	size_t FindString(const std::wstring& text, size_t start_pos, bool forward, bool matchcase, bool word);
	size_t FindStringFromCaretPos(const std::wstring& text, bool forward, bool matchcase, bool word);
	size_t FindNextWordBreak(size_t pos, bool forward);
	bool GetLineColumnByCaretPos(size_t pos, int& line, int& column);
	bool GetCaretPosByLineColumn(int line, int column, size_t& pos);

	bool CanUndo();
	bool CanRedo();
	void Undo();
	void Redo();

	template<typename T> void AddChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

	template<typename T> void AddChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

	template<typename T> void AddDrawItemEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc, MQMemoDrawItemParam& param), bool prior = false) {
		AddEventCallback("memodrawitem", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQMemoDrawItemEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveDrawItemEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc, MQMemoDrawItemParam& param)) {
		RemoveEventCallback("memodrawitem", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQMemoDrawItemEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsDrawItemEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc, MQMemoDrawItemParam& param)) const {
		return ExistsEventCallback("memodrawitem", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQMemoDrawItemEventClosure<T>(p, f)));
	}
};


// SpinBox
// 整数入力
class MQSpinBox : public MQWidgetBase
{
public:
	enum MQSpinBoxTextAlignment {
		ALIGN_LEFT,
		ALIGN_RIGHT,
	};

public:
	// Constructor
	// コンストラクタ
	MQSpinBox();
	MQSpinBox(int id);

	// Destructor
	// デストラクタ
	~MQSpinBox();

	int GetPosition();
	void SetPosition(int value);

	int GetMin();
	void SetMin(int value);

	int GetMax();
	void SetMax(int value);

	int GetIncrement();
	void SetIncrement(int value);

	MQSpinBoxTextAlignment GetAlignment();
	void SetAlignment(MQSpinBoxTextAlignment value);

	int GetVisibleColumn();
	void SetVisibleColumn(int value);

	bool GetEnterSelect();
	void SetEnterSelect(bool value);

	bool GetEnterKeyDefault();
	void SetEnterKeyDefault(bool value);

	void SetFocus(bool value);


	template<typename T> void AddChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

	template<typename T> void AddChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

};


// DoubleSpinBox
// 整数入力
class MQDoubleSpinBox : public MQWidgetBase
{
public:
	enum MQDoubleSpinBoxTextAlignment {
		ALIGN_LEFT,
		ALIGN_RIGHT,
	};

public:
	// Constructor
	// コンストラクタ
	MQDoubleSpinBox();
	MQDoubleSpinBox(int id);

	// Destructor
	// デストラクタ
	~MQDoubleSpinBox();

	double GetPosition();
	void SetPosition(double value);

	double GetMin();
	void SetMin(double value);

	double GetMax();
	void SetMax(double value);

	double GetIncrement();
	void SetIncrement(double value);

	bool GetExponential();
	void SetExponential(bool value);

	double GetMantissa();
	void SetMantissa(double value);

	int GetDecimalDigit();
	void SetDecimalDigit(int value);

	bool GetVariableDigit();
	void SetVariableDigit(bool value);

	int GetAutoDigit();
	void SetAutoDigit(int value);

	int GetMaxDecimalDigit();
	void SetMaxDecimalDigit(int value);

	MQDoubleSpinBoxTextAlignment GetAlignment();
	void SetAlignment(MQDoubleSpinBoxTextAlignment value);

	int GetVisibleColumn();
	void SetVisibleColumn(int value);

	bool GetEnterSelect();
	void SetEnterSelect(bool value);

	bool GetEnterKeyDefault();
	void SetEnterKeyDefault(bool value);

	void SetDisplayUnit(MQDISPLAYUNIT unit);

	void SetFocus(bool value);


	template<typename T> void AddChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

	template<typename T> void AddChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

};


// Slider
// スライダー
class MQSlider : public MQWidgetBase
{
public:
	// Constructor
	// コンストラクタ
	MQSlider();
	MQSlider(int id);

	// Destructor
	// デストラクタ
	~MQSlider();

	double GetPosition();
	void SetPosition(double value);

	double GetMin();
	void SetMin(double value);

	double GetMax();
	void SetMax(double value);


	template<typename T> void AddChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

	template<typename T> void AddChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

};


// Progress bar
// プログレスバー
class MQProgressBar : public MQWidgetBase
{
public:
	// Constructor
	// コンストラクタ
	MQProgressBar();
	MQProgressBar(int id);

	// Destructor
	// デストラクタ
	~MQProgressBar();

	double GetPosition();
	void SetPosition(double value);

	double GetMin();
	void SetMin(double value);

	double GetMax();
	void SetMax(double value);
};


// Scroll bar
// スクロールバー
class MQScrollBar : public MQWidgetBase
{
public:
	enum MQScrollBarDirection {
		DIRECTION_HORIZONTAL,
		DIRECTION_VERTICAL,
	};

public:
	// Constructor
	// コンストラクタ
	MQScrollBar();
	MQScrollBar(int id);

	// Destructor
	// デストラクタ
	~MQScrollBar();

	MQScrollBarDirection GetDirection();
	void SetDirection(MQScrollBarDirection value);

	int GetPosition();
	void SetPosition(int value);

	int GetMin();
	void SetMin(int value);

	int GetMax();
	void SetMax(int value);

	int GetPage();
	void SetPage(int value);

	int GetIncrement();
	void SetIncrement(int value);


	template<typename T> void AddChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

	template<typename T> void AddChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

};


// Color panel
// カラーパネル
class MQColorPanel : public MQWidgetBase
{
public:
	// Constructor
	// コンストラクタ
	MQColorPanel();
	MQColorPanel(int id);

	// Destructor
	// デストラクタ
	~MQColorPanel();

	void GetColor(int& r, int& g, int& b);
	void SetColor(int r, int g, int b);

	void GetHSV(double& h, double& s, double& v);
	void SetHSV(double h, double s, double v);


	template<typename T> void AddChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangedEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

	template<typename T> void AddChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsChangingEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("changing", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

};


// Paint box
// ペイントボックス
class MQPaintBox : public MQWidgetBase
{
public:
	// Constructor
	// コンストラクタ
	MQPaintBox();
	MQPaintBox(int id);

	// Destructor
	// デストラクタ
	~MQPaintBox();


	template<typename T> void AddPaintEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetPaintParam&), bool prior = false) {
		AddEventCallback("paint", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetPaintEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemovePaintEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetPaintParam&)) {
		RemoveEventCallback("paint", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetPaintEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsPaintEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument, MQWidgetPaintParam&)) const {
		return ExistsEventCallback("paint", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetPaintEventClosure<T>(p, f)));
	}

};


// Menu bar
// メニューバー
class MQMenuBar : public MQFrameBase
{
public:
	// Constructor
	// コンストラクタ
	MQMenuBar(MQWidgetBase *parent);
	MQMenuBar(int id);

	// Destructor
	// デストラクタ
	~MQMenuBar();

	MQMenuItem *CreateMenuItem(const std::wstring& text = std::wstring());
	MQMenuItem *CreateSubMenuItem(MQMenuItem *parent, const std::wstring& text = std::wstring());

private:
	std::set<MQMenuItem*> m_CreatedMenuItems;
};


// Menu item
// メニューアイテム
class MQMenuItem : public MQWidgetBase
{
public:
	// Constructor
	// コンストラクタ
	MQMenuItem(MQWidgetBase *parent);
	MQMenuItem(int id);

	// Destructor
	// デストラクタ
	~MQMenuItem();

	std::wstring GetText();
	void SetText(const std::wstring& text);

	bool GetChecked();
	void SetChecked(bool val);

	bool GetToggle();
	void SetToggle(bool val);

	bool GetClickClose();
	void SetClickClose(bool val);

	bool GetSeparator();
	void SetSeparator(bool val);

	std::wstring GetShortcutString();
	void SetShortcutString(const std::wstring& str);

	void SetSystemSVGFile(const wchar_t *filename);

	void SetRightIconSystemSVGFile(const wchar_t *filename);

	template<typename T> void AddClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("execute", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

	template<typename T> void AddRightIconClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc), bool prior = false) {
		AddEventCallback("righticonclick", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)), prior);
	}
	template<typename T> void RemoveRightIconClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) {
		RemoveEventCallback("righticonclick", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}
	template<typename T> bool ExistsRightIconClickEvent(T *p, BOOL (T::*f)(MQWidgetBase*, MQDocument doc)) const {
		return ExistsEventCallback("righticonclick", MQWidgetSharedPtr<MQWidgetEventClosureBase>(new MQWidgetEventClosure<T>(p, f)));
	}

};


// MQColorDialog
// カラーダイアログ
class MQColorDialog : public MQDialog
{
public:
	MQColorDialog(MQWindowBase& parent);
	virtual ~MQColorDialog();

	void GetColor(int& r, int& g, int& b);
	void SetColor(int r, int g, int b);

	void GetHSV(double& h, double& s, double& v);
	void SetHSV(double h, double s, double v);

private:
	void CreateColorDialogID();
};


// MQFileDialogBase
// ファイルダイアログ
class MQFileDialogBase
{
protected:
	// Constructor
	// コンストラクタ
	MQFileDialogBase();

public:
	// Destructor
	// デストラクタ
	virtual ~MQFileDialogBase();

	int AddFilter(const std::wstring& val);
	int GetFilterCount() const;
	std::wstring GetFilter(int index) const;
	void SetFilter(int index, const std::wstring& val);
	void ClearFilters();

	std::wstring GetTitle() const;
	void SetTitle(const std::wstring& val);

	std::wstring GetFileName() const;
	void SetFileName(const std::wstring& val);

	std::wstring GetInitialDir() const;
	void SetInitialDir(const std::wstring& val);

	std::wstring GetDefaultExt() const;
	void SetDefaultExt(const std::wstring& val);

	int GetFilterIndex() const;
	void SetFilterIndex(int val);

	bool GetNoChangeDir() const;
	void SetNoChangeDir(bool val);

public:
	enum {
		NullID = 0,
	};

protected:
	int m_ID;

};


class MQOpenFileDialog : public MQFileDialogBase
{
public:
	MQOpenFileDialog(MQWindowBase& parent);
	virtual ~MQOpenFileDialog();

	bool GetFileMustExist() const;
	void SetFileMustExist(bool val);

	bool GetMultiSelect() const;
	void SetMultiSelect(bool val);

	bool Execute();

	int GetFileNamesCount() const;
	std::wstring GetFileNames(int index) const;

};


class MQSaveFileDialog : public MQFileDialogBase
{
public:
	MQSaveFileDialog(MQWindowBase& parent);
	virtual ~MQSaveFileDialog();

	bool Execute();
};


// MQFolderDialog
// ファイルダイアログ
class MQFolderDialog
{
public:
	// Constructor
	// コンストラクタ
	MQFolderDialog(MQWindowBase& parent);
	// Destructor
	// デストラクタ
	virtual ~MQFolderDialog();

	std::wstring GetTitle() const;
	void SetTitle(const std::wstring& val);

	std::wstring GetFolder() const;
	void SetFolder(const std::wstring& val);

	bool GetNewFolder() const;
	void SetNewFolder(bool val);

	bool Execute();

public:
	enum {
		NullID = 0,
	};

protected:
	int m_ID;

};


struct MQCanvasPoint
{
	float x;
	float y;

	MQCanvasPoint() { }
	MQCanvasPoint(float _x, float _y) : x(_x), y(_y) { }
	MQCanvasPoint(const MQCanvasPoint& p) : x(p.x), y(p.y) { }

	float length() const { return (float)sqrt(x*x + y*y); }
	float length2() const { return x*x + y*y; }
	float innerprod(const MQCanvasPoint& p2) const { return x*p2.x + y*p2.y; }

	bool operator == (const MQCanvasPoint& p){
		return x == p.x && y == p.y;
	}
	bool operator != (const MQCanvasPoint& p){
		return !(x == p.x && y == p.y);
	}

	MQCanvasPoint& operator = (const MQCanvasPoint& p){
		x = p.x;
		y = p.y;
		return *this;
	}
	MQCanvasPoint& operator += (const MQCanvasPoint& p){
		x += p.x;
		y += p.y;
		return *this;
	}
	MQCanvasPoint& operator -= (const MQCanvasPoint& p){
		x -= p.x;
		y -= p.y;
		return *this;
	}
	MQCanvasPoint& operator *= (const MQCanvasPoint& p){
		x *= p.x;
		y *= p.y;
		return *this;
	}
	MQCanvasPoint& operator *= (float s){
		x *= s;
		y *= s;
		return *this;
	}
	MQCanvasPoint& operator /= (float s){
		x /= s;
		y /= s;
		return *this;
	}
	friend MQCanvasPoint operator + (const MQCanvasPoint& p1, const MQCanvasPoint& p2){
		return MQCanvasPoint(p1.x+p2.x, p1.y+p2.y);
	}
	friend MQCanvasPoint operator - (const MQCanvasPoint& p1, const MQCanvasPoint& p2){
		return MQCanvasPoint(p1.x-p2.x, p1.y-p2.y);
	}
	friend MQCanvasPoint operator * (const MQCanvasPoint& p1, const MQCanvasPoint& p2){
		return MQCanvasPoint(p1.x*p2.x, p1.y*p2.y);
	}
	friend MQCanvasPoint operator * (const MQCanvasPoint& p, float s){
		return MQCanvasPoint(p.x*s, p.y*s);
	}
	friend MQCanvasPoint operator * (float s, const MQCanvasPoint& p){
		return MQCanvasPoint(p.x*s, p.y*s);
	}
	friend MQCanvasPoint operator / (const MQCanvasPoint& p, float s){
		return MQCanvasPoint(p.x/s, p.y/s);
	}
	friend MQCanvasPoint operator - (const MQCanvasPoint& p){
		return MQCanvasPoint(-p.x, -p.y);
	}
};

class MQSVGDraw
{
	friend class MQCanvas;
public:
	MQSVGDraw();
	~MQSVGDraw();

	bool LoadFile(const wchar_t *filename);

private:
	void *m_Ptr;
};

class MQCanvas
{
public:
	enum MQCANVAS_CAP_TYPE {
		CAP_BUTT	= 0,
		CAP_ROUND	= 1,
		CAP_SQUARE	= 2,
	};
	
	enum MQCANVAS_JOIN_TYPE {
		JOIN_MITER	= 0,
		JOIN_ROUND	= 1,
		JOIN_BEVEL	= 2,
	};
public:
	MQCanvas(void *ptr);
	MQCanvas(int x1, int y1, int x2, int y2); // For offscreen image
	virtual ~MQCanvas();

	void GetBitmap(unsigned char*& buffer, size_t& row_bytes); // For offscreen image
	void GetCanvasRect(int& x, int& y, int& width, int& height);

	void SetColor(int r, int g, int b, int a);
	void SetColor(const MQCanvasColor& col) { SetColor(col.r, col.g, col.b, col.a); }
	void SetGradientColor(int x1, int y1, int x2, int y2, const std::vector<MQCanvasColor>& colors, const std::vector<float>& segments);
	void SetGradientColor(float x1, float y1, float x2, float y2, const std::vector<MQCanvasColor>& colors, const std::vector<float>& segments);

	void SetStrokeWidth(float width);
	void SetStrokeCap(MQCANVAS_CAP_TYPE cap);
	void SetStrokeJoin(MQCANVAS_JOIN_TYPE join);
	void SetStrokeMiterLimit(float limit);
	void SetStrokeDash(const std::vector<float>& intervals);
	void SetFont(const wchar_t *fontname, bool bold);
	void SetFontSize(int size);
	void SetFontRateSize(float rate);
	void SetAntiAlias(bool val);

	void PushClipRect(int x, int y, int w, int h);
	void PopClipRect();

	void Clear(int r, int g, int b, int a);
	void Clear(const MQCanvasColor& col) { Clear(col.r, col.g, col.b, col.a); }

	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawPolyline(const POINT *points, int num_points);
	void DrawPolyline(const MQCanvasPoint *points, int num_points);
	void DrawCircle(int x, int y, float r);
	void DrawCircle(float x, float y, float r);
	void FillCircle(int x, int y, float r);
	void FillCircle(float x, float y, float r);
	void DrawEllipse(int x, int y, float rx, float ry);
	void DrawEllipse(float x, float y, float rx, float ry);
	void FillEllipse(int x, int y, float rx, float ry);
	void FillEllipse(float x, float y, float rx, float ry);
	void DrawRect(int x, int y, int w, int h);
	void DrawRect(float x, float y, float w, float h);
	void FillRect(int x, int y, int w, int h);
	void FillRect(float x, float y, float w, float h);
	void DrawRoundRect(int x, int y, int w, int h, int rx, int ry);
	void DrawRoundRect(float x, float y, float w, float h, float rx, float ry);
	void FillRoundRect(int x, int y, int w, int h, int rx, int ry);
	void FillRoundRect(float x, float y, float w, float h, float rx, float ry);
	void DrawPolygon(const POINT *points, int num_points);
	void DrawPolygon(const MQCanvasPoint *points, int num_points);
	void FillPolygon(const POINT *points, int num_points);
	void FillPolygon(const MQCanvasPoint *points, int num_points);
	void DrawDIB(void *header, void *buffer, int x, int y);
	void DrawDIB(void *header, void *buffer, int x, int y, int w, int h);
	void DrawSVG(MQSVGDraw *svg, int x, int y, int w, int h);
	void DrawText(const wchar_t *str, int x, int y, int w, int h, bool horz_center, bool vert_center = true);
	POINT MeasureText(const wchar_t *str);

private:
	void *m_Ptr;
	bool m_Owner;
};


#endif //_MQWIDGET_H_
